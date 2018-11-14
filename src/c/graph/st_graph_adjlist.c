#include <stdio.h>
#include <stdlib.h>

#include "st_graph_adjlist.h"
#include "st_queue.h"
#include "st_stack.h"



int visited[MAX_VERTEX_NUM];	// 访问标志数组(全局量) 
void(*VisitFunc)(char* v);		// 函数变量(全局量) 
int count; 						// 全局量count对访问计数 
int low[MAX_VERTEX_NUM];

// 局部接口声明
static int LocateVex(ALGraph G,VertexType u);
static VertexType* GetVex(ALGraph G,int v);
static int FirstAdjVex(ALGraph G,VertexType v);
static int NextAdjVex(ALGraph G,VertexType v,VertexType w);
static void FindInDegree(ALGraph G,int indegree[]);
static void DFSArticul(ALGraph G,int v0);
static int TopologicalOrder(ALGraph G,GSqStack *T);


// 函数接口定义
// 若G中存在顶点u,则返回该顶点在图中位置;否则返回-1。 可以用hash来找位置
static int LocateVex(ALGraph G,VertexType u)
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
		{
			p->info = NULL; // 图 
		}
			
		p->nextarc = (*G).vertices[i].firstarc; // 插在表头 
		(*G).vertices[i].firstarc = p;

		if((*G).kind >= 2) // 无向图或网,产生第二个表结点 ，因为无向图是相对的！
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			
			if((*G).kind == 3) // 无向网 
			{
				p->info = (int*)malloc(sizeof(int));
				*(p->info) = w;
			}
			else
			{
				p->info = NULL; // 无向图 
			}
			
			p->nextarc = (*G).vertices[j].firstarc; // 插在表头 
			(*G).vertices[j].firstarc = p;
		}
	}
	return 1;
}

// 销毁图G。
void DestroyGraph(ALGraph *G)
{
	int i;
	ArcNode *p,*q;
	for(i = 0;i < (*G).vexnum; ++i)
	{
		p = (*G).vertices[i].firstarc;
		while(p)
		{
			q = p->nextarc;
			if((*G).kind%2) // 网 
				free(p->info);
			
			free(p);
			p=q;
		}
	}
	(*G).vexnum=0;
	(*G).arcnum=0;
 }

// 返回序号v的值。
static VertexType* GetVex(ALGraph G,int v)
{
	if(v>=G.vexnum||v<0)
		exit(0);
	return &G.vertices[v].data;
}

// 对v赋新值value。
int PutVex(ALGraph *G,VertexType v,VertexType value)
{
	int i;
	i=LocateVex(*G,v);
	if(i > -1) // v是G的顶点 
	{
		strcpy((*G).vertices[i].data,value);
		return 1;
	}
	return 0;
}

// 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1。
static int FirstAdjVex(ALGraph G,VertexType v)
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
static int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{
	ArcNode *p;
	int v1,w1;
	
	v1 = LocateVex(G,v); // v1为顶点v在图G中的序号 
	w1 = LocateVex(G,w); // w1为顶点w在图G中的序号 
	p = G.vertices[v1].firstarc;
	while(p&&p->adjvex != w1) // 指针p不空且所指表结点不是w 
		p = p->nextarc;
	
	if(!p||!p->nextarc) // 没找到w或w是最后一个邻接点 
		return -1;
	else // p->adjvex==w 
		// 返回v的(相对于w的)下一个邻接顶点的序号 
		return p->nextarc->adjvex;
}

// 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做)。
void InsertVex(ALGraph *G,VertexType v)
{   
	strcpy((*G).vertices[(*G).vexnum].data,v); // 构造新顶点向量 
	(*G).vertices[(*G).vexnum].firstarc=NULL;
	(*G).vexnum++; // 图G的顶点数加1 
}

// 删除G中顶点v及其相关的弧。
int DeleteVex(ALGraph *G,VertexType v)
{
	int i,j;
	ArcNode *p,*q;
	
	j=LocateVex(*G,v);	// j是顶点v的序号 
	if(j < 0 )			// v不是图G的顶点 
		return 0;
	
	p = (*G).vertices[j].firstarc;	// 删除以v为出度的弧或边 
	while( p )
	{
		q = p;
		p = p->nextarc;
		if((*G).kind % 2)	// 网 
			free(q->info);
		
		free(q);
		(*G).arcnum--;		// 弧或边数减1 
	}
	(*G).vexnum--;	// 顶点数减1 
	for(i = j; i < (*G).vexnum; i++)	// 顶点v后面的顶点前移 
		(*G).vertices[i] = (*G).vertices[i+1];
	
	// 删除以v为入度的弧或边且必要时修改表结点的顶点位置值
	for(i = 0; i < (*G).vexnum; i++) 
	{
		p = (*G).vertices[i].firstarc; // 指向第1条弧或边 
		while(p) // 有弧 
		{
			if(p->adjvex == j)		// 是以v为入度的边。
			{
				if(p == (*G).vertices[i].firstarc) // 待删结点是第1个结点 
				{
					(*G).vertices[i].firstarc = p->nextarc;
					if((*G).kind % 2)	// 网 
						free(p->info);
					free(p);
					p = (*G).vertices[i].firstarc;
					if((*G).kind < 2)	// 有向 
						(*G).arcnum--;	// 弧或边数减1 
				}
				else
				{
					q->nextarc = p->nextarc;
					if((*G).kind%2)	// 网 
						free(p->info);
					free(p);
					p = q->nextarc;
					if((*G).kind < 2)	// 有向 
						(*G).arcnum--;	// 弧或边数减1 
				}
			}
			else
			{
				if(p->adjvex > j)
					p->adjvex--; // 修改表结点的顶点位置值(序号) 
				q = p;
				p = p->nextarc;
			}
		}
	}
	return 1;
}

// 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v>。
int InsertArc(ALGraph *G,VertexType v, VertexType w)
{
	ArcNode *p;
	int w1,i,j;
	i=LocateVex(*G,v); // 弧尾或边的序号 
	j=LocateVex(*G,w); // 弧头或边的序号 
	if(i < 0 || j < 0)
		return 0;
	
	(*G).arcnum++;	// 图G的弧或边的数目加1 
	if((*G).kind%2) // 网 
	{
		printf("请输入弧(边)%s→%s的权值: ",v,w);
		scanf("%d",&w1);
	}
	p=(ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex=j;
	if((*G).kind%2) // 网 
	{
		p->info=(int*)malloc(sizeof(int));
		*(p->info)=w1;
	}
	else
	{
		p->info = NULL;
	}
	p->nextarc = (*G).vertices[i].firstarc; // 插在表头 
	(*G).vertices[i].firstarc = p;
	if((*G).kind >= 2)	// 无向,生成另一个表结点 
	{
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		if((*G).kind == 3) // 无向网 
		{
			p->info = (int*)malloc(sizeof(int));
			*(p->info) = w1;
		}
		else
		{
			p->info=NULL;
		}
		p->nextarc=(*G).vertices[j].firstarc; // 插在表头 
		(*G).vertices[j].firstarc=p;
	}
	return 1;
}

// 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v>。
int DeleteArc(ALGraph *G,VertexType v,VertexType w)
{
	ArcNode *p,*q;
	int i,j;
	i = LocateVex(*G,v); // i是顶点v(弧尾)的序号 
	j = LocateVex(*G,w); // j是顶点w(弧头)的序号 
	if(i < 0 || j < 0 || i == j)
		return 0;
	p=(*G).vertices[i].firstarc; // p指向顶点v的第一条出弧 
	while(p&&p->adjvex!=j) // p不空且所指之弧不是待删除弧<v,w> 
	{ // p指向下一条弧 
		q=p;
		p=p->nextarc;
	}
	if(p&&p->adjvex==j) // 找到弧<v,w> 
	{
		if(p==(*G).vertices[i].firstarc) // p所指是第1条弧 
			(*G).vertices[i].firstarc=p->nextarc; // 指向下一条弧 
		else
			q->nextarc=p->nextarc; // 指向下一条弧 
			
		if((*G).kind%2) // 网 
			free(p->info);
		free(p); // 释放此结点 
		(*G).arcnum--; // 弧或边数减1 
	}
	if((*G).kind>=2) // 无向,删除对称弧<w,v> 
	{
		p=(*G).vertices[j].firstarc; // p指隙サ鉾的第一条出弧 
		while(p&&p->adjvex!=i) // p不空且所指之弧不是待删除弧<w,v> 
		{ // p指向下一条弧 
			q=p;
			p=p->nextarc;
		}
		if(p&&p->adjvex==i) // 找到弧<w,v> 
		{
			if(p==(*G).vertices[j].firstarc) // p所指是第1条弧 
				(*G).vertices[j].firstarc=p->nextarc; // 指向下一条弧 
			else
				q->nextarc=p->nextarc; // 指向下一条弧 
				
			if((*G).kind==3) // 无向网 
				free(p->info);
			free(p); // 释放此结点 
		}
	}
	return 1;
}

//	从第v个顶点出发递归地深度优先遍历图G。
void DFS(ALGraph G,int v)
{
	int w;
	VertexType v1,w1;

	strcpy(v1,*GetVex(G,v));
	visited[v] = 1;	// 设置访问标志为1(已访问) 
	VisitFunc(G.vertices[v].data); // 访问第v个顶点 
	for(w = FirstAdjVex(G,v1); w >= 0; w = NextAdjVex(G,v1,strcpy(w1,*GetVex(G,w))))
		if(!visited[w])
			DFS(G,w);	// 对v的尚未访问的邻接点w递归调用DFS 
}

//	算法7.4 P169
//	对图G作深度优先遍历。
void DFSTraverse(ALGraph G,void(*Visit)(char*))
{
	int v;
	// 使用全局变量VisitFunc,使DFS不必设函数指针参数
	VisitFunc = Visit; 
	
	for(v = 0; v < G.vexnum; v++)
		visited[v] = 0;	// 访问标志数组初始化 
	for(v = 0; v < G.vexnum; v++)
		if(!visited[v])
			DFS(G,v);		// 对尚未访问的顶点调用DFS 
		printf("\n");
}

void BFSTraverse(ALGraph G,void(*Visit)(char*))
{
	int v,u,w;
	VertexType u1,w1;
	PSTQueue Q;
	
	for(v = 0; v < G.vexnum; ++v)
		visited[v]=0;	// 置初值 
	STInitialize_Q(&Q);			// 置空的辅助队列Q 
	for(v = 0; v < G.vexnum; v++)	// 如果是连通图,只v=0就遍历全图 
		if(!visited[v])				// v尚未访问 
		{
			visited[v]=1;
			Visit(G.vertices[v].data);
			STEnQueue_Q(&Q,v);			// v入队列 
			while(!STIsEmpty_Q(Q))	// 队列不空 
			{
				STDeQueue_Q(&Q,&u);		// 队头元素出队并置为u 
				strcpy(u1,*GetVex(G,u));
				for(w = FirstAdjVex(G,u1); w >= 0; w = NextAdjVex(G, u1, strcpy(w1, *GetVex(G,w))))
				{
					if(!visited[w])	// w为u的尚未访问的邻接顶点 
					{
						visited[w] = 1;
						Visit(G.vertices[w].data);
						STEnQueue_Q(&Q,w);	// w入队 
					}
				}
			}
		}
		printf("\n");
}

//	输出图的邻接表G。
void G_Display(ALGraph G)
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

// 求顶点的入度，
static void FindInDegree(ALGraph G,int indegree[])
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





// 有向图G采用邻接表存储结构。若G无回路,则输出G的顶点的一个拓扑序
// 列并返回1, 否则返回0。
int TopologicalSort(ALGraph G)
{
	int i,k,count,indegree[MAX_VERTEX_NUM];
	GSqStack S;
	ArcNode *p;
	
	FindInDegree(G,indegree); // 对各顶点求入度indegree[0..vernum-1] 
	GInitStack(&S); // 初始化栈 
	for(i=0;i<G.vexnum;++i) // 建零入度顶点栈S 
	{
		if(!indegree[i])
			GPush(&S,i); // 入度为0者进栈 
	}
	count=0; // 对输出顶点计数 
	while(!GStackEmpty(S))
	{
		// 栈不空 
		GPop(&S,&i);
		printf("%s ",G.vertices[i].data); // 输出i号顶点并计数 
		++count;
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)
		{
			// 对i号顶点的每个邻接点的入度减1 
			k=p->adjvex;
			if(!(--indegree[k])) // 若入度减为0,则入栈 
				GPush(&S,k);
		}
	}
	GFreeStack(&S);
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

// G为有向网,输出G的各项关键活动

// 有向网G采用邻接表存储结构,求各顶点事件的最早发生时间ve (全局变量)。
// T为拓扑序列顶点栈,S为零入度顶点栈。若G无回路,则用栈T返回G的一个拓
// 扑序列,且函数值为1,否则为0 
int ve[MAX_VERTEX_NUM]; // 全局变量(用于算法7.13和算法7.14) 
int TopologicalOrder(ALGraph G,GSqStack *T)
{
	int j,k,count,indegree[MAX_VERTEX_NUM];
	GSqStack S;
	ArcNode *p;
	
	FindInDegree(G,indegree);//对各顶点求入度indegree[0..vernum-1] 
	GInitStack(&S); // 初始化栈 
	for(j=0;j<G.vexnum;++j) // 建零入度顶点栈S 
		if(!indegree[j])
			GPush(&S,j); // 入度为0者进栈 
	GInitStack(T); // 初始化拓扑序列顶点栈 
	count=0; // 对输出顶点计数 
	for(j=0;j<G.vexnum;++j) // 初始化ve[]=0 (最小值) 
		ve[j]=0;
	while(!GStackEmpty(S))
	{
		// 栈不空 
		GPop(&S,&j);
		GPush(T,j); // j号顶点入T栈并计数 
		++count;
		for(p=G.vertices[j].firstarc;p;p=p->nextarc)
		{
			// 对j号顶点的每个邻接点的入度减1 
			k=p->adjvex;
			if(--indegree[k]==0) // 若入度减为0,则入栈 
				GPush(&S,k);
			if(ve[j]+*(p->info)>ve[k])
				ve[k]=ve[j]+*(p->info);
		}
	}
	if(count<G.vexnum)
	{
		printf("此有向网有回路\n");
		return 0;
	}
	else
		return 1;
}


int CriticalPath(ALGraph G)
{ 
	int vl[MAX_VERTEX_NUM];
	GSqStack T;
	int i,j,k,ee,el;
	ArcNode *p;
	char dut,tag;
	
	if(!TopologicalOrder(G,&T)) // 产生有向环 
		return 0;
	j=ve[0];
	for(i=1;i<G.vexnum;i++) // j=Max(ve[]) 完成点的值 
	{
		if(ve[i]>j)
			j=ve[i];
	}
	
	for(i=0;i<G.vexnum;i++) // 初始化顶点事件的最迟发生时间(最大值) 
		vl[i]=j; // 完成点的最早发生时间 
	while(!GStackEmpty(T)) // 按拓扑逆序求各顶点的vl值 
	{
		for(GPop(&T,&j),p=G.vertices[j].firstarc;p;p=p->nextarc)
		{
			k=p->adjvex;
			dut=*(p->info); // dut<j,k> 
			if(vl[k]-dut<vl[j])
				vl[j]=vl[k]-dut;
		}
	}
	printf(" j  k  dut  ee  el  tag\n");
	for(j=0;j<G.vexnum;++j) // 求ee,el和关键活动 
	{
		for(p=G.vertices[j].firstarc;p;p=p->nextarc)
		{
			k=p->adjvex;
			dut=*(p->info);
			ee=ve[j];
			el=vl[k]-dut;
			tag=(ee==el)?'*':' ';
			// 输出关键活动
			printf("%2d %2d %3d %3d %3d    %c\n",j,k,dut,ee,el,tag); 
		}
	}
	printf("关键活动为:\n");
	for(j=0;j<G.vexnum;++j) // 同上 
	{
		for(p=G.vertices[j].firstarc;p;p=p->nextarc)
		{
			k=p->adjvex;
			dut=*(p->info);
			if(ve[j]==vl[k]-dut)
				// 输出关键活动 
				printf("%s→%s\n",G.vertices[j].data,G.vertices[k].data); 
		}
	}
	return 1;
}


// 深度优先生成树
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
	for(w = FirstAdjVex(G,v1); w >= 0; w = NextAdjVex(G,v1,strcpy(w1, *GetVex(G,w))))
	{
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




