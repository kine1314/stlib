#include<stdio.h>
#include<stdlib.h>


/* C语言 详解华为笔试题，两个无序单链表，排序后合并成一个有序链表。 */
struct stud/*定义链表*/
{
int data;
struct stud *next;
};

void pai_xue(struct stud *head1,struct stud *head2,int count1,int count2)/*冒泡排序法*/
{
int i,j,temp=0;
struct stud *p;
for(i=0;i<count1-1;++i)
   for(p=head1->next;p->next!=NULL;p=p->next)/*对链表1进行排序*/
   {
    if(p->data>p->next->data)
    {
    temp=p->data;
    p->data=p->next->data;
    p->next->data=temp;
    }
   }

   for(i=0;i<count2-1;++i)
   for(p=head2->next;p->next!=NULL;p=p->next)/*对链表2进行排序*/
   {
    if(p->data>p->next->data)
    {
    temp=p->data;
    p->data=p->next->data;
    p->next->data=temp;
    }
   }
   printf("\n链表1排完序后\n");/*输出链表1和2*/
   p=head1->next;
   while(p)
   {
   printf("%d",p->data);
   p=p->next;
   }
   printf("\n");
   printf("\n链表2排完序后\n");
   p=head2->next;
   while(p)
   {
   printf("%d",p->data);
    p=p->next;
   }
   printf("\n");

  
}
void main()
{

struct stud *head1,*head2,*p,*q,*head3;
int count1=1,count2=1;
head3=(struct stud *)malloc(sizeof(struct stud *));/*定义链表头结点，并分配空间*/
head3->next=NULL;
head1=(struct stud *)malloc(sizeof(struct stud *));
head2=(struct stud *)malloc(sizeof(struct stud *));
p=(struct stud *)malloc(sizeof(struct stud *));
q=(struct stud *)malloc(sizeof(struct stud *));
head1->next=NULL;
head2->next=NULL;
printf("输入一个数据以999结束\n");
scanf("%d",&p->data);
while(p->data!=999)/*链表1输入数据*/
{
count1++;
p->next=head1->next;
head1->next=p;
printf("输入一个数据以999结束\n");
p=(struct stud *)malloc(sizeof(struct stud *));
scanf("%d",&p->data);
}
printf("现在开始给第二个链表输入数据\n");
printf("输入一个数据以999结束\n");
scanf("%d",&q->data);
while(q->data!=999)/*链表2输入数据*/
{
count2++;
q->next=head2->next;
head2->next=q;
printf("输入一个数据以999结束\n");
q=(struct stud *)malloc(sizeof(struct stud *));
scanf("%d",&q->data);
}
pai_xue(head1,head2,count1,count2);


head1=head1->next;
head2=head2->next;
while(head1!=NULL&&head2!=NULL)/*将排序好的链表1和2 的数据导入链表3*/
{
   if(head1->data<=head2->data)
   {
    p=head1->next;
  
    head1->next=head3->next;
    head3->next=head1;
  
    head1=p;
   }
  
   else
   {
    q=head2->next;
   
    head2->next=head3->next;
    head3->next=head2;
   
    head2=q;
   }
}

if(head1!=NULL)/*如果有链表1或2的数据不为空，将剩下的数据导入链表3中*/
{
  
  
   p=head1;
   while(p!=NULL)
   {
   q=p->next;
   p->next=head3->next;
   head3->next=p;
   p=q;
   }
  
}
if(head2!=NULL)
{
  
   q=head2;
   while(q!=NULL)
   {
    p=q->next;
    q->next=head3->next;
    head3->next=q;
    q=p;
   }
}

q=head3->next;/*将链表倒置，原来是由大到小，倒置成由小到大*/
head3->next=NULL;
while(q!=NULL)
{
   p=q->next;
   q->next=head3->next;
   head3->next=q;
   q=p;
}
printf("两个链表合并后由小到大为\n");
p=head3->next;
while(p)
{
printf("%d",p->data);
p=p->next;
}
}