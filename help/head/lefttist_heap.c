/*	lefttist_heap.c -- 左式堆实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "lefttist_heap.h"

/*	局部ADT定义	*/

typedef Node Item2 ;
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

typedef Heap Item3 ;
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

/*	局部函数声明	*/

static Heap Merge1 (const Heap h1, const Heap h2) ;
static Heap Swap_Children (const Heap heap) ;

/*	接口函数定义	*/

int CreateANullHeap (Heap * const pheap)
{
	*pheap = (Node *) malloc (sizeof (Node)) ;
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

int HeapIsEmpty (const Heap heap)
{
	return NULL == heap ;
}

Heap Merge (const Heap h1, const Heap h2)
{
	if (NULL == h1)
		return h2 ;
	if (NULL == h2)
		return h1 ;
	if (h1 -> item < h2 -> item)
		return Merge1 (h1, h2) ;
	else
		return Merge1 (h2, h1) ;
}

Heap Insert (Heap heap, const Item item)
{
	Heap new_heap ;

	new_heap = (Node *) malloc (sizeof (Node)) ;
	if (!new_heap)
		return NULL ;
	else
	{
		new_heap -> item = item ;
		new_heap -> NPL = 0 ;
		new_heap -> left = new_heap -> right = NULL ;
		heap = Merge (heap, new_heap) ;
	}

	return heap ;
}

Heap DeleteMin (const Heap heap)
{
	Heap left, right ;

	if (HeapIsEmpty (heap))
	{
		puts ("Heap is empty.") ;
		return heap ;
	}
	left = heap -> left ;
	right = heap -> right ;
	free (heap) ;

	return Merge (left, right) ;
}

Node * Find (const Heap heap, const Item item)
{
	Node * temp ;

	if (NULL == heap)
		return NULL ;
	if (item == heap -> item)
		return heap ;
	if ((temp = Find (heap -> left, item)) != NULL)
		return temp ;
	if ((temp = Find (heap -> right, item)) != NULL)
		return temp ;
	else
		return NULL ;
}

Heap Bulid (Heap heap, const Item * array, const int size)
{
	Heap h ;
	Queue3 q ;
	Node3 * arr ;
	int ct ;
	
	if (!HeapIsEmpty (heap))
		return NULL ;
	Initialize_Queue3 (&q) ;
	arr = (Node3 *) malloc (sizeof (Node3) * size) ;
	if (NULL == arr)
		return NULL ;
	for (ct = 0; ct < size; ct++)
		arr[ct].item3 = (Node *) malloc (sizeof (Node)) ;
	for (ct = 0; ct < size; ct++)
	{
		arr[ct].item3 -> item = array[ct] ;
		arr[ct].item3 -> NPL = 0 ;
		arr[ct].item3 -> left = arr[ct].item3 -> right = NULL ;
		En_Queue3 (&q, arr[ct].item3) ;
	}
//	此处的内存空间情况很微妙.目前解释不了.我怀疑是借用了队列的空间,但没有什么语言依据
	h = (Node *) malloc (sizeof (Node)) ;
	while (q -> items != 1)
	{
		De_Queue3 (&q, &heap) ;
		De_Queue3 (&q, &h) ;
		heap = Merge (heap, h) ;
		En_Queue3 (&q, heap) ;
	}
	De_Queue3 (&q, &heap) ;
	Release3 (&q) ;
//	此处的内存空间情况很微妙.目前解释不了.我怀疑是借用了队列的空间,但没有什么语言依据
//	free (h) ;

	return heap ;
}

void LevelOrderTraversal (const Heap heap)
{
	Queue q ;
	Item2 item2 ;

	Initialize_Queue (&q) ;
	item2 = *heap ;
	En_Queue (&q, item2) ;
	while (!Queue_Is_Empty (&q))
	{
		De_Queue (&q, &item2) ;
		printf ("%d\n", item2.item) ;
		if (item2.left)
			En_Queue (&q, *item2.left) ;
		if (item2.right)
			En_Queue (&q, *item2.right) ;
	}
	Release2 (&q) ;
}

/*	局部函数定义	*/

static Heap Merge1 (const Heap h1, const Heap h2)
{
	if (NULL == h1->left)
		h1->left = h2 ;
	else
	{
		h1->right = Merge(h1->right, h2) ;
		if (h1->left->NPL < h1->right->NPL)
			Swap_Children (h1) ;
		h1->NPL = h1->right->NPL + 1 ;
	}

	return h1 ;
}

static Heap Swap_Children (const Heap heap)
{
	Node * temp ;

	temp = heap -> left ;
	heap -> left = heap -> right ;
	heap -> right = temp ;

	return heap ;
}

/*	局部ADT定义	*/

static int Initialize_Queue (Queue * const pqueue)
{
	*pqueue = (struct queue *) malloc (sizeof (struct queue)) ;
	if (!*pqueue)
		return 0 ;
	(*pqueue) -> front = (*pqueue) -> rear = NULL ;
	(*pqueue) -> items = 0 ;

	return 1 ;
}

static int Queue_Is_Empty (const Queue * const pqueue)
{
	return 0 == (*pqueue) -> items ;
}

static int En_Queue (const Queue * const pqueue, const Item2 item2)
{
	Node2 * new_node ;

	new_node = Make_Node2 (item2) ;
	if (!new_node)
		return 0 ;
	if (Queue_Is_Empty (pqueue))
		(*pqueue) -> front = (*pqueue) -> rear = new_node ;
	else
	{
		(*pqueue) -> rear -> next = new_node ;
		(*pqueue) -> rear = (*pqueue) -> rear -> next ;
	}
	(*pqueue) -> items++ ;

	return 1 ;
}

static int De_Queue (Queue * pqueue, Item2 * pitem2)
{
	Node2 * temp ;

	if (Queue_Is_Empty (pqueue))
		return 0 ;
	*pitem2 = (*pqueue) -> front -> item2 ;
	temp = (*pqueue) -> front ;
	if (1 == (*pqueue) -> items)
		(*pqueue) -> front = (*pqueue) -> rear = NULL ;
	else
		(*pqueue) -> front = (*pqueue) -> front -> next ;
	(*pqueue) -> items-- ;
	free (temp) ;
	
	return 1 ;
}

static void Release2 (const Queue * const pqueue)
{
	Node2 * scan, * temp ;

	scan = (*pqueue) -> front ;
	while (scan)
	{
		temp = scan ;
		scan = scan -> next ;
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
	new_node -> item2 = item2 ;
	new_node -> next = NULL ;

	return new_node ;
}

static int Initialize_Queue3 (Queue3 * const pqueue3)
{
	*pqueue3 = (struct queue3 *) malloc (sizeof (struct queue3)) ;
	if (!*pqueue3)
		return 0 ;
	(*pqueue3) -> front = (*pqueue3) -> rear = NULL ;
	(*pqueue3) -> items = 0 ;

	return 1 ;
}

static int Queue_Is_Empty3 (const Queue3 * const pqueue3)
{
	return 0 == (*pqueue3) -> items ;
}

static int En_Queue3 (const Queue3 * const pqueue3, const Item3 item3)
{
	Node3 * new_node ;

	new_node = Make_Node3 (item3) ;
	if (!new_node)
		return 0 ;
	if (Queue_Is_Empty3 (pqueue3))
		(*pqueue3) -> front = (*pqueue3) -> rear = new_node ;
	else
	{
		(*pqueue3) -> rear -> next = new_node ;
		(*pqueue3) -> rear = (*pqueue3) -> rear -> next ;
	}
	(*pqueue3) -> items++ ;

	return 1 ;
}

static int De_Queue3 (Queue3 * pqueue3, Item3 * pitem3)
{
	Node3 * temp ;

	if (Queue_Is_Empty3 (pqueue3))
		return 0 ;
	*pitem3 = (*pqueue3) -> front -> item3 ;
	temp = (*pqueue3) -> front ;
	if (1 == (*pqueue3) -> items)
		(*pqueue3) -> front = (*pqueue3) -> rear = NULL ;
	else
		(*pqueue3) -> front = (*pqueue3) -> front -> next ;
	(*pqueue3) -> items-- ;
	free (temp) ;
	
	return 1 ;
}

static void Release3 (const Queue3 * const pqueue3)
{
	Node3 * scan, * temp ;

	scan = (*pqueue3) -> front ;
	while (scan)
	{
		temp = scan ;
		scan = scan -> next ;
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
	new_node -> item3 = item3 ;
	new_node -> next = NULL ;

	return new_node ;
}