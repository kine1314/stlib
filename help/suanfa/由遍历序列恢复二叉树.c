#include<stdio.h>
#include <malloc.h>

#define maxsize 20
char *prelist="ABDECFLG";
char *inlist="DBEALFCG";
char *postlist="DEBLFGCA";

typedef char DataType;
typedef struct node2
{
	char data;
	struct node2 *lchild,*rchild;
} bitree;

void Visit(DataType item)
{
	printf("%c",item);
}

void PreOrder(bitree *t,void Visit(DataType item))
{
	if(t!=NULL)
	{
		Visit(t->data);
		PreOrder(t->lchild, Visit);
		PreOrder(t->rchild,Visit);
	}
}


void InOrder(bitree *t,void Visit(DataType item))
{
	if(t!=NULL)
	{
		InOrder(t->lchild, Visit);
		Visit(t->data);  
		InOrder(t->rchild,Visit);
	}
}

void PostOrder(bitree *t,void Visit(DataType item))
{
	if(t!=NULL)
	{
		PostOrder(t->lchild, Visit); 
		PostOrder(t->rchild,Visit);
		Visit(t->data);
	}
}



/*��������������лָ�������*/

bitree *preintotree(char *pre,char *in,int i,int j,int k,int l)
{
	int m;
	bitree *p;
	p=(bitree*)malloc(sizeof(bitree));

	p->data=*(pre+i);

	m=k;
	while(*(in+m)!=*(pre+i))
	{
		m++;
	}
	if (m==k)
	{
		p->lchild=NULL;
	}
	else
	{
		p->lchild=preintotree(pre,in,i+1,i+m-k,k,m-1);
	}
	if (m==l)
	{
		p->rchild=NULL;
	}
	else
	{
		p->rchild=preintotree(pre,in,i+m-k+1,j,m+1,l);
	}
	return(p);
}

/*������ͺ������лָ�������*/

bitree *inposttotree(char *in,char *post,int i,int j,int k,int l)
{
	int m;
	bitree *p;
	p=(bitree*)malloc(sizeof(bitree));
	p->data=*(post+l);
	m=i;
	while(*(in+m)!=*(post+l))
	{
		m++;
	}
	if (m==i)
	{
		p->lchild=NULL;
	}
	else                     
	{
		p->lchild=inposttotree(in,post,i,m-1,k,k+m-i-1);
	}
	if (m==j)
	{
		p->rchild=NULL;
	}
	else
	{
		p->rchild=inposttotree(in,post,m+1,j,k+m-i,l-1);
	}
	return(p);
}





//������
void erchashu3()
{
	int i,j;


	bitree *root1,*root2;
	root1=preintotree(prelist,inlist,0,7,0,7);
	root2=inposttotree(prelist,inlist,0,7,0,7);
	printf("-------------------�ɱ������лָ��������㷨��ʾ����----------------------------\n");
	printf("\n����˵����\n");
	printf("�ж����������ֱ������п�νһȷ��һ�ö�����\n");
	printf("ע�������������Ψһȷ��һ�ö����������ڴ˲�����ʾ\n");
	printf("��ʾ���У�\n�������У�ABDECFLG;\n��������:DBEALFCG;\n��������:DEBLFGCA");
	printf("\n�����ˣ� ��        ѧ�ţ�20082554        �༶����0801-3��\n");
	printf("\n��ѡ��ѡ�������ֱ������У�\n");
	printf("1�����������\n2������ͺ���\n");
	loop:
	scanf("%d",&i);

	switch(i)
	{
		case 1:
		{  
			printf("\n��������ʾ�����\n");
			printf("\n�������У�\n");
			root1=preintotree(prelist,inlist,0,7,0,7);
			PreOrder(root1,Visit);
			printf("\n\n�������У�\n");
			InOrder(root1,Visit);
			printf("\n\n�������У�\n");
			PostOrder(root1,Visit);
			printf("\n");
			break;
		}
		case 2:
		{
			printf("��������ʾ�����\n");
			printf("\n�������У�\n");
			PreOrder(root2,Visit);
			printf("\n\n�������У�\n");
			InOrder(root2,Visit);
			printf("\n\n�������У�\n");
			PostOrder(root2,Visit);
			printf("\n");
			break;
		}
		default :
		{
			printf("������벻�ڷ�Χ�ڣ����������룡\n");

			goto loop;
		}
		printf("\n");
		printf("\n");
		printf("\n");
	}

}


int main(void)
{
	erchashu3();
	return 1 ;
}