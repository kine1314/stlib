#include "iostream"
using namespace std;
typedef struct LIST
{
 int data;
 struct LIST* next;
}LINKLIST;
LINKLIST* merge(LINKLIST* &p0,LINKLIST* &p1)
{
 if (p1==NULL)
 {
  return p0;
 }
 else if (p0==NULL)
 {
  return p1;
 }
 else
 {
  LINKLIST* head,*LIST,*p,*p2;
  if (p1->data<p0->data)
  {
   head=p1;
   p=p1->next;
   p2=p0;
  }
  else
  {
   head=p0;
   p2=p0->next;
   p=p1;
  }
  LIST=head;
  while (p!=NULL&&p2!=NULL)
  {
   if ((p->data<p2->data)&&p!=NULL&&p2!=NULL)
   {
    head->next=p;
    head=p;
    p=p->next;
   }
   else if ((p->data>=p2->data)&&p!=NULL&&p2!=NULL)
   {
    head->next=p2;
    head=p2;
    p2=p2->next;
   }
  }
  if(p!=NULL)
  {
   head->next=p;
  }
  else if(p2!=NULL)
  {
   head->next=p2;
  }
  return LIST;
 }
}
void m_sort(LINKLIST* &list,int n)
{
 if (n>1)
 {
  int center=n/2,i;
  LINKLIST* p=list,*p1;
  for (i=1;i<center;i++)
  {
   p=p->next;
  }
  p1=p->next;
  p->next=NULL;
  m_sort(list,center);
  m_sort(p1,n-center);
     list=merge(list,p1);
 }
}
int main()
{
 int a,count=0;
 LINKLIST *list,*p;
 list=(LINKLIST*)malloc(sizeof(LINKLIST));
 list->next=NULL;
 while (cin>>a)
 {
  p=(LINKLIST*)malloc(sizeof(LINKLIST));
  p->data=a;
  p->next=list->next;
  list->next=p;
  count++;
 }
 m_sort(p,count);
 cout<<endl;
 while (p!=NULL)
 {
  cout<<p->data<<endl;
  p=p->next;
 }
 return 0;
}