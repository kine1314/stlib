#include <stdio.h>
#include <stdlib.h>

 

typedef struct node Node;
struct node
{
 int data;
 Node* next;
};

 

/*创建链表*/
void createlist(Node* head)
{
 Node* p=head;
 int i=1;
 while(i<100)
 {
    p->next=malloc(sizeof(Node));
    p=p->next;
    p->data=rand()%1005;
    p->next=NULL;
	i++;
 }
}

 

/*释放链表*/
void freelist(Node* head)
{
 Node* temp=head;
 while(head)
 {
  temp=head;
  head=head->next;
  free(temp);
 }
}

 

/*打印链表*/
void printlist(Node* head)
{
 printf("\n");
 while(head)
 {
  printf("%d ",head->data);
  head=head->next;
 }
 printf("\n");
}

 

/*获取链表中的节点数*/
int getNodeNum(Node* h)
{
 int n=0;
 while(h)
 {
  n++;
  h=h->next;
 }
 return n;
}

 

/*把一个指针移动n步*/
void move(Node** h,int n)
{
 int i;
 for(i=0;i<n;i++)
 {
  *h=(*h)->next;
 }
}


/*单链表希尔排序例程*/
void shellsort(Node* h)
{
     int i=0;
     int flag=0;/*标记一次快速插入迭代是否结束*/
     Node* h1;/*h1用来从头开始遍历寻找插入节点*/
     Node* h2;/*h2用来指向需要插入的结点*/
     Node* h3;/*h3用来指向h2的前一个结点*/
     int n=0;/*节点数*/
     int t;/*步进值*/
     n=getNodeNum(h);/*节点数*/

     for(t=n/2;t>0;t=t/2)/*希尔迭代，每次缩小步进值*/
     {
          h2=h3=h;/*每次希尔迭代，初始化h2和h3的位置*/
          move(&h3,t-1);
          move(&h2,t);/*移动t步*/

          while(h2)/*插入排序*/
              {
                    h1=h; /*初始化h1的位置*/
                    flag=0;/*flag置0*/
                    while(flag==0)
                    {
                           if((h1->next->data) > (h2->data))/*如果找到，即把h2所指向的结点插到h1后面，然后跳出循环*/
                           {
                                  h3->next=h2->next;
                                  h2->next=h1->next;
                                  h1->next=h2;
                                  h2=h3->next;/*h2所指节点已经移到前面，h2要向后移动*/
                                  break; /*别忘了此处的break*/
                           }
                           /*移动h1*/
                            for(i=0;i<t;i++)
                            {
                                 h1=h1->next;
                                 if((h1==h2)||(h1==NULL))
                                 {
                                   flag=1;/*h1移到了h2*/
                                   break;/*马上停止移动，防止指针越界*/
                                 }
                            }
                    }
          
                    if((flag==1)&&(h2!=NULL))/*只在h2所指结点不需要前插时，移动h2和h3*/
                    {
                        h2=h2->next;
                        h3=h3->next;
                    }
             }
     }
}


/*单链表插入排序的测试例程*/
int main(void)
{
 int i;
 /*构造一个包含头节点的单链表*/
 Node* head = malloc(sizeof(Node));
 head->data = 0;
 createlist(head);
 printlist(head);
 /*希尔排序*/
 shellsort(head);
 printlist(head);
 freelist(head);
 scanf("%d",&i);
 return 0;
}