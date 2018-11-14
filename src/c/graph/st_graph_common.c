/*	Stack_ADT.c -- 栈模型实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "st_graph_common.h"


/*	局部函数声明	*/
 
static GStack_Node * Make_Node (const GSName * const panme) ;

/*	接口函数定义	*/

int InitializeGStack (GStack * const pstack)
{
	*pstack = (GStack_Node *) malloc (sizeof (GStack_Node)) ;
	if (NULL == *pstack)
		return 0 ;
	else
	{
		*pstack = NULL ;
		return 1 ;
	}
}

int GStackIsEmpty (const GStack * const pstack)
{
	return NULL == *pstack ;
}

int GSPush (GStack * const pstack, const GSName * const pname)
{
	GStack_Node * new_node ;

	new_node = Make_Node (pname) ;
	if (new_node)
	{
		new_node->next = *pstack ;		// 放在链表头
		*pstack = new_node ;
		return 1 ;
	}
	else
		return 0 ;
}

int GSPop (GStack * const pstack, GSName * const pname)
{
	GStack_Node * temp ;

	if (GStackIsEmpty (pstack))
		return 0 ;
	else
	{
		*pname = (*pstack)->name ;
		temp = *pstack ;
		*pstack = (*pstack)->next ;		// 栈顶先出
		free (temp) ;
		return 1 ;
	}
}

void GSTraversal (const GStack * const pstack, void (* pfun) (const GStack_Node * const stack_node))
{
	GStack_Node * scan = *pstack ;

	while (scan)
	{
		(* pfun) (scan) ;
		scan = scan->next ;
	}
}

void ReleaseGStack (const GStack * const pstack)
{
	GStack_Node * temp, * scan = *pstack ;

	while (scan)
	{
		temp = scan ;
		scan = scan->next ;
		free (temp) ;
	}
}

/*	局部函数定义	*/

static GStack_Node * Make_Node (const GSName * const pname)
{
	GStack_Node * new_node ;

	new_node = (GStack_Node *) malloc (sizeof (GStack_Node)) ;
	if (new_node)
	{
		new_node->name = *pname ;
	}

	return new_node ;
}

/*	局部函数声明	*/

static GQueue_Node * Make_Queue_Node (const GQueue_Item * const pqueue_item) ;

/*	接口函数定义	*/

int InitializeGQueue (GQueue * const pqueue)
{
	*pqueue = (struct queue *) malloc (sizeof (struct queue)) ;
	if (*pqueue)
	{
		(*pqueue)->front = (*pqueue)->rear = NULL ;
		return 1 ;
	}
	else
		return 0 ;
}

int GQueueIsEmpty (const GQueue * const pqueue)
{
	return NULL == (*pqueue)->front ;
}

int EnGQueue (GQueue * const pqueue, const GQueue_Item * const pqueue_item)
{
	GQueue_Node * new_queue_node ;

	new_queue_node = Make_Queue_Node (pqueue_item) ;
	if (NULL == new_queue_node)
		return 0 ;
	if (GQueueIsEmpty (pqueue))
		(*pqueue)->front = (*pqueue)->rear = new_queue_node ;
	else
		(*pqueue)->rear = (*pqueue)->rear->next = new_queue_node ;

	return 1 ;
}

int DeQueue (GQueue * const pqueue, GQueue_Item * const pqueue_item)
{
	GQueue_Node * temp ;

	if (GQueueIsEmpty (pqueue))
		return 0 ;
	*pqueue_item = (*pqueue)->front->queue_item ;
	if ((*pqueue)->front == (*pqueue)->rear)
	{
		free ((*pqueue)->front) ;
		(*pqueue)->front = (*pqueue)->rear = NULL ;
	}
	else
	{
		temp = (*pqueue)->front ;
		(*pqueue)->front = (*pqueue)->front->next ;
		free (temp) ;
	}

	return 1 ;
}

void ReleaseGQueue (GQueue * const pqueue)
{
	GQueue_Node * temp, * scan = (*pqueue)->front ;

	while (scan)
	{
		temp = scan ;
		scan = scan->next ;
		free (temp) ;
	}
	free (*pqueue) ;
}

/*	局部函数定义	*/

static GQueue_Node * Make_Queue_Node (const GQueue_Item * const pqueue_item)
{
	GQueue_Node * new_queue_node ;

	new_queue_node = (GQueue_Node *) malloc (sizeof (GQueue_Node)) ;
	if (new_queue_node)
	{
		new_queue_node->queue_item = *pqueue_item ;
		new_queue_node->next = NULL ;
	}

	return new_queue_node ;
}


// 临时配合邻接表使用的hash表



/*	接口函数定义	*/

int GHash (const GHash_Table * const pht, const GHName * const pname)
{
	return *pname * PRIME % (*pht)->capacity ;
}

int Initialize_GH (GHash_Table * const pht, const int capacity)
{
	int real_capacity, i ;

	if (capacity <= 0)
		return 0 ;
	real_capacity = Get_Prime_Size (capacity) ;
	*pht = (struct Ghash_table *) malloc (sizeof (struct Ghash_table)) ;
	if (NULL == *pht)
		return 0 ;
	(*pht)->lists = (GHCell *) malloc (sizeof (GHCell) * real_capacity) ;
	if (NULL == (*pht)->lists)
	{
		free (*pht) ;
		return 0 ;
	}
	for (i = 0; i < real_capacity; i++)
	{
		(*pht)->lists[i].entry = Empty ;
		(*pht)->lists[i].name = NUL ;
		(*pht)->lists[i].be_deleted = FALSE ;
	}
	(*pht)->current = 0 ;
	(*pht)->capacity = real_capacity ;

	return 1 ;
}

GHCell * Find_GH (const GHash_Table * const pht, const GHName * const pname)
{
	int hash_value, i = 1, capacity = (*pht)->capacity ;

	hash_value = GHash (pht, pname) ;
	while (Legitimate == (*pht)->lists[hash_value].entry && (*pht)->lists[hash_value].name != *pname)
	{
		putchar ('\a') ;
		hash_value = (hash_value + Square_ (i++)) % capacity ;
	}

	return (*pht)->lists + hash_value ;
}

int Insert_GH (const GHash_Table * const pht, const GHName * const pname, const int index)
{
	GHCell * p ;

	if ((*pht)->current > (*pht)->capacity / 2 + 1)
		return FAILED ;
	p = Find_GH (pht, pname) ;
	if (Empty == p->entry || Deleted == p->entry)
	{
		p->entry = Legitimate ;
		p->name = *pname ;
		p->index_in_adjacenty_list = index ;
	}
	(*pht)->current++ ;

	return (p - (*pht)->lists) / sizeof (GHCell) ;
}

int Delete_GH (const GHash_Table * const pht, const GHName * const pname)
{
	GHCell * p ;

	p = Find_GH (pht, pname) ;
	if (*pname == p->name && Legitimate == p->entry)
	{
		p->entry = Deleted ;
		(*pht)->current-- ;
		return 1 ;
	}
	else
		return 0 ;
}

void Release_GH (const GHash_Table * const pht)
{
	free ((*pht)->lists) ;
	free (*pht) ;
}

// 配合dijkstra实现的二叉堆
/*	局部函数声明	*/

static int Percolate_Up (const GBinary_Heap * const pbh, const int index) ;
static int Percolate_Down (const GBinary_Heap * const pbh, const int index) ;

/*	接口函数定义	*/

int Initialize_GB (GBinary_Heap * const pbh, const int capacity)
{
	if (capacity < 0)
		return 0 ;
	*pbh = (struct Gbinary_heap *) malloc (sizeof (struct Gbinary_heap)) ;
	if (NULL == *pbh)
		return 0 ;
	(*pbh)->heap = (GHeap_Item *) malloc (sizeof (GHeap_Item) * (capacity + 1)) ;
	if (NULL == (*pbh)->heap)
	{
		free (*pbh) ;
		return 0 ;
	}
	(*pbh)->heap[0] = (Vertex_w *) malloc (sizeof (Vertex_w)) ;
	if (NULL == (*pbh)->heap[0])
	{
		free ((*pbh)->heap) ;
		free (*pbh) ;
		return 0 ;
	}
	(*pbh)->heap[0]->dist = NEGATIVEINFINITY ;
	(*pbh)->capacity = capacity ;
	(*pbh)->current = 0 ;

	return 1 ;
}

int Insert_GB (const GBinary_Heap * const pbh, const GHeap_Item hi)
{
	if ((*pbh)->current == (*pbh)->capacity)
		return 0 ;
	(*pbh)->heap[++(*pbh)->current] = hi ;
	Percolate_Up (pbh, (*pbh)->current) ;

	return 1 ;
}

GHeap_Item DeleteMin_GB (const GBinary_Heap * const pbh)
{
	GHeap_Item hi ;

	if (0 == (*pbh)->current)
		return (*pbh)->heap[0] ;
	hi = (*pbh)->heap[1] ;
	Percolate_Down (pbh, 1) ;
	(*pbh)->current-- ;

	return hi ;
}

int IncreaseKey_GB (const GBinary_Heap * const pbh, const int index, const int triangle)
{
	if (0 == (*pbh)->current || index <= 0 || index > (*pbh)->current || triangle < 0)
		return 0 ;
	(*pbh)->heap[index]->dist += triangle ;
	Percolate_Down (pbh, index) ;

	return 1 ;
}

int DecreaseKey_GB (const GBinary_Heap * const pbh, const int index, const int triangle)
{
	if (0 == (*pbh)->current || index <= 0 || index > (*pbh)->current || triangle < 0)
		return 0 ;
	(*pbh)->heap[index]->dist -= triangle ;
	Percolate_Up (pbh, index) ;

	return 1 ;
}

void Release_GB (const GBinary_Heap * const pbh)
{
	free ((*pbh)->heap[0]) ;
	free ((*pbh)->heap) ;
	free (*pbh) ;
}

/*	局部函数定义	*/

static int Percolate_Up (const GBinary_Heap * const pbh, const int index)
{
	int dist, i ;

	if (index <= 0 || index > (*pbh)->current)
		return 0 ;
	dist = (*pbh)->heap[index] -> dist ;
	for (i = index; i / 2 > 0; i /= 2)
	{
		if (dist < (*pbh)->heap[i / 2] -> dist)
			(*pbh)->heap[i / 2] = (*pbh)->heap[i] ;
		else
			break ;
	}
	(*pbh)->heap[i] = (*pbh)->heap[index] ;

	return 1 ;
}

static int Percolate_Down (const GBinary_Heap * const pbh, const int index)
{
	int dist, i, child, current ;

	if (index <= 0 || index > (*pbh)->current)
		return 0 ;
	current = (*pbh)->current ;
	dist = (*pbh)->heap[current]->dist ;
	for (i = index; i * 2 <= current ; i = child)
	{
		child = i * 2 ;
		if (child != current && (*pbh)->heap[child]->dist > (*pbh)->heap[child + 1]->dist)
			child++ ;
		if (dist > (*pbh)->heap[child]->dist)
			(*pbh)->heap[i] = (*pbh)->heap[child] ;
		else
			break ;
	}
	(*pbh)->heap[i] = (*pbh)->heap[current] ;

	return 1 ;
}



// 二叉堆 for kruskal算法
/*	局部函数声明	*/

static int Percolate_Up_kruskal (const Binary_Heap_kruskal * const pbh, const int index) ;
static int Percolate_Down_kruskal (const Binary_Heap_kruskal * const pbh, const int index) ;

/*	接口函数定义	*/

int Initialize_B_kruskal (Binary_Heap_kruskal * const pbh, const int capacity)
{
	*pbh = (struct binary_heap_kruskal *) malloc (sizeof (struct binary_heap_kruskal)) ;
	if (NULL == *pbh)
		return 0 ;
	(*pbh)->heap = (Edge_kruskal *) malloc (sizeof (Edge_kruskal) * (capacity + 1)) ;
	if (NULL == (*pbh)->heap)
	{
		free (*pbh) ;
		return 0 ;
	}
	(*pbh)->heap[0].weight = NEGATIVEINFINITY ;
	(*pbh)->current = 0 ;
	(*pbh)->capacity = capacity ;

	return 1 ;
}

int Insert_B_kruskal (const Binary_Heap_kruskal * const pbh, const Edge_kruskal * const pd)
{
	int current ;

	if ((*pbh)->current == (*pbh)->capacity)
		return 0 ;
	current = ++(*pbh) -> current ;
	(*pbh)->heap[current].v_hash_value = pd->v_hash_value ;
	(*pbh)->heap[current].w_hash_value = pd->w_hash_value ;
	(*pbh)->heap[current].weight = pd->weight ;
	Percolate_Up_kruskal (pbh, current) ;

	return 1 ;
}

int DeleteMin_B_kruskal (const Binary_Heap_kruskal * const pbh, Edge_kruskal * const pd)
{
	if ((*pbh)->current <= 0)
		return 0 ;
	*pd = (*pbh)->heap[1] ;
	Percolate_Down_kruskal (pbh, (*pbh)->current) ;
	(*pbh)->current-- ;

	return 1 ;
}

void Release_B_kruskal (const Binary_Heap_kruskal * const pbh)
{
	free ((*pbh)->heap) ;
	free (*pbh) ;
}

/*	局部函数定义	*/

static int Percolate_Up_kruskal (const Binary_Heap_kruskal * const pbh, const int index)
{
	Edge_kruskal temp = (*pbh)->heap[index] ;
	int i ;

	if (index <= 0 || index > (*pbh)->current)
		return 0 ;
	for (i = index; i / 2 > 0; i /= 2)
	{
		if (temp.weight < (*pbh)->heap[i / 2].weight)
			(*pbh)->heap[i] = (*pbh)->heap[i / 2] ;
		else
			break ;
	}
	(*pbh)->heap[i] = temp ;

	return 1 ;
}

static int Percolate_Down_kruskal (const Binary_Heap_kruskal * const pbh, const int index)
{
	int current = (*pbh)->current ;
	Edge_kruskal temp = (*pbh)->heap[current] ;
	int i, child ;

	if (index <= 0 || index > (*pbh)->current)
		return 0 ;
	for (i = 1; i * 2 <= current; i = child)
	{
		child = i * 2 ;
		if (child != current && (*pbh)->heap[child].weight > (*pbh)->heap[child + 1].weight)
			child++ ;
		if (temp.weight > (*pbh)->heap[child].weight)
			(*pbh)->heap[i] = (*pbh)->heap[child] ;
		else
			break ;
	}
	(*pbh)->heap[i] = temp ;

	return 1 ;
}



