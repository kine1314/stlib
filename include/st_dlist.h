#ifndef	__ST_DLIST_H__
#define	__ST_DLIST_H__

#include "stlib.h"

ST_BEGIN_DECLS;

typedef struct _STDLIST
{
	stpointer data ;
	struct _STDLIST *next ;
	struct _STDLIST *prev ;
}STDLIST ;

/* Doubly linked lists
 */
STDLIST*	st_dlist_alloc(void) ;
void		st_dlist_free1(STDLIST	*list);
void		st_dlist_free(STDLIST	*list);
STDLIST*	st_dlist_append(STDLIST		*list,	stpointer data);
STDLIST* 	st_dlist_prepend(STDLIST	*list,	stpointer data);
STDLIST*	st_dlist_insert(STDLIST		*list,	stpointer data,	stint position);
STDLIST*	st_dlist_insert_sorted(STDLIST		*list,
								  stpointer		data,
								  STCompareFunc	func);
STDLIST*	st_dlist_insert_before(STDLIST	*list,
					 			  STDLIST	*sibling,
					 			  stpointer	data);
STDLIST*	st_dlist_concat(STDLIST		*list1, STDLIST			*list2);
STDLIST*  	st_dlist_remove(STDLIST		*list, stconstpointer	data) ;
STDLIST*  	st_dlist_remove_all(STDLIST	*list, stconstpointer	data) ;
STDLIST*	st_dlist_remove_link(STDLIST	*list, STDLIST *link_) ;
STDLIST* 	st_dlist_delete_link(STDLIST	*list, STDLIST *link_) ;
STDLIST*  	st_dlist_reverse(STDLIST	*list) ;
STDLIST*  	st_dlist_copy(STDLIST		*list) ;
STDLIST*  	st_dlist_nth(STDLIST 		*list, stuint n);
STDLIST*  	st_dlist_nth_prev(STDLIST 	*list, stuint n);
stpointer 	st_dlist_nth_data(STDLIST	*list, stuint n);
STDLIST*  	st_dlist_find(STDLIST *list, stconstpointer data);
STDLIST*   	st_dlist_find_custom(STDLIST	*list,
 							stconstpointer	data,
 							STCompareFunc	func);
stint     	st_dlist_position(STDLIST	*list, STDLIST *llink);
stint     	st_dlist_index(STDLIST		*list,
					 stconstpointer     data);
STDLIST*  	st_dlist_first(STDLIST		*list);
STDLIST*  	st_dlist_last(STDLIST		*list);
stuint    	st_dlist_length(STDLIST		*list);
void     	st_dlist_foreach(STDLIST 	*list,
					  STFunc			func,
					  stpointer			user_data);
STDLIST*  	st_dlist_sort(STDLIST		*list,
					  STCompareFunc		compare_func) ;
STDLIST*  	st_dlist_sort_with_data(STDLIST	*list,
					  STCompareDataFunc		compare_func,
					  stpointer				user_data) ;


#define 	st_dlist_previous(list)			((list) ? (((GList *)(list))->prev) : NULL)
#define 	st_dlist_next(list)				((list) ? (((GList *)(list))->next) : NULL)

ST_END_DECLS;	/* __cplusplus */
#endif	/* __ST_DLIST_H__ */


