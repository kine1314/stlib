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
 * ��Ƶ������malloc�����ڴ棬Ȼ������free�ͷ��ڴ�ʱ�������������Ҫ���⡣
 * 		(1)��һ��������Ƶ���ķ����ͷ��ڴ���ܵ���ϵͳ�ڴ���Ƭ���ࣻ
 * 		(2)�ڶ��������Ƿ����ͷ��ڴ滨�ѵ�ʱ����ܱȽ϶ࣨ������ⲻ̫���ԣ���
 * ���ʱ�����ǾͿ��Կ���ʹ���ڴ���ˡ�
 * �����ص��ڴ��˼����ǣ���������ϵͳ����һ��ܴ���ڴ棨����ڴ���Ϊ�ܴ����������ǳ�����Ϊmemory pool����
 * Ȼ����������ʵ��������malloc��free�Ȳ�����������Ҫ�����ڴ�ʱ�������Լ�����malloc�������ڴ����ȡһС���ʹ����
 * (���ĳ�֮ΪС�ڴ��)��������free�����ͷŴ��ڴ����ȡ�õ��ڴ�ʱ�����С�ڴ��Ҳ�����黹��ϵͳ����ֻ�ǻ����ڴ�ء�
 *
 * ���дtelnet��ԭ����д�˸������ڴ�أ��ʹ�ҷ����¡�
 * ����ڴ���ṩ�����Ĺ��ܣ�
 * 		i���ṩ��malloc����mem_alloc���ڴ���ϻ�ȡ�̶���С���ڴ棬�ṩ��free����mem_free�ͷ��ڴ浽�ڴ���У�
 * 		ii���ڴ�س�ʼ��СΪĳ���̶���С��BUF_SIZE����n�������ڴ���е��ڴ治����ʱ���ڴ������һ����������ֱ����ϵͳ�ڴ档
 * Ҫʵ����Щ���ܣ�����Ӧ����һ�����ݽṹ��mem_node_t�����ڴ���еĸ���С�ڴ���������
 * Ȼ��Ϊ��ʹ�ڴ���ܹ���һ����������������Ҫ�ܷ���������ڴ�飨�����С�ڴ�أ���
 * Ϊ����˳���Ĺ����������ڴ�飬��Ҫһ�����ݽṹ��mem_block_t������¼��Щ��Ϣ��
 * ����ڴ�صĵ�ǰ״̬�������ɷ���Ŀ����������е�С�ڴ��ĸ����ȣ������Ǹ���Ȥ�Ķ��������������ݽṹ��mem_pool_t������¼��
*/
typedef union _mem_node
{
	union _mem_node *next;
	char buf[BUF_SIZE];
}mem_node_t, *pmem_node_t;

typedef struct _mem_block
{
	mem_node_t *node_head; 		/* ��һ��С�ڴ�� */
	mem_node_t *node_tail; 		/* ���һ��С�ڴ�� */
	int node_cnt; 				/* node count */
	struct _mem_block *next;
}mem_block_t, *pmem_block_t;


typedef struct _mem_pool
{
	mem_block_t *block_head; 	/* ��һ�����ڴ�� */
	mem_block_t *block_tail; 	/* ���һ�����ڴ�� */
	mem_node_t *free_head; 		/* ��ǰ���������ͷָ�� */
	int block_cnt; 				/* block count */
	int free_cnt; 				/* free node count; */
	int base; 					/* �ڴ�صĳ�ʼ��С */
	int step; 					/* �ڴ�ص��������� */
}mem_pool_t, *pmem_pool_t;


/*
 * Ȼ���ṩ��һЩ����������
 * 		mem_pool_init������ʼ���ڴ�أ�
 * 		mem_pool_destroy�����ͷ��ڴ�أ����ڴ����ռ�ռ�黹ϵͳ��
 * 		print_mem_pool_info������ӡ�ڴ�ص���Ϣ��
 * 		mem_alloc���������ڴ���Ϸ���С�ڴ�飻
 * 		mem_free����С�ڴ��黹���ڴ�ء�
 * mem_alloc��mem_free�����ľ����ڴ�صĿ�������ǰ�ߴӿ�������ȡһ����㣬���߽�һ���������������
 * �����������������mem_pool_init��ʼ���ģ����ҵ��ڴ������ʱ���������µĴ��ڴ��ʱ��
 * ���ǽ����ڴ���ϵ�С�ڴ��Ҳ�ҽӵ��������������������Ҫע�����С�ڴ������ݽṹ�������ϣ�
 * ������ΪС�ڴ��Ҫô�ǹҽ��ڿ��������ϣ�Ҫô�Ƿ�������û����ؾ���ֻ�ܾ�������״̬֮һ,������ݽṹ�ɸ��������ʵ��Ľ���
 * �������֮ǰ��Ҫ����˵�����ǣ������ڴ�ض��ṩ�˷��䲻ͬ��С���ڴ��Ĺ��ܣ��������ͬ��С�ı��ڴ����������Ҳ��ʵ����Щ���ܣ�
 * �Ķ��ǱȽ����׵�^_^
 * ��󣬱��ڴ����vc6����֤��Ƶ�������ͷ�100�ֽڴ�С���ڴ�ʱ�����ڴ��Ч��Լ��ֱ��malloc��free��10�����������С��Сʱ��
 * Ч�ʱ��������ͣ����������С����ʱ��Ч�ʱ��������ߣ�����1000�ֽڴ�С���ڴ�ʱ��Ч�ʱ�ԼΪ100��
*/
#endif


#include "stlib.h"

ST_BEGIN_DECLS;
#define MEM_POOL_DEBUG


#define BUF_SIZE 100				// һС���ڴ�Ĵ�С

#define BASE_COUNT 10000			// Ĭ���ڴ��Ĵ�С

#define STEP_COUNT 1000				// ��������

/* #pragma pack () */



/* */
/* С�ڴ��ڵ�ṹ */
typedef union _mem_node
{
    union _mem_node *next;
    char buf[BUF_SIZE];
}mem_node_t, *pmem_node_t;



/* used to store block information */

typedef struct _mem_block
{
    mem_node_t *node_head;					/* ��һ��С�ڴ�� */
    mem_node_t *node_tail;					/* ���һ��С�ڴ�� */
    int node_cnt; 							/* ��¼һ��block node count */
    struct _mem_block *next;
}mem_block_t, *pmem_block_t;



/* used to store the pool information */
typedef struct _mem_pool
{
    mem_block_t *block_head;			/* ��һ�����ڴ�� */
    mem_block_t *block_tail;			/* ���һ�����ڴ�� */
    mem_node_t *free_head;				/* ��ǰ���������ͷָ�� */
    int block_cnt; 						/* block count */
    int free_cnt; 						/* free node count; */
    int base;							/* �ڴ�صĳ�ʼ��С */
    int step;							/* �ڴ�ص��������� */
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
