#include <stdio.h>
#include <stdlib.h>
#include "st_dlist.h"
#include "st_log.h"


/* 获取链表的最后一个节点 */
STDLIST*	st_dlist_last(STDLIST* list)
{
	if(NULL != list)
	{
		while(NULL != list->next)
		{
			list = list->next ;
		}
	}

	return list ;
}


/* 获取链表的第一个节点 */
STDLIST*  	st_dlist_first(STDLIST		*list)
{
	if(NULL != list)
	{
		while(NULL != list->prev)
		{
			list = list->prev ;
		}
	}

	return list ;
}


/* 查找第n个节点 */
STDLIST*  	st_dlist_nth(STDLIST 		*list, stuint n)
{
	while((n-- > 0 ) && (NULL != list))
		list = list->next ;

	return list ;
}

STDLIST*	st_dlist_alloc(void) 
{
	STDLIST *temp = NULL ;

	temp = (STDLIST *)malloc(sizeof(STDLIST));
	temp->next = NULL ;
	temp->prev = NULL ;

	if(NULL == temp)
	{
		__err("malloc men fail \n");
		exit(1);
	}
}

void		st_dlist_free1(STDLIST	*list)
{
	if(NULL != list)
	{
		free(list) ;
		list = NULL ;
	}
}

void		st_dlist_free(STDLIST	*list)
{
	STDLIST* temp = NULL ;

	if(NULL != list)
	{
		do
		{
			temp = list ;
			list = list->next ;
			st_dlist_free1(temp);
		}while(NULL != list);
	}
}



STDLIST*	st_dlist_append(STDLIST		*list,	stpointer data)
{
	STDLIST* new_list = NULL ;
	STDLIST* last = NULL ;

	new_list = st_dlist_alloc();
	new_list->data = data ;
	new_list->next = NULL ;

	if(NULL != list)
	{
		last = st_dlist_last(list);			/* 配置new list 到链尾 */
		last->next = new_list ;
		new_list->prev = last ;

		return list ;
	}
	else
	{
		new_list->prev = NULL ;				/* 直接返回new list */

		return new_list ;
	}
}


STDLIST* 	st_dlist_prepend(STDLIST	*list,	stpointer data)
{
	STDLIST* new_list = NULL ;

	new_list = st_dlist_alloc();
	new_list->data = data ;
	new_list->next = list ;

	if(NULL != list)
	{
		new_list->prev = list->prev ;			/* NULL */
		if(NULL != list->prev)
		{
			list->prev->next = new_list ;		/* add new list to the middle of list and prev list */
		}
		list->prev = new_list ;
	}
	else
	{
		new_list->prev = NULL ;
	}
	
	return new_list ;
}



STDLIST*	st_dlist_insert(STDLIST		*list,	stpointer data,	stint position)
{
	STDLIST* new_list = NULL ;
	STDLIST* tmp_list = NULL ;

	if(position < 0)			/* if the position < 0 , add to the end of list */
	{
		return st_dlist_append(list, data);
	}	
	else if(0 == position)		/* if the position == 0 , add to the start of list */
	{
		return st_dlist_prepend(list, data);
	}

	tmp_list = st_dlist_nth(list, position);
	if(NULL == tmp_list)
	{
		return st_dlist_append(list, data);		/* if the position > max value */
	}

	new_list = st_dlist_alloc() ;
	new_list->data = data ;
	new_list->prev = tmp_list->prev ;
	if(NULL != tmp_list->prev)
	{
		tmp_list->prev->next = new_list ;
	}
	new_list->next = tmp_list ;
	tmp_list->prev = new_list ;

	if(tmp_list == list)
		return new_list ;					/* prepend */
	else
		return list ;
		
}


STDLIST*	st_dlist_insert_sorted(STDLIST		*list,
								  stpointer		data,
								  STCompareFunc	func)
{
	
}


/* 插入新节点到sibling节点之前，如果为NULL,叉到最后 */
STDLIST*	st_dlist_insert_before(STDLIST	*list,
					 			  STDLIST	*sibling,
					 			  stpointer	data)
{
	if(NULL == list)				/* 如果list为NULL, 则直接返回 */
	{
		list = st_dlist_alloc() ;
		list->data = data ;
		return list ;
	}
	else if (sibling)				/* 创建node，插入到sibling的前面 */
	{	
		STDLIST* node = NULL ;
		node->data = data ;
		node->prev = sibling->prev ;
		node->next = sibling ;
		sibling->prev = node ;
		if(NULL != node->prev)
		{
			node->prev->next = node ;
			return list ;
		}
		else
		{
			return node ;
		}
	}
	else							/* 如果sibling为NULL, 则查到list的尾部 */
	{
		STDLIST* last = NULL ;
#if 1
		last = st_dlist_last(list);
#else
		last = list ;
		while(last->next)
		{
			last = last->next ;
		}
#endif
		last->next = st_dlist_alloc() ;
		last->next->data = data ;
		last->next->prev = last ;
		last->next->next = NULL ;

		return list ;
	}
}


STDLIST*	st_dlist_concat(STDLIST		*list1, STDLIST			*list2)
{
	STDLIST* temp_list = NULL ;

	temp_list = st_dlist_last(list1) ;

	if(NULL != temp_list)
	{
		temp_list->next = list2 ;
	}
	else
	{
		list1 = list2 ;
	}
	list2->prev = temp_list ;

	return list1 ;
}


STDLIST*  	st_dlist_remove(STDLIST		*list, stconstpointer	data) 
{
	STDLIST* tmp_lsit = NULL ;

	tmp_lsit = list ;
	while(tmp_lsit)
	{
		if(tmp_lsit->data != data)			/* 找到包含data的节点 */
		{
			tmp_lsit = tmp_lsit->next ;	
		}
		else
		{
			if(NULL != tmp_lsit->prev)		/* 删除节点后重新连接 */
				tmp_lsit->prev->next = tmp_lsit->next ;
			if(NULL != tmp_lsit->next)
				tmp_lsit->next->prev = tmp_lsit->prev ;
			if(list == tmp_lsit)
				list = list->next ;
			st_dlist_free1(tmp_lsit) ;
			break ;
		}
	}
	return list ;
}

/* 删除所有data的节点 */
STDLIST*  	st_dlist_remove_all(STDLIST	*list, stconstpointer	data) 
{
	STDLIST* tmp_lsit = NULL ;

	tmp_lsit = list ;

	while(tmp_lsit)
	{
		if(data != tmp_lsit->data)
		{
			tmp_lsit = tmp_lsit->next ;
		}
		else
		{
			STDLIST* next = tmp_lsit->next ;			/* 保存当前节点的next */
			
			if(NULL != tmp_lsit->prev)					/* 保证唯一性 */
				tmp_lsit->prev->next = next ;
			else
				list = next ;
			
			if(NULL != tmp_lsit->next)
				next->prev = tmp_lsit->prev ;

			st_dlist_free1(tmp_lsit) ;
			tmp_lsit = next ;
		}
	}

	return list ;
}



/* 断开链表中得一个节点 */
STDLIST*	st_dlist_remove_link(STDLIST	*list, STDLIST *link_) 
{
	if(NULL != list->prev)
		list->prev->next = list->next ;
	if(NULL != list->next)
		list->next->prev = list->prev ;
	if(list == link_)
		list = list->next ;

	list->prev = NULL ;
	list->next = NULL ;

	return list ;								/* 返回已经断开的节点 */
}



/* 删除节点link_ */
STDLIST* 	st_dlist_delete_link(STDLIST	*list, STDLIST *link_) 
{
	list = st_dlist_remove(list, link_) ;
	st_dlist_free1(link_);

	return list ;
}


/* 逆转链表,跟单链表一样善用临时节点的保存过度 */
/*		<<<	 >>> >>> >>> >>>	
 *	NULL	2	3	4	5	NULL			
 *			 <<< <<< <<< 		
 *
 *	(1)last:		2	NULL					list:	3	4	5	NULL
 *	(2)last:		3	2	NULL				list:	4	5	NULL
 *	(3)last:		4	3	2	NULL			list:	5	NULL
 *	(4)last:		5	4	3	2	NULLL		list:	NULL
 *	(5)last:	NULL	5	4	3	2	NULL	list:
 * 
 */
STDLIST*  	st_dlist_reverse(STDLIST	*list) 
{
	STDLIST *last = NULL;

	while (list)
	{
		last = list;
		list = last->next;
		last->next = last->prev;
		last->prev = list;
	}

	return last;
}


/* 返回复制的链表 */
STDLIST*  	st_dlist_copy(STDLIST		*list) 
{
	STDLIST* new_list = NULL ;

	if(NULL != list)
	{
		STDLIST* last = NULL ;
		new_list = st_dlist_alloc();
		new_list->data = list->data ;
		new_list->prev = NULL ;
		last = new_list ;
		list = list->next ;
		while(list)
		{
			last->next = st_dlist_alloc() ;
			last->next->prev = last ;
			last = last->next ;
			last->data = list->data ;
			list = list->next ;
		}
		last->next = NULL ;
	}

	return new_list ;
}





/* 向前查找第n个节点 */
STDLIST*  	st_dlist_nth_prev(STDLIST 	*list, stuint n)
{
	while((n-- > 0) && (NULL != list))
		list = list->prev ;

	return list ;
}


/* 超找第n个节点的data */
stpointer 	st_dlist_nth_data(STDLIST	*list, stuint n)
{
	while((n-- > 0) && (NULL != list))
	{
		list = list->next ;
	}

	return list ? list->data : NULL ;

}



STDLIST*  	st_dlist_find(STDLIST *list, stconstpointer data)
{
	while(list)
	{
		if(list->data == data)
			break ;
		list = list->next ;
	}

	return list ;
}


STDLIST*   	st_dlist_find_custom(STDLIST	*list,
 							stconstpointer	data,
 							STCompareFunc	func)
{
	while(list)
	{
		if(!func(list->data, data))				/* 如果相等返回0 */
			return list ;

		list = list->next ;
	}
	return NULL ;
}

/* 查找llink在链表中得位置， 返回index */
stint     	st_dlist_position(STDLIST	*list, STDLIST *llink)
{
	stint i = 0 ;

	while(list)
	{
		if(list == llink)
			return i ;

		list = list->next ;
		i++ ;
	}
	return -1 ;
}


/* 查找data在链表的位置，返回index */
stint     	st_dlist_index(STDLIST		*list,
					 stconstpointer     data)
{
	stint i = 0 ;

	while(list)
	{
		if(list->data == data)
			return i ;

		i++ ;
		list = list->next ;
	}

	return -1 ;
}



/* 获取链表长度 */
stuint    	st_dlist_length(STDLIST		*list)
{
	stuint length = 0 ;

	while(list)
	{
		list = list->next ;
		length++ ;
	}
	return length ;
}


/* 遍历链表 */
void     	st_dlist_foreach(STDLIST 	*list,
					  STFunc			func,
					  stpointer			user_data)
{
	while(list)
	{
		STDLIST* next ;
		next = list->next ;
		(* func)(list->data, user_data) ;
		list = next ;
	}

}




static STDLIST *
st_dlist_sort_merge (STDLIST     *l1, 
		   STDLIST     *l2,
		   STFunc     compare_func,
		   stpointer  user_data)
{
	STDLIST list, *l, *lprev;
	stint cmp;

	l = &list; 
	lprev = NULL;

	while (l1 && l2)
	{
		cmp = ((STCompareDataFunc) compare_func) (l1->data, l2->data, user_data);

		if (cmp <= 0)
		{
			l->next = l1;
			l1 = l1->next;
		} 
		else 
		{
			l->next = l2;
			l2 = l2->next;
		}
		l = l->next;
		l->prev = lprev; 
		lprev = l;
	}
	l->next = l1 ? l1 : l2;
	l->next->prev = l;

	return list.next;
}

static STDLIST* 
st_dlist_sort_real (STDLIST    *list,
		  STFunc     compare_func,
		  stpointer  user_data)
{
	STDLIST *l1, *l2;

	if (!list) 
		return NULL;
	if (!list->next) 
		return list;

	l1 = list; 
	l2 = list->next;

	while ((l2 = l2->next) != NULL)
	{
		if ((l2 = l2->next) == NULL) 
			break;
		l1 = l1->next;
	}
	l2 = l1->next; 
	l1->next = NULL; 

	return st_dlist_sort_merge (st_dlist_sort_real (list, compare_func, user_data),
								st_dlist_sort_real (l2, compare_func, user_data),
								compare_func,
								user_data);
}

STDLIST*  	st_dlist_sort(STDLIST		*list,
					  STCompareFunc		compare_func) 
{
	return st_dlist_sort_real (list, (STFunc) compare_func, NULL);
}




STDLIST*  	st_dlist_sort_with_data(STDLIST	*list,
					  STCompareDataFunc		compare_func,
					  stpointer				user_data) 
{
	return st_dlist_sort_real (list, (STFunc) compare_func, user_data);
}


					  