/*
 * st_open_addressing_double_hash.c
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */
#include <malloc.h>
#include "st_open_addressing_double_hash.h"


/*	局部函数声明	*/
/* 线性探测 */
static int Leaner_ (const int i, const int item, const int prime) ;


/*	接口函数定义	*/


int OADInitializeTable (OAHashTable * const ph, const int size)
{
	int temp, count ;

	*ph = (struct oa_hashtable *) malloc (sizeof (struct oa_hashtable)) ;
	if (NULL == *ph)
	{
		puts ("Out of space.[1]") ;
		return 0 ;
	}
	temp = (*ph)->size = Get_Prime_Size (size) ;
	(*ph)->lists = (Cell *) malloc (sizeof (Cell) * temp) ;
	if (NULL == (*ph)->lists)
	{
		puts ("Out of space.[2]") ;
		free (*ph) ;
		return 0 ;
	}
	for (count = 0; count < temp; count++)
		(*ph)->lists[count].info = Empty ;

	return 1 ;
}

Cell * OADFind (const OAHashTable * const ph, const HItem item)
{
	int size, key, index, i = 0 ;

	size = (*ph)->size ;
	key = STHash (item, size) ;
	do
	{
		if (i < size)
			index = (key + Leaner_ (i++, item, PRIME)) % size ;		// 双散列探测地址法
		else
			break ;
	}
	while (Legitimate == (*ph)->lists[index].info && (*ph)->lists[index].item != item);

	return (*ph)->lists + index ;
}

int OADInsert (const OAHashTable * const ph, const HItem item)
{
	Cell * position ;

	position = OADFind (ph, item) ;
	if (position->info != Legitimate)
	{
		position->info = Legitimate ;
		position->item = item ;
		return 1 ;
	}

	return 0 ;
}

int OADDelete (const OAHashTable * const ph, const HItem item)
{
	Cell * position ;

	position = OADFind (ph, item) ;
	if (Legitimate == position->info && item == position-> item)
	{
		position->info = Deleted ;
		return 1 ;
	}

	return 0 ;
}

void OADTraversal (const OAHashTable * const ph, void (* pfun) (const Cell cell))
{
	int count, size ;

	size = (*ph)->size ;
	for (count = 0; count < size; count++)
		(* pfun) ((*ph)->lists[count]) ;
}

void OADRelease (const OAHashTable * const ph)
{
	free ((*ph)->lists) ;
	free (*ph) ;
}

/*	局部函数定义	*/
static int Leaner_ (const int i, const int item, const int prime)
{
	return i * STHash2 (item, prime) ;
}
