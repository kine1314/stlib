#include<stdio.h>
#include<stdlib.h>
struct stud/*����������ڵ�*/
{
	int data;
	struct stud *next;
};
struct su/*����ջ������zhan�൱������ͷ��㣬top����ĸ߶�*/
{
	struct stud *zhan;
	int top;
};

ru_zhan(struct su *node,int n)/*������ջ����*/
{
	int i,j;

	if(node->top==0)/*��ջ�ĵ�һ��Ԫ��*/
	{
	   struct stud *p;
	   p=(struct stud *)malloc(sizeof(struct stud));
	   if(NULL==p)
	   {
		   printf("�ڴ����ʧ��\n");
		   exit(1);
	   }
	   node->top++;
	   p->data=n;
	   p->next=node->zhan->next;
	   node->zhan->next=p;
	}
	else
	{
	   struct stud *p;
	   p=(struct stud *)malloc(sizeof(struct stud));
	   if(NULL==p)
	   {
		   printf("�ڴ����ʧ��\n");
		   exit(1);
	   }
	   node->top++;
	   p->data=n;
	   p->next=node->zhan->next;
	   node->zhan->next=p;
	}
}

chu_zhan(struct su **node)/*��ջ�������õ��Ƕ���ָ�룬����Ϊ����Ҫ�ͷ���ָ��ڵ�ָ��Ŀռ�*/
{
	struct stud *p;
	int i;
	if((*node)->top==0)
	{
		printf("ջ�Ѿ�����");
		return -1;
	}
	else
	{
		(*node)->top--;
		p=(*node)->zhan->next;
		i=p->data;
		(*node)->zhan->next=(*node)->zhan->next->next;
		free(p);
	}
	return i;
}

void main()
{
	struct su *node;
	char c;
	int n;
	node=(struct su * )malloc(sizeof(struct su));
	if(NULL==node)
	{
	   printf("allocation failture\n");
	   exit(1);
	}
	node->zhan=(struct stud *)malloc(sizeof(struct stud));/*ע������һ��Ҫ���ṹ�������еĽڵ����ռ�*/
	node->top=0;
	node->zhan->next=NULL;
	printf("������y��ջ��n��ջ��x�˳�\n");
	c=getchar();
	while(c!='x')
	{
		if(c=='y')
		{
			printf("��������ջ������\n");
			scanf("%d",&n);
			ru_zhan(node,n);
			printf("��ջ�ɹ�\n");
		}
		else if(c=='n')
		{
			int n;
			printf("���ڿ�ʼ��ջ\n");
			n=chu_zhan(&node);
			if(n>=0)
			   printf("��ջ��Ԫ����%d\n",n);
			else
			   printf("ջ�Ѿ�����\n");
		}
		else
		   ;

		printf("������y��ջ��n��ջ��x�˳�");
		   c=getchar();
	}
	printf("ллʹ���ټ�\n");
}