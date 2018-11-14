#include<stdio.h>
#include<stdlib.h>
typedef int datatype;
typedef struct Linklist
{
  datatype data;
  struct Linklist *next,*prior;
}Link;
typedef Link *Node;
int N;
Node create(int n)  //建立一双向循环链表
{
	Node phead,p,q;
	int i ,t;	
	printf("请输入第1个结点:");
	scanf("%d",&i);
	//创建头节点
	phead=(Node)malloc(sizeof(Link));
	phead->data=i;
	phead->next=NULL;
	phead->prior=NULL;
	//令q指向头结点,q为p的前一个结点
	q=phead;
	for(t=1;t<n;t++)
	{
		printf("请输入第%d个结点:",t+1);
		scanf("%d",&i);
		//新建结点p,将输入的i存入p->data,并且令p->next为空
		p=(Node)malloc(sizeof(Link));
	    //将p的上一个节点q的next指向p
		q->next=p;
	    p->data=i;
		p->next=NULL;
		p->prior=q;
		//将当前新创建的结点p保存为q
		q=p;
	}
	phead->prior=p;
	p->next=phead;
    return phead;
}
void showlist(Node phead)
{
	Node p;
	p=phead;
	if(phead==NULL)
		printf("链表为空!\n");
	else
	    printf("链表各结点为:\n");
	while(p->next!=phead)
	{
		printf("%d\n",p->data);
		p=p->next;
	}
	if(p->next=phead)
		printf("%d\n",p->data);
}

Node insert(Node phead)
{
	//i为接入输入的数据，t为接受输入的位置
	int i,t,n;
	//q为要插入的结点，p结点遍历链表
	Node q,p;
	printf("请输入要插入的位置,0代表第一个结点前：");
	scanf("%d",&t);
	if(t>N)
	{
	     printf("输入值>链表总长度，请输入要插入的位置:");
	     scanf("%d",&t);
	}
	printf("请输入要插入的整数:");
	scanf("%d",&i);
	p=phead;
	if(t==0)
	{
		q=(Node)malloc(sizeof(Link));
        q->data=i;
		phead->prior->next=q;
		q->next=phead;
		q->prior=phead->prior;
		phead->prior=q;
		phead=q;
		return phead;
	}
	if(t==1)
	{
		q=(Node)malloc(sizeof(Link));
		q->data=i;
		phead->next->prior=q;
	    q->next=phead->next;
		q->prior=phead;
		phead->next=q;
		return phead;
	}
	for(n=1;n<t;n++)
	{
		p=p->next;
	}
	q=(Node)malloc(sizeof(Link));
	q->data=i;
	phead->next->prior=q;
	q->next=p->next;
	q->prior=p;
	p->next=q;
	return phead;
}

Node del_n(Node phead)
{
	int n;
	int t;
	//p为要删除的节点,q为p的前一个结点
	Node p,q;
	printf("请输入要删除的第n个节点,n=");
	scanf("%d",&n);
	p=q=phead;
	if(n==1)
	{
	    phead=phead->next;
	    free(p);		
     	return phead;
	}
    for(t=1;t<n;t++)
		p=p->next;
	for(t=1;t<n-1;t++)
		q=q->next;
	q->next=p->next;
	free(p);
	return phead;
}
Node reverse(Node phead)
{
    Node p;
	p=phead;
	printf("该链表的逆序为：\n");
	while(p->prior!=phead)
	{
	    printf("%d\n",p->prior->data);
		p=p->prior;
	}
	if(p->prior=phead)
        printf("%d\n",p->prior->data);
	phead=phead->prior;
	return phead;
}
int main()
{
	Node phead;
	printf("创建一个有N个结点的链表,N=");
	scanf("%d",&N);
	if(N<=0)
	{
		printf("请输入正整数，N=");
	    scanf("%d",&N);
	}
	phead=create(N);
	showlist(phead);
	reverse(phead);
    phead=insert(phead);
	showlist(phead);
	phead=del_n(phead);
	showlist(phead);
	return 0;
}