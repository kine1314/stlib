/*	extendible_hashing.c -- 可扩散列实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "extendible_hashing.h"

/*	局部函数声明	*/

static char pow_base_two (const int power) ;

/*	接口函数定义	*/

int Hash (const Item * const pitem, const char constant)
{
	return *pitem >> constant ;
}

int InitializeTable (Table * const ptable)
{
	*ptable = (struct table *) malloc (sizeof (struct table)) ;
	if (NULL == *ptable)
	{
		puts ("Out of space.[1]") ;
		return 0 ;
	}
	(*ptable) -> directory_size = M ;
	(*ptable) -> index_digit = M / 2 ;
	(*ptable) -> item_digit = LENTH ;
	(*ptable) -> array_size = M ;
	(*ptable) -> directory = (Subdirectories *) malloc (sizeof (Subdirectories) * M) ;
	if (NULL == (*ptable) -> directory)
	{
		puts ("Out of space.[2]") ;
		free (*ptable) ;
		return 0 ;
	}
	(*ptable) -> directory[0].byte_index = 0 ;
	(*ptable) -> directory[0].point = NULL ;
	(*ptable) -> directory[0].point_to_itself = NO ;
	(*ptable) -> directory[1].byte_index = 1 ;
	(*ptable) -> directory[1].point = NULL ;
	(*ptable) -> directory[1].point_to_itself = NO ;
	(*ptable) -> directory[2].byte_index = 2 ;
	(*ptable) -> directory[2].point = NULL ;
	(*ptable) -> directory[2].point_to_itself = NO ;
	(*ptable) -> directory[3].byte_index = 3 ;
	(*ptable) -> directory[3].point = NULL ;
	(*ptable) -> directory[3].point_to_itself = NO ;

	return 1 ;
}

int Insert (const Table * const ptable, const Item * const pitem)
{
	Subdirectories * s_temp ;
	Item * arr_temp ;
	char * d_temp ;
	char key, constant, difference, index, step ;
	int ct_out, ct_lin, same_preamle, d_s_record, i_temp ;

	constant = (*ptable) -> item_digit - (*ptable) -> index_digit ;
	//	取出前N位
	key = Hash (pitem, constant) ;
	/*	如果索引空间为空(针对添加操作初期的情况) 或者 未指向其自身的数据空间 创建空间同时完成添加	*/
	if (NULL == (*ptable) -> directory[key].point || NO == (*ptable) -> directory[key].point_to_itself)
	{
		(*ptable) -> directory[key].point = (Unit *) malloc (sizeof (Unit)) ;
		if (NULL == (*ptable) -> directory[key].point)
		{
			puts ("Out of space.[3]") ;
			return 0 ;
		}
		(*ptable) -> directory[key].point -> array = (Item *) malloc (sizeof (Item) * (*ptable) -> array_size) ;
		if (NULL == (*ptable) -> directory[key].point -> array)
		{
			puts ("Out of space.[4]") ;
			free ((*ptable) -> directory[key].point) ;
			return 0 ;
		}
		(*ptable) -> directory[key].point -> sub = 0 ;
		(*ptable) -> directory[key].point -> array[0] = *pitem ;
		(*ptable) -> directory[key].point -> sub++ ;
		(*ptable) -> directory[key].point_to_itself = YES ;
	}
	//	否则如果索引空间当前已满(隐式的条件是指向其自身空间)	*/
	else if ((*ptable) -> array_size == (*ptable) -> directory[key].point -> sub)
	{
		//	重复数据检测.不添加重复数据
		for (ct_out = 0; ct_out < (*ptable) -> array_size; ct_out++)
			if (*pitem == (*ptable) -> directory[key].point -> array[ct_out])
				return 0 ;
		//	记录目录中的索引值	*/
		d_temp = (char *) malloc (sizeof (char) * (*ptable) -> directory_size) ;
		if (NULL == d_temp)
		{
			puts ("Out of space.[5]") ;
			free ((*ptable) -> directory[key].point) ;
			free ((*ptable) -> directory[key].point -> array) ;
			return 0 ;
		}
		//	利用了循环展开	*/
		for (ct_out = 0, i_temp = (*ptable) -> directory_size; ct_out < i_temp; ct_out += 4)
		{
			d_temp[ct_out + 0] = (*ptable) -> directory[ct_out + 0].byte_index ;
			d_temp[ct_out + 1] = (*ptable) -> directory[ct_out + 1].byte_index ;
			d_temp[ct_out + 2] = (*ptable) -> directory[ct_out + 2].byte_index ;
			d_temp[ct_out + 3] = (*ptable) -> directory[ct_out + 3].byte_index ;
		}
		//	检测相同前导位数量	*/
		arr_temp = (Item *) malloc (sizeof (Item) * (*ptable) -> array_size) ;
		if (NULL == arr_temp)
		{
			puts ("Out of space.[6]") ;
			free ((*ptable) -> directory[key].point) ;
			free ((*ptable) -> directory[key].point -> array) ;
			free (d_temp) ;
			return 0 ;
		}
		//	记录数据空间内数据	*/
		for (ct_out = 0, i_temp = (*ptable) -> array_size; ct_out < i_temp; ct_out++)
			arr_temp[ct_out] = (*ptable) -> directory[key].point -> array[ct_out] ;
		/*	得到相同前导位数dL	*/
		for (same_preamle = (*ptable) -> index_digit; same_preamle <= LENTH; same_preamle++)
		{
			if ((arr_temp[0] >> (LENTH - same_preamle) ^ arr_temp[1] >> (LENTH - same_preamle)) != 0)
			{
				same_preamle-- ;
				break ;
			}
			if ((arr_temp[0] >> (LENTH - same_preamle) ^ arr_temp[2] >> (LENTH - same_preamle)) != 0)
			{
				same_preamle-- ;
				break ;
			}
			if ((arr_temp[0] >> (LENTH - same_preamle) ^ arr_temp[3] >> (LENTH - same_preamle)) != 0)
			{
				same_preamle-- ;
				break ;
			}
		}
		//	相同前导位数同原索引位数的差	*/
		difference = same_preamle - (*ptable) -> index_digit ;
		//	更新目录索引位数(因为数据空间满的情况下必然至少要将目录扩充一位)	*/
		(*ptable) -> index_digit = same_preamle + 1 ;
		//	如果dL > d	*/
		if (difference > 0)
			difference += 1 ;
		else
			difference = 1 ;
		//	创建新目录	*/
		s_temp = (*ptable) -> directory ;
		d_s_record = (*ptable) -> directory_size ;	//	记录原目录长度
		(*ptable) -> directory_size = (*ptable) -> directory_size * 2 * difference ;	//	更新目录长度
		//	更新索引值	*/
		key = key * 2 * difference ;
		(*ptable) -> directory = (Subdirectories *) malloc (sizeof (Subdirectories) * (*ptable) -> directory_size) ;
		if (NULL == (*ptable) -> directory)
		{
			puts ("Out of space.[6]") ;
			free ((*ptable) -> directory[key].point) ;
			free ((*ptable) -> directory[key].point -> array) ;
			free (d_temp) ;
			free (arr_temp) ;
			return 0 ;
		}
		//	更新目录	*/
		for (ct_out = 0, step = pow_base_two ((*ptable) -> index_digit) / 4; ct_out < d_s_record; ct_out++)
		{
			ct_lin = ct_out * step ;
			(*ptable) -> directory[ct_lin].byte_index = s_temp[ct_out].byte_index * step ;
			(*ptable) -> directory[ct_lin].point = s_temp[ct_out].point ;
			(*ptable) -> directory[ct_lin].point_to_itself = s_temp[ct_out].point_to_itself ;
			ct_lin++ ;
			while (ct_lin < ct_out * step + step)
			{
				(*ptable) -> directory[ct_lin].byte_index = (*ptable) -> directory[ct_lin - 1].byte_index + 1 ;
				(*ptable) -> directory[ct_lin].point = s_temp[ct_out].point ;
				(*ptable) -> directory[ct_lin].point_to_itself = NO ;
				ct_lin++ ;
			}
		}
		/*	完成最后的对单元内数据的处理(此时数据单元内一定有 (*ptable) -> array_size 个数据)	*/
		//	调整数据空间内所有数据
		for (ct_out = 0, i_temp = (*ptable) -> array_size; ct_out < i_temp; ct_out++)
		{
			index = (*ptable) -> directory[key].point -> array[ct_out] >> (LENTH - same_preamle - 1) ;
			if (NO == (*ptable) -> directory[index].point_to_itself)
			{
				(*ptable) -> directory[index].point = (Unit *) malloc (sizeof (Unit)) ;
				if (NULL == (*ptable) -> directory[index].point)
				{
					puts ("Out of space.[7]") ;
					free ((*ptable) -> directory[key].point -> array) ;
					free ((*ptable) -> directory[key].point) ;
					free (d_temp) ;
					free (arr_temp) ;
					free ((*ptable) -> directory) ;
					return 0 ;
				}
				(*ptable) -> directory[index].point -> array = (Item *) malloc (sizeof (Item) * (*ptable) -> array_size) ;
				if (NULL == (*ptable) -> directory[index].point -> array)
				{
					puts ("Ouf of space.[8]") ;
					free ((*ptable)->directory[key].point -> array) ;
					free ((*ptable)->directory[key].point) ;
					free (d_temp) ;
					free (arr_temp) ;
					free ((*ptable)->directory[index].point->array) ;
					free ((*ptable)-> directory) ;
					return 0 ;
				}
				//	初始化新的数据空间
				(*ptable)->directory[index].point -> sub = 0 ;
				//	将数据添加到新的数据空间中
				(*ptable)->directory[index].point->array[0] = (*ptable) -> directory[key].point -> array[ct_out] ;
				(*ptable)->directory[index].point->sub++ ;
				(*ptable)->directory[index].point_to_itself = YES ;
				//	对原数据空间内数据进行处理(将最后一个数据替换到移走数据的位置)
				(*ptable)->directory[key].point->array[ct_out] = (*ptable) -> directory[key].point -> array[(*ptable) -> directory[key].point -> sub - 1] ;
				(*ptable)->directory[key].point-> sub-- ;
			}
		}
		//	将新数据添加到数据空间中
		constant = (*ptable) -> item_digit - (*ptable) -> index_digit ;
		key = Hash (pitem, constant) ;
		if (NO == (*ptable) -> directory[key].point)
		{
			(*ptable) -> directory[key].point = (Unit *) malloc (sizeof (Unit)) ;
			if (NULL == (*ptable) -> directory[key].point)
			{
				puts ("Out of space.[9]") ;
				free (d_temp) ;
				free (arr_temp) ;
				return 0 ;
			}
			(*ptable) -> directory[key].point -> array = (Item *) malloc (sizeof (Item) * (*ptable) -> array_size) ;
			if (NULL == (*ptable) -> directory[key].point -> array)
			{
				puts ("Out of space.[10]") ;
				free (d_temp) ;
				free (arr_temp) ;
				free ((*ptable) -> directory[key].point) ;
				return 0 ;
			}
			(*ptable) -> directory[key].point -> array[0] = *pitem ;
			(*ptable) -> directory[key].point -> sub++ ;
			(*ptable) -> directory[key].point_to_itself = YES ;
		}
		else
		{
			(*ptable) ->directory[key].point -> array[(*ptable) -> directory[key].point -> sub] = *pitem ;
			(*ptable) ->directory[key].point -> sub++ ;
		}
		free (s_temp) ;
		free (arr_temp) ;
		free (d_temp) ;
	}
	//	最期望出现的情况	*/
	else
	{
		//	重复数据检测.不添加重复数据
		for (ct_out = 0; ct_out < (*ptable) -> array_size; ct_out++)
			if (*pitem == (*ptable) -> directory[key].point -> array[ct_out])
				return 0 ;
		(*ptable) -> directory[key].point -> array[(*ptable) ->directory[key].point -> sub] = *pitem ;
		(*ptable) -> directory[key].point -> sub++ ;
	}

	return 1 ;
}

void Traversal (const Table * const ptable, void (* pfun) (const Subdirectories subdirectories))
{
	int count, i_temp ;

	for (count = 0, i_temp = (*ptable) -> directory_size; count < i_temp; count++)
	{
		if (YES == (*ptable) -> directory[count].point_to_itself)
			(*pfun) ((*ptable) -> directory[count]) ;
	}
}

int Find (const Table * const ptable, const Item * const pitem)
{
	Item * array ;
	int count, i_temp ;
	char key, constant ;

	constant = (*ptable) -> item_digit - (*ptable) -> index_digit ;
	key = Hash (pitem, constant) ;
	if (NULL == (*ptable) -> directory[key].point)
		return 0 ;
	array = (*ptable) -> directory[key].point -> array ;
	for (count = 0, i_temp = (*ptable) -> array_size; count < i_temp; count++)
	{
		if (*pitem == (*ptable) -> directory[key].point -> array[count])
			return 1 ;
	}

	return 0 ;
}

int Delete (const Table * const ptable, const Item * const pitem)
{
	int count, i_temp ;
	char key, constant ;

	constant = (*ptable) -> item_digit - (*ptable) -> index_digit ;
	key = Hash (pitem, constant) ;
	if (NULL == (*ptable) -> directory[key].point)
		return 0 ;
	for (count = 0, i_temp = (*ptable) -> array_size; count < i_temp; count++)
	{
		if (*pitem == (*ptable) -> directory[key].point -> array[count])
		{
			(*ptable) -> directory[key].point -> array[count] = (*ptable) -> directory[key].point -> array[(*ptable) -> directory[key].point -> sub - 1] ;
			(*ptable) -> directory[key].point -> sub-- ;
			return 1 ;
		}
	}

	return 0 ;
}

void Release (const Table * const ptable)
{
	int count ;

	for (count = (*ptable) -> directory_size - 1; count >= 0; count--)
	{
		if ((*ptable) ->directory[count].point != NULL && YES == (*ptable) -> directory[count].point_to_itself)
		{
			free ((*ptable) -> directory[count].point -> array) ;
			free ((*ptable) -> directory[count].point) ;
		}		
	}
	free ((*ptable) -> directory) ;
	free (*ptable) ;
}

/*	局部函数定义	*/

static char pow_base_two (const int power)
{
	char count, value ;

	for (count = 0, value = 1; count < power; count++)
		value *= 2 ;

	return value ;
}
