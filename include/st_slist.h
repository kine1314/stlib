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
// 删除第一个data的节点 
STSList*  st_slist_remove(STSList *list, stconstpointer data) ;		
// 删除所有data节点
STSList*  st_slist_remove_all(STSList *list, stconstpointer data) ;
// 只断开连接，不释放内存
STSList*  st_slist_remove_link(STSList *list, STSList *link_) ;
// 断开连接并释放内存
STSList*  st_slist_delete_link(STSList *list, STSList *link_) ;
// 单链表的逆序
STSList*  st_slist_reverse(STSList *list);
// 复制链表的一个拷贝出来
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
   排序算法					最好时间	平均时间	最坏时间	辅助空间	稳定性

   直接插入排序				O(n)		O(n^2)		O(n^2)		O(1)		稳定
   希尔排序								O(n^1.3)				O(1)		不稳定

   直接选择排序				O(n^2)		O(n^2)		O(n^2)		O(1)		不稳定
   堆排序					O(n x lbn)	O(n x lbn)	O(n x lbn)	O(1)		不稳定

   冒泡排序					O(n)		O(n^2)		O(n^2)		O(1)		稳定
   快速排序					O(n x lbn)	O(n x lbn)	O(n x lbn)	O(lbn)		不稳定

   归并排序					O(n x lbn)	O(n x lbn)	O(n x lbn)	O(n)		不稳定

   基数排序(基于链式队列)	O(mxn)		O(mxn)		O(mxn)		O(n)		稳定
   基数排序(基于顺序队列)	O(mxn)		O(mxn)		O(mxn)		O(mxn)		稳定
 */
/*
: 排序算法小结：
: 稳定排序：直接插入法，冒泡法，归并排序，基数排序；
: 元素较少时:直接插入排序，直接选择排序；
: 元素较多时：快速排序，堆排序，归并排序；
: 元素基本有序：直接插入排序，冒泡排序，快速排序；
: 关键字随即分布：基数排序；
: 有益于链表：插入排序，归并排序，基数排序；
: 不利于链表：快速排序，堆排序；
*/
/*
 * 直接插入排序和折半插入，对于数组，由于移动次数是不变的，
 * 因此折半插入时间依然是O（n^2）。而链表插入排序则是省去
 * 了移动过程，链表（单链表）实际不属于顺序存储结构，因此链表也不存在折半的方法。
 * 或者不适合二分查找；
 */
STSList* st_slist_direct_insert_sort(STSList* list);		
STSList* st_slist_select_sort(STSList* list);
void st_slist_shell_sort(STSList* list);
STSList* st_slist_quick_sort(STSList* phead, STSList *pend);
void st_slist_quick_sort2(STSList **head, STSList *end);
STSList* st_slist_iteration_merge_sort(STSList* list);			// 迭代实现单链表归并排序
STSList* st_slist_bubble_sort(STSList* list);
//STSList* st_slist_head_sort(STSList* list);					// 链表不适合堆排序
/*锦标赛排序，树形选择排序*/
/* 基数排序，桶排序 */
STSList* st_slist_radix_sort(STSList* list, stint radix);
/* 外排序 */


#define  st_slist_next(slist)	         ((slist) ? (((STSList *)(slist))->next) : NULL)

ST_END_DECLS;	/* __cplusplus */

#endif	/* __ST_SLIST_H__ */

