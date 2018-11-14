/*
 * st_pthread_pool.h
 *
 *  Created on: 2011-12-6
 *      Author: kine
 */

#ifndef ST_PTHREAD_POOL_H_
#define ST_PTHREAD_POOL_H_
#include "stlib.h"

ST_BEGIN_DECLS;

/*�߳���������*/
typedef struct worker
{
	/*�ص���������������ʱ����ô˺�����ע��Ҳ��������������ʽ*/
	void *(*process) (void *arg);
	void *arg;/*�ص������Ĳ���*/
	struct worker *next;
} CThread_worker;

/*�̳߳ؽṹ*/
typedef struct
{
	pthread_mutex_t queue_lock;
	pthread_cond_t queue_ready;

	/*����ṹ���̳߳������еȴ�����*/
	CThread_worker *queue_head;

	/*�Ƿ������̳߳�*/
	int shutdown;
	pthread_t *threadid;
	/*�̳߳�������Ļ�߳���Ŀ*/
	int max_thread_num;
	/*��ǰ�ȴ����е�������Ŀ*/
	int cur_queue_size;

} CThread_pool;

void pool_init (int max_thread_num);
int pool_destroy (void);
int pool_add_worker (void *(*process) (void *arg), void *arg);

ST_END_DECLS;
#endif /* ST_PTHREAD_POOL_H_ */
