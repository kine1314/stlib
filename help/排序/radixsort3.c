#include <stdio.h>

#include <stdlib.h>

#include <time.h>

 

#define RADIX 10           /*	�ؼ��ֻ���	*/

#define NUM 10             /*	����ڵ����	*/

 

typedef struct LNode       /*	����ڵ㶨��	*/
{
	void	*data;              /*	��ŵ�����	*/
	struct	LNode *next;    /*	ָ����һ���ڵ��ָ��	*/
}LNode,* LinkList;

 

LinkList CreateLink(LNode LL[NUM]);								/* �������� */

void OutputLink(LinkList p);									/* ��ӡ���� */

LNode** DistributeL(LinkList p, int keyNum, LNode ** pa);		/* ���� */

LinkList CollectL(LinkList p, LNode** pa);						/* �ռ� */

LNode* st_slist_radix_sort(LNode* p)
{
	int key = 1;
	int i;
	int j;
	LNode* h[NUM] = {NULL};

	for(i = 0; i < 3; ++i, key *= 10)
	{
		DistributeL(p, key, h);
		
		p = CollectL((LinkList)p,h);
		
		for(j = 0; j < NUM; ++j)
			h[j] = NULL;
		
		printf("after sort\n");
		OutputLink(p);
	}	

	return p ;
}

int main()
{
	LNode LL[NUM];
	
	LinkList p;
	LinkList temp ;
 

	p = CreateLink(LL);
	
	printf("before sort\n");
	OutputLink(p);

	temp = st_slist_radix_sort(p);
	OutputLink(temp);

	return 0 ;
}

 

LinkList CreateLink(LNode LL[NUM])
{
	//�����������Ա�
	int count;
	time_t t;

	srand((unsigned)time(&t));
	for(count = 0; count < NUM; ++count)
	{
		LL[count].data = (void *)(rand()%1000);
		if(9 == count)
		{
			LL[count].next = NULL;
		}
		else
		{
			LL[count].next = &LL[count+1];
		}
	}

	return &LL[0];
}

void OutputLink(LinkList p)
{
	int count;

	for(count = 0; count < NUM; ++count)
	{
		printf("%5d",p->data);

		p = p->next;
	}

	printf("\n");

}

LNode** DistributeL(LinkList p, int keyNum, LNode ** pa) 	//�������ݵķ���
{
	int arr[10]= {0};	/*	��¼ͬһ��λ����ͬ���ĸ���	*/
	int k;

	while(p)
	{
		k = (int)p->data/keyNum%10;

		if(NULL == pa[k])
		{
			pa[k] = (LinkList)malloc(sizeof(LNode)*10);
			pa[k][arr[k]] = *p;
			pa[k][arr[k]].next = NULL;
			++arr[k];
		}
		else
		{
			pa[k][arr[k]] = *p;
			pa[k][arr[k]].next = NULL;
			pa[k][arr[k]-1].next = &pa[k][arr[k]];
			++arr[k];
		}
		p = p->next;
	}

	return pa;

}

LinkList CollectL(LinkList p, LNode ** pa)  		//�������ݵ��ռ�
{
	int count;
	int i = 0;
	LinkList pc;	/*	�洢pa[count]�ĳ�ʼֵ�����ͷſռ�ʱʹ��	*/
	LinkList pp = p;	/*	�洢p�ĳ�ʼֵ������ֵʱʹ��	*/

	for(count = 0; count < NUM; ++count)
	{
		pc = pa[count];

		while(NULL != pa[count])
		{
			p[i] = *pa[count];
			pa[count] = pa[count]->next;
			if(9 == i)
			{
				p[i].next = NULL;
			}
			else
			{
				p[i].next = &p[i+1];
			}

			++i;

		} 

		pa[count] = pc;

		if(NULL != pa[count])
			free(pa[count]);

	}

	return pp;

}


