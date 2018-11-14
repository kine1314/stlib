/*	open_addressing_hash(2) -- 开放定址散列表实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "open_addressing_hash(2).h"

/*	局部函数声明	*/

static int Get_Prime_Value (const int size) ;
static int Is_An_Prime (const int number) ;
static int Square_ (const int i) ;


/*	接口函数定义	*/

int Hash (const int item, const int size)
{
	return item % size ;
}

int InitializeTable (HashTable * const ph, const int size)
{
	int temp, count ;

	(*ph) = (struct hashtable *) malloc (sizeof (struct hashtable)) ;
	if (NULL == *ph)
	{
		puts ("Out of space[1].") ;
		return 0 ;
	}
	temp = (*ph) -> size = Get_Prime_Value (size) ;
	(*ph) -> lists = (Cell *) malloc (sizeof (Cell) * temp) ;
	if (NULL == (*ph) -> lists)
	{
		free (*ph) ;
		puts ("Out of space.[2]") ;
		return 0 ;
	}
	for (count = 0; count < temp; count++)
		(*ph) -> lists[count].entry = Empty ;

	return 1 ;
}

Cell * Find (const HashTable * const ph, const Item item)
{
	int key, size, critical, value, index, i = 0 ;

	size = (*ph) -> size ;
	key = Hash (item, size) ;
	critical = size / 2 + 1 ;
	do
	{
		if (i <= critical)
		{
			value = Square_ (i++) ;
			index = (key + value) % size ;
		}
		else
			break ;
	}
	while (Legitimate == (*ph) -> lists[index].entry && (*ph) -> lists[index].item != item)
		;

	return (*ph) -> lists + index ;
}

int Insert (const HashTable * const ph, const Item item)
{
	Cell * position ;

	position = Find (ph, item) ;
	if (Empty == position -> entry || Deleted == position -> entry)
	{
		position -> entry = Legitimate ;
		position -> item = item ;
		return 1 ;
	}

	return 0 ;
}

int Delete (const HashTable * const ph, const Item item)
{
	Cell * position ;

	position = Find (ph, item) ;
	if (Legitimate == position -> entry && item == position -> item)
	{
		position -> entry = Deleted ;
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

void Release (const HashTable * const ph)
{
	free ((*ph) -> lists) ;
	free (*ph) ;
}

/*	局部函数定义	*/

static int Get_Prime_Value (const int size)
{
	int real_size = size ;

	while (!Is_An_Prime (real_size))
		real_size++ ;

	return real_size ;
}

static int Is_An_Prime (const int number)
{
	int count, value ;

	if (number < 2)
	{
		puts ("Wrong input.") ;
		return 0 ;
	}
	for (count = 2, value = number / 2 + 1; count < value; count++)
		if (0 == number % count)
			return 0 ;

	return 1 ;
}

static int Square_ (const int i)
{
	return i * i ;
}

