#ifndef	__ST_BINOMIAL_QUEUE_H__
#define	__ST_BINOMIAL_QUEUE_H__



/*	st_binomial_queue.h -- �������ͷ�ļ�	*/
/*	ͷ�ļ����ط���ͷ�ļ��Ǹ�������	*/
#include <stdio.h>
#include <stdlib.h>

#include "stlib.h"
ST_BEGIN_DECLS;



#define BQINFINITY 32767

/*	�������Ͷ���	*/

typedef long BQItem ;					//	Ϊʲô�����ϲ�� int ^ ^
typedef struct _BQNode
{
	BQItem item ;
	struct _BQNode * left ;				//	��һ������
	struct _BQNode * nextsibling ;		//	���ֵ�
} BQNode ;

typedef BQNode * SubTree ;
typedef struct binqueue
{
	SubTree * forest ;					// ������е�ɭ��
	int size ;
	int current ;
} * BinQueue ;

/*	�ӿں�������	*/

/*	����:	��ʼ��һ���������	*/
/*	����ǰ:	pbq ָ��һ���������, size ָʾ���С	*/
/*	������:	����ڴ����ɹ�, �� size ��С�Ķ�����б���ʼ��Ϊ��, ����1; ���򷵻�0	*/
int BQInitialize (BinQueue * const pbq, const int size) ;

/*	����:	ȷ��һ����������Ƿ�Ϊ��	*/
/*	����ǰ:	bq ��һ���ѳ�ʼ���Ķ������	*/
/*	������:	����ö���Ϊ��, ����1; ���򷵻�0	*/
int BQIsEmpty (const BinQueue bq) ;

/*	����:	�ϲ������������	*/
/*	����ǰ:	bq1, bq2 �������ѳ�ʼ���Ķ������	*/
/*	������:	����ϲ���Ķ�������ܹ��Ž� bq1, ���� bq1 �� bq2 ����ͬһ���������, ���غϲ�����µĶ���; ���򷵻�ԭ bq1	*/
BinQueue BQMerge (BinQueue bq1, BinQueue bq2) ;

/*	����:	���������в���Ԫ��	*/
/*	����ǰ:	bq ��һ���ѳ�ʼ���Ķ������, item ����Ԫ��	*/
/*	������:	����������δ��, �� item ��ӵ��ö�����, �����¶���; ���򷵻�ԭ����	*/
BinQueue BQInsert (BinQueue bq, const BQItem item) ;

/*	����:	ɾ��������һ��������е���СԪ��	*/
/*	����ǰ:	pbq ָ��һ���ѳ�ʼ���Ķ������	*/
/*	������:	����ö��в�Ϊ��, ɾ����������СԪ��; ���򷵻� -INFINITY	*/
BQItem BQDeleteMin (BinQueue bq) ;

/*	����:	��һ���������������ڶ�������е�����Ԫ��	*/
/*	����ǰ:	bq ��һ���ѳ�ʼ���Ķ������, pfun ָ��һ��û�з���ֵ, ����һ��Item���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ����������ڶ���������Ԫ��1��	*/
void BQTraversal (const BinQueue bq, void (* pfun) (const BQItem item)) ;

/*	����:	�ͷ�һ�����������ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	bq ��һ���ѳ�ʼ���Ķ������	*/
/*	������:	�ö�����ռ�õ��ڴ�ռ䱻���	*/
void BQRelease (const BinQueue bq) ;


ST_END_DECLS;

#endif	/* __ST_BINOMIAL_QUEUE_H__ */

