/*	st_d_heap.c -- d-堆实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "st_d_heap.h"



/*	局部函数声明	*/

static int DHPercolate_Up (const DHeap * const pheap, const DHItem item, const int position) ;
static int DHPercolate_Down (const DHeap * const pheap, const DHItem item, const int position) ;

/*	接口函数定义	*/

int DHInitialize (DHeap * const pheap, const int capacity, const int d)
{
	if (capacity < 0)
		return 0 ;
	*pheap = (struct _DHeap *) malloc (sizeof (struct _DHeap) * (capacity + 1)) ;
	if (NULL == *pheap)
	{
		puts ("Out of space.[1]") ;
		return 0 ;
	}
	(*pheap)->array = (DHItem *) malloc (sizeof (DHItem) * capacity) ;
	if (NULL == (*pheap)->array)
	{
		puts ("Out of space.[2]") ;
		free (*pheap) ;
		return 0 ;
	}
	(*pheap)->capacity = capacity ;
	(*pheap)->size = 0 ;
	(*pheap)->d = d ;
	(*pheap)->array[0] = DHMINDATA ;

	return 1 ;
}

int DHIsEmpty (const DHeap * const pheap)
{
	return 0 == (*pheap)->size ;
}

int DHIsFull (const DHeap * const pheap)
{
	return (*pheap)->capacity == (*pheap)->size ;
}

int DHInsert (const DHeap * const pheap, const DHItem item)
{
	int i ;

	if (DHIsFull (pheap))
		return 0 ;
	//	变量作为参数在函数间传递时后缀自增、自减不改变变量的值
	i = DHPercolate_Up (pheap, item, ++(*pheap)->size) ;
	(*pheap)->array[i] = item ;

	return 1 ;
}

DHItem DHDeleteMin (const DHeap * const pheap)
{
	DHItem min, item ;
	int i, position;

	if (DHIsEmpty (pheap))
		return (*pheap)->array[0] ;
	min = (*pheap)->array[1] ;
	item = (*pheap)->array[(*pheap)->size] ;
	(*pheap)->size-- ;
	position = 1 ;
	i = DHPercolate_Down (pheap, item, position) ;
	(*pheap)->array[i] = item ;

	return min ;
}

int DHDecreaseKey (const DHeap * const pheap, const int position, const int triangle)
{
	DHItem item ;
	int i ;

	if (position > 0 && position <= (*pheap)->size && triangle > 0)
	{
		item = (*pheap)->array[position] -= triangle ;
		i = DHPercolate_Up (pheap, item, position) ;
		(*pheap)->array[i] = item ;
		return 1 ;
	}
	else
		return 0 ;
}

int DHIncreaseKey (const DHeap * const pheap, const int position, const int triangle)
{
	DHItem item ;
	int i ;

	if (position > 0 && position <= (*pheap)->size && triangle > 0)
	{
		item = (*pheap)->array[position] += triangle ;
		i = DHPercolate_Down (pheap, item, position) ;
		(*pheap)->array[i] = item ;
		return 1 ;
	}
	else
		return 0 ;
}

int DHBuild (const DHeap * const pheap, const DHItem * parray, const int size)
{
	DHItem item ;
	int i, d, ct ;

	if (!DHIsEmpty (pheap) || size <= 0)
		return 0 ;
	for (i = 0; i < size; i++)
		(*pheap)->array[i + 1] = parray[i] ;
	(*pheap)->size = size ;
	for (d = (*pheap)->d, ct = (size + d - 2) / d; ct > 0; ct--)
	{
		item = (*pheap)->array[ct] ;
		i = DHPercolate_Down (pheap, item, ct) ;
		(*pheap)->array[i] = item ;
	}

	return 1 ;
}

int DHDelete (const DHeap * const pheap, const int position)
{
	int triangle ;

	if (position < 0 || position > (*pheap)->size)
		return 0 ;
	triangle = (*pheap)->array[position] - (*pheap)->array[1] + 1 ;
	DHDecreaseKey (pheap, position, triangle) ;
	DHDeleteMin (pheap) ;

	return 1 ;
}

void DHTraversal (const DHeap * const pheap, void (* pfun) (const DHItem item))
{
	int i, size ;

	for (i = 1, size = (*pheap)->size; i <= size; i++)
		(* pfun) ((*pheap)->array[i]) ;
}

void DHRelease (const DHeap * const pheap)
{
	free ((*pheap)->array) ;
	free (*pheap) ;
}

/*	局部函数定义	*/

static int DHPercolate_Up (const DHeap * const pheap, const DHItem item, const int position)
{
	int i, d ;

	for (i = position, d = (*pheap) -> d; (*pheap)->array[(i + d - 2) / d] > item; i = (i + d - 2) / d)
		(*pheap)->array[i] = (*pheap)->array[(i + d - 2) / d] ;

	return i ;
}

static int DHPercolate_Down (const DHeap * const pheap, const DHItem item, const int position)
{
	DHItem item_record ;
	int i, j, d, child, int_record;

	for (i = position, d = (*pheap)->d; (i - 1) * d + 2 <= (*pheap)->size; i = child)
	{
		child = (i - 1) * d + 2 ;
		for (j = 1, int_record = child, item_record = (*pheap)->array[child]; int_record + j != (*pheap)->size + 1 && j < d; j++)
		{
			if ((*pheap)->array[int_record + j] < item_record)
			{
					item_record = (*pheap)->array[int_record + j] ;
					child = j + int_record ;
			}
		}
		if (item > (*pheap)->array[child])
			(*pheap)->array[i] = (*pheap)->array[child] ;
		else
			break ;
	}

	return i ;
}

















