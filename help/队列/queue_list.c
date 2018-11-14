#include <stdio.h>
#include <stdlib.h>
typedef int elemType;
/************************************************************************/
/*                    �����ǹ��ڶ������Ӵ洢������6���㷨               */
/************************************************************************/
struct sNode
{
	elemType data;				/* ֵ�� */
    struct sNode *next;			/* ����ָ�� */
};
struct queueLK
{
    struct sNode *front;    /* ����ָ�� */
    struct sNode *rear;        /* ��βָ�� */
};
    /* 1.��ʼ������ */
void initQueue(struct queueLK *hq)
{
    hq->front = hq->rear = NULL;        /* �Ѷ��׺Ͷ�βָ���ÿ� */
    return;
}
    
/* 2.�������в���һ��Ԫ��x */
void enQueue(struct queueLK *hq, elemType x)
{
    /* �õ�һ����newPָ����ָ����½�� */
    struct sNode *newP;
    newP = malloc(sizeof(struct sNode));
    if(newP == NULL)
	{
		printf("�ڴ�ռ����ʧ�ܣ� ");
		exit(1);
    }
    /* ��x��ֵ�����½���ֵ�򣬰��½���ָ�����ÿ� */
    newP->data = x;
    newP->next = NULL;
    /* ������Ϊ�գ����½�㼴�Ƕ��׽�����Ƕ�β��� */
    if(hq->rear == NULL)
	{
    	hq->front = hq->rear = newP;
    }
	else
	{    
		/* �����ӷǿգ��������޸Ķ�β����ָ����Ͷ�βָ�룬ʹָ֮���µĶ�β��� */
		//hq->rear = hq->rear->next = newP;        /* ע�⸳ֵ˳��Ŷ */
		hq->rear->next = newP ;
		hq->rear = newP ;
    }
    return;
}

/* 3.�Ӷ�����ɾ��һ��Ԫ�� */
elemType outQueue(struct queueLK *hq)
{
    struct sNode *p;
    elemType temp;
	
    /* ������Ϊ����ֹͣ���� */
    if(hq->front == NULL)
	{
		printf("����Ϊ�գ��޷�ɾ���� ");
		exit(1);
    }
    temp = hq->front->data;        /* �ݴ��βԪ���Ա㷵�� */
    p = hq->front;                /* �ݴ��βָ���Ա���ն�β��� */
    hq->front = p->next;        /* ʹ����ָ��ָ����һ����� */
    /* ��ɾ��������Ϊ�գ�����ͬʱʹ��βָ��Ϊ�� */
    if(hq->front == NULL)
	{
    	hq->rear = NULL;
    }
    free(p);        /* ����ԭ���׽�� */
    return temp;    /* ���ر�ɾ���Ķ���Ԫ��ֵ */
}

/* 4.��ȡ����Ԫ�� */
elemType peekQueue(struct queueLK *hq)
{
    /* ������Ϊ����ֹͣ���� */
    if(hq->front == NULL)
	{
		printf("����Ϊ�գ��޷�ɾ���� ");
		exit(1);
	}
	return hq->front->data;        /* ���ض���Ԫ�� */
}

/* 5.��������Ƿ�Ϊ�գ���Ϊ���򷵻�1, ���򷵻�0 */
int emptyQueue(struct queueLK *hq)
{
	/* �ж϶��׻��β��һ��ָ���Ƿ�Ϊ�ռ��� */
	if(hq->front == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/* 6.��������е�����Ԫ�� */
void clearQueue(struct queueLK *hq)
{
	struct sNode *p = hq->front;        /* ����ָ�븳��p */
	/* ����ɾ�������е�ÿһ����㣬���ʹ����ָ��Ϊ�� */
	while(p != NULL)
	{
		hq->front = hq->front->next;
		free(p);
		p = hq->front;
	}    
	/* ѭ�����������ָ���Ѿ�Ϊ�� */
	hq->rear = NULL;        /* �ö�βָ��Ϊ�� */
	return;
}
		
/************************************************************************/
int main(int argc, char* argv[])
{
	struct queueLK q;
	int a[8] = {3, 8, 5, 17, 9, 30, 15, 22};
	int i;
	initQueue(&q);
	for(i = 0; i < 8; i++)
	{
		enQueue(&q, a[i]);
	}
	fprintf(stderr, "%d \n", outQueue(&q));    fprintf(stderr, "%d  \n", outQueue(&q));
	enQueue(&q, 68);
	fprintf(stderr, "%d \n", peekQueue(&q));    fprintf(stderr, "%d  \n", outQueue(&q));
	while(!emptyQueue(&q))
	{
		fprintf(stderr, "%d ", outQueue(&q));
	}
	fprintf(stderr, "\n");
	clearQueue(&q);
}
