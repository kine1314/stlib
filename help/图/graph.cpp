#include<stdio.h>
#include<iostream>
#include<stdlib.h>

using namespace std;

#define MAX 30
typedef struct MGraph
{	int arcs[MAX][MAX]; //邻接距阵
	int vexnum,arcnum; //图的当前顶点数和弧数
}MGraph;
MGraph  graph;
int a[6][6]={	{0,5,0,7,0,0},{0,0,4,0,0,0},{8,0,0,0,0,9},
				{0,0,5,0,0,6},{0,0,0,5,0,0},{3,0,0,0,1,0}
			};
void print();
void creategraph(); //创建一个图
void DFSTraverse(int v,bool *&visited); //深度优先遍历
void BFSTraverse(int v,bool *&visited);//广度优先遍历
void Insert();//插入
void del();//删除


void creategraph() //创建一个图
{	
	int i,j;
	graph.vexnum=6;
	graph.arcnum=9;
	for(i=1;i<=graph.vexnum;i++)
		for(j=1;j<=graph.vexnum;j++)
			graph.arcs[i][j]=a[i-1][j-1];
	cout<<"图的邻接距阵是:"<<endl;
	for(i=1;i<=graph.vexnum;i++)
	{	for(j=1;j<=graph.vexnum;j++)
			cout<<graph.arcs[i][j]<<"  ";
		cout<<endl;
	}
}
void DFSTraverse(int v,bool *&visited) //深度优先遍历
{	
	cout<<"-->"<<v;
	visited[v]=true;
	for(int j=1;j<=graph.vexnum;j++)
		if(v!=j&&graph.arcs[v][j]!=0&&!visited[j])
			DFSTraverse(j,visited);
}
void BFSTraverse(int v,bool *&visited)//广度优先遍历
{	
	int q[MAX];
	int front=0,rear=0;
	cout<<"-->"<<v;
	visited[v]=true;
	q[++rear]=v;
	while(front!=rear)
	{	front=(front+1)%MAX;
		int k=q[front];
		for(int j=1;j<=graph.vexnum;j++)
		{	if(k!=j&&graph.arcs[k][j]!=0&&!visited[j])
			{	cout<<"-->"<<j;
				visited[j]=true;
				rear=(rear+1)%MAX;
				q[rear]=j;
			}
		}
	}
}
void Insert()//插入
{	
	int i,j;
	int s;
	printf("输入要插入路径的两个端点及路径长度:");
	scanf("%d%d%d",&i,&j,&s);
	if(i<=graph.vexnum&&j<=graph.vexnum&&graph.arcs[i][j]==0)
	{	graph.arcs[i][j]=s;
		a[i-1][j-1]=s;
		graph.arcnum++;
	}
	else if(i>graph.vexnum||j>graph.vexnum)printf("\n不能插入此路径,因为输入的端点不存在!!\n");
	else printf("\n本图已存在此路径!!\n");
}

void del()//删除
{	
	int i,j;
	printf("输入要删除路径的两个端点:");
	scanf("%d%d",&i,&j);
	if(i<=graph.vexnum&&j<=graph.vexnum&&graph.arcs[i][j]!=0)
	{	graph.arcs[i][j]=0;
		a[i-1][j-1]=0;
		graph.arcnum--;
	}
	else if(i>graph.vexnum||j>graph.vexnum)printf("\n不能删除此路径,因为输入的端点不存在!!\n");
	else printf("\n本图不存在此路径!!\n");
}

void print()
{	
	char ch;
	int v,i;
	bool *visited=new bool[MAX];
	do{
		printf("\n************图的基本操作!!!***********\n");
		printf("A:创建一个图  \nB:深度优先遍历\n");
		printf("C:广度优先遍历\nD:插入        \n");
		printf("E:删除        \n");
		printf("(按Q推出)请选择:");
		cin>>&ch;
		switch(ch)
		{
		case 'A':{creategraph();break;}
		case 'B':
			{
			for(i=0;i<MAX;i++)
				visited[i]=false;
			printf("输入深度优先遍历的起始点:");
			scanf("%d",&v);
			DFSTraverse(v,visited);
			break;
			}
		case 'C':
			{
			for(i=0;i<MAX;i++)
				visited[i]=false;	
			printf("输入广度优先遍历的起始点:");
			scanf("%d",&v);
			BFSTraverse(v,visited);
			break;
			}
		case 'D':{Insert();break;}
		case 'E':{del();break;}
		case 'Q':exit(0);
		}
		cout<<"\ncome on(y/n):";
		cin>>&ch;
	}while(ch!='n');
}
int main()
{
	print();
}
