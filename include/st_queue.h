#ifndef	__ST_QUEUE_H__
#define	__ST_QUEUE_H__
#include "stlib.h"

ST_BEGIN_DECLS;

typedef int 	QItem ;
typedef struct _STQueueNode_s
{
	QItem item ;
	struct _STQueueNode_s * next ;
} STQueueNode_t ;

typedef struct _STQueue_s
{
	STQueueNode_t * front, * rear ;			// ���е�ͷβ
	int current ;							// ���еĴ�С
} * PSTQueue ;


/*	�ӿں�������	*/

/*	����:	��������ʼ��һ������	*/
/*	����ǰ:	pq ָ��һ������	*/
/*	������:	����ڴ����ɹ�, ��������ʼ���ö���, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool STInitialize_Q (PSTQueue * const pq) ;

/*	����:	ȷ��һ�������Ƿ�Ϊ��	*/
/*	����ǰ:	pq ָ��һ���ѳ�ʼ���Ķ���	*/
/*	������:	����ö���Ϊ��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool STIsEmpty_Q (const PSTQueue * const pq) ;

/*	����:	����������һ��������Ϊָ�����ݵĽ��	*/
/*	����ǰ:	pq ָ��һ���ѳ�ʼ���Ķ���, item ��ָ�����������	*/
/*	������:	����ڴ����ɹ�, ���������Ϊ item �Ľ�㵽������, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool STEnQueue_Q (const PSTQueue * const pq, const QItem item) ;

/*	����:	�Ӷ�����ɾ��ͷ�����, �ͷ���ռ�õ��ڴ�ռ�, ��������������ָ������	*/
/*	����ǰ:	pq ָ��һ���ѳ�ʼ���Ķ���, messenger ��һ��ָ�� QItem ��ָ��, ���ڽ�����Я���ص��ñ������ĺ���	*/
/*	������:	������в�Ϊ��, ɾ��ͷ���, �ͷ���ռ�õ��ڴ�ռ�, ����ͷ���, �������������� *messenger	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool STDeQueue_Q (const PSTQueue * const pq, QItem * const messenger) ;

/*	����:	�ͷ�һ������ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	pq ָ��һ���ѳ�ʼ���Ķ���	*/
/*	������:	�ö���ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O (N)	*/
void STRelease_Q (const PSTQueue * const pq) ;



ST_END_DECLS;
#endif	/* __ST_QUEUE_H__ */

