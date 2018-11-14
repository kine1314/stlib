/*
 * st_mempool.h
 *
 *  Created on: 2011-12-6
 *      Author: kine
 */

#ifndef ST_MEMPOOL_H_
#define ST_MEMPOOL_H_
#if 0
/*
 * 当频繁地用malloc申请内存，然后再用free释放内存时，会存在两个主要问题。
 * 		(1)第一个问题是频繁的分配释放内存可能导致系统内存碎片过多；
 * 		(2)第二个问题是分配释放内存花费的时间可能比较多（这个问题不太明显）。
 * 这个时候我们就可以考虑使用内存池了。
 * 最朴素的内存池思想就是，首先你向系统申请一块很大的内存（这块内存因为很大，以致于我们常称它为memory pool），
 * 然后你在上面实现类似于malloc和free等操作。当你需要分配内存时，你用自己的类malloc函数从内存池上取一小块给使用者
 * (后文称之为小内存块)，当用类free函数释放从内存池上取得的内存时，这个小内存块也并不归还给系统，而只是还给内存池。
 *
 * 最近写telnet还原程序，写了个简易内存池，和大家分享下。
 * 这个内存池提供这样的功能：
 * 		i）提供类malloc函数mem_alloc从内存池上获取固定大小的内存，提供类free函数mem_free释放内存到内存池中；
 * 		ii）内存池初始大小为某个固定大小（BUF_SIZE）的n倍，当内存池中的内存不够用时，内存池能以一定步长增长直到无系统内存。
 * 要实现这些功能，首先应该用一个数据结构（mem_node_t）将内存池中的各个小内存块挂起来；
 * 然后为了使内存池能够以一定步长增长，我们要能分配多个大的内存块（即多个小内存池），
 * 为了能顺利的管理各个大的内存块，需要一个数据结构（mem_block_t）来记录这些信息；
 * 最后，内存池的当前状态（包括可分配的空闲链表，空闲的小内存块的个数等）是我们感兴趣的东西，所以用数据结构（mem_pool_t）来记录。
*/
typedef union _mem_node
{
	union _mem_node *next;
	char buf[BUF_SIZE];
}mem_node_t, *pmem_node_t;

typedef struct _mem_block
{
	mem_node_t *node_head; 		/* 第一个小内存块 */
	mem_node_t *node_tail; 		/* 最后一个小内存块 */
	int node_cnt; 				/* node count */
	struct _mem_block *next;
}mem_block_t, *pmem_block_t;


typedef struct _mem_pool
{
	mem_block_t *block_head; 	/* 第一个大内存块 */
	mem_block_t *block_tail; 	/* 最后一个大内存块 */
	mem_node_t *free_head; 		/* 当前空闲链表的头指针 */
	int block_cnt; 				/* block count */
	int free_cnt; 				/* free node count; */
	int base; 					/* 内存池的初始大小 */
	int step; 					/* 内存池的增长步长 */
}mem_pool_t, *pmem_pool_t;


/*
 * 然后提供了一些操作函数：
 * 		mem_pool_init用来初始化内存池；
 * 		mem_pool_destroy用来释放内存池，将内存池所占空间归还系统；
 * 		print_mem_pool_info用来打印内存池的信息；
 * 		mem_alloc，用来从内存池上分配小内存块；
 * 		mem_free，将小内存块归还给内存池。
 * mem_alloc和mem_free操作的就是内存池的空闲链表，前者从空闲链表取一个结点，后者将一个结点插入空闲链表。
 * 而这个空闲链表是由mem_pool_init初始化的，而且当内存池增长时，即增加新的大内存块时，
 * 我们将大内存块上的小内存块也挂接到这个空闲链表上来。需要注意的是小内存块的数据结构用了联合，
 * 这是因为小内存块要么是挂接在空闲链表上，要么是分配给了用户，必居且只能居这两种状态之一,这个数据结构可根据需求适当改进。
 * 在码代码之前，要补充说明的是，不少内存池都提供了分配不同大小的内存块的功能，将多个不同大小的本内存池链接起来也可实现这些功能，
 * 改动是比较容易的^_^
 * 最后，本内存池在vc6下验证当频繁分配释放100字节大小的内存时，本内存池效率约是直接malloc和free的10倍，当分配大小变小时，
 * 效率比有所降低，但当分配大小增大时，效率比有所升高，分配1000字节大小的内存时，效率比约为100。
*/
#endif


#include "stlib.h"

ST_BEGIN_DECLS;
#define MEM_POOL_DEBUG


#define BUF_SIZE 100				// 一小块内存的大小

#define BASE_COUNT 10000			// 默认内存块的大小

#define STEP_COUNT 1000				// 增长步长

/* #pragma pack () */



/* */
/* 小内存块节点结构 */
typedef union _mem_node
{
    union _mem_node *next;
    char buf[BUF_SIZE];
}mem_node_t, *pmem_node_t;



/* used to store block information */

typedef struct _mem_block
{
    mem_node_t *node_head;					/* 第一个小内存块 */
    mem_node_t *node_tail;					/* 最后一个小内存块 */
    int node_cnt; 							/* 记录一个block node count */
    struct _mem_block *next;
}mem_block_t, *pmem_block_t;



/* used to store the pool information */
typedef struct _mem_pool
{
    mem_block_t *block_head;			/* 第一个大内存块 */
    mem_block_t *block_tail;			/* 最后一个大内存块 */
    mem_node_t *free_head;				/* 当前空闲链表的头指针 */
    int block_cnt; 						/* block count */
    int free_cnt; 						/* free node count; */
    int base;							/* 内存池的初始大小 */
    int step;							/* 内存池的增长步长 */
}mem_pool_t, *pmem_pool_t;





/* mem_pool will have at least base blocks, and will increase steps a time if needed */

int mem_pool_init(int base, int step);

void mem_pool_destroy(void);

void print_mem_pool_info(void);

/* since the block size is constant, this function need no input parameter */

void *mem_alloc(void);

void mem_free(void *ptr);


ST_END_DECLS ;
#endif /* ST_MEMPOOL_H_ */
