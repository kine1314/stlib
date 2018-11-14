#include <stdio.h>
#include <malloc.h>
typedef struct lnode {

int data;
struct lnode *next;
}lnode,*linklist;
linklist creatlist(int m)//创建链表
{

linklist p,l,s;
int i;
p=l=(linklist)malloc(sizeof(lnode));
p->next=NULL;
printf("请输入链表中的一个数字：");
scanf("%d",&p->data);
for(i=2;i<=m;i++)
{
s=(linklist)malloc(sizeof(lnode));
s->next = NULL;
printf("请输入第%d个数字",i);
scanf("%d",&s->data);
p->next=s;
p=p->next;
}
printf("\n");
return l; 
}
void print(linklist h)//打印链表
{
linklist p=h->next;
int t=1;
printf("打印各个数字：\n");
do
{ 
printf("请输出第%d个数:",t);
printf("%d\n",p->data);
p=p->next;
t++;
}while(p); 
}
linklist mergelist(void)//两个链表合并
{
int e,n;
linklist pa,pb,pc,head;
printf("请输入第一个链表的长度：");
scanf("%d",&e);
pa=creatlist(e);
printf("请输入第二个链表的长度：");
scanf("%d",&n); 
pb=creatlist(n);
head=pc=(linklist)malloc(sizeof(lnode));
pc->next=NULL;
while(pa&&pb)
{
if(pa->data<=pb->data) 
{
pc->next=pa;
pc=pa;
pa=pa->next;
}
else
{
pc->next=pb;
pc=pb;
pb=pb->next;
}
}
pc->next=pa?pa:pb;
return head; 
}
void main()
{
linklist head;
head=mergelist(); 
print(head);
}
