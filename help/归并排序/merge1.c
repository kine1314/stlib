#include<stdio.h>
#include<stdlib.h>


/* C���� ��⻪Ϊ�����⣬�����������������ϲ���һ���������� */
struct stud/*��������*/
{
int data;
struct stud *next;
};

void pai_xue(struct stud *head1,struct stud *head2,int count1,int count2)/*ð������*/
{
int i,j,temp=0;
struct stud *p;
for(i=0;i<count1-1;++i)
   for(p=head1->next;p->next!=NULL;p=p->next)/*������1��������*/
   {
    if(p->data>p->next->data)
    {
    temp=p->data;
    p->data=p->next->data;
    p->next->data=temp;
    }
   }

   for(i=0;i<count2-1;++i)
   for(p=head2->next;p->next!=NULL;p=p->next)/*������2��������*/
   {
    if(p->data>p->next->data)
    {
    temp=p->data;
    p->data=p->next->data;
    p->next->data=temp;
    }
   }
   printf("\n����1�������\n");/*�������1��2*/
   p=head1->next;
   while(p)
   {
   printf("%d",p->data);
   p=p->next;
   }
   printf("\n");
   printf("\n����2�������\n");
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
head3=(struct stud *)malloc(sizeof(struct stud *));/*��������ͷ��㣬������ռ�*/
head3->next=NULL;
head1=(struct stud *)malloc(sizeof(struct stud *));
head2=(struct stud *)malloc(sizeof(struct stud *));
p=(struct stud *)malloc(sizeof(struct stud *));
q=(struct stud *)malloc(sizeof(struct stud *));
head1->next=NULL;
head2->next=NULL;
printf("����һ��������999����\n");
scanf("%d",&p->data);
while(p->data!=999)/*����1��������*/
{
count1++;
p->next=head1->next;
head1->next=p;
printf("����һ��������999����\n");
p=(struct stud *)malloc(sizeof(struct stud *));
scanf("%d",&p->data);
}
printf("���ڿ�ʼ���ڶ���������������\n");
printf("����һ��������999����\n");
scanf("%d",&q->data);
while(q->data!=999)/*����2��������*/
{
count2++;
q->next=head2->next;
head2->next=q;
printf("����һ��������999����\n");
q=(struct stud *)malloc(sizeof(struct stud *));
scanf("%d",&q->data);
}
pai_xue(head1,head2,count1,count2);


head1=head1->next;
head2=head2->next;
while(head1!=NULL&&head2!=NULL)/*������õ�����1��2 �����ݵ�������3*/
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

if(head1!=NULL)/*���������1��2�����ݲ�Ϊ�գ���ʣ�µ����ݵ�������3��*/
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

q=head3->next;/*�������ã�ԭ�����ɴ�С�����ó���С����*/
head3->next=NULL;
while(q!=NULL)
{
   p=q->next;
   q->next=head3->next;
   head3->next=q;
   q=p;
}
printf("��������ϲ�����С����Ϊ\n");
p=head3->next;
while(p)
{
printf("%d",p->data);
p=p->next;
}
}