/*
 * st_mempool.c
 *
 *  Created on: 2011-12-6
 *      Author: kine
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "st_mempool.h"




/*	局部函数声明	*/
/* add new memory block to our memory pool */
static int add_mem_block(int cnt);
/* init the new block */
static int mem_block_init(int cnt, mem_block_t *block);
/* init free_list of the new block */
static int free_list_init(const mem_block_t *block);

/*	全局变量声明	*/
static mem_pool_t mem_pool;


/*	接口函数定义	*/

/* mem_pool will have at least base blocks, and will increase steps a time if needed */
int mem_pool_init(int base, int step)
{
    if(base <= 0)
    {
        base = BASE_COUNT;
    }

    if(step <= 0)
    {
        step = STEP_COUNT;
    }

    /* initiate mem_pool */
    memset(&mem_pool, 0, sizeof(mem_pool));
    mem_pool.base = base;			// 内存池大小
    mem_pool.step = step;			// 内存池满时增长步长

    /* add the base block(node of base count) into the memory pool */
    if(!add_mem_block(base))
    {
        fprintf(stderr, "mem_pool_init::add_mem_block error\n");
        return 0;
    }

    return 1;
}

/* 销毁内存池 */
void mem_pool_destroy(void)
{
    mem_block_t *prev, *cur;

    prev = NULL;
    cur = mem_pool.block_head;

    while(prev != NULL)
    {
        prev = cur;
        cur = cur->next;
        free(cur->node_head);
        free(prev);
    }

    memset(&mem_pool, 0, sizeof(mem_pool_t));
}

void print_mem_pool_info(void)
{
    int i;
    mem_block_t *p;

    if(mem_pool.block_head == NULL)
    {
        fprintf(stderr, "memory pool has been created!\n");
        return;
    }

    printf("***************memory pool information start***********************\n");
    printf("block count: %4d\n", mem_pool.block_cnt);
    printf("current free node count: %4d\n", mem_pool.free_cnt);
    printf("base block size: %4d\n", mem_pool.base);
    printf("increasing block size: %4d\n", mem_pool.step);
    printf("the first block: %#x\n", mem_pool.block_head);
    printf("the last block: %#x\n", mem_pool.block_tail);
    printf("the first free node: %#x\n\n", mem_pool.free_head);

    for(p = mem_pool.block_head, i = 0; p != NULL; p = p->next, i++)
    {
        printf("-------------------block %4d--------------------------\n", i+1);
        printf("node count: %4d\n", p->node_cnt);
        printf("the first node: %#x\n", p->node_head);
        printf("the last node: %#x\n", p->node_tail);
        printf("------------------------------------------------------\n");
    }

    printf("************************memory pool information end**************************************\n");
}


/* since the block size is constant, this function need no input parameter */
void *mem_alloc(void)
{
    mem_node_t *p;

    /* no free node ready, attempt to allocate new free node */
    if(mem_pool.free_head == NULL)
    {
        if(!add_mem_block(mem_pool.step))
        {
            return NULL;
        }
    }

    /* get free node from free_list */
    p = mem_pool.free_head;
    mem_pool.free_head = p->next;

    /* decrease the free node count */
    mem_pool.free_cnt--;

    return p;
}

void mem_free(void *ptr)
{
    if(ptr == NULL)
    {
        return;
    }

    /* return the node to free_list */
    ((mem_node_t *)ptr)->next = mem_pool.free_head;
    mem_pool.free_head = ptr;

    /* increase the free node count */
    mem_pool.free_cnt++;
}





/*	局部函数定义	*/
/* add new memory block to our memory pool */
static int add_mem_block(int cnt)
{
    mem_block_t *block;

    if( (block = malloc(sizeof(mem_block_t))) == NULL)
    {
        fprintf(stderr, "add_mem_block::malloc error\n");
        return 0;
    }

    memset(block, 0, sizeof(mem_block_t));
    if(!mem_block_init(cnt, block))				// 初始化block的链表
    {
            fprintf(stderr, "mem_pool_init::mem_block_init error\n");
            return 0;
    }

    /* insert the new block in the head */
    block->next = mem_pool.block_head;
    mem_pool.block_head = block;
    if(mem_pool.block_tail == NULL)
    {
        mem_pool.block_tail = block;
    }


    /* insert the new block into the free list */
    block->node_tail->next = mem_pool.free_head;
    mem_pool.free_head = block->node_head;
    mem_pool.free_cnt += cnt;

    /* increase the block count */
    mem_pool.block_cnt++;

    return 1;
}

/* init the new block */
static int mem_block_init(int cnt, mem_block_t *block)
{
    int size;
    mem_node_t *p;

    if(block == NULL)
    {
        return 0;
    }

    size = cnt*sizeof(mem_node_t);				// 分配连续大小的内存（base个node）

    if( (p = malloc(size)) == NULL)
    {
        fprintf(stderr, "mem_pool_init::malloc error\n");
        return 0;
    }

    memset(p, 0, size);
    memset(block, 0, sizeof(mem_block_t));
    block->node_cnt = cnt;
    block->node_head = p;
    block->node_tail = p+cnt-1;			// 为什么-1
    free_list_init(block);				// 初始化小内存块空闲链表

    return 1;
}

/* init free_list of the new block */
static int free_list_init(const mem_block_t *block)
{
    mem_node_t *p, *end;

    if(block == NULL)
    {
        return 0;
    }

    /* start initiating free list */
    end = block->node_tail; /* block_cnt > 0 */
    /* 把空闲链表链起来 */
    for(p = block->node_head; p < end; p++)
    {
        p->next = (p+1);
    }
    p->next = NULL; /* end->next = NULL */

    return 1;
}







