/*
 * open_addressing_hash_2.c
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */
#include <malloc.h>
#include "st_open_addressing_hash_2.h"


/*	接口函数定义	*/

int OA2InitializeTable (OAHashTable * const ph, const int size)
{
	int temp, count ;

	(*ph) = (struct oa_hashtable *) malloc (sizeof (struct oa_hashtable)) ;
	if (NULL == *ph)
	{
		puts ("Out of space[1].") ;
		return 0 ;
	}
	temp = (*ph)->size = Get_Prime_Size (size) ;
	(*ph)->lists = (Cell *) malloc (sizeof (Cell) * temp) ;
	if (NULL == (*ph)->lists)
	{
		free (*ph) ;
		puts ("Out of space.[2]") ;
		return 0 ;
	}
	for (count = 0; count < temp; count++)
		(*ph)->lists[count].info = Empty ;

	return 1 ;
}

Cell * OA2Find (const OAHashTable * const ph, const HItem item)
{
	int key, size, critical, value, index, i = 0 ;

	size = (*ph)->size ;
	key = STHash (item, size) ;
	critical = size / 2 + 1 ;
	do
	{
		if (i <= critical)
		{
			value = Square_ (i++) ;
			index = (key + value) % size ;						// 平方探测
		}
		else
			break ;
	}
	while (Legitimate == (*ph)->lists[index].info && (*ph)->lists[index].item != item);

	return (*ph)->lists + index ;
}

int OA2Insert (const OAHashTable * const ph, const HItem item)
{
	Cell * position ;

	position = OA2Find (ph, item) ;
	if (Empty == position->info || Deleted == position->info)
	{
		position->info = Legitimate ;
		position -> item = item ;
		return 1 ;
	}

	return 0 ;
}

int OA2Delete (const OAHashTable * const ph, const HItem item)
{
	Cell * position ;

	position = OA2Find (ph, item) ;
	if (Legitimate == position->info && item == position -> item)
	{
		position->info = Deleted ;
		return 1 ;
	}

	return 0 ;
}

void OA2Traversal (const OAHashTable * const ph, void (* pfun) (const Cell cell))
{
	int count, size = (*ph)->size ;

	for (count = 0; count < size; count++)
		(* pfun) ((*ph)->lists[count]) ;
}

void OA2Release (const OAHashTable * const ph)
{
	free ((*ph)->lists) ;
	free (*ph) ;
}

/*	局部函数定义	*/



