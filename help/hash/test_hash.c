#include <stdio.h>
//#include "Separate_Chaining_Hash.h"
#include "open_addressing_hash.h"

#define	MAX_HASH_NUM		8


static void int_print(const SPListNode * const pnode)
{
    printf("%d\n", pnode->item);

    return;
}

#if 0
int main(void)
{
	SPHashTable HT ;
	SPItem r[MAX_HASH_NUM] = {2, 44, 23, 45, 66, 77, 36, 88};
	int i , ret , index;
	SPHeader h ;

	printf("!!!\n");
	HT = SPInitializeTable(MAX_HASH_NUM);
	//printf("hash size [%d]\n", HT->size);
	printf("!!!\n");
	for(i = 0 ; i < MAX_HASH_NUM ; i++)
	{
		printf("r[%d] :%d\n", i, r[i]);
		ret = SPInsert(r[i], &HT);
		if(0 == ret)
		{
			printf("表中已有关键字为%d的记录\n",r[i]);
		}
	}
	printf("从低索引向高索引将一个函数作用于表中所有存在的结点:\n");
	SPTraversal(&HT, int_print);

	h = SPFind(44, HT) ;
	printf("h node [%d]\n", h->item);

	//printf("delete hash table\n");
	//Delete(r[0], &HT) ;
	//Traversal(&HT, int_print);

	//index = Hash(77, MAX_HASH_NUM) ;
	//printf("hash index [%d]\n", index);
	
}
#elif 1
int main(void)
{
	HashTable HT ;
	int i , ret , index;
	Item r[MAX_HASH_NUM] = {2, 44, 23, 45, 66, 77, 36, 88};

	InitializeTable(&HT, MAX_HASH_NUM);
	for(i = 0 ; i < MAX_HASH_NUM ; i++)
	{
		printf("r[%d] :%d\n", i, r[i]);
		ret = Insert(&HT, r[i]);
		if(0 == ret)
		{
			printf("表中已有关键字为%d的记录\n",r[i]);
		}
	}
	printf("从低索引向高索引将一个函数作用于表中所有存在的结点:\n");
	Traversal(&HT, int_print);
}
#endif


