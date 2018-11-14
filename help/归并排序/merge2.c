/*
    Author : glq2000[glq2000@126.com http://hi.baidu.com/bmrs]
      Date : Wen, 2010-7-22
      ���� : �ϲ�������������  
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Node
{
    int value;
    struct _Node *next;    
}Node, *PNode;

PNode BuildLink(int n, int *pi);         //����һ���ڵ���ĿΪn��������, ��������ͷָ�� 
PNode MergeLink(PNode p1, PNode p2);     //�ϲ������������� 
void OutputLink(PNode ph);              //��������� 


int main()
{
    int a[] = {3, 12, 44, 55, 67, 89, 555};
    int b[] = {4, 46, 68, 69, 70, 90, 98, 888, 999 ,8888};
    PNode p1 = BuildLink(sizeof(a)/sizeof(int), a);
    PNode p2 = BuildLink(sizeof(b)/sizeof(int), b);
    OutputLink(p1);
    OutputLink(p2);
    PNode pMerge = MergeLink(p1, p2);
    OutputLink(pMerge); 
    
    getchar();
    return 0;    
}


PNode BuildLink(int n, int *pi)
{
    int i;
    PNode ph=NULL, pn;
    for(i=0; i<n; ++i)
    {
        if(!(pn=(PNode)malloc(sizeof(Node))))
        {
            printf("malloc error.\n");
            exit(1);
        }
        pn->value = *(pi+n-1-i);
        pn->next = ph;
        ph = pn;
    }
    
    return ph;
} 


void OutputLink(PNode ph)
{
    while(ph)
    {
        printf("%d ", ph->value);
        ph = ph->next;
    }
    printf("\n");
}


//�ϲ�������������,�����غϲ����������ͷָ�� 
PNode MergeLink(PNode p1, PNode p2)
{
    if(!p1) return p1;    //�������Ϊ��,��ֱ�ӷ�����һ������ 
    if(!p2) return p2;    //�������Ϊ��,��ֱ�ӷ�����һ������         
        
    PNode ph, p;          //ph �ϲ����������ͷָ�� 
    if(p1->value < p2->value)
    {
        ph = p1;
        p = p1;
        p1 = p1->next;
    }
    else
    {
        ph = p2;
        p = p2;
        p2 = p2->next;        
    }

    while(p1 && p2)
    {
        if(p1->value < p2->value)
        {
            p->next = p1;
            p = p1;
            p1 = p1->next;    
        }
        else
        {
            p->next = p2;
            p = p2;
            p2 = p2->next;    
        }    
    }
    
    if(!p1) p->next = p2;
    if(!p2) p->next = p1;
    
    return ph;
}