#include <stdio.h>
#include <stdlib.h>

 

typedef struct node Node;
struct node
{
 int data;
 Node* next;
};

 

/*��������*/
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

 

/*�ͷ�����*/
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

 

/*��ӡ����*/
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

 

/*��ȡ�����еĽڵ���*/
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

 

/*��һ��ָ���ƶ�n��*/
void move(Node** h,int n)
{
 int i;
 for(i=0;i<n;i++)
 {
  *h=(*h)->next;
 }
}


/*������ϣ����������*/
void shellsort(Node* h)
{
     int i=0;
     int flag=0;/*���һ�ο��ٲ�������Ƿ����*/
     Node* h1;/*h1������ͷ��ʼ����Ѱ�Ҳ���ڵ�*/
     Node* h2;/*h2����ָ����Ҫ����Ľ��*/
     Node* h3;/*h3����ָ��h2��ǰһ�����*/
     int n=0;/*�ڵ���*/
     int t;/*����ֵ*/
     n=getNodeNum(h);/*�ڵ���*/

     for(t=n/2;t>0;t=t/2)/*ϣ��������ÿ����С����ֵ*/
     {
          h2=h3=h;/*ÿ��ϣ����������ʼ��h2��h3��λ��*/
          move(&h3,t-1);
          move(&h2,t);/*�ƶ�t��*/

          while(h2)/*��������*/
              {
                    h1=h; /*��ʼ��h1��λ��*/
                    flag=0;/*flag��0*/
                    while(flag==0)
                    {
                           if((h1->next->data) > (h2->data))/*����ҵ�������h2��ָ��Ľ��嵽h1���棬Ȼ������ѭ��*/
                           {
                                  h3->next=h2->next;
                                  h2->next=h1->next;
                                  h1->next=h2;
                                  h2=h3->next;/*h2��ָ�ڵ��Ѿ��Ƶ�ǰ�棬h2Ҫ����ƶ�*/
                                  break; /*�����˴˴���break*/
                           }
                           /*�ƶ�h1*/
                            for(i=0;i<t;i++)
                            {
                                 h1=h1->next;
                                 if((h1==h2)||(h1==NULL))
                                 {
                                   flag=1;/*h1�Ƶ���h2*/
                                   break;/*����ֹͣ�ƶ�����ָֹ��Խ��*/
                                 }
                            }
                    }
          
                    if((flag==1)&&(h2!=NULL))/*ֻ��h2��ָ��㲻��Ҫǰ��ʱ���ƶ�h2��h3*/
                    {
                        h2=h2->next;
                        h3=h3->next;
                    }
             }
     }
}


/*�������������Ĳ�������*/
int main(void)
{
 int i;
 /*����һ������ͷ�ڵ�ĵ�����*/
 Node* head = malloc(sizeof(Node));
 head->data = 0;
 createlist(head);
 printlist(head);
 /*ϣ������*/
 shellsort(head);
 printlist(head);
 freelist(head);
 scanf("%d",&i);
 return 0;
}