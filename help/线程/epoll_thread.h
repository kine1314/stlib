/*
几个用到的类型定义以及全局变量bq
*/
char smtp_cmd_format;
struct epoll_event ev, events[MAX_EPOLL_SIZE];
int kdpfd,nfds;
struct block_queue
{
	int queue[THREADS_COUNT];
	long size;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
}block_queue_t;
block_queue_t bq;
struct block_queue_param
{
	void* func;
	void* queue;
}block_queue_param_t;

