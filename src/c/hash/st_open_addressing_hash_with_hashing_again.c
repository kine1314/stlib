/*
 * st_open_addressing_hash_with_hashing_again.c
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */
#include <malloc.h>
#include "st_open_addressing_hash_with_hashing_again.h"

/*	�ֲ���������	*/
static int Leaner_Agian_ (const int i) ;
static int Left_Is_Equal_To_Right (const HItem left, const HItem right) ;
static void Copy_Item_To_Cell (const HItem * const pitem, Cell * const pcell) ;


/*	�ӿں�������	*/

/*	��������, ���������ݲ����ؼ���	*/
int Change (const HItem item)
{
	int key = item ;

	return key ;
}

int OAAInitializeTable (OAHashTable * const ph, const int size)
{
	int temp, count ;

	*ph = (struct oa_hashtable *) malloc (sizeof (struct oa_hashtable)) ;
	if (NULL == *ph)
	{
		puts ("Out of space.[1]") ;
		return 0 ;
	}
	temp = (*ph)->size = Get_Prime_Size (size) ;						// ����ɢ�б�Ĵ�С��������С
	(*ph)->lists = (Cell *) malloc (sizeof (Cell) * temp) ;				// Ϊÿ��������ڴ�����
	if (NULL == (*ph)->lists)
	{
		puts ("Out of space.[2]") ;
		free (*ph) ;
		return 0 ;
	}
	(*ph)->used = ZERO ;
	for (count = ZERO; count < temp; count++)							// ��ʼ��ÿ����
	{
		(*ph)->lists[count].info = Empty ;
		(*ph)->lists[count].times = ZERO ;
	}

	return 1 ;
}

Cell * OAAFind (const OAHashTable * const ph, const HItem item)
{
	int hash_value, size, index, i, key ;

	i = 0 ;
	key = Change (item) ;
	size = (*ph)->size ;
	hash_value = STHash (key, size) ;
	do
	{
		if (i < size)
			index = (key + Leaner_Agian_ (i++)) % size ;	// ����̽����ɢ�е�ַ
		else
			break ;
	}
	while (Legitimate == (*ph)->lists[index].info && !Left_Is_Equal_To_Right ((*ph)->lists[index].item, item));

	return (*ph)->lists + index ;
}

int OAAInsert (const OAHashTable * const ph, const HItem item)
{
	Cell * position ;
	int critical = (*ph)->size / 2 + 1 ;

	if ((*ph)->used >= critical)
	{
		if (ZERO == HashAgain (ph))				// ������һ���ʱ����ɢ��
			puts ("STHash again failed.") ;
	}
	position = OAAFind (ph, item) ;
	if (position->info != Legitimate)
	{
		position->info = Legitimate ;
		Copy_Item_To_Cell (&item, position) ;
		position->times++ ;
		(*ph)->used++ ;
	}
	else if (/*	Legitimate == position->info &&	*/Left_Is_Equal_To_Right (position->item, item))
		position->times++ ;
	else
		return 0 ;

	return 1 ;
}

/*
 * һ����ɢ�е��������1��������һ�����ɢ�У�2��������ʧ�ܵ�ʱ����ɢ��
 * 				��3��;�в��ԣ�����ĳһ��װ������ʱ��ɢ��
 * ���µ���ɢ����ʹ�ã�1��
 *  */
int HashAgain (const OAHashTable * const ph)
{
	OAHashTable new_h ;
	int count, old_size ;
	Cell * old_lists ;

	old_lists = (*ph)->lists ;
	old_size = (*ph)->size ;
	/*	old_size * TWO + ONE ���� old_size * TWO ���Լ���1�ι��̵���	*/
	if (ZERO == OAAInitializeTable (&new_h, old_size * TWO + ONE))		// ���³�ʼ��������С�Ĺ�ϣ��
		return 0 ;
	for (count = 0; count < old_size; count++)							// ��ԭ����Ԫ�ز��뵽�µı���
		if (Legitimate == old_lists[count].info)
			OAAInsert (&new_h, old_lists[count].item) ;
	(*ph)->lists = new_h->lists ;
	(*ph)->size = new_h->size ;
	free (old_lists) ;
	free (new_h) ;

	return 1 ;
}

int OAADelete (const OAHashTable * const ph, const HItem item)
{
	Cell * position ;

	position = OAAFind (ph, item) ;
	if (Legitimate == position->info && Left_Is_Equal_To_Right (position->item, item))
	{
		if (ONE == position->times)
		{
			position->info = Deleted ;
			(*ph)->used-- ;
		}
		position->times-- ;
		return 1 ;
	}

	return 0 ;
}

void OAATraversal (const OAHashTable * const ph, void (* pfun) (const Cell cell))
{
	int count, temp ;

	/*	���ٴ洢������	*/
	for (count = 0, temp = (*ph)->size; count < temp; count++)
		(* pfun) ((*ph)->lists[count]) ;
}

void OAARelease (const OAHashTable * const ph)
{
	free ((*ph)->lists) ;
	free (*ph) ;
}

/*	�ֲ���������	*/


static int Leaner_Agian_ (const int i)
{
	return i ;
}

static int Left_Is_Equal_To_Right (const HItem left, const HItem right)
{
	return left == right ;
}

static void Copy_Item_To_Cell (const HItem * const pitem, Cell * const pcell)
{
	pcell->item = *pitem ;
}
