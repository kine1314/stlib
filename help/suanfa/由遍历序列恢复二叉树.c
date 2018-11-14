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



/*由中序和先序序列恢复二叉树*/

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

/*由中序和后序序列恢复二叉树*/

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





//主函数
void erchashu3()
{
	int i,j;


	bitree *root1,*root2;
	root1=preintotree(prelist,inlist,0,7,0,7);
	root2=inposttotree(prelist,inlist,0,7,0,7);
	printf("-------------------由遍历序列恢复二叉树算法演示程序----------------------------\n");
	printf("\n程序说明：\n");
	printf("有二叉树的三种遍历序列可谓一确定一棵二叉树\n");
	printf("注：后序和先序不能唯一确定一棵二叉树，故在此不加演示\n");
	printf("演示序列：\n先序序列：ABDECFLG;\n先序序列:DBEALFCG;\n先序序列:DEBLFGCA");
	printf("\n制作人： 马静        学号：20082554        班级：计0801-3班\n");
	printf("\n请选择选择哪两种遍历序列：\n");
	printf("1：中序和先序\n2：中序和后序\n");
	loop:
	scanf("%d",&i);

	switch(i)
	{
		case 1:
		{  
			printf("\n以下是演示结果：\n");
			printf("\n先序序列：\n");
			root1=preintotree(prelist,inlist,0,7,0,7);
			PreOrder(root1,Visit);
			printf("\n\n中序序列：\n");
			InOrder(root1,Visit);
			printf("\n\n后序序列：\n");
			PostOrder(root1,Visit);
			printf("\n");
			break;
		}
		case 2:
		{
			printf("以下是演示结果：\n");
			printf("\n先序序列：\n");
			PreOrder(root2,Visit);
			printf("\n\n中序序列：\n");
			InOrder(root2,Visit);
			printf("\n\n后序序列：\n");
			PostOrder(root2,Visit);
			printf("\n");
			break;
		}
		default :
		{
			printf("你的输入不在范围内，请重新输入！\n");

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