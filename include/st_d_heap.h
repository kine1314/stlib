#ifndef	__ST_D_HEAP_H__
#define	__ST_D_HEAP_H__

#include "stlib.h"

ST_BEGIN_DECLS ;

/*	st_d_heap.h -- d-��ͷ�ļ�	*/
#define DHMINDATA 			-32678



/*	�������Ͷ���	*/

typedef int DHItem ;
typedef struct _DHeap
{
	DHItem * array ;
	int capacity ;
	int size ;
	int d ;
} * DHeap ;

/*	�ӿں�������	*/

/*	����:	��������ʼ��һ��d-��	*/
/*	����ǰ:	pheap ָ��һ��d-��, capacity ������ָʾ�������ı���, d �����нڵ������ӵ�����	*/
/*	������:	����ڴ����ɹ�, һ������Ϊ capacity �Ķѱ�����������ʼΪ��, ���ж�������������Ϊ d , ����1; ���򷵻�0	*/
int DHInitialize (DHeap * const pheap, const int capacity, const int d) ;

/*	����:	ȷ��һ�����Ƿ�Ϊ��	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ����d-��	*/
/*	������:	����ö�Ϊ��, ����1; ���򷵻�0	*/
int DHIsEmpty (const DHeap * const pheap) ;

/*	����:	ȷ��һ�����Ƿ�����	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ����d-��	*/
/*	������:	����ö�����, ����1; ���򷵻�0	*/
int DHIsFull (const DHeap * const pheap) ;

/*	����:	��d-�������һ��Ԫ��	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ����d-��, item �Ǵ���ӵ�����	*/
/*	������:	�����δ��, �� item ��ӵ�����, ����1; ���򷵻�0	*/
int DHInsert (const DHeap * const pheap, const DHItem item) ;

/*	����:	ɾ�������ض�����С��Ԫ��	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ����d-��	*/
/*	������:	����Ѳ�Ϊ��, ɾ�������ض��е���СԪ��; ���򷵻�MINDATA	*/
DHItem DHDeleteMin (const DHeap * const pheap) ;

/*	����:	���Ͷ���ָ��λ�ô�Ԫ�ص�ֵ	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ����d-��, position ָʾ���е�λ��, triangle �Ǹı���	*/
/*	������:	��� position �ڶ��е�λ�ô���, triangle > 0, ��λ���ϵ�Ԫ�ر����� triangle, ����1; ���򷵻�0	*/
int DHDecreaseKey (const DHeap * const pheap, const int position, const int triangle) ;

/*	����:	���Ӷ���ָ��λ�ô�Ԫ�ص�ֵ	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ����d-��, position ָʾ���е�λ��, triangle �Ǹı���	*/
/*	������:	��� position �ڶ��е�λ�ô���, traingle > 0, ��λ���ϵ�Ԫ�ر����� traingle, ����1; ���򷵻�0	*/
int DHIncreaseKey (const DHeap * const pheap, const int position, const int triangle) ;

/*	����:	����һ���������鹹��һ��d-��	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ����d-��, array ��һ��ָ������������Ԫ�ص�ָ��, size �������С	*/
/*	������:	�����Ϊ��, �����С>0, �����ö�, ����1; ���򷵻�0	*/
int DHBuild (const DHeap * const pheap, const DHItem * parray, const int size) ;

/*	����:	ɾ��d-����ָ��λ�õ�Ԫ��	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ����d-��, position ָʾ���е�λ��	*/
/*	������:	������� position λ�ô���, ��λ�ô���Ԫ�ر�ɾ��, ����1; ���򷵻�0	*/
int DHDelete (const DHeap * const pheap, const int position) ;

/*	����:	������1 - size ���ν�һ������������d-��������Ԫ��1��	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ���Ķ�, pfun ָ��һ��û�з���ֵ, ����һ��Item���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ������������õ���������Ԫ��1��	*/
void DHTraversal (const DHeap * const pheap, void (* pfun) (const DHItem item)) ;

/*	����:	�ͷ�һ��d-��ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	pheap ָ��һ���ѳ�ʼ���Ķ�	*/
/*	������: �ö�ռ�õ��ڴ�ռ䱻�ͷ�	*/
void DHRelease (const DHeap * const pheap) ;
















ST_END_DECLS ;
#endif	/* __ST_D_HEAP_H__ */

