#include <stdlib.h>
#include <stdio.h>
#include "st_slist.h"




/*-------------------------------------------------------------------------*
Function:	st_slist_last
Created By:   璐﹕tjq
Created Date: 璐?011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
stpointer data
Returns:
STSList
Discription:
get the last node of the list
 *-------------------------------------------------------------------------*/
STSList*  st_slist_last(STSList *list)
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


static STSList *
st_slist_sort_merge (STSList   *l1, 
		STSList   *l2,
		STFunc     compare_func,
		stpointer  user_data)
{
	STSList list, *l;
	stint cmp;

	l=&list;

	while (l1 && l2)
	{
		cmp = ((STCompareDataFunc) compare_func) (l1->data, l2->data, user_data);

		if (cmp <= 0)
		{
			l=l->next=l1;
			l1=l1->next;
		} 
		else 
		{
			l=l->next=l2;
			l2=l2->next;
		}
	}
	l->next= l1 ? l1 : l2;

	return list.next;
}

static STSList *
st_slist_sort_real (STSList   *list,
		STFunc     compare_func,
		stpointer  user_data)
{
	STSList *l1, *l2;

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
		l1=l1->next;
	}
	l2 = l1->next; 
	l1->next = NULL;

	return st_slist_sort_merge (st_slist_sort_real (list, compare_func, user_data),
			st_slist_sort_real (l2, compare_func, user_data),
			compare_func,
			user_data);	
}



/*-------------------------------------------------------------------------*
Function:	st_slist_sort
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
STCompareFunc compare_func
Returns:
STSList						### the new start of the SList
Discription:
Sorts a #GSList using the given comparison function.
 *-------------------------------------------------------------------------*/
STSList* st_slist_sort(STSList *list, STCompareFunc compare_func)
{
	return st_slist_sort_real (list, (STFunc) compare_func, NULL);
}

/*-------------------------------------------------------------------------*
Function:	st_slist_sort_with_data
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
STCompareFunc compare_func
Returns:
STSList						### the new start of the SList
Discription:
Sorts a #GSList using the given comparison function.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_sort_with_data          (STSList           *list,
		STCompareDataFunc  compare_func,
		stpointer          user_data)
{
	return st_slist_sort_real (list, (STFunc) compare_func, user_data);
}



/*-------------------------------------------------------------------------*
Function:	st_slist_foreach
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
STFunc func, 
stpointer user_data
Returns:
STSList						### the new start of the SList
Discription:
Calls a function for each element of a #GSList
 *-------------------------------------------------------------------------*/
void st_slist_foreach(STSList *list, STFunc func, stpointer user_data)
{
	while(NULL != list)
	{
		(*func)(list->data, user_data) ;
		list = list->next ;
	}
}




/*-------------------------------------------------------------------------*
Function:	st_slist_length
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
Returns:
STSList						### the new start of the SList
Discription:
This function iterates over the whole list to 
 * count its elements.
 *-------------------------------------------------------------------------*/
stuint st_slist_length(STSList *list)
{
	stuint length ;

	length = 0 ;

	while(NULL != list)
	{
		length++ ;
		list = list->next ;
	}	

	return length ;
}




/*-------------------------------------------------------------------------*
Function:	st_slist_position
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
STSList *llink
Returns:
STSList						### the new start of the SList
Discription:
Gets the position of the given element 
 * in the SList (starting from 0).
 *-------------------------------------------------------------------------*/
stint st_slist_position(STSList *list, STSList *llink)
{
	stint i = 0 ;

	while(NULL != list)
	{
		if(list == llink)
			return i ;

		i++ ;
		list = list->next ;
	}

	return -1 ;
}


/*-------------------------------------------------------------------------*
Function:	st_slist_find
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
stuint n
Returns:
STSList						### the new start of the SList
Discription:
Finds the element in a SList which 
 * contains the given data.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_find(STSList *list, stconstpointer data)
{
	while(NULL != list)
	{
		if(list->data == data)
			break ;
		list = list->next ;
	}	

	return list ;
}


/*-------------------------------------------------------------------------*
Function:	st_slist_nth
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
stuint n
Returns:
STSList						### the new start of the SList
Discription:
Gets the element at the given position in a SList.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_nth(STSList *list, stuint n)
{
	while(n-- && list)
		list = list->next ;

	return list ;
}


/*-------------------------------------------------------------------------*
Function:	st_slist_nth_data
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
stuint n
Returns:
STSList						### the new start of the SList
Discription:
Gets the data of the element at the given position.
 *-------------------------------------------------------------------------*/
stpointer st_slist_nth_data(STSList *list, stuint n)
{
	while(n-- && list)
		list = list->next ;

	return list ? list->data : NULL ;
}



/*-------------------------------------------------------------------------*
Function:	st_slist_copy
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
Returns:
STSList						### the new start of the SList
Discription:
Note that this is a "shallow" copy. If the list elements 
 * consist of pointers to data, the pointers are copied but 
 * the actual data isn't.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_copy(STSList *list)
{
	STSList *new_list = NULL ;

	if(NULL != list)
	{
		STSList *last = NULL ;

		new_list = st_slist_alloc();
		new_list->data = list->data ;
		last = new_list ;
		list = list->next ;

		while(NULL != list)
		{
			last->next = st_slist_alloc();
			last = last->next ;
			last->data = list->data ;
			list = list->next ;
		}
		list->next = NULL ;
	}


	return new_list ;
}


/*-------------------------------------------------------------------------*
Function:	st_slist_reverse
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
Returns:
STSList						### the new start of the SList
Discription:
Reverses a list
 *-------------------------------------------------------------------------*/
/*
list 2 3 5 6 7			list
next 3 5 6 7 			next = list->next
list 2					list->next = prev
prev 2					prev = list
list = 3 5 6 7			list = next

list 3 5 6 7
next 5 6 7 
list 3 2
prev 3 2
list = 5 6 7

list 5 6 7
next 6 7 
list 5 3 2
prev 5 3 2
list = 6 7

list 6 7
next 7 
list 6 5 3 2
prev 6 5 3 2
list = 7

list 7
next NULL 
list 7 6 5 3 2
prev 7 6 5 3 2
list = NULL
*/
STSList*  st_slist_reverse(STSList *list)
{
	STSList *prev = NULL ;

	while(NULL != list)
	{
		STSList *next = list->next ;
		
		list->next = prev ;
		prev = list ;
		list = next ;
	}

	return list ;
}



static /*inline*/ STSList*
_st_slist_remove_link (STSList *list,
		STSList *link)
{
	STSList *temp = NULL ;
	STSList *prev = NULL ;

	temp = list ;

	while(NULL != temp)
	{
		if(temp == link)
		{
			if(NULL != prev)
			{
				prev->next = temp->next ;
			}	
			if(list == temp)
			{
				list = list->next ;
			}	
			temp->next = NULL ;
			break ;
		}
		prev = temp ;
		temp = temp->next ;
	}

	return list ;
}


/*-------------------------------------------------------------------------*
Function:	st_slist_delete_link
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list1		
STSList *link_
Returns:
STSList						### the new start of the SList
Discription:
Removes the node link_ from the list and frees it. 
 * Compare this to g_slist_remove_link() which removes the node 
 * without freeing it.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_delete_link(STSList *list, STSList *link_)

{
	list = _st_slist_remove_link (list, link_);
	free(link_) ;
	link_ = NULL ;

	return list ;
}

/*-------------------------------------------------------------------------*
Function:	st_slist_remove_link
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list1		
STSList *link_
Returns:
STSList						### the new start of the SList
Discription:
Removes an element from a #GSList, without 
 * freeing the element. The removed element's next 
 * link is set to %NULL, so that it becomes a
 * self-contained list with one element.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_remove_link(STSList *list, STSList *link_)
{
	return _st_slist_remove_link (list, link_);
}

/*-------------------------------------------------------------------------*
Function:	st_slist_remove_all
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list1		
stconstpointer data
Returns:
STSList						### the new start of the SList
Discription:
Removes all list nodes with data equal to @data. 
 * Returns the new head of the list. Contrast with 
 * g_slist_remove() which removes only the first node 
 * matching the given data.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_remove_all(STSList *list, stconstpointer data) 
{
	STSList *prev = NULL ;
	STSList *temp = NULL ;

	temp = list ;

	while(NULL != temp)
	{
		if(temp->data == data)
		{
			//STSList *next = temp->next ;
			if(NULL != prev)
			{
				prev = temp->next ;
			}
			else
			{
				list = temp->next ;
			}
			free(temp);
			temp = NULL ;
			temp = temp->next ;
		}
		else
		{
			prev = temp ;
			temp = temp->next ;
		}	
	}	
}


/*-------------------------------------------------------------------------*
Function:	st_slist_remove
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list1		
stconstpointer data
Returns:
STSList						### the new start of the SList
Discription:
Removes an element from a SList.
 * If two elements contain the same data, only the first is removed.
 * If none of the elements contain the data, the SList is unchanged.
 *
 *-------------------------------------------------------------------------*/
STSList*  st_slist_remove(STSList *list, stconstpointer data)
{
	STSList *prev = NULL ;		// 保存前一个指针，用于连接用
	STSList *temp = NULL ;

	temp = list ;

	while(NULL != temp)
	{
		if(temp->data == data)
		{
			if(NULL != prev)	// prev 不为空，为中间节点
			{
				prev->next = temp->next ;
			}
			else		// prev 为空，即第一节点
			{
				list = temp->next ;
			}	
			free(temp);
			temp = NULL ;
			break ;		// 删除第一个后就break
		}
		prev = temp ;
		temp = temp->next ;
	}	

	return list ;
}


/*-------------------------------------------------------------------------*
Function:	st_slist_concat
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list1		
STSList *list2				### SList to add to the end of the first
Returns:
STSList						### the new start of the SList
Discription:
Adds the second #GSList onto the end of the first #GSList.
 * Note that the elements of the second #GSList are not copied.
 * They are used directly.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_concat(STSList *list1, STSList *list2)
{
	if(NULL != list2)
	{
		if(NULL != list1)
		{
			st_slist_last(list1)->next = list2 ;
		}	
		else 
		{
			list1 = list2 ;
		}
	}	

	return list1 ;
}


static STSList*
st_slist_insert_sorted_real (STSList   *list,
		stpointer  data,
		STFunc     func,
		stpointer  user_data)
{
	STSList *tmp_list = list;
	STSList *prev_list = NULL;
	STSList *new_list;
	stint cmp;


	if (!list)
	{
		new_list = st_slist_alloc ();
		new_list->data = data;
		new_list->next = NULL;
		return new_list;
	}

	cmp = ((STCompareDataFunc) func) (data, tmp_list->data, user_data);

	while ((tmp_list->next) && (cmp > 0))	// fit the position: end of the list or cmp < 0
	{
		prev_list = tmp_list;
		tmp_list = tmp_list->next;

		cmp = ((STCompareDataFunc) func) (data, tmp_list->data, user_data);
	}

	// create a new list
	new_list = st_slist_alloc ();
	new_list->data = data;

	if ((!tmp_list->next) && (cmp > 0))
	{
		tmp_list->next = new_list;
		new_list->next = NULL;
		return list;
	}

	if (prev_list)
	{
		prev_list->next = new_list;
		new_list->next = tmp_list;
		return list;
	}
	else
	{
		new_list->next = list;
		return new_list;
	}
}

/*-------------------------------------------------------------------------*
Function:	st_slist_insert_sorted
Created By:   stjq
Created Date: 2011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
stpointer data				### the data for the new element
stint position				### the position to insert the element. 
Returns:
STSList						### the new start of the SList
Discription:
Inserts a new element into the list at the given position.
If this is negative, or is larger than the number 
 *     of elements in the list, the new element is added on
 *     to the end of the list.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_insert_sorted(STSList *list,
		stpointer			data,
		STCompareFunc		func)
{
	return st_slist_insert_sorted_real (list, data, (STFunc) func, NULL);
}

STSList*  st_slist_insert_sorted_with_data (STSList *list,
		stpointer          data,
		STCompareDataFunc  func,
		stpointer          user_data)
{
	return st_slist_insert_sorted_real (list, data, (STFunc) func, user_data);
}

/*-------------------------------------------------------------------------*
Function:	st_slist_insert
Created By:   璐﹕tjq
Created Date: 璐?011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
stpointer data				### the data for the new element
stint position				### the position to insert the element. 
Returns:
STSList						### the new start of the SList
Discription:
Inserts a new element into the list at the given position.
If this is negative, or is larger than the number 
 *     of elements in the list, the new element is added on
 *     to the end of the list.
 *-------------------------------------------------------------------------*/
STSList*  st_slist_insert(STSList *list, stpointer data, stint position)
{
	STSList* new_list = NULL ;
	STSList* prev_list = NULL ;
	STSList* temp_list = NULL ;

	if(0 > position)
		st_slist_append(list, data);
	else if(0 == position)
		st_slist_prepend(list, data);

	new_list = st_slist_alloc();
	new_list->data = data ;

	if(NULL == list)
	{
		new_list->next = NULL ;
		return new_list ;
	}

	prev_list = NULL ;
	temp_list = list ;

	// 找到所在位置
	while((position-- > 0) && temp_list)	
	{
		prev_list = temp_list ;
		temp_list = temp_list->next ;
	}
	// 将new_list放到合适的位置
	if(NULL != prev_list)
	{
		new_list->next = prev_list->next ;
		prev_list->next = list ;
	}
	else
	{
		new_list->next = list ;
		list = new_list ;
	}

	return list ;
}


/*-------------------------------------------------------------------------*
Function:	st_slist_prepend
Created By:   璐﹕tjq
Created Date: 璐?011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
stpointer data
Returns:
STSList
Discription:
append the data to the start of list
 *-------------------------------------------------------------------------*/
STSList*  st_slist_prepend(STSList *list, stpointer data)
{
	STSList *new_list = NULL ;

	new_list = (STSList *)st_slist_alloc();
	new_list->data = data ;
	new_list->next = list ;

	return new_list ;
}

/*-------------------------------------------------------------------------*
Function:	st_slist_append
Created By:   璐﹕tjq
Created Date: 璐?011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list		
stpointer data
Returns:
STSList
Discription:
append the data to the end of list
 *-------------------------------------------------------------------------*/
STSList*  st_slist_append(STSList *list, stpointer data)
{
	STSList* new_list = NULL ;
	STSList* last = NULL ;

	new_list = (STSList*)st_slist_alloc();
	new_list->data = data ;
	new_list->next = NULL ;

	if(NULL != list)
	{
		last = st_slist_last (list);
		/* g_assert (last != NULL); */
		last->next = new_list;

		return list;	
	}
	else
	{
		return new_list ;
	}
}

STSList*  st_slist_merge_2_list(STSList	*head1, STSList	*head2)
{
	STSList *head,*tail,*p = head1,*q = head2,*s;

    if( NULL == p )
        return q;
    if( NULL == q )
        return p;

    tail = p;
    if( p->data > q->data) 
        tail = q;
    head = tail;

    while( NULL != p && NULL != q )
    {
        if(p->data <= q->data ) 
            //如果p所指元素<q所指元素，那么把p所指元素，率先拉入合并后的链表中，
            //p赋给s，并从p的下一个元素p->next查找。
            //直到发现p所指 不再 < q，而是p > q了 即转至下述代码的else部分。
        {
            s = p; 
            p = p->next;
        }
        else
        {
            s = q;
            q = q->next;
        }
        tail->next = s;
        tail = s;
    }

    if( NULL == p )
        p = q;
    s = p;
    tail->next = s;

    return head;	
}


STSList*  st_slist_recursive_merge_2_list(STSList	*head1, STSList	*head2)
{
	STSList *head = NULL ;
	
	if ( head1 == NULL )
		return head2 ;
	if ( head2 == NULL)
		return head1 ;
	
	if ( head1->data < head2->data )
	{
		head = head1 ;
		head->next = st_slist_recursive_merge_2_list(head1->next,head2);
	}
	else
	{
		head = head2 ;
		head->next = st_slist_recursive_merge_2_list(head1,head2->next);
	}
	return head ;	
}


/*-------------------------------------------------------------------------*
Function:	st_slist_free
Created By:   璐﹕tjq
Created Date: 璐?011/08/06
Modified By:
Modified Date:
Parameters:
STSList *list								
Returns:
void
Discription:
free all the mem of list node
 *-------------------------------------------------------------------------*/
void st_slist_free(STSList *list)
{
	STSList *temp = NULL ;

	if(NULL != list)
	{
		do
		{
			temp = list ;
			list = list->next ;
			free(temp);
			temp = NULL ;
		}while(NULL != list);
	}	
}

/*-------------------------------------------------------------------------*
Function:	st_slist_alloc
Created By:   璐﹕tjq
Created Date: 璐?011/08/06
Modified By:
Modified Date:
Parameters:
void								### the list which be dump
Returns:
void
Discription:
alloc the mem of list node
 *-------------------------------------------------------------------------*/
STSList *st_slist_alloc(void)
{
	return malloc(sizeof(STSList));
}

void st_dump_list(STSList *head)
{
	STSList *p;

	p = head;		// protect the head point
	if(head != NULL) /*只要不是空链表，就输出链表中所有节点*/
	{
		printf("head is %o\n", (stuint)head); /*输出头指针指向的地址*/
		do 
		{ 
			printf("%o   %d   %o\n", (stuint)p, (stint)p->data, (stuint)p->next);
			p = p->next; /*移到下一个节点*/
		}
		while (p != NULL);
	}
}


///////////////////////////sort list///////////////////////////////
/*-------------------------------------------------------------------------*
Function:	st_slist_direct_insert_sort
Created By:   ..stjq
Created Date: ..2011/08/06
Modified By:
Modified Date:
Parameters:
STSList* list
Returns:
STSList* list
Discription:
==========================
 功能：直接插入排序(由小到大)
 返回：指向链表表头的指针
==========================
直接插入排序的基本思想就是假设链表的前面n-1个节点是已经按键值
（就是用它排序的字段，我们取学号num为键值）排好序的，对于节点n在
这个序列中找插入位置，使得n插入后新序列仍然有序。按照这种思想，依次
对链表从头到尾执行一遍，就可以使无序链表变为有序链表。 

单向链表的直接插入排序图示：
---->[1]---->[3]---->[2]...---->[n]---->[NULL]（原链表）
head   1->next  3->next  2->next   n->next

---->[1]---->[NULL]（从原链表中取第1个节点作为只有一个节点的有序链表）
head
图11

---->[3]---->[2]...---->[n]---->[NULL]（原链表剩下用于直接插入排序的节点）
first   3->next  2->next   n->next
图12

---->[1]---->[2]---->[3]...---->[n]---->[NULL]（排序后链表）
head   1->next  2->next  3->next   n->next

图13：有N个节点的链表直接插入排序

1、先在原链表中以第一个节点为一个有序链表，其余节点为待定节点。
2、从图12链表中取节点，到图11链表中定位插入。
3、上面图示虽说画了两条链表，其实只有一条链表。在排序中，实质只增加了一个
用于指向剩下需要排序节点的头指针first罢了。
这一点请读者务必搞清楚，要不然就可能认为它和上面的选择排序法一样了。
 *-------------------------------------------------------------------------*/
STSList* st_slist_direct_insert_sort(STSList* head)
{
	STSList *first ;		/*为原链表剩下用于直接插入排序的节点头指针*/
	STSList *iNode ;		/*临时指针变量：插入节点*/	
	STSList *p; 			/*临时指针变量p->next == q*/
	STSList *q; 			/*临时指针变量p->next == q*/

	first = head->next ;	/*原链表剩下用于直接插入排序的节点链表：可根据图12来理解。*/
	head->next = NULL ;		/*只含有一个节点的链表新的有序链表：可根据图11来理解。*/

	while(NULL != first)	/*遍历剩下无序的链表*/
	{
		/* 次for循环查找设当的插入位置，保存在pq指针上 */
		/*
		 * 有三种情况:(1)插头;(2)插中间;(3)插尾巴
		 * 
		 */
		for(iNode = first, q = head ; (NULL != q) && (q->data < iNode->data) ; p = q, q = q->next);

		/*退出for循环，就是找到了插入的位置*/
		/*注意：按道理来说，这句话可以放到下面注释了的那个位置也应该对的，但是就是不能。原因：你若理解了上面的第3条，就知道了。*/
		first = first->next ;	/*无序链表中的节点离开，以便它插入到有序链表中。并生成新的待排序链表*/ 

		if(q == head)			/*插在第一个节点之前*/
		{
			head = iNode ;
		}
		else					/* 插中间或者插尾巴，此时p为待查位置的上个节点，q为下个节点，或者为NULL */
		{
			p->next = iNode ;
		}
		iNode->next = q ;		/* 完成节点的插入，生成新的排序列表 */ 
		/*first = first->next;*/
	}

	return head ;
}


/*-------------------------------------------------------------------------*
Function:	st_slist_select_sort
Created By:   ..stjq
Created Date: ..2011/08/06
Modified By:
Modified Date:
Parameters:
STSList* list
Returns:
STSList* list
Discription:
==========================
 功能：选择排序(由小到大)
 返回：指向链表表头的指针
==========================
选择排序的基本思想就是反复从还未排好序的那些节点中，
 选出键值（就是用它排序的字段，我们取学号num为键值）最小的节点，
 依次重新组合成一个链表。

 我认为写链表这类程序，关键是理解：
 head存储的是第一个节点的地址，head->next存储的是第二个节点的地址；
 任意一个节点p的地址，只能通过它前一个节点的next来求得。

单向链表的选择排序图示：
---->[1]---->[3]---->[2]...---->[n]---->[NULL]（原链表）
head   1->next  3->next  2->next   n->next

---->[NULL]（空链表）
first
tail

---->[1]---->[2]---->[3]...---->[n]---->[NULL]（排序后链表）
first   1->next  2->next  3->next   tail->next

图10：有N个节点的链表选择排序

1、先在原链表中找最小的，找到一个后就把它放到另一个空的链表中；
2、空链表中安放第一个进来的节点，产生一个有序链表,并且让它在原链表中分离出来（此时要注意原链表中出来的是第一个节点还是中间其它节点）；
3、继续在原链表中找下一个最小的，找到后把它放入有序链表的尾指针的next,然后它变成其尾指针
 *-------------------------------------------------------------------------*/
STSList* st_slist_select_sort(STSList* head)
{
	STSList *first;	/*排列后新有序链的表头指针*/
	STSList *tail; 	/*排列后新有序链的表尾指针*/ 
	STSList *p_min; /*保留键值更小的节点的前驱节点的指针*/
	STSList *min; 	/*存储最小节点*/ 
	STSList *p; 	/*当前临时比较的节点*/

	first = NULL ;	/* 初始化新有序链表为空 */

	while(NULL != head)
	{
		/*注意：这里for语句就是体现选择排序思想的地方*/
		/* 每次比较都必须把剩余的待排序链表扫描一遍，所以比较次数为((n-1)*n)/2 */
		for(p=head, min=head ; p->next != NULL ; p=p->next)	/*循环遍历链表中的节点，找出此时最小的节点。*/
		{
			if(p->next->data < min->data)					/*找到一个比当前min小的节点。*/
			{
				p_min = p ;									/*保存找到节点的前驱节点：显然p->next的前驱节点是p。*/
				min = p->next ;								/*保存键值更小的节点。*/
			}	
		}
		/*上面for语句结束后，就要做两件事；一是把它放入新有序链表中；二是根据相应的条件判断，安排它离开原来的链表。*/
		/*第一件事添加最小的节点到新有序链表*/
		if(NULL == first)
		{
			first = min ;				/*第一次找到键值最小的节点。*/
			tail = min ;				/*注意：尾指针让它指向最后的一个节点。*/
		}	
		else							/*有序链表中已经有节点*/
		{
			tail->next = min ;			/* 把新的最小节点添加到有序链的尾部 */
			tail = min ;				/* 更新有序链的尾节点指针 */
		}

		/*第二件事删除原链表节点*/
		if(min == head)					/*如果找到的最小节点就是第一个节点*/
		{
			head = head->next ;			/* 直接更新无序链的头指针为head->next */
		}
		else							/*如果不是第一个节点*/
		{
			p_min->next = min->next ;	/*前次最小节点的next指向当前min的next,这样就让min离开了原链表。*/
		}
	}

	/*循环结束得到有序链表first*/
	if(NULL != first)
		tail->next = NULL ;				/*单向链表的最后一个节点的next应该指向NULL*/ 

	head = first ;

	return head ;
}

static void my_swap(stint **a,stint **b)  
{  
    stint temp; 
    temp=*a;  
    *a=*b;  
    *b=temp;  
}  

STSList* st_slist_quick_sort(STSList* phead, STSList *pend)
{
	STSList *pslow=phead;  
    STSList *pfast=phead->next;  
    STSList *ptemp=phead;  

    if(phead==NULL || pend==NULL)  
        return ;  
    if(phead==pend)  
        return ;  
    
    while(pfast)  
    {  
        if(pfast->data<phead->data)					//每次都选择待排序链表的头结点作为划分的基准  
        {  
            ptemp=pslow;							//ptemp始终为pslow的前驱结点  
            pslow=pslow->next;  
			//fprintf(stderr, "pslow->data %d, pfast->data %d\n", pslow->data, pfast->data);
            my_swap(&pslow->data,&pfast->data);		//pslow指针指向比基准小的结点组成的链表  
            //fprintf(stderr, "pslow->data %d, pfast->data %d\n", pslow->data, pfast->data);
        }  
        pfast=pfast->next;  
    }  
  
    my_swap(&pslow->data,&phead->data);				//此时pslow指针指向比基准小的结点组成的链表的最后一个结点，也就是基准的位置，所以要与基准（head结点）交换  
    
    st_slist_quick_sort(phead,ptemp);				//ptemp为左右两部分分割点（基准）的前一个结点  
    st_slist_quick_sort(pslow->next,pend);			//右部分是比基准大的结点组成的链表 	

	return phead ;
}


void st_slist_quick_sort2(STSList **head, STSList *end)  
{
    STSList *right;     
    STSList **left_walk, **right_walk;     
    STSList *pivot, *old;     
    stint count, left_count, right_count;     
    if (*head == end)  
        return;  
	
    do {     
        pivot = *head;
        left_walk = head;
        right_walk = &right;     
        left_count = right_count = 0;     
        //取第一个节点作为比较的基准，小于基准的在左面的子链表中，     
        //大于基准的在右边的子链表中     
        for (old = (*head)->next; old != end; old = old->next)  
        {     
            if (old->data < pivot->data)  
            {      
            	//小于基准,加入到左面的子链表,继续比较     
                ++left_count;     
                *left_walk = old;            //把该节点加入到左边的链表中，     
                left_walk = &(old->next);     
            }  
            else  
            {                         //大于基准,加入到右边的子链表，继续比较     
                ++right_count;     
                *right_walk = old;                
                right_walk = &(old->next);     
            }     
        }     
        //合并链表     
        *right_walk = end;       //结束右链表     
        *left_walk = pivot;      //把基准置于正确的位置上     
        pivot->next = right;     //把链表合并     
        //对较小的子链表进行快排序，较大的子链表进行迭代排序。     
        if(left_walk > right_walk)  
        {  
            st_slist_quick_sort2(&(pivot->next), end);     
            end = pivot;     
            count = left_count;     
        }  
        else  
        {     
            st_slist_quick_sort2(head, pivot);     
            head = &(pivot->next);     
            count = right_count;     
        }     
    }  
    while (count > 1);      	
}




/*获取链表中的节点数*/
static stint getNodeNum(STSList* h)
{
	int n=0;
	while(h)
	{
		n++;
		h=h->next;
	}
	return n;
}

 

/*把一个指针移动n步*/
static void move(STSList** h,stint n)
{
	stint i;
	for(i=0;i<n;i++)
	{
		*h=(*h)->next;
	}
}

void st_slist_shell_sort(STSList* list)
{
	stint i=0;
	stint flag=0;		/*标记一次快速插入迭代是否结束*/
	STSList* h1;		/*h1用来从头开始遍历寻找插入节点*/
	STSList* h2;		/*h2用来指向需要插入的结点*/
	STSList* h3;		/*h3用来指向h2的前一个结点*/
	stint n=0;			/*节点数*/
	stint t;			/*步进值*/
	
	n=getNodeNum(list);	/*节点数*/

	for(t=n/2;t>0;t=t/2)/*希尔迭代，每次缩小步进值*/
	{
		h2=h3=list;		/*每次希尔迭代，初始化h2和h3的位置*/
		move(&h3,t-1);
		move(&h2,t);	/*移动t步*/

		while(h2)		/*插入排序*/
		{
			h1=list;	/*初始化h1的位置*/
			flag=0;		/*flag置0*/
			while(flag==0)
			{
				if((h1->next->data) > (h2->data))/*如果找到，即把h2所指向的结点插到h1后面，然后跳出循环*/
				{
					h3->next=h2->next;
					h2->next=h1->next;
					h1->next=h2;
					h2=h3->next;/*h2所指节点已经移到前面，h2要向后移动*/
					break; /*别忘了此处的break*/
				}
				/*移动h1*/
				for(i=0 ; i<t ; i++)
				{
					h1=h1->next;
					if((h1==h2)||(h1==NULL))
					{
						flag=1;/*h1移到了h2*/
						break;/*马上停止移动，防止指针越界*/
					}
				}
			}

			if((flag==1)&&(h2!=NULL))/*只在h2所指结点不需要前插时，移动h2和h3*/
			{
				h2=h2->next;
				h3=h3->next;
			}
		}
	}	
}


/*-------------------------------------------------------------------------*
Function:	st_slist_bubble_sort
Created By:   ..stjq
Created Date: ..2011/08/06
Modified By:
Modified Date:
Parameters:
STSList* list
Returns:
STSList* list
Discription:
==========================
 功能：冒泡排序(由小到大)
 返回：指向链表表头的指针
==========================
直接插入排序的基本思想就是对当前还未排好序的范围内的全部节点，
 自上而下对相邻的两个节点依次进行比较和调整，让键值（就是用它排
 序的字段，我们取学号num为键值）较大的节点往下沉，键值较小的往
 上冒。即：每当两相邻的节点比较后发现它们的排序与排序要求相反时，
 就将它们互换。

 
单向链表的冒泡排序图示：
---->[1]---->[3]---->[2]...---->[n]---->[NULL]（原链表）
head   1->next  3->next  2->next   n->next 

---->[1]---->[2]---->[3]...---->[n]---->[NULL]（排序后链表）
head   1->next  2->next  3->next   n->next

图14：有N个节点的链表冒泡排序

任意两个相邻节点p、q位置互换图示:
假设p1->next指向p，那么显然p1->next->next就指向q,
p1->next->next->next就指向q的后继节点，我们用p2保存
p1->next->next指针。即：p2=p1->next->next，则有：
[  ]---->[p]---------->[q]---->[  ]（排序前）
  p1->next  p1->next->next  p2->next
图15

[  ]---->[q]---------->[p]---->[  ]（排序后）

图16

1、排序后q节点指向p节点，在调整指向之前，我们要保存原p的指向节点地址，即：p2=p1->next->next；
2、顺着这一步一步往下推,排序后图16中p1->next->next要指的是p2->next,所以p1->next->next=p2->next;
3、在图15中p2->next原是q发出来的指向，排序后图16中q的指向要变为指向p的，而原来p1->next是指向p的，所以p2->next=p1->next;
4、在图15中p1->next原是指向p的，排序后图16中p1->next要指向q,原来p1->next->next（即p2)是指向q的，所以p1->next=p2;
5、至此，我们完成了相邻两节点的顺序交换。
6、下面的程序描述改进了一点就是记录了每次最后一次节点下沉的位置，这样我们不必每次都从头到尾的扫描，只需要扫描到记录点为止。
   因为后面的都已经是排好序的了。
 *-------------------------------------------------------------------------*/
STSList* st_slist_bubble_sort(STSList* head)
{
	STSList *endpt; 	/*控制循环比较*/
	STSList *p; 		/*临时指针变量*/
	STSList *p1; 
	STSList *p2;

	p1 = (STSList *)malloc(sizeof(STSList));
 	p1->next = head;	/*注意理解：我们增加一个节点，放在第一个节点的前面，主要是为了便于比较。因为第一个节点没有前驱，我们不能交换地址。*/
 	head = p1;			/*让head指向p1节点，排序完成后，我们再把p1节点释放掉*/

	for (endpt=NULL; endpt!=head; endpt=p) /*结合第6点理解*/
	{
		for (p=p1=head; p1->next->next!=endpt; p1=p1->next)
		{
			if (p1->next->data > p1->next->next->data) /*如果前面的节点键值比后面节点的键值大，则交换*/
			{
				p2 = p1->next->next; 		/*结合第1点理解*/	/* 保存后驱的所有节点 */
				p1->next->next = p2->next;	/*结合第2点理解*/	/* 把后驱节点提前一位 */
				p2->next = p1->next; 		/*结合第3点理解*/	/* 把交换好的节点存放在p2 */
				p1->next = p2; 				/*结合第4点理解*/	/* 把交换好的节点存放在p1 */
				p = p1->next->next; 		/*结合第6点理解*/	/* 记录了每次最后一次节点下沉的位置 */
			}
		}
	}

	p1 = head; 			/*把p1的信息去掉*/
	head = head->next; 	/*让head指向排序后的第一个节点*/
	free(p1); 			/*释放p1*/
	p1 = NULL; 			/*p1置为NULL，保证不产生“野指针”，即地址不确定的指针变量*/

	return head;
}


STSList** DistributeL(STSList* p, int keyNum, STSList ** pa, stint NUM) 	//进行数据的分配
{
	stint arr[10]= {0};	/*	记录同一个位数相同数的个数	*/
	stint k;

	while(p)
	{
		k = (stint)p->data/keyNum%10;

		if(NULL == pa[k])
		{
			pa[k] = (STSList*)malloc(sizeof(STSList)*NUM);
			pa[k][arr[k]] = *p;
			pa[k][arr[k]].next = NULL;
			++arr[k];
		}
		else
		{
			pa[k][arr[k]] = *p;
			pa[k][arr[k]].next = NULL;
			pa[k][arr[k]-1].next = &pa[k][arr[k]];
			++arr[k];
		}
		p = p->next;
	}

	return pa;

}

STSList* CollectL(STSList* p, STSList ** pa, stint NUM)  		//进行数据的收集
{
	stint count;
	stint i = 0;
	STSList* pc;		/*	存储pa[count]的初始值，在释放空间时使用	*/
	STSList* pp = p;	/*	存储p的初始值，返回值时使用	*/

	for(count = 0; count < NUM; ++count)
	{
		pc = pa[count];

		while(NULL != pa[count])
		{
			p[i] = *pa[count];
			pa[count] = pa[count]->next;
			if((NUM-1) == i)
			{
				p[i].next = NULL;
			}
			else
			{
				p[i].next = &p[i+1];
			}

			++i;

		} 

		pa[count] = pc;

		if(NULL != pa[count])
			free(pa[count]);

	}

	return pp;

}


STSList* st_slist_radix_sort(STSList* list, stint radix)
{
	stint key = 1;
	stint i;
	stint j;
	STSList* h[10] = {0};
	stint NUM ;

	NUM = getNodeNum(list);			
	for(i = 0; i < radix; ++i, key *= 10)
	{
		DistributeL(list, key, h, NUM);
		
		list = CollectL((STSList*)list, h, NUM);
		
		for(j = 0; j < NUM; ++j)
			h[j] = NULL;
		
		//printf("after sort\n");
		//OutputLink(p);
	}	

	return list ;	
}


