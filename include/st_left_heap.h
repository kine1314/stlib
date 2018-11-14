#ifndef	__ST_LEFT_HEAP_H__
#define	__ST_LEFT_HEAP_H__

#include "stlib.h"

ST_BEGIN_DECLS;

/* 
 * ����ָ��ȴ�����2���˳�����ʱ�䣬���Ҳ���нṹ�ԺͶ����ԣ�
 * ��ʽ��Ҳ�Ƕ�����������������Ψһ���������:��ʽ�Բ�������ƽ��ģ�
 * ��������ǳ���ƽ�⡣
 */
/* ��ʽ�ѵĹ����Ƿ����֧�ֺϲ����� */

/* ��ʽ�ѵ�����:1.����ڵ��nplҪ�������ӽڵ��npl����Сֵ��1��
 * 				2.���ڶ��е�ÿ���ڵ�X������ӵ�npl�������Ҷ��ӵ�nplһ����(>=)
 *				3.����·������r���ڵ����ʽ��������(2��r�η�-1)���ڵ�
 */

typedef int LeftHeadET ;

struct _LHNode;
typedef struct _LHNode * LHPriorityQueue;


/*	�ӿں�������	*/

/*	����:	��������ʼ��һ������ʽ��	*/
/*	����ǰ:	pheap ָ��һ����ʽ��	*/
/*	������:	����ڴ����ɹ�, ���� pheap ָ�����ʽ��, ������Ϊ�ն�, ����1; ���򷵻�0	*/
int CreateANullLHeap (LHPriorityQueue * const pheap) ;

/*	����:	ȷ��һ����ʽ���Ƿ�Ϊ��	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ���Ķ�	*/
/*	������:	����ö�Ϊ��, ����1; ���򷵻�0	*/
int LHIsEmpty (const LHPriorityQueue heap) ;

/*	����:	�ϲ�������ʽ�Ѳ������¶�	*/
/*	����ǰ:	h1, h2 �������ѳ�ʼ������ʽ��	*/
/*	������:	�����ѱ��ϲ����ұ�����	*/
LHPriorityQueue LHMerge (const LHPriorityQueue h1, const LHPriorityQueue h2) ;

/*	����:	��һ����������ӵ���ʽ����	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ���Ķ�, item ��ָ����������	*/
/*	������:	����ڴ����ɹ�, item ����ӵ�����, �����¶�; ���򷵻�ԭ��	*/
LHPriorityQueue LHInsert (LHPriorityQueue heap, const LeftHeadET item) ;

/*	����:	ɾ����ʽ���е���СԪ��	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ���Ķ�	*/
/*	������:	����Ѳ�Ϊ��, ɾ����СԪ��, �����¶�; ���򷵻�ԭ��	*/
LHPriorityQueue LHDeleteMin (const LHPriorityQueue heap) ;

/*	����:	���Ҳ�������ʽ���е�һ������ָ���ؼ��ֵĽڵ�	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ������ʽ��, item ��ָ���Ĺؼ���	*/
/*	������:	����ҵ�, ����ָ��ýڵ��ָ��; ���򷵻�NULL	*/
struct _LHNode * LHFind (const LHPriorityQueue heap, const LeftHeadET item);

/*	����:	����һ���������鹹��һ����ʽ��	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ���Ķ�, array ��һ����������, size �������С	*/
/*	������:	����ڴ����ɹ�, ���������� array ΪԪ�عؼ��ֵ���ʽ��, ���ظö�; ���򷵻�NULL	*/
LHPriorityQueue LHBulid (LHPriorityQueue heap, const LeftHeadET * array, const int size) ;

/*	����:	�������һ����ʽ��	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ������ʽ��	*/
/*	������:	��������ö�	*/
void LHLevelOrderTraversal (const LHPriorityQueue heap) ;

void LHDisplayOneHeap(struct _LHNode * node) ;


ST_END_DECLS ;
#endif	/* __ST_LEFT_HEAP_H__ */

