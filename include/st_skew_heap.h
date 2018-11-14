#ifndef	__ST_SKEW_HEAP_H__
#define	__ST_SKEW_HEAP_H__

#include "stlib.h"

ST_BEGIN_DECLS ;

#define SHINSERT(heap, item) (heap = SHInsert (heap, item))
#define SHDELETEMIN(heap, pnode) (heap = SHDeleteMin (heap, pnode))
#define SHBUILD(heap, parray, size) (heap = SHBuild (parray, size))

/*	�������Ͷ���	*/

typedef int SHItem ;
typedef struct _SHNode
{
	SHItem item ;
	struct _SHNode * left ;
	struct _SHNode * right ;
} SHNode ;
typedef SHNode * SHeap ;

/*	�ӿں�������	*/

/*	����:	��������һ��б����Ϊ��	*/
/*	����ǰ:	pheap ָ��һ��б��	*/
/*	������:	����ڴ����ɹ�, ��б�ѱ���ʼΪ��, ����1; ���򷵻�0	*/
int SHCreate (SHeap * const ph) ;

/*	����:	ȷ��һ��б���Ƿ�Ϊ��	*/
/*	����ǰ:	h ��һ���ѳ�ʼ����б��	*/
/*	������:	����ö�Ϊ��, ����1; ���򷵻�0	*/
int SHIsEmpty (const SHeap h) ;

/*	����:	�ϲ�����б�Ѳ����غϲ����б��	*/
/*	����ǰ:	h1, h2 �������ѳ�ʼ����б��	*/
/*	������:	�ϲ�����, �����¶�	*/
SHeap SHMerge (const SHeap h1, const SHeap h2) ;

/*	����:	��б���в���һ���ڵ�	*/
/*	����ǰ:	h ��һ���ѳ�ʼ����б��, item ���½ڵ������	*/
/*	������:	���½ڵ���뵽����, �����¶�	*/
SHeap SHInsert (SHeap h, const SHItem item) ;

/*	����:	ɾ��б������С�ؼ��ֵĽڵ�	*/
/*	����ǰ:	heap ��һ���ѳ�ʼ����б��, pnode �ǳ�����С�ؼ��ֽڵ��ָ�����	*/
/*	������:	����Ѳ�Ϊ��, ɾ����С�ؼ��ֵĽڵ�, ʹ pnode ָ��ýڵ�, �����¶�; ���򷵻�ԭ��	*/
SHeap SHDeleteMin (SHeap h, SHNode * const pnode) ;

/*	����:	���Ҳ�����ָ��б���о���ָ���ؼ��ֽڵ��ָ��	*/
/*	����ǰ:	h ��һ���ѳ�ʼ����б��, item ָʾ�����ҵĹؼ���	*/
/*	������:	����ҵ��ýڵ�, ����ָ��ýڵ��ָ��; ���򷵻�NULL	*/
SHNode * SHFind (const SHeap h, const SHItem item) ;

/*	����:	����һ���������鹹��������һ��б�Ѷ�	*/
/*	����ǰ:	array ��һ����������, size ָʾ����Ĵ�С	*/
/*	������:	����ڴ����ɹ�, ���������ظö�; ���򷵻�NULL	*/
SHeap SHBuild (const SHItem array[], const int size) ;

/*	����:	���һ��б����ռ�ڴ�ռ�	*/
/*	����ǰ:	h ��һ���ѳ�ʼ����б��	*/
/*	������:	�ö���ռ�ڴ�ռ䱻�ͷ�	*/
void SHRelease (const SHeap h) ;



ST_END_DECLS ;
#endif	/* __ST_SKEW_HEAP_H__ */

