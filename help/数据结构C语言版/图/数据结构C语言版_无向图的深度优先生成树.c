/*
	数据结构C语言版 无向图的深度优先生成树
	P171
	编译环境：
	Dev-C++ 4.9.9.2(测试失败)
	VC++6.0测试成功
	日期：2011年2月15日
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
// algo7-1.c 调用算法7.7、7.8 

#define MAX_NAME 5 // 顶点字符串的最大长度+1 

typedef char ElemType[MAX_NAME];
typedef ElemType TElemType;

 // 树的二叉链表(孩子－兄弟)存储表示 
typedef struct CSNode
{
	TElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;


// 图的邻接表存储表示  
typedef char VertexType[MAX_NAME];	// 字符串类型 
#define MAX_VERTEX_NUM 10

typedef struct ArcNode
{
	int adjvex;					// 该弧所指向的顶点的位置 
	struct ArcNode *nextarc;	// 指向下一条弧的指针 
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



// 返回v的值。
VertexType* GetVex(ALGraph G,int v)
{
	if(v >= G.vexnum || v<0)
		exit(0);
	return &G.vertices[v].data;
}

// 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1。 
int LocateVex(ALGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	return -1;
}

// 采用邻接表存储结构,构造没有相关信息的图G
int CreateGraph(ALGraph *G)
{
	int i,j,k;
	VertexType va,vb;
	ArcNode *p;
	
	printf("请输入图的顶点数和边数:（空格区分）\n");
	scanf("%d%d", &(*G).vexnum, &(*G).arcnum);
	fflush(stdin); 
	printf("请输入%d个顶点的值(<%d个字符):(回车区分)\n", (*G).vexnum,MAX_NAME);
	for(i = 0; i < (*G).vexnum; ++i)	// 构造顶点向量 
	{
		scanf("%s", (*G).vertices[i].data);
		(*G).vertices[i].firstarc = NULL;
	}
	printf("请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔):\n");
	for(k = 0;k < (*G).arcnum; ++k)	// 构造表结点链表 
	{
		scanf("%s%s",va,vb);
		i = LocateVex(*G,va); // 弧尾 
		j = LocateVex(*G,vb); // 弧头 
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextarc = (*G).vertices[i].firstarc; // 插在表头 
		(*G).vertices[i].firstarc = p;
		
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		p->nextarc = (*G).vertices[j].firstarc; // 插在表头 
		(*G).vertices[j].firstarc = p;	
	}
	return 1;
}

//	输出图
void Display(ALGraph G)
{
	int i;
	ArcNode *p;

	printf("无向图\n");
	printf("%d个顶点：\n",G.vexnum);
	for(i = 0; i < G.vexnum; ++i)
		printf("%s ",G.vertices[i].data);
	printf("\n%d条弧(边):\n", G.arcnum);
	for(i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			if(i < p->adjvex)
				printf("%s－%s\n",G.vertices[i].data,
					G.vertices[p->adjvex].data);
			p=p->nextarc;
		}
	}
}

// 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1。
int FirstAdjVex(ALGraph G,VertexType v)
{
	ArcNode *p;
	int v1;
	
	v1 = LocateVex(G,v); // v1为顶点v在图G中的序号 
	p = G.vertices[v1].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}

// 返回v的(相对于w的)下一个邻接顶点的序号。若w是v的最后一个
// 邻接点,	则返回-1。
int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{
	ArcNode *p;
	int v1,w1;
	
	v1 = LocateVex(G,v); // v1为顶点v在图G中的序号 
	w1 = LocateVex(G,w); // w1为顶点w在图G中的序号 
	p = G.vertices[v1].firstarc;
	while(p && p->adjvex != w1) // 指针p不空且所指表结点不是w 
		p = p->nextarc;
	if(!p||!p->nextarc) // 没找到w或w是最后一个邻接点 
		return -1;
	else // p->adjvex==w 
		return p->nextarc->adjvex; // 返回v的(相对于w的)下一个邻接顶点的序号 
}

int visited[MAX_VERTEX_NUM];	// 访问标志数组(全局量) 
void(*VisitFunc)(char* v);		// 函数变量(全局量) 

// 算法7.8 P172
// 从第v个顶点出发深度优先遍历图G,建立以T为根的生成树。
void DFSTree(ALGraph G,int v,CSTree *T)
{
	int first = 1;
	int w;
	CSTree p,q;
	VertexType v1,w1;
	visited[v]=1;
	
	strcpy(v1, *GetVex(G,v));
	// w依次为v的邻接顶点 
	for(w = FirstAdjVex(G,v1); w >= 0; 
			w = NextAdjVex(G,v1,strcpy(w1, *GetVex(G,w))))
		if(!visited[w]) // w顶点不曾被访问 
		{
			p = (CSTree)malloc(sizeof(CSNode)); // 分配孩子结点 
			strcpy(p->data, *GetVex(G,w));
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if(first)
			{
				// w是v的第一个未被访问的邻接顶点 
				(*T)->firstchild=p;
				first=0; // 是根的第一个孩子结点 
			}
			else // w是v的其它未被访问的邻接顶点 
				q->nextsibling=p; // 是上一邻接顶点的兄弟姐妹结点 
			q = p;
			DFSTree(G,w,&q); // 从第w个顶点出发深度优先遍历图G,建立子生成树q 
		}
}

// 算法7.7 P171
// 建立无向图G的深度优先生成森林的(最左)孩子(右)兄弟链表T。
void DFSForest(ALGraph G,CSTree *T)
{  
	CSTree p,q;
	int v;
	*T=NULL;
	
	for(v=0;v<G.vexnum;++v)
		visited[v]=0; // 赋初值 
	for(v=0;v<G.vexnum;++v) // 从第0个顶点找起 
		if(!visited[v])
		{
			// 第v顶点为新的生成树的根结点 
			p = (CSTree)malloc(sizeof(CSNode)); // 分配根结点 
			strcpy(p->data, *GetVex(G,v));
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if(!*T)	// 是第一棵生成树的根(T的根) 
				*T = p;
			else	// 是其它生成树的根(前一棵的根的＂兄弟＂) 
				q->nextsibling = p;
			q = p;	// q指示当前生成树的根 
			DFSTree(G,v,&p); // 建立以p为根的生成树 
		}
}

// 先根遍历孩子－兄弟二叉链表结构的树T
void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))
{
	if(T)
	{
		Visit(T->data); // 先访问根结点 
		PreOrderTraverse(T->firstchild,Visit); // 再先根遍历长子子树 
		PreOrderTraverse(T->nextsibling,Visit); // 最后先根遍历下一个兄弟子树 
	}
}

void print(TElemType i)
{
	printf("%s ", i);
}

int main()
{
	ALGraph g;
	CSTree t;
	
	CreateGraph(&g);
	Display(g);
	DFSForest(g,&t);
	printf("先根遍历生成森林：\n");
	PreOrderTraverse(t,print);
	printf("\n");
	
	system("pause");
	return 0;
}

/*
输出效果：

请输入图的顶点数和边数:（空格区分）
3 2
请输入3个顶点的值(<5个字符):(回车区分)
a
b
c
请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔):
a b
a c
无向图
3个顶点：
a b c
2条弧(边):
a－c
a－b
先根遍历生成森林：
a c b
请按任意键继续. . .


*/