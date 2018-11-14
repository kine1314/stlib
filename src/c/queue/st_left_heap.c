#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "st_log.h"
#include "st_left_heap.h"

typedef struct _LHNode
{
	LeftHeadET   Element;
	LHPriorityQueue Left;
	LHPriorityQueue Right;
	int           Npl;
}LHNode;

/*	局部ADT定义	*/
// 此队列用于遍历打印左式堆
typedef LHNode Item2 ;
typedef struct node2
{
	Item2 item2 ;
	struct node2 * next ;
} Node2 ;
typedef struct queue
{
	Node2 * front ;
	Node2 * rear ;
	int items ;
} * Queue ;


// 此队列用于建立左式堆
typedef LHPriorityQueue Item3 ;
typedef struct node3
{
	Item3 item3 ;
	struct node3 * next ;
} Node3 ;
typedef struct queue3
{
	Node3 * front ;
	Node3 * rear ;
	int items ;
} * Queue3 ;

static LHPriorityQueue LHMerge1 (const LHPriorityQueue h1, const LHPriorityQueue h2) ;
static LHPriorityQueue LHSwap_Children (const LHPriorityQueue heap) ;

/*	局部ADT声明	*/

static int Initialize_Queue (Queue * const pqueue) ;
static int Queue_Is_Empty (const Queue * const pqueue) ;
static int En_Queue (const Queue * const pqueue, const Item2 item2) ;
static int De_Queue (Queue * pqueue, Item2 * pitem2) ;
static void Release2 (const Queue * const pqueue) ;
static Node2 * Make_Node2 (const Item2 item2) ;

static int Initialize_Queue3 (Queue3 * const pqueue3) ;
static int Queue_Is_Empty3 (const Queue3 * const pqueue3) ;
static int En_Queue3 (const Queue3 * const pqueue3, const Item3 item3) ;
static int De_Queue3 (Queue3 * pqueue3, Item3 * pitem3) ;
static void Release3 (const Queue3 * const pqueue3) ;
static Node3 * Make_Node3 (const Item3 item3) ;


/*	接口函数定义	*/

int CreateANullLHeap (LHPriorityQueue * const pheap)
{
	*pheap = (LHNode *) malloc (sizeof (LHNode)) ;
	if (NULL == *pheap)
	{
		puts ("Out of space.[1]") ;
		return 0 ;
	}
	else
	{
		*pheap = NULL ;
		return 1 ;
	}
}

int LHIsEmpty (const LHPriorityQueue heap)
{
	return NULL == heap ;
}

LHPriorityQueue LHMerge (const LHPriorityQueue h1, const LHPriorityQueue h2)
{
	if (NULL == h1)
		return h2 ;
	if (NULL == h2)
		return h1 ;
	if (h1->Element < h2->Element)
		return LHMerge1 (h1, h2) ;
	else
		return LHMerge1 (h2, h1) ;
}

LHPriorityQueue LHInsert (LHPriorityQueue heap, const LeftHeadET item)
{
	LHPriorityQueue new_heap ;

	new_heap = (LHNode *) malloc (sizeof (LHNode)) ;
	if (!new_heap)
		return NULL ;
	else
	{
		new_heap->Element = item ;
		new_heap->Npl = 0 ;
		new_heap->Left = new_heap->Right = NULL ;
		heap = LHMerge (heap, new_heap) ;
	}

	return heap ;
}

LHPriorityQueue LHDeleteMin (const LHPriorityQueue heap)
{
	LHPriorityQueue Left, Right ;

	if (LHIsEmpty (heap))
	{
		puts ("LHPriorityQueue is empty.") ;
		return heap ;
	}
	Left = heap->Left ;
	Right = heap->Right ;
	free (heap) ;

	return LHMerge (Left, Right) ;
}

struct _LHNode * LHFind (const LHPriorityQueue heap, const LeftHeadET item)
{
	LHNode * temp ;

	if (NULL == heap)
	{
		return NULL ;
	}
	if (item == heap->Element)
	{
		return heap ;
	}
	if ((temp = LHFind (heap->Left, item)) != NULL)
	{
		return temp ;
	}
	if ((temp = LHFind (heap->Right, item)) != NULL)
	{
		return temp ;
	}
	else
	{
		return NULL ;
	}
}

LHPriorityQueue LHBulid (LHPriorityQueue heap, const LeftHeadET * array, const int size)
{
	LHPriorityQueue h ;
	Queue3 q ;
	Node3 * arr ;
	int ct ;
	
	if (!LHIsEmpty (heap))
		return NULL ;
	Initialize_Queue3 (&q) ;
	arr = (Node3 *) malloc (sizeof (Node3) * size) ;
	if (NULL == arr)
		return NULL ;

	// 分配临时队列元素的内存
	for (ct = 0; ct < size; ct++)
		arr[ct].item3 = (LHNode *) malloc (sizeof (LHNode)) ;

	// 填充临时队列的元素，每个元素都是一个单元素的堆
	for (ct = 0; ct < size; ct++)
	{
		arr[ct].item3->Element = array[ct] ;
		arr[ct].item3->Npl = 0 ;
		arr[ct].item3->Left = arr[ct].item3->Right = NULL ;
		En_Queue3 (&q, arr[ct].item3) ;					// 入队
	}
	
	//	此处的内存空间情况很微妙.目前解释不了.我怀疑是借用了队列的空间,但没有什么语言依据
	h = (LHNode *) malloc (sizeof (LHNode)) ;
	while (q->items != 1)
	{
		De_Queue3 (&q, &heap) ;				// 获取左式堆的跟元素
		De_Queue3 (&q, &h) ;
		heap = LHMerge (heap, h) ;
		En_Queue3 (&q, heap) ;
	}
	De_Queue3 (&q, &heap) ;
	Release3 (&q) ;
//	此处的内存空间情况很微妙.目前解释不了.我怀疑是借用了队列的空间,但没有什么语言依据
//	free (h) ;

	return heap ;
}

void LHLevelOrderTraversal (const LHPriorityQueue heap)
{
	Queue q ;
	Item2 item2 ;

	Initialize_Queue (&q) ;
	item2 = *heap ;
	En_Queue (&q, item2) ;
	while (!Queue_Is_Empty (&q))
	{
		De_Queue (&q, &item2) ;
		printf ("%d\n", item2.Element) ;
		if (item2.Left)
			En_Queue (&q, *item2.Left) ;
		if (item2.Right)
			En_Queue (&q, *item2.Right) ;
	}
	Release2 (&q) ;
}

/*	局部函数定义	*/

static LHPriorityQueue LHMerge1 (const LHPriorityQueue h1, const LHPriorityQueue h2)
{
	if (NULL == h1->Left)
		h1->Left = h2 ;
	else
	{
		h1->Right = LHMerge(h1->Right, h2) ;
		if (h1->Left->Npl < h1->Right->Npl)
			LHSwap_Children (h1) ;
		h1->Npl = h1->Right->Npl + 1 ;
	}

	return h1 ;
}

static LHPriorityQueue LHSwap_Children (const LHPriorityQueue heap)
{
	LHNode * temp ;

	temp = heap->Left ;
	heap->Left = heap->Right ;
	heap->Right = temp ;

	return heap ;
}

/*	局部ADT定义	*/

static int Initialize_Queue (Queue * const pqueue)
{
	*pqueue = (struct queue *) malloc (sizeof (struct queue)) ;
	if (!*pqueue)
		return 0 ;
	(*pqueue)->front = (*pqueue)->rear = NULL ;
	(*pqueue)->items = 0 ;

	return 1 ;
}

static int Queue_Is_Empty (const Queue * const pqueue)
{
	return 0 == (*pqueue)->items ;
}

static int En_Queue (const Queue * const pqueue, const Item2 item2)
{
	Node2 * new_node ;

	new_node = Make_Node2 (item2) ;
	if (!new_node)
		return 0 ;
	if (Queue_Is_Empty (pqueue))
		(*pqueue)->front = (*pqueue)->rear = new_node ;
	else
	{
		(*pqueue)->rear->next = new_node ;
		(*pqueue)->rear = (*pqueue)->rear->next ;
	}
	(*pqueue)->items++ ;

	return 1 ;
}

static int De_Queue (Queue * pqueue, Item2 * pitem2)
{
	Node2 * temp ;

	if (Queue_Is_Empty (pqueue))
		return 0 ;
	*pitem2 = (*pqueue)->front->item2 ;
	temp = (*pqueue)->front ;
	if (1 == (*pqueue)->items)
		(*pqueue)->front = (*pqueue)->rear = NULL ;
	else
		(*pqueue)->front = (*pqueue)->front->next ;
	(*pqueue)->items-- ;
	free (temp) ;
	
	return 1 ;
}

static void Release2 (const Queue * const pqueue)
{
	Node2 * scan, * temp ;

	scan = (*pqueue)->front ;
	while (scan)
	{
		temp = scan ;
		scan = scan->next ;
		free (temp) ;
	}
	free (*pqueue) ;
}

static Node2 * Make_Node2 (const Item2 item2)
{
	Node2 * new_node ;

	new_node = (Node2 *) malloc (sizeof (Node2)) ;
	if (!new_node)
		return NULL ;
	new_node->item2 = item2 ;
	new_node->next = NULL ;

	return new_node ;
}

static int Initialize_Queue3 (Queue3 * const pqueue3)
{
	*pqueue3 = (struct queue3 *) malloc (sizeof (struct queue3)) ;
	if (!*pqueue3)
		return 0 ;
	(*pqueue3)->front = (*pqueue3)->rear = NULL ;
	(*pqueue3)->items = 0 ;

	return 1 ;
}

static int Queue_Is_Empty3 (const Queue3 * const pqueue3)
{
	return 0 == (*pqueue3)->items ;
}

static int En_Queue3 (const Queue3 * const pqueue3, const Item3 item3)
{
	Node3 * new_node ;

	new_node = Make_Node3 (item3) ;
	if (!new_node)
		return 0 ;
	if (Queue_Is_Empty3 (pqueue3))
		(*pqueue3)->front = (*pqueue3)->rear = new_node ;
	else
	{
		(*pqueue3)->rear->next = new_node ;
		(*pqueue3)->rear = (*pqueue3)->rear->next ;
	}
	(*pqueue3)->items++ ;

	return 1 ;
}

static int De_Queue3 (Queue3 * pqueue3, Item3 * pitem3)
{
	Node3 * temp ;

	if (Queue_Is_Empty3 (pqueue3))
		return 0 ;
	*pitem3 = (*pqueue3)->front->item3 ;
	temp = (*pqueue3)->front ;
	if (1 == (*pqueue3)->items)
		(*pqueue3)->front = (*pqueue3)->rear = NULL ;
	else
		(*pqueue3)->front = (*pqueue3)->front->next ;
	(*pqueue3)->items-- ;
	free (temp) ;
	
	return 1 ;
}

static void Release3 (const Queue3 * const pqueue3)
{
	Node3 * scan, * temp ;

	scan = (*pqueue3)->front ;
	while (scan)
	{
		temp = scan ;
		scan = scan->next ;
		free (temp) ;
	}
	free (*pqueue3) ;
}

static Node3 * Make_Node3 (const Item3 item3)
{
	Node3 * new_node ;

	new_node = (Node3 *) malloc (sizeof (Node3)) ;
	if (!new_node)
		return NULL ;
	new_node->item3 = item3 ;
	new_node->next = NULL ;

	return new_node ;
}


void LHDisplayOneHeap(struct _LHNode * node)
{
	__msg("Element [%d]\n", node->Element);
}


