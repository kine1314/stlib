/*	open_addressing_hash_with_hashing_again.c -- 开放定址散列表线性探测法可再散列实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "open_addressing_hash_with_hashing_again.h"

/*	局部函数声明	*/

static int Get_Prime_Value (const int size) ;
static int Is_A_Prime (const int number) ;
static int Leaner_ (const int i) ;
static int Left_Is_Equal_To_Right (const Item left, const Item right) ;
static void Copy_Item_To_Cell (const Item * const pitem, Cell * const pcell) ;

/*	接口函数定义	*/

int Hash (const int key, const int size)
{
	return key % size ;
}

/*	接受数据, 并依据数据产生关键字	*/
int Change (const Item item)
{
	int key = item ;

	return key ;
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
	(*ph) -> used = ZERO ;
	for (count = ZERO; count < temp; count++)
	{
		(*ph) -> lists[count].info = Empty ;
		(*ph) -> lists[count].times = ZERO ;
	}

	return 1 ;
}

Cell * Find (const HashTable * const ph, const Item item)
{
	int hash_value, size, index, i, key ;

	i = 0 ;
	key = Change (item) ;
	size = (*ph) -> size ;
	hash_value = Hash (key, size) ;
	do
	{
		if (i < size)
			index = (key + Leaner_ (i++)) % size ;
		else
			break ;
	}
	while (Legitimate == (*ph) -> lists[index].info && !Left_Is_Equal_To_Right ((*ph) -> lists[index].item, item))
		;
	
	return (*ph) -> lists + index ;
}

int Insert (const HashTable * const ph, const Item item)
{
	Cell * position ;
	int critical = (*ph) -> size / 2 + 1 ;

	if ((*ph) -> used >= critical)
	{
		if (ZERO == HashAgain (ph))
			puts ("Hash again failed.") ;
	}
	position = Find (ph, item) ;
	if (position -> info != Legitimate)
	{
		position -> info = Legitimate ;
		Copy_Item_To_Cell (&item, position) ;
		position -> times++ ;
		(*ph) -> used++ ;
	}
	else if (/*	Legitimate == position -> info &&	*/Left_Is_Equal_To_Right (position -> item, item))
		position -> times++ ;
	else
		return 0 ;

	return 1 ;
}

int HashAgain (const HashTable * const ph)
{
	HashTable new_h ;
	int count, old_size ;
	Cell * old_lists ;
	
	old_lists = (*ph) -> lists ;
	old_size = (*ph) -> size ;
	/*	old_size * TWO + ONE 代替 old_size * TWO 可以减少1次过程调用	*/
	if (ZERO == InitializeTable (&new_h, old_size * TWO + ONE))
		return 0 ;
	for (count = 0; count < old_size; count++)
		if (Legitimate == old_lists[count].info)
			Insert (&new_h, old_lists[count].item) ;
	(*ph) -> lists = new_h -> lists ;
	(*ph) -> size = new_h -> size ;
	free (old_lists) ;
	free (new_h) ;

	return 1 ;
}

int Delete (const HashTable * const ph, const Item item)
{
	Cell * position ;

	position = Find (ph, item) ;
	if (Legitimate == position -> info && Left_Is_Equal_To_Right (position -> item, item))
	{
		if (ONE == position -> times)
		{
			position -> info = Deleted ;
			(*ph) -> used-- ;
		}
		position -> times-- ;
		return 1 ;
	}

	return 0 ;
}

void Traversal (const HashTable * const ph, void (* pfun) (const Cell cell))
{
	int count, temp ;

	/*	减少存储器引用	*/
	for (count = 0, temp = (*ph) -> size; count < temp; count++)
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

	while (!Is_A_Prime (real_size))
		real_size++ ;

	return real_size ;
}

static int Is_A_Prime (const int number)
{
	int count, temp ;

	if (number < 2)
	{
		puts ("Wrong input.") ;
		return 0 ;
	}
	for (count = 2, temp = number / 2 + 1; count <= temp; count++)
		if (0 == number % count)
			return 0 ;

	return 1 ;
}

static int Leaner_ (const int i)
{
	return i ;
}

static int Left_Is_Equal_To_Right (const Item left, const Item right)
{
	return left == right ;
}

static void Copy_Item_To_Cell (const Item * const pitem, Cell * const pcell)
{
	pcell -> item = *pitem ;
}
