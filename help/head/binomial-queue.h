/*	binomial-queue.h -- 二项队列头文件	*/
/*	头文件加载放在头文件是个好主意	*/
#include <stdio.h>
#include <stdlib.h>
#define INFINITY 32767
/*	数据类型定义	*/

typedef int Item ;				//	为什么我如此喜欢 int ^ ^
typedef struct node
{
	Item item ;
	struct node * left ;		//	左子树
	struct node * nextsibling ;	//	左兄弟
} Node ;
typedef Node * SubTree ;
typedef struct binqueue
{
	SubTree * forest ;
	int size ;
	int current ;
} * BinQueue ;

/*	接口函数声明	*/

/*	操作:	初始化一个二项队列	*/
/*	操作前:	pbq 指向一个二项队列, size 指示其大小	*/
/*	操作后:	如果内存分配成功, 该 size 大小的二项队列被初始化为空, 返回1; 否则返回0	*/
int InitializeBinQueue (BinQueue * const pbq, const int size) ;

/*	操作:	确定一个二项队列是否为空	*/
/*	操作前:	bq 是一个已初始化的二项队列	*/
/*	操作后:	如果该队列为空, 返回1; 否则返回0	*/
int BinQueueIsEmpty (const BinQueue bq) ;

/*	操作:	合并两个二项队列	*/
/*	操作前:	bq1, bq2 是两个已初始化的二项队列	*/
/*	操作后:	如果合并后的二项队列能够放进 bq1, 并且 bq1 和 bq2 不是同一个二项队列, 返回合并后的新的队列; 否则返回原 bq1	*/
BinQueue Merge (BinQueue bq1, BinQueue bq2) ;

/*	操作:	向二项队列中插入元素	*/
/*	操作前:	bq 是一个已初始化的二项队列, item 是新元素	*/
/*	操作后:	如果二项队列未满, 将 item 添加到该队列中, 返回新队列; 否则返回原队列	*/
BinQueue Insert (BinQueue bq, const Item item) ;

/*	操作:	删除并返回一个二项队列的最小元素	*/
/*	操作前:	pbq 指向一个已初始化的二项队列	*/
/*	操作后:	如果该队列不为空, 删除并返回最小元素; 否则返回 -INFINITY	*/
Item DeleteMin (BinQueue bq) ;

/*	操作:	将一个函数依次作用于二项队列中的所有元素	*/
/*	操作前:	bq 是一个已初始化的二项队列, pfun 指向一个没有返回值, 接受一个Item类型参数的函数	*/
/*	操作后:	pfun 指向的函数被作用于队列中所有元素1次	*/
void Traversal (const BinQueue bq, void (* pfun) (const Item item)) ;

/*	操作:	释放一个二项队列所占用的内存空间	*/
/*	操作前:	bq 是一个已初始化的二项队列	*/
/*	操作后:	该队列所占用的内存空间被清空	*/
void Release (const BinQueue bq) ;
