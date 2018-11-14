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
	STQueueNode_t * front, * rear ;			// 队列的头尾
	int current ;							// 队列的大小
} * PSTQueue ;


/*	接口函数声明	*/

/*	操作:	创建并初始化一个队列	*/
/*	操作前:	pq 指向一个队列	*/
/*	操作后:	如果内存分配成功, 创建并初始化该队列, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool STInitialize_Q (PSTQueue * const pq) ;

/*	操作:	确定一个队列是否为空	*/
/*	操作前:	pq 指向一个已初始化的队列	*/
/*	操作后:	如果该队列为空, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool STIsEmpty_Q (const PSTQueue * const pq) ;

/*	操作:	向队列中添加一个数据域为指定数据的结点	*/
/*	操作前:	pq 指向一个已初始化的队列, item 是指定待添加数据	*/
/*	操作后:	如果内存分配成功, 添加数据域为 item 的结点到队列中, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool STEnQueue_Q (const PSTQueue * const pq, const QItem item) ;

/*	操作:	从队列中删除头部结点, 释放其占用的内存空间, 并将其数据域赋予指定变量	*/
/*	操作前:	pq 指向一个已初始化的队列, messenger 是一个指向 QItem 的指针, 用于将数据携带回调用本函数的函数	*/
/*	操作后:	如果队列不为空, 删除头结点, 释放其占用的内存空间, 更新头结点, 并将其数据域赋予 *messenger	*/
/*	时间复杂度:	O (1)	*/
stbool STDeQueue_Q (const PSTQueue * const pq, QItem * const messenger) ;

/*	操作:	释放一个队列占用的内存空间	*/
/*	操作前:	pq 指向一个已初始化的队列	*/
/*	操作后:	该队列占用的内存空间被释放	*/
/*	时间复杂度:	O (N)	*/
void STRelease_Q (const PSTQueue * const pq) ;



ST_END_DECLS;
#endif	/* __ST_QUEUE_H__ */

