#include <stdio.h>
#include <stdlib.h>

#include "st_graph_adjlist.h"
#include "st_queue.h"
#include "st_stack.h"



int visited[MAX_VERTEX_NUM];	// ���ʱ�־����(ȫ����) 
void(*VisitFunc)(char* v);		// ��������(ȫ����) 
int count; 						// ȫ����count�Է��ʼ��� 
int low[MAX_VERTEX_NUM];

// �ֲ��ӿ�����
static int LocateVex(ALGraph G,VertexType u);
static VertexType* GetVex(ALGraph G,int v);
static int FirstAdjVex(ALGraph G,VertexType v);
static int NextAdjVex(ALGraph G,VertexType v,VertexType w);
static void FindInDegree(ALGraph G,int indegree[]);
static void DFSArticul(ALGraph G,int v0);
static int TopologicalOrder(ALGraph G,GSqStack *T);


// �����ӿڶ���
// ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1�� ������hash����λ��
static int LocateVex(ALGraph G,VertexType u)
{
	int i;
	for(i=0;i<G.vexnum;++i)
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	return -1;
}

// �����ڽӱ�洢�ṹ,����û�������Ϣ��ͼG(��һ����������4��ͼ)��
int CreateGraph(ALGraph *G)
{
	int i,j,k;
	int w;		// Ȩֵ 
	VertexType va,vb;
	ArcNode *p;
	
	printf("������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3): ");
	scanf("%d",&(*G).kind);
	printf("������ͼ�Ķ������ͱ���:���ո�\n");
	scanf("%d%d", &(*G).vexnum, &(*G).arcnum);
	printf("������%d�������ֵ(<%d���ַ�):\n",(*G).vexnum,MAX_NAME);
	
	for(i = 0; i < (*G).vexnum; ++i)	// ���춥������ 
	{
		scanf("%s", (*G).vertices[i].data);
		(*G).vertices[i].firstarc = NULL;
	}
	
	if((*G).kind == 1 || (*G).kind == 3) // �� 
		printf("��˳������ÿ����(��)��Ȩֵ����β�ͻ�ͷ(�Կո���Ϊ���):\n");
	else // ͼ 
		printf("��˳������ÿ����(��)�Ļ�β�ͻ�ͷ(�Կո���Ϊ���):\n");
	
	for(k = 0;k < (*G).arcnum; ++k)	// ����������� 
	{
		if((*G).kind==1||(*G).kind==3) // �� 
			scanf("%d%s%s",&w,va,vb);
		else			// ͼ 
			scanf("%s%s",va,vb);
		
		i = LocateVex(*G,va); // ��β 
		j = LocateVex(*G,vb); // ��ͷ 
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		if((*G).kind == 1 || (*G).kind == 3) // �� 
		{
			p->info = (int *)malloc(sizeof(int));
			*(p->info) = w;
		}
		else
		{
			p->info = NULL; // ͼ 
		}
			
		p->nextarc = (*G).vertices[i].firstarc; // ���ڱ�ͷ 
		(*G).vertices[i].firstarc = p;

		if((*G).kind >= 2) // ����ͼ����,�����ڶ������� ����Ϊ����ͼ����Եģ�
		{
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			
			if((*G).kind == 3) // ������ 
			{
				p->info = (int*)malloc(sizeof(int));
				*(p->info) = w;
			}
			else
			{
				p->info = NULL; // ����ͼ 
			}
			
			p->nextarc = (*G).vertices[j].firstarc; // ���ڱ�ͷ 
			(*G).vertices[j].firstarc = p;
		}
	}
	return 1;
}

// ����ͼG��
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
			if((*G).kind%2) // �� 
				free(p->info);
			
			free(p);
			p=q;
		}
	}
	(*G).vexnum=0;
	(*G).arcnum=0;
 }

// �������v��ֵ��
static VertexType* GetVex(ALGraph G,int v)
{
	if(v>=G.vexnum||v<0)
		exit(0);
	return &G.vertices[v].data;
}

// ��v����ֵvalue��
int PutVex(ALGraph *G,VertexType v,VertexType value)
{
	int i;
	i=LocateVex(*G,v);
	if(i > -1) // v��G�Ķ��� 
	{
		strcpy((*G).vertices[i].data,value);
		return 1;
	}
	return 0;
}

// ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ���,�򷵻�-1��
static int FirstAdjVex(ALGraph G,VertexType v)
{
	ArcNode *p;
	int v1;
	
	v1 = LocateVex(G,v); // v1Ϊ����v��ͼG�е���� 
	p = G.vertices[v1].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}

// ����v��(�����w��)��һ���ڽӶ������š���w��v�����һ��
// �ڽӵ�,	�򷵻�-1��
static int NextAdjVex(ALGraph G,VertexType v,VertexType w)
{
	ArcNode *p;
	int v1,w1;
	
	v1 = LocateVex(G,v); // v1Ϊ����v��ͼG�е���� 
	w1 = LocateVex(G,w); // w1Ϊ����w��ͼG�е���� 
	p = G.vertices[v1].firstarc;
	while(p&&p->adjvex != w1) // ָ��p��������ָ���㲻��w 
		p = p->nextarc;
	
	if(!p||!p->nextarc) // û�ҵ�w��w�����һ���ڽӵ� 
		return -1;
	else // p->adjvex==w 
		// ����v��(�����w��)��һ���ڽӶ������� 
		return p->nextarc->adjvex;
}

// ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��)��
void InsertVex(ALGraph *G,VertexType v)
{   
	strcpy((*G).vertices[(*G).vexnum].data,v); // �����¶������� 
	(*G).vertices[(*G).vexnum].firstarc=NULL;
	(*G).vexnum++; // ͼG�Ķ�������1 
}

// ɾ��G�ж���v������صĻ���
int DeleteVex(ALGraph *G,VertexType v)
{
	int i,j;
	ArcNode *p,*q;
	
	j=LocateVex(*G,v);	// j�Ƕ���v����� 
	if(j < 0 )			// v����ͼG�Ķ��� 
		return 0;
	
	p = (*G).vertices[j].firstarc;	// ɾ����vΪ���ȵĻ���� 
	while( p )
	{
		q = p;
		p = p->nextarc;
		if((*G).kind % 2)	// �� 
			free(q->info);
		
		free(q);
		(*G).arcnum--;		// ���������1 
	}
	(*G).vexnum--;	// ��������1 
	for(i = j; i < (*G).vexnum; i++)	// ����v����Ķ���ǰ�� 
		(*G).vertices[i] = (*G).vertices[i+1];
	
	// ɾ����vΪ��ȵĻ�����ұ�Ҫʱ�޸ı���Ķ���λ��ֵ
	for(i = 0; i < (*G).vexnum; i++) 
	{
		p = (*G).vertices[i].firstarc; // ָ���1������� 
		while(p) // �л� 
		{
			if(p->adjvex == j)		// ����vΪ��ȵıߡ�
			{
				if(p == (*G).vertices[i].firstarc) // ��ɾ����ǵ�1����� 
				{
					(*G).vertices[i].firstarc = p->nextarc;
					if((*G).kind % 2)	// �� 
						free(p->info);
					free(p);
					p = (*G).vertices[i].firstarc;
					if((*G).kind < 2)	// ���� 
						(*G).arcnum--;	// ���������1 
				}
				else
				{
					q->nextarc = p->nextarc;
					if((*G).kind%2)	// �� 
						free(p->info);
					free(p);
					p = q->nextarc;
					if((*G).kind < 2)	// ���� 
						(*G).arcnum--;	// ���������1 
				}
			}
			else
			{
				if(p->adjvex > j)
					p->adjvex--; // �޸ı���Ķ���λ��ֵ(���) 
				q = p;
				p = p->nextarc;
			}
		}
	}
	return 1;
}

// ��G������<v,w>,��G�������,������Գƻ�<w,v>��
int InsertArc(ALGraph *G,VertexType v, VertexType w)
{
	ArcNode *p;
	int w1,i,j;
	i=LocateVex(*G,v); // ��β��ߵ���� 
	j=LocateVex(*G,w); // ��ͷ��ߵ���� 
	if(i < 0 || j < 0)
		return 0;
	
	(*G).arcnum++;	// ͼG�Ļ���ߵ���Ŀ��1 
	if((*G).kind%2) // �� 
	{
		printf("�����뻡(��)%s��%s��Ȩֵ: ",v,w);
		scanf("%d",&w1);
	}
	p=(ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex=j;
	if((*G).kind%2) // �� 
	{
		p->info=(int*)malloc(sizeof(int));
		*(p->info)=w1;
	}
	else
	{
		p->info = NULL;
	}
	p->nextarc = (*G).vertices[i].firstarc; // ���ڱ�ͷ 
	(*G).vertices[i].firstarc = p;
	if((*G).kind >= 2)	// ����,������һ������ 
	{
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		if((*G).kind == 3) // ������ 
		{
			p->info = (int*)malloc(sizeof(int));
			*(p->info) = w1;
		}
		else
		{
			p->info=NULL;
		}
		p->nextarc=(*G).vertices[j].firstarc; // ���ڱ�ͷ 
		(*G).vertices[j].firstarc=p;
	}
	return 1;
}

// ��G��ɾ����<v,w>,��G�������,��ɾ���Գƻ�<w,v>��
int DeleteArc(ALGraph *G,VertexType v,VertexType w)
{
	ArcNode *p,*q;
	int i,j;
	i = LocateVex(*G,v); // i�Ƕ���v(��β)����� 
	j = LocateVex(*G,w); // j�Ƕ���w(��ͷ)����� 
	if(i < 0 || j < 0 || i == j)
		return 0;
	p=(*G).vertices[i].firstarc; // pָ�򶥵�v�ĵ�һ������ 
	while(p&&p->adjvex!=j) // p��������ָ֮�����Ǵ�ɾ����<v,w> 
	{ // pָ����һ���� 
		q=p;
		p=p->nextarc;
	}
	if(p&&p->adjvex==j) // �ҵ���<v,w> 
	{
		if(p==(*G).vertices[i].firstarc) // p��ָ�ǵ�1���� 
			(*G).vertices[i].firstarc=p->nextarc; // ָ����һ���� 
		else
			q->nextarc=p->nextarc; // ָ����һ���� 
			
		if((*G).kind%2) // �� 
			free(p->info);
		free(p); // �ͷŴ˽�� 
		(*G).arcnum--; // ���������1 
	}
	if((*G).kind>=2) // ����,ɾ���Գƻ�<w,v> 
	{
		p=(*G).vertices[j].firstarc; // pָ϶���w�ĵ�һ������ 
		while(p&&p->adjvex!=i) // p��������ָ֮�����Ǵ�ɾ����<w,v> 
		{ // pָ����һ���� 
			q=p;
			p=p->nextarc;
		}
		if(p&&p->adjvex==i) // �ҵ���<w,v> 
		{
			if(p==(*G).vertices[j].firstarc) // p��ָ�ǵ�1���� 
				(*G).vertices[j].firstarc=p->nextarc; // ָ����һ���� 
			else
				q->nextarc=p->nextarc; // ָ����һ���� 
				
			if((*G).kind==3) // ������ 
				free(p->info);
			free(p); // �ͷŴ˽�� 
		}
	}
	return 1;
}

//	�ӵ�v����������ݹ��������ȱ���ͼG��
void DFS(ALGraph G,int v)
{
	int w;
	VertexType v1,w1;

	strcpy(v1,*GetVex(G,v));
	visited[v] = 1;	// ���÷��ʱ�־Ϊ1(�ѷ���) 
	VisitFunc(G.vertices[v].data); // ���ʵ�v������ 
	for(w = FirstAdjVex(G,v1); w >= 0; w = NextAdjVex(G,v1,strcpy(w1,*GetVex(G,w))))
		if(!visited[w])
			DFS(G,w);	// ��v����δ���ʵ��ڽӵ�w�ݹ����DFS 
}

//	�㷨7.4 P169
//	��ͼG��������ȱ�����
void DFSTraverse(ALGraph G,void(*Visit)(char*))
{
	int v;
	// ʹ��ȫ�ֱ���VisitFunc,ʹDFS�����躯��ָ�����
	VisitFunc = Visit; 
	
	for(v = 0; v < G.vexnum; v++)
		visited[v] = 0;	// ���ʱ�־�����ʼ�� 
	for(v = 0; v < G.vexnum; v++)
		if(!visited[v])
			DFS(G,v);		// ����δ���ʵĶ������DFS 
		printf("\n");
}

void BFSTraverse(ALGraph G,void(*Visit)(char*))
{
	int v,u,w;
	VertexType u1,w1;
	PSTQueue Q;
	
	for(v = 0; v < G.vexnum; ++v)
		visited[v]=0;	// �ó�ֵ 
	STInitialize_Q(&Q);			// �ÿյĸ�������Q 
	for(v = 0; v < G.vexnum; v++)	// �������ͨͼ,ֻv=0�ͱ���ȫͼ 
		if(!visited[v])				// v��δ���� 
		{
			visited[v]=1;
			Visit(G.vertices[v].data);
			STEnQueue_Q(&Q,v);			// v����� 
			while(!STIsEmpty_Q(Q))	// ���в��� 
			{
				STDeQueue_Q(&Q,&u);		// ��ͷԪ�س��Ӳ���Ϊu 
				strcpy(u1,*GetVex(G,u));
				for(w = FirstAdjVex(G,u1); w >= 0; w = NextAdjVex(G, u1, strcpy(w1, *GetVex(G,w))))
				{
					if(!visited[w])	// wΪu����δ���ʵ��ڽӶ��� 
					{
						visited[w] = 1;
						Visit(G.vertices[w].data);
						STEnQueue_Q(&Q,w);	// w��� 
					}
				}
			}
		}
		printf("\n");
}

//	���ͼ���ڽӱ�G��
void G_Display(ALGraph G)
{
	int i;
	ArcNode *p;

	switch(G.kind)
	{
	case DG: printf("����ͼ\n");
		break;
	case DN: printf("������\n");
		break;
	case AG: printf("����ͼ\n");
		break;
	case AN: printf("������\n");
	}
	printf("%d�����㣺\n",G.vexnum);
	for(i = 0; i < G.vexnum; ++i)
		printf("%s ",G.vertices[i].data);
	printf("\n%d����(��):\n", G.arcnum);
	for(i = 0; i < G.vexnum; i++)
	{
		p = G.vertices[i].firstarc;
		while(p)
		{
			if(G.kind <= 1) // ���� 
			{
				printf("%s��%s ",G.vertices[i].data,
					G.vertices[p->adjvex].data);
				if(G.kind == DN) // �� 
					printf(":%d ", *(p->info));
			}
			else	// ����(�����������) 
			{
				if(i < p->adjvex)
				{
					printf("%s��%s ",G.vertices[i].data,
						G.vertices[p->adjvex].data);
					if(G.kind == AN)	// �� 
						printf(":%d ",*(p->info));
				}
			}
			p=p->nextarc;
		}
		printf("\n");
	}
}

// �󶥵����ȣ�
static void FindInDegree(ALGraph G,int indegree[])
{ 
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
	indegree[i]=0; // ����ֵ 
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





// ����ͼG�����ڽӱ�洢�ṹ����G�޻�·,�����G�Ķ����һ��������
// �в�����1, ���򷵻�0��
int TopologicalSort(ALGraph G)
{
	int i,k,count,indegree[MAX_VERTEX_NUM];
	GSqStack S;
	ArcNode *p;
	
	FindInDegree(G,indegree); // �Ը����������indegree[0..vernum-1] 
	GInitStack(&S); // ��ʼ��ջ 
	for(i=0;i<G.vexnum;++i) // ������ȶ���ջS 
	{
		if(!indegree[i])
			GPush(&S,i); // ���Ϊ0�߽�ջ 
	}
	count=0; // ������������ 
	while(!GStackEmpty(S))
	{
		// ջ���� 
		GPop(&S,&i);
		printf("%s ",G.vertices[i].data); // ���i�Ŷ��㲢���� 
		++count;
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)
		{
			// ��i�Ŷ����ÿ���ڽӵ����ȼ�1 
			k=p->adjvex;
			if(!(--indegree[k])) // ����ȼ�Ϊ0,����ջ 
				GPush(&S,k);
		}
	}
	GFreeStack(&S);
	if(count<G.vexnum)
	{
		printf("������ͼ�л�·\n");
		return 0;
	}
	else
	{
		printf("Ϊһ���������С�\n");
		return 1;
	}
}

// �ӵ�v0���������������ȱ���ͼG�����Ҳ�����ؽڵ㡣
void DFSArticul(ALGraph G,int v0)
{
	int min,w;
	ArcNode *p;
	visited[v0]=min=++count; // v0�ǵ�count�����ʵĶ��� 
	for(p=G.vertices[v0].firstarc;p;p=p->nextarc) // ��v0��ÿ���ڽӶ����� 
	{
		w=p->adjvex; // wΪv0���ڽӶ��� 
		if(visited[w]==0) // wδ�����ʣ���v0�ĺ��� 
		{
			DFSArticul(G,w); // ����ǰ���low[w] 
			if(low[w]<min)
				min=low[w];
			if(low[w]>=visited[v0])
				printf("%d %s\n",v0,G.vertices[v0].data); // �ؽڵ� 
		}
		else if(visited[w]<min)
		min=visited[w]; // w�ѷ��ʣ�w��v0���������ϵ����� 
	}
	low[v0]=min;
}

// ��ͨͼG���ڽӱ����洢�ṹ�����Ҳ����G��ȫ���ؽڵ㡣 
// ȫ����count�Է��ʼ����� 
void FindArticul(ALGraph G)
{
	int i,v;
	ArcNode *p;
	count=1;
	low[0]=visited[0]=1; // �趨�ڽӱ���0�Ŷ���Ϊ�������ĸ� 
	for(i=1;i<G.vexnum;++i)
		visited[i]=0; // ���ඥ����δ���� 
	p=G.vertices[0].firstarc;
	v=p->adjvex;
	DFSArticul(G,v); // �ӵ�v�������������Ȳ��ҹؽڵ� 
	if(count<G.vexnum) // �������ĸ��������������� 
	{
		printf("%d %s\n",0,G.vertices[0].data); // ���ǹؽڵ㣬��� 
		while(p->nextarc)
		{
			p=p->nextarc;
			v=p->adjvex;
			if(visited[v]==0)
			DFSArticul(G,v);
		}
	}
}

// GΪ������,���G�ĸ���ؼ��

// ������G�����ڽӱ�洢�ṹ,��������¼������緢��ʱ��ve (ȫ�ֱ���)��
// TΪ�������ж���ջ,SΪ����ȶ���ջ����G�޻�·,����ջT����G��һ����
// ������,�Һ���ֵΪ1,����Ϊ0 
int ve[MAX_VERTEX_NUM]; // ȫ�ֱ���(�����㷨7.13���㷨7.14) 
int TopologicalOrder(ALGraph G,GSqStack *T)
{
	int j,k,count,indegree[MAX_VERTEX_NUM];
	GSqStack S;
	ArcNode *p;
	
	FindInDegree(G,indegree);//�Ը����������indegree[0..vernum-1] 
	GInitStack(&S); // ��ʼ��ջ 
	for(j=0;j<G.vexnum;++j) // ������ȶ���ջS 
		if(!indegree[j])
			GPush(&S,j); // ���Ϊ0�߽�ջ 
	GInitStack(T); // ��ʼ���������ж���ջ 
	count=0; // ������������ 
	for(j=0;j<G.vexnum;++j) // ��ʼ��ve[]=0 (��Сֵ) 
		ve[j]=0;
	while(!GStackEmpty(S))
	{
		// ջ���� 
		GPop(&S,&j);
		GPush(T,j); // j�Ŷ�����Tջ������ 
		++count;
		for(p=G.vertices[j].firstarc;p;p=p->nextarc)
		{
			// ��j�Ŷ����ÿ���ڽӵ����ȼ�1 
			k=p->adjvex;
			if(--indegree[k]==0) // ����ȼ�Ϊ0,����ջ 
				GPush(&S,k);
			if(ve[j]+*(p->info)>ve[k])
				ve[k]=ve[j]+*(p->info);
		}
	}
	if(count<G.vexnum)
	{
		printf("���������л�·\n");
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
	
	if(!TopologicalOrder(G,&T)) // �������� 
		return 0;
	j=ve[0];
	for(i=1;i<G.vexnum;i++) // j=Max(ve[]) ��ɵ��ֵ 
	{
		if(ve[i]>j)
			j=ve[i];
	}
	
	for(i=0;i<G.vexnum;i++) // ��ʼ�������¼�����ٷ���ʱ��(���ֵ) 
		vl[i]=j; // ��ɵ�����緢��ʱ�� 
	while(!GStackEmpty(T)) // ������������������vlֵ 
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
	for(j=0;j<G.vexnum;++j) // ��ee,el�͹ؼ�� 
	{
		for(p=G.vertices[j].firstarc;p;p=p->nextarc)
		{
			k=p->adjvex;
			dut=*(p->info);
			ee=ve[j];
			el=vl[k]-dut;
			tag=(ee==el)?'*':' ';
			// ����ؼ��
			printf("%2d %2d %3d %3d %3d    %c\n",j,k,dut,ee,el,tag); 
		}
	}
	printf("�ؼ��Ϊ:\n");
	for(j=0;j<G.vexnum;++j) // ͬ�� 
	{
		for(p=G.vertices[j].firstarc;p;p=p->nextarc)
		{
			k=p->adjvex;
			dut=*(p->info);
			if(ve[j]==vl[k]-dut)
				// ����ؼ�� 
				printf("%s��%s\n",G.vertices[j].data,G.vertices[k].data); 
		}
	}
	return 1;
}


// �������������
// �ӵ�v���������������ȱ���ͼG,������TΪ������������
void DFSTree(ALGraph G,int v,CSTree *T)
{
	int first = 1;
	int w;
	CSTree p,q;
	VertexType v1,w1;
	visited[v]=1;
	
	strcpy(v1, *GetVex(G,v));
	// w����Ϊv���ڽӶ��� 
	for(w = FirstAdjVex(G,v1); w >= 0; w = NextAdjVex(G,v1,strcpy(w1, *GetVex(G,w))))
	{
		if(!visited[w]) // w���㲻�������� 
		{
			p = (CSTree)malloc(sizeof(CSNode)); // ���亢�ӽ�� 
			strcpy(p->data, *GetVex(G,w));
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if(first)
			{
				// w��v�ĵ�һ��δ�����ʵ��ڽӶ��� 
				(*T)->firstchild=p;
				first=0; // �Ǹ��ĵ�һ�����ӽ�� 
			}
			else // w��v������δ�����ʵ��ڽӶ��� 
				q->nextsibling=p; // ����һ�ڽӶ�����ֵܽ��ý�� 
			q = p;
			DFSTree(G,w,&q); // �ӵ�w���������������ȱ���ͼG,������������q 
		}
	}
}

// �㷨7.7 P171
// ��������ͼG�������������ɭ�ֵ�(����)����(��)�ֵ�����T��
void DFSForest(ALGraph G,CSTree *T)
{  
	CSTree p,q;
	int v;
	*T=NULL;
	
	for(v=0;v<G.vexnum;++v)
		visited[v]=0; // ����ֵ 
	for(v=0;v<G.vexnum;++v) // �ӵ�0���������� 
		if(!visited[v])
		{
			// ��v����Ϊ�µ��������ĸ���� 
			p = (CSTree)malloc(sizeof(CSNode)); // �������� 
			strcpy(p->data, *GetVex(G,v));
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if(!*T)	// �ǵ�һ���������ĸ�(T�ĸ�) 
				*T = p;
			else	// �������������ĸ�(ǰһ�õĸ��ģ��ֵܣ�) 
				q->nextsibling = p;
			q = p;	// qָʾ��ǰ�������ĸ� 
			DFSTree(G,v,&p); // ������pΪ���������� 
		}
}

// �ȸ��������ӣ��ֵܶ�������ṹ����T
void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))
{
	if(T)
	{
		Visit(T->data); // �ȷ��ʸ���� 
		PreOrderTraverse(T->firstchild,Visit); // ���ȸ������������� 
		PreOrderTraverse(T->nextsibling,Visit); // ����ȸ�������һ���ֵ����� 
	}
}




