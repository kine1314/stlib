/*
 * st_open_addressing_hash_2.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_OPEN_ADDRESSING_HASH_2_H_
#define ST_OPEN_ADDRESSING_HASH_2_H_
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;


/*	�ӿں�������	*/


/*	����:	��������ʼ��һ����	*/
/*	����ǰ:	ph ָ��һ����, size ��ָʾ��Ĵ�С�ı���	*/
/*	������:	�������, �ñ�������������Ԫ����������Ϊ��, ��� size ��������, ��ȡ���� size ����С����Ϊ��Ĵ�С, ����1; ���򷵻�0	*/
int OA2InitializeTable (OAHashTable * const ph, const int size) ;

/*	����:	���Ҳ����ر���������Ϊָ�����ݵ�Ԫ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, item ��ָ��������	*/
/*	������:	�������, ����һ��ָ��������Ϊָ�����ݵ�Ԫ�ص�ָ��; ���򷵻�һ��ָ��ͣ���ڲ��ҹ��̽���ʱԪ��λ�õ�ָ��	*/
Cell * OA2Find (const OAHashTable * const ph, const HItem item) ;

/*	����:	��������һ��������Ϊָ�����ݵ�Ԫ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, item ��ָ��������	*/
/*	������:	�������, ������Ϊָ�����ݵ�Ԫ�ر���ӵ�����, ����1; ���򷵻�0	*/
int OA2Insert (const OAHashTable * const ph, const HItem item) ;

/*	����:	�ӱ���ɾ��һ��������Ϊָ�����ݵ�Ԫ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, item ��ָ��������	*/
/*	������:	�������, ������Ϊָ�����ݵ�Ԫ�ر��ӱ���ɾ��, ����1; ���򷵻�0	*/
int OA2Delete (const OAHashTable * const ph, const HItem item) ;

/*	����:	�ӵ���������������ν�һ�����������ڱ�������Ԫ��һ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, pfun ָ��һ��û�з���ֵ, ����һ��Cell���Ͳ����ĺ���	*/
/*	������:	�ӵ���������������ν� pfun ָ��ĺ��������ڱ�������Ԫ��һ��	*/
void OA2Traversal (const OAHashTable * const ph, void (* pfun) (const Cell cell)) ;

/*	����:	�ͷ�һ����ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�ñ�ռ�õ��ڴ�ռ䱻�ͷ�	*/
void OA2Release (const OAHashTable * const ph) ;



ST_END_DECLS ;
#endif /* ST_OPEN_ADDRESSING_HASH_2_H_ */
