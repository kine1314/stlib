#ifndef	__ST_GRAPH_ADJLIST_H__
#define	__ST_GRAPH_ADJLIST_H__

#include "stlib.h"


ST_BEGIN_DECLS ;

 // 树的二叉链表(孩子－兄弟)存储表示 


// 图的邻接表存储表示 
#define MAX_NAME 3						// 顶点字符串的最大长度+1 
#define MAX_VERTEX_NUM 20
typedef int InfoType;					// 存放网的权值 
typedef char VertexType[MAX_NAME];		// 字符串类型 
typedef enum{DG,DN,AG,AN}GraphKind; 	// {有向图,有向网,无向图,无向网} 

// 深度优先生成树
typedef char GElemType[MAX_NAME];
typedef GElemType GTElemType;
typedef struct _CSNode
{
	GTElemType data;
	struct _CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

typedef struct ArcNode
{
	int adjvex;							// 该弧所指向的顶点的位置 
	struct ArcNode *nextarc;			// 指向下一条弧的指针 
	InfoType *info;						// 网的权值指针） 
}ArcNode;	// 表结点 

typedef struct VNode
{
	VertexType data;					// 顶点信息 
	ArcNode *firstarc;					// 第一个表结点的地址,指向第一条依附该顶点的弧的指针 
 }VNode,AdjList[MAX_VERTEX_NUM];		// 头结点 

typedef struct
{
	AdjList vertices;
	int vexnum,arcnum;					// 图的当前顶点数和弧数 
	int kind;							// 图的种类标志 
}ALGraph;



// 外部接口声明
// 邻接表存储图
int		CreateGraph(ALGraph *G);
void	DestroyGraph(ALGraph *G);
void 	InsertVex(ALGraph *G, VertexType v);
int 	DeleteVex(ALGraph *G, VertexType v);
int 	InsertArc(ALGraph *G, VertexType v, VertexType w);
int 	DeleteArc(ALGraph *G, VertexType v, VertexType w);
void 	DFSTraverse(ALGraph G, void(*Visit)(char*));
void 	BFSTraverse(ALGraph G, void(*Visit)(char*));
void 	G_Display(ALGraph G);
int 	PutVex(ALGraph *G,VertexType v,VertexType value);
// 拓扑排序
int 	TopologicalSort(ALGraph G);
// 关节点
void 	FindArticul(ALGraph G);
// 关键路径
int 	CriticalPath(ALGraph G) ;
// 无向图的深度优先生成树
// 建立无向图G的深度优先生成森林的(最左)孩子(右)兄弟链表T。
void 	DFSForest(ALGraph G,CSTree *T);
// 先根遍历孩子－兄弟二叉链表结构的树T
void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))

ST_END_DECLS;
#endif	/* __ST_GRAPH_ADJLIST_H__ */

