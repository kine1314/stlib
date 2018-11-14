#ifndef	__ST_BINHEAP_H__
#define	__ST_BINHEAP_H__

#include "stlib.h"
#include "st_type.h"

ST_BEGIN_DECLS;

/* 二叉堆是棵完全二叉树，基于这种规律，所以使用数组比描述，
 * 对于数组上任意位置i上的元素，其左儿子在位置2i上，右儿子
 * 在2i+1上，他得父亲则在[i/2]上。缺点就是堆得大小要事先定义；
 * 大小排序是从上倒下左到有排序；任意节点都应小于其左右后裔；
 */


struct STBinHeap_s;
typedef struct STBinHeap_s *BHPriorityQueue;

/*	操作:	初始化一个二叉堆	*/
/*	操作前:	size 是指定二叉堆的大小的变量	*/
/*	操作后:	该表被创建并且表中的所有表元指针被初始化为空, 返回该表	*/
/*	时间复杂度:	O (1)	*/
BHPriorityQueue BHInitialize( int MaxElements );

/*	操作:	销毁二叉堆	*/
/*	操作前:	H 指向一个已初始化的表	*/
/*	操作后:	该表所占用的全部内存空间被释放	*/
/*	时间复杂度:	O (1)	*/
void BHDestroy( BHPriorityQueue H );

/*	操作:	清空二叉堆	*/
/*	操作前:	H 指向一个已初始化的表	*/
/*	操作后:	表的size为0	*/
/*	时间复杂度:	O (1)	*/
void BHMakeEmpty( BHPriorityQueue H );

/*	操作:	向一个优先队列中插入一个结点	*/
/*	操作前:	H 指向一个已初始化的优先队列, pn 是待添加到队列中的结点	*/
/*	操作后:	如果该优先队列未满, 向该优先队列中添加 X , 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)，二分查找	*/
stbool BHInsert( BinHeadET X, BHPriorityQueue H );

/*	操作:	判断二叉堆是否为空	*/
/*	操作前:	H 指向一个已初始化的表	*/
/*	操作后:	返回是否满	*/
/*	时间复杂度:	O (1)	*/
stbool BHIsFull( BHPriorityQueue H );

/*	操作:	删除并返回优先队列中数据域最小的结点	*/
/*	操作前:	H 指向一个已初始化的优先队列	*/
/*	操作后:	如果该优先队列不为空, 删除并返回数据域最小的结点; 否则返回 NULL	*/
/*	时间复杂度:	O (log N),二分查找	*/
BinHeadET BHDeleteMin( BHPriorityQueue H );

/*	操作:	获取优先队列中的最小值	*/
/*	操作前:	H 指向一个已初始化的优先队列	*/
/*	操作后:	如果该优先队列不为空, 返回队列的第一个节点	*/
/*	时间复杂度:	O (1)	*/
BinHeadET BHFindMin( BHPriorityQueue H );

/*	操作:	确定一个优先队列是否为空	*/
/*	操作前:	H 指向一个已初始化的优先队列	*/
/*	操作后:	如果该优先队列为空, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool BHIsEmpty( BHPriorityQueue H );

/*	操作:	确定一个优先队列是否已满	*/
/*	操作前:	H 指向一个已初始化的优先队列	*/
/*	操作后:	如果该优先队列已满, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool BHIsFull( BHPriorityQueue H );

/*	操作:	增加优先队列中指定位置的结点的数据指定值	*/
/*	操作前:	ppq 指向一个已初始化的优先队列, position 指定位置, delta 是改变量	*/
/*	操作前:	如果 position 为有效位置 && delta > 0, 将优先队列中 position 位置的结点的数据增加 delta , 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool BHIncreaseKey_P (const BHPriorityQueue const ppq, const int position, const int delta) ;

/*	操作:	减少优先队列中指定位置结点的数据指定值	*/
/*	操作前:	ppq 指向一个已初始化的优先队列, position 指定位置, delta 是改变量	*/
/*	操作后:	如果 position 是有效位置 && delta > 0, 将优先队列中 position 位置的结点的数据减少 delta , 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool DecreaseKey_P (const BHPriorityQueue const ppq, const int position, const int delta) ;

stbool BHDisplayHead(BHPriorityQueue H);

ST_END_DECLS ;
#endif	/* __ST_BINHEAP_H__ */

