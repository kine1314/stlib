/*
 * st_extendible_hashing.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_EXTENDIBLE_HASHING_H_
#define ST_EXTENDIBLE_HASHING_H_
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;
#define EX_M 		4				// ������Ŀ¼�Ĵ�С
#define EX_LENTH 	8
#define NO 			0
#define YES 		1

/*	�������Ͷ���	*/

typedef unsigned char EXItem ;		/*	����	*/
typedef struct ex_unit
{
	EXItem * array ;				/*	��������	*/
	char sub ;						/*	ʹ���б�Ԫ������	*/
} EXUnit ;							/*	���ݵ�Ԫ	*/
typedef struct ex_subdir
{
	EXUnit * point ;				/*	ָ�����ݵ�Ԫ��ָ��	*/
	char point_to_itself ;			/*	����Ƿ�ָ����䱾������ݿռ�	*/
	char byte_index ;				/*	λ����ֵ	*/
} EXSubdir ;						/*	��Ŀ¼	*/
typedef struct ex_htable
{
	EXSubdir * directory ;			/*	Ŀ¼(��Ŀ¼����)	*/
	char directory_size ;			/*	Ŀ¼��С	*/
	char index_digit ;				/*	����λ��	*/
	char item_digit ;				/*	����λ��	*/
	char array_size ;				/*	���������С	*/
} * EXHTable ;


/*	��������������Ϊchar����.�з���8λ������,�������ڲ���	*/

/*	�ӿں�������	*/

/*	����:	���ݶ����������ݲ���һ����ֵ������	*/
/*	����ǰ:	pitem ָ��ָ������, constant �Ǳ���λ����ֵ	*/
/*	������:	����һ����ֵ������	*/
int EXHash (const EXItem * const pitem, const char constant) ;

/*	����:	��������ʼ��һ������ɢ�б�	*/
/*	����ǰ:	ptable ָ��һ������ɢ�б�	*/
/*	������:	����ڴ����ɹ�, �����ÿ���ɢ�б�, Ŀ¼��С��ʼ��Ϊ4, ����λ����ʼ��Ϊ2, ���������С��ʼ��Ϊ4, ����1; ���򷵻�0	*/
int EXInitializeTable (EXHTable * const ptable) ;

/*	����:	�����ɢ�б������һ��Ԫ��	*/
/*	����ǰ:	ptable ָ��һ���ѳ�ʼ���Ŀ���ɢ�б�, pitem ָ��ָ��������	*/
/*	������:	���δ�ظ����, ����ڴ����ɹ�, ��ָ����������ӵ�����ɢ�б���, ����1; ���򷵻�0	*/
int EXInsert (const EXHTable * const ptable, const EXItem * const pitem) ;

/*	����:	���Ҳ����ؿ���ɢ�б��е�һ��ָ������	*/
/*	����ǰ:	ptable ָ��һ���ѳ�ʼ���Ŀ���ɢ�б�, pitem ָ��ָ��������	*/
/*	������:	����ҵ�, ����1; ���򷵻�0	*/
int EXFind (const EXHTable * const ptable, const EXItem * const pitem) ;

/*	����:	�ӿ���ɢ�б�Ŀ¼�ĵ���������������ν�һ������������pointָ��ָ�����������ݿռ�ĵ���Ŀ¼	*/
/*	����ǰ:	ptable ָ��һ���ѳ�ʼ���Ŀ���ɢ�б�, pfun ָ��һ��û�з���ֵ, ����һ��Subdirectories���Ͳ����ĺ���	*/
/*	������:	�ӿ���ɢ�б�Ŀ¼�ĵ���������������ν�һ������������pointָ��ָ�����������ݿռ�ĵ���Ŀ¼	*/
void EXTraversal (const EXHTable * const ptable, void (* pfun) (const EXSubdir ex_subdir)) ;

/*	����:	�ӿ���ɢ�б���ɾ��һ��ָ������	*/
/*	����ǰ:	ptable ָ��һ���ѳ�ʼ���Ŀ���ɢ�б�, pitem ��׼��ɾ��������	*/
/*	������:	����ҵ�������, �������ݴӿ���ɢ�б���ɾ��, ����1; ���򷵻�0	*/
int EXDelete (const EXHTable * const ptable, const EXItem * const pitem) ;

/*	����:	��տ���ɢ�б�ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	pteble ָ��һ���ѳ�ʼ���Ŀ���ɢ�б�	*/
/*	������:	�ÿ���ɢ�б�ռ�õ��ڴ�ռ䱻�ͷ�	*/
void EXRelease (const EXHTable * const ptable) ;


ST_END_DECLS ;
#endif /* ST_EXTENDIBLE_HASHING_H_ */
