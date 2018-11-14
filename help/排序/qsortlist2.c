/**   
** ������Ŀ�������   
** author :liuzhiwei 
** data   :2011-08-07   
**/  
#include <stdio.h>     
#include <stdlib.h>       
//#include "iostream"  
//#include "ctime"  
//using namespace std;  
//������ڵ�  
  
#define MAX_SIZE	8

typedef struct SList  
{  
    int *data;  
    struct SList* next;  
}SList;  
  
void bulid_slist(SList** phead, int n)    //ָ��ָ���ָ��  
{  
    int i;  
    SList* ptr = NULL;  
    for(i = 0; i < n; ++i)  
    {  
        SList* temp = malloc( sizeof(SList) );  
        temp->data = rand() % n;   //����n��n���ڵ������  
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
  
SList* get_last_slist(SList* phead)   //ȡ��������ָ�����һ������ָ��  
{  
    SList *ptr = phead;  
    while(ptr->next)  
    {  
        ptr = ptr->next;  
    }  
    return ptr;  
}  
  
void print_slist(SList* phead)   //�������  
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
  
void sort_slist(SList* phead, SList* pend)    //��ͷָ��Ϊphead��βָ��Ϊpend�������������  
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
        if(pfast->data<phead->data)        //ÿ�ζ�ѡ������������ͷ�����Ϊ���ֵĻ�׼  
        {  
            ptemp=pslow;          //ptempʼ��Ϊpslow��ǰ�����  
            pslow=pslow->next;  
			//fprintf(stderr, "before pslow->data %d, pfast->data %d\n", pslow->data, pfast->data);
            my_swap(&pslow->data,&pfast->data);       //pslowָ��ָ��Ȼ�׼С�Ľ����ɵ�����  
			//fprintf(stderr, "after pslow->data %d, pfast->data %d\n", pslow->data, pfast->data);
        }  
        pfast=pfast->next;  
    }  
  
    my_swap(&pslow->data,&phead->data);       //��ʱpslowָ��ָ��Ȼ�׼С�Ľ����ɵ���������һ����㣬Ҳ���ǻ�׼��λ�ã�����Ҫ���׼��head��㣩����  
    sort_slist(phead,ptemp);             //ptempΪ���������ַָ�㣨��׼����ǰһ�����  
    sort_slist(pslow->next,pend);        //�Ҳ����ǱȻ�׼��Ľ����ɵ�����  
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
	if(head != NULL) /*ֻҪ���ǿ�������������������нڵ�*/
	{
		printf("head is %o\n", head); /*���ͷָ��ָ��ĵ�ַ*/
		do 
		{ 
			printf("%o   %d   %o\n", p, p->data, p->next);
			p = p->next; /*�Ƶ���һ���ڵ�*/
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