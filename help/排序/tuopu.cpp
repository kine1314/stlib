#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;
#define Max 1001
int n,m;
typedef struct Arc*link;
struct Arc
{
	char info[15];//�洢�����Ϣ
	int adjvex;//�ڽӵ���
	link nextarc;//ָ����һ���ڽӵ�
};
struct Vex
{
	char info[15];//������Ϣ
	int indgree;//�������
	link firstarc;//ָ����һ���ڽӵ�
}v[Max];
int find(char*str)//�ڶ��㼯�в�����ϢΪstr�Ķ���ı�Ų�����
{
	for(int i=1;i<=n;i++)
		if(!strcmp(str,v[i].info))
			return i;
}
void creat()//�����ڽӱ�
{
	cout<<"�γ�����:"<<endl;
	cin>>n;
	cout<<"���������������Ϣ�����γ̱�ţ�"<<endl;
	for(int i=1;i<=n;i++)
	{
		cin>>v[i].info;
		v[i].indgree=0;
		v[i].firstarc=NULL;
	}
	cout<<"�������������Ŀ��"<<endl;
	cin>>m;
	cout<<"���������(���޿γ̱����ǰ):"<<endl;
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
void update(int node)//ÿ���һ������ʱҪ��Ӧ�ĵ��øú��������¶��������Ϣ
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
	cout<<"�����������Ŀ:"<<endl;
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