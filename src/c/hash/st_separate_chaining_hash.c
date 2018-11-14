/*
 * st_separate_chaining_hash.c
 *
 *  Created on: 2011-11-28
 *      Author: kine
 */

/*	Separate_Chaining_Hash -- ��������ɢ�б�ʵ���ļ�	*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "st_separate_chaining_hash.h"

/*	�ֲ��������Ͷ���	*/

typedef struct pair
{
	SPListNode * parent ;
	SPListNode * current ;
} Pair ;

/*	�ֲ���������	*/


SPListNode * Make_SPNode (const HItem item) ;
Pair Seek_and_Return (const HItem item, const int key, const SPHashTable * const ph) ;
void Work_For_Release (SPListNode * node) ;

/*	�ӿں�������	*/

SPHashTable SPInitializeTable (const int size)
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
	h->size = Get_Prime_Size (size) ;								// ȷ����Ĵ�С������
	h->lists = (SPHeader *) malloc (sizeof (SPHeader) * h->size) ;
	if (NULL == h->lists)
		puts ("Out of space![2]") ;
	for (count = 0; count < h->size; count++)
		h->lists[count] = NULL ;

	return h ;
}


SPHeader SPFind (const HItem item, const SPHashTable h)
{
	SPListNode * p ;
	SPListNode * o ;
	int key = STHash (item, h->size) ;

	p = h->lists[key] ;
	while (p != NULL && p->item != item)
		p = p->next ;

	return p ;
}

int SPInsert (const HItem item, SPHashTable * const ph)
{
	SPListNode * new_node, * location, * record ;
	int key ;

	key = STHash (item, (*ph)->size) ;
	record = (*ph)->lists[key] ;
	/*	���ͷ����ָ��ΪNULL	*/
	if (NULL == record)
	{
		new_node = Make_SPNode (item) ;
		if (NULL == new_node)
		{
			puts ("Out of space![3]") ;
			return UNSUCCESS ;
		}
		(*ph)->lists[key] = new_node ;
	}
	else		// �ظ��Ļ�׷������
	{
		location = Find (item, *ph) ;
		/*	������ظ�	*/
		if (NULL == location)
		{
			new_node = Make_SPNode (item) ;
			if (NULL == new_node)
			{
				puts ("Out of space![4]") ;
				return UNSUCCESS ;
			}
			new_node->next = (*ph)->lists[key] ;
			(*ph)->lists[key] = new_node ;			// new node ��������ͷ
		}
		else
			/*	�������ظ����	*/
			return UNSUCCESS ;
	}

	return SUCCESS ;
}

int SPDelete (const HItem item, SPHashTable * const ph)
{
	SPListNode * temp ;
	Pair pair ;
	int key ;

	key = STHash (item, (*ph)->size) ;
	pair = Seek_and_Return (item, key, ph) ;
	if (pair.current != NULL)
	{
		temp = pair.current ;
		if (pair.parent != NULL)
			pair.parent->next = pair.current->next ;
		else
			(*ph)->lists[key] = pair.current->next ;		// ֱ���滻��ͷ
		free (temp) ;
		return SUCCESS ;
	}
	else
		return UNSUCCESS ;

}

void SPTraversal (const SPHashTable * const ph, void (* pfun) (const SPListNode * const pnode))
{
	SPListNode * scan ;
	int count, size ;

	for (count = 0, size = (*ph)->size; count < size; count++)
	{
		if ((*ph)->lists[count] != NULL)
		{
			scan = (*ph)->lists[count] ;
			while (scan != NULL)
			{
				(* pfun) (scan) ;
				scan = scan->next ;
			}
		}
	}
}

void SPRelease (SPHashTable * ph)
{
	int count, size ;

	for (count = 0, size = (*ph)->size; count < size; count++)
	{
		if ((*ph)->lists[count] != NULL)
			Work_For_Release ((*ph)->lists[count]) ;
	}
	free ((*ph)->lists) ;
	free (*ph) ;
}


/*	�ֲ���������	*/



SPListNode * Make_SPNode (const HItem item)
{
	SPListNode * new_node ;

	new_node = (SPListNode *) malloc (sizeof (SPListNode)) ;
	if (NULL == new_node)
		return NULL ;
	else
	{
		new_node->item = item ;
		new_node->next = NULL ;
	}

	return new_node ;
}

Pair Seek_and_Return (const HItem item, const int key, const SPHashTable * const ph)
{
	Pair pair ;
	pair.parent = NULL ;
	pair.current = (*ph)->lists[key] ;

	while (pair.current != NULL && pair.current -> item != item)
	{
		pair.parent = pair.current ;
		pair.current = pair.current->next ;
	}

	return pair ;
}

void Work_For_Release (SPListNode * node)
{
	if (node != NULL)
		Work_For_Release (node->next) ;
	else
		free (node) ;
}
