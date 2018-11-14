#include <stdio.h>
#include <stdlib.h>
typedef int elemType;
/************************************************************************/
/*                      以下是关于队列顺序存储操作的6种算法               */
/************************************************************************/
struct queue{
	elemType *queue;        /* 指向存储队列的数组空间 */
	int front, rear, len;    /* 队首指针（下标），队尾指针（下标），队列长度变量 */
	int maxSize;            /* queue数组长度 */
};
void againMalloc(struct queue *q)
{
	/* 空间扩展为原来的2倍，原内容被自动拷贝到p所指向的存储空间中 */
	elemType *p;
	p = realloc(q->queue, 2 * q->maxSize * sizeof(elemType));
	/* 动态存储空间分配，若失败则退出运行 */
	if(!p){
		printf("空间分配失败！ ");
		exit(1);
	}
	q->queue = p;        /* 使queue指向新的队列空间 */
	fprintf(stderr, "q->rear [%d]\n", q->rear);
	/* 把原队列的尾部内容后移maxSize个位置 */
	if(q->rear != q->maxSize -1){
		int i;
		for(i = 0; i <= q->rear; i++){
			q->queue[i+q->maxSize] = q->queue[i];
		}
		fprintf(stderr, "q->rear [%d]\n", q->rear);
		q->rear += q->maxSize;        /* 队尾指针后移maxSize个位置 */
	}
	q->maxSize = 2 * q->maxSize;    /* 把队列空间大小修改为新的长度 */
	return;
}
/* 1.初始化队列 */
void initQueue(struct queue *q, int ms)
{
	/* 检查ms是否有效，若无效则退出运行 */
	if(ms <= 0){
		printf("ms值非法! ");
		exit(1);
	}
	q->maxSize = ms;        /* 置队列空间大小为ms */
	/* 动态存储空间分配，若失败则退出运行 */
	q->queue = malloc(ms * sizeof(elemType));
	if(!q->queue){
		printf("内存空间分配失败！ ");
		exit(1);
	}
	q->front = q->rear = 0;        /* 初始置队列为空 */
	return;
}
/* 2.向队列中插入元素x */
void enQueue(struct queue *q, elemType x)
{
	/* 当队列满时进行动态生分配 */
	if((q->rear + 1) % q->maxSize == q->front){
		againMalloc(q);
	}
	q->rear = (q->rear + 1) % q->maxSize;        /* 求出队尾的下一个位置 */
	q->queue[q->rear] = x;                        /* 把x的值赋给新的队尾 */
	return;
}
/* 3.从队列中删除元素并返回 */
elemType outQueue(struct queue *q)
{
	/* 若队列为空则终止运行 */
	if(q->front == q->rear){
		printf("队列为空，无法删除！ ");
		exit(1);
	}
	q->front = (q->front +1) % q->maxSize;        /* 使队首指针指向下一个位置 */
	return q->queue[q->front];                    /* 返回队首元素 */
}
/* 4.读取队首元素，不改变队列状态 */
elemType peekQueue(struct queue *q)
{
	/* 若队列为空则终止运行 */
	if(q->front == q->rear){
		printf("队列为空，无法删除！ ");
		exit(1);
	}
	return q->queue[(q->front +1) % q->maxSize];/* 队首元素是队首指针的下一个位置中的元素 */
}
/* 5.检查一个队列是否为空，若是则返回1,否则返回0 */
int emptyQueue(struct queue *q)
{
	if(q->front == q->rear){
		return 1;
	}else{
		return 0;
	}
}
/* 6.清除一个队列，并释放动态存储空间 */
void clearQueue(struct queue *q)
{
	if(q->queue != NULL){
		free(q->queue);
		q->queue = NULL;            /* 设置队列空间指针为空 */
		q->front = q->rear = 0;        /* 设置队列为空 */
		q->maxSize = 0;                /* 设置队列大小为0 */
	}
	return;
}
/************************************************************************/
int main(int argc, char* argv[])
{
	struct queue q;
	int a[8] = {3, 8, 5, 17, 9, 30, 15, 22};
	int i;
	initQueue(&q, 5);
	for(i = 0; i < 8; i++){
		enQueue(&q, a[i]);
	}
	printf("[%d]\n", q.queue[0]);
	printf("%d\n", outQueue(&q));    printf("%d \n", outQueue(&q));
	printf("[%d]\n", q.queue[0]);
	enQueue(&q, 68);
	printf("%d\n", peekQueue(&q));    printf("%d \n", outQueue(&q));
	printf("\n");
	printf("length = %d\n", q.maxSize);
	
	while(!emptyQueue(&q)){
		printf("%d ", outQueue(&q));
	}
	printf("\n");
	
	clearQueue(&q);
	//system("pause");
	return 0;
}