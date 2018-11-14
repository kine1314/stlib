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
 * ����һ���µĿն���
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
 * �ͷŶ��е�����Ԫ��
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
	queue->head = queue->tail = NULL ;		/* �ն��У���β��Ϊ�� */
	queue->length = 0 ;
}




/**
 * st_queue_clear:
 * @queue:	a STQueue whitch will be free ;
 * clear a new #STQueue. 
 * ��ն���
 **/
void     	st_queue_clear(STQueue	*queue)
{
	if(NULL != queue)
	{
		st_dlist_free(queue->head) ;		/* delete all node of the queue */
		st_queue_init(queue);				/* ���³�ʼ����պ�Ķ��� */
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
		queue->tail = queue->head ;							/* ����β�ڵ� */
		queue->head = st_dlist_reverse(queue->head) ;		/* �����׽ڵ㣬������ת˫������ */
	}
}
	

/**
 * st_queue_copy:
 * @queue:	a STQueue
 * 
 * ����һ��STQueue
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
 * ��ĳ�ֹ��ܹ�ϵȥ�������У����������Сֵ��������userdata��
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
			STDLIST* next = list->next ;			/* Ӧ�ñ���nextָ�룬��Ϊ�п�����func�ﶪʧ */
			func (list->data, user_data);
			list = next ;
		}
	}
}


/**
 * st_queue_find:
 * @queue:	a STQueue
 * 
 * ���Ҷ����е�һ������data�Ľڵ�
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
 * ���Ҷ����е�һ������STCompareFunc�Ľڵ�
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
 * ���н���������������compare_func����
 **/
void		g_queue_sort(STQueue	*queue,
				 		 STCompareDataFunc	compare_func,
				 		 stpointer	user_data)
{
	if(NULL != queue && NULL != compare_func)
	{
		queue->head = st_dlist_sort_with_data (queue->head, compare_func, user_data);		/* ���Կ������������ */
	  	queue->tail = st_dlist_last (queue->head);
	}
}


/**
 * g_queue_push_head:
 * @queue:	a STQueue
 * 
 * ���һ���ڵ㵽����ͷ
 **/
void     st_queue_push_head(STQueue	*queue,
				 		stpointer	data)
{
	if(NULL != queue)
	{
		queue->head = st_dlist_prepend(queue->head, data);			/* ���뵽��ͷ */
		if(NULL == queue->tail)
			queue->tail = queue->head ;								/* ǰ�壬��β�ǲ���� */
		queue->length++;
	}

}


void     st_queue_push_tail(STQueue	*queue,
				 		   stpointer	data)
{
	if(NULL != queue)
	{
		queue->tail = st_dlist_append (queue->tail, data);			/* �����е�β�ڵ�׷��һ���ڵ㣬����ԭͷָ�� */
		if (queue->tail->next)										/* �������β����һ���ǿգ���ԭ���зǿգ������ö��е�β */
			queue->tail = queue->tail->next;
		else
			queue->head = queue->tail;								/* ����ǵ�һ���ڵ㣬��ͷβ������ */
		queue->length++;
	}
}


/**
 * st_queue_push_nth:
 * @queue:	a STQueue
 * 
 * ��data�嵽ָ��λ��
 **/
void     st_queue_push_nth(STQueue	*queue,
				 		  stpointer          data,
				 		  stint              n)
{
	if(NULL != queue)
	{
		if(n < 0 && n > queue->length)
		{
			st_queue_push_tail(queue, data);								/* ��β����� */
			return ;  
		}
		st_queue_insert_before(queue, st_queue_peek_nth(queue, n), data);	/* ���뵽nλ�� */
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

		node = queue->head ;					/* ��ʱ��node�ݴ� */
		data = node->data ;
		queue->head = node->next ;
		if(NULL != queue->head)
			queue->head->prev = NULL;			/* ���pop�󣬶��зǿ� */
		else
			queue->tail = NULL ;				/* ���Ϊ�գ�prev��nextȫ�ÿ� */
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
		if(NULL != queue->tail)						/* ���pop�󣬶��зǿ� */
			queue->tail->next = NULL ;
		else										/* ���Ϊ�գ�prev��nextȫ�ÿ� */
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

	nth_link = st_queue_peek_nth(queue, n) ;			/* ��ȡ������node */
	result = nth_link->data ;
	st_queue_delete_link(queue, nth_link);				/* ɾ�������е�node */

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

  	if (n >= queue->length)				/* ���n����length��return */
   		return NULL;
  
  	if (n > queue->length / 2)			/* ������°벿����β����ʼ���� */
    {
      	n = queue->length - n - 1;

      	link = queue->tail;
      	for (i = 0; i < n; ++i)
			link = link->prev;
    }
  	else								/* ������ϰ벿����ͷ��ʼ���� */
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
 * ��data�嵽sibling�ڵ�֮ǰ
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
		NULL == link_->prev && NULL == link_->next)			/* ��֤link_��һ���ڵ� */
	{
		link_->next = queue->head ;
		if(NULL != queue->head)
		{
			queue->head->prev = link_ ;						/* ���queue�ǿգ�����queue->head->prev */
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
		NULL == link_->prev && NULL == link_->next)			/* ��֤link_��һ���ڵ� */
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
		queue->head = node->next ;				// TODO: ���¶�ͷ
		if(NULL != queue->head)					// TODO: ����ǿ�
		{
			queue->head->prev = NULL ;
			node->next = NULL ;
		}
		else									// TODO: ���Ϊ��
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
		queue->tail = node->prev ;						// TODO: ���¶�β
		if(NULL != queue->tail)							// TODO: ����ǿ�
		{
			queue->tail->next = NULL ;
			node->prev = NULL ;
		}
		else											// TODO: ���Ϊ��
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
 * pop���ӣ����ǷŽڵ�
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

	if(n > queue->length/2)					// TODO: ����ڶ��е��°벿
	{
		n = queue->length - n - 1 ;
		link = queue->tail ;
		for(i = 0 ; i < n ; i++)
			link = link->prev ;
	}
	else									// TODO: ����ڶ��е��ϰ벿
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
		if (link_ == queue->tail)					/* ���link�����һ����ֱ�ӶϿ� */
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
//                	˳���ʵ�ֶ���	                 //
///////////////////////////////////////////////////////
/**
 * ˳���ʵ�ֵ�ѭ�����У���front��rear��-1ʱΪ�գ���rear+1 == frontʱΪ����
 * array[front]��ͷԪ�أ�array[rear]��βԪ��
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
 * ��β��� 
 **/
stint st_array_queue_push(STQueueA* queue, stint data) 
{
	/* �ж��Ƿ����� */
	if((queue->front) == (queue->rear+1)%queue->maxSize)
		return -1 ;
	else
	{
		if(queue->rear == -1)								/* ��������ǿգ�����Ӻ�ͷβ����0 */
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
 * ��ͷ����
 **/
stint st_array_queue_pop(STQueueA* queue)
{
	stint front ;
	
	/* �ж϶����Ƿ��ǿ� */
	if(-1 == queue->rear)
	{
		return -1 ;
	}
	else
	{
		front = queue->front ;
		if(queue->rear == queue->front) 						/* ����Ƕ��е����һ��Ԫ�� */
		{
			queue->rear = queue->front = -1 ;
		}
		else
		{
			queue->front = (queue->front+1)%queue->maxSize ;	/* ��ͷѭ����ǰ�ƶ� */
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



