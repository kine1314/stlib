/*	Head.h -- ͨ��ͷ�ļ�	*/
#include <stdio.h>
#include <stdlib.h>

/*	���к궨�����������Ͷ���	*/
#ifndef QUEUE_HAS_BEEN_DEFINED
#define QUEUE_HAS_BEEN_DEFINED 1
#define FALSE (0)	/*	Without ';'	!	*/
#define TRUE (1)

typedef int BOOL ;
typedef int Item ;
typedef struct queueNode
{
	Item item ;
	struct queueNode * next ;
} QueueNode ;
typedef struct queue
{
	QueueNode * front, * rear ;
	int current ;
} * Queue ;
#endif

/*	��С�Ѻ궨�����������Ͷ���	*/
#ifndef PRIORITYQUEUE_HAS_BEEN_DEFINED
#define PRIORITYQUEUE_HAS_BEEN_DEFINED 1
#define FALSE (0)
#define TRUE (1)
#define PARENT(i) (i / 2)
#define LEFT(i) (i * 2)
#define RIGHT(i) (i * 2 + 1)

//typedef int BOOL ;
typedef QueueNode * PriorityNode ;
typedef struct priorityQueue
{
	PriorityNode * heap ;
	int current, size ;
} * PriorityQueue ;
#endif