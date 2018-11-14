/*	Separate_Chaining_Hash -- 分离链接散列表实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "Separate_Chaining_Hash.h"

/*	局部数据类型定义	*/

typedef struct pair
{
	SPListNode * parent ;
	SPListNode * current ;
} Pair ;

/*	局部函数声明	*/

int Get_Prime_Size (const int size) ;
int Is_A_Prime_Number (const int number) ;
SPListNode * Make_Node (const SPItem item) ;
Pair Seek_and_Return (const SPItem item, const int key, const SPHashTable * const ph) ;
void Work_For_Release (SPListNode * node) ;

/*	接口函数定义	*/

SPHashTable InitializeTable (const int size)
{
	SPHashTable h ;
	int count ;

	if (size > MAXTABLESIZE)
	{
		puts ("Table size is too big!") ;
		return NULL ;
	}
	h = (struct sp_hashtable *) malloc (sizeof (struct sp_hashtable)) ;
	if (NULL == h)
		puts ("Out of space![1]") ;
	h -> size = Get_Prime_Size (size) ;								// 确定表的大小是素数
	h -> lists = (SPHeader *) malloc (sizeof (SPHeader) * h -> size) ;
	if (NULL == h -> lists)
		puts ("Out of space![2]") ;
	for (count = 0; count < h->size; count++)
		h -> lists[count] = NULL ;

	return h ;
}

int Hash (const SPItem item, const int size)
{
	int hash_value = item ;

	return hash_value % size ;					// 整数的散列，直接去表大小的模
}

SPHeader Find (const SPItem item, const SPHashTable h)
{
	SPListNode * p ;
	SPListNode * o ;
	int key = Hash (item, h -> size) ;

	p = h -> lists[key] ;
	while (p != NULL && p -> item != item)
		p = p -> next ;

	return p ;
}

int Insert (const SPItem item, SPHashTable * const ph)
{
	SPListNode * new_node, * location, * record ;
	int key ;

	key = Hash (item, (*ph) -> size) ;
	record = (*ph) -> lists[key] ;
	/*	如果头结点的指针为NULL	*/
	if (NULL == record)
	{
		new_node = Make_Node (item) ;
		if (NULL == new_node)
		{
			puts ("Out of space![3]") ;
			return 0 ;
		}
		(*ph) -> lists[key] = new_node ;
	}
	else		// 重复的话追加链表
	{
		location = Find (item, *ph) ;
		/*	如果无重复	*/
		if (NULL == location)
		{
			new_node = Make_Node (item) ;
			if (NULL == new_node)
			{
				puts ("Out of space![4]") ;
				return 0 ;
			}
			new_node -> next = (*ph) -> lists[key] ;
			(*ph) -> lists[key] = new_node ;
		}
		else
			/*	不进行重复添加	*/
			return 0 ;
	}

	return 1 ;
}

int Delete (const SPItem item, SPHashTable * const ph)
{
	SPListNode * temp ;
	Pair pair ;
	int key ;

	key = Hash (item, (*ph) -> size) ;
	pair = Seek_and_Return (item, key, ph) ;
	if (pair.current != NULL)
	{
		temp = pair.current ;
		if (pair.parent != NULL)
			pair.parent -> next = pair.current -> next ;
		else
			(*ph) -> lists[key] = pair.current -> next ;		// 直接替换表头
		free (temp) ;
		return 1 ;
	}
	else
		return 0 ;

}

void Traversal (const SPHashTable * const ph, void (* pfun) (const SPListNode * const pnode))
{
	SPListNode * scan ;
	int count, size ;

	for (count = 0, size = (*ph) -> size; count < size; count++)
	{
		if ((*ph) -> lists[count] != NULL)
		{
			scan = (*ph) -> lists[count] ;
			while (scan != NULL)
			{
				(* pfun) (scan) ;
				scan = scan -> next ;
			}
		}
	}
}

void Release (SPHashTable * ph)
{
	int count, size ;

	for (count = 0, size = (*ph) -> size; count < size; count++)
	{
		if ((*ph) -> lists[count] != NULL)
			Work_For_Release ((*ph) -> lists[count]) ;
	}
	free ((*ph) -> lists) ;
	free (*ph) ;
}


/*	局部函数定义	*/

int Get_Prime_Size (const int size)
{
	int temp = size ;

	while (!Is_A_Prime_Number (temp))
		temp++ ;

	return temp ;
}

int Is_A_Prime_Number (const int number)
{
	int count, value ;

	if (number < 2)
		puts ("Input wrong!") ;
	value = number / 2 + 1 ;
	for (count = 2; count < value; count++)
		if (0 == number % count)
			return 0 ;

	return 1 ;
}

SPListNode * Make_Node (const SPItem item)
{
	SPListNode * new_node ;

	new_node = (SPListNode *) malloc (sizeof (SPListNode)) ;
	if (NULL == new_node)
		return NULL ;
	else
	{
		new_node -> item = item ;
		new_node -> next = NULL ;
	}

	return new_node ;
}

Pair Seek_and_Return (const SPItem item, const int key, const SPHashTable * const ph)
{
	Pair pair ;
	pair.parent = NULL ;
	pair.current = (*ph) -> lists[key] ;

	while (pair.current != NULL && pair.current -> item != item)
	{
		pair.parent = pair.current ;
		pair.current = pair.current -> next ;
	}

	return pair ;
}

void Work_For_Release (SPListNode * node)
{
	if (node != NULL)
		Work_For_Release (node -> next) ;
	else
		free (node) ;
}
