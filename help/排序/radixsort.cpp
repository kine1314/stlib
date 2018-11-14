#include "stdafx.h"   
#include <iostream.h>   
   
/*   基数排序的算法源程序*/    
#define   R   10 /*   R为基数, 测试数据要求用10个左右的数据项进行测试,因此R=10*/    
struct   Node   //汽车节点,单链表结点类型   
{    
        int  key[3];   //汽车牌号   
        /*   汽车其他信息;*/    
        char board[10];//商标，此处至少应该定义数组吧，因为商标应该大于一个字符   
        char color[5];//颜色，若直接用字符串表示，可以定义为数组，原来你定义字符，那你程序必须有字符对应转为颜色   
        int  data[3];//注册日期，年月日用字符表示不合适，可以定义日期结构体，或者干脆用数组表示   
        char name[8];//车主姓名，总体感觉你为什么爱用字符，要知道字符只能存一个，而姓名显然是多个字符，即字符串，那么用字符数组或字符指针是必然的。而指针涉及动态申请内存，建议还是用数组简单   
   
        Node   *next; //下一个结点指针   
};    
   
struct   QueueNode   { //汽车节点构成的单链表   
        Node   *f;                                     /*   队列的头指针   */    
        Node   *e;                                     /*   队列的尾指针   */    
}queue[R];    
   
struct   Node   element[R+1]={   
        0,0,0,"","",0,0,0,"",NULL,/*表头*/     
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
};//存放R个汽车节点的数组   
   
void   radixSort(Node   **plist, int d,int r)//d为排序码的最大位数=3,r为基数排序的基数=R   
{    
        int   i,j,k;      
        Node   *p,   *head   =   (*plist)-> next;    
        for(j=d-1;j>=0;j--)    
        {   
            /*   进行d次分配和收集*/    
                p   =   head;    
                for(i   =   0;   i      r;   i++)   {      
                        queue[i].f   =   NULL;     queue[i].e   =   NULL;   /*   清队列   */    
                }    
                while   (p   !=   NULL)   {    
                        k   =   p-> key[j];                             /*   按排序码的第j个分量进行分配*/    
                        if   (queue[k].f   ==   NULL)      
                                queue[k].f   =   p;                   /*   若第k个队列为空，则当前记录为队头*/      
                        else   (queue[k].e)-> next   =   p;/*   否则当前记录链接到第k队的队尾*/    
                        queue[k].e   =   p;    
                        p   =   p-> next;    
                }    
   
                for(i   =   0;   queue[i].f   ==   NULL;   i++)   /*   找出第一个非空队列*/    
                        ;    
                p   =   queue[i].e;     head   =   queue[i].f;   /*   head为收集链表的头指针*/    
   
                for(i++;   i      r;   i++)    
                        if(queue[i].f   !=   NULL)   {   /*   收集非空队列   */    
                                p-> next   =   queue[i].f;    
                                p   =   queue[i].e;    
                        }                  
                p-> next   =   NULL;    
        }    
        (*plist)-> next   =   head;    
}    
   
   
void output()//输出   
{   
    Node   * p =   element;    
    p   =   p-> next; //因为element下标为0的元素是表头，不存数据，其next指针指向第一个汽车节点   
    char c;   
    while   (p   !=   NULL){    
            cout<<"汽车牌号:";   
            cout.width(2);   
            cout.fill('0');    
            c=p->key[1]+64;//因为目前的基数排序函数的源码要求排序的关键词是0-9之间的整数，因为输入数据时，将大写字母-64变成0-9之间整数，那么输出需要+64才能重新变成大写字母。注意这意味大写字母只能是A-I,满足测试数据A-E的要求   
            cout<<p->key[0]<<c;   
            cout.width(4);   
            cout.fill('0');   
            cout<<p->key[2]<<",";         
   
            cout<<"汽车商标:"<<p->board<<",";   
            cout<<"汽车颜色:"<<p->color<<",";   
               
            cout<<"汽车注册日期:"<<p->data[0]<<"-";   
            cout.width(2);   
            cout.fill('0');   
            cout<<p->data[1]<<"-";   
            cout.width(2);//只影响紧随其后的域，在一个域输出完后，域宽恢复成它的默认值,因此需要再设置一次   
            cout.fill('0');   
            cout<<p->data[2]<<",";   
               
            cout<<"车主姓名:"<<p->name<<endl;                   
               
            p   =   p-> next;    
    }    
}   
   
int   main(){    
        int   i;    
        Node   * p =   element;    
        for   (i   =   0;   i      R;   i++)    
           element[i].next   =   &element[i+1];    
        element[R].next   =   NULL;    
        radixSort(&p,   3,   R); //链表基数排序   
         output();   
      
        return   0;    
} 