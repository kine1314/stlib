#include "stdafx.h"   
#include <iostream.h>   
   
/*   ����������㷨Դ����*/    
#define   R   10 /*   RΪ����, ��������Ҫ����10�����ҵ���������в���,���R=10*/    
struct   Node   //�����ڵ�,������������   
{    
        int  key[3];   //�����ƺ�   
        /*   ����������Ϣ;*/    
        char board[10];//�̱꣬�˴�����Ӧ�ö�������ɣ���Ϊ�̱�Ӧ�ô���һ���ַ�   
        char color[5];//��ɫ����ֱ�����ַ�����ʾ�����Զ���Ϊ���飬ԭ���㶨���ַ����������������ַ���ӦתΪ��ɫ   
        int  data[3];//ע�����ڣ����������ַ���ʾ�����ʣ����Զ������ڽṹ�壬���߸ɴ��������ʾ   
        char name[8];//��������������о���Ϊʲô�����ַ���Ҫ֪���ַ�ֻ�ܴ�һ������������Ȼ�Ƕ���ַ������ַ�������ô���ַ�������ַ�ָ���Ǳ�Ȼ�ġ���ָ���漰��̬�����ڴ棬���黹���������   
   
        Node   *next; //��һ�����ָ��   
};    
   
struct   QueueNode   { //�����ڵ㹹�ɵĵ�����   
        Node   *f;                                     /*   ���е�ͷָ��   */    
        Node   *e;                                     /*   ���е�βָ��   */    
}queue[R];    
   
struct   Node   element[R+1]={   
        0,0,0,"","",0,0,0,"",NULL,/*��ͷ*/     
        1,'B'-64,6,"hq1","red",2008,1,1,"ty",NULL,/*36*/    
        2,'A'-64,5,"hq2","red",2008,1,1,"ty",NULL,/*5*/    
        1,'B'-64,6,"hq3","red",2008,1,1,"ty",NULL,/*16*/    
        1,'C'-64,8,"hq4","red",2008,1,1,"ty",NULL,/*98*/    
        1,'B'-64,5,"hq5","red",2008,1,1,"ty",NULL,/*95*/    
        1,'A'-64,7,"hq6","red",2008,1,1,"ty",NULL,/*47*/    
        1,'B'-64,2,"hq7","red",2008,1,1,"ty",NULL,/*32*/    
        2,'D'-64,6,"hq8","red",2008,1,1,"ty",NULL,/*36*/    
        3,'B'-64,8,"hq9","red",2008,1,1,"ty",NULL,/*48*/    
        2,'B'-64,1,"hq10","red",2008,1,1,"ty",NULL   /*10*/    
};//���R�������ڵ������   
   
void   radixSort(Node   **plist, int d,int r)//dΪ����������λ��=3,rΪ��������Ļ���=R   
{    
        int   i,j,k;      
        Node   *p,   *head   =   (*plist)-> next;    
        for(j=d-1;j>=0;j--)    
        {   
            /*   ����d�η�����ռ�*/    
                p   =   head;    
                for(i   =   0;   i      r;   i++)   {      
                        queue[i].f   =   NULL;     queue[i].e   =   NULL;   /*   �����   */    
                }    
                while   (p   !=   NULL)   {    
                        k   =   p-> key[j];                             /*   ��������ĵ�j���������з���*/    
                        if   (queue[k].f   ==   NULL)      
                                queue[k].f   =   p;                   /*   ����k������Ϊ�գ���ǰ��¼Ϊ��ͷ*/      
                        else   (queue[k].e)-> next   =   p;/*   ����ǰ��¼���ӵ���k�ӵĶ�β*/    
                        queue[k].e   =   p;    
                        p   =   p-> next;    
                }    
   
                for(i   =   0;   queue[i].f   ==   NULL;   i++)   /*   �ҳ���һ���ǿն���*/    
                        ;    
                p   =   queue[i].e;     head   =   queue[i].f;   /*   headΪ�ռ������ͷָ��*/    
   
                for(i++;   i      r;   i++)    
                        if(queue[i].f   !=   NULL)   {   /*   �ռ��ǿն���   */    
                                p-> next   =   queue[i].f;    
                                p   =   queue[i].e;    
                        }                  
                p-> next   =   NULL;    
        }    
        (*plist)-> next   =   head;    
}    
   
   
void output()//���   
{   
    Node   * p =   element;    
    p   =   p-> next; //��Ϊelement�±�Ϊ0��Ԫ���Ǳ�ͷ���������ݣ���nextָ��ָ���һ�������ڵ�   
    char c;   
    while   (p   !=   NULL){    
            cout<<"�����ƺ�:";   
            cout.width(2);   
            cout.fill('0');    
            c=p->key[1]+64;//��ΪĿǰ�Ļ�����������Դ��Ҫ������Ĺؼ�����0-9֮�����������Ϊ��������ʱ������д��ĸ-64���0-9֮����������ô�����Ҫ+64�������±�ɴ�д��ĸ��ע������ζ��д��ĸֻ����A-I,�����������A-E��Ҫ��   
            cout<<p->key[0]<<c;   
            cout.width(4);   
            cout.fill('0');   
            cout<<p->key[2]<<",";         
   
            cout<<"�����̱�:"<<p->board<<",";   
            cout<<"������ɫ:"<<p->color<<",";   
               
            cout<<"����ע������:"<<p->data[0]<<"-";   
            cout.width(2);   
            cout.fill('0');   
            cout<<p->data[1]<<"-";   
            cout.width(2);//ֻӰ�������������һ�������������ָ�������Ĭ��ֵ,�����Ҫ������һ��   
            cout.fill('0');   
            cout<<p->data[2]<<",";   
               
            cout<<"��������:"<<p->name<<endl;                   
               
            p   =   p-> next;    
    }    
}   
   
int   main(){    
        int   i;    
        Node   * p =   element;    
        for   (i   =   0;   i      R;   i++)    
           element[i].next   =   &element[i+1];    
        element[R].next   =   NULL;    
        radixSort(&p,   3,   R); //�����������   
         output();   
      
        return   0;    
} 