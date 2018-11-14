#ifndef	__ST_SKEW_HEAP_H__
#define	__ST_SKEW_HEAP_H__

#include "stlib.h"

ST_BEGIN_DECLS ;

#define SHINSERT(heap, item) (heap = SHInsert (heap, item))
#define SHDELETEMIN(heap, pnode) (heap = SHDeleteMin (heap, pnode))
#define SHBUILD(heap, parray, size) (heap = SHBuild (parray, size))

/*	数据类型定义	*/

typedef int SHItem ;
typedef struct _SHNode
{
	SHItem item ;
	struct _SHNode * left ;
	struct _SHNode * right ;
} SHNode ;
typedef SHNode * SHeap ;

/*	接口函数声明	*/

/*	操作:	创建并将一个斜堆置为空	*/
/*	操作前:	pheap 指向一个斜堆	*/
/*	操作后:	如果内存分配成功, 该斜堆被初始为空, 返回1; 否则返回0	*/
int SHCreate (SHeap * const ph) ;

/*	操作:	确定一个斜堆是否为空	*/
/*	操作前:	h 是一个已初始化的斜堆	*/
/*	操作后:	如果该堆为空, 返回1; 否则返回0	*/
int SHIsEmpty (const SHeap h) ;

/*	操作:	合并两个斜堆并返回合并后的斜堆	*/
/*	操作前:	h1, h2 是两个已初始化的斜堆	*/
/*	操作后:	合并二者, 返回新堆	*/
SHeap SHMerge (const SHeap h1, const SHeap h2) ;

/*	操作:	向斜堆中插入一个节点	*/
/*	操作前:	h 是一个已初始化的斜堆, item 是新节点的数据	*/
/*	操作后:	将新节点插入到堆中, 返回新堆	*/
SHeap SHInsert (SHeap h, const SHItem item) ;

/*	操作:	删除斜堆中最小关键字的节点	*/
/*	操作前:	heap 是一个已初始化的斜堆, pnode 是承载最小关键字节点的指针变量	*/
/*	操作后:	如果堆不为空, 删除最小关键字的节点, 使 pnode 指向该节点, 返回新堆; 否则返回原堆	*/
SHeap SHDeleteMin (SHeap h, SHNode * const pnode) ;

/*	操作:	查找并返回指向斜堆中具有指定关键字节点的指针	*/
/*	操作前:	h 是一个已初始化的斜堆, item 指示被查找的关键字	*/
/*	操作后:	如果找到该节点, 返回指向该节点的指针; 否则返回NULL	*/
SHNode * SHFind (const SHeap h, const SHItem item) ;

/*	操作:	根据一个数据数组构建并返回一个斜堆堆	*/
/*	操作前:	array 是一个数据数组, size 指示数组的大小	*/
/*	操作后:	如果内存分配成功, 创建并返回该堆; 否则返回NULL	*/
SHeap SHBuild (const SHItem array[], const int size) ;

/*	操作:	清空一个斜堆所占内存空间	*/
/*	操作前:	h 是一个已初始化的斜堆	*/
/*	操作后:	该堆所占内存空间被释放	*/
void SHRelease (const SHeap h) ;



ST_END_DECLS ;
#endif	/* __ST_SKEW_HEAP_H__ */

