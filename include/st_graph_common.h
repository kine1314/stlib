#ifndef	__ST_GRAPH_H__
#define	__ST_GRAPH_H__

#include "stlib.h"
#include "st_hash_common.h"
#include "st_adjacenty_list.h"
#include "st_adjacenty_list_w.h"

ST_BEGIN_DECLS ;
/*
 * 图的相关概念:
 *	1.图G的顶点数n和边数e的关系,
 *	（1）若G是无向图，则0≤e≤n(n-1)/2,恰有n(n-1)/2条边的无向图称无向完全图(Undireet-ed Complete Graph)
 *	（2）若G是有向图，则0≤e≤n(n-1)。恰有n(n-1)条边的有向图称为有向完全图(Directed Complete Graph)。	
 *	（3）完全图具有最多的边数。任意一对顶点间均有边相连。
 *		完全图(complete graph)：
 *		完全无向图：
 *	　　有n个顶点无向图，若有n(n-1)/2条边，
 *		完全有向图：
 *	　　有n个顶点有向图，若有n(n-1)条边，
 *	（4）对于有向图来说，图中任意一对顶点 v i 和 v j (i ≠ j) 均有从 v i 到 v j 及从 v j 到 v i 的有向路径，则称该有向图是强连通的。
 *		若从顶点 v i 到顶点 v j (i ≠ j) 有路径，则 v i 和 v j 是连通的。
 *	2.1图的邻接矩阵表示法
    　在图的邻接矩阵表示法中：① 用邻接矩阵表示顶点间的相邻关系 ② 用一个顺序表来存储顶点信息
    2．2图的邻接矩阵(Adacency Matrix)
    　设G=(V，E)是具有n个顶点的图，则G的邻接矩阵是具有如下性质的n阶方阵：A[n,n]:1表示是G的边，0表示不是G的边；
     从图的邻接矩阵表示法中可以得到如下结论： 　　
	（1）对于n个顶点的无向图，有A（i，i）=0，1≤i≤n。
　　（2）无向图的邻接矩阵是对称的，即A（i，j）=A（j，i），1≤i≤n，1≤j≤n。
　　（3）有向图的邻接矩阵不一定对称的。因此用邻接矩阵来表示一个具有n个顶点的有向图时需要n2个单位来存储邻接矩阵；对有n个顶点的无向图则需存入上（下）三角形，故只需n（n+1）/2个单位。
　　（4）无向图的邻接矩阵的第i行（或第i列）非零元素的个数正好是第i个顶点的度TD（vi）。
　　（5）有向图的邻接矩阵的第i行（或第i列）非零元素的个数正好是第i个顶点的出度OD（vi）[或入度ID（vi）]。
	3．网（带权值的图）的邻接矩阵若G是网络，则邻接矩阵可定义为：其中：wij表示边上的权值；∞表示一个计算机允许的、大于所有边上权值的数。
	4.图的遍历算法设计需要考虑3个问题：
	  （1）图的特点没有首尾之分，所以算法的参考要指定访问的第一个顶点。
	  （2）对图的遍历路径有可能构成一个回路，从而造成死循环，所以算法设计要考虑遍历路径可能的回路问题。
	  （3）一个顶点可能和若干个顶点都是想邻顶点，要使一个顶点的所有想邻顶点按照某种次序被访问。
	　　对于连通图，从初始顶点出发一定存在路径和图中的所有其他顶点相连，所以对于连通图从初始顶点出发一定可以遍历该图。
		1.连通图的深度优先遍历算法思想。
		（1）访问初始顶点v并标记顶点v已访问。
		（2）查找顶点v的第一个邻接顶点w。
		（3）若顶点v的邻接顶点w存在，则继续执行；否则回溯到v，再找v的另外一个未访问过的邻接点。
		（4）若顶点w尚未被访问，则访问顶点w并标记顶点w为已访问。
		（5）继续查找顶点w的下一个邻接顶点wi，如果v取值wi转到步骤（3）。直到连通图中所有顶点全部访问过为止。
		1.连通图的广度优先遍历算法思想。
		（1）顶点v入队列。
		（2）当队列非空时则继续执行，否则算法结束。
		（3）出队列取得队头顶点v；访问顶点v并标记顶点v已被访问。
		（4）查找顶点v的第一个邻接顶点col。
		（5）若v的邻接顶点col未被访问过的，则col入队列。
		（6）继续查找顶点v的另一个新的邻接顶点col，转到步骤（5）。直到顶点v的所有未被访问过的邻接点处理完。转到步骤（2）。
 */

//栈ADT实现
/*	数据类型定义	*/

typedef char GSName ;
typedef struct Gstack_node
{
	GSName name ;
	struct Gstack_node * next ;
} GStack_Node ;
typedef GStack_Node * GStack ;

/*	接口函数声明	*/

/*	操作:	初始化一个栈	*/
/*	操作前:	pstack 指向一个栈	*/
/*	操作后:	如果内存分配成功, 该栈被初始化并被置为空, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int InitializeGStack (GStack * const pstack) ;

/*	操作:	确定一个栈是否为空	*/
/*	操作前:	pstack 指向一个已初始化的栈	*/
/*	操作后:	如果栈为空, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int GStackIsEmpty (const GStack * const pstack) ;

/*	操作:	将一个元素入栈	*/
/*	操作前:	pstack 指向一个已初始化的栈, panme 指向入栈的元素的数据	*/
/*	操作后:	如果内存分配成功, 元素数据域为 *pname 的元素入栈, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int GSPush (GStack * const pstack, const GSName * const pname) ;

/*	操作:	从栈中弹出一个元素	*/
/*	操作前:	pstack 指向一个已初始化的栈, pname 指向一个元素数据域的数据	*/
/*	操作后:	如果栈不为空, 栈顶元素出栈并且 *panme 被赋值, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int GSPop (GStack * const pstack, GSName * const pname) ;

/*	操作:	将一个函数从栈顶到栈底依次作用于栈中所有元素1次	*/
/*	操作前:	pstack 指向一个已初始化的栈, pfun 指向一个没有返回值, 接受一个Stack_Node类型参数的函数	*/
/*	操作后:	pfun 指向的函数被作用于栈中所有元素1次	*/
/*	时间复杂度:	O(N)	*/
void GSTraversal (const GStack * const pstack, void (* pfun) (const GStack_Node * const pstack_node)) ;

/*	操作:	释放一个栈所用的内存空间	*/
/*	操作前:	pstack 指向一个已初始化的栈	*/
/*	操作后:	该栈所占用的内存空间被释放	*/
/*	时间复杂度:	O(N)	*/
void ReleaseGStack (const GStack * const pstack) ;

// 队列ADT的实现
/*	数据类型定义	*/
typedef struct vertex * GQueue_Item ;

typedef struct Gqueue_node
{
	GQueue_Item queue_item ;
	struct Gqueue_node * next ;
} GQueue_Node ;

typedef struct queue
{
	GQueue_Node * front ;
	GQueue_Node * rear ;
} * GQueue ;

/*	接口函数声明	*/

/*	操作:	创建并初始化一个队列	*/
/*	操作前:	pqueue 指向一个队列	*/
/*	操作后:	如果内存分配成功, 队列被创建并被初始化为空, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int InitializeGQueue (GQueue * const pqueue) ;

/*	操作:	确定一个队列是否为空	*/
/*	操作前:	pqueue 指向一个已初始化的队列	*/
/*	操作后:	如果该队列为空, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int GQueueIsEmpty (const GQueue * const pqueue) ;

/*	操作:	向队列中添加数据域为指定数据的元素	*/
/*	操作前:	pqueue 指向一个已初始化的队列, pqueue_item 指向被添加的数据	*/
/*	操作后:	如果内存分配成功, 数据域为 *pqueue_item 的元素被添加到队列中, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int EnGQueue (GQueue * const pqueue, const GQueue_Item * const pqueue_item) ;

/*	操作:	从队列中删除一个元素	*/
/*	操作前:	pqueue 指向一个已初始化的队列, pqueue_item 是一个Queue_Item *类型的变量	*/
/*	操作后:	如果队列不为空, 从队列中删除一个元素, 并将该元素的数据赋予 *pqueue_item 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int DeGQueue (GQueue * const pqueue, GQueue_Item * const pqueue_item) ;

/*	操作:	释放一个队列所占用的内存空间	*/
/*	操作前:	pqueue 指向一个已初始化的队列	*/
/*	操作后:	该队列所占用的内存空间被释放	*/
/*	时间复杂度:	O(N)	*/
void ReleaseGQueue (GQueue * const pqueue) ;


// 临时配合邻接表使用的hash表
/*	数据类型定义	*/

typedef char GHName ;
typedef struct GHcell
{
	GHName name ;
	int be_deleted ;		//	在优先队列中是否是已删除过的
	enum KindOfEntry entry ;
	int index_in_adjacenty_list ;
} GHCell ;
typedef struct Ghash_table
{
	GHCell * lists ;
	int current ;
	int capacity ;
} * GHash_Table ;

/*	接口函数声明	*/

/*	操作:	根据一个数据产生一个数值并返回	*/
/*	操作前:	pht 指向一个已初始化的散列表, pname 指向一个数据	*/
/*	操作后:	根据该数据产生一个数值并返回	*/
/*	时间复杂度:	O(1)	*/
int GHash (const GHash_Table * const pht, const GHName * const pname) ;

/*	操作:	创建并初始化一个散列表	*/
/*	操作前:	pht 指向一个散列表, capacity 是指示表大小的数据	*/
/*	操作后:	如果 capacity > 0 && 内存分配成功, 该散列表被创建为 >= capacity 最小素数大小并初始化为空, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int Initialize_GH (GHash_Table * const pht, const int capacity) ;

/*	操作:	查找并返回一个指向数据在散列表中的位置的指针	*/
/*	操作前:	pht 指向一个已初始化的散列表, pname 指向被查找的数据	*/
/*	操作后:	如果找到数据域为 *pname 的元素, 返回指向该元素的指针; 否则返回指向查找结束时停止在散列表元素的指针	*/
/*	时间复杂度: O(N)	*/
GHCell * Find_GH (const GHash_Table * const pht, const GHName * const pname) ;

/*	操作:	向散列表中添加一个元素并返回在散列表中的索引	*/
/*	操作前:	pht 指向一个已初始化的散列表, pname 是指向名字的指针, index 是元素在邻接表中的索引	*/
/*	操作后:	如果表当前大小 <= 表大小的一半, 添加该元素, 返回当前索引; 否则返回 FAILED	*/
/*	时间复杂度: O(N)	*/
int Insert_GH (const GHash_Table * const pht, const GHName * const pname, const int index) ;

/*	操作:	从散列表中懒惰删除数据域为指定数据的元素	*/
/*	操作前:	pht 指向一个已初始化的散列表, pname 是指向名字的指针	*/
/*	操作后:	如果找到该元素, 对其进行懒惰删除, 返回 1 ; 否则返回 0	*/
/*	时间复杂度:	O(N)	*/
int Delete_GH (const GHash_Table * const pht, const GHName * const pname) ;

/*	操作:	释放一个散列表所占用的内存空间	*/
/*	操作前:	pht 指向一个已初始化的散列表	*/
/*	操作后:	该散列表所占内存空间被释放	*/
/*	时间复杂度:	O(1)	*/
void Release_GH (const GHash_Table * const pht) ;

// 配合dijkstra实现的二叉堆
/*	数据类型定义	*/

typedef struct vertex_w* GHeap_Item ;
typedef struct Gbinary_heap
{
	GHeap_Item * heap ;
	int capacity ;
	int current ;
} * GBinary_Heap ;

/*	接口函数声明	*/

/*	操作:	创建并初始化一个二叉堆	*/
/*	操作前:	pbh 指向一个二叉堆, capacity 指示该堆的大小	*/
/*	操作后:	如果 capacity > 0 && 内存分配成功, 创建该堆, 返回 1 ; 否则返回 0	*/
/*	时间复杂度: O(1)	*/
int Initialize_GB (GBinary_Heap * const pbh, const int capacity) ;

/*	操作:	向堆中添加一个数据域为指定数据的元素	*/
/*	操作前:	pbh 指向一个已初始化的二叉堆, hi 是待添加的指定数据	*/
/*	操作后:	如果堆未满, 向二叉堆中添加新元素, 返回 1 ; 否则返回 0	*/
/*	时间复杂度: O (log N)	*/
int Insert_GB (const GBinary_Heap * const pbh, const GHeap_Item hi) ;

/*	操作:	删除并返回堆中最小的元素	*/
/*	操作前:	pbh 指向一个已初始化的二叉堆	*/
/*	操作后:	如果堆未空, 删除堆中最小元素并返回; 否则返回堆中的哑元素	*/
/*	时间复杂度:	O (log N)	*/
GHeap_Item DeleteMin_GB (const GBinary_Heap * const pbh) ;

/*	操作:	将堆中指定元素的 dist 域的值增加 Δ	*/
/*	操作前:	phb 指向一个已初始化的二叉堆, index 指示指定元素的索引, triangle 指示Δ的大小	*/
/*	操作后:	如果堆不为空 && index 是合法的索引 && Δ >= 0, 堆中索引为 index 的元素的 dist 域被增加 Δ, 返回 1 ; 否则返回 0	*/
/*	时间复杂度:	O (log N)	*/
int IncreaseKey_GB (const GBinary_Heap * const pbh, const int index, const int triangle) ;

/*	操作:	将堆中指定元素的 dist 域值减少 Δ	*/
/*	操作前:	pbh 指向一个一初始化的二叉堆, index 指示指定元素的索引, triangle 指示Δ的大小	*/
/*	操作后:	如果堆不为空 && index 是合法的索引 && Δ >= 0, 堆中索引为 index 的元素的 dist 域被减少 Δ, 返回 1 ; 否则返回 0	*/
/*	时间复杂度:	O (log N)	*/
int DecreaseKey_GB (const GBinary_Heap * const pbh, const int index, const int triangle) ;

/*	操作:	释放一个二叉堆所占用的内存空间	*/
/*	操作前:	pbh 指向一个已初始化的二叉堆	*/
/*	操作后:	该堆所占用的内存空间被释放	*/
/*	时间复杂度:	O (1)	*/
void Release_GB (const GBinary_Heap * const pbh) ;


// 二叉堆 for kruskal算法
/*	数据类型定义	*/

typedef struct edge_kruskal
{
	int v_hash_value ;
	int w_hash_value ;
	int weight ;
} Edge_kruskal ;
typedef struct binary_heap_kruskal
{
	Edge_kruskal * heap ;
	int capacity ;
	int current ;
} * Binary_Heap_kruskal ;

/*	接口函数声明	*/

/*	操作:	创建并初始化一个二叉堆	*/
/*	操作前:	pbh 指向一个二叉堆, capacity 指示该堆的大小	*/
/*	操作后:	如果 capacity > 0 && 内存分配成功, 创建该堆, 返回 1 ; 否则返回 0	*/
/*	时间复杂度: O(1)	*/
int Initialize_B_kruskal (Binary_Heap_kruskal * const pbh, const int capacity) ;

/*	操作:	向堆中添加一个数据域为指定数据的元素	*/
/*	操作前:	pbh 指向一个已初始化的二叉堆, pd 指向待添加的边	*/
/*	操作后:	如果堆未满, 向二叉堆中添加新元素, 返回 1 ; 否则返回 0	*/
/*	时间复杂度: O (log N)	*/
int Insert_B_kruskal (const Binary_Heap_kruskal * const pbh, const Edge_kruskal * const pd) ;

/*	操作:	删除堆中的 weight 域最小的元素	*/
/*	操作前:	pbh 指向一个已初始化的二叉堆, pd 是指向存放数据的指针	*/
/*	操作后:	如果堆未空, 删除最小元素, 将其值赋予 pd 指向的数据, 返回 1 ; 否则返回 0	*/
/*	时间复杂度:	O (log N)	*/
int DeleteMin_B_kruskal (const Binary_Heap_kruskal * const pbh, Edge_kruskal * const pd) ;

/*	操作:	释放一个堆所占用的内存空间	*/
/*	操作前:	pbh 指向一个已初始化的二叉堆	*/
/*	操作后:	该堆所占用的内存空间被释放	*/
/*	时间复杂度:	O (1)	*/
void Release_B_kruskal (const Binary_Heap_kruskal * const pbh) ;


ST_END_DECLS ;
#endif	/* __ST_GRAPH_H__ */

