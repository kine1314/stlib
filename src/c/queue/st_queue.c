#include <stdio.h>
#include <malloc.h>

#include "st_queue.h"
#include "st_log.h"


/*	局部函数声明	*/

static STQueueNode_t * makeNode_Q (const QItem item) ;

/*	接口函数定义	*/

stbool STInitialize_Q (PSTQueue * const pq)
{
	*pq = (struct _STQueue_s *) malloc (sizeof (struct _STQueue_s)) ;
	if (NULL == *pq)
	{
		__err("alloc mem for queue faild \n");
		return FALSE ;
	}
	
	(*pq)->front = (*pq)->rear = NULL ;				// 头尾都是空
	(*pq)->current = 0 ;

	return TRUE ;
}

stbool STIsEmpty_Q (const PSTQueue * const pq)
{
	if (0 == (*pq)->current)
		return TRUE ;
	else
		return FALSE ;
}

stbool STEnQueue_Q (const PSTQueue * const pq, const QItem item)
{
	STQueueNode_t * newNode ;

	newNode = makeNode_Q(item) ;
	
	if (NULL == newNode)
		return FALSE ;
	
	if (STIsEmpty_Q (pq))
	{
		(*pq)->front = (*pq)->rear = newNode ;		// 如果是第一个节点，头尾都指向他
	}
	else
	{
		(*pq)->rear->next = newNode ;
		(*pq)->rear = newNode ;
	}
	(*pq)->current++ ;

	return TRUE ;
}

stbool STDeQueue_Q (const PSTQueue * const pq, QItem * const messenger)
{
	STQueueNode_t * record ;

	if (STIsEmpty_Q (pq))
		return FALSE ;
	
	record = (*pq)->front ;						// 获取队头
	*messenger = record->item ;					// 获取对头的data
	
	(*pq)->front = record->next ;				// 重置对头，对头向后移动
	
	if (record == (*pq)->rear)					// 检测是否到队尾,通过出对前的位置判断
		(*pq)->rear = NULL ;
	
	free(record) ;
	(*pq)->current-- ;

	return TRUE ;
}

void STRelease_Q (const PSTQueue * const pq)
{
	STQueueNode_t * record ;

	while ((*pq)->front != NULL)
	{
		record = (*pq)->front ;
		(*pq)->front = record->next ;
		free(record) ;
	}
	free(*pq) ;
}


/*	局部函数定义	*/

static STQueueNode_t * makeNode_Q (const QItem item)
{
	STQueueNode_t * newNode ;

	newNode = (STQueueNode_t *) malloc (sizeof (STQueueNode_t)) ;
	if (NULL == newNode)
	{
		__err("alloc mem for STQueueNode_t faild \n");
		return NULL ;
	}
	
	newNode->item = item ;
	newNode->next = NULL ;

	return newNode ;
}





