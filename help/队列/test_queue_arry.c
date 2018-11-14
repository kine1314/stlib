#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct _QUEUE_NODE
{
	int* pData;
	int length;			/* for the max size */
	int head ;
	int tail;
	int count;			/* the current count */
}QUEUE_NODE;


QUEUE_NODE* alloca_queue(int number)
{
	QUEUE_NODE* pQueueNode;
	if( 0 == number)
		return NULL;

	pQueueNode = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE));
	assert(NULL != pQueueNode);
	memset(pQueueNode, 0, sizeof(QUEUE_NODE));

	pQueueNode->pData = (int*)malloc(sizeof(int) * number);
	if(NULL == pQueueNode->pData){
		free(pQueueNode);
		return NULL;
	}

	pQueueNode->head = pQueueNode->tail = -1 ;
	pQueueNode->count = 0 ;
	pQueueNode->length = number;
	return pQueueNode;
}


int delete_queue(const QUEUE_NODE* pQueueNode)
{
	if(NULL == pQueueNode) 
		return 0;
	
	if(NULL == pQueueNode->pData)
		return 0 ;
	
	free(pQueueNode->pData);
	free((void*)pQueueNode);
	return 1;
}


int insert_queue(QUEUE_NODE* pQueueNode, int value)
{
	if(NULL == pQueueNode)
		return 0;

	if(pQueueNode->length == pQueueNode->count)		/* the queue is full */
		return 0;
/*
	pQueueNode->tail = (pQueueNode->tail + 1) % pQueueNode->length;
	pQueueNode->pData[pQueueNode->tail] = value;  
	pQueueNode->count ++;
*/

	if(pQueueNode->tail == -1)
		pQueueNode->tail = pQueueNode->head = 0 ;		/* the first node */
	else
		pQueueNode->tail = (pQueueNode->tail + 1)%pQueueNode->length ;
	pQueueNode->pData[pQueueNode->tail] = value;  
	pQueueNode->count++;

	return 1;
}

int get_queue_data(QUEUE_NODE* pQueueNode, int* value)
{
	if(NULL == pQueueNode || NULL == value)
		return 0;

	if(0 == pQueueNode->count)			/* the queue is null */
		return 0;

	*value = pQueueNode->pData[pQueueNode->head];
	if(pQueueNode->head == pQueueNode->tail)
		pQueueNode->head = pQueueNode->tail = -1 ;
	else
		pQueueNode->head = (pQueueNode->head + 1) % pQueueNode->length ;
	pQueueNode-> count --;

/*
	pQueueNode-> pData[pQueueNode->head] = 0; 
	pQueueNode-> count --;
	pQueueNode->head = (pQueueNode->head + 1) % pQueueNode->length;
*/
	return 1;
}


int  get_total_number(const QUEUE_NODE* pQueueNode)
{
	if(NULL == pQueueNode)
		return 0;

	return pQueueNode->count;
}

int  get_total_length(const QUEUE_NODE* pQueueNode)
{
	if(NULL == pQueueNode)
		return 0;

	return pQueueNode->length;
}

void 

int main(void)
{
	QUEUE_NODE* queue ;
	int data ;

	queue = alloca_queue(5) ;
	insert_queue(queue, 87);
	insert_queue(queue, 66);
	insert_queue(queue, 56);
	get_queue_data(queue, &data);
	insert_queue(queue, 98);
	insert_queue(queue, 34);
	insert_queue(queue, 33);
	printf("len = [%d], data[%d]\n", get_total_number(queue), data);
	printf("[%d]\n", queue->pData[0]);

}


