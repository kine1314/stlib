#include<stdio.h>
#include<malloc.h>

#define MAXLEN 40
#define VEXTYPE char

typedef struct gnode
{ 
	int adjvex;
	struct gnode *next;
}EDGENODE;

typedef struct
{
	int id;
	VEXTYPE vextex;
	EDGENODE *link;
}VEXNODE;

typedef struct
{
	VEXNODE adjlist[MAXLEN];
	int vexnum,arcnum;
	int kind;
}ADJGRAPH;

ADJGRAPH creat_adjgraph()
{
	EDGENODE *p;
	int i,s,d;
	ADJGRAPH adjg;
	adjg.kind=1;

	printf("�����붨�����ͱ������Կո�ֿ�����\n");
	scanf("%d %d",&s,&d);
	adjg.vexnum=s; 
	adjg.arcnum=d;
	for(i=0;i<adjg.vexnum ;i++)
	{
		printf("��%d���������Ϣ��",i+1);
		getchar();
		scanf("%c",&adjg.adjlist[i].vextex);
		adjg.adjlist[i].link=NULL;
		adjg.adjlist[i].id=0;
	}
	for(i=0;i<adjg.arcnum;i++)
	{
		printf("��%d���ߵ���ʼ������յ㶥��ı�ţ��Կո�ֿ�����",i+1);
		scanf("%d %d",&s,&d);
		while(s<1||s>adjg.vexnum||d<1||d>adjg.vexnum)
		{printf("    ��ų�����Χ�����������룡");
		scanf("%d %d",&s,&d);}
		s--; d--; p=(EDGENODE*)malloc(sizeof(EDGENODE));
		p->adjvex=d;  p->next=adjg.adjlist[s].link;
		adjg.adjlist[s].link=p;  adjg.adjlist[d].id++;
	}
	return adjg;
}

void topsort(ADJGRAPH ag)
{ 
	int i,j,k,m,n,top;
	EDGENODE *p;

	n=ag.vexnum; top=-1;

	for(i=0;i<n;i++)
	{
		if(ag.adjlist[i].id==0)
		{ 
			ag.adjlist[i].id=top;  
			top=i;
		}

		m=0;
		while(top!=-1)
		{
			j=top;  
			top=ag.adjlist[top].id;
			printf("%3c",ag.adjlist[j].vextex);
			m++; 
			p=ag.adjlist[j].link;
			while(p!=NULL)
			{
				k=p->adjvex;
				ag.adjlist[k].id--;
				if(ag.adjlist[k].id==0)
				{
					ag.adjlist[k].id=top; 
					top=k;
				}
				p=p->next;  
			}
		}
		if(m<n)
		printf("  *****ͼ���л����޷���������*****\n");
	}
}
void main()
{ADJGRAPH ag;
ag=creat_adjgraph();
printf("����������Ϊ��\n");
topsort(ag);
printf("\n");
}
