/*	adjacenty_list.h -- 邻接表头文件	*/
#include <stdarg.h>

/*	数据类型定义	*/
typedef char Name ;
typedef struct vertex
{
	Name name ;
	struct vertex * next ;
} Vertex ;
typedef struct adjacency_list
{
	Vertex * list ;
	int * indegree ;
	int capacity ;
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
int InitializeALineOfAdjacent_List (const Adjacent_List * const padj, const int index, const Name name, const int indegree, const int sub, ...) ;

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