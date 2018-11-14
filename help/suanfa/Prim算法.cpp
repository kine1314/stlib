#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int vexnum;//点数量
	int arcnum;//边数量
	int **arcs;//边指针
	char *vexs;//点名称
}iGraph;

typedef struct close
{
	int adjvex;//
	int endvex;//
	int lowcost;//最小权值
}*closedge,closedges;

void CreateUDN(iGraph &G);//创建无向图
int LocateVex(iGraph G,char v);//节点的顶点向量中的下标
void PrintUDN(iGraph G);//输出存储结构示意图
void MiniSpanTree_PRIM(iGraph G,closedge &minedge);//求最小生成树的算法
void PrintMinEdge(iGraph G,closedge minedge);//输出最小生成树的边


int prim()
{
	iGraph G;
	closedge minedge;

	CreateUDN(G);
	printf("\n");
	MiniSpanTree_PRIM(G,minedge);
	PrintMinEdge(G,minedge);
	printf("\n");
	return 0;
}

void CreateUDN(iGraph &G)
{
	int i,j,k,l,cost;
	char name1,name2;
	printf("-----------------------prim算法演示-----------------------\n");
	printf("编写人：高云川         学号：20082556");
	printf("请输入顶点数和边数，用空格符隔开：\n");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	getchar();
	G.vexs=(char *)malloc(G.vexnum*sizeof(char));//开辟空间
	for(i=0;i<G.arcnum;i++)
	{
		G.arcs=(int **)malloc(G.arcnum*sizeof(int *));
	}
	for(i=0;i<G.arcnum;i++)
	{
		G.arcs[i]=(int *)malloc(G.arcnum*sizeof(int));
	}
	printf("请输入各顶点名字，回车确认：\n");
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%c",&G.vexs[i]);
		getchar();
	}
	printf("请输入图中各边。输入格式为：“端点1-端点2-权值”：\n");

	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			G.arcs[i][j]=100000; //使边的权值初始化为最大
		}
	}

	for(i=0;i<G.arcnum;i++)
	{
		scanf("%c-%c-%d",&name1,&name2,&cost);
		getchar();
		for(j=0;j<G.vexnum;j++)//在表中查找点
		{    
			if(name1==G.vexs[j])
			{
				k=j;
			}
			if(name2==G.vexs[j])
			{
				l=j;
			}
		}
		if(k==l)//两个点如果相同，报错
		{
			i--;
			printf("输入错误的数据,请重新输入\n");
			continue;
		}

		G.arcs[k][l]=cost;//无向边赋权值
		G.arcs[l][k]=cost;
	}//使输入的边赋值

	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			if(i==j)
			{
				G.arcs[i][j]=0;//如果端点相同，则不存在边
			}
		}
	}
}

int LocateVex(iGraph G,char v)//节点的顶点向量中的下标
{
	int i,m;
	for(i=0;i<G.vexnum;i++)
	{
		if(v==G.vexs[i])
		{
			m=i;
		}
	}
	return m;
}

void PrintUDN(iGraph G)//打印模块
{
	int i,j;
	printf("对应的矩阵为\n");
	printf("   ");
	for(i=0;i<G.vexnum;i++)
	{
		printf("\t%c  ",G.vexs[i]);
		printf("\n");
	}
	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum+1;j++)
		{ 
			if(j==0)
			{
				printf("%c\t",G.vexs[i]);
			}
			else
			{
				if(G.arcs[i][j-1]==100000)//如果没有被赋值，即ij两点不连通
				{
					printf("NO\t");
				}
				else
				{
					printf("%d\t",G.arcs[i][j-1]);
				}
			}
		}
		printf("\n");
	}
}

void MiniSpanTree_PRIM(iGraph G,closedge &minedge)//最小生成树
{  
	int i,j,k,z;
	int temp;
	int currentmin;
	k=0;
	minedge=(closedge)malloc((G.vexnum+1)*sizeof(closedges));
	for(j=1;j<G.vexnum;j++)
	{
		minedge[j-1].adjvex=k;
		minedge[j-1].endvex=j;
		minedge[j-1].lowcost=G.arcs[k][j];
	}
	for(i=0;i<G.vexnum-1;i++)
	{  
		currentmin=minedge[i].lowcost;
		k=i;
		for(j=i+1;j<G.vexnum-1;j++)
		{
			if(minedge[j].lowcost<currentmin)
			{
				currentmin=minedge[j].lowcost;
				k=j;
			}
		}
		//第K个元素和第I个元素交换 
		temp=minedge[i].adjvex;
		minedge[i].adjvex=minedge[k].adjvex;
		minedge[k].adjvex=temp;
		temp=minedge[i].endvex;
		minedge[i].endvex=minedge[k].endvex;
		minedge[k].endvex=temp;
		temp=minedge[i].lowcost;
		minedge[i].lowcost=minedge[k].lowcost;
		minedge[k].lowcost=temp;

		for(j=i+1;j<G.vexnum-1;j++)
		{
			z=minedge[i].endvex;//Z为新找到的顶点
			k=minedge[j].endvex;
			if(k!=z)
			{
				if(G.arcs[z][k]<minedge[j].lowcost)
				{
					minedge[j].adjvex=z;
					minedge[j].lowcost=G.arcs[z][k];//和以前的节点比较，如果边的权值小，则，即选取已有的结点中权值最小的边
				}
			}
		}
	}
}

void PrintMinEdge(iGraph G,closedge minedge)
{
	int i,sum;
	sum=0;
	printf("最小生成树对应的边为\n");
	for(i=0;i<G.vexnum-1;i++)
	{
		printf("%c-%c:权值为：%d\n",G.vexs[minedge[i].adjvex],G.vexs[minedge[i].endvex],minedge[i].lowcost);
		sum=sum+minedge[i].lowcost;
	}
	printf("最小生成树的权值为：%d",sum);
}


int main(void)
{
	prim();
	return 1 ;
}
