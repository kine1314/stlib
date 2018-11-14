#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "st_gquene.h"


/**
 * st_queue_new:
 *
 * Creates a new #STQueue. 
 *
 * Returns: a new #STQueue.
 * 创建一个新的空队列
 **/
STQueue*	st_queue_new(void) 
{
	STQueue* queue = NULL ;

	queue = (STQueue *)malloc(sizeof(STQueue));
	if(NULL == queue)
	{
		__err("alloc mem for queue failed !\n");
		exit(1) ;
	}
	
	return queue ;
}



/**
 * st_queue_free:
 * @queue:	a STQueue whitch will be free ;
 * free a new #STQueue. 
 * 释放队列的所有元素
 **/
void		st_queue_free(STQueue	*queue) 
{
	if(NULL != queue)
	{
		st_dlist_free(queue->head) ;		/* delete all node of the queue */
		free(queue) ;
		queue = NULL ;
	}
}

/**
 * st_queue_init:
 * @queue: an uninitialized #STQueue
 */
void		st_queue_init(STQueue	*queue) 
{
	queue->head = queue->tail = NULL ;		/* 空队列，首尾都为空 */
	queue->length = 0 ;
}




/**
 * st_queue_clear:
 * @queue:	a STQueue whitch will be free ;
 * clear a new #STQueue. 
 * 清空队列
 **/
void     	st_queue_clear(STQueue	*queue)
{
	if(NULL != queue)
	{
		st_dlist_free(queue->head) ;		/* delete all node of the queue */
		st_queue_init(queue);				/* 重新初始化清空后的队列 */
	}
}


/**
 * st_queue_is_empty:
 * @queue:	a STQueue whitch will be free ;
 * check wether the queue is empty
 * return: if empty return TRUE, else return FALSE
 **/
stbool		st_queue_is_empty(STQueue	*queue) 
{
	if(NULL != queue)
	{
		return queue->head == NULL ;
	}
}


/**
 * st_queue_get_length:
 * @queue:	a STQueue
 * 
 * return: the length of queue ;
 **/
stuint    	st_queue_get_length(STQueue	*queue)
{
	if(NULL != queue)
	{
		return queue->length;
	}
}



/**
 * st_queue_reverse:
 * @queue:	a STQueue
 * 
 * reverse the queue ;
 **/
void     	st_queue_reverse(STQueue	*queue)
{
	if(NULL != queue)
	{
		queue->tail = queue->head ;							/* 交换尾节点 */
		queue->head = st_dlist_reverse(queue->head) ;		/* 交换首节点，别且逆转双向链表 */
	}
}
	

/**
 * st_queue_copy:
 * @queue:	a STQueue
 * 
 * 拷贝一份STQueue
 **/
STQueue*	st_queue_copy(STQueue	*queue)
{
	STQueue* result ;
	STDLIST* list ;

	result  = st_queue_new() ;
	for(list = queue->head ; list != NULL ; list = list->next)
	{
		st_queue_push_tail(result, list->data) ;
	}
	return result ;
}



/**
 * st_queue_foreach:
 * @queue:	a STQueue
 * 
 * 以某种功能关系去遍历队列，例如查找最小值，保存在userdata；
 **/
void     	st_queue_foreach(STQueue	*queue,
				 			 STFunc		func,
				 			 stpointer	user_data)
{
	if(NULL != queue && NULL != func)
	{
		STDLIST* list ;

		list = queue->head ;
		while(list)
		{
			STDLIST* next = list->next ;			/* 应该保存next指针，因为有可能在func里丢失 */
			func (list->data, user_data);
			list = next ;
		}
	}
}


/**
 * st_queue_find:
 * @queue:	a STQueue
 * 
 * 查找队列中第一个包含data的节点
 **/
STDLIST*	st_queue_find(STQueue	*queue, 
 						  stconstpointer	data)
{
	if(NULL != queue)
	{	
		return st_dlist_find(queue->head, data);
	}
}


/**
 * g_queue_find_custom:
 * @queue:	a STQueue
 * 
 * 查找队列中第一个符合STCompareFunc的节点
 **/
STDLIST*	g_queue_find_custom(STQueue	*queue,
				 				stconstpointer	data,
				 				STCompareFunc	func)
{
	if(NULL != queue && NULL != func)
	{
		return st_dlist_find_custom(queue->head, data, func) ;
	}
}

/**
 * g_queue_sort:
 * @queue:	a STQueue
 * 
 * 队列进行排序，升降可由compare_func控制
 **/
void		g_queue_sort(STQueue	*queue,
				 		 STCompareDataFunc	compare_func,
				 		 stpointer	user_data)
{
	if(NULL != queue && NULL != compare_func)
	{
		queue->head = st_dlist_sort_with_data (queue->head, compare_func, user_data);		/* 可以控制排序的升降 */
	  	queue->tail = st_dlist_last (queue->head);
	}
}


/**
 * g_queue_push_head:
 * @queue:	a STQueue
 * 
 * 添加一个节点到队列头
 **/
void     st_queue_push_head(STQueue	*queue,
				 		stpointer	data)
{
	if(NULL != queue)
	{
		queue->head = st_dlist_prepend(queue->head, data);			/* 插入到对头 */
		if(NULL == queue->tail)
			queue->tail = queue->head ;								/* 前插，队尾是不变的 */
		queue->length++;
	}

}


void     st_queue_push_tail(STQueue	*queue,
				 		   stpointer	data)
{
	if(NULL != queue)
	{
		queue->tail = st_dlist_append (queue->tail, data);			/* 往队列的尾节点追加一个节点，返回原头指针 */
		if (queue->tail->next)										/* 如果队列尾的下一个非空，即原队列非空，则重置队列的尾 */
			queue->tail = queue->tail->next;
		else
			queue->head = queue->tail;								/* 如果是第一个节点，则头尾都是他 */
		queue->length++;
	}
}


/**
 * st_queue_push_nth:
 * @queue:	a STQueue
 * 
 * 将data插到指定位置
 **/
void     st_queue_push_nth(STQueue	*queue,
				 		  stpointer          data,
				 		  stint              n)
{
	if(NULL != queue)
	{
		if(n < 0 && n > queue->length)
		{
			st_queue_push_tail(queue, data);								/* 从尾部入队 */
			return ;  
		}
		st_queue_insert_before(queue, st_queue_peek_nth(queue, n), data);	/* 插入到n位置 */
	}
}

/**
 * st_queue_pop_head:
 * @queue: a #GQueue.
 *
 * Removes the first element of the queue.
 *
 * Returns: the data of the first element in the queue, or %NULL if the queue
 *   is empty.
 **/
stpointer	st_queue_pop_head(STQueue	*queue)
{
	if(NULL == queue)
		return NULL ;

	if(NULL != queue->head)
	{
		stpointer data ;
		STDLIST* node ;

		node = queue->head ;					/* 临时的node暂存 */
		data = node->data ;
		queue->head = node->next ;
		if(NULL != queue->head)
			queue->head->prev = NULL;			/* 如果pop后，队列非空 */
		else
			queue->tail = NULL ;				/* 如果为空，prev和next全置空 */
		st_dlist_free1(node);
		queue->length-- ;

		return data ;
	}
	
}



/**
 * st_queue_pop_tail:
 * @queue: a #GQueue.
 *
 * Removes the last element of the queue.
 *
 * Returns: the data of the last element in the queue, or %NULL if the queue
 *   is empty.
 **/
stpointer	st_queue_pop_tail(STQueue	*queue)
{
	if(NULL == queue)
		return NULL ;

	if(NULL != queue->tail)
	{
		stpointer data ;
		STDLIST* node ;

		node = queue->tail ;
		data = node->data ;
		queue->tail = node->prev ;
		if(NULL != queue->tail)						/* 如果pop后，队列非空 */
			queue->tail->next = NULL ;
		else										/* 如果为空，prev和next全置空 */
			queue->head = NULL ;

		st_dlist_free1(node);
		queue->length-- ;
		return data ;
	}
}


/**
 * st_queue_pop_nth:
 * @queue: a #GQueue
 * @n: the position of the element.
 * 
 * Removes the @n'th element of @queue.
 * 
 * Return value: the element's data, or %NULL if @n is off the end of @queue.
 * 
 **/
stpointer 	st_queue_pop_nth(STQueue	*queue,
				 		    stuint	n)
{
	STDLIST *nth_link;
  	stpointer result;
  
	if(NULL == queue)
		return NULL ;

	if(n < 0 && n >= queue->length)
		return NULL ;

	nth_link = st_queue_peek_nth(queue, n) ;			/* 获取队列中node */
	result = nth_link->data ;
	st_queue_delete_link(queue, nth_link);				/* 删除队列中得node */

	return result ;
}


/**
 * st_queue_peek_head:
 * @queue: a #GQueue.
 *
 * Returns the first element of the queue.
 *
 * Returns: the data of the first element in the queue, or %NULL if the queue
 *   is empty.
 **/
stpointer 	st_queue_peek_head(STQueue	*queue)
{
	if(NULL == queue)	
		return NULL ;

	return queue->head ? queue->head->data : NULL ;
}



stpointer 	g_queue_peek_tail(STQueue	*queue)
{
	if(NULL == queue)	
		return NULL ;

	return queue->tail ? queue->tail->data : NULL ;
}



stpointer 	st_queue_peek_nth(STQueue	*queue,
				 			 stuint	n)
{
  	STDLIST *link;
  	stint i;
  
  	if(NULL == queue)
  		return NULL ;

  	if (n >= queue->length)				/* 如果n超出length，return */
   		return NULL;
  
  	if (n > queue->length / 2)			/* 如果在下半部，从尾部开始遍历 */
    {
      	n = queue->length - n - 1;

      	link = queue->tail;
      	for (i = 0; i < n; ++i)
			link = link->prev;
    }
  	else								/* 如果是上半部，从头开始遍历 */
    {
      	link = queue->head;
      	for (i = 0; i < n; ++i)
			link = link->next;
    }

  	return link;	
}


/**
 * st_queue_index:
 * @queue: a #GQueue
 * @data: the data to find.
 * 
 * Returns the position of the first element in @queue which contains @data.
 * 
 * Return value: The position of the first element in @queue which contains @data, or -1 if no element in @queue contains @data.
 * 
 **/
stint     	st_queue_index(STQueue	*queue,
				 		  stconstpointer	data)
{
	if(NULL == queue)
  		return NULL ;

	return st_dlist_index(queue->head, data) ;
}



/**
 * st_queue_remove:
 * @queue: a #GQueue
 * @data: data to remove
 * 
 * Removes the first element in @queue that contains @data. 
 * 
 **/
void		st_queue_remove(STQueue	*queue,
				 		  stconstpointer	data)
{
	STDLIST* link ;
	if(NULL != queue)
	{
		link = st_dlist_find (queue->head, data);
		if(NULL != link)
			st_queue_delete_link(queue, link);
	}
}


/**
 * st_queue_remove_all:
 * @queue: a #GQueue
 * @data: data to remove
 * 
 * Remove all elemeents in @queue which contains @data.
 * 
 **/
void     	st_queue_remove_all(STQueue	*queue,
				 		  stconstpointer	data)
{
	STDLIST* link ;

	if(NULL != queue)
	{
		link = queue->head;
		while(link)	
		{
			STDLIST* next = link->next ;
			if(link->data == data)
				st_queue_delete_link(queue, link);

			link = next ;
		}
	}
}


/**
 * st_queue_insert_before:
 * @queue:	a STQueue
 * 
 * 将data插到sibling节点之前
 **/
void     	st_queue_insert_before(STQueue	*queue,
								  STDLIST	*sibling,
								  stpointer	data)
{
	if(NULL != queue && NULL != sibling)
	{
		queue->head = st_dlist_insert_before (queue->head, sibling, data);
	  	queue->length++;
	}
}


/**
 * st_queue_insert_after:
 * @queue: a #GQueue
 * @sibling: a #GList link that <emphasis>must</emphasis> be part of @queue
 * @data: the data to insert
 *
 * Inserts @data into @queue after @sibling
 *
 * @sibling must be part of @queue
 * 
 **/
void     	st_queue_insert_after(STQueue	*queue,
								 STDLIST	*sibling,
								 stpointer	data)
{
	if(NULL != queue && NULL != sibling)
	{
		if (sibling == queue->tail)
    		st_queue_push_tail (queue, data);
  		else
   	 		st_queue_insert_before (queue, sibling->next, data);
	}
}


/**
 * st_queue_insert_sorted:
 * @queue: a #GQueue
 * @data: the data to insert
 * @func: the #GCompareDataFunc used to compare elements in the queue. It is
 *     called with two elements of the @queue and @user_data. It should
 *     return 0 if the elements are equal, a negative value if the first
 *     element comes before the second, and a positive value if the second
 *     element comes before the first.
 * @user_data: user data passed to @func.
 * 
 * Inserts @data into @queue using @func to determine the new position.
 * 
 **/
void     	st_queue_insert_sorted(STQueue	*queue,
								  stpointer	data,
								  STCompareDataFunc	func,
								  stpointer	user_data)
{
	STDLIST* list ;

	if(NULL != queue)
	{
		list = queue->head;
  		while (list && func (list->data, data, user_data) < 0)
    		list = list->next;

  		if (list)
    		st_queue_insert_before (queue, list, data);
  		else
    		st_queue_push_tail (queue, data);
	}
}


/**
 * st_queue_push_head_link:
 * @queue: a #GQueue.
 * @link_: a single #GList element, <emphasis>not</emphasis> a list with
 *     more than one element.
 *
 * Adds a new element at the head of the queue.
 **/
void     	st_queue_push_head_link(STQueue	*queue,
				 				   STDLIST	*link_)
{
  	if(NULL != queue && NULL != link_ && 
		NULL == link_->prev && NULL == link_->next)			/* 保证link_是一个节点 */
	{
		link_->next = queue->head ;
		if(NULL != queue->head)
		{
			queue->head->prev = link_ ;						/* 如果queue非空，重置queue->head->prev */
		}
		else
		{
			queue->tail = link_ ;							/* NULL,  */
		}
		queue->head = link_ ;
		queue->length++ ;
	}
}



/**
 * st_queue_push_tail_link:
 * @queue: a #GQueue.
 * @link_: a single #GList element, <emphasis>not</emphasis> a list with
 *   more than one element.
 *
 * Adds a new element at the tail of the queue.
 **/
void     	st_queue_push_tail_link(STQueue	*queue,
				 				   STDLIST	*link_)
{
	if(NULL != queue && NULL != link_ && 
		NULL == link_->prev && NULL == link_->next)			/* 保证link_是一个节点 */
	{
		link_->prev = queue->tail ;
		if(NULL != queue->tail)
		{
			queue->tail->next = link_ ;
		}
		else
		{
			queue->head = link_ ;
		}
		queue->tail = link_ ;
		queue->length++ ;
	}
}



/**
 * st_queue_push_nth_link:
 * @queue: a #GQueue
 * @n: the position to insert the link. If this is negative or larger than
 *     the number of elements in @queue, the link is added to the end of
 *     @queue.
 * @link_: the link to add to @queue
 * 
 * Inserts @link into @queue at the given position.
 * 
 **/
void     	st_queue_push_nth_link(STQueue	*queue,
				 				  stint		n,
				 				  STDLIST	*link_)
{
	STDLIST* next ;
	STDLIST* prev ;
	
	if(NULL != queue && NULL != link_)
	{
		if(n < 0 || n >= queue->length)
		{
			st_queue_push_tail_link(queue, link_);
			return ;
		}
		next = st_queue_peek_nth_link(queue, n);
		prev = next->prev;
		if (prev)
    		prev->next = link_;
  		next->prev = link_;

  		link_->next = next;
  		link_->prev = prev;

  		if (queue->head->prev)
    		queue->head = queue->head->prev;

  		if (queue->tail->next)
    		queue->tail = queue->tail->next;
  
  		queue->length++;
	}
}


/**
 * st_queue_pop_head_link:
 * @queue: a #GQueue.
 *
 * Removes the first element of the queue.
 *
 * Returns: the #GList element at the head of the queue, or %NULL if the queue
 *   is empty.
 **/
STDLIST*   	st_queue_pop_head_link(STQueue	*queue)
{
	if(NULL == queue)
		return NULL ;

	if(NULL != queue->head)
	{
		STDLIST* node = queue->head ;
		queue->head = node->next ;				// TODO: 更新对头
		if(NULL != queue->head)					// TODO: 如果非空
		{
			queue->head->prev = NULL ;
			node->next = NULL ;
		}
		else									// TODO: 如果为空
		{
			queue->tail = NULL ;
		}
		queue->length-- ;
		return node ;
	}

	return NULL ;
}


/**
 * st_queue_pop_tail_link:
 * @queue: a #GQueue.
 *
 * Removes the last element of the queue.
 *
 * Returns: the #GList element at the tail of the queue, or %NULL if the queue
 *   is empty.
 **/
STDLIST*   	st_queue_pop_tail_link(STQueue	*queue)
{
	if(NULL == queue)
		return NULL ;

	if(NULL != queue->tail)
	{
		STDLIST* node ;

		node = queue->tail ;
		queue->tail = node->prev ;						// TODO: 更新对尾
		if(NULL != queue->tail)							// TODO: 如果非空
		{
			queue->tail->next = NULL ;
			node->prev = NULL ;
		}
		else											// TODO: 如果为空
		{
			queue->head = NULL ;
		}
		queue->length-- ;
		return node ;
	}

	return NULL ;
}


/**
 * st_queue_pop_nth_link:
 * @queue:	a STQueue
 * 
 * pop连接，不是放节点
 **/
STDLIST*   	st_queue_pop_nth_link(STQueue	*queue,
				 				 stuint		n)
{
	STDLIST* link ;
	
	if(NULL == queue)
		return NULL ;

	if(n < 0 && n >= queue->length)
		return NULL ;

	link = st_queue_peek_nth_link(queue, n);
	st_queue_unlink(queue, link);

	return link ;
}


/**
 * st_queue_peek_head_link:
 * @queue: a #GQueue
 * 
 * Returns the first link in @queue
 * 
 * Return value: the first link in @queue, or %NULL if @queue is empty
 * 
 **/
STDLIST*   	st_queue_peek_head_link(STQueue	*queue)
{
	if(NULL == queue)
		return NULL ;

	return queue->head ;
}


/**
 * st_queue_peek_tail_link:
 * @queue: a #GQueue
 * 
 * Returns the last link @queue.
 * 
 * Return value: the last link in @queue, or %NULL if @queue is empty
 * 
 * Since: 2.4
 **/
STDLIST*   	st_queue_peek_tail_link(STQueue	*queue)
{
	if(NULL == queue)
		return NULL ;

	return queue->tail ;
}



/**
 * st_queue_peek_nth_link:
 * @queue: a #GQueue
 * @n: the link's position
 * 
 * Removes and returns the link at the given position.
 * 
 * Return value: The @n'th link, or %NULL if @n is off the end of @queue.
 * 
 **/
STDLIST*   	st_queue_peek_nth_link(STQueue	*queue,
				 				  stuint	n)
{
	STDLIST* link ;
	stint i ;

	if(NULL == queue)
		return NULL ;

	if(n >= queue->length)
		return NULL ;

	if(n > queue->length/2)					// TODO: 如果在队列的下半部
	{
		n = queue->length - n - 1 ;
		link = queue->tail ;
		for(i = 0 ; i < n ; i++)
			link = link->prev ;
	}
	else									// TODO: 如果在队列的上半部
	{
		link = queue->head ;
		for(i = 0 ; i < n ; i++)
			link = link->next ;
	}

	return link ;
}




/**
 * st_queue_link_index:
 * @queue: a #Gqueue
 * @link_: A #GList link
 * 
 * Returns the position of @link_ in @queue.
 * 
 * Return value: The position of @link_, or -1 if the link is
 * not part of @queue
 * 
 * Since: 2.4
 **/
stint     	st_queue_link_index(STQueue		*queue,
				 			   STDLIST		*link_)
{
	if(NULL != queue)
	{
		return st_dlist_position(queue->head, link_) ;
	}

	return -1 ;
}



/**
 * st_queue_unlink
 * @queue: a #GQueue
 * @link_: a #GList link that <emphasis>must</emphasis> be part of @queue
 *
 * Unlinks @link_ so that it will no longer be part of @queue. The link is
 * not freed.
 *
 * @link_ must be part of @queue,
 * 
 **/				 			   
void     	st_queue_unlink(STQueue			*queue,
				 		   STDLIST			*link_)
{
	if(NULL != queue && NULL != link_)
	{
		if (link_ == queue->tail)					/* 如果link是最后一个，直接断开 */
			queue->tail = queue->tail->prev;

		queue->head = st_dlist_remove_link (queue->head, link_);
		queue->length--;
	}
}



/**
 * st_queue_delete_link:
 * @queue: a #GQueue
 * @link_: a #GList link that <emphasis>must</emphasis> be part of @queue
 *
 * Removes @link_ from @queue and frees it.
 *
 * @link_ must be part of @queue.

 **/
void     	st_queue_delete_link(STQueue		*queue,
				 			    STDLIST		*link_)
{
	if(NULL != queue && NULL != link_)
	{
		st_queue_unlink (queue, link_);
  		st_dlist_free1 (link_);
	}
}



///////////////////////////////////////////////////////
//                	顺序表实现队列	                 //
///////////////////////////////////////////////////////
/**
 * 顺序表实现的循环队列，当front和rear是-1时为空，当rear+1 == front时为满；
 * array[front]是头元素，array[rear]是尾元素
 **/
STQueueA* st_array_queue_new(void)
{
	STQueueA* queue = NULL ;

	queue = (STQueueA *)malloc(sizeof(STQueueA));
	if(NULL == queue)
	{
		__err("alloc mem for queue failed !\n");
		exit(1) ;
	}

	return queue ;
}

void st_array_queue_free(STQueueA* queue)
{
	if(NULL != queue)
	{
		free(queue) ;
		queue = NULL ;
	}
}
#if	isDynamic
void st_array_queue_dynamic_init(STQueueA* queue, stint maxSize)
{
	if(NULL == queue)
	{
		__err("queue is NULL !\n");
		return ;
	}

	if(maxSize <= 0)
	{
		__err("the value of maxSize is illegal !\n");
		exit(1) ;
	}

	queue->maxSize = maxSize ;
	queue->length = 0 ;
	queue->pData = (stint *)malloc(sizeof(stint)*maxSize) ;
	queue->front = queue->rear = -1 ;

}

void st_array_queue_dynamic_delete(STQueueA* queue)
{
	if(NULL != queue)
	{
		if(NULL != queue->pData)
		{
			free(queue->pData) ;
			queue->pData = NULL ;
			queue->front = queue->rear = -1 ;
			queue->length = 0 ;
		}
	}
	st_array_queue_free(queue);
}

#else
void st_array_queue_init(STQueueA* queue) 
{
	if(NULL == queue)
	{
		__err("queue is NULL !\n");
		return ;
	}

	if(MAXSIZE < 0)
	{
		__err("the value of maxSize is illegal !\n");
		exit(1) ;
	}

	queue->maxSize = MAXSIZE ;
	queue->length = 0 ;

	queue->front = queue->rear = -1 ;

	return  ;
}

void st_array_queue_delete(STQueueA* queue)
{
	if(NULL != queue)
	{
		if(NULL != queue->pData)
		{
			memset(queue->pData, 0, sizeof(queue->pData));
			queue->front = queue->rear = -1 ;
			queue->length = 0 ;
		}
	}
	st_array_queue_free(queue);
}

#endif

void st_array_queue_clear(STQueueA* queue)
{
	if(NULL != queue)
	{
		if(NULL != queue->pData)
		{
			memset(queue->pData, 0, sizeof(queue->pData));
			queue->front = queue->rear = -1 ;
			queue->length = 0 ;
		}
	}
}

stint st_array_queue_empty(STQueueA* queue)
{
	if(NULL != queue)
		return queue->rear == -1 ;
}

stint st_array_queue_full(STQueueA* queue)
{
	if(NULL != queue)
		return ((queue->rear+1)%queue->maxSize) == queue->front ;
}





stint st_array_queue_peek(STQueueA* queue)
{
	if(NULL != queue)
		return queue->pData[queue->front] ;
}


/**
 * st_array_queue_push
 * if fail return -1, else return the length ;
 * 从尾入队 
 **/
stint st_array_queue_push(STQueueA* queue, stint data) 
{
	/* 判断是否满队 */
	if((queue->front) == (queue->rear+1)%queue->maxSize)
		return -1 ;
	else
	{
		if(queue->rear == -1)								/* 如果队列是空，则入队后头尾都是0 */
			queue->rear = queue->front = 0 ;
		else
			queue->rear = (queue->rear+1)%queue->maxSize;
		queue->pData[queue->rear] = data ;
		queue->length++ ;
		return queue->length ;
	}
}


/**
 * st_array_queue_pop
 * if fail return NULL , else return  data ;
 * 从头出列
 **/
stint st_array_queue_pop(STQueueA* queue)
{
	stint front ;
	
	/* 判断队列是否是空 */
	if(-1 == queue->rear)
	{
		return -1 ;
	}
	else
	{
		front = queue->front ;
		if(queue->rear == queue->front) 						/* 如果是队列的最后一个元素 */
		{
			queue->rear = queue->front = -1 ;
		}
		else
		{
			queue->front = (queue->front+1)%queue->maxSize ;	/* 对头循环向前移动 */
		}
		queue->length-- ;
		return front;
	}
}


void st_array_queue_dump(STQueueA* queue)
{
	stint i ;

	if(NULL == queue)
	{
		goto FAIL ;
	}
	if(queue->rear == -1)
	{
		goto FAIL ;
	}

	if((queue->front == queue->rear) && queue->front != -1)
	{
		__msg("%d\n", queue->pData[queue->front]);
	}
	else
	{
		//__msg("[%d], [%d]\n", queue->front, queue->rear);
		for(i = queue->front ; i != (queue->rear+1)%queue->maxSize ; )
		{
			printf("%d ", queue->pData[i]) ;
			(i++)%MAXSIZE;
		}
		printf("\n");
	}
	return ;

FAIL:
	__err("the queue is NULL !\n");
	return ;
}



