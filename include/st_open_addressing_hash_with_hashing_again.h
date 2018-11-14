/*
 * st_open_addressing_hash_with_hashing_again.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_OPEN_ADDRESSING_HASH_WITH_HASHING_AGAIN_H_
#define ST_OPEN_ADDRESSING_HASH_WITH_HASHING_AGAIN_H_
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;


/*	����:	���ݴ������Ĳ�������һ��int����ֵ������	*/
/*	����ǰ:	item �Ǵ������Ĳ���	*/
/*	������:	����һ��int����ֵ������	*/
int OAAChange (const HItem item) ;

/*	����:	��������ʼ��һ����	*/
/*	����ǰ:	ph ָ��һ��δ��ʼ���ı�, size ������ָʾ���С�ı���	*/
/*	������:	����ڴ�ռ����ɹ�, ������, ��������Ԫ����������Ϊ��, ��� size ����������ȡ���� size ����С����Ϊ��Ĵ�С, ����1; ���򲻴�����, ����0	*/
int OAAInitializeTable (OAHashTable * const ph, const int size) ;

/*	����:	����һ��������Ϊָ�����ݵ�Ԫ���ڱ��е�λ�ò�����ָ���λ�õ�ָ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, item ��ָ������	*/
/*	������:	����ҵ�, ����һ��ָ��������Ϊָ�����ݵ�Ԫ�ص�ָ��; ���򷵻�һ��ָ����ҽ���ʱͣ��Ԫ�ش���ָ��	*/
Cell * OAAFind (const OAHashTable * const ph, const HItem item) ;

/*	����:	��������һ��������Ϊָ�����ݵ�Ԫ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, item ��ָ������	*/
/*	������:	����ҵ���������Ԫ�ص�λ��, ��������Ϊָ�����ݵ�Ԫ����ӵ�����, ���ظ�����ӳ��ִ���, ����1; ���򷵻�0	*/
int OAAInsert (const OAHashTable * const ph, const HItem item) ;

/*	����:	��һ������ɢ��Ϊ��СΪ���ڵ���ԭ���С2������С�����ı�, �������ݿ������±�, �ͷ�ԭ��ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	����ڴ�ռ����ɹ�, �±�����, ��СΪ���ڵ���ԭ���С2������С�����ı�, ԭ�����ݿ������±�, ����1; ���򲻸ı�ԭ��, ����0	*/
int OAAHashAgain (const OAHashTable * const ph) ;

/*	����:	��һ��������Ϊָ�����ݵ�Ԫ�شӱ���ɾ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�	*/
/*	����ǰ:	����ҵ�������Ϊָ�����ݵ�Ԫ��, ����ӱ���ɾ��, ����1; ���򷵻�0	*/
int OAADelete (const OAHashTable * const ph, const HItem item) ;

/*	����:	�ӵ���������������ν�һ�����������ڱ�������Ԫ��1��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, pfun ָ��һ��û�з���ֵ, ����һ��Cell���Ͳ����ĺ���	*/
/*	������:	�ӵ������������һ�ν�pfunָ��ĺ��������ڱ�������Ԫ��1��	*/
void OAATraversal (const OAHashTable * const ph, void (* pfun) (const Cell cell)) ;

/*	����:	�ͷ�һ����ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�ñ�ռ�õ��ڴ�ռ䱻�ͷ�	*/
void OAARelease (const OAHashTable * const ph) ;


ST_END_DECLS ;
#endif /* ST_OPEN_ADDRESSING_HASH_WITH_HASHING_AGAIN_H_ */
