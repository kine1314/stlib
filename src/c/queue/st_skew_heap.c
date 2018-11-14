/*	st_skew_heap.c -- б��ʵ���ļ�	*/
#include <stdio.h>
#include <stdlib.h>

#include "st_log.h"
#include "st_skew_heap.h"


/*	�ֲ�ADT����	*/

/*	Item1����Ϊָ���������ͷ�ԭ�ռ�����ɷǷ��Ĵ洢������	*/
/*	�õ��ľ����ѵ��: ָ�뻹��Ҫ����.û�����ɵ�ʱ��Ҫ����	*/
typedef SHNode SHItem1 ;
typedef struct _SHNode1
{
	SHItem1 item1 ;
	struct _SHNode1 * next ;
} SHNode1 ;
typedef struct _SHQueue
{
	SHNode1 * front ;
	SHNode1 * rear ;
	int size ;
} * PSHQueue ;

int Initialize_SHQueue (PSHQueue * const pqueue) ;
int SHQueue_Is_Empty (const PSHQueue * const pqueue) ;
int En_SHQueue (const PSHQueue * const pqueue, const SHItem1 item1) ;
int De_SHQueue (const PSHQueue * const pqueue, SHItem1 * const pitem1) ;
void SHQRelease_ (const PSHQueue * const pqueue) ;
SHNode1 * SHQMake_Node1 (const SHItem1 item1) ;

/*	�ֲ���������	*/

static SHeap SHMerge1 (const SHeap h1, const SHeap h2) ;
static SHeap SHSwap_Children (const SHeap h1) ;

/*	�ӿں�������	*/

int SHCreate (SHeap * const ph)
{
	*ph = (SHNode *) malloc (sizeof (SHNode)) ;
	if (NULL == *ph)
		return 0 ;
	else
	{
		*ph = NULL ;
		return 1 ;
	}
}

int SHIsEmpty (const SHeap h)
{
	return NULL == h ;
}

SHeap SHMerge (const SHeap h1, const SHeap h2)
{
	if (NULL == h1)
		return h2 ;
	else if (NULL == h2)
		return h1 ;
	else if (h1->item < h2->item)
		return SHMerge1 (h1, h2) ;
	else
		return SHMerge1 (h2, h1) ;
}

SHeap SHInsert (SHeap h, const SHItem item)
{
	SHeap new_heap ;

	new_heap = (SHNode *) malloc (sizeof (SHNode)) ;
	if (NULL == new_heap)
		return h ;
	new_heap->item = item ;
	new_heap->left = new_heap->right = NULL ;
	h = SHMerge (h, new_heap) ;

	return h ;
}

SHeap SHDeleteMin (SHeap h, SHNode * const pnode)
{
	SHNode * temp ;

	if (SHIsEmpty (h))
		return h ;
	temp = h ;
	*pnode = *h ;
	h = SHMerge (h->left, h->right) ;
	free (temp) ;

	return h ;
}

SHNode * SHFind (const SHeap h, const SHItem item)
{
	SHNode * temp ;

	if (NULL == h)
		return NULL ;
	else if (item == h->item)
		return h ;
	else if ((temp = SHFind (h->left, item)))
		return temp ;
	else if ((temp = SHFind (h->right, item)))
		return temp ;
	else
		return NULL ;
}

SHeap SHBuild (const SHItem array[], const int size)
{
	SHeap h1, h2 ;
	PSHQueue q ;
	SHNode * arr ;
	int ct ;

	if (!Initialize_SHQueue (&q))
		return NULL ;
	arr = (SHNode *) malloc (sizeof (SHNode) * size) ;
	for (ct = 0; ct < size; ct++)
	{
		arr[ct].item = array[ct] ;
		arr[ct].left = arr[ct].right = NULL ;
		En_SHQueue (&q, arr[ct]) ;
	}
	//	�����ڴ治��ʹ��֮�����̻���ȥ��ϰ��
	free (arr) ;
	while (q -> size != 1)
	{
		//	�˴����ڴ�������, ��ֻ֪����ô���ڴ湻��.���������������ô�����
		h1 = (SHNode *) malloc (sizeof (SHNode)) ;
		h2 = (SHNode *) malloc (sizeof (SHNode)) ;
		De_SHQueue (&q, h1) ;
		De_SHQueue (&q, h2) ;
		h1 = SHMerge (h1, h2) ;
		En_SHQueue (&q, *h1) ;
	}
	De_SHQueue (&q, h1) ;
	SHQRelease_ (&q) ;
	//	h1 �� h2 ��ͬ�е���б�������ڴ������

	return h1 ;
}

void SHRelease (const SHeap h)
{
	if (h)
	{
		SHRelease (h->left) ;
		SHRelease (h->right) ;
		free (h) ;
	}
}

/*	�ֲ���������	*/

static SHeap SHMerge1 (const SHeap h1, const SHeap h2)
{
	if (NULL == h1->left)
		h1->left = h2 ;
	else
	{
		h1->right = SHMerge (h1->right, h2) ;
		//	ͬ��ʽ�����, б�ѵĺô��ǽ�ʡ�˿ռ�, ��������һ���������
		SHSwap_Children (h1) ;
	}

	return h1 ;
}

static SHeap SHSwap_Children (const SHeap h1)
{
	SHNode * temp ;

	temp = h1->left ;
	h1->left = h1->right ;
	h1->right = temp ;

	return h1 ;
}

/*	�ֲ�ADT����	*/

int Initialize_SHQueue (PSHQueue * const pqueue)
{
	*pqueue = (struct _SHQueue *) malloc (sizeof (struct _SHQueue)) ;
	if (NULL == *pqueue)
		return 0 ;
	(*pqueue)->front = (*pqueue)->rear = NULL ;
	(*pqueue)->size = 0 ;

	return 1 ;
}

int SHQueue_Is_Empty (const PSHQueue * const pqueue)
{
	return 0 == (*pqueue)->size ;
}

int En_SHQueue (const PSHQueue * const pqueue, const SHItem1 item1)
{
	SHNode1 * new_node ;

	new_node = SHQMake_Node1 (item1) ;
	if (NULL == new_node)
		return 0 ;
	if (SHQueue_Is_Empty (pqueue))
	{
		//	ʵ���϶�����ͨ�� front ʵ�ֵ�, rear ���ֻ�Ǹ�������. ���Բ�Ϊ�����ռ�
		(*pqueue)->front = (*pqueue)->rear = new_node ;
	}
	else
	{
		/*	Ҳ�������Ҳ���������δ���ĺ���	*/
		/*	�ڵڶ��ε��õ�ʱ��, (*pqueue) -> rear -> next = new_node ��ʵ�൱�� (*pqueue) -> front -> next = new_node	*/
		/*	���ⲽ����˶��е�����.̫��ʽ��.����ǰò�������ϡ���Ϳ��!	*/
		(*pqueue)->rear ->next = new_node ;
		(*pqueue)->rear = new_node ;
	}
	(*pqueue)->size++ ;

	return 1 ;
}

int De_SHQueue (const PSHQueue * const pqueue, SHItem1 * const pitem1)
{
	SHNode1 * temp ;

	if (SHQueue_Is_Empty (pqueue))
		return 0 ;
	*pitem1 = (*pqueue)->front->item1 ;
	temp = (*pqueue)->front ;
	if ((*pqueue)->size != 1)
		(*pqueue)->front = (*pqueue)->front->next ;
	else
		(*pqueue)->front = (*pqueue)->rear = NULL ;
	(*pqueue)->size-- ;
	free (temp) ;

	return 1 ;
}

void SHQRelease_ (const PSHQueue * const pqueue)
{
	SHNode1 * scan, * temp ;

	scan = (*pqueue)->front ;
	while (scan)
	{
		temp = scan ;
		scan = scan->next ;
		free (temp) ;
	}
	free (*pqueue) ;
}

SHNode1 * SHQMake_Node1 (const SHItem1 item1)
{
	SHNode1 * new_node ;

	new_node = (SHNode1 *) malloc (sizeof (SHNode1)) ;
	if (NULL == new_node)
		return NULL ;
	new_node->item1 = item1 ;
	new_node->next = NULL ;

	return new_node ;
}




