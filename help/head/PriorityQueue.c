/*	PriorityQueue.c -- ��С��ʵ���ļ�	*/
#include "PriorityQueue.h"

/*	�ֲ���������	*/

static BOOL percolateUp_P (PriorityNode * const heap, const int position, const int size) ;
static BOOL percolateDown_P (PriorityNode * const heap, const int position, const int size) ;

/*	�ӿں�������	*/

BOOL Initialize_P (PriorityQueue * const ppq, const int size)
{
	if (size <= 0)
		return FALSE ;
	*ppq = (struct priorityQueue *) malloc (sizeof (struct priorityQueue)) ;
	if (NULL == *ppq)
		return FALSE ;
	(*ppq) -> heap = (PriorityNode *) malloc (sizeof (PriorityNode) * (size + 1)) ;
	if (NULL == (*ppq) -> heap)
	{
		free (*ppq) ;
		return FALSE ;
	}
	(*ppq) -> current = 0 ;
	(*ppq) -> size = size ;

	return TRUE ;
}

BOOL IsEmpty_P (const PriorityQueue * const ppq)
{
	if (0 == (*ppq) -> current)
		return TRUE ;
	else
		return FALSE ;
}

BOOL IsFull_P (const PriorityQueue * const ppq)
{
	if ((*ppq) -> current == (*ppq) -> size)
		return TRUE ;
	else
		return FALSE ;
}

BOOL Insert_P (const PriorityQueue * const ppq, const PriorityNode pn)
{
	if (TRUE == IsFull_P (ppq))
		return FALSE ;
	(*ppq) -> heap[++(*ppq) -> current] = pn ;		// �������
	percolateUp_P ((*ppq) -> heap, (*ppq) -> current, (*ppq) -> current) ;
	
	return TRUE ;
}

PriorityNode DeleteMin_P (const PriorityQueue * const ppq)
{
	PriorityNode record ;

	if (IsEmpty_P (ppq))
		return NULL ;
	record = (*ppq) -> heap[1] ;
	(*ppq) -> heap[1] = (*ppq) -> heap[(*ppq) -> current--] ;

	percolateDown_P ((*ppq) -> heap, 1, (*ppq) -> current) ;

	return record ;
}

BOOL IncreaseKey_P (const PriorityQueue * const ppq, const int position, const Item delta)
{
	if (position < 1 || position > (*ppq) -> current || delta <= 0)
		return FALSE ;
	(*ppq) -> heap[position] -> item += delta ;
	percolateDown_P ((*ppq) -> heap, position, (*ppq) -> current) ;

	return TRUE ;
}

BOOL DecreaseKey_P (const PriorityQueue * const ppq, const int position, const Item delta)
{
	if (position < 1 || position > (*ppq) -> current || delta <= 0)
		return FALSE ;
	(*ppq) -> heap[position] -> item -= delta ;
	percolateUp_P ((*ppq) -> heap, position, (*ppq) -> current) ;

	return TRUE ;
}

void Release_P (const PriorityQueue * const ppq)
{
	free ((*ppq) -> heap) ;
	free (*ppq) ;
}

/*	�ֲ���������	*/

static BOOL percolateUp_P (PriorityNode * const heap, const int position, const int size)
{
	PriorityNode temp ;
	int i ;
	
	if (position < 1 || position > size)		// �ж�λ���Ƿ�Ϸ�
		return FALSE ;

	temp = heap[position] ;						// ��ȡ��Ҫ�����node
	// Ѱ�Һ��ʵ�λ��
	for (i = position; PARENT(i) >= 1 && heap[PARENT(i)]->item > temp -> item; i = PARENT (i))
		heap[i] = heap[PARENT (i)] ;
	heap[i] = temp ;

	return TRUE ;
}

static BOOL percolateDown_P (PriorityNode * const heap, const int position, const int size)
{
	PriorityNode temp ;
	int i, child ;

	if (position < 1 || position > size)
		return FALSE ;
	temp = heap[position] ;
	for (i = position; LEFT (i) <= size; i = child)
	{
		child = LEFT (i) ;
		if (child != size && heap[child] -> item > heap[child + 1] -> item)
			child = RIGHT (i) ;
		if (temp -> item > heap[child] -> item)
			heap[i] = heap[child] ;
		else
			break ;
	}
	heap[i] = temp ;

	return TRUE ;
}