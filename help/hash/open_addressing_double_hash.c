/*	open_addressing_double_hash.c -- 开放定址散列表双散列实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "open_addressing_double_hash.h"

/*	局部函数声明	*/
static int Get_Prime_Value (const int size) ;
static int Is_A_Prime (const int number) ;
static int Leaner_ (const int i, const int item, const int prime) ;

/*	接口函数定义	*/

int Hash (const int item, const int size)
{
	return item % size ;
}

int Hash2 (const int item, const int prime)
{
	return prime - (item % prime) ;
}

int InitializeTable (HashTable * const ph, const int size)
{
	int temp, count ;

	*ph = (struct hashtable *) malloc (sizeof (struct hashtable)) ;
	if (NULL == *ph)
	{
		puts ("Out of space.[1]") ;
		return 0 ;
	}
	temp = (*ph) -> size = Get_Prime_Value (size) ;
	(*ph) -> lists = (Cell *) malloc (sizeof (Cell) * temp) ;
	if (NULL == (*ph) -> lists)
	{
		puts ("Out of space.[2]") ;
		free (*ph) ;
		return 0 ;
	}
	for (count = 0; count < temp; count++)
		(*ph) -> lists[count].info = Empty ;

	return 1 ;
}

Cell * Find (const HashTable * const ph, const Item item)
{
	int size, key, index, i = 0 ;

	size = (*ph) -> size ;
	key = Hash (item, size) ;
	do
	{
		if (i < size)
			index = (key + Leaner_ (i++, item, PRIME)) % size ;		// 双散列探测地址法
		else
			break ;
	}
	while (Legitimate == (*ph) -> lists[index].info && (*ph) -> lists[index].item != item)
		;

	return (*ph) -> lists + index ;
}

int Insert (const HashTable * const ph, const Item item)
{
	Cell * position ;

	position = Find (ph, item) ;
	if (position -> info != Legitimate)
	{
		position -> info = Legitimate ;
		position -> item = item ;
		return 1 ;
	}

	return 0 ;
}

int Delete (const HashTable * const ph, const Item item)
{
	Cell * position ;

	position = Find (ph, item) ;
	if (Legitimate == position -> info && item == position -> item)
	{
		position -> info = Deleted ;
		return 1 ;
	}

	return 0 ;
}

void Traversal (const HashTable * const ph, void (* pfun) (const Cell cell))
{
	int count, size ;

	size = (*ph) -> size ;
	for (count = 0; count < size; count++)
		(* pfun) ((*ph) -> lists[count]) ;
}

void Release (const HashTable * const ph)
{
	free ((*ph) -> lists) ;
	free (*ph) ;
}

/*	局部函数定义	*/
static int Get_Prime_Value (const int size)
{
	int real_value = size ;

	while (!Is_A_Prime (real_value))
		real_value++ ;

	return real_value ;
}

static int Is_A_Prime (const int number)
{
	int count, temp ;

	if (number < 2)
	{
		puts ("Wrong number.") ;
		return 0 ;
	}
	for (count = 2, temp = number / 2 + 1; count <= temp; count++)
		if (0 == number % count)
			return 0 ;

	return 1 ;
}

static int Leaner_ (const int i, const int item, const int prime)
{
	return i * Hash2 (item, prime) ;
}
