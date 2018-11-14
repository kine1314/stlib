/*
 * st_pthread_pool.c
 *
 *  Created on: 2011-12-6
 *      Author: kine
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "st_pthread_pool.h"

/*	�ֲ���������	*/
static void *thread_routine (void *arg);

/*	ȫ�ֱ�������	*/
static CThread_pool *pool = NULL;


/*	�ӿں�������	*/
void pool_init (int max_thread_num)
{
	int i = 0;

	pool = (CThread_pool *) malloc (sizeof (CThread_pool));

	pthread_mutex_init (&(pool->queue_lock), NULL);
	pthread_cond_init (&(pool->queue_ready), NULL);

	pool->queue_head = NULL;

	pool->max_thread_num = max_thread_num;		// �̳߳صĴ�С
	pool->cur_queue_size = 0;

	pool->shutdown = 0;							// �̳߳��Ƿ����ٵı�־
	// ��������id�ռ�
	pool->threadid = (pthread_t *) malloc (max_thread_num * sizeof (pthread_t));

	// �������������߳̾��;�̳߳صĸ������߳̾���ĸ���
	for (i = 0; i < max_thread_num; i++)
	{
		pthread_create (&(pool->threadid[i]), NULL, thread_routine, NULL);
	}
}




/*�����̳߳أ��ȴ������е����񲻻��ٱ�ִ�У������������е��̻߳�һֱ����������������˳�*/
int pool_destroy (void)
{
	int i;

	if (pool->shutdown)
		return -1;/*��ֹ���ε���*/

	pool->shutdown = 1;

	/*�������еȴ��̣߳��̳߳�Ҫ������*/
	pthread_cond_broadcast (&(pool->queue_ready));

	/*�����ȴ��߳��˳�������ͳɽ�ʬ��*/
	for (i = 0; i < pool->max_thread_num; i++)
		pthread_join (pool->threadid[i], NULL);

	free (pool->threadid);

	/*���ٵȴ�����*/
	CThread_worker *head = NULL;
	while (pool->queue_head != NULL)
	{
		head = pool->queue_head;
		pool->queue_head = pool->queue_head->next;
		free (head);
	}
	/*���������ͻ�����Ҳ����������*/
	pthread_mutex_destroy(&(pool->queue_lock));
	pthread_cond_destroy(&(pool->queue_ready));

	free (pool);
	/*���ٺ�ָ���ÿ��Ǹ���ϰ��*/
	pool=NULL;
	return 0;
}

/*���̳߳��м�������*/
int pool_add_worker (void *(*process) (void *arg), void *arg)
{
	/*����һ��������*/
	CThread_worker *newworker = (CThread_worker *) malloc (sizeof (CThread_worker));
	newworker->process = process;				// ����ʵ��
	newworker->arg = arg;
	newworker->next = NULL;/*�����ÿ�*/

	pthread_mutex_lock (&(pool->queue_lock));
	/*��������뵽�ȴ�������*/
	CThread_worker *member = pool->queue_head;
	if (member != NULL)					// ���в�Ϊ�յ�ʱ��
	{
		while (member->next != NULL)
		{
			member = member->next;
		}

		member->next = newworker;		// new work �������
	}
	else
	{
		pool->queue_head = newworker;
	}

	assert (pool->queue_head != NULL);

	pool->cur_queue_size++;				// ���д�С+1
	pthread_mutex_unlock (&(pool->queue_lock));
	/*���ˣ��ȴ��������������ˣ�����һ���ȴ��̣߳�ע����������̶߳���æµ�����û���κ�����*/
	pthread_cond_signal (&(pool->queue_ready));
	return 0;
}

/*	�ֲ���������	*/
static void *thread_routine (void *arg)
{
	printf ("starting thread 0x%x\n", pthread_self ());
	while (1)
	{
		pthread_mutex_lock (&(pool->queue_lock));		// ���������ٲ�������������
		printf("haha\n");
		/*����ȴ�����Ϊ0���Ҳ������̳߳أ���������״̬; ע��
		pthread_cond_wait��һ��ԭ�Ӳ������ȴ�ǰ����������Ѻ�����*/
		while (pool->cur_queue_size == 0 && !pool->shutdown)
		{
			printf ("thread 0x%x is waiting\n", pthread_self ());

			pthread_cond_wait (&(pool->queue_ready), &(pool->queue_lock));	// �ȴ�������ź�
		}

		/*�̳߳�Ҫ������*/
		if (pool->shutdown)
		{
			/*����break,continue,return����ת��䣬ǧ��Ҫ�����Ƚ���*/
			pthread_mutex_unlock (&(pool->queue_lock));
			printf ("thread 0x%x will exit\n", pthread_self ());
			pthread_exit (NULL);
		}

		printf ("thread 0x%x is starting to work\n", pthread_self ());

		/*assert�ǵ��Եĺð���*/
		assert (pool->cur_queue_size != 0);
		assert (pool->queue_head != NULL);

		/*�ȴ����г��ȼ�ȥ1����ȡ�������е�ͷԪ��*/
		pool->cur_queue_size--;
		CThread_worker *worker = pool->queue_head;		// ��ȡ���е�һ������
		pool->queue_head = worker->next;
		pthread_mutex_unlock (&(pool->queue_lock));

		/*���ûص�������ִ������*/
		(*(worker->process)) (worker->arg);
		free (worker);
		worker = NULL;
	}
	/*��һ��Ӧ���ǲ��ɴ��*/
	pthread_exit (NULL);
}

