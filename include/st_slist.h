#ifndef	__ST_SLIST_H__
#define	__ST_SLIST_H__

#include "stlib.h"

ST_BEGIN_DECLS;	/* __cplusplus */



typedef struct _STSList
{
	void	*data ;
	struct	_STSList *next ;
}STSList ;

/* Singly linked lists
 */



STSList *st_slist_alloc(void);
void st_slist_free(STSList *list);
STSList*  st_slist_append(STSList *list, stpointer data);
STSList*  st_slist_prepend(STSList *list, stpointer data);
STSList*  st_slist_insert(STSList *list, stpointer data, stint position);
STSList*  st_slist_insert_sorted(STSList *list,
								  stpointer			data,
								  STCompareFunc		func);

STSList*  st_slist_insert_sorted_with_data (STSList *list,
								  stpointer          data,
								  STCompareDataFunc  func,
								  stpointer          user_data);

STSList*  st_slist_concat(STSList *list1, STSList *list2);
// ɾ����һ��data�Ľڵ� 
STSList*  st_slist_remove(STSList *list, stconstpointer data) ;		
// ɾ������data�ڵ�
STSList*  st_slist_remove_all(STSList *list, stconstpointer data) ;
// ֻ�Ͽ����ӣ����ͷ��ڴ�
STSList*  st_slist_remove_link(STSList *list, STSList *link_) ;
// �Ͽ����Ӳ��ͷ��ڴ�
STSList*  st_slist_delete_link(STSList *list, STSList *link_) ;
// �����������
STSList*  st_slist_reverse(STSList *list);
// ���������һ����������
STSList*  st_slist_copy(STSList *list) ;
STSList*  st_slist_nth(STSList *list, stuint n);
STSList*  st_slist_find(STSList *list, stconstpointer data);
stint     st_slist_position(STSList *list, STSList *llink);
STSList*  st_slist_last(STSList *list);
stuint    st_slist_length(STSList *list);
void     st_slist_foreach(STSList *list,
					  STFunc	func,
					  stpointer	user_data);
STSList*  st_slist_sort(STSList		*list,
					  STCompareFunc	compare_func) ;
STSList*  st_slist_sort_with_data(STSList	*list,
					  STCompareDataFunc		compare_func,
					  stpointer				user_data) ;
STSList*  st_slist_merge_2_list(STSList	*list1, STSList	*list2);				
STSList*  st_slist_recursive_merge_2_list(STSList	*list1, STSList	*list2);
stpointer st_slist_nth_data(STSList	*list, stuint n);
void st_dump_list(STSList *head);							


//////////////sort list//////////////////
/*
   �����㷨					���ʱ��	ƽ��ʱ��	�ʱ��	�����ռ�	�ȶ���

   ֱ�Ӳ�������				O(n)		O(n^2)		O(n^2)		O(1)		�ȶ�
   ϣ������								O(n^1.3)				O(1)		���ȶ�

   ֱ��ѡ������				O(n^2)		O(n^2)		O(n^2)		O(1)		���ȶ�
   ������					O(n x lbn)	O(n x lbn)	O(n x lbn)	O(1)		���ȶ�

   ð������					O(n)		O(n^2)		O(n^2)		O(1)		�ȶ�
   ��������					O(n x lbn)	O(n x lbn)	O(n x lbn)	O(lbn)		���ȶ�

   �鲢����					O(n x lbn)	O(n x lbn)	O(n x lbn)	O(n)		���ȶ�

   ��������(������ʽ����)	O(mxn)		O(mxn)		O(mxn)		O(n)		�ȶ�
   ��������(����˳�����)	O(mxn)		O(mxn)		O(mxn)		O(mxn)		�ȶ�
 */
/*
: �����㷨С�᣺
: �ȶ�����ֱ�Ӳ��뷨��ð�ݷ����鲢���򣬻�������
: Ԫ�ؽ���ʱ:ֱ�Ӳ�������ֱ��ѡ������
: Ԫ�ؽ϶�ʱ���������򣬶����򣬹鲢����
: Ԫ�ػ�������ֱ�Ӳ�������ð�����򣬿�������
: �ؼ����漴�ֲ�����������
: �����������������򣬹鲢���򣬻�������
: �����������������򣬶�����
*/
/*
 * ֱ�Ӳ���������۰���룬�������飬�����ƶ������ǲ���ģ�
 * ����۰����ʱ����Ȼ��O��n^2���������������������ʡȥ
 * ���ƶ����̣�����������ʵ�ʲ�����˳��洢�ṹ���������Ҳ�������۰�ķ�����
 * ���߲��ʺ϶��ֲ��ң�
 */
STSList* st_slist_direct_insert_sort(STSList* list);		
STSList* st_slist_select_sort(STSList* list);
void st_slist_shell_sort(STSList* list);
STSList* st_slist_quick_sort(STSList* phead, STSList *pend);
void st_slist_quick_sort2(STSList **head, STSList *end);
STSList* st_slist_iteration_merge_sort(STSList* list);			// ����ʵ�ֵ�����鲢����
STSList* st_slist_bubble_sort(STSList* list);
//STSList* st_slist_head_sort(STSList* list);					// �����ʺ϶�����
/*��������������ѡ������*/
/* ��������Ͱ���� */
STSList* st_slist_radix_sort(STSList* list, stint radix);
/* ������ */


#define  st_slist_next(slist)	         ((slist) ? (((STSList *)(slist))->next) : NULL)

ST_END_DECLS;	/* __cplusplus */

#endif	/* __ST_SLIST_H__ */

