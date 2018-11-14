#include<stdio.h>
#include<stdlib.h>
struct stud/*声明的链表节点*/
{
	int data;
	struct stud *next;
};
struct su/*声明栈，其中zhan相当于链表头结点，top链表的高度*/
{
	struct stud *zhan;
	int top;
};

ru_zhan(struct su *node,int n)/*进行入栈操作*/
{
	int i,j;

	if(node->top==0)/*入栈的第一个元素*/
	{
	   struct stud *p;
	   p=(struct stud *)malloc(sizeof(struct stud));
	   if(NULL==p)
	   {
		   printf("内存分配失败\n");
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
		   printf("内存分配失败\n");
		   exit(1);
	   }
	   node->top++;
	   p->data=n;
	   p->next=node->zhan->next;
	   node->zhan->next=p;
	}
}

chu_zhan(struct su **node)/*出栈，这里用的是二级指针，是因为肯能要释放所指向节点指针的空间*/
{
	struct stud *p;
	int i;
	if((*node)->top==0)
	{
		printf("栈已经空了");
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
	node->zhan=(struct stud *)malloc(sizeof(struct stud));/*注意这里一定要给结构体镶套中的节点分配空间*/
	node->top=0;
	node->zhan->next=NULL;
	printf("请输入y入栈，n出栈，x退出\n");
	c=getchar();
	while(c!='x')
	{
		if(c=='y')
		{
			printf("请输入入栈的数字\n");
			scanf("%d",&n);
			ru_zhan(node,n);
			printf("入栈成功\n");
		}
		else if(c=='n')
		{
			int n;
			printf("现在开始出栈\n");
			n=chu_zhan(&node);
			if(n>=0)
			   printf("出栈的元素是%d\n",n);
			else
			   printf("栈已经空了\n");
		}
		else
		   ;

		printf("请输入y入栈，n出栈，x退出");
		   c=getchar();
	}
	printf("谢谢使用再见\n");
}