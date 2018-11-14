/*
	数据结构C语言版 图的邻接矩阵存储表示和实现
	P161 
	编译环境：Dev-C++ 4.9.9.2
	日期：2011年2月15日 
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
#include <stdlib.h>
//#include <conio.h>

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

typedef VRType QElemType; // 队列类型 

//  单链队列－－队列的链式存储结构 
typedef struct QNode
{
	QElemType data;		//数据域
	struct QNode *next;	//指针域
}QNode,*QueuePtr;


typedef struct
{
	QueuePtr front,	//队头指针，指针域指向队头元素
		rear;		//队尾指针，指向队尾元素
}LinkQueue;



// 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1。
int LocateVex(MGraph G,VertexType u)
{
	int i;
	for(i = 0; i < G.vexnum; ++i)
		if( strcmp(u, G.vexs[i]) == 0)
			return i;
	return -1;
}

// 采用数组(邻接矩阵)表示法,构造有向图G。
int CreateDG(MGraph *G)
{
	int i,j,k,l,IncInfo;
	char s[MAX_INFO], *info;
	VertexType va, vb;
	
	printf("请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0):"
		"(空格隔开) ");
	scanf("%d%d%d", &(*G).vexnum, &(*G).arcnum, &IncInfo);
	fflush(stdin);
	printf("请输入%d个顶点的值(<%d个字符):\n", (*G).vexnum, MAX_NAME);
	for(i = 0; i < (*G).vexnum; ++i)	// 构造顶点向量 
		scanf("%s", (*G).vexs[i]);
	for(i = 0; i < (*G).vexnum; ++i)	// 初始化邻接矩阵
		for(j = 0; j < (*G).vexnum; ++j)
		{
			(*G).arcs[i][j].adj = 0;	// 图边的权值初始化为0
			(*G).arcs[i][j].info = NULL;
		}
	printf("请输入%d条弧的弧尾 弧头(空格隔开): \n",(*G).arcnum);
	for(k = 0; k <(*G).arcnum ; ++k)
	{
		scanf("%s%s%*c", va, vb);	// %*c吃掉回车符
		i = LocateVex(*G, va);
		j = LocateVex(*G, vb);
		(*G).arcs[i][j].adj = 1;	// 有向图，弧的权值设为1
		if( IncInfo )
		{
			printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
			gets(s);
			l=strlen(s);
			if(l)
			{
				info=(char*)malloc((l+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info = info; // 有向 
			}
		}
	}
	(*G).kind=DG;	//有向图种类标志
	return 1;
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

// 采用数组(邻接矩阵)表示法,构造无向图G 
int CreateAG(MGraph *G)
{
	int i,j,k,l,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;
	
	printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1,否:0):(空格区分) ");
	scanf("%d%d%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
	fflush(stdin); 
	printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) // 构造顶点向量 
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) // 初始化邻接矩阵 
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=0; // 图初始化为0 
			(*G).arcs[i][j].info=NULL;
		}
	printf("请输入%d条边的顶点1 顶点2(以空格作为间隔): \n",(*G).arcnum);
	for(k=0;k<(*G).arcnum;++k)
	{
		scanf("%s%s%*c",va,vb); // %*c吃掉回车符 
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; // 无向图，关系值为1 
		if(IncInfo)	//边是否有信息
		{
			printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
			gets(s);
			l=strlen(s);
			if(l)
			{
				info=(char*)malloc((l+1)*sizeof(char));
				strcpy(info,s);
				// 无向，对称 
				(*G).arcs[i][j].info=(*G).arcs[j][i].info=info;
			}
		}
	}
	(*G).kind=AG;	//无向图的种类标志
	return 1;
}

// 算法7.2  P162
// 采用数组(邻接矩阵)表示法,构造无向网G。
int CreateAN(MGraph *G)
{
	int i,j,k,w,IncInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;
	
	printf("请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0):(空格区分) ");
	scanf("%d%d%d%*c",&(*G).vexnum,&(*G).arcnum,&IncInfo); 
	printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
	for(i=0;i<(*G).vexnum;++i) // 构造顶点向量 
		scanf("%s",(*G).vexs[i]);
	for(i=0;i<(*G).vexnum;++i) // 初始化邻接矩阵 
		for(j=0;j<(*G).vexnum;++j)
		{
			(*G).arcs[i][j].adj=INFINITY; // 网初始化为无穷大 
			(*G).arcs[i][j].info=NULL;
		}
	printf("请输入%d条边的顶点1 顶点2 权值(以空格作为间隔): \n",(*G).arcnum);
	for(k=0;k<(*G).arcnum;++k)
	{
		scanf("%s%s%d%*c",va,vb,&w); // %*c吃掉回车符 
		i=LocateVex(*G,va);
		j=LocateVex(*G,vb);
		(*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; // 无向 
		if(IncInfo)
		{
			printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
			gets(s);
			w=strlen(s);
			if(w)
			{
				info=(char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				(*G).arcs[i][j].info=(*G).arcs[j][i].info=info; // 无向 
			}
		}
	}
	(*G).kind=AN;	//无向网的种类标志
	return 1;
}

// 算法7.1 P162 
// 采用数组(邻接矩阵)表示法,构造图G。
int CreateGraph(MGraph *G)
{
	printf("请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4): \n");
	scanf("%d", &(*G).kind);
	switch( (*G).kind )
	{
	case DG: return CreateDG(G); // 构造有向图 
	case DN: return CreateDN(G); // 构造有向网 
	case AG: return CreateAG(G); // 构造无向图 
	case AN: return CreateAN(G); // 构造无向网 
	case 4:
	default: return 0;
	}
}

// 销毁图G 
void DestroyGraph(MGraph *G)
{
	int i, j;
	if((*G).kind < 2)	// 有向 
		for(i = 0; i < (*G).vexnum; i++)	// 释放弧的相关信息(如果有的话) 
		{
			for(j = 0; j < (*G).vexnum; j++)
				if( (*G).arcs[i][j].adj == 1 && (*G).kind == 0 
					|| (*G).arcs[i][j].adj != INFINITY
					&& (*G).kind == 1)	// 有向图的弧 || 有向网的弧 
					if( (*G).arcs[i][j].info ) // 有相关信息
					{
						free((*G).arcs[i][j].info);
						(*G).arcs[i][j].info = NULL;
					}
		}
	else	// 无向 
		for(i = 0; i < (*G).vexnum; i++) // 释放边的相关信息(如果有的话) 
			for(j = i + 1; j < (*G).vexnum; j++)
				if( (*G).arcs[i][j].adj == 1 && (*G).kind == 2 
					|| (*G).arcs[i][j].adj != INFINITY
					&& (*G).kind == 3)	// 无向图的边||无向网的边 
					if( (*G).arcs[i][j].info )	// 有相关信息 
					{
						free((*G).arcs[i][j].info);
						(*G).arcs[i][j].info=(*G).arcs[j][i].info=NULL;
					}
	(*G).vexnum = 0;
	(*G).arcnum = 0;
}

// 返回v的值。
VertexType* GetVex(MGraph G,int v)
{
	if(v >= G.vexnum || v < 0)
		exit(0);
	return &G.vexs[v];
}

// 对v赋新值value。
int PutVex(MGraph *G,VertexType v,VertexType value)
{
	int k;
	k = LocateVex(*G, v); // k为顶点v在图G中的序号 
	if(k < 0)
		return 0;
	strcpy((*G).vexs[k], value);
	return 1;
}

// 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1。 
int FirstAdjVex(MGraph G,VertexType v)
{	
	int i,j=0,k;
	k=LocateVex(G,v); // k为顶点v在图G中的序号 
	if(G.kind == DN || G.kind == AN) // 网 
		j = INFINITY;
	for(i= 0; i < G.vexnum; i++)
		if(G.arcs[k][i].adj != j)
			return i;
	return -1;
}

// 返回v的(相对于w的)下一个邻接顶点的序号,若w是v的最后一个邻接顶点,
// 则返回-1。
int NextAdjVex(MGraph G,VertexType v,VertexType w)
{ 	
	int i,j=0,k1,k2;
	
	k1 = LocateVex(G,v);	// k1为顶点v在图G中的序号 
	k2 = LocateVex(G,w);	// k2为顶点w在图G中的序号 
	if(G.kind==DN||G.kind==AN) // 网 
		j = INFINITY;
	for(i = k2+1; i < G.vexnum; i++)
		if(G.arcs[k1][i].adj != j)
			return i;
	return -1;
}

// 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) 
void InsertVex(MGraph *G,VertexType v)
{
	int i;
	strcpy((*G).vexs[(*G).vexnum],v); // 构造新顶点向量 
	for(i = 0; i <= (*G).vexnum; i++)
	{	// 初始化该行邻接矩阵的值(无边或弧的值)
		if((*G).kind % 2) // 网
		{
			(*G).arcs[(*G).vexnum][i].adj = INFINITY;
			(*G).arcs[i][(*G).vexnum].adj = INFINITY;
		}
		else // 图 
		{
			(*G).arcs[(*G).vexnum][i].adj = 0;
			(*G).arcs[i][(*G).vexnum].adj = 0;
		}
		(*G).arcs[(*G).vexnum][i].info = NULL; // 初始化相关信息指针 
		(*G).arcs[i][(*G).vexnum].info = NULL;
	}
	(*G).vexnum += 1;	// 图G的顶点数加1 
}

// 删除G中顶点v及其相关的弧。
int DeleteVex(MGraph *G,VertexType v)
{ 	
	int i,j,k;
	VRType m=0;
	k = LocateVex(*G,v);	// k为待删除顶点v的序号 
	if(k < 0)				// v不是图G的顶点
		return 0;
	if((*G).kind == DN || (*G).kind == AN) // 网
		m = INFINITY;
	for(j = 0; j < (*G).vexnum; j++)
		if((*G).arcs[j][k].adj != m)	// 有入弧或边 
		{
			if((*G).arcs[j][k].info)		// 有相关信息 
				free((*G).arcs[j][k].info);	// 释放相关信息 
			(*G).arcnum--;	// 修改弧数 
		}
	if((*G).kind == DG || (*G).kind == DN) // 有向 
		for(j = 0; j < (*G).vexnum; j++)
			if((*G).arcs[k][j].adj != m)	// 有出弧 
			{
				if((*G).arcs[k][j].info) // 有相关信息 
					free((*G).arcs[k][j].info); // 释放相关信息 
				(*G).arcnum--; // 修改弧数 
			}
	for(j=k+1;j<(*G).vexnum;j++) // 序号k后面的顶点向量依次前移 
		strcpy((*G).vexs[j-1],(*G).vexs[j]);
	for(i=0;i<(*G).vexnum;i++)
		for(j=k+1;j<(*G).vexnum;j++)
			(*G).arcs[i][j-1]=(*G).arcs[i][j]; // 移动待删除顶点之后的矩阵元素 
	for(i=0;i<(*G).vexnum;i++)
		for(j=k+1;j<(*G).vexnum;j++)
			(*G).arcs[j-1][i]=(*G).arcs[j][i]; // 移动待删除顶点之下的矩阵元素 
	(*G).vexnum--;	// 更新图的顶点数 
	
	return 1;
}

// 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v> 。
int InsertArc(MGraph *G,VertexType v,VertexType w)
{	
	int i,l,v1,w1;
	char *info,s[MAX_INFO];
	
	v1 = LocateVex(*G,v); // 尾 
	w1 = LocateVex(*G,w); // 头 
	if(v1 < 0 || w1 < 0)
		return 0;
	(*G).arcnum++;	// 弧或边数加1 
	if((*G).kind%2) // 网 
	{
		printf("请输入此弧或边的权值: ");
		scanf("%d",&(*G).arcs[v1][w1].adj);
	}
	else	// 图 
		(*G).arcs[v1][w1].adj = 1;
	printf("是否有该弧或边的相关信息(0:无 1:有): \n");
	scanf("%d%*c",&i);
	if(i)
	{
		printf("请输入该弧或边的相关信息(<%d个字符)：\n",MAX_INFO);
		gets(s);
		l=strlen(s);
		if(l)
		{
			info=(char*)malloc((l+1)*sizeof(char));
			strcpy(info,s);
			(*G).arcs[v1][w1].info=info;
		}
	}
	if((*G).kind>1) // 无向 
	{
		(*G).arcs[w1][v1].adj=(*G).arcs[v1][w1].adj;
		(*G).arcs[w1][v1].info=(*G).arcs[v1][w1].info; // 指向同一个相关信息 
	}
	return 1;
}

// 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v> 
int DeleteArc(MGraph *G,VertexType v,VertexType w)
{ 
	int v1,w1;
	v1=LocateVex(*G,v); // 尾 
	w1=LocateVex(*G,w); // 头 
	if(v1<0||w1<0) // v1、w1的值不合法 
		return 0;
	if((*G).kind%2==0) // 图 
		(*G).arcs[v1][w1].adj=0;
	else // 网 
		(*G).arcs[v1][w1].adj=INFINITY;
	if((*G).arcs[v1][w1].info) // 有其它信息 
	{
		free((*G).arcs[v1][w1].info);
		(*G).arcs[v1][w1].info=NULL;
	}
	if((*G).kind>=2) // 无向,删除对称弧<w,v> 
	{
		(*G).arcs[w1][v1].adj=(*G).arcs[v1][w1].adj;
		(*G).arcs[w1][v1].info=NULL;
	}
	(*G).arcnum--;
	return 1;
}

int visited[MAX_VERTEX_NUM];	// 访问标志数组(全局量) 

int(*VisitFunc)(VertexType);		// 函数指针变量 

// 算法7.5 P169
// 从第v个顶点出发递归地深度优先遍历图G。
void DFS(MGraph G,int v)
{
	VertexType w1,v1;
	int w;
	visited[v] = 1;		// 设置访问标志为1(已访问) 
	VisitFunc(G.vexs[v]);	// 访问第v个顶点 
	strcpy(v1, *GetVex(G,v));
	for(w = FirstAdjVex(G,v1); w >= 0; w = NextAdjVex(G, v1, strcpy(w1,*GetVex(G,w))))
		if( !visited[w] )
			// 对v的尚未访问的序号为w的邻接顶点递归调用DFS 
			DFS(G,w);
}

// 算法7.4 P169
// 从第1个顶点起,深度优先遍历图G,并对每个顶点调用函数Visit一次。
void DFSTraverse(MGraph G, int(*Visit)(VertexType))
{
	int v;
	// 使用全局变量VisitFunc,使DFS不必设函数指针参数
	VisitFunc = Visit; 
	for(v = 0; v < G.vexnum; v++)
		visited[v] = 0;		// 访问标志数组初始化(未被访问) 
	for(v = 0; v < G.vexnum; v++)
		if( !visited[v] )
			DFS(G,v);			// 对尚未访问的顶点调用DFS 
	printf("\n");
}


// 	构造一个空队列Q。
int InitQueue(LinkQueue *Q)
{
	// 动态分配一个空间
	(*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
	if(!(*Q).front)
		exit(0);
	(*Q).front->next = NULL;	//队头指针指向空，无数据域，这样构成了一个空队列
	return 1;
}

//	插入元素e为Q的新的队尾元素。
int EnQueue(LinkQueue *Q,QElemType e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if(!p)	// 存储分配失败 
		exit(0);
	//生成一个以为e为数据域的队列元素
	p->data = e;
	p->next = NULL;
	//将该新队列元素接在队尾的后面
	(*Q).rear->next = p;
	(*Q).rear = p;
	return 1;
}

// 	若队列不空,删除Q的队头元素,用e返回其值,并返回1,否则返回0。
int DeQueue(LinkQueue *Q,QElemType *e)
{
	QueuePtr p;
	if((*Q).front == (*Q).rear)
		return 0;
	p = (*Q).front->next;	//队头元素
	*e = p->data;
	(*Q).front->next = p->next;
	if((*Q).rear == p)
		(*Q).rear = (*Q).front;
	free(p);
	return 1;
}

// 	若Q为空队列,则返回1,否则返回0。
int QueueEmpty(LinkQueue Q)
{
	if(Q.front == Q.rear)
		return 1;
	else
		return 0;
}

//	算法7.6 P170
// 从第1个顶点起,按广度优先非递归遍历图G,并对每个顶点调用函数
//	Visit一次且仅一次。使用辅助队列Q和访问标志数组visited。
void BFSTraverse(MGraph G, int(*Visit)(VertexType))
{
	int v,u,w;
	VertexType w1,u1;
	LinkQueue Q;
	
	for(v = 0; v < G.vexnum; v++)
		visited[v] = 0;		// 置初值 
	InitQueue(&Q);				// 置空的辅助队列Q 
	for(v = 0; v < G.vexnum; v++)
		if(!visited[v])			// v尚未访问 
		{
			visited[v] = 1;	// 设置访问标志为1(已访问) 
			Visit(G.vexs[v]);
			EnQueue(&Q, v);		// v入队列 
			while(!QueueEmpty(Q))	// 队列不空 
			{
				DeQueue(&Q, &u);	// 队头元素出队并置为u 
				strcpy(u1, *GetVex(G,u));
				for(w = FirstAdjVex(G,u1); w >= 0; w = 
					NextAdjVex(G, u1, strcpy(w1,*GetVex(G,w))))
					if(!visited[w]) // w为u的尚未访问的邻接顶点的序号 
					{
						visited[w] = 1;
						Visit(G.vexs[w]);
						EnQueue(&Q,w);
					}
			}
		}
	printf("\n");
}

void Display(MGraph G)
{
	// 输出邻接矩阵G 
	int i,j;
	char s[7],s1[3];
	
	switch(G.kind)
	{
	case DG: 
		strcpy(s,"有向图\0");
		strcpy(s1,"弧\0");
		break;
	case DN: 
		strcpy(s,"有向网\0");
		strcpy(s1,"弧\0");
		break;
	case AG: 
		strcpy(s,"无向图\0");
		strcpy(s1,"边\0");
		break;
	case AN:
		strcpy(s,"无向网\0");
		strcpy(s1,"边\0");
	}
	printf("%d个顶点%d条%s的%s\n",G.vexnum,G.arcnum,s1,s);
	for(i=0; i<G.vexnum; ++i)	// 输出G.vexs 输出顶点
		printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
	printf("G.arcs.adj:\n");	// 输出G.arcs.adj 邻接矩阵 
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
			// 这里进行修改，调节显示效果 
			printf("%6d",G.arcs[i][j].adj);
		printf("\n");
	}
	printf("G.arcs.info:\n"); // 输出G.arcs.info 弧的信息 
	printf("顶点1(弧尾) 顶点2(弧头) 该%s信息：\n",s1);
	if(G.kind<2) // 有向 
		for(i=0;i<G.vexnum;i++)
			for(j=0;j<G.vexnum;j++)
			{
				if(G.arcs[i][j].info)
					printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
			}
	else // 无向 
	{
		for(i=0;i<G.vexnum;i++)
			for(j=i+1;j<G.vexnum;j++)
				if(G.arcs[i][j].info)
					printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
	}
}

// 采用数组(邻接矩阵)表示法,由文件构造没有相关信息的无向图G 
int CreateFAG(MGraph *G)
{
	int i,j,k;
	char filename[13];
	VertexType va,vb;
	FILE *graphlist;
	
	printf("请输入数据文件名(1.txt)：");
	scanf("%s",filename);
	graphlist = fopen(filename,"r");
	fscanf(graphlist, "%d", &(*G).vexnum);
	fscanf(graphlist, "%d", &(*G).arcnum);
	for(i = 0; i < (*G).vexnum; ++i)	// 构造顶点向量 
		fscanf(graphlist,"%s",(*G).vexs[i]);
	for(i = 0; i < (*G).vexnum; ++i)	// 初始化邻接矩阵 
		for(j = 0; j < (*G).vexnum; ++j)
		{
			(*G).arcs[i][j].adj = 0;		// 图 
			(*G).arcs[i][j].info = NULL;	// 没有相关信息 
		}
	for(k = 0; k < (*G).arcnum; ++k)
	{
		fscanf(graphlist, "%s%s", va, vb);
		i = LocateVex(*G,va);
		j = LocateVex(*G,vb);
		(*G).arcs[i][j].adj = (*G).arcs[j][i].adj=1; // 无向图 
	}
	fclose(graphlist);
	(*G).kind = AG;
	return 1;
}

int visit(VertexType i)
{
	printf("%s ",i);
	return 1;
}

int main()
{
	int i,j,k,n,f = 0;
	VertexType v1,v2;
	MGraph g;

#if 0 
	printf("请顺序选择有向图,有向网,无向图,无向网\n");
	while(1)
	{
		f = CreateGraph(&g);
		if(!f)
			break; 
		getch();
		Display(g);
		getch();
		printf("插入新顶点，请输入顶点的值: ");
		scanf("%s",v1);
		InsertVex(&g,v1);
		printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
		scanf("%d",&n);
		for(k=0;k<n;k++)
		{
			printf("请输入另一顶点的值: ");
			scanf("%s",v2);
			if(g.kind<=1) // 有向 
			{
				printf("对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾): ");
				scanf("%d",&j);
				if(j)         
					InsertArc(&g,v2,v1);
				else
					InsertArc(&g,v1,v2);
			}
			else // 无向 
				InsertArc(&g,v1,v2);
		}
		Display(g);
		printf("删除顶点及相关的弧或边，请输入顶点的值: ");
		scanf("%s",v1);
		DeleteVex(&g,v1);
		Display(g);
		DestroyGraph(&g);
	}
#endif
 
#if 1
	CreateFAG(&g);
	Display(g);
	printf("深度优先搜索的结果:\n");
	DFSTraverse(g,visit);
	printf("广度优先搜索的结果:\n");
	BFSTraverse(g,visit);
	printf("删除一条边或弧，请输入待删除边或弧的弧尾 弧头：");
	scanf("%s%s",v1,v2);
	DeleteArc(&g,v1,v2);
	Display(g);
		printf("修改顶点的值，请输入原值 新值: ");
	scanf("%*c%s%s",v1,v2);
	f = PutVex(&g,v1,v2);
	if(f == 0)
		printf("修改失败");
	Display(g);
	DestroyGraph(&g);
#endif

	system("pause");
	return 0;
}


/*

1.txt的内容：

8
14
a
b
c
d
e
f
g
h
a b
a c
b e
b d
b c
c d
c h
h g
h d
d e
d f
d g
e f
f g
 


输出效果：

请顺序选择有向图,有向网,无向图,无向网
请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4):
0
请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0):(空格隔开) 3 3 0
请输入3个顶点的值(<5个字符):
a
b
c
请输入3条弧的弧尾 弧头(空格隔开):
a b
a c
b c
3个顶点3条弧的有向图
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.arcs.adj:
     0     1     1
     0     0     1
     0     0     0
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该弧信息：
插入新顶点，请输入顶点的值: d
插入与新顶点有关的弧或边，请输入弧或边数: 1
请输入另一顶点的值: b
对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾): 1
是否有该弧或边的相关信息(0:无 1:有):

0
4个顶点4条弧的有向图
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.vexs[3]=d
G.arcs.adj:
     0     1     1     0
     0     0     1     1
     0     0     0     0
     0     0     0     0
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该弧信息：
删除顶点及相关的弧或边，请输入顶点的值: c
3个顶点2条弧的有向图
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=d
G.arcs.adj:
     0     1     0
     0     0     1
     0     0     0
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该弧信息：
请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4):
4
请按任意键继续. . .


请顺序选择有向图,有向网,无向图,无向网
请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4):
1
请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): (空格隔开)
3 3 1
请输入3个顶点的值(<5个字符):
a
b
c
请输入3条弧的弧尾 弧头 权值(以空格作为间隔):
a b 1
请输入该弧的相关信息(<20个字符): 1111
a c 2
请输入该弧的相关信息(<20个字符): 222
b c 3
请输入该弧的相关信息(<20个字符): 333
3个顶点3条弧的有向网
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.arcs.adj:
  2147483647           1           2
  2147483647  2147483647           3
  2147483647  2147483647  2147483647
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该弧信息：
    a           b     1111
    a           c     222
    b           c     333
插入新顶点，请输入顶点的值: d
插入与新顶点有关的弧或边，请输入弧或边数: 1
请输入另一顶点的值: c
对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾): 0
请输入此弧或边的权值: 4
是否有该弧或边的相关信息(0:无 1:有):
0
4个顶点4条弧的有向网
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.vexs[3]=d
G.arcs.adj:
  2147483647           1           2  2147483647
  2147483647  2147483647           3  2147483647
  2147483647  2147483647  2147483647  2147483647
  2147483647  2147483647           4  2147483647
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该弧信息：
    a           b     1111
    a           c     222
    b           c     333
删除顶点及相关的弧或边，请输入顶点的值: c
3个顶点1条弧的有向网
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=d
G.arcs.adj:
  2147483647           1  2147483647
  2147483647  2147483647  2147483647
  2147483647  2147483647  2147483647
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该弧信息：
    a           b     1111
请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4):
4
请按任意键继续. . .


请顺序选择有向图,有向网,无向图,无向网
请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4):
2
请输入无向图G的顶点数,边数,边是否含其它信息(是:1,否:0):(空格区分) 3 3 0
请输入3个顶点的值(<5个字符):
a
b
c
请输入3条边的顶点1 顶点2(以空格作为间隔):
a b
a c
b c
3个顶点3条边的无向图
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.arcs.adj:
           0           1           1
           1           0           1
           1           1           0
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该边信息：
插入新顶点，请输入顶点的值: d
插入与新顶点有关的弧或边，请输入弧或边数: 1
请输入另一顶点的值: c
是否有该弧或边的相关信息(0:无 1:有):
0
4个顶点4条边的无向图
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.vexs[3]=d
G.arcs.adj:
           0           1           1           0
           1           0           1           0
           1           1           0           1
           0           0           1           0
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该边信息：
删除顶点及相关的弧或边，请输入顶点的值: b
3个顶点2条边的无向图
G.vexs[0]=a
G.vexs[1]=c
G.vexs[2]=d
G.arcs.adj:
           0           1           0
           1           0           1
           0           1           0
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该边信息：
请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4):
4
请按任意键继续. . .


请顺序选择有向图,有向网,无向图,无向网
请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4):
3
请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0):(空格区分) 3 3 0
请输入3个顶点的值(<5个字符):
a
b
c
请输入3条边的顶点1 顶点2 权值(以空格作为间隔):
a b 1
a c 2
b c 3
3个顶点3条边的无向网
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.arcs.adj:
  2147483647           1           2
           1  2147483647           3
           2           3  2147483647
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该边信息：
插入新顶点，请输入顶点的值: d
插入与新顶点有关的弧或边，请输入弧或边数: 1
请输入另一顶点的值: c
请输入此弧或边的权值: 4
是否有该弧或边的相关信息(0:无 1:有):
0
4个顶点4条边的无向网
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.vexs[3]=d
G.arcs.adj:
  2147483647           1           2  2147483647
           1  2147483647           3  2147483647
           2           3  2147483647           4
  2147483647  2147483647           4  2147483647
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该边信息：
删除顶点及相关的弧或边，请输入顶点的值: c
3个顶点1条边的无向网
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=d
G.arcs.adj:
  2147483647           1  2147483647
           1  2147483647  2147483647
  2147483647  2147483647  2147483647
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该边信息：
请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4):
4
请按任意键继续. . .


请输入数据文件名(1.txt)：1.txt
8个顶点14条边的无向图
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.vexs[3]=d
G.vexs[4]=e
G.vexs[5]=f
G.vexs[6]=g
G.vexs[7]=h
G.arcs.adj:
     0     1     1     0     0     0     0     0
     1     0     1     1     1     0     0     0
     1     1     0     1     0     0     0     1
     0     1     1     0     1     1     1     1
     0     1     0     1     0     1     0     0
     0     0     0     1     1     0     1     0
     0     0     0     1     0     1     0     1
     0     0     1     1     0     0     1     0
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该边信息：
深度优先搜索的结果:
a b c d e f g h
广度优先搜索的结果:
a b c d e h f g
删除一条边或弧，请输入待删除边或弧的弧尾 弧头：a b
8个顶点13条边的无向图
G.vexs[0]=a
G.vexs[1]=b
G.vexs[2]=c
G.vexs[3]=d
G.vexs[4]=e
G.vexs[5]=f
G.vexs[6]=g
G.vexs[7]=h
G.arcs.adj:
     0     0     1     0     0     0     0     0
     0     0     1     1     1     0     0     0
     1     1     0     1     0     0     0     1
     0     1     1     0     1     1     1     1
     0     1     0     1     0     1     0     0
     0     0     0     1     1     0     1     0
     0     0     0     1     0     1     0     1
     0     0     1     1     0     0     1     0
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该边信息：
修改顶点的值，请输入原值 新值: a i
8个顶点13条边的无向图
G.vexs[0]=i
G.vexs[1]=b
G.vexs[2]=c
G.vexs[3]=d
G.vexs[4]=e
G.vexs[5]=f
G.vexs[6]=g
G.vexs[7]=h
G.arcs.adj:
     0     0     1     0     0     0     0     0
     0     0     1     1     1     0     0     0
     1     1     0     1     0     0     0     1
     0     1     1     0     1     1     1     1
     0     1     0     1     0     1     0     0
     0     0     0     1     1     0     1     0
     0     0     0     1     0     1     0     1
     0     0     1     1     0     0     1     0
G.arcs.info:
顶点1(弧尾) 顶点2(弧头) 该边信息：
请按任意键继续. . .

*/ 
