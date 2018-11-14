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
Node create(int n)  //����һ˫��ѭ������
{
	Node phead,p,q;
	int i ,t;	
	printf("�������1�����:");
	scanf("%d",&i);
	//����ͷ�ڵ�
	phead=(Node)malloc(sizeof(Link));
	phead->data=i;
	phead->next=NULL;
	phead->prior=NULL;
	//��qָ��ͷ���,qΪp��ǰһ�����
	q=phead;
	for(t=1;t<n;t++)
	{
		printf("�������%d�����:",t+1);
		scanf("%d",&i);
		//�½����p,�������i����p->data,������p->nextΪ��
		p=(Node)malloc(sizeof(Link));
	    //��p����һ���ڵ�q��nextָ��p
		q->next=p;
	    p->data=i;
		p->next=NULL;
		p->prior=q;
		//����ǰ�´����Ľ��p����Ϊq
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
		printf("����Ϊ��!\n");
	else
	    printf("��������Ϊ:\n");
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
	//iΪ������������ݣ�tΪ���������λ��
	int i,t,n;
	//qΪҪ����Ľ�㣬p����������
	Node q,p;
	printf("������Ҫ�����λ��,0�����һ�����ǰ��");
	scanf("%d",&t);
	if(t>N)
	{
	     printf("����ֵ>�����ܳ��ȣ�������Ҫ�����λ��:");
	     scanf("%d",&t);
	}
	printf("������Ҫ���������:");
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
	//pΪҪɾ���Ľڵ�,qΪp��ǰһ�����
	Node p,q;
	printf("������Ҫɾ���ĵ�n���ڵ�,n=");
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
	printf("�����������Ϊ��\n");
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
	printf("����һ����N����������,N=");
	scanf("%d",&N);
	if(N<=0)
	{
		printf("��������������N=");
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