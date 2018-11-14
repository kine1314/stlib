#include <stdlib.h>
#include <stdio.h>
#include "st_slist.h"




/*-------------------------------------------------------------------------*
Function:	st_slist_last
Created By:   贩stjq
Created Date: �?011/08/06
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
	STSList *prev = NULL ;		// ����ǰһ��ָ�룬����������
	STSList *temp = NULL ;

	temp = list ;

	while(NULL != temp)
	{
		if(temp->data == data)
		{
			if(NULL != prev)	// prev ��Ϊ�գ�Ϊ�м�ڵ�
			{
				prev->next = temp->next ;
			}
			else		// prev Ϊ�գ�����һ�ڵ�
			{
				list = temp->next ;
			}	
			free(temp);
			temp = NULL ;
			break ;		// ɾ����һ�����break
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
Created By:   贩stjq
Created Date: �?011/08/06
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

	// �ҵ�����λ��
	while((position-- > 0) && temp_list)	
	{
		prev_list = temp_list ;
		temp_list = temp_list->next ;
	}
	// ��new_list�ŵ����ʵ�λ��
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
Created By:   贩stjq
Created Date: �?011/08/06
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
Created By:   贩stjq
Created Date: �?011/08/06
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
            //���p��ָԪ��<q��ָԪ�أ���ô��p��ָԪ�أ���������ϲ���������У�
            //p����s������p����һ��Ԫ��p->next���ҡ�
            //ֱ������p��ָ ���� < q������p > q�� ��ת�����������else���֡�
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
Created By:   贩stjq
Created Date: �?011/08/06
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
Created By:   贩stjq
Created Date: �?011/08/06
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
	if(head != NULL) /*ֻҪ���ǿ�������������������нڵ�*/
	{
		printf("head is %o\n", (stuint)head); /*���ͷָ��ָ��ĵ�ַ*/
		do 
		{ 
			printf("%o   %d   %o\n", (stuint)p, (stint)p->data, (stuint)p->next);
			p = p->next; /*�Ƶ���һ���ڵ�*/
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
 ���ܣ�ֱ�Ӳ�������(��С����)
 ���أ�ָ�������ͷ��ָ��
==========================
ֱ�Ӳ�������Ļ���˼����Ǽ��������ǰ��n-1���ڵ����Ѿ�����ֵ
����������������ֶΣ�����ȡѧ��numΪ��ֵ���ź���ģ����ڽڵ�n��
����������Ҳ���λ�ã�ʹ��n�������������Ȼ���򡣰�������˼�룬����
�������ͷ��βִ��һ�飬�Ϳ���ʹ���������Ϊ�������� 

���������ֱ�Ӳ�������ͼʾ��
---->[1]---->[3]---->[2]...---->[n]---->[NULL]��ԭ����
head   1->next  3->next  2->next   n->next

---->[1]---->[NULL]����ԭ������ȡ��1���ڵ���Ϊֻ��һ���ڵ����������
head
ͼ11

---->[3]---->[2]...---->[n]---->[NULL]��ԭ����ʣ������ֱ�Ӳ�������Ľڵ㣩
first   3->next  2->next   n->next
ͼ12

---->[1]---->[2]---->[3]...---->[n]---->[NULL]�����������
head   1->next  2->next  3->next   n->next

ͼ13����N���ڵ������ֱ�Ӳ�������

1������ԭ�������Ե�һ���ڵ�Ϊһ��������������ڵ�Ϊ�����ڵ㡣
2����ͼ12������ȡ�ڵ㣬��ͼ11�����ж�λ���롣
3������ͼʾ��˵��������������ʵֻ��һ�������������У�ʵ��ֻ������һ��
����ָ��ʣ����Ҫ����ڵ��ͷָ��first���ˡ�
��һ���������ظ������Ҫ��Ȼ�Ϳ�����Ϊ���������ѡ������һ���ˡ�
 *-------------------------------------------------------------------------*/
STSList* st_slist_direct_insert_sort(STSList* head)
{
	STSList *first ;		/*Ϊԭ����ʣ������ֱ�Ӳ�������Ľڵ�ͷָ��*/
	STSList *iNode ;		/*��ʱָ�����������ڵ�*/	
	STSList *p; 			/*��ʱָ�����p->next == q*/
	STSList *q; 			/*��ʱָ�����p->next == q*/

	first = head->next ;	/*ԭ����ʣ������ֱ�Ӳ�������Ľڵ������ɸ���ͼ12����⡣*/
	head->next = NULL ;		/*ֻ����һ���ڵ�������µ����������ɸ���ͼ11����⡣*/

	while(NULL != first)	/*����ʣ�����������*/
	{
		/* ��forѭ�������赱�Ĳ���λ�ã�������pqָ���� */
		/*
		 * ���������:(1)��ͷ;(2)���м�;(3)��β��
		 * 
		 */
		for(iNode = first, q = head ; (NULL != q) && (q->data < iNode->data) ; p = q, q = q->next);

		/*�˳�forѭ���������ҵ��˲����λ��*/
		/*ע�⣺��������˵����仰���Էŵ�����ע���˵��Ǹ�λ��ҲӦ�öԵģ����Ǿ��ǲ��ܡ�ԭ���������������ĵ�3������֪���ˡ�*/
		first = first->next ;	/*���������еĽڵ��뿪���Ա������뵽���������С��������µĴ���������*/ 

		if(q == head)			/*���ڵ�һ���ڵ�֮ǰ*/
		{
			head = iNode ;
		}
		else					/* ���м���߲�β�ͣ���ʱpΪ����λ�õ��ϸ��ڵ㣬qΪ�¸��ڵ㣬����ΪNULL */
		{
			p->next = iNode ;
		}
		iNode->next = q ;		/* ��ɽڵ�Ĳ��룬�����µ������б� */ 
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
 ���ܣ�ѡ������(��С����)
 ���أ�ָ�������ͷ��ָ��
==========================
ѡ������Ļ���˼����Ƿ����ӻ�δ�ź������Щ�ڵ��У�
 ѡ����ֵ����������������ֶΣ�����ȡѧ��numΪ��ֵ����С�Ľڵ㣬
 ����������ϳ�һ������

 ����Ϊд����������򣬹ؼ�����⣺
 head�洢���ǵ�һ���ڵ�ĵ�ַ��head->next�洢���ǵڶ����ڵ�ĵ�ַ��
 ����һ���ڵ�p�ĵ�ַ��ֻ��ͨ����ǰһ���ڵ��next����á�

���������ѡ������ͼʾ��
---->[1]---->[3]---->[2]...---->[n]---->[NULL]��ԭ����
head   1->next  3->next  2->next   n->next

---->[NULL]��������
first
tail

---->[1]---->[2]---->[3]...---->[n]---->[NULL]�����������
first   1->next  2->next  3->next   tail->next

ͼ10����N���ڵ������ѡ������

1������ԭ����������С�ģ��ҵ�һ����Ͱ����ŵ���һ���յ������У�
2���������а��ŵ�һ�������Ľڵ㣬����һ����������,����������ԭ�����з����������ʱҪע��ԭ�����г������ǵ�һ���ڵ㻹���м������ڵ㣩��
3��������ԭ����������һ����С�ģ��ҵ�������������������βָ���next,Ȼ���������βָ��
 *-------------------------------------------------------------------------*/
STSList* st_slist_select_sort(STSList* head)
{
	STSList *first;	/*���к����������ı�ͷָ��*/
	STSList *tail; 	/*���к����������ı�βָ��*/ 
	STSList *p_min; /*������ֵ��С�Ľڵ��ǰ���ڵ��ָ��*/
	STSList *min; 	/*�洢��С�ڵ�*/ 
	STSList *p; 	/*��ǰ��ʱ�ȽϵĽڵ�*/

	first = NULL ;	/* ��ʼ������������Ϊ�� */

	while(NULL != head)
	{
		/*ע�⣺����for����������ѡ������˼��ĵط�*/
		/* ÿ�αȽ϶������ʣ��Ĵ���������ɨ��һ�飬���ԱȽϴ���Ϊ((n-1)*n)/2 */
		for(p=head, min=head ; p->next != NULL ; p=p->next)	/*ѭ�����������еĽڵ㣬�ҳ���ʱ��С�Ľڵ㡣*/
		{
			if(p->next->data < min->data)					/*�ҵ�һ���ȵ�ǰminС�Ľڵ㡣*/
			{
				p_min = p ;									/*�����ҵ��ڵ��ǰ���ڵ㣺��Ȼp->next��ǰ���ڵ���p��*/
				min = p->next ;								/*�����ֵ��С�Ľڵ㡣*/
			}	
		}
		/*����for�������󣬾�Ҫ�������£�һ�ǰ������������������У����Ǹ�����Ӧ�������жϣ��������뿪ԭ��������*/
		/*��һ���������С�Ľڵ㵽����������*/
		if(NULL == first)
		{
			first = min ;				/*��һ���ҵ���ֵ��С�Ľڵ㡣*/
			tail = min ;				/*ע�⣺βָ������ָ������һ���ڵ㡣*/
		}	
		else							/*�����������Ѿ��нڵ�*/
		{
			tail->next = min ;			/* ���µ���С�ڵ���ӵ���������β�� */
			tail = min ;				/* ������������β�ڵ�ָ�� */
		}

		/*�ڶ�����ɾ��ԭ����ڵ�*/
		if(min == head)					/*����ҵ�����С�ڵ���ǵ�һ���ڵ�*/
		{
			head = head->next ;			/* ֱ�Ӹ�����������ͷָ��Ϊhead->next */
		}
		else							/*������ǵ�һ���ڵ�*/
		{
			p_min->next = min->next ;	/*ǰ����С�ڵ��nextָ��ǰmin��next,��������min�뿪��ԭ����*/
		}
	}

	/*ѭ�������õ���������first*/
	if(NULL != first)
		tail->next = NULL ;				/*������������һ���ڵ��nextӦ��ָ��NULL*/ 

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
        if(pfast->data<phead->data)					//ÿ�ζ�ѡ������������ͷ�����Ϊ���ֵĻ�׼  
        {  
            ptemp=pslow;							//ptempʼ��Ϊpslow��ǰ�����  
            pslow=pslow->next;  
			//fprintf(stderr, "pslow->data %d, pfast->data %d\n", pslow->data, pfast->data);
            my_swap(&pslow->data,&pfast->data);		//pslowָ��ָ��Ȼ�׼С�Ľ����ɵ�����  
            //fprintf(stderr, "pslow->data %d, pfast->data %d\n", pslow->data, pfast->data);
        }  
        pfast=pfast->next;  
    }  
  
    my_swap(&pslow->data,&phead->data);				//��ʱpslowָ��ָ��Ȼ�׼С�Ľ����ɵ���������һ����㣬Ҳ���ǻ�׼��λ�ã�����Ҫ���׼��head��㣩����  
    
    st_slist_quick_sort(phead,ptemp);				//ptempΪ���������ַָ�㣨��׼����ǰһ�����  
    st_slist_quick_sort(pslow->next,pend);			//�Ҳ����ǱȻ�׼��Ľ����ɵ����� 	

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
        //ȡ��һ���ڵ���Ϊ�ȽϵĻ�׼��С�ڻ�׼����������������У�     
        //���ڻ�׼�����ұߵ���������     
        for (old = (*head)->next; old != end; old = old->next)  
        {     
            if (old->data < pivot->data)  
            {      
            	//С�ڻ�׼,���뵽�����������,�����Ƚ�     
                ++left_count;     
                *left_walk = old;            //�Ѹýڵ���뵽��ߵ������У�     
                left_walk = &(old->next);     
            }  
            else  
            {                         //���ڻ�׼,���뵽�ұߵ������������Ƚ�     
                ++right_count;     
                *right_walk = old;                
                right_walk = &(old->next);     
            }     
        }     
        //�ϲ�����     
        *right_walk = end;       //����������     
        *left_walk = pivot;      //�ѻ�׼������ȷ��λ����     
        pivot->next = right;     //������ϲ�     
        //�Խ�С����������п����򣬽ϴ����������е�������     
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




/*��ȡ�����еĽڵ���*/
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

 

/*��һ��ָ���ƶ�n��*/
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
	stint flag=0;		/*���һ�ο��ٲ�������Ƿ����*/
	STSList* h1;		/*h1������ͷ��ʼ����Ѱ�Ҳ���ڵ�*/
	STSList* h2;		/*h2����ָ����Ҫ����Ľ��*/
	STSList* h3;		/*h3����ָ��h2��ǰһ�����*/
	stint n=0;			/*�ڵ���*/
	stint t;			/*����ֵ*/
	
	n=getNodeNum(list);	/*�ڵ���*/

	for(t=n/2;t>0;t=t/2)/*ϣ��������ÿ����С����ֵ*/
	{
		h2=h3=list;		/*ÿ��ϣ����������ʼ��h2��h3��λ��*/
		move(&h3,t-1);
		move(&h2,t);	/*�ƶ�t��*/

		while(h2)		/*��������*/
		{
			h1=list;	/*��ʼ��h1��λ��*/
			flag=0;		/*flag��0*/
			while(flag==0)
			{
				if((h1->next->data) > (h2->data))/*����ҵ�������h2��ָ��Ľ��嵽h1���棬Ȼ������ѭ��*/
				{
					h3->next=h2->next;
					h2->next=h1->next;
					h1->next=h2;
					h2=h3->next;/*h2��ָ�ڵ��Ѿ��Ƶ�ǰ�棬h2Ҫ����ƶ�*/
					break; /*�����˴˴���break*/
				}
				/*�ƶ�h1*/
				for(i=0 ; i<t ; i++)
				{
					h1=h1->next;
					if((h1==h2)||(h1==NULL))
					{
						flag=1;/*h1�Ƶ���h2*/
						break;/*����ֹͣ�ƶ�����ָֹ��Խ��*/
					}
				}
			}

			if((flag==1)&&(h2!=NULL))/*ֻ��h2��ָ��㲻��Ҫǰ��ʱ���ƶ�h2��h3*/
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
 ���ܣ�ð������(��С����)
 ���أ�ָ�������ͷ��ָ��
==========================
ֱ�Ӳ�������Ļ���˼����ǶԵ�ǰ��δ�ź���ķ�Χ�ڵ�ȫ���ڵ㣬
 ���϶��¶����ڵ������ڵ����ν��бȽϺ͵������ü�ֵ������������
 ����ֶΣ�����ȡѧ��numΪ��ֵ���ϴ�Ľڵ����³�����ֵ��С����
 ��ð������ÿ�������ڵĽڵ�ȽϺ������ǵ�����������Ҫ���෴ʱ��
 �ͽ����ǻ�����

 
���������ð������ͼʾ��
---->[1]---->[3]---->[2]...---->[n]---->[NULL]��ԭ����
head   1->next  3->next  2->next   n->next 

---->[1]---->[2]---->[3]...---->[n]---->[NULL]�����������
head   1->next  2->next  3->next   n->next

ͼ14����N���ڵ������ð������

�����������ڽڵ�p��qλ�û���ͼʾ:
����p1->nextָ��p����ô��Ȼp1->next->next��ָ��q,
p1->next->next->next��ָ��q�ĺ�̽ڵ㣬������p2����
p1->next->nextָ�롣����p2=p1->next->next�����У�
[  ]---->[p]---------->[q]---->[  ]������ǰ��
  p1->next  p1->next->next  p2->next
ͼ15

[  ]---->[q]---------->[p]---->[  ]�������

ͼ16

1�������q�ڵ�ָ��p�ڵ㣬�ڵ���ָ��֮ǰ������Ҫ����ԭp��ָ��ڵ��ַ������p2=p1->next->next��
2��˳����һ��һ��������,�����ͼ16��p1->next->nextҪָ����p2->next,����p1->next->next=p2->next;
3����ͼ15��p2->nextԭ��q��������ָ�������ͼ16��q��ָ��Ҫ��Ϊָ��p�ģ���ԭ��p1->next��ָ��p�ģ�����p2->next=p1->next;
4����ͼ15��p1->nextԭ��ָ��p�ģ������ͼ16��p1->nextҪָ��q,ԭ��p1->next->next����p2)��ָ��q�ģ�����p1->next=p2;
5�����ˣ�����������������ڵ��˳�򽻻���
6������ĳ��������Ľ���һ����Ǽ�¼��ÿ�����һ�νڵ��³���λ�ã��������ǲ���ÿ�ζ���ͷ��β��ɨ�裬ֻ��Ҫɨ�赽��¼��Ϊֹ��
   ��Ϊ����Ķ��Ѿ����ź�����ˡ�
 *-------------------------------------------------------------------------*/
STSList* st_slist_bubble_sort(STSList* head)
{
	STSList *endpt; 	/*����ѭ���Ƚ�*/
	STSList *p; 		/*��ʱָ�����*/
	STSList *p1; 
	STSList *p2;

	p1 = (STSList *)malloc(sizeof(STSList));
 	p1->next = head;	/*ע����⣺��������һ���ڵ㣬���ڵ�һ���ڵ��ǰ�棬��Ҫ��Ϊ�˱��ڱȽϡ���Ϊ��һ���ڵ�û��ǰ�������ǲ��ܽ�����ַ��*/
 	head = p1;			/*��headָ��p1�ڵ㣬������ɺ������ٰ�p1�ڵ��ͷŵ�*/

	for (endpt=NULL; endpt!=head; endpt=p) /*��ϵ�6�����*/
	{
		for (p=p1=head; p1->next->next!=endpt; p1=p1->next)
		{
			if (p1->next->data > p1->next->next->data) /*���ǰ��Ľڵ��ֵ�Ⱥ���ڵ�ļ�ֵ���򽻻�*/
			{
				p2 = p1->next->next; 		/*��ϵ�1�����*/	/* ������������нڵ� */
				p1->next->next = p2->next;	/*��ϵ�2�����*/	/* �Ѻ����ڵ���ǰһλ */
				p2->next = p1->next; 		/*��ϵ�3�����*/	/* �ѽ����õĽڵ�����p2 */
				p1->next = p2; 				/*��ϵ�4�����*/	/* �ѽ����õĽڵ�����p1 */
				p = p1->next->next; 		/*��ϵ�6�����*/	/* ��¼��ÿ�����һ�νڵ��³���λ�� */
			}
		}
	}

	p1 = head; 			/*��p1����Ϣȥ��*/
	head = head->next; 	/*��headָ�������ĵ�һ���ڵ�*/
	free(p1); 			/*�ͷ�p1*/
	p1 = NULL; 			/*p1��ΪNULL����֤��������Ұָ�롱������ַ��ȷ����ָ�����*/

	return head;
}


STSList** DistributeL(STSList* p, int keyNum, STSList ** pa, stint NUM) 	//�������ݵķ���
{
	stint arr[10]= {0};	/*	��¼ͬһ��λ����ͬ���ĸ���	*/
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

STSList* CollectL(STSList* p, STSList ** pa, stint NUM)  		//�������ݵ��ռ�
{
	stint count;
	stint i = 0;
	STSList* pc;		/*	�洢pa[count]�ĳ�ʼֵ�����ͷſռ�ʱʹ��	*/
	STSList* pp = p;	/*	�洢p�ĳ�ʼֵ������ֵʱʹ��	*/

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


