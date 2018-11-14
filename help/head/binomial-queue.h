/*	binomial-queue.h -- �������ͷ�ļ�	*/
/*	ͷ�ļ����ط���ͷ�ļ��Ǹ�������	*/
#include <stdio.h>
#include <stdlib.h>
#define INFINITY 32767
/*	�������Ͷ���	*/

typedef int Item ;				//	Ϊʲô�����ϲ�� int ^ ^
typedef struct node
{
	Item item ;
	struct node * left ;		//	������
	struct node * nextsibling ;	//	���ֵ�
} Node ;
typedef Node * SubTree ;
typedef struct binqueue
{
	SubTree * forest ;
	int size ;
	int current ;
} * BinQueue ;

/*	�ӿں�������	*/

/*	����:	��ʼ��һ���������	*/
/*	����ǰ:	pbq ָ��һ���������, size ָʾ���С	*/
/*	������:	����ڴ����ɹ�, �� size ��С�Ķ�����б���ʼ��Ϊ��, ����1; ���򷵻�0	*/
int InitializeBinQueue (BinQueue * const pbq, const int size) ;

/*	����:	ȷ��һ����������Ƿ�Ϊ��	*/
/*	����ǰ:	bq ��һ���ѳ�ʼ���Ķ������	*/
/*	������:	����ö���Ϊ��, ����1; ���򷵻�0	*/
int BinQueueIsEmpty (const BinQueue bq) ;

/*	����:	�ϲ������������	*/
/*	����ǰ:	bq1, bq2 �������ѳ�ʼ���Ķ������	*/
/*	������:	����ϲ���Ķ�������ܹ��Ž� bq1, ���� bq1 �� bq2 ����ͬһ���������, ���غϲ�����µĶ���; ���򷵻�ԭ bq1	*/
BinQueue Merge (BinQueue bq1, BinQueue bq2) ;

/*	����:	���������в���Ԫ��	*/
/*	����ǰ:	bq ��һ���ѳ�ʼ���Ķ������, item ����Ԫ��	*/
/*	������:	����������δ��, �� item ��ӵ��ö�����, �����¶���; ���򷵻�ԭ����	*/
BinQueue Insert (BinQueue bq, const Item item) ;

/*	����:	ɾ��������һ��������е���СԪ��	*/
/*	����ǰ:	pbq ָ��һ���ѳ�ʼ���Ķ������	*/
/*	������:	����ö��в�Ϊ��, ɾ����������СԪ��; ���򷵻� -INFINITY	*/
Item DeleteMin (BinQueue bq) ;

/*	����:	��һ���������������ڶ�������е�����Ԫ��	*/
/*	����ǰ:	bq ��һ���ѳ�ʼ���Ķ������, pfun ָ��һ��û�з���ֵ, ����һ��Item���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ����������ڶ���������Ԫ��1��	*/
void Traversal (const BinQueue bq, void (* pfun) (const Item item)) ;

/*	����:	�ͷ�һ�����������ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	bq ��һ���ѳ�ʼ���Ķ������	*/
/*	������:	�ö�����ռ�õ��ڴ�ռ䱻���	*/
void Release (const BinQueue bq) ;
