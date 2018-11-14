/*
	数据结构C语言版 迪杰斯特拉算法 
	P189 
	编译环境：Dev-C++ 4.9.9.2
	日期：2011年2月15日 
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
// 迪杰斯特拉算法的实现 

#define MAX_NAME 5			// 顶点字符串的最大长度+1
#define MAX_INFO 20			// 相关信息字符串的最大长度+1
typedef int VRType;			// 顶点关系的数据类型
#define INFINITY INT_MAX	// 用整型最大值代替∞
#define MAX_VERTEX_NUM 20	// 最大顶点个数 
typedef char InfoType;		// 信息的类型
typedef char VertexType[MAX_NAME];	// 顶点数据类型及长度
typedef enum{DG, DN, AG, AN} GraphKind; // {有向图,有向网,无向图,无向网} 

// 邻接矩阵的数据结构
typedef struct
{
	VRType adj; // 顶点关系类型。对无权图，用1(是)或0(否)表示相邻否； 
				// 对带权图，则为权值类型 
	InfoType *info; // 该弧相关信息的指针(可无) 
 }ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 图的数据结构
typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];	// 顶点向量
	AdjMatrix arcs;		// 邻接矩阵
	int vexnum,			// 图的当前顶点数
		arcnum;			// 图的当前弧数
	GraphKind kind;		// 图的种类标志
} MGraph;

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];


// 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1。
int LocateVex(MGraph G,VertexType u)
{
	int i;
	for(i = 0; i < G.vexnum; ++i)
		if( strcmp(u, G.vexs[i]) == 0)
			return i;
	return -1;
}

// 采用数组(邻接矩阵)表示法,构造有向网G。
int CreateDN(MGraph *G)
{
	int i,j,k,w,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;

	printf("请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0):"
		" (空格隔开)\n");
	scanf("%d%d%d%*c", &(*G).vexnum, &(*G).arcnum, &IncInfo);
	
	printf("请输入%d个顶点的值(<%d个字符):\n", (*G).vexnum, MAX_NAME);
	for(i=0;i<(*G).vexnum;++i)		// 构造顶点向量
		scanf("%s%*c",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i)		// 初始化邻接矩阵
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=INFINITY; // 网,边的权值初始化为无穷大 
			(*G).arcs[i][j].info=NULL;
		}
	
	printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔): \n",(*G).arcnum);
	for(k=0;k<(*G).arcnum;++k)
	{
		scanf("%s%s%d%*c",va,vb,&w);  // %*c吃掉回车符 
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=w; // 有向网，弧的权值为w 
		if(IncInfo)
		{
			printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
			scanf("%s%*c", s);
			w = strlen(s);
			if(w)
			{
				info=(char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=info; // 有向 
			}
		}
	}
	(*G).kind=DN;	//有向网的种类标志
	return 1;
}

// 算法7.15 P189
// 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度 
// D[v]。若P[v][w]为1,则w是从v0到v当前求得最短路径上的顶点。 
// final[v]为1当且仅当v∈S,即已经求得从v0到v的最短路径
void ShortestPath_DIJ(MGraph G,int v0,PathMatrix *P,ShortPathTable *D)
{ 
	int v,w,i,j,min;
	int final[MAX_VERTEX_NUM];
	
	for(v=0;v<G.vexnum;++v)
	{
		final[v]=0;
		(*D)[v]=G.arcs[v0][v].adj;
		for(w=0;w<G.vexnum;++w)
			(*P)[v][w]=0; // 设空路径 
		if((*D)[v]<INFINITY)
		{
			(*P)[v][v0]=1;
			(*P)[v][v]=1;
		}
	}
	(*D)[v0]=0;
	final[v0]=1; // 初始化,v0顶点属于S集 
	for(i=1;i<G.vexnum;++i) // 其余G.vexnum-1个顶点 
	{ // 开始主循环,每次求得v0到某个v顶点的最短路径,并加v到S集 
		min=INFINITY; // 当前所知离v0顶点的最近距离 
		for(w=0;w<G.vexnum;++w)
			if(!final[w]) // w顶点在V-S中 
				if((*D)[w]<min)
				{
					v=w;
					min=(*D)[w];
				} // w顶点离v0顶点更近 
		final[v]=1; // 离v0顶点最近的v加入S集 
		for(w=0;w<G.vexnum;++w) // 更新当前最短路径及距离 
		{
			if(!final[w]&&min<INFINITY && G.arcs[v][w].adj < INFINITY
				&& (min+G.arcs[v][w].adj<(*D)[w]))
			{
				// 修改D[w]和P[w],w∈V-S 
				(*D)[w]=min+G.arcs[v][w].adj;
				for(j=0;j<G.vexnum;++j)
					(*P)[w][j]=(*P)[v][j];
				(*P)[w][w]=1;
			}
		}
	}
}

int main()
{
	int i,j,v0=0; // v0为源点 
	MGraph g;
	PathMatrix p;
	ShortPathTable d;
	
	CreateDN(&g);
	ShortestPath_DIJ(g,v0,&p,&d);
	printf("最短路径数组p[i][j]如下:\n");
	for(i=0;i<g.vexnum;++i)
	{
		for(j=0;j<g.vexnum;++j)
			printf("%2d",p[i][j]);
		printf("\n");
	}
	printf("%s到各顶点的最短路径长度为：\n",g.vexs[0]);
	for(i=1;i<g.vexnum;++i)
		printf("%s-%s:%d\n",g.vexs[0],g.vexs[i],d[i]);
	
	system("pause");
	return 0; 
}

/*
输出效果：

请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): (空格隔开)
4 4 0
请输入4个顶点的值(<5个字符):
a
b
c
d
请输入4条弧的弧尾 弧头 权值(以空格作为间隔):
a b 1
a c 2
b d 3
c d 4
最短路径数组p[i][j]如下:
 0 0 0 0
 1 1 0 0
 1 0 1 0
 1 1 0 1
a到各顶点的最短路径长度为：
a-b:1
a-c:2
a-d:4
请按任意键继续. . . 

*/ 
