/*	Queue.c -- 队列实现文件	*/
#include "Queue.h"

/*	局部函数声明	*/

static QueueNode * makeNode_Q (const Item item) ;

/*	接口函数定义	*/

BOOL Initialize_Q (Queue * const pq)
{
	*pq = (struct queue *) malloc (sizeof (struct queue)) ;
	if (NULL == *pq)
		return FALSE ;
	(*pq) -> front = (*pq) -> rear = NULL ;
	(*pq) -> current = 0 ;

	return TRUE ;
}

BOOL IsEmpty_Q (const Queue * const pq)
{
	if (0 == (*pq) -> current)
		return TRUE ;
	else
		return FALSE ;
}

BOOL EnQueue_Q (const Queue * const pq, const Item item)
{
	QueueNode * newNode ;

	newNode = makeNode_Q (item) ;
	if (NULL == newNode)
		return FALSE ;
	if (IsEmpty_Q (pq))
		(*pq) -> front = (*pq) -> rear = newNode ;
	else
	{
		(*pq) -> rear -> next = newNode ;
		(*pq) -> rear = newNode ;
	}
	(*pq) -> current++ ;

	return TRUE ;
}

BOOL DeQueue_Q (const Queue * const pq, Item * const messenger)
{
	QueueNode * record ;

	if (IsEmpty_Q (pq))
		return FALSE ;
	record = (*pq) -> front ;
	*messenger = record -> item ;
	(*pq) -> front = record -> next ;
	if (record == (*pq) -> rear)
		(*pq) -> rear = NULL ;
	free (record) ;
	(*pq) -> current-- ;

	return TRUE ;
}

void Release_Q (const Queue * const pq)
{
	QueueNode * record ;

	while ((*pq) -> front != NULL)
	{
		record = (*pq) -> front ;
		(*pq) -> front = record -> next ;
		free (record) ;
	}
	free (*pq) ;
}

/*	局部函数定义	*/

static QueueNode * makeNode_Q (const Item item)
{
	QueueNode * newNode ;

	newNode = (QueueNode *) malloc (sizeof (QueueNode)) ;
	if (NULL == newNode)
		return NULL ;
	newNode -> item = item ;
	newNode -> next = NULL ;

	return newNode ;
}