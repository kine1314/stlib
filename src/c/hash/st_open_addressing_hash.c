/*
 * st_open_addressing_hash.c
 *
 *  Created on: 2011-11-28
 *      Author: kine
 */

/*	open_addressing_hash.c -- 开放定址散列表实现文件	*/
#include <malloc.h>
#include "st_open_addressing_hash.h"


/*	局部数据类型定义	*/
struct apple	/*	我实在想不出别的名字了	*/
{
	int full ;
	int value ;
} ;

/*	局部函数定义	*/

struct apple Linear_ (const int i, const int size) ;

/*	接口函数定义	*/


int OAInitializeTable (OAHashTable * const ph, const int size)
{
	int count, temp ;

	(*ph) = (struct oa_hashtable *) malloc (sizeof (struct oa_hashtable)) ;
	if (NULL == (*ph))
	{
		puts ("Out of space[1].") ;
		return UNSUCCESS ;
	}
	(*ph)->size = Get_Prime_Size (size) ;									// 表的大小是素数
	(*ph)->lists = (Cell *) malloc (sizeof (Cell) * (*ph)->size) ;		// 每个表都分配一个存储数据的list
	if (NULL == (*ph)->lists)
	{
		free ((*ph)) ;
		puts ("Out of space[2].") ;
		return UNSUCCESS ;
	}
	temp = (*ph)->size ;
	for (count = 0; count < temp; count++)
		(*ph)->lists[count].info = Empty ;									// 为没个表的info都设成empty

	return SUCCESS ;
}

Cell * OAFind (const OAHashTable * const ph, const HItem item)
{
	struct apple value ;
	int key, size, index, i = 0 ;

	size = (*ph)->size ;
	key = STHash (item, size) ;
	do
	{
		value = Linear_ (i++, size) ;
		if (value.full)
			/*	此时遍历了整个表	*/
			break ;
		index = (key + value.value) % size ;								// 线性探测发 Hi=(H(key)+di) MOD m
	}
	while (Legitimate == (*ph)->lists[index].info && (*ph)->lists[index].item != item);		// 条件：非空&&不相等

	return (*ph)->lists + index ;
}

int OAInsert (OAHashTable * const ph, const HItem item)
{
	Cell * position ;

	position = OAFind (ph, item) ;
	/* 成功找到插入位置，并进行赋值 */
	if (Empty == position->info || Deleted == position->info)
	{
		position->info = Legitimate ;
		position->item = item ;
		return SUCCESS ;
	}

	return UNSUCCESS ;
}

int OADelete (OAHashTable * const ph, const HItem item)
{
	Cell * position ;

	position = OAFind (ph, item) ;
	if (Legitimate == position->info && item == position->item)
	{
		position->info = Deleted ;
		return SUCCESS ;
	}

	return UNSUCCESS ;
}

void OATraversal (const OAHashTable * const ph, void (* pfun) (const Cell cell))
{
	int count, size = (*ph)->size ;

	for (count = 0; count < size; count++)
		(* pfun) ((*ph)->lists[count]) ;
}

void OARelease (OAHashTable * const ph)
{
	free ((*ph)->lists) ;
	free (*ph) ;
}

/*	局部函数定义	*/

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
