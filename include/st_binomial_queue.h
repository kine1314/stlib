#ifndef	__ST_BINOMIAL_QUEUE_H__
#define	__ST_BINOMIAL_QUEUE_H__



/*	st_binomial_queue.h -- 二项队列头文件	*/
/*	头文件加载放在头文件是个好主意	*/
#include <stdio.h>
#include <stdlib.h>

#include "stlib.h"
ST_BEGIN_DECLS;



#define BQINFINITY 32767

/*	数据类型定义	*/

typedef long BQItem ;					//	为什么我如此喜欢 int ^ ^
typedef struct _BQNode
{
	BQItem item ;
	struct _BQNode * left ;				//	第一个儿子
	struct _BQNode * nextsibling ;		//	右兄弟
} BQNode ;

typedef BQNode * SubTree ;
typedef struct binqueue
{
	SubTree * forest ;					// 二项队列的森林
	int size ;
	int current ;
} * BinQueue ;

/*	接口函数声明	*/

/*	操作:	初始化一个二项队列	*/
/*	操作前:	pbq 指向一个二项队列, size 指示其大小	*/
/*	操作后:	如果内存分配成功, 该 size 大小的二项队列被初始化为空, 返回1; 否则返回0	*/
int BQInitialize (BinQueue * const pbq, const int size) ;

/*	操作:	确定一个二项队列是否为空	*/
/*	操作前:	bq 是一个已初始化的二项队列	*/
/*	操作后:	如果该队列为空, 返回1; 否则返回0	*/
int BQIsEmpty (const BinQueue bq) ;

/*	操作:	合并两个二项队列	*/
/*	操作前:	bq1, bq2 是两个已初始化的二项队列	*/
/*	操作后:	如果合并后的二项队列能够放进 bq1, 并且 bq1 和 bq2 不是同一个二项队列, 返回合并后的新的队列; 否则返回原 bq1	*/
BinQueue BQMerge (BinQueue bq1, BinQueue bq2) ;

/*	操作:	向二项队列中插入元素	*/
/*	操作前:	bq 是一个已初始化的二项队列, item 是新元素	*/
/*	操作后:	如果二项队列未满, 将 item 添加到该队列中, 返回新队列; 否则返回原队列	*/
BinQueue BQInsert (BinQueue bq, const BQItem item) ;

/*	操作:	删除并返回一个二项队列的最小元素	*/
/*	操作前:	pbq 指向一个已初始化的二项队列	*/
/*	操作后:	如果该队列不为空, 删除并返回最小元素; 否则返回 -INFINITY	*/
BQItem BQDeleteMin (BinQueue bq) ;

/*	操作:	将一个函数依次作用于二项队列中的所有元素	*/
/*	操作前:	bq 是一个已初始化的二项队列, pfun 指向一个没有返回值, 接受一个Item类型参数的函数	*/
/*	操作后:	pfun 指向的函数被作用于队列中所有元素1次	*/
void BQTraversal (const BinQueue bq, void (* pfun) (const BQItem item)) ;

/*	操作:	释放一个二项队列所占用的内存空间	*/
/*	操作前:	bq 是一个已初始化的二项队列	*/
/*	操作后:	该队列所占用的内存空间被清空	*/
void BQRelease (const BinQueue bq) ;


ST_END_DECLS;

#endif	/* __ST_BINOMIAL_QUEUE_H__ */

