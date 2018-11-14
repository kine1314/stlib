/*
 * st_extendible_hashing.c
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */
#include <malloc.h>
#include "st_extendible_hashing.h"

/*	�ֲ���������	*/

static char pow_base_two (const int power) ;

/*	�ӿں�������	*/

int EXHash (const EXItem * const pitem, const char constant)
{
	return *pitem >> constant ;
}

int EXInitializeTable (EXHTable * const ptable)
{
	*ptable = (struct ex_htable *) malloc (sizeof (struct ex_htable)) ;
	if (NULL == *ptable)
	{
		puts ("Out of space.[1]") ;
		return 0 ;
	}
	(*ptable)->directory_size = EX_M ;
	(*ptable)->index_digit = EX_M / 2 ;
	(*ptable)->item_digit = EX_LENTH ;
	(*ptable)->array_size = EX_M ;
	(*ptable)->directory = (EXSubdir *) malloc (sizeof (EXSubdir) * EX_M) ;
	if (NULL == (*ptable)->directory)
	{
		puts ("Out of space.[2]") ;
		free (*ptable) ;
		return 0 ;
	}
	(*ptable)->directory[0].byte_index = 0 ;
	(*ptable)->directory[0].point = NULL ;
	(*ptable)->directory[0].point_to_itself = NO ;
	(*ptable)->directory[1].byte_index = 1 ;
	(*ptable)->directory[1].point = NULL ;
	(*ptable)->directory[1].point_to_itself = NO ;
	(*ptable)->directory[2].byte_index = 2 ;
	(*ptable)->directory[2].point = NULL ;
	(*ptable)->directory[2].point_to_itself = NO ;
	(*ptable)->directory[3].byte_index = 3 ;
	(*ptable)->directory[3].point = NULL ;
	(*ptable)->directory[3].point_to_itself = NO ;

	return 1 ;
}

int EXInsert (const EXHTable * const ptable, const EXItem * const pitem)
{
	EXSubdir * s_temp ;
	EXItem * arr_temp ;
	char * d_temp ;
	char key, constant, difference, index, step ;
	int ct_out, ct_lin, same_preamle, d_s_record, i_temp ;

	constant = (*ptable)->item_digit - (*ptable)->index_digit ;
	//	ȡ��ǰNλ
	key = EXHash (pitem, constant) ;
	/*	��������ռ�Ϊ��(�����Ӳ������ڵ����) ���� δָ������������ݿռ� �����ռ�ͬʱ������	*/
	if (NULL == (*ptable)->directory[key].point || NO == (*ptable)->directory[key].point_to_itself)
	{
		(*ptable)->directory[key].point = (EXUnit *) malloc (sizeof (EXUnit)) ;
		if (NULL == (*ptable)->directory[key].point)
		{
			puts ("Out of space.[3]") ;
			return 0 ;
		}
		(*ptable)->directory[key].point->array = (EXItem *) malloc (sizeof (EXItem) * (*ptable)->array_size) ;
		if (NULL == (*ptable)->directory[key].point->array)
		{
			puts ("Out of space.[4]") ;
			free ((*ptable)->directory[key].point) ;
			return 0 ;
		}
		(*ptable)->directory[key].point->sub = 0 ;
		(*ptable)->directory[key].point->array[0] = *pitem ;
		(*ptable)->directory[key].point->sub++ ;
		(*ptable)->directory[key].point_to_itself = YES ;
	}
	//	������������ռ䵱ǰ����(��ʽ��������ָ��������ռ�)	*/
	else if ((*ptable)->array_size == (*ptable)->directory[key].point->sub)
	{
		//	�ظ����ݼ��.������ظ�����
		for (ct_out = 0; ct_out < (*ptable)->array_size; ct_out++)
			if (*pitem == (*ptable)->directory[key].point->array[ct_out])
				return 0 ;
		//	��¼Ŀ¼�е�����ֵ	*/
		d_temp = (char *) malloc (sizeof (char) * (*ptable)->directory_size) ;
		if (NULL == d_temp)
		{
			puts ("Out of space.[5]") ;
			free ((*ptable)->directory[key].point) ;
			free ((*ptable)->directory[key].point->array) ;
			return 0 ;
		}
		//	������ѭ��չ��	*/
		for (ct_out = 0, i_temp = (*ptable)->directory_size; ct_out < i_temp; ct_out += 4)
		{
			d_temp[ct_out + 0] = (*ptable)->directory[ct_out + 0].byte_index ;
			d_temp[ct_out + 1] = (*ptable)->directory[ct_out + 1].byte_index ;
			d_temp[ct_out + 2] = (*ptable)->directory[ct_out + 2].byte_index ;
			d_temp[ct_out + 3] = (*ptable)->directory[ct_out + 3].byte_index ;
		}
		//	�����ͬǰ��λ����	*/
		arr_temp = (EXItem *) malloc (sizeof (EXItem) * (*ptable)->array_size) ;
		if (NULL == arr_temp)
		{
			puts ("Out of space.[6]") ;
			free ((*ptable)->directory[key].point) ;
			free ((*ptable)->directory[key].point->array) ;
			free (d_temp) ;
			return 0 ;
		}
		//	��¼���ݿռ�������	*/
		for (ct_out = 0, i_temp = (*ptable)->array_size; ct_out < i_temp; ct_out++)
			arr_temp[ct_out] = (*ptable)->directory[key].point->array[ct_out] ;
		/*	�õ���ͬǰ��λ��dL	*/
		for (same_preamle = (*ptable)->index_digit; same_preamle <= EX_LENTH; same_preamle++)
		{
			if ((arr_temp[0] >> (EX_LENTH - same_preamle) ^ arr_temp[1] >> (EX_LENTH - same_preamle)) != 0)
			{
				same_preamle-- ;
				break ;
			}
			if ((arr_temp[0] >> (EX_LENTH - same_preamle) ^ arr_temp[2] >> (EX_LENTH - same_preamle)) != 0)
			{
				same_preamle-- ;
				break ;
			}
			if ((arr_temp[0] >> (EX_LENTH - same_preamle) ^ arr_temp[3] >> (EX_LENTH - same_preamle)) != 0)
			{
				same_preamle-- ;
				break ;
			}
		}
		//	��ͬǰ��λ��ͬԭ����λ���Ĳ�	*/
		difference = same_preamle - (*ptable)->index_digit ;
		//	����Ŀ¼����λ��(��Ϊ���ݿռ���������±�Ȼ����Ҫ��Ŀ¼����һλ)	*/
		(*ptable)->index_digit = same_preamle + 1 ;
		//	���dL > d	*/
		if (difference > 0)
			difference += 1 ;
		else
			difference = 1 ;
		//	������Ŀ¼	*/
		s_temp = (*ptable)->directory ;
		d_s_record = (*ptable)->directory_size ;	//	��¼ԭĿ¼����
		(*ptable)->directory_size = (*ptable)->directory_size * 2 * difference ;	//	����Ŀ¼����
		//	��������ֵ	*/
		key = key * 2 * difference ;
		(*ptable)->directory = (EXSubdir *) malloc (sizeof (EXSubdir) * (*ptable)->directory_size) ;
		if (NULL == (*ptable)->directory)
		{
			puts ("Out of space.[6]") ;
			free ((*ptable)->directory[key].point) ;
			free ((*ptable)->directory[key].point->array) ;
			free (d_temp) ;
			free (arr_temp) ;
			return 0 ;
		}
		//	����Ŀ¼	*/
		for (ct_out = 0, step = pow_base_two ((*ptable)->index_digit) / 4; ct_out < d_s_record; ct_out++)
		{
			ct_lin = ct_out * step ;
			(*ptable)->directory[ct_lin].byte_index = s_temp[ct_out].byte_index * step ;
			(*ptable)->directory[ct_lin].point = s_temp[ct_out].point ;
			(*ptable)->directory[ct_lin].point_to_itself = s_temp[ct_out].point_to_itself ;
			ct_lin++ ;
			while (ct_lin < ct_out * step + step)
			{
				(*ptable)->directory[ct_lin].byte_index = (*ptable)->directory[ct_lin - 1].byte_index + 1 ;
				(*ptable)->directory[ct_lin].point = s_temp[ct_out].point ;
				(*ptable)->directory[ct_lin].point_to_itself = NO ;
				ct_lin++ ;
			}
		}
		/*	������ĶԵ�Ԫ�����ݵĴ���(��ʱ���ݵ�Ԫ��һ���� (*ptable)->array_size ������)	*/
		//	�������ݿռ�����������
		for (ct_out = 0, i_temp = (*ptable)->array_size; ct_out < i_temp; ct_out++)
		{
			index = (*ptable)->directory[key].point->array[ct_out] >> (EX_LENTH - same_preamle - 1) ;
			if (NO == (*ptable)->directory[index].point_to_itself)
			{
				(*ptable)->directory[index].point = (EXUnit *) malloc (sizeof (EXUnit)) ;
				if (NULL == (*ptable)->directory[index].point)
				{
					puts ("Out of space.[7]") ;
					free ((*ptable)->directory[key].point->array) ;
					free ((*ptable)->directory[key].point) ;
					free (d_temp) ;
					free (arr_temp) ;
					free ((*ptable)->directory) ;
					return 0 ;
				}
				(*ptable)->directory[index].point->array = (EXItem *) malloc (sizeof (EXItem) * (*ptable)->array_size) ;
				if (NULL == (*ptable)->directory[index].point->array)
				{
					puts ("Ouf of space.[8]") ;
					free ((*ptable)->directory[key].point->array) ;
					free ((*ptable)->directory[key].point) ;
					free (d_temp) ;
					free (arr_temp) ;
					free ((*ptable)->directory[index].point->array) ;
					free ((*ptable)->directory) ;
					return 0 ;
				}
				//	��ʼ���µ����ݿռ�
				(*ptable)->directory[index].point->sub = 0 ;
				//	��������ӵ��µ����ݿռ���
				(*ptable)->directory[index].point->array[0] = (*ptable)->directory[key].point->array[ct_out] ;
				(*ptable)->directory[index].point->sub++ ;
				(*ptable)->directory[index].point_to_itself = YES ;
				//	��ԭ���ݿռ������ݽ��д���(�����һ�������滻���������ݵ�λ��)
				(*ptable)->directory[key].point->array[ct_out] = (*ptable)->directory[key].point->array[(*ptable)->directory[key].point->sub - 1] ;
				(*ptable)->directory[key].point->sub-- ;
			}
		}
		//	����������ӵ����ݿռ���
		constant = (*ptable)->item_digit - (*ptable)->index_digit ;
		key = EXHash (pitem, constant) ;
		if (NO == (*ptable)->directory[key].point)
		{
			(*ptable)->directory[key].point = (EXUnit *) malloc (sizeof (EXUnit)) ;
			if (NULL == (*ptable)->directory[key].point)
			{
				puts ("Out of space.[9]") ;
				free (d_temp) ;
				free (arr_temp) ;
				return 0 ;
			}
			(*ptable)->directory[key].point->array = (EXItem *) malloc (sizeof (EXItem) * (*ptable)->array_size) ;
			if (NULL == (*ptable)->directory[key].point->array)
			{
				puts ("Out of space.[10]") ;
				free (d_temp) ;
				free (arr_temp) ;
				free ((*ptable)->directory[key].point) ;
				return 0 ;
			}
			(*ptable)->directory[key].point->array[0] = *pitem ;
			(*ptable)->directory[key].point->sub++ ;
			(*ptable)->directory[key].point_to_itself = YES ;
		}
		else
		{
			(*ptable) ->directory[key].point->array[(*ptable)->directory[key].point->sub] = *pitem ;
			(*ptable) ->directory[key].point->sub++ ;
		}
		free (s_temp) ;
		free (arr_temp) ;
		free (d_temp) ;
	}
	//	���������ֵ����	*/
	else
	{
		//	�ظ����ݼ��.������ظ�����
		for (ct_out = 0; ct_out < (*ptable)->array_size; ct_out++)
			if (*pitem == (*ptable)->directory[key].point->array[ct_out])
				return 0 ;
		(*ptable)->directory[key].point->array[(*ptable) ->directory[key].point->sub] = *pitem ;
		(*ptable)->directory[key].point->sub++ ;
	}

	return 1 ;
}

void EXTraversal (const EXHTable * const ptable, void (* pfun) (const EXSubdir ex_subdir))
{
	int count, i_temp ;

	for (count = 0, i_temp = (*ptable)->directory_size; count < i_temp; count++)
	{
		printf("(*ptable)->directory_size [%d]\n", (*ptable)->directory_size);
		if (YES == (*ptable)->directory[count].point_to_itself)
			(*pfun) ((*ptable)->directory[count]) ;
	}
}

int EXFind (const EXHTable * const ptable, const EXItem * const pitem)
{
	EXItem * array ;
	int count, i_temp ;
	char key, constant ;

	constant = (*ptable)->item_digit - (*ptable)->index_digit ;
	key = EXHash (pitem, constant) ;
	if (NULL == (*ptable)->directory[key].point)
		return 0 ;
	array = (*ptable)->directory[key].point->array ;
	for (count = 0, i_temp = (*ptable)->array_size; count < i_temp; count++)
	{
		if (*pitem == (*ptable)->directory[key].point->array[count])
			return 1 ;
	}

	return 0 ;
}

int EXDelete (const EXHTable * const ptable, const EXItem * const pitem)
{
	int count, i_temp ;
	char key, constant ;

	constant = (*ptable)->item_digit - (*ptable)->index_digit ;
	key = EXHash (pitem, constant) ;
	if (NULL == (*ptable)->directory[key].point)
		return 0 ;
	for (count = 0, i_temp = (*ptable)->array_size; count < i_temp; count++)
	{
		if (*pitem == (*ptable)->directory[key].point->array[count])
		{
			(*ptable)->directory[key].point->array[count] = (*ptable)->directory[key].point->array[(*ptable)->directory[key].point->sub - 1] ;
			(*ptable)->directory[key].point->sub-- ;
			return 1 ;
		}
	}

	return 0 ;
}

void EXRelease (const EXHTable * const ptable)
{
	int count ;

	for (count = (*ptable)->directory_size - 1; count >= 0; count--)
	{
		if ((*ptable) ->directory[count].point != NULL && YES == (*ptable)->directory[count].point_to_itself)
		{
			free ((*ptable)->directory[count].point->array) ;
			free ((*ptable)->directory[count].point) ;
		}
	}
	free ((*ptable)->directory) ;
	free (*ptable) ;
}

/*	�ֲ���������	*/

static char pow_base_two (const int power)
{
	char count, value ;

	for (count = 0, value = 1; count < power; count++)
		value *= 2 ;

	return value ;
}

