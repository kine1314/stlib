#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int vexnum;//������
	int arcnum;//������
	int **arcs;//��ָ��
	char *vexs;//������
}iGraph;

typedef struct close
{
	int adjvex;//
	int endvex;//
	int lowcost;//��СȨֵ
}*closedge,closedges;

void CreateUDN(iGraph &G);//��������ͼ
int LocateVex(iGraph G,char v);//�ڵ�Ķ��������е��±�
void PrintUDN(iGraph G);//����洢�ṹʾ��ͼ
void MiniSpanTree_PRIM(iGraph G,closedge &minedge);//����С���������㷨
void PrintMinEdge(iGraph G,closedge minedge);//�����С�������ı�


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
	printf("-----------------------prim�㷨��ʾ-----------------------\n");
	printf("��д�ˣ����ƴ�         ѧ�ţ�20082556");
	printf("�����붥�����ͱ������ÿո��������\n");
	scanf("%d %d",&G.vexnum,&G.arcnum);
	getchar();
	G.vexs=(char *)malloc(G.vexnum*sizeof(char));//���ٿռ�
	for(i=0;i<G.arcnum;i++)
	{
		G.arcs=(int **)malloc(G.arcnum*sizeof(int *));
	}
	for(i=0;i<G.arcnum;i++)
	{
		G.arcs[i]=(int *)malloc(G.arcnum*sizeof(int));
	}
	printf("��������������֣��س�ȷ�ϣ�\n");
	for(i=0;i<G.vexnum;i++)
	{
		scanf("%c",&G.vexs[i]);
		getchar();
	}
	printf("������ͼ�и��ߡ������ʽΪ�����˵�1-�˵�2-Ȩֵ����\n");

	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			G.arcs[i][j]=100000; //ʹ�ߵ�Ȩֵ��ʼ��Ϊ���
		}
	}

	for(i=0;i<G.arcnum;i++)
	{
		scanf("%c-%c-%d",&name1,&name2,&cost);
		getchar();
		for(j=0;j<G.vexnum;j++)//�ڱ��в��ҵ�
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
		if(k==l)//�����������ͬ������
		{
			i--;
			printf("������������,����������\n");
			continue;
		}

		G.arcs[k][l]=cost;//����߸�Ȩֵ
		G.arcs[l][k]=cost;
	}//ʹ����ı߸�ֵ

	for(i=0;i<G.vexnum;i++)
	{
		for(j=0;j<G.vexnum;j++)
		{
			if(i==j)
			{
				G.arcs[i][j]=0;//����˵���ͬ���򲻴��ڱ�
			}
		}
	}
}

int LocateVex(iGraph G,char v)//�ڵ�Ķ��������е��±�
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

void PrintUDN(iGraph G)//��ӡģ��
{
	int i,j;
	printf("��Ӧ�ľ���Ϊ\n");
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
				if(G.arcs[i][j-1]==100000)//���û�б���ֵ����ij���㲻��ͨ
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

void MiniSpanTree_PRIM(iGraph G,closedge &minedge)//��С������
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
		//��K��Ԫ�غ͵�I��Ԫ�ؽ��� 
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
			z=minedge[i].endvex;//ZΪ���ҵ��Ķ���
			k=minedge[j].endvex;
			if(k!=z)
			{
				if(G.arcs[z][k]<minedge[j].lowcost)
				{
					minedge[j].adjvex=z;
					minedge[j].lowcost=G.arcs[z][k];//����ǰ�Ľڵ�Ƚϣ�����ߵ�ȨֵС���򣬼�ѡȡ���еĽ����Ȩֵ��С�ı�
				}
			}
		}
	}
}

void PrintMinEdge(iGraph G,closedge minedge)
{
	int i,sum;
	sum=0;
	printf("��С��������Ӧ�ı�Ϊ\n");
	for(i=0;i<G.vexnum-1;i++)
	{
		printf("%c-%c:ȨֵΪ��%d\n",G.vexs[minedge[i].adjvex],G.vexs[minedge[i].endvex],minedge[i].lowcost);
		sum=sum+minedge[i].lowcost;
	}
	printf("��С��������ȨֵΪ��%d",sum);
}


int main(void)
{
	prim();
	return 1 ;
}
