#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;
#define Max 1001
int n,m;
typedef struct Arc*link;
struct Arc
{
	char info[15];//存储结点信息
	int adjvex;//邻接点编号
	link nextarc;//指向下一个邻接点
};
struct Vex
{
	char info[15];//顶点信息
	int indgree;//顶点入度
	link firstarc;//指向下一个邻接点
}v[Max];
int find(char*str)//在顶点集中查找信息为str的定点的编号并返回
{
	for(int i=1;i<=n;i++)
		if(!strcmp(str,v[i].info))
			return i;
}
void creat()//建立邻接表
{
	cout<<"课程总数:"<<endl;
	cin>>n;
	cout<<"请输入各个定点信息（即课程编号）"<<endl;
	for(int i=1;i<=n;i++)
	{
		cin>>v[i].info;
		v[i].indgree=0;
		v[i].firstarc=NULL;
	}
	cout<<"请输入有向边数目："<<endl;
	cin>>m;
	cout<<"输入有向边(先修课程编号在前):"<<endl;
    for( i=1;i<=m;i++)
	{
		char ss[15],tt[12];
		cin>>ss>>tt;
		int s=find(ss),t=find(tt);
		v[t].indgree++;
		link p=(link)malloc(sizeof(Arc));
		strcpy(p->info,v[t].info);
		p->adjvex=t;
		p->nextarc=v[s].firstarc;
		v[s].firstarc=p;
	}
}
void update(int node)//每输出一个顶点时要相应的调用该函数，更新顶点入度信息
{
	link p=v[node].firstarc;
	while(p)
	{
		if(v[p->adjvex].indgree>0)
			v[p->adjvex].indgree--;
		p=p->nextarc;
	}
}
int main()
{
	int rel[Max],len=0,t;
	cout<<"请输入测试数目:"<<endl;
	cin>>t;
	while(t--)
	{
		creat();
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				if(!v[i].indgree)
				{
					rel[len++]=i;
					v[i].indgree=-1;
					update(i);
				}
				cout<<"-----------------------"<<endl;
				if(len<n)
					cout<<"Input error!"<<endl;
				else
				{
					for(int i=0;i<len;i++)
						cout<<v[i].info<<" ";
					cout<<endl;
				}
				cout<<"------------------------"<<endl;
    }
	system("pause");
	return 0;
} 