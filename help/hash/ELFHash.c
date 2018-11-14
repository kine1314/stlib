#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int HASH_TABLE_SIZE = 13;

typedef struct hash_table_pair_s {
    char *key;
    int value;
    struct hash_table_pair_s *next;
} hash_table_pair_t;

#if 0
int ELFhash(const char *key)
{
    unsigned long h = 0;
    unsigned long g;
    while( *key )
    {
        h =( h<< 4) + *key++;
        g = h & 0xf0000000L;
        if( g ) h ^= g >> 24;
        h &= ~g;
    }
    return h;
}
#elif 0
int ELFhash/*SDBMHash*/(char *key)
{
	unsigned int hash = 0;
 
	while (*key)
	{
		// equivalent to: hash = 65599*hash + (*str++);
		hash = (*key++) + (hash << 6) + (hash << 16) - hash;
	}
 
	return (hash & 0x7FFFFFFF);
}
#else
// RS Hash Function
unsigned int ELFhash/*RSHash*/(char *key)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
 
	while (*key)
	{
		hash = hash * a + (*key++);
		a *= b;
	}
 
	return (hash & 0x7FFFFFFF);
}

#endif

void hash_table_insert(hash_table_pair_t *hash_table, const char *key, int value)
{
    int pos;
    hash_table_pair_t *new_pair;
    char *new_str;

    pos = ELFhash(key) % HASH_TABLE_SIZE;
    if (hash_table[pos].key != NULL) {
        printf("conflict: %s and %s\n", key, hash_table[pos].key);
        new_pair = (hash_table_pair_t *)malloc(sizeof(hash_table_pair_t));
        new_str = (char *)malloc(sizeof(char) * (strlen(key) + 1));
        strcpy(new_str, key);
        new_pair->key = new_str;
        new_pair->value = value;
        new_pair->next = hash_table[pos].next;
        hash_table[pos].next = new_pair;
    }
    else {
        new_str = (char *)malloc(sizeof(char) * (strlen(key) + 1));
        strcpy(new_str, key);
        hash_table[pos].key = new_str;
        hash_table[pos].value = value;
        hash_table[pos].next = NULL;
    }
}

int hash_table_get(hash_table_pair_t *hash_table, const char *key, int *value)
{
    int pos;
    hash_table_pair_t *p;

    pos = ELFhash(key) % HASH_TABLE_SIZE;
    for (p = &hash_table[pos]; p != NULL; p = p->next) {
        if (!strcmp(p->key, key)) {
            *value = p->value;
            return 0;
        }
    }
    return -1;
}

int main()
{
    int i, status, value;
    const char *MyBirds[13] = { "robin",  "sparrow",  "hawk",  "eagle",  "seagull",  "bluejay",  "owl",  "cardinal",  "Jakana",  "Moa",  "Egret",  "Penguin",  "hawk" };

    hash_table_pair_t *hash_table = (hash_table_pair_t *)malloc(HASH_TABLE_SIZE * sizeof(hash_table_pair_t));
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_table[i].key = NULL;
        hash_table[i].next = NULL;
        hash_table[i].value = 0;
    }
    for (i = 0; i < sizeof(MyBirds) / sizeof(MyBirds[0]); i++) {
        hash_table_insert(hash_table, MyBirds[i], i);
    }
    for (i = 0; i < sizeof(MyBirds) / sizeof(MyBirds[0]); i++) {
        status = hash_table_get(hash_table, MyBirds[i], &value);
        if (status == -1) {
            printf("not found %s\n", MyBirds[i]);
        }
        else {
            printf("found %s: %d\n", MyBirds[i], value);
        }
    }

    return 0;
}
