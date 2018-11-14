/*
	数据结构C语言版 求关节点
	P176 
	编译环境：Dev-C++ 4.9.9.2
	日期：2011年2月15日 
*/

#include <stdio.h>
#include <malloc.h> 

// 图的邻接表存储表示 
#define MAX_NAME 3					// 顶点字符串的最大长度+1 
#define MAX_VERTEX_NUM 20
typedef int InfoType;				// 存放网的权值 
typedef char VertexType[MAX_NAME];	// 字符串类型 
typedef enum{DG,DN,AG,AN}GraphKind; // {有向图,有向网,无向图,无向网} 

typedef struct ArcNode
{
	int adjvex;					// 该弧所指向的顶点的位置 
	struct ArcNode *nextarc;	// 指向下一条弧的指针 
	InfoType *info;				// 网的权值指针） 
}ArcNode;	// 表结点 

typedef struct VNode
{
	VertexType data;			// 顶点信息 
	ArcNode *firstarc;			// 第一个表结点的地址,指向第一条依附该顶点的弧的指针 
 }VNode,AdjList[MAX_VERTEX_NUM];// 头结点 

typedef struct
{
	AdjList vertices;
	int vexnum,arcnum;	// 图的当前顶点数和弧数 
	int kind;			// 图的种类标志 
}ALGraph;


// 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1。 
int LocateVex(ALGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	return -1;
}

// 采用邻接表存储结构,构造没有相关信息的图G(用一个函数构造4种图)。
int CreateGraph(ALGraph *G)
{
	int i,j,k;
	int w;		// 权值 
	VertexType va,vb;
	ArcNode *p;
	
	printf("请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
	scanf("%d",&(*G).kind);
	printf("请输入图的顶点数和边数:（空格）\n");
	scanf("%d%d", &(*G).vexnum, &(*G).arcnum);
	printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
	for(i = 0; i < (*G).vexnum; ++i)	// 构造顶点向量 
	{
		scanf("%s", (*G).vertices[i].data);
		(*G).vertices[i].firstarc = NULL;
	}
	if((*G).kind == 1 || (*G).kind == 3) // 网 
		printf("请顺序输入每条弧(边)的权值、弧尾和弧头(以空格作为间隔):\n");
	else // 图 
		printf("请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔):\n");
	for(k = 0;k < (*G).arcnum; ++k)	// 构造表结点链表 
	{
		if((*G).kind==1||(*G).kind==3) // 网 
			scanf("%d%s%s",&w,va,vb);
		else			// 图 
			scanf("%s%s",va,vb);
		i = LocateVex(*G,va); // 弧尾 
		j = LocateVex(*G,vb); // 弧头 
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		if((*G).kind == 1 || (*G).kind == 3) // 网 
		{
			p->info = (int *)malloc(sizeof(int));
			*(p->info) = w;
		}
		else
			p->info = NULL; // 图 
		p->nextarc = (*G).vertices[i].firstarc; // 插在表头 
		(*G).vertices[i].firstarc = p;
		if((*G).kind >= 2) // 无向图或网,产生第二个表结点 
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			if((*G).kind == 3) // 无向网 
			{
				p->info = (int*)malloc(sizeof(int));
				*(p->info) = w;
			}
			else
				p->info = NULL; // 无向图 
			p->nextarc = (*G).vertices[j].firstarc; // 插在表头 
			(*G).vertices[j].firstarc = p;
		}
	}
	return 1;
}

int visited[MAX_VERTEX_NUM];	// 访问标志数组(全局量) 
int count; // 全局量count对访问计数 
int low[MAX_VERTEX_NUM];

// 算法7.11 P178 
// 从第v0个顶点出发深度优先遍历图G，查找并输出关节点。
void DFSArticul(ALGraph G,int v0)
{
	int min,w;
	ArcNode *p;
	visited[v0]=min=++count; // v0是第count个访问的顶点 
	for(p=G.vertices[v0].firstarc;p;p=p->nextarc) // 对v0的每个邻接顶点检查 
	{
		w=p->adjvex; // w为v0的邻接顶点 
		if(visited[w]==0) // w未曾访问，是v0的孩子 
		{
			DFSArticul(G,w); // 返回前求得low[w] 
			if(low[w]<min)
				min=low[w];
			if(low[w]>=visited[v0])
				printf("%d %s\n",v0,G.vertices[v0].data); // 关节点 
		}
		else if(visited[w]<min)
		min=visited[w]; // w已访问，w是v0在生成树上的祖先 
	}
	low[v0]=min;
}

// 算法7.10 P178 
// 连通图G以邻接表作存储结构，查找并输出G上全部关节点。 
// 全局量count对访问计数。 
void FindArticul(ALGraph G)
{
	int i,v;
	ArcNode *p;
	count=1;
	low[0]=visited[0]=1; // 设定邻接表上0号顶点为生成树的根 
	for(i=1;i<G.vexnum;++i)
		visited[i]=0; // 其余顶点尚未访问 
	p=G.vertices[0].firstarc;
	v=p->adjvex;
	DFSArticul(G,v); // 从第v顶点出发深度优先查找关节点 
	if(count<G.vexnum) // 生成树的根有至少两棵子树 
	{
		printf("%d %s\n",0,G.vertices[0].data); // 根是关节点，输出 
		while(p->nextarc)
		{
			p=p->nextarc;
			v=p->adjvex;
			if(visited[v]==0)
			DFSArticul(G,v);
		}
	}
}

int main()
{
	int i;
	ALGraph g;
	printf("请选择无向图\n");
	CreateGraph(&g);
	printf("输出关节点：\n");
	FindArticul(g);
	printf("\n%2s %9s %14s %8s\n", "i", "G.vertices[i].data","visited[i]", "low[i]");
	for(i=0;i<g.vexnum;++i)
		printf("%2d %9s %14d %8d\n",i,g.vertices[i].data,visited[i],low[i]);

	system("pause");
	return 0; 
}

/*
输出效果：

请选择无向图
请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3): 2
请输入图的顶点数和边数:（空格）
3 2
请输入3个顶点的值(<3个字符):
a
b
c
请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔):
a b
a c
输出关节点：
0 a

 i G.vertices[i].data     visited[i]   low[i]
 0         a              1        1
 1         b              3        1
 2         c              2        1
请按任意键继续. . . 

*/
