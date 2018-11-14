/*	open_addressing_hash.c -- 开放定址散列表实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "open_addressing_hash.h"

/*	局部数据类型定义	*/
struct apple	/*	我实在想不出别的名字了	*/
{
	int full ;
	int value ;
} ;

/*	局部函数定义	*/

int Get_Prime_Value (const int size) ;
int Is_An_Prime (const int number) ;
struct apple Linear_ (const int i, const int size) ;

/*	接口函数定义	*/

int Hash (const int item, const int size)
{
	int value = item ;

	return value % size ;
}

int InitializeTable (HashTable * const ph, const int size)
{
	int count, temp ;

	(*ph) = (struct hashtable *) malloc (sizeof (struct hashtable)) ;
	if (NULL == (*ph))
	{
		puts ("Out of space[1].") ;
		return 0 ;
	}
	(*ph) -> size = Get_Prime_Value (size) ;
	(*ph) -> lists = (Cell *) malloc (sizeof (Cell) * (*ph) -> size) ;
	if (NULL == (*ph) -> lists)
	{
		free (*ph) ;
		puts ("Out of space[2].") ;
		return 0 ;
	}
	temp = (*ph) -> size ;
	for (count = 0; count < temp; count++)
		(*ph) -> lists[count].info = Empty ;

	return 1 ;
}

Cell * Find (const HashTable * const ph, const Item item)
{
	struct apple value ;
	int key, size, index, i = 0 ;

	size = (*ph) -> size ;
	key = Hash (item, size) ;
	do
	{
		value = Linear_ (i++, size) ;
		if (value.full)
			/*	此时遍历了整个表	*/
			break ;
		index = (key + value.value) % size ;
	}
	while (Legitimate == (*ph) -> lists[index].info && (*ph) -> lists[index].item != item);

	return (*ph) -> lists + index ;
}

int Insert (HashTable * const ph, const Item item)
{
	Cell * position ;

	position = Find (ph, item) ;
	if (Empty == position -> info || Deleted == position -> info)
	{
		position -> info = Legitimate ;
		position -> item = item ;
		return 1 ;
	}

	return 0 ;
}

int Delete (HashTable * const ph, const Item item)
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
	int count, size = (*ph) -> size ;

	for (count = 0; count < size; count++)
		(* pfun) ((*ph) -> lists[count]) ;
}

void Release (HashTable * const ph)
{
	free ((*ph) -> lists) ;
	free (*ph) ;
}

/*	局部函数定义	*/

int Get_Prime_Value (const int size)
{
	int prime_value = size ;

	while (!Is_An_Prime (prime_value))
		prime_value++ ;

	return prime_value ;
}

int Is_An_Prime (const int number)
{
	int count, size ;

	if (number < 2)
	{
		puts ("Input wrong.") ;
		return 0 ;
	}
	for (count = 2, size = number / 2 + 1; count < size; count++)
		if (0 == number % count)
			return 0 ;
	
	return 1 ;
}

struct apple Linear_ (const int i, const int size)
{
	struct apple value ;

	if (i < 0)
		puts ("Wrong element") ;
	else if (i > size - 1)
		value.full = 1 ;
	else/* if (i <= size - 1)	*/
	{
		value.full = 0 ;
		value.value = i ;
	}

	return value ;
}
