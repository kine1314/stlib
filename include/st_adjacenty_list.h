#ifndef	__ST_ADJACENTY_LIST_H__
#define	__ST_ADJACENTY_LIST_H__

#include "stlib.h"

ST_BEGIN_DECLS ;

/*	st_adjacenty_list.h -- 邻接表头文件	*/
/* 一个有向图G=(V,E)有顶点集(vertex)V和边(edge)集E组成。 */


#include <stdarg.h>

#include "st_graph_common.h"

#define GINFINITY 	0//(~(1 << 31))
#define UNKNOWN 	0
#define KNOWN 		1

/*	数据类型定义	*/
typedef char ADJLName ;
typedef struct vertex
{
	ADJLName name ;
	int known ;
	int	dist ;
	ADJLName path ;
	struct vertex * next ;
} ADJLVertex ;
typedef struct adjacency_list
{
	ADJLVertex * list ;			// 记录点的边
	int * indegree ;			// 用单独的数组来保存各个点的入度
	int capacity ;				// 记录大小容量
} * Adjacent_List ;

/*	接口函数声明	*/

/*	操作:	为一个邻接表分配存储空间	*/
/*	操作前:	padj 指向一个邻接表, capacity 指示邻接表的大小	*/
/*	操作后:	如果 capacity > 0 && 内分分配成功, 创建该邻接表, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int CreateAdjacent_List (Adjacent_List * const padj, const int capacity) ;

/*	操作:	初始化邻接表的第 index 行	*/
/*	操作前:	padj 指向一个已创建的邻接表, index 指示行的索引, name 指示表头顶点名字, indegree 指示该顶点的入度, sub 指示参数的个数, ... 指示邻接到该顶点的顶点	*/
/*	操作后:	如果该邻接表存在第 index 行, 参数无误, 则初始化该行, 返回1; 否则返回0	*/
/*	时间复杂度:	O(N)	*/
int InitializeALineOfAdjacent_List (const Adjacent_List * const padj, const int index, const ADJLName name, const int indegree, const int sub, ...) ;

/*	操作:	从低索引向高索引依次打印邻接表中所有顶点1次	*/
/*	操作前:	padj 指向一个已创建完毕的邻接表	*/
/*	操作后:	该邻接表中的所有顶点依次被打印1次	*/
/*	时间复杂度:	O(N * N)	*/
void PrintAdjacent_List (const Adjacent_List * const padj) ;

/*	操作:	释放一个邻接表所占用的内存空间	*/
/*	操作前:	padj 指向一个已创建的邻接表	*/
/*	操作后:	该邻接表所占用的内存空间被释放	*/
/*	时间复杂度:	O(N * N)	*/
void ReleaseForAdjacent_List (const Adjacent_List * const padj) ;

/*	操作:	对邻接表输出一个拓扑排序	*/
/*	操作前:	padj 指向一个已创建的邻接表， topological保存一个拓扑排序元素的数组	*/
/*	操作后:	输出一个拓扑排序到topological	*/
/*	时间复杂度:	O(N * N)	*/
void st_topological_sort (Adjacent_List * padj, ADJLName * topological);

/*	操作:	对邻接表找出无权图的最短路径	*/
/*	操作前:	padj 指向一个已创建的邻接表	*/
/*	操作后:	初始化邻接表中的个点的最短路径	*/
/*	时间复杂度:	O(N * N)	*/
void Unweightd (Adjacent_List * const padj) ;

ST_END_DECLS ;
#endif	/* __ST_ADJACENTY_LIST_H__ */

