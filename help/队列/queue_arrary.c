#include <stdio.h>
#include <stdlib.h>
typedef int elemType;
/************************************************************************/
/*                      �����ǹ��ڶ���˳��洢������6���㷨               */
/************************************************************************/
struct queue{
	elemType *queue;        /* ָ��洢���е�����ռ� */
	int front, rear, len;    /* ����ָ�루�±꣩����βָ�루�±꣩�����г��ȱ��� */
	int maxSize;            /* queue���鳤�� */
};
void againMalloc(struct queue *q)
{
	/* �ռ���չΪԭ����2����ԭ���ݱ��Զ�������p��ָ��Ĵ洢�ռ��� */
	elemType *p;
	p = realloc(q->queue, 2 * q->maxSize * sizeof(elemType));
	/* ��̬�洢�ռ���䣬��ʧ�����˳����� */
	if(!p){
		printf("�ռ����ʧ�ܣ� ");
		exit(1);
	}
	q->queue = p;        /* ʹqueueָ���µĶ��пռ� */
	fprintf(stderr, "q->rear [%d]\n", q->rear);
	/* ��ԭ���е�β�����ݺ���maxSize��λ�� */
	if(q->rear != q->maxSize -1){
		int i;
		for(i = 0; i <= q->rear; i++){
			q->queue[i+q->maxSize] = q->queue[i];
		}
		fprintf(stderr, "q->rear [%d]\n", q->rear);
		q->rear += q->maxSize;        /* ��βָ�����maxSize��λ�� */
	}
	q->maxSize = 2 * q->maxSize;    /* �Ѷ��пռ��С�޸�Ϊ�µĳ��� */
	return;
}
/* 1.��ʼ������ */
void initQueue(struct queue *q, int ms)
{
	/* ���ms�Ƿ���Ч������Ч���˳����� */
	if(ms <= 0){
		printf("msֵ�Ƿ�! ");
		exit(1);
	}
	q->maxSize = ms;        /* �ö��пռ��СΪms */
	/* ��̬�洢�ռ���䣬��ʧ�����˳����� */
	q->queue = malloc(ms * sizeof(elemType));
	if(!q->queue){
		printf("�ڴ�ռ����ʧ�ܣ� ");
		exit(1);
	}
	q->front = q->rear = 0;        /* ��ʼ�ö���Ϊ�� */
	return;
}
/* 2.������в���Ԫ��x */
void enQueue(struct queue *q, elemType x)
{
	/* ��������ʱ���ж�̬������ */
	if((q->rear + 1) % q->maxSize == q->front){
		againMalloc(q);
	}
	q->rear = (q->rear + 1) % q->maxSize;        /* �����β����һ��λ�� */
	q->queue[q->rear] = x;                        /* ��x��ֵ�����µĶ�β */
	return;
}
/* 3.�Ӷ�����ɾ��Ԫ�ز����� */
elemType outQueue(struct queue *q)
{
	/* ������Ϊ������ֹ���� */
	if(q->front == q->rear){
		printf("����Ϊ�գ��޷�ɾ���� ");
		exit(1);
	}
	q->front = (q->front +1) % q->maxSize;        /* ʹ����ָ��ָ����һ��λ�� */
	return q->queue[q->front];                    /* ���ض���Ԫ�� */
}
/* 4.��ȡ����Ԫ�أ����ı����״̬ */
elemType peekQueue(struct queue *q)
{
	/* ������Ϊ������ֹ���� */
	if(q->front == q->rear){
		printf("����Ϊ�գ��޷�ɾ���� ");
		exit(1);
	}
	return q->queue[(q->front +1) % q->maxSize];/* ����Ԫ���Ƕ���ָ�����һ��λ���е�Ԫ�� */
}
/* 5.���һ�������Ƿ�Ϊ�գ������򷵻�1,���򷵻�0 */
int emptyQueue(struct queue *q)
{
	if(q->front == q->rear){
		return 1;
	}else{
		return 0;
	}
}
/* 6.���һ�����У����ͷŶ�̬�洢�ռ� */
void clearQueue(struct queue *q)
{
	if(q->queue != NULL){
		free(q->queue);
		q->queue = NULL;            /* ���ö��пռ�ָ��Ϊ�� */
		q->front = q->rear = 0;        /* ���ö���Ϊ�� */
		q->maxSize = 0;                /* ���ö��д�СΪ0 */
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