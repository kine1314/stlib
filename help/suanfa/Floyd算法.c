#include <stdio.h>
#define INFINITY 100
#define MAX_VERTEX_NUM 20
#define OK 1


typedef struct
{
	int vex[MAX_VERTEX_NUM];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum,arcnum;
}MGraph;

int p[20][20][20];
int a[20];

int LocateVex(MGraph *G,int v)
{
	int i,j;
	for(i=0;i<=G->vexnum;i++)
	{
		if(G->vex[i]==v)
		{
			j=i;
			break;
		}
	}
	return j;
}

void setpath(int v,int w,int u)
{

	int i=0,j=0,a,b;
	/*			 printf("%d,%d,%d->",v,w,u);
	printf("%d %d %d\n",p[v][u][0],p[v][u][1],p[v][u][2]);
	printf("%d %d %d\n",p[u][w][0],p[u][w][1],p[u][w][2]);
	*/				 
	while(p[v][u][i]!=-1)
	{
		i++;
	}

	while(p[u][w][j]!=-1)
	{
		j++;
	}
	for(a=0;a<i;a++)
	{
		p[v][w][a]=p[v][u][a];
		//	    printf("----%d----\n",p[v][w][a]);
	}
	for(b=0;b<j-1;b++)
	{
		p[v][w][a+b]=p[u][w][b+1];
		//	    printf("----%d----\n",p[v][w][a+b]);
	}

}

int CreateND(MGraph *G)
{
	int i,j,k,v1,v2,w;
	printf("     floyd代码   \n 梁鑫   20082557   \n输入节点数和边数（用空格隔开）:");
	scanf("%d %d",&G->vexnum,&G->arcnum);
	//	printf("\n");
	printf("输入节点编号（用空格隔开）:");
	for(i=0;i<G->vexnum;++i)
	{
		scanf("%d",&G->vex[i]);
	}
	for(i=0;i<G->vexnum;++i)
	{
		for(j=0;j<G->vexnum;++j)
		{
			G->arcs[i][j]=INFINITY;
		}
	}
	//	printf("\n");
	printf("输入边的权值（格式：顶点一，顶点二，路长（回车））:\n");
	for(k=0;k<G->arcnum;++k)
	{
		scanf("%d,%d,%d",&v1,&v2,&w);
		i=LocateVex(G,v1);
		j=LocateVex(G,v2);
		G->arcs[i][j]=w;
	}
	return OK;
}

void shortestpath(MGraph *G)
{  
	int v,w,u,i;

	int d[20][20];

	for(v=0;v<G->vexnum;++v)
	{
		for(w=0;w<G->vexnum;++w)
		{
			d[v][w]=G->arcs[v][w];
			for(u=0;u<G->vexnum;++u)
			{
				p[v][w][u]=-1;
			}
			if(d[v][w]<100)
			{ 
				p[v][w][0]=v;
				p[v][w][1]=w;
			}
		}
	}

	for(v=0;v<G->vexnum;++v)
	{
		for(w=0;w<G->vexnum;++w)
		{
			p[v][w][G->vexnum]=-1;
		}
	}

	//printf("!!!!%d!!!\n",p[0][1][2]);
	for(u=0;u<G->vexnum;++u)
	{
		for(v=0;v<G->vexnum;++v)
		{
			for(w=0;w<G->vexnum;++w)
			{
				if(d[v][u]+d[u][w]<d[v][w])
				{ 
					d[v][w]=d[v][u]+d[u][w];
					//   printf("!!!!!!!\n");
					//  printf("%d,%d,%d,%d\n",d[v][w],v,w,u);
					setpath(v,w,u);
					//printf("%d,%d,%d,%d\n",d[v][w],v,w,u);
				}
			}
			//  printf("!!!!!!!\n");
		}
	}

	for(v=0;v<G->vexnum;++v)
	{
		for(w=0;w<G->vexnum;++w)
		{
			if(v==w) continue;
			{
				printf("\n%d->%d is %d:",G->vex[v],G->vex[w],d[v][w]);
			}


			for(i=0;i<=G->vexnum;++i)
			{
				if(d[v][w]==100)
				{
					printf("不可达");
					break;
				}
				if(p[v][w][i]!=-1)
				{
					printf("路径%d ",G->vex[p[v][w][i]]);
				}
			}

		}
	}
}

void floyd()
{
	MGraph G;
	CreateND(&G);
	shortestpath(&G);
	printf("\n");
}

int main(void)
{
	floyd();
	return 1 ;
}