#ifndef	__ST_GQUEUE_H__
#define	__ST_GQUEUE_H__

ST_BEGIN_DECLS;	/* __cplusplus */

#include "stlib.h"
#include "st_dlist.h"
#include "st_log.h"



typedef struct _STQueue
{
  STDLIST *head;
  STDLIST *tail;
  stuint  length;
}STQueue;


#define ST_QUEUE_INIT { NULL, NULL, 0 }

/**
 * STQueue (double link queue)
 */

STQueue*	st_queue_new(void) ;
void		st_queue_free(STQueue	*queue) ;
void		st_queue_init(STQueue	*queue) ;
void     	st_queue_clear(STQueue	*queue);
stbool		st_queue_is_empty(STQueue	*queue) ;
stuint    	st_queue_get_length(STQueue	*queue);
void     	st_queue_reverse(STQueue	*queue);
STQueue*	st_queue_copy(STQueue	*queue);
void     	st_queue_foreach(STQueue	*queue,
				 			 STFunc		func,
				 			 stpointer	user_data);
STDLIST*	st_queue_find(STQueue	*queue, 
 						  stconstpointer	data);
STDLIST*	st_queue_find_custom(STQueue	*queue,
				 				stconstpointer	data,
				 				STCompareFunc	func);
void		st_queue_sort(STQueue	*queue,
				 		 STCompareDataFunc	compare_func,
				 		 stpointer	user_data);

void     	st_queue_push_head(STQueue	*queue,
				 		stpointer	data);
void     	st_queue_push_tail(STQueue	*queue,
				 		   stpointer	data);
void     	st_queue_push_nth(STQueue	*queue,
				 		  stpointer          data,
				 		  stint              n);
stpointer	st_queue_pop_head(STQueue	*queue);
stpointer	st_queue_pop_tail(STQueue	*queue);
stpointer 	st_queue_pop_nth(STQueue	*queue,
				 		    stuint	n);
stpointer 	st_queue_peek_head(STQueue	*queue);
stpointer 	st_queue_peek_tail(STQueue	*queue);
stpointer 	st_queue_peek_nth(STQueue	*queue,
				 			 stuint	n);
stint     	st_queue_index(STQueue	*queue,
				 		  stconstpointer	data);
void		st_queue_remove(STQueue	*queue,
				 		  stconstpointer	data);
void     	st_queue_remove_all(STQueue	*queue,
				 		  stconstpointer	data);
void     	st_queue_insert_before(STQueue	*queue,
								  STDLIST	*sibling,
								  stpointer	data);
void     	st_queue_insert_after(STQueue	*queue,
								 STDLIST	*sibling,
								 stpointer	data);
void     	st_queue_insert_sorted(STQueue	*queue,
								  stpointer	data,
								  STCompareDataFunc	func,
								  stpointer	user_data);

void     	st_queue_push_head_link(STQueue	*queue,
				 				   STDLIST	*link_);
void     	st_queue_push_tail_link(STQueue	*queue,
				 				   STDLIST	*link_);
void     	st_queue_push_nth_link(STQueue	*queue,
				 				  stint		n,
				 				  STDLIST	*link_);
STDLIST*   	st_queue_pop_head_link(STQueue	*queue);
STDLIST*   	st_queue_pop_tail_link(STQueue	*queue);
STDLIST*   	st_queue_pop_nth_link(STQueue	*queue,
				 				 stuint		n);
STDLIST*   	st_queue_peek_head_link(STQueue	*queue);
STDLIST*   	st_queue_peek_tail_link(STQueue	*queue);
STDLIST*   	st_queue_peek_nth_link(STQueue	*queue,
				 				  stuint	n);
stint     	st_queue_link_index(STQueue		*queue,
				 			   STDLIST		*link_);
void     	st_queue_unlink(STQueue			*queue,
				 		   STDLIST			*link_);
void     	st_queue_delete_link(STQueue		*queue,
				 			    STDLIST		*link_);


///////////////////////////////////////////////////////
//                	顺序表实现队列	                 //
///////////////////////////////////////////////////////
#define	isDynamic		1

#define	MAXSIZE		10

typedef struct _STQueueA
{
#if	isDynamic		
	stint* pData ;						/* 指向队列的动态数组存储空间 */ 
#else
	stint pData[MAXSIZE];				/* 指向队列的数组存储空间 */ 
#endif
	stint front, rear, length ;		/* 对头，队尾的下标，以及队列长度 */
	stint maxSize ;					/* 队列的最大值，最多maxSize-1 个元素 */
}STQueueA ;

STQueueA* st_array_queue_new(void);
void st_array_queue_free(STQueueA* queue);
#if	isDynamic
void st_array_queue_dynamic_init(STQueueA* queue, stint maxSize);
void st_array_queue_dynamic_delete(STQueueA* queue);
#else
void st_array_queue_init(STQueueA* queue) ;
void st_array_queue_delete(STQueueA* queue);
#endif
void st_array_queue_clear(STQueueA* queue);
stint st_array_queue_empty(STQueueA* queue);
stint st_array_queue_peek(STQueueA* queue);

stint st_array_queue_push(STQueueA* queue, stint data) ;
stint st_array_queue_pop(STQueueA* queue);
void st_array_queue_dump(STQueueA* queue);






ST_END_DECLS;	/* __cplusplus */
#endif	/*__ST_GQUEUE_H__*/

