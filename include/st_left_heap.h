#ifndef	__ST_LEFT_HEAP_H__
#define	__ST_LEFT_HEAP_H__

#include "stlib.h"

ST_BEGIN_DECLS;

/* 
 * 处理指针比处理用2做乘除更耗时间，左堆也具有结构性和堆序性，
 * 左式堆也是二叉树，跟二叉树数唯一的区别就是:左式对不是理想平衡的，
 * 而是趋向非常不平衡。
 */
/* 左式堆的功能是方便地支持合并操作 */

/* 左式堆的特性:1.任意节点的npl要比诸多儿子节点的npl的最小值多1。
 * 				2.对于堆中的每个节点X，左儿子的npl至少与右儿子的npl一样大即(>=)
 *				3.在右路径上有r个节点的左式堆至少有(2的r次方-1)个节点
 */

typedef int LeftHeadET ;

struct _LHNode;
typedef struct _LHNode * LHPriorityQueue;


/*	接口函数声明	*/

/*	操作:	创建并初始化一个空左式堆	*/
/*	操作前:	pheap 指向一个左式堆	*/
/*	操作后:	如果内存分配成功, 创建 pheap 指向的左式堆, 将其置为空堆, 返回1; 否则返回0	*/
int CreateANullLHeap (LHPriorityQueue * const pheap) ;

/*	操作:	确定一个左式堆是否为空	*/
/*	操作前:	heap 是一个已初始化的堆	*/
/*	操作后:	如果该堆为空, 返回1; 否则返回0	*/
int LHIsEmpty (const LHPriorityQueue heap) ;

/*	操作:	合并两个左式堆并返回新堆	*/
/*	操作前:	h1, h2 是两个已初始化的左式堆	*/
/*	操作后:	两个堆被合并并且被返回	*/
LHPriorityQueue LHMerge (const LHPriorityQueue h1, const LHPriorityQueue h2) ;

/*	操作:	将一个新数据添加到左式堆中	*/
/*	操作前:	heap 是一个已初始化的堆, item 是指定的新数据	*/
/*	操作后:	如果内存分配成功, item 被添加到堆中, 返回新堆; 否则返回原堆	*/
LHPriorityQueue LHInsert (LHPriorityQueue heap, const LeftHeadET item) ;

/*	操作:	删除左式堆中的最小元素	*/
/*	操作前:	heap 是一个已初始化的堆	*/
/*	操作后:	如果堆不为空, 删除最小元素, 返回新堆; 否则返回原堆	*/
LHPriorityQueue LHDeleteMin (const LHPriorityQueue heap) ;

/*	操作:	查找并返回左式堆中的一个具有指定关键字的节点	*/
/*	操作前:	heap 是一个已初始化的左式堆, item 是指定的关键字	*/
/*	操作后:	如果找到, 返回指向该节点的指针; 否则返回NULL	*/
struct _LHNode * LHFind (const LHPriorityQueue heap, const LeftHeadET item);

/*	操作:	根据一个数据数组构建一个左式堆	*/
/*	操作前:	heap 是一个已初始化的堆, array 是一个数据数组, size 是数组大小	*/
/*	操作后:	如果内存分配成功, 构建以数组 array 为元素关键字的左式堆, 返回该堆; 否则返回NULL	*/
LHPriorityQueue LHBulid (LHPriorityQueue heap, const LeftHeadET * array, const int size) ;

/*	操作:	层序遍历一个左式堆	*/
/*	操作前:	heap 是一个已初始化的左式堆	*/
/*	操作后:	层序遍历该堆	*/
void LHLevelOrderTraversal (const LHPriorityQueue heap) ;

void LHDisplayOneHeap(struct _LHNode * node) ;


ST_END_DECLS ;
#endif	/* __ST_LEFT_HEAP_H__ */

