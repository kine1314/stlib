/*
	数据结构C语言版 弗洛伊德算法 
	P191
	编译环境：Dev-C++ 4.9.9.2
	日期：2011年2月15日 
*/

#include <stdio.h>
#include <limits.h>

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

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];


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

// 算法7.16
// 用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w]及其 
// 带权长度D[v][w]。若P[v][w][u]为1,则u是从v到w当前求得最短 
// 路径上的顶点。
void ShortestPath_FLOYD(MGraph G,PathMatrix *P,DistancMatrix *D)
{ 
	int u,v,w,i;
	for(v=0;v<G.vexnum;v++) // 各对结点之间初始已知路径及距离 
		for(w=0;w<G.vexnum;w++)
		{
			(*D)[v][w]=G.arcs[v][w].adj;
			for(u=0;u<G.vexnum;u++)
				(*P)[v][w][u]=0;
			if((*D)[v][w]<INFINITY) // 从v到w有直接路径 
			{
				(*P)[v][w][v]=1;
				(*P)[v][w][w]=1;
			}
		}
	for(u=0;u<G.vexnum;u++)
		for(v=0;v<G.vexnum;v++)
			for(w=0;w<G.vexnum;w++)
				// 从v经u到w的一条路径更短 
				if((*D)[v][u]+(*D)[u][w]<(*D)[v][w])
				{
					(*D)[v][w]=(*D)[v][u]+(*D)[u][w];
					for(i=0;i<G.vexnum;i++)
						(*P)[v][w][i]=(*P)[v][u][i]||(*P)[u][w][i];
				}
}

int main()
{
	MGraph g;
	int i,j,k,l,m,n;
	PathMatrix p;
	DistancMatrix d;
	
	CreateDN(&g);
	for(i=0;i<g.vexnum;i++)
		g.arcs[i][i].adj=0; // ShortestPath_FLOYD()要求对角元素值为0 
	printf("邻接矩阵:\n");
	for(i=0;i<g.vexnum;i++)
	{
		for(j=0;j<g.vexnum;j++)
			printf("%11d",g.arcs[i][j]);
		printf("\n");
	}
	ShortestPath_FLOYD(g,&p,&d);
	printf("d矩阵:\n");
	for(i=0;i<g.vexnum;i++)
	{
		for(j=0;j<g.vexnum;j++)
			printf("%6d",d[i][j]);
		printf("\n");
	}
	for(i=0;i<g.vexnum;i++)
		for(j=0;j<g.vexnum;j++)
			printf("%s到%s的最短距离为%d\n",g.vexs[i],g.vexs[j],d[i][j]);
	printf("p矩阵:\n");
	l=strlen(g.vexs[0]); // 顶点向量字符串的长度 
	for(i=0;i<g.vexnum;i++)
	{
		for(j=0;j<g.vexnum;j++)
		{
			if(i!=j)
			{
				m=0; // 占位空格 
				for(k=0;k<g.vexnum;k++)
					if(p[i][j][k]==1)
						printf("%s",g.vexs[k]);
				else
					m++;
				for(n=0;n<m*l;n++) // 输出占位空格 
					printf(" ");
			}
			else
				for(k=0;k<g.vexnum*l;k++) // 输出占位空格 
					printf(" ");
			printf("   "); // 输出矩阵元素之间的间距 
		}
		printf("\n");
	}

	system("pause");
	return 0; 
}

/*
输出效果：

请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): (空格隔开)
3 5 0
请输入3个顶点的值(<5个字符):
V0
V1
V2
请输入5条弧的弧尾 弧头 权值(以空格作为间隔):
V0 V1 4
V0 V2 11
V1 V0 6
V1 V2 2
V2 V0 3
邻接矩阵:
          0          4         11
          6          0          2
          3 2147483647          0
d矩阵:
     0     4     6
     5     0     2
     3     7     0
V0到V0的最短距离为0
V0到V1的最短距离为4
V0到V2的最短距离为6
V1到V0的最短距离为5
V1到V1的最短距离为0
V1到V2的最短距离为2
V2到V0的最短距离为3
V2到V1的最短距离为7
V2到V2的最短距离为0
p矩阵:
         V0V1     V0V1V2
V0V1V2            V1V2
V0V2     V0V1V2
请按任意键继续. . . 

*/
