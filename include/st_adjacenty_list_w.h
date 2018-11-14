#ifndef	__ST_ADJACENTY_LIST_W_H__
#define	__ST_ADJACENTY_LIST_W_H__

#include "stlib.h"

ST_BEGIN_DECLS ;

/*	st_adjacenty_list_w.h -- 存储带权图邻接表头文件	*/

#include <stdarg.h>

#include "st_graph_common.h"

#define INFINITY (~(1 << 31))
#define NEGATIVEINFINITY (-INFINITY - 1)

/*	数据类型定义	*/
typedef char ADJLWName ;
typedef struct adjoin_to_vertex
{
	int hash_value ;
	int cvw ;
	struct adjoin_to_vertex * next ;
} Adjoin_To_Vertex ;
typedef struct vertex_w
{
	int hash_value ;
	int known ;
	int dist ;
	int weight ;
	ADJLWName path ;
	Adjoin_To_Vertex * adjoin_to ;
} Vertex_w ;
typedef struct adjacenty_list_w
{
	Vertex_w * list ;
	int * indegree ;
	int capacity ;
} * Adjacenty_List_w ;

/*	接口函数声明	*/

/*	操作:	创建一个邻接表	*/
/*	操作前:	padj 指向一个邻接表, capacity 指示邻接表的大小	*/
/*	操作后:	如果 capacity > 0 && 内存分配成功, 创建该邻接表, 返回 1; 否则返回 0	*/
/*	时间复杂度:	O(1)	*/
int Initialize_A_W (Adjacenty_List_w * const padj, const int capacity) ;

/*	操作:	初始化邻接表的某一行	*/
/*	操作前:	padj 指向一个已初始化的邻接表, pht 指向一个已初始化的散列表, index 指示行的索引, name 指示顶点名字, indegree 指示顶点入度, sub 指示参数的个数, ... 交替出现指示邻接到该顶点的顶点名字和顶点到该顶点构成的边的权	*/
/*	操作后:	如果 index 是合法的索引 && indegree >= 0 && sub >= 0, 该行被按照参数初始化, 返回 1; 否则返回 0	*/
/*	时间复杂度:	O(V)	*/
int InitializeALine_A_W (Adjacenty_List_w * const padj, const struct Ghash_table ** const pht, const int index, const ADJLWName name, const int indegree, const int sub, ...) ;

/*	操作:	打印一个邻接表	*/
/*	操作前:	padj 指向一个已初始化的邻接表, pht 指向一个已初始化的散列表	*/
/*	操作后:	该邻接表被打印	*/
/*	时间复杂度:	O (V)	*/
void PrintAdjacenty_List_A_W (const Adjacenty_List_w * const padj, const struct Ghash_table ** const pht) ;

/*	操作:	释放一个邻接表所占用的内存空间	*/
/*	操作前:	padj 指向一个已初始化的邻接表	*/
/*	操作后:	该邻接表所占用的内存空间被释放	*/
/*	时间复杂度:	O(V)	*/
void Release_A_W (const Adjacenty_List_w * const padj) ;

/* 反转一个邻接表 */
int Reverse_A_W (Adjacenty_List_w * const padj, const struct Ghash_table ** const pht);

/*	操作:	对邻接表找出有权图的最短路径	*/
/*	操作前:	padj 指向一个已创建的邻接表	*/
/*	操作后:	初始化邻接表中的个点的最短路径	*/
/*	时间复杂度:	O(V * V)	*/
int dijkstra (const Adjacenty_List_w * padj, const struct Ghash_table ** const pht, const int start);

/*	操作:	对邻接表找出有权图的最短路径,得到最短路径的个数，并输出边数最小的一条最短路径	*/
/*	操作前:	padj 指向一个已创建的邻接表	*/
/*	操作后:	初始化邻接表中的个点的最短路径	*/
/*	时间复杂度:	O(V * V)	*/
int new_dijkstra (const Adjacenty_List_w * padj, const struct Ghash_table ** const pht, const int start);

/* 找出最小生成树 */
int prim (const Adjacenty_List_w * padj, const struct Ghash_table ** const pht, const int start);

/* 贪婪地求最小生成树 */
void kruskal (const Adjacenty_List_w * const padj, const struct Ghash_table ** const pht, const int start, char (* const result)[2], int * const weight);

/* 找图的关节点 */
void find_art (const Adjacenty_List_w * const padj, const struct Ghash_table ** const pht, const int v);


ST_END_DECLS;
#endif	/* __ST_ADJACENTY_LIST_W_H__ */
