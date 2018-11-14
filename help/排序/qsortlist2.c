/**   
** 单链表的快速排序   
** author :liuzhiwei 
** data   :2011-08-07   
**/  
#include <stdio.h>     
#include <stdlib.h>       
//#include "iostream"  
//#include "ctime"  
//using namespace std;  
//单链表节点  
  
#define MAX_SIZE	8

typedef struct SList  
{  
    int *data;  
    struct SList* next;  
}SList;  
  
void bulid_slist(SList** phead, int n)    //指向指针的指针  
{  
    int i;  
    SList* ptr = NULL;  
    for(i = 0; i < n; ++i)  
    {  
        SList* temp = malloc( sizeof(SList) );  
        temp->data = rand() % n;   //产生n个n以内的随机数  
        temp->next = NULL;  
        if(ptr == NULL)  
        {  
            *phead = temp;  
            ptr = temp;  
        }  
        else  
        {  
            ptr->next = temp;  
            ptr = ptr->next;  
        }  
    }  
}  
  
SList* get_last_slist(SList* phead)   //取得链表中指向最后一个结点的指针  
{  
    SList *ptr = phead;  
    while(ptr->next)  
    {  
        ptr = ptr->next;  
    }  
    return ptr;  
}  
  
void print_slist(SList* phead)   //输出链表  
{  
    SList *ptr = phead;  
    while(ptr)  
    {  
        printf("%d ", ptr->data);  
        ptr = ptr->next;  
    }  
    printf("\n");  
}  
  
void my_swap(int *a,int *b)  
{  
    int temp;  
    temp=*a;  
    *a=*b;  
    *b=temp;  
}  
  
void sort_slist(SList* phead, SList* pend)    //将头指针为phead，尾指针为pend的链表进行排序  
{  
    if(phead==NULL || pend==NULL)  
        return ;  
    if(phead==pend)  
        return ;  
    SList *pslow=phead;  
    SList *pfast=phead->next;  
    SList *ptemp=phead;  
    while(pfast)  
    {  
        if(pfast->data<phead->data)        //每次都选择待排序链表的头结点作为划分的基准  
        {  
            ptemp=pslow;          //ptemp始终为pslow的前驱结点  
            pslow=pslow->next;  
			//fprintf(stderr, "before pslow->data %d, pfast->data %d\n", pslow->data, pfast->data);
            my_swap(&pslow->data,&pfast->data);       //pslow指针指向比基准小的结点组成的链表  
			//fprintf(stderr, "after pslow->data %d, pfast->data %d\n", pslow->data, pfast->data);
        }  
        pfast=pfast->next;  
    }  
  
    my_swap(&pslow->data,&phead->data);       //此时pslow指针指向比基准小的结点组成的链表的最后一个结点，也就是基准的位置，所以要与基准（head结点）交换  
    sort_slist(phead,ptemp);             //ptemp为左右两部分分割点（基准）的前一个结点  
    sort_slist(pslow->next,pend);        //右部分是比基准大的结点组成的链表  
}  
  
void destroy_slist(SList* phead)  
{  
    SList* ptr = phead;  
    while(ptr)  
    {  
        SList* temp = ptr;  
        ptr = ptr->next;  
        free (temp);  
    }  
}  

SList *st_slist_alloc(void)
{
	return malloc(sizeof(SList));
}

SList*  st_slist_last(SList *list)
{
	if(NULL != list)
	{
		while(NULL != list->next)
		{
			list = list->next ;
		}
	}

	return list ;
}

SList*  st_slist_append(SList *list, void * data)
{
	SList* new_list = NULL ;
	SList* last = NULL ;

	new_list = (SList*)st_slist_alloc();
	new_list->data = data ;
	new_list->next = NULL ;

	if(NULL != list)
	{
		last = st_slist_last (list);
		/* g_assert (last != NULL); */
		last->next = new_list;

		return list;	
	}
	else
	{
		return new_list ;
	}
}

SList *init_list(int size, int *array)
{
	int i ;
	SList *slist = NULL ;

	for (i = 0; i < MAX_SIZE; i++) 
	{
		slist = st_slist_append(slist, (void *)(array[i]));
	}

	return slist ;
}

void st_dump_list(SList *head)
{
	SList *p;

	p = head;		// protect the head point
	if(head != NULL) /*只要不是空链表，就输出链表中所有节点*/
	{
		printf("head is %o\n", head); /*输出头指针指向的地址*/
		do 
		{ 
			printf("%o   %d   %o\n", p, p->data, p->next);
			p = p->next; /*移到下一个节点*/
		}
		while (p != NULL);
	}
}
  
int main(void)  
{  
	SList* plast = NULL ;
	SList* phead = NULL; 

    srand(time(NULL));  
    printf("Before sort single list\n");  
     
    //bulid_slist(&phead, 100);  
	int array[MAX_SIZE] = {4, 6, 1, 5, 2, 9, 2, 4};

	phead = init_list(MAX_SIZE, array);

    st_dump_list(phead);  
    plast = st_slist_last(phead);  
    printf("head:%d\nlast:%d\n", phead->data, plast->data);  
    printf("After sort single list\n");  
    sort_slist(phead, plast);  
    st_dump_list(phead);  
    destroy_slist(phead);  
    system("pause");  
    return 0;  
}  