#include <iostream>
#include<stdio.h>
#include <malloc.h>

using namespace std; 
#define int_max 10000
#define inf 9999 
#define max 20

typedef struct ArcCell
{
	int adj;
	char *info;
}ArcCell,AdjMatrix[max][max];

typedef struct 
{
	char vexs[max];
	AdjMatrix arcs;
	int vexnum,arcnum;
}MGraph_L;

int localvex(MGraph_L G,char v)
{
	int i=0;

	while(G.vexs[i]!=v)
	{
		++i;
	}
	return i;
}

int creatMGraph_L(MGraph_L &G)
{
	char v1,v2;
	int i,j,w;
	cout<<"                        *****以下是Kruskal算法演示*****"<<endl<<"编写人：孙伟伟      学号：20082547"<<endl;
	cout<<"请输入图G顶点和弧的个数，以回车键结束:"<<endl;
	cin>>G.vexnum>>G.arcnum;
	for(i=0;i!=G.vexnum;++i)
	{
		cout<<"输入顶点"<<i<<endl;
		cin>>G.vexs[i];
	}
	for(i=0;i!=G.vexnum;++i)
	{
		for(j=0;j!=G.vexnum;++j)
		{ 
			G.arcs[i][j].adj=int_max;
			G.arcs[i][j].info=NULL;
		}
	}

	for(int k=0;k!=G.arcnum;++k)
	{ 
		cout<<"输入一条边依附的顶点和权（两个顶点和权分别用空格隔开，以回车结束）:"<<endl;
		cin>>v1>>v2>>w;
		i=localvex(G,v1);
		j=localvex(G,v2);
		G.arcs[i][j].adj=w;
		G.arcs[j][i].adj=w;
	}
	return G.vexnum;
}

int visited[max];
int we;
typedef struct arcnode
{
	int adjvex;
	struct arcnode *nextarc;
	char *info;
}arcnode;
typedef struct vnode
{
	char data;
	arcnode *firstarc;
}vnode,adjlist;

typedef struct
{
	adjlist vertices[max];
	int vexnum,arcnum;
	int kind;
}algraph;

typedef struct qnode
{
	int data;
	struct qnode *next;
}qnode,*queueptr;

typedef struct
{
	queueptr front;
	queueptr rear;
}linkqueue;

typedef struct acr
{
	int pre;
	int bak;
	int weight;
}edg;


int creatadj(algraph &gra,MGraph_L G)
{
	int i=0,j=0;
	arcnode *arc,*tem,*p;
	for(i=0;i!=G.vexnum;++i)
	{
		gra.vertices[i].data=G.vexs[i];
		gra.vertices[i].firstarc=NULL;
	}
	for(i=0;i!=G.vexnum;++i)
	{
		for(j=0;j!=G.vexnum;++j)
		{
			if(gra.vertices[i].firstarc==NULL)
			{
				if(G.arcs[i][j].adj!=int_max&&j!=G.vexnum)
				{
					arc=(arcnode *)malloc(sizeof(arcnode));
					arc->adjvex=j;
					gra.vertices[i].firstarc=arc;
					arc->nextarc=NULL;
					p=arc;
					++j;
					while(G.arcs[i][j].adj!=int_max&&j!=G.vexnum)
					{
						tem=(arcnode *)malloc(sizeof(arcnode));
						tem->adjvex=j;    
						gra.vertices[i].firstarc=tem;
						tem->nextarc=arc;
						arc=tem;
						++j;
					}
					--j;
				}
			}
			else
			{
				if(G.arcs[i][j].adj!=int_max&&j!=G.vexnum)
				{
					arc=(arcnode *)malloc(sizeof(arcnode));
					arc->adjvex=j;
					p->nextarc=arc;
					arc->nextarc=NULL;
					p=arc;
				}
			}
		}
	}
	gra.vexnum=G.vexnum;
	gra.arcnum=G.arcnum;
	return 1;
}

int acrvisited[100];
int find(int acrvisited[],int f)
{
	while(acrvisited[f]>0)
	{
		f=acrvisited[f];
	}
	return f;
}
void kruscal_arc(MGraph_L G,algraph gra)
{ 
	edg edgs[20];
	int i,j,k=0;
	for(i=0;i!=G.vexnum;++i)
	{
		for(j=i;j!=G.vexnum;++j)
		{
			if(G.arcs[i][j].adj!=10000)
			{
				edgs[k].pre=i;
				edgs[k].bak=j;
				edgs[k].weight=G.arcs[i][j].adj;
				++k;
			}
		}
	}
	int x,y;
	int m,n,b=0;
	int buf,edf;
	for(i=0;i!=gra.arcnum;++i)
	{
		acrvisited[i]=0; 
	}
	for(j=0;j!=G.arcnum;++j)
	{
		m=10000;
		for(i=0;i!=G.arcnum;++i)
		{
			if(edgs[i].weight<m)
			{
				m=edgs[i].weight;
				x=edgs[i].pre;
				y=edgs[i].bak;
				n=i;

			}

		}
		buf=find(acrvisited,x);
		edf=find(acrvisited,y); 
		edgs[n].weight=10000;
		if(buf!=edf)
		{
			acrvisited[buf]=edf;

			printf("<%c,%c>权值为:%d",G.vexs[x],G.vexs[y],m);
			b+=m;
			cout<<endl;
		}
	}
	cout<<"最小生成树的权为:"<<b;
	cout<<endl;
}

void kruskal()
{ 
	algraph gra;
	MGraph_L G;
	int d;
	char a='a';
	d=creatMGraph_L(G);
	creatadj(gra,G);
	cout<<"运用kruscal算法所得最小生成树组成的边为:"<<endl;
	kruscal_arc(G,gra);
}


int main(void)
{	
	kruskal();
	return 1 ;
}
