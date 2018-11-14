/*	MergeQueue.c -- O (NlogK) 时间将K个有序队列合并为一个新有序队列	*/
#include "Queue.h"
#include "PriorityQueue.h"

#define SIZE (5)

int main (void) ;
BOOL merge (const Queue * const array, const int number, Queue * const pNewQueue) ;

int main (void)
{
	Queue array[SIZE] ;
	Queue q1, q2, q3, q4, q5, newQueue ;
	Item item ;

	/*	Artificial element.	*/
	Initialize_Q (&q1) ;
	Initialize_Q (&q2) ;
	Initialize_Q (&q3) ;
	Initialize_Q (&q4) ;
	Initialize_Q (&q5) ;

	item = 1 ;
	EnQueue_Q (&q1, item) ;
	item = 2 ;
	EnQueue_Q (&q1, item) ;
	item = 2 ;
	EnQueue_Q (&q1, item) ;
	item = 4 ;
	EnQueue_Q (&q1, item) ;
	item = 20 ;
	EnQueue_Q (&q1, item) ;

	item = 3 ;
	EnQueue_Q (&q2, item) ;
	item = 7 ;
	EnQueue_Q (&q2, item) ;
	item = 8 ;
	EnQueue_Q (&q2, item) ;
	item = 8 ;
	EnQueue_Q (&q2, item) ;
	item = 9 ;
	EnQueue_Q (&q2, item) ;	
	item = 16 ;
	EnQueue_Q (&q2, item) ;

	item = 45 ;
	EnQueue_Q (&q3, item) ;
	item = 56 ;
	EnQueue_Q (&q3, item) ;	
	item = 77 ;
	EnQueue_Q (&q3, item) ;

	item = 14 ;
	EnQueue_Q (&q4, item) ;
	item = 67 ;
	EnQueue_Q (&q4, item) ;
	item = 78 ;
	EnQueue_Q (&q4, item) ;
	item = 89 ;
	EnQueue_Q (&q4, item) ;
	item = 90 ;
	EnQueue_Q (&q4, item) ;	
	item = 92 ;
	EnQueue_Q (&q4, item) ;

	item = 11 ;
	EnQueue_Q (&q5, item) ;
	item = 22 ;
	EnQueue_Q (&q5, item) ;
	item = 33 ;
	EnQueue_Q (&q5, item) ;
	item = 34 ;
	EnQueue_Q (&q5, item) ;
	item = 35 ;
	EnQueue_Q (&q5, item) ;	
	item = 37 ;
	EnQueue_Q (&q5, item) ;
	item = 45 ;
	EnQueue_Q (&q5, item) ;
	item = 56 ;
	EnQueue_Q (&q5, item) ;	
	item = 67 ;
	EnQueue_Q (&q5, item) ;

	array[0] = q1 ;
	array[1] = q2 ;
	array[2] = q3 ;
	array[3] = q4 ;
	array[4] = q5 ;

	/*	Initialize new queue.	*/
	Initialize_Q (&newQueue) ;
	/*	It's so attractive!	*/
	merge (array, SIZE, &newQueue) ;
	
	Release_Q (&q1) ;
	Release_Q (&q2) ;
	Release_Q (&q3) ;
	Release_Q (&q4) ;
	Release_Q (&q5) ;
	Release_Q (&newQueue) ;

	return 0 ;
}

/*	O (NlogK)	*/
// 使用优先队列来合并排序
BOOL merge (const Queue * const array, const int number, Queue * const pNewQueue)
{
	PriorityQueue pq ;
	PriorityNode temp ;
	int i , j;

	if (number <= 0 || FALSE == Initialize_P (&pq, number))
		return FALSE ;
	/*	Bulid heap.	*/
	for (i = 0; i < number; i++)
		Insert_P (&pq, array[i] -> front) ;
	/*	Core loop.	*/
	while (FALSE == IsEmpty_P (&pq))
	{	
		printf("%d\n", j++);
		temp = DeleteMin_P (&pq) ;						// 删除最小的
		EnQueue_Q (pNewQueue, temp -> item) ;
		if (temp -> next != NULL)
			Insert_P (&pq, temp -> next) ;				// 插入下一个
	}
	Release_P (&pq) ;

	return TRUE ;
}