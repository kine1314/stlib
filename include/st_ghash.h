/*
 * st_ghash.h
 *
 *  Created on: 2011-11-18
 *      Author: kine
 */

#ifndef ST_GHASH_H_
#define ST_GHASH_H_

#include "stlib.h"
#include "st_dlist.h"

ST_BEGIN_DECLS ;


typedef struct _STHashNode
{
    stpointer   key;
    stpointer   value;

    /* If key_hash == 0, node is not in use
     * If key_hash == 1, node is a tombstone
     * If key_hash >= 2, node contains data */
    stuint      key_hash;
}STHashNode;

typedef struct _STHashTable
{
    stint             size;
    stint             mod;
    stuint            mask;
    stint             nnodes;
    stint             noccupied;  /* nnodes + tombstones */
    STHashNode       *nodes;
    STHashFunc        hash_func;
    STEqualFunc       key_equal_func;
    volatile stint    ref_count;

    STDestroyNotify   key_destroy_func;
    STDestroyNotify   value_destroy_func;
}STHashTable;

typedef struct _STHashTableIter
{
    /*< private >*/
    stpointer	dummy1;
    stpointer	dummy2;
    stpointer	dummy3;
    stint		dummy4;
    stbool		dummy5;
    stpointer	dummy6;
}STHashTableIter;


/* Hash tables
*/
STHashTable* st_hash_table_new		   (STHashFunc	    hash_func,
        STEqualFunc	    key_equal_func);
STHashTable* st_hash_table_new_full      	   (STHashFunc	    hash_func,
        STEqualFunc	    key_equal_func,
        STDestroyNotify  key_destroy_func,
        STDestroyNotify  value_destroy_func);
void	    st_hash_table_destroy	   (STHashTable	   *hash_table);
void	    st_hash_table_insert		   (STHashTable	   *hash_table,
        stpointer	    key,
        stpointer	    value);
void        st_hash_table_replace           (STHashTable     *hash_table,
        stpointer	    key,
        stpointer	    value);
stbool    st_hash_table_remove		   (STHashTable	   *hash_table,
        stconstpointer   key);
void        st_hash_table_remove_all        (STHashTable     *hash_table);
stbool    st_hash_table_steal             (STHashTable     *hash_table,
        stconstpointer   key);
void        st_hash_table_steal_all         (STHashTable     *hash_table);
stpointer    st_hash_table_lookup		   (STHashTable	   *hash_table,
        stconstpointer   key);
stbool    st_hash_table_lookup_extended   (STHashTable	   *hash_table,
        stconstpointer   lookup_key,
        stpointer	   *orig_key,
        stpointer	   *value);
void	    st_hash_table_foreach	   (STHashTable	   *hash_table,
        STHFunc	    func,
        stpointer	    user_data);
stpointer    st_hash_table_find	           (STHashTable	   *hash_table,
        STHRFunc	    predicate,
        stpointer	    user_data);
stuint	    st_hash_table_foreach_remove	   (STHashTable	   *hash_table,
        STHRFunc	    func,
        stpointer	    user_data);
stuint	    st_hash_table_foreach_steal	   (STHashTable	   *hash_table,
        STHRFunc	    func,
        stpointer	    user_data);
stuint	    st_hash_table_size		   (STHashTable	   *hash_table);
STDLIST *     st_hash_table_get_keys          (STHashTable     *hash_table);
STDLIST *     st_hash_table_get_values        (STHashTable     *hash_table);

void        st_hash_table_iter_init         (STHashTableIter *iter,
        STHashTable     *hash_table);
stbool    st_hash_table_iter_next         (STHashTableIter *iter,
        stpointer       *key,
        stpointer       *value);
STHashTable* st_hash_table_iter_get_hash_table (STHashTableIter *iter);
void        st_hash_table_iter_remove       (STHashTableIter *iter);
void        st_hash_table_iter_steal        (STHashTableIter *iter);

/* keeping hash tables alive */
STHashTable* st_hash_table_ref   		   (STHashTable 	   *hash_table);
void        st_hash_table_unref             (STHashTable     *hash_table);


/* Hash Functions
*/
stbool st_str_equal (stconstpointer  v1, stconstpointer  v2);
stuint    st_str_hash  (stconstpointer  v);
stbool st_int_equal (stconstpointer  v1, stconstpointer  v2);
stuint    st_int_hash  (stconstpointer  v);

/* This "hash" function will just return the key's address as an
 * unsigned integer. Useful for hashing on plain addresses or
 * simple integer values.
 * Passing NULL into st_hash_table_new() as STHashFunc has the
 * same effect as passing st_direct_hash().
 */
stuint    st_direct_hash  (stconstpointer  v) ;
stbool st_direct_equal (stconstpointer  v1, stconstpointer  v2) ;


ST_END_DECLS ;
#endif /* ST_GHASH_H_ */
