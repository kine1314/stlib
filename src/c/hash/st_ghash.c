/*
 * st_ghash.c
 *
 *  Created on: 2011-11-18
 *      Author: kine
 */
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "st_ghash.h"

#define HASH_TABLE_MIN_SHIFT 3  /* 1 << 3 == 8 buckets */

typedef struct
{
    STHashTable  *hash_table;
    stpointer     dummy1;
    stpointer     dummy2;
    int          position;
    stbool     dummy3;
    int          version;
} RealIter;

/* Each table size has an associated prime modulo (the first prime
 * lower than the table size) used to find the initial bucket. Probing
 * then works modulo 2^n. The prime modulo is necessary to get a
 * good distribution with poor hash functions. */
static const stint prime_mod [] =
{
    1,          /* For 1 << 0 */
    2,
    3,
    7,
    13,
    31,
    61,
    127,
    251,
    509,
    1021,
    2039,
    4093,
    8191,
    16381,
    32749,
    65521,      /* For 1 << 16 */
    131071,
    262139,
    524287,
    1048573,
    2097143,
    4194301,
    8388593,
    16777213,
    33554393,
    67108859,
    134217689,
    268435399,
    536870909,
    1073741789,
    2147483647  /* For 1 << 31 */
};

    static void
st_hash_table_set_shift (STHashTable *hash_table, stint shift)
{
    stint i;
    stuint mask = 0;

    hash_table->size = 1 << shift;
    hash_table->mod  = prime_mod [shift];

    for (i = 0; i < shift; i++)
    {
        mask <<= 1;
        mask |= 1;
    }

    hash_table->mask = mask;
}

    static stint
st_hash_table_find_closest_shift (stint n)
{
    stint i;

    for (i = 0; n; i++)
        n >>= 1;

    return i;
}

    static void
st_hash_table_set_shift_from_size (STHashTable *hash_table, stint size)
{
    stint shift;

    shift = st_hash_table_find_closest_shift (size);
    shift = MAX (shift, HASH_TABLE_MIN_SHIFT);

    st_hash_table_set_shift (hash_table, shift);
}

/*
 * st_hash_table_lookup_node:
 * @hash_table: our #STHashTable
 * @key: the key to lookup against
 * @hash_return: optional key hash return location
 * Return value: index of the described #STHashNode
 *
 * Performs a lookup in the hash table.  Virtually all hash operations
 * will use this function internally.
 *
 * This function first computes the hash value of the key using the
 * user's hash function.
 *
 * If an entry in the table matching @key is found then this function
 * returns the index of that entry in the table, and if not, the
 * index of an empty node (never a tombstone).
 */
    static stinline stuint
st_hash_table_lookup_node (STHashTable    *hash_table,
        stconstpointer  key)
{
    STHashNode *node;
    stuint node_index;
    stuint hash_value;
    stuint step = 0;

    /* Empty buckets have hash_value set to 0, and for tombstones, it's 1.
     * We need to make sure our hash value is not one of these. */

    hash_value = (* hash_table->hash_func) (key);
    if (hash_value <= 1)
        hash_value = 2;

    node_index = hash_value % hash_table->mod;
    node = &hash_table->nodes [node_index];

    while (node->key_hash)
    {
        /*  We first check if our full hash values
         *  are equal so we can avoid calling the full-blown
         *  key equality function in most cases.
         */

        if (node->key_hash == hash_value)
        {
            if (hash_table->key_equal_func)
            {
                if (hash_table->key_equal_func (node->key, key))
                    break;
            }
            else if (node->key == key)
            {
                break;
            }
        }

        step++;
        node_index += step;
        node_index &= hash_table->mask;
        node = &hash_table->nodes[node_index];
    }

    return node_index;
}

/*
 * st_hash_table_lookup_node_for_insertion:
 * @hash_table: our #STHashTable
 * @key: the key to lookup against
 * @hash_return: key hash return location
 * Return value: index of the described #STHashNode
 *
 * Performs a lookup in the hash table, preserving extra information
 * usually needed for insertion.
 *
 * This function first computes the hash value of the key using the
 * user's hash function.
 *
 * If an entry in the table matching @key is found then this function
 * returns the index of that entry in the table, and if not, the
 * index of an unused node (empty or tombstone) where the key can be
 * inserted.
 *
 * The computed hash value is returned in the variable pointed to
 * by @hash_return. This is to save insertions from having to compute
 * the hash record again for the new record.
 */
    static stinline stuint
st_hash_table_lookup_node_for_insertion (STHashTable    *hash_table,
        stconstpointer  key,
        stuint         *hash_return)
{
    STHashNode *node;
    stuint node_index;
    stuint hash_value;
    stuint first_tombstone;
    stbool have_tombstone = FALSE;
    stuint step = 0;

    /* Empty buckets have hash_value set to 0, and for tombstones, it's 1.
     * We need to make sure our hash value is not one of these. */

    hash_value = (* hash_table->hash_func) (key);
    if (hash_value <= 1)
        hash_value = 2;

    *hash_return = hash_value;

    node_index = hash_value % hash_table->mod;
    node = &hash_table->nodes [node_index];

    while (node->key_hash)
    {
        /*  We first check if our full hash values
         *  are equal so we can avoid calling the full-blown
         *  key equality function in most cases.
         */

        if (node->key_hash == hash_value)
        {
            if (hash_table->key_equal_func)
            {
                if (hash_table->key_equal_func (node->key, key))
                    return node_index;
            }
            else if (node->key == key)
            {
                return node_index;
            }
        }
        else if (node->key_hash == 1 && !have_tombstone)
        {
            first_tombstone = node_index;
            have_tombstone = TRUE;
        }

        step++;
        node_index += step;
        node_index &= hash_table->mask;
        node = &hash_table->nodes [node_index];
    }

    if (have_tombstone)
        return first_tombstone;

    return node_index;
}

/*
 * st_hash_table_remove_node:
 * @hash_table: our #STHashTable
 * @node: pointer to node to remove
 * @notify: %TRUE if the destroy notify handlers are to be called
 *
 * Removes a node from the hash table and updates the node count.
 * The node is replaced by a tombstone. No table resize is performed.
 *
 * If @notify is %TRUE then the destroy notify functions are called
 * for the key and value of the hash node.
 */
    static void
st_hash_table_remove_node (STHashTable   *hash_table,
        STHashNode    *node,
        stbool      notify)
{
    if (notify && hash_table->key_destroy_func)
        hash_table->key_destroy_func (node->key);

    if (notify && hash_table->value_destroy_func)
        hash_table->value_destroy_func (node->value);

    /* Erect tombstone */
    node->key_hash = 1;

    /* Be GC friendly */
    node->key = NULL;
    node->value = NULL;

    hash_table->nnodes--;
}

/*
 * st_hash_table_remove_all_nodes:
 * @hash_table: our #STHashTable
 * @notify: %TRUE if the destroy notify handlers are to be called
 *
 * Removes all nodes from the table.  Since this may be a precursor to
 * freeing the table entirely, no resize is performed.
 *
 * If @notify is %TRUE then the destroy notify functions are called
 * for the key and value of the hash node.
 */
    static void
st_hash_table_remove_all_nodes (STHashTable *hash_table,
        stbool    notify)
{
    int i;

    for (i = 0; i < hash_table->size; i++)
    {
        STHashNode *node = &hash_table->nodes [i];

        if (node->key_hash > 1)
        {
            if (notify && hash_table->key_destroy_func)
                hash_table->key_destroy_func (node->key);

            if (notify && hash_table->value_destroy_func)
                hash_table->value_destroy_func (node->value);
        }
    }

    /* We need to set node->key_hash = 0 for all nodes - might as well be GC
     * friendly and clear everything */
    memset (hash_table->nodes, 0, hash_table->size * sizeof (STHashNode));

    hash_table->nnodes = 0;
    hash_table->noccupied = 0;
}

/*
 * st_hash_table_resize:
 * @hash_table: our #STHashTable
 *
 * Resizes the hash table to the optimal size based on the number of
 * nodes currently held.  If you call this function then a resize will
 * occur, even if one does not need to occur.  Use
 * st_hash_table_maybe_resize() instead.
 *
 * This function may "resize" the hash table to its current size, with
 * the side effect of cleaning up tombstones and otherwise optimizing
 * the probe sequences.
 */
    static void
st_hash_table_resize (STHashTable *hash_table)
{
    STHashNode *new_nodes;
    stint old_size;
    stint i;

    old_size = hash_table->size;
    st_hash_table_set_shift_from_size (hash_table, hash_table->nnodes * 2);

    new_nodes = (STHashNode *)malloc(hash_table->size);

    for (i = 0; i < old_size; i++)
    {
        STHashNode *node = &hash_table->nodes [i];
        STHashNode *new_node;
        stuint hash_val;
        stuint step = 0;

        if (node->key_hash <= 1)
            continue;

        hash_val = node->key_hash % hash_table->mod;
        new_node = &new_nodes [hash_val];

        while (new_node->key_hash)
        {
            step++;
            hash_val += step;
            hash_val &= hash_table->mask;
            new_node = &new_nodes [hash_val];
        }

        *new_node = *node;
    }

    free (hash_table->nodes);
    hash_table->nodes = new_nodes;
    hash_table->noccupied = hash_table->nnodes;
}

/*
 * st_hash_table_maybe_resize:
 * @hash_table: our #STHashTable
 *
 * Resizes the hash table, if needed.
 *
 * Essentially, calls st_hash_table_resize() if the table has strayed
 * too far from its ideal size for its number of nodes.
 */
    static stinline void
st_hash_table_maybe_resize (STHashTable *hash_table)
{
    stint noccupied = hash_table->noccupied;
    stint size = hash_table->size;

    if ((size > hash_table->nnodes * 4 && size > 1 << HASH_TABLE_MIN_SHIFT) ||
            (size <= noccupied + (noccupied / 16)))
        st_hash_table_resize (hash_table);
}

/**
 * st_hash_table_new:
 * @hash_func: a function to create a hash value from a key.
 *   Hash values are used to determine where keys are stored within the
 *   #STHashTable data structure. The st_direct_hash(), st_int_hash() and
 *   st_str_hash() functions are provided for some common types of keys.
 *   If hash_func is %NULL, st_direct_hash() is used.
 * @key_equal_func: a function to check two keys for equality.  This is
 *   used when looking up keys in the #STHashTable.  The st_direct_equal(),
 *   st_int_equal() and st_str_equal() functions are provided for the most
 *   common types of keys. If @key_equal_func is %NULL, keys are compared
 *   directly in a similar fashion to st_direct_equal(), but without the
 *   overhead of a function call.
 *
 * Creates a new #STHashTable with a reference count of 1.
 *
 * Return value: a new #STHashTable.
 **/
STHashTable*
st_hash_table_new (STHashFunc    hash_func,
        STEqualFunc   key_equal_func)
{
    return st_hash_table_new_full (hash_func, key_equal_func, NULL, NULL);
}


/**
 * st_hash_table_new_full:
 * @hash_func: a function to create a hash value from a key.
 * @key_equal_func: a function to check two keys for equality.
 * @key_destroy_func: a function to free the memory allocated for the key
 *   used when removing the entry from the #STHashTable or %NULL if you
 *   don't want to supply such a function.
 * @value_destroy_func: a function to free the memory allocated for the
 *   value used when removing the entry from the #STHashTable or %NULL if
 *   you don't want to supply such a function.
 *
 * Creates a new #STHashTable like st_hash_table_new() with a reference count
 * of 1 and allows to specify functions to free the memory allocated for the
 * key and value that get called when removing the entry from the #STHashTable.
 *
 * Return value: a new #STHashTable.
 **/
    STHashTable*
st_hash_table_new_full (STHashFunc       hash_func,
        STEqualFunc      key_equal_func,
        STDestroyNotify  key_destroy_func,
        STDestroyNotify  value_destroy_func)
{
    STHashTable *hash_table;

    hash_table = (STHashTable *)malloc(sizeof(STHashTable));
    st_hash_table_set_shift (hash_table, HASH_TABLE_MIN_SHIFT);
    hash_table->nnodes             = 0;
    hash_table->noccupied          = 0;
    hash_table->hash_func          = hash_func;
    hash_table->key_equal_func     = key_equal_func;
    hash_table->ref_count          = 1;

    hash_table->key_destroy_func   = key_destroy_func;
    hash_table->value_destroy_func = value_destroy_func;
    hash_table->nodes              = (STHashNode*)malloc(hash_table->size);

    return hash_table;
}

/**
 * st_hash_table_iter_init:
 * @iter: an uninitialized #STHashTableIter.
 * @hash_table: a #STHashTable.
 *
 * Initializes a key/value pair iterator and associates it with
 * @hash_table. Modifying the hash table after calling this function
 * invalidates the returned iterator.
 * |[
 * STHashTableIter iter;
 * stpointer key, value;
 *
 * st_hash_table_iter_init (&iter, hash_table);
 * while (st_hash_table_iter_next (&iter, &key, &value))
 *   {
 *     /&ast; do something with key and value &ast;/
 *   }
 * ]|
 *
 * Since: 2.16
 **/
    void
st_hash_table_iter_init (STHashTableIter *iter,
        STHashTable     *hash_table)
{
    RealIter *ri = (RealIter *) iter;

    if(NULL == iter || NULL == hash_table)
    	return

    ri->hash_table = hash_table;
    ri->position = -1;

}

/**
 * st_hash_table_iter_next:
 * @iter: an initialized #STHashTableIter.
 * @key: a location to store the key, or %NULL.
 * @value: a location to store the value, or %NULL.
 *
 * Advances @iter and retrieves the key and/or value that are now
 * pointed to as a result of this advancement. If %FALSE is returned,
 * @key and @value are not set, and the iterator becomes invalid.
 *
 * Return value: %FALSE if the end of the #STHashTable has been reached.
 *
 * Since: 2.16
 **/
    stbool
st_hash_table_iter_next (STHashTableIter *iter,
        stpointer       *key,
        stpointer       *value)
{
    RealIter *ri = (RealIter *) iter;
    STHashNode *node;
    stint position;

    if(NULL == iter || ri->position >= ri->hash_table->size)
    	return FALSE ;

    position = ri->position;

    do
    {
        position++;
        if (position >= ri->hash_table->size)
        {
            ri->position = position;
            return FALSE;
        }

        node = &ri->hash_table->nodes [position];
    }
    while (node->key_hash <= 1);

    if (key != NULL)
        *key = node->key;
    if (value != NULL)
        *value = node->value;

    ri->position = position;
    return TRUE;
}

/**
 * st_hash_table_iter_get_hash_table:
 * @iter: an initialized #STHashTableIter.
 *
 * Returns the #STHashTable associated with @iter.
 *
 * Return value: the #STHashTable associated with @iter.
 *
 * Since: 2.16
 **/
STHashTable *
st_hash_table_iter_get_hash_table (STHashTableIter *iter)
{
    if(NULL == iter)
    	return NULL ;

    return ((RealIter *) iter)->hash_table;
}

static void
iter_remove_or_steal (RealIter *ri, stbool notify)
{
    if(NULL == ri || ri->position < 0 || ri->position >= ri->hash_table->size)
    	return ;

    st_hash_table_remove_node (ri->hash_table, &ri->hash_table->nodes [ri->position], notify);
}

/**
 * st_hash_table_iter_remove():
 * @iter: an initialized #STHashTableIter.
 *
 * Removes the key/value pair currently pointed to by the iterator
 * from its associated #STHashTable. Can only be called after
 * st_hash_table_iter_next() returned %TRUE, and cannot be called more
 * than once for the same key/value pair.
 *
 * If the #STHashTable was created using st_hash_table_new_full(), the
 * key and value are freed using the supplied destroy functions, otherwise
 * you have to make sure that any dynamically allocated values are freed
 * yourself.
 *
 * Since: 2.16
 **/
void
st_hash_table_iter_remove (STHashTableIter *iter)
{
    iter_remove_or_steal ((RealIter *) iter, TRUE);
}

/**
 * st_hash_table_iter_steal():
 * @iter: an initialized #STHashTableIter.
 *
 * Removes the key/value pair currently pointed to by the iterator
 * from its associated #STHashTable, without calling the key and value
 * destroy functions. Can only be called after
 * st_hash_table_iter_next() returned %TRUE, and cannot be called more
 * than once for the same key/value pair.
 *
 * Since: 2.16
 **/
void
st_hash_table_iter_steal (STHashTableIter *iter)
{
    iter_remove_or_steal ((RealIter *) iter, FALSE);
}






#if !defined(WIN32)

#if     __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
#define G_GNUC_MAY_ALIAS __attribute__((may_alias))
#else
#define G_GNUC_MAY_ALIAS
#endif
/* Adapted from CVS version 1.9 of glibc's sysdeps/x86_64/bits/atomic.h
 */
stint
st_atomic_int_exchange_and_add (volatile stint G_GNUC_MAY_ALIAS *atomic,
			       stint           val)
{
  stint result;

  __asm__ __volatile__ ("lock; xaddl %0,%1"
                        : "=r" (result), "=m" (*atomic)
			: "0" (val), "m" (*atomic));
  return result;
}

void
st_atomic_int_add (volatile stint G_GNUC_MAY_ALIAS *atomic, stint           val)
{
  __asm__ __volatile__ ("lock; addl %1,%0"
			: "=m" (*atomic)
			: "ir" (val), "m" (*atomic));
}
#endif /* DEFINE_WITH_WIN32_INTERLOCKED */


/**
 * st_hash_table_ref:
 * @hash_table: a valid #STHashTable.
 *
 * Atomically increments the reference count of @hash_table by one.
 * This function is MT-safe and may be called from any thread.
 *
 * Return value: the passed in #STHashTable.
 *
 * Since: 2.10
 **/
STHashTable*
st_hash_table_ref (STHashTable *hash_table)
{
    if(NULL == hash_table)
    	return NULL ;

    if(hash_table->ref_count <= 0)
    	return hash_table ;

#if !defined(WIN32)
    st_atomic_int_add (&hash_table->ref_count, 1);
#endif
    return hash_table;
}

/**
 * st_hash_table_unref:
 * @hash_table: a valid #STHashTable.
 *
 * Atomically decrements the reference count of @hash_table by one.
 * If the reference count drops to 0, all keys and values will be
 * destroyed, and all memory allocated by the hash table is released.
 * This function is MT-safe and may be called from any thread.
 *
 * Since: 2.10
 **/
void
st_hash_table_unref (STHashTable *hash_table)
{
    if(NULL == hash_table || hash_table->ref_count <= 0)
    	return ;

#if !defined(WIN32)
    if (st_atomic_int_exchange_and_add (&hash_table->ref_count, -1) - 1 == 0)
#endif
    {
        st_hash_table_remove_all_nodes (hash_table, TRUE);
        free (hash_table->nodes);
        free (hash_table);
    }
}

/**
 * st_hash_table_destroy:
 * @hash_table: a #STHashTable.
 *
 * Destroys all keys and values in the #STHashTable and decrements its
 * reference count by 1. If keys and/or values are dynamically allocated,
 * you should either free them first or create the #STHashTable with destroy
 * notifiers using st_hash_table_new_full(). In the latter case the destroy
 * functions you supplied will be called on all keys and values during the
 * destruction phase.
 **/
void
st_hash_table_destroy (STHashTable *hash_table)
{
    if(NULL == hash_table || hash_table->ref_count <= 0)
		return ;

    st_hash_table_remove_all (hash_table);
    st_hash_table_unref (hash_table);
}

/**
 * st_hash_table_lookup:
 * @hash_table: a #STHashTable.
 * @key: the key to look up.
 *
 * Looks up a key in a #STHashTable. Note that this function cannot
 * distinguish between a key that is not present and one which is present
 * and has the value %NULL. If you need this distinction, use
 * st_hash_table_lookup_extended().
 *
 * Return value: the associated value, or %NULL if the key is not found.
 **/
stpointer
st_hash_table_lookup (STHashTable   *hash_table,
        stconstpointer key)
{
    STHashNode *node;
    stuint      node_index;

    if(NULL == hash_table)
    	return NULL ;

    node_index = st_hash_table_lookup_node (hash_table, key);
    node = &hash_table->nodes [node_index];

    return node->key_hash ? node->value : NULL;
}

/**
 * st_hash_table_lookup_extended:
 * @hash_table: a #STHashTable
 * @lookup_key: the key to look up
 * @orig_key: return location for the original key, or %NULL
 * @value: return location for the value associated with the key, or %NULL
 *
 * Looks up a key in the #STHashTable, returning the original key and the
 * associated value and a #stbool which is %TRUE if the key was found. This
 * is useful if you need to free the memory allocated for the original key,
 * for example before calling st_hash_table_remove().
 *
 * You can actually pass %NULL for @lookup_key to test
 * whether the %NULL key exists.
 *
 * Return value: %TRUE if the key was found in the #STHashTable.
 **/
stbool
st_hash_table_lookup_extended (STHashTable    *hash_table,
        stconstpointer  lookup_key,
        stpointer      *orig_key,
        stpointer      *value)
{
    STHashNode *node;
    stuint      node_index;

    if(NULL == hash_table)
    	return FALSE ;

    node_index = st_hash_table_lookup_node (hash_table, lookup_key);
    node = &hash_table->nodes [node_index];

    if (!node->key_hash)
        return FALSE;

    if (orig_key)
        *orig_key = node->key;

    if (value)
        *value = node->value;

    return TRUE;
}

/*
 * st_hash_table_insert_internal:
 * @hash_table: our #STHashTable
 * @key: the key to insert
 * @value: the value to insert
 * @keep_new_key: if %TRUE and this key already exists in the table
 *   then call the destroy notify function on the old key.  If %FALSE
 *   then call the destroy notify function on the new key.
 *
 * Implements the common logic for the st_hash_table_insert() and
 * st_hash_table_replace() functions.
 *
 * Do a lookup of @key.  If it is found, replace it with the new
 * @value (and perhaps the new @key).  If it is not found, create a
 * new node.
 */
static void
st_hash_table_insert_internal (STHashTable *hash_table,
        stpointer    key,
        stpointer    value,
        stbool    keep_new_key)
{
    STHashNode *node;
    stuint node_index;
    stuint key_hash;
    stuint old_hash;

    if(NULL == hash_table || hash_table->ref_count <= 0)
		return ;

    node_index = st_hash_table_lookup_node_for_insertion (hash_table, key, &key_hash);
    node = &hash_table->nodes [node_index];

    old_hash = node->key_hash;

    if (old_hash > 1)
    {
        if (keep_new_key)
        {
            if (hash_table->key_destroy_func)
                hash_table->key_destroy_func (node->key);
            node->key = key;
        }
        else
        {
            if (hash_table->key_destroy_func)
                hash_table->key_destroy_func (key);
        }

        if (hash_table->value_destroy_func)
            hash_table->value_destroy_func (node->value);

        node->value = value;
    }
    else
    {
        node->key = key;
        node->value = value;
        node->key_hash = key_hash;

        hash_table->nnodes++;

        if (old_hash == 0)
        {
            /* We replaced an empty node, and not a tombstone */
            hash_table->noccupied++;
            st_hash_table_maybe_resize (hash_table);
        }
    }
}

/**
 * st_hash_table_insert:
 * @hash_table: a #STHashTable.
 * @key: a key to insert.
 * @value: the value to associate with the key.
 *
 * Inserts a new key and value into a #STHashTable.
 *
 * If the key already exists in the #STHashTable its current value is replaced
 * with the new value. If you supplied a @value_destroy_func when creating the
 * #STHashTable, the old value is freed using that function. If you supplied
 * a @key_destroy_func when creating the #STHashTable, the passed key is freed
 * using that function.
 **/
void
st_hash_table_insert (STHashTable *hash_table,
        stpointer    key,
        stpointer    value)
{
    st_hash_table_insert_internal (hash_table, key, value, FALSE);
}

/**
 * st_hash_table_replace:
 * @hash_table: a #STHashTable.
 * @key: a key to insert.
 * @value: the value to associate with the key.
 *
 * Inserts a new key and value into a #STHashTable similar to
 * st_hash_table_insert(). The difference is that if the key already exists
 * in the #STHashTable, it gets replaced by the new key. If you supplied a
 * @value_destroy_func when creating the #STHashTable, the old value is freed
 * using that function. If you supplied a @key_destroy_func when creating the
 * #STHashTable, the old key is freed using that function.
 **/
void
st_hash_table_replace (STHashTable *hash_table,
        stpointer    key,
        stpointer    value)
{
    st_hash_table_insert_internal (hash_table, key, value, TRUE);
}

/*
 * st_hash_table_remove_internal:
 * @hash_table: our #STHashTable
 * @key: the key to remove
 * @notify: %TRUE if the destroy notify handlers are to be called
 * Return value: %TRUE if a node was found and removed, else %FALSE
 *
 * Implements the common logic for the st_hash_table_remove() and
 * st_hash_table_steal() functions.
 *
 * Do a lookup of @key and remove it if it is found, calling the
 * destroy notify handlers only if @notify is %TRUE.
 */
static stbool
st_hash_table_remove_internal (STHashTable    *hash_table,
        stconstpointer  key,
        stbool       notify)
{
    STHashNode *node;
    stuint node_index;

    if(NULL == hash_table)
    	return FALSE ;

    node_index = st_hash_table_lookup_node (hash_table, key);
    node = &hash_table->nodes [node_index];

    /* st_hash_table_lookup_node() never returns a tombstone, so this is safe */
    if (!node->key_hash)
        return FALSE;

    st_hash_table_remove_node (hash_table, node, notify);
    st_hash_table_maybe_resize (hash_table);

    return TRUE;
}

/**
 * st_hash_table_remove:
 * @hash_table: a #STHashTable.
 * @key: the key to remove.
 *
 * Removes a key and its associated value from a #STHashTable.
 *
 * If the #STHashTable was created using st_hash_table_new_full(), the
 * key and value are freed using the supplied destroy functions, otherwise
 * you have to make sure that any dynamically allocated values are freed
 * yourself.
 *
 * Return value: %TRUE if the key was found and removed from the #STHashTable.
 **/
stbool
st_hash_table_remove (STHashTable    *hash_table,
        stconstpointer  key)
{
    return st_hash_table_remove_internal (hash_table, key, TRUE);
}

/**
 * st_hash_table_steal:
 * @hash_table: a #STHashTable.
 * @key: the key to remove.
 *
 * Removes a key and its associated value from a #STHashTable without
 * calling the key and value destroy functions.
 *
 * Return value: %TRUE if the key was found and removed from the #STHashTable.
 **/
stbool
st_hash_table_steal (STHashTable    *hash_table,
        stconstpointer  key)
{
    return st_hash_table_remove_internal (hash_table, key, FALSE);
}

/**
 * st_hash_table_remove_all:
 * @hash_table: a #STHashTable
 *
 * Removes all keys and their associated values from a #STHashTable.
 *
 * If the #STHashTable was created using st_hash_table_new_full(), the keys
 * and values are freed using the supplied destroy functions, otherwise you
 * have to make sure that any dynamically allocated values are freed
 * yourself.
 *
 * Since: 2.12
 **/
void
st_hash_table_remove_all (STHashTable *hash_table)
{
    if(NULL == hash_table)
    	return ;


    st_hash_table_remove_all_nodes (hash_table, TRUE);
    st_hash_table_maybe_resize (hash_table);
}

/**
 * st_hash_table_steal_all:
 * @hash_table: a #STHashTable.
 *
 * Removes all keys and their associated values from a #STHashTable
 * without calling the key and value destroy functions.
 *
 * Since: 2.12
 **/
void
st_hash_table_steal_all (STHashTable *hash_table)
{
    if(NULL == hash_table)
    	return ;

    st_hash_table_remove_all_nodes (hash_table, FALSE);
    st_hash_table_maybe_resize (hash_table);
}

/*
 * st_hash_table_foreach_remove_or_steal:
 * @hash_table: our #STHashTable
 * @func: the user's callback function
 * @user_data: data for @func
 * @notify: %TRUE if the destroy notify handlers are to be called
 *
 * Implements the common logic for st_hash_table_foreach_remove() and
 * st_hash_table_foreach_steal().
 *
 * Iterates over every node in the table, calling @func with the key
 * and value of the node (and @user_data).  If @func returns %TRUE the
 * node is removed from the table.
 *
 * If @notify is true then the destroy notify handlers will be called
 * for each removed node.
 */
static stuint
st_hash_table_foreach_remove_or_steal (STHashTable *hash_table,
        STHRFunc	  func,
        stpointer    user_data,
        stbool    notify)
{
    stuint deleted = 0;
    stint i;

    for (i = 0; i < hash_table->size; i++)
    {
        STHashNode *node = &hash_table->nodes [i];

        if (node->key_hash > 1 && (* func) (node->key, node->value, user_data))
        {
            st_hash_table_remove_node (hash_table, node, notify);
            deleted++;
        }
    }

    st_hash_table_maybe_resize (hash_table);

    return deleted;
}

/**
 * st_hash_table_foreach_remove:
 * @hash_table: a #STHashTable.
 * @func: the function to call for each key/value pair.
 * @user_data: user data to pass to the function.
 *
 * Calls the given function for each key/value pair in the #STHashTable.
 * If the function returns %TRUE, then the key/value pair is removed from the
 * #STHashTable. If you supplied key or value destroy functions when creating
 * the #STHashTable, they are used to free the memory allocated for the removed
 * keys and values.
 *
 * See #STHashTableIter for an alternative way to loop over the
 * key/value pairs in the hash table.
 *
 * Return value: the number of key/value pairs removed.
 **/
stuint
st_hash_table_foreach_remove (STHashTable *hash_table,
        STHRFunc     func,
        stpointer    user_data)
{
    if(NULL == hash_table || NULL == func)
    	return ;

    return st_hash_table_foreach_remove_or_steal (hash_table, func, user_data, TRUE);
}

/**
 * st_hash_table_foreach_steal:
 * @hash_table: a #STHashTable.
 * @func: the function to call for each key/value pair.
 * @user_data: user data to pass to the function.
 *
 * Calls the given function for each key/value pair in the #STHashTable.
 * If the function returns %TRUE, then the key/value pair is removed from the
 * #STHashTable, but no key or value destroy functions are called.
 *
 * See #STHashTableIter for an alternative way to loop over the
 * key/value pairs in the hash table.
 *
 * Return value: the number of key/value pairs removed.
 **/
stuint
st_hash_table_foreach_steal (STHashTable *hash_table,
        STHRFunc     func,
        stpointer    user_data)
{
    if(NULL == hash_table || NULL == func)
    	return ;

    return st_hash_table_foreach_remove_or_steal (hash_table, func, user_data, FALSE);
}

/**
 * st_hash_table_foreach:
 * @hash_table: a #STHashTable.
 * @func: the function to call for each key/value pair.
 * @user_data: user data to pass to the function.
 *
 * Calls the given function for each of the key/value pairs in the
 * #STHashTable.  The function is passed the key and value of each
 * pair, and the given @user_data parameter.  The hash table may not
 * be modified while iterating over it (you can't add/remove
 * items). To remove all items matching a predicate, use
 * st_hash_table_foreach_remove().
 *
 * See st_hash_table_find() for performance caveats for linear
 * order searches in contrast to st_hash_table_lookup().
 **/
void
st_hash_table_foreach (STHashTable *hash_table,
        STHFunc      func,
        stpointer    user_data)
{
    stint i;

    if(NULL == hash_table || NULL == func)
    	return ;

    for (i = 0; i < hash_table->size; i++)
    {
        STHashNode *node = &hash_table->nodes [i];

        if (node->key_hash > 1)
            (* func) (node->key, node->value, user_data);
    }
}

/**
 * st_hash_table_find:
 * @hash_table: a #STHashTable.
 * @predicate:  function to test the key/value pairs for a certain property.
 * @user_data:  user data to pass to the function.
 *
 * Calls the given function for key/value pairs in the #STHashTable until
 * @predicate returns %TRUE.  The function is passed the key and value of
 * each pair, and the given @user_data parameter. The hash table may not
 * be modified while iterating over it (you can't add/remove items).
 *
 * Note, that hash tables are really only optimized for forward lookups,
 * i.e. st_hash_table_lookup().
 * So code that frequently issues st_hash_table_find() or
 * st_hash_table_foreach() (e.g. in the order of once per every entry in a
 * hash table) should probably be reworked to use additional or different
 * data structures for reverse lookups (keep in mind that an O(n) find/foreach
 * operation issued for all n values in a hash table ends up needing O(n*n)
 * operations).
 *
 * Return value: The value of the first key/value pair is returned, for which
 * func evaluates to %TRUE. If no pair with the requested property is found,
 * %NULL is returned.
 *
 * Since: 2.4
 **/
    stpointer
st_hash_table_find (STHashTable      *hash_table,
        STHRFunc          predicate,
        stpointer         user_data)
{
    stint i;

    if(NULL == hash_table || NULL == predicate)
    	return NULL ;

    for (i = 0; i < hash_table->size; i++)
    {
        STHashNode *node = &hash_table->nodes [i];

        if (node->key_hash > 1 && predicate (node->key, node->value, user_data))
            return node->value;
    }

    return NULL;
}

/**
 * st_hash_table_size:
 * @hash_table: a #STHashTable.
 *
 * Returns the number of elements contained in the #STHashTable.
 *
 * Return value: the number of key/value pairs in the #STHashTable.
 **/
    stuint
st_hash_table_size (STHashTable *hash_table)
{
    if(NULL == hash_table)
    	return 0 ;

    return hash_table->nnodes;
}

/**
 * st_hash_table_get_keys:
 * @hash_table: a #STHashTable
 *
 * Retrieves every key inside @hash_table. The returned data is valid
 * until @hash_table is modified.
 *
 * Return value: a #STDLIST containing all the keys inside the hash
 *   table. The content of the list is owned by the hash table and
 *   should not be modified or freed. Use g_list_free() when done
 *   using the list.
 *
 * Since: 2.14
 */
    STDLIST *
st_hash_table_get_keys (STHashTable *hash_table)
{
    stint i;
    STDLIST *retval;

    if(NULL == hash_table)
    	return NULL ;

    retval = NULL;
    for (i = 0; i < hash_table->size; i++)
    {
        STHashNode *node = &hash_table->nodes [i];

        if (node->key_hash > 1)
            retval = st_dlist_prepend (retval, node->key);
    }

    return retval;
}

/**
 * st_hash_table_get_values:
 * @hash_table: a #STHashTable
 *
 * Retrieves every value inside @hash_table. The returned data is
 * valid until @hash_table is modified.
 *
 * Return value: a #STDLIST containing all the values inside the hash
 *   table. The content of the list is owned by the hash table and
 *   should not be modified or freed. Use g_list_free() when done
 *   using the list.
 *
 * Since: 2.14
 */
    STDLIST *
st_hash_table_get_values (STHashTable *hash_table)
{
    stint i;
    STDLIST *retval;

    if(NULL == hash_table)
    	return NULL ;

    retval = NULL;
    for (i = 0; i < hash_table->size; i++)
    {
        STHashNode *node = &hash_table->nodes [i];

        if (node->key_hash > 1)
            retval = st_dlist_prepend (retval, node->value);
    }

    return retval;
}

/**
 * g_str_equal:
 * @v1: a key
 * @v2: a key to compare with @v1
 *
 * Compares two strings for byte-by-byte equality and returns %TRUE
 * if they are equal. It can be passed to g_hash_table_new() as the
 * @key_equal_func parameter, when using strings as keys in a #STHashTable.
 *
 * Returns: %TRUE if the two keys match
 */
stbool
st_str_equal (stconstpointer v1,
		 stconstpointer v2)
{
  const stint8 *string1 = v1;
  const stint8 *string2 = v2;

  return strcmp (string1, string2) == 0;
}

/**
 * g_str_hash:
 * @v: a string key
 *
 * Converts a string to a hash value.
 * It can be passed to g_hash_table_new() as the @hash_func
 * parameter, when using strings as keys in a #STHashTable.
 *
 * Returns: a hash value corresponding to the key
 */
stuint
st_str_hash (stconstpointer v)
{
  /* 31 bit hash function */
  const signed char *p = v;
  stuint32 h = *p;

  if (h)
    for (p += 1; *p != '\0'; p++)
      h = (h << 5) - h + *p;

  return h;
}

/**
 * g_int_equal:
 * @v1: a pointer to a #gint key.
 * @v2: a pointer to a #gint key to compare with @v1.
 *
 * Compares the two #gint values being pointed to and returns
 * %TRUE if they are equal.
 * It can be passed to g_hash_table_new() as the @key_equal_func
 * parameter, when using pointers to integers as keys in a #STHashTable.
 *
 * Returns: %TRUE if the two keys match.
 */
stbool
st_int_equal (stconstpointer v1,
	     stconstpointer v2)
{
  return *((const stint*) v1) == *((const stint*) v2);
}

/**
 * st_int_hash:
 * @v: a pointer to a #gint key
 *
 * Converts a pointer to a #gint to a hash value.
 * It can be passed to g_hash_table_new() as the @hash_func parameter,
 * when using pointers to integers values as keys in a #STHashTable.
 *
 * Returns: a hash value corresponding to the key.
 */
stuint
st_int_hash (stconstpointer v)
{
  return *(const stint*) v;
}



