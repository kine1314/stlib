/*
	数据结构C语言版 拓扑排序 
	P182
	编译环境：Dev-C++ 4.9.9.2
	日期：2011年2月15日 
*/
#include <stdio.h>
#include <malloc.h>

//  输出有向图的一个拓扑序列。实现算法7.12的程序 
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

//	输出图的邻接表G。
void Display(ALGraph G)
{
	int i;
	ArcNode *p;

	switch(G.kind)
	{
	case DG: printf("有向图\n");
		break;
	case DN: printf("有向网\n");
		break;
	case AG: printf("无向图\n");
		break;
	case AN: printf("无向网\n");
	}
	printf("%d个顶点：\n",G.vexnum);
	for(i = 0; i < G.vexnum; ++i)
		printf("%s ",G.vertices[i].data);
	printf("\n%d条弧(边):\n", G.arcnum);
	for(i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			if(G.kind <= 1) // 有向 
			{
				printf("%s→%s ",G.vertices[i].data,
					G.vertices[p->adjvex].data);
				if(G.kind == DN) // 网 
					printf(":%d ", *(p->info));
			}
			else	// 无向(避免输出两次) 
			{
				if(i < p->adjvex)
				{
					printf("%s－%s ",G.vertices[i].data,
						G.vertices[p->adjvex].data);
					if(G.kind == AN)	// 网 
						printf(":%d ",*(p->info));
				}
			}
			p=p->nextarc;
		}
		printf("\n");
	}
}

// 求顶点的入度，算法7.12、7.13调用
void FindInDegree(ALGraph G,int indegree[])
{ 
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
	indegree[i]=0; // 赋初值 
	for(i=0;i<G.vexnum;i++)
	{
		p=G.vertices[i].firstarc;
		while(p)
		{
			indegree[p->adjvex]++;
			p=p->nextarc;
		}
	}
}

typedef int SElemType; // 栈类型 

#define STACK_INIT_SIZE 10	// 存储空间初始分配量 
#define STACKINCREMENT 2	// 存储空间分配增量 
// 栈的顺序存储表示 P46 
typedef struct SqStack
{
	SElemType *base;	// 在栈构造之前和销毁之后，base的值为NULL 
	SElemType *top;		// 栈顶指针 
	int stacksize;		// 当前已分配的存储空间，以元素为单位 
}SqStack;	// 顺序栈



//	构造一个空栈S。
int InitStack(SqStack *S)
{
	// 为栈底分配一个指定大小的存储空间
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if( !(*S).base )
		exit(0);		// 存储分配失败 
	(*S).top = (*S).base;	// 栈底与栈顶相同表示一个空栈
	(*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

// 若栈S为空栈（栈顶与栈底相同的），则返回1，否则返回0。
int StackEmpty(SqStack S)
{
	if(S.top == S.base)
		return 1;
	else
		return 0;
}

//	插入元素e为新的栈顶元素。
int Push(SqStack *S, SElemType e)
{
	if((*S).top - (*S).base >= (*S).stacksize)	// 栈满，追加存储空间 
	{
		(*S).base = (SElemType *)realloc((*S).base, 
			((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if( !(*S).base )
			exit(0); // 存储分配失败 
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++=e;
	// 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

//	若栈不空，则删除S的栈顶元素，用e返回其值，并返回1；否则返回0。
int Pop(SqStack *S,SElemType *e)
{
	if((*S).top == (*S).base)
		return 0;
	*e = *--(*S).top;
	// 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

// 算法7.12 P182
// 有向图G采用邻接表存储结构。若G无回路,则输出G的顶点的一个拓扑序
// 列并返回1, 否则返回0。
int TopologicalSort(ALGraph G)
{
	int i,k,count,indegree[MAX_VERTEX_NUM];
	SqStack S;
	ArcNode *p;
	
	FindInDegree(G,indegree); // 对各顶点求入度indegree[0..vernum-1] 
	InitStack(&S); // 初始化栈 
	for(i=0;i<G.vexnum;++i) // 建零入度顶点栈S 
		if(!indegree[i])
			Push(&S,i); // 入度为0者进栈 
	count=0; // 对输出顶点计数 
	while(!StackEmpty(S))
	{
		// 栈不空 
		Pop(&S,&i);
		printf("%s ",G.vertices[i].data); // 输出i号顶点并计数 
		++count;
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)
		{
			// 对i号顶点的每个邻接点的入度减1 
			k=p->adjvex;
			if(!(--indegree[k])) // 若入度减为0,则入栈 
			Push(&S,k);
		}
	}
	if(count<G.vexnum)
	{
		printf("此有向图有回路\n");
		return 0;
	}
	else
	{
		printf("为一个拓扑序列。\n");
		return 1;
	}
}

int main()
{
	ALGraph f;
	printf("请选择有向图\n");
	CreateGraph(&f);
	Display(f);
	TopologicalSort(f);
	
	system("pause");
	return 0; 
}
/*
输出效果：

请选择有向图
请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3): 0
请输入图的顶点数和边数:（空格）
4 4
请输入4个顶点的值(<3个字符):
a
b
c
d
请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔):
a b
a c
b d
c d
有向图
4个顶点：
a b c d
4条弧(边):
a→c a→b
b→d
c→d

a b c d 为一个拓扑序列。
请按任意键继续. . . 

*/ 
