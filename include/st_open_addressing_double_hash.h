/*
 * st_open_addressing_double_hash.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_OPEN_ADDRESSING_DOUBLE_HASH_H_
#define ST_OPEN_ADDRESSING_DOUBLE_HASH_H_
//���Ŷ�ַɢ�б�˫ɢ��ͷ�ļ�	���Ŷ�ַɢ�б�����̽�ⷨ��˫ɢ�У���ʵ���ļ�C����
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;
/*	�ӿں�������	*/


/*	����:	��������ʼ��һ����	*/
/*	����ǰ:	ph ָ��һ����, size ������ָʾ���С�ı���	*/
/*	������:	�������, �����ñ�, ��������Ԫ����������Ϊ��, ��� size ������, ȡ size Ϊ��Ĵ�С, ����ȡ���� size ����С����Ϊ��Ĵ�С, ����1; ���򷵻�0	*/
int OADInitializeTable (OAHashTable * const ph, const int size) ;

/*	����:	���Ҳ�����һ��ָ��������Ϊָ�����ݵ�Ԫ�ص�ָ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, item ��ָ�������ҵ�����	*/
/*	������:	�������, ����һ��ָ�򱻲���Ԫ�ص�ָ��; ���򷵻�һ��ָ����ҽ���ʱԪ��λ�õ�ָ��	*/
Cell * OADFind (const OAHashTable * const ph, const HItem item) ;

/*	����:	��������һ��������Ϊָ�����ݵĽ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, item ��ָ������ӵ�����	*/
/*	������:	�������, ������Ϊָ�����ݵ�һ���½�㱻��ӵ�����, ����1; �������, ����0	*/
int OADInsert (const OAHashTable * const ph, const HItem item) ;

/*	����:	�ӱ���ɾ��һ��������Ϊָ�����ݵĽ��	*/
/*	����ǰ: ph ָ��һ���ѳ�ʼ���ı�, item ��ָ����ɾ��������	*/
/*	������:	�������, ������Ϊָ�����ݵ�һ����㱻�ӱ���ɾ��, ����1; ����ɾ��, ����0	*/
int OADDelete (const OAHashTable * const ph, const HItem item) ;

/*	����:	�ӵ���������������ν�һ�����������ڱ�������Ԫ��һ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, pfun ָ��һ��û�з���ֵ, ����һ��Cell���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ����ӵ���������������������ڱ�������Ԫ��һ��	*/
void OADTraversal (const OAHashTable * const ph, void (* pfun) (const Cell cell)) ;

/*	����:	�ͷ�һ����ռ�õ��ڴ�ռ�	*/
/*	����ǰ: ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������: �ñ�ռ�õ��ڴ�ռ䱻�ͷ�	*/
void OADRelease (const OAHashTable * const ph) ;



ST_END_DECLS ;
#endif /* ST_OPEN_ADDRESSING_DOUBLE_HASH_H_ */
