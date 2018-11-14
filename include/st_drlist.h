#ifndef	__ST_DRLIST_H__
#define	__ST_DRLIST_H__

#include "stlib.h"

ST_BEGIN_DECLS;		/* __cplusplus */


/*��֤���������еĽڵ���ɷ���*/
#define ST_LIST_POISON1  ((void *) 0x00100100)
#define ST_LIST_POISON2  ((void *) 0x00200200)

typedef struct _st_list_head 
{
	struct _st_list_head *next;
	struct _st_list_head *prev;
}st_list_head;

typedef struct _st_hlist_node
{
	struct _st_hlist_node *next;
	struct _st_hlist_node **pprev;
}st_hlist_node ;

typedef struct _st_hlist_head
{
	struct _st_hlist_node *first;
}st_hlist_head ;

/* ����һ���Ѿ���ʼ���ı�ͷ����prev��next����ָ���Լ� */
#define ST_LIST_HEAD_INIT(name) { &(name), &(name) }
#define ST_LIST_HEAD(name) 										\
		st_list_head name = ST_LIST_HEAD_INIT(name)			// name = {.prev = name, .next = name} ;

/* ��̬��ʼ��һ���Ѿ����ڵ�list_head����ptrΪһ���ṹ���ָ�룬
 * �������Գ�ʼ����ջ�Լ�ȫ���������list_head����
 */
/*��list_head����ʼ���ģ����ĳ�ʼ�����ǽ�next��prev��������λ��Ϊ���ṹ�ĵ�ַ��ͬ*/
static stinline void ST_INIT_LIST_HEAD(st_list_head *list)
{
       list->next = list;
       list->prev = list;
}

/*
 * Insert a new entry between two known consecutive entries.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static stinline void __st_list_add(st_list_head *new, 
 							  st_list_head *prev,  
 							  st_list_head *next)
{
       next->prev = new;
       new->next = next;
       new->prev = prev;
       prev->next = new;
}

/**
 * st_list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 * �ڱ�ͷ�����ǲ�����head֮��
 */
static stinline void st_list_add(st_list_head *new, st_list_head *head)
{
       __st_list_add(new, head, head->next);
}

/**
 * st_list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 * ���ڱ�β�����ǲ�����head->prev֮��
 */
static stinline void st_list_add_tail(st_list_head *new, st_list_head *head)
{
       __st_list_add(new, head->prev, head);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static stinline void __st_list_del(st_list_head * prev, st_list_head * next)
{
       next->prev = prev;
       prev->next = next;
}

/**
 * __st_list_del_entry - deletes entry from list.
 * @entry: the element to delete from the list.
 * Note: list_empty() on entry does not return true after this, the entry is
 * in an undefined state.
 */
static stinline void __st_list_del_entry(st_list_head *entry)
{
        __st_list_del(entry->prev, entry->next);
}

static stinline void st_list_del(st_list_head *entry)
{
        __st_list_del(entry->prev, entry->next);
        entry->next = ST_LIST_POISON1;
        entry->prev = ST_LIST_POISON2;
}

/**
 * st_list_replace - replace old entry by new one
 * @old : the element to be replaced
 * @new : the new element to insert
 *
 * If @old was empty, it will be overwritten.
 */
static stinline void st_list_replace(st_list_head *old,
                                st_list_head *new)
{
        new->next = old->next;
        new->next->prev = new;
        new->prev = old->prev;
        new->prev->next = new;
}

static stinline void st_list_replace_init(st_list_head *old,
					st_list_head *new)
{
	st_list_replace(old, new);
	ST_INIT_LIST_HEAD(old);
}



/**
 * st_list_del_init - deletes entry from list and reinitialize it.
 * @entry: the element to delete from the list.
 * ɾ��entry��ָ��Ľ�㣬ͬʱ����LIST_INIT_HEAD()�ѱ�ɾ���ڵ�Ϊ��Ϊ����ͷ����һ���µĿ�˫ѭ������
 */
static stinline void st_list_del_init(st_list_head *entry)
{
	__st_list_del_entry(entry);
	ST_INIT_LIST_HEAD(entry);
}



/**
 * st_list_move - delete from one list and add as another's head
 * @list: the entry to move
 * @head: the head that will precede our entry
 * ��list���ǰ��������㻥��ָ��˴ˣ�
 * ɾ��listָ����ָ��Ľ�㣬�ٽ��˽�����head��
 * ��head->next����ָ����ָ��Ľ��֮�䡣
 * ������list��ָ��Ľ���ƶ���head��ָ��Ľ��ĺ��档
 */
static stinline void st_list_move(st_list_head *list, st_list_head *head)
{
	__st_list_del_entry(list);
	st_list_add(list, head);
}



/**
 * list_move_tail - delete from one list and add as another's tail
 * @list: the entry to move
 * @head: the head that will follow our entry
 * ɾ����list��ָ��Ľ�㣬������뵽head��ָ��Ľ���ǰ�棬
 * ���head->prevָ�������β���Ļ���
 * ���ǽ�list��ָ��Ľ����뵽����Ľ�β��
 */
static stinline void st_list_move_tail(st_list_head *list,
				  st_list_head *head)
{
	__st_list_del_entry(list);
	st_list_add_tail(list, head);
}

/**
 * st_list_is_last - tests whether @list is the last entry in list @head
 * @list: the entry to test
 * @head: the head of the list
 */
static stinline stint st_list_is_last(const st_list_head *list,
				const st_list_head *head)
{
	return list->next == head;
}

/**
 * st_list_empty - tests whether a list is empty
 * @head: the list to test.
 */
/* ���Ҫ������list�Ƿ��ǿյģ� ֻҪ���hello.next�Ƿ����&hello�Ϳ�����*/
static stinline stint st_list_empty(const st_list_head *head)
{
	return head->next == head;
}

/**
 * st_list_empty_careful - tests whether a list is empty and not being modified
 * @head: the list to test
 *
 * Description:
 * tests whether a list is empty _and_ checks that no other CPU might be
 * in the process of modifying either member (next or prev)
 *
 * NOTE: using st_list_empty_careful() without synchronization
 * can only be safe if the only activity that can happen
 * to the list entry is list_del_init(). Eg. it cannot be used
 * if another CPU could re-list_add() it.
 * ����Ҫ��Ϊ��Ӧ����һ��cpu���ڴ���ͬһ����������next��prev��һ�µ������
 */
static stinline stint st_list_empty_careful(const st_list_head *head)
{
	st_list_head *next = head->next;
	return (next == head) && (next == head->prev);
}

/**
 * st_list_rotate_left - rotate the list to the left
 * @head: the head of the list
 */
static stinline void st_list_rotate_left(st_list_head *head)
{
	st_list_head *first;

	if (!st_list_empty(head)) {
		first = head->next;
		st_list_move_tail(first, head);
	}
}

/**
 * st_list_is_singular - tests whether a list has just one entry.
 * @head: the list to test.
 */
static stinline stint st_list_is_singular(const st_list_head *head)
{
	return !st_list_empty(head) && (head->next == head->prev);
}

static stinline void __st_list_cut_position(st_list_head *list,
					st_list_head *head, st_list_head *entry)
{
	st_list_head *new_first = entry->next;
	list->next = head->next;
	list->next->prev = list;
	list->prev = entry;
	entry->next = list;
	head->next = new_first;
	new_first->prev = head;
}

/**
 * st_list_cut_position - cut a list into two
 * @list: a new list to add all removed entries
 * @head: a list with entries
 * @entry: an entry within head, could be the head itself
 *	and if so we won't cut the list
 *
 * This helper moves the initial part of @head, up to and
 * including @entry, from @head to @list. You should
 * pass on @entry an element you know is on @head. @list
 * should be an empty list or a list you do not care about
 * losing its data.
 *
 */
static stinline void st_list_cut_position(st_list_head *list,
				st_list_head *head, st_list_head *entry)
{
	if (st_list_empty(head))
		return;
	if (st_list_is_singular(head) &&
		(head->next != entry && head != entry))
		return;
	if (entry == head)
		ST_INIT_LIST_HEAD(list);
	else
		__st_list_cut_position(list, head, entry);
}

static stinline void __st_list_splice(const st_list_head *list,
				 					st_list_head *prev,
				 					st_list_head *next)
{
	st_list_head *first = list->next;
	st_list_head *last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
}

/**
 * st_list_splice - join two lists, this is designed for stacks
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 * list �ҽ���head�ĺ���
 */
static stinline void st_list_splice(const st_list_head *list,
							st_list_head *head)
{
	if (!st_list_empty(list))
		__st_list_splice(list, head, head->next);
}

/**
 * st_list_splice_tail - join two lists, each list being a queue
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 * list�ҽ���head��ǰ��
 */
static stinline void st_list_splice_tail(st_list_head *list,
									st_list_head *head)
{
	if (!st_list_empty(list))
		__st_list_splice(list, head->prev, head);
}

/**
 * st_list_splice_init - join two lists and reinitialise the emptied list.
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * The list at @list is reinitialised
 */
static stinline void st_list_splice_init(st_list_head *list,
				    				st_list_head *head)
{
	if (!st_list_empty(list)) {
		__st_list_splice(list, head, head->next);
		ST_INIT_LIST_HEAD(list);
	}
}

/**
 * st_list_splice_tail_init - join two lists and reinitialise the emptied list
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 *
 * Each of the lists is a queue.
 * The list at @list is reinitialised
 */
static stinline void st_list_splice_tail_init(st_list_head *list,
					 						st_list_head *head)
{
	if (!st_list_empty(list)) {
		__st_list_splice(list, head->prev, head);
		ST_INIT_LIST_HEAD(list);
	}
}



/**
 * st_list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define st_list_entry(ptr, type, member) 									\
	st_container_of(ptr, type, member)

/**
 * st_list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define st_list_first_entry(ptr, type, member) 								\
	st_list_entry((ptr)->next, type, member)


/**
 * st_list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 * ��pos�ڵ㿪ʼ������ֱ��pos == head�����������
 */
#define st_list_for_each(pos, head) 										\
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * __st_list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 *
 * This variant doesn't differ from list_for_each() any more.
 * We don't do prefetching in either case.
 */
#define __st_list_for_each(pos, head) 										\
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * st_list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 * ��pos�ڵ㿪ʼ��ǰ������ֱ��pos == head ���� ��
 */
#define st_list_for_each_prev(pos, head) 									\
	for (pos = (head)->prev; pos != (head); pos = pos->prev)

/**
 * st_list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop cursor.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define st_list_for_each_safe(pos, n, head) 								\
	for (pos = (head)->next, n = pos->next; pos != (head); 					\
		pos = n, n = pos->next)

/**
 * st_list_for_each_prev_safe - iterate over a list backwards safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop cursor.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define st_list_for_each_prev_safe(pos, n, head) 							\
	for (pos = (head)->prev, n = pos->prev; 								\
	     pos != (head); 													\
	     pos = n, n = pos->prev)

/**
 * st_list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 * ��list_for_each()��ͬ�������pos��������ṹָ�����ͣ�������(struct list_head *)��
 */
#define st_list_for_each_entry(pos, head, member)							\
	for (pos = st_list_entry((head)->next, typeof(*pos), member);			\
	     &pos->member != (head); 											\
	     pos = st_list_entry(pos->member.next, typeof(*pos), member))
	
/**
 * st_list_for_each_entry_reverse - iterate backwards over list of given type.
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define st_list_for_each_entry_reverse(pos, head, member)					\
	for (pos = st_list_entry((head)->prev, typeof(*pos), member);			\
	     &pos->member != (head); 											\
	     pos = st_list_entry(pos->member.prev, typeof(*pos), member))

/**
 * st_list_prepare_entry - prepare a pos entry for use in list_for_each_entry_continue()
 * @pos:	the type * to use as a start point
 * @head:	the head of the list
 * @member:	the name of the list_struct within the struct.
 *
 * Prepares a pos entry for use as a start point in list_for_each_entry_continue().
 * ����һϵ�м�������pos��ֵ�����pos��ʼ���������û�У��������ͷ��ʼ��
 * Ϊ�ˣ�Linuxר���ṩ��һ��list_prepare_entry(pos,head,member)�꣬
 * �����ķ���ֵ��Ϊlist_for_each_entry_continue()��pos�������Ϳ���������һҪ��
 */
#define st_list_prepare_entry(pos, head, member) 							\
	((pos) ? : st_list_entry(head, typeof(*pos), member))	

/**
 * st_list_for_each_entry_continue - continue iteration over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 *
 * Continue to iterate over list of given type, continuing after
 * the current position.
 * ����������Ǵ�����ͷ��ʼ�����Ǵ���֪��ĳ���ڵ�pos��ʼ��
 * �����ʹ��list_for_each_entry_continue(pos,head,member)
 */
#define st_list_for_each_entry_continue(pos, head, member) 					\
	for (pos = st_list_entry(pos->member.next, typeof(*pos), member);		\
	     &pos->member != (head);											\
	     pos = st_list_entry(pos->member.next, typeof(*pos), member))

/**
 * st_list_for_each_entry_continue_reverse - iterate backwards from the given point
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 *
 * Start to iterate over list of given type backwards, continuing after
 * the current position.
 */
#define st_list_for_each_entry_continue_reverse(pos, head, member)			\
	for (pos = st_list_entry(pos->member.prev, typeof(*pos), member);		\
	     &pos->member != (head);											\
	     pos = st_list_entry(pos->member.prev, typeof(*pos), member))

/**
 * st_list_for_each_entry_from - iterate over list of given type from the current point
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 *
 * Iterate over list of given type, continuing from current position.
 */
#define st_list_for_each_entry_from(pos, head, member) 						\
	for (; &pos->member != (head);											\
	     pos = st_list_entry(pos->member.next, typeof(*pos), member))

/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 * ��posͬ���͵�ָ��n����forѭ�����ݴ�pos��һ���ڵ�ĵ�ַ��������pos�ڵ㱻�ͷŶ���ɵĶ�����
 */
#define st_list_for_each_entry_safe(pos, n, head, member)					\
	for (pos = st_list_entry((head)->next, typeof(*pos), member),			\
		n = st_list_entry(pos->member.next, typeof(*pos), member);			\
	     &pos->member != (head); 											\
	     pos = n, n = st_list_entry(n->member.next, typeof(*n), member))

/**
 * st_list_for_each_entry_safe_continue - continue list iteration safe against removal
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 *
 * Iterate over list of given type, continuing after current point,
 * safe against removal of list entry.
 */
#define st_list_for_each_entry_safe_continue(pos, n, head, member) 			\
	for (pos = st_list_entry(pos->member.next, typeof(*pos), member), 		\
		n = st_list_entry(pos->member.next, typeof(*pos), member);			\
	     &pos->member != (head);											\
	     pos = n, n = st_list_entry(n->member.next, typeof(*n), member))

/**
 * st_list_for_each_entry_safe_from - iterate over list from current point safe against removal
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 *
 * Iterate over list of given type from current point, safe against
 * removal of list entry.
 */
#define st_list_for_each_entry_safe_from(pos, n, head, member) 				\
	for (n = st_list_entry(pos->member.next, typeof(*pos), member);			\
	     &pos->member != (head);											\
	     pos = n, n = st_list_entry(n->member.next, typeof(*n), member))

/**
 * st_list_for_each_entry_safe_reverse - iterate backwards over list safe against removal
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 *
 * Iterate backwards over list of given type, safe against removal
 * of list entry.
 */
#define st_list_for_each_entry_safe_reverse(pos, n, head, member)			\
	for (pos = st_list_entry((head)->prev, typeof(*pos), member),			\
		n = st_list_entry(pos->member.prev, typeof(*pos), member);			\
	     &pos->member != (head); 											\
	     pos = n, n = st_list_entry(n->member.prev, typeof(*n), member))

/**
 * st_list_safe_reset_next - reset a stale list_for_each_entry_safe loop
 * @pos:	the loop cursor used in the list_for_each_entry_safe loop
 * @n:		temporary storage used in list_for_each_entry_safe
 * @member:	the name of the list_struct within the struct.
 *
 * st_list_safe_reset_next is not safe to use in general if the list may be
 * modified concurrently (eg. the lock is dropped in the loop body). An
 * exception to this is if the cursor element (pos) is pinned in the list,
 * and st_list_safe_reset_next is called after re-taking the lock and before
 * completing the current iteration of the loop body.
 */
#define st_list_safe_reset_next(pos, n, member)								\
	n = st_list_entry(pos->member.next, typeof(*pos), member)


/*
 * Double linked lists with a single pointer list head.
 * Mostly useful for hash tables where the two pointer list head is
 * too wasteful.
 * You lose the ability to access the tail in O(1).
 */
/*��ϣ����ṹ*/
/** 
 * ��Ϊ˫ͷ��next��prev����˫�������HASH����˵"�����˷�"��
 * ������������һ������HASH��Ӧ�õ�hlist���ݽṹ--��ָ���ͷ˫ѭ������
 */
#define ST_HLIST_HEAD_INIT { .first = NULL }
#define ST_HLIST_HEAD(name) st_hlist_head name = {  .first = NULL }
#define ST_INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)
static  void ST_INIT_HLIST_NODE(st_hlist_node *h)
{
	h->next = ST_LIST_POISON1;
	h->pprev = ST_LIST_POISON2;
}

static stinline stint st_hlist_unhashed(const st_hlist_node *h)
{
	return !h->pprev;
}

static stinline stint st_hlist_empty(const st_hlist_head *h)
{
	return !h->first;
}

static stinline void __st_hlist_del(st_hlist_node *n)
{
	st_hlist_node *next = n->next;
	st_hlist_node **pprev = n->pprev;
	*pprev = next;
	if (next)
		next->pprev = pprev;
}

static stinline void hlist_del(st_hlist_node *n)
{
	__st_hlist_del(n);
	n->next = ST_LIST_POISON1;
	n->pprev = ST_LIST_POISON2;
}

static stinline void st_hlist_del_init(st_hlist_node *n)
{
	if (!st_hlist_unhashed(n)) {
		__st_hlist_del(n);
		ST_INIT_HLIST_NODE(n);
	}
}

static stinline void st_hlist_add_head(st_hlist_node *n, st_hlist_head *h)
{
	st_hlist_node *first = h->first;
	n->next = first;
	if (first)
		first->pprev = &n->next;
	h->first = n;
	n->pprev = &h->first;
}

/* next must be != NULL */
static stinline void st_hlist_add_before(st_hlist_node *n,
					st_hlist_node *next)
{
	n->pprev = next->pprev;
	n->next = next;
	next->pprev = &n->next;
	*(n->pprev) = n;
}

static stinline void st_hlist_add_after(st_hlist_node *n,
					st_hlist_node *next)
{
	next->next = n->next;
	n->next = next;
	next->pprev = &n->next;

	if(next->next)
		next->next->pprev  = &next->next;
}

/* after that we'll appear to be on some hlist and hlist_del will work */
static stinline void st_hlist_add_fake(st_hlist_node *n)
{
	n->pprev = &n->next;
}

/*
 * Move a list from one list head to another. Fixup the pprev
 * reference of the first entry if it exists.
 */
static stinline void st_hlist_move_list(st_hlist_head *old,
				   st_hlist_head *new)
{
	new->first = old->first;
	if (new->first)
		new->first->pprev = &new->first;
	old->first = NULL;
}

#define st_hlist_entry(ptr, type, member) st_container_of(ptr,type,member)

#define st_hlist_for_each(pos, head) \
	for (pos = (head)->first; pos ; pos = pos->next)

#define st_hlist_for_each_safe(pos, n, head) \
	for (pos = (head)->first; pos && ({ n = pos->next; 1; }); \
	     pos = n)

/**
 * st_hlist_for_each_entry	- iterate over list of given type
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &struct hlist_node to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the hlist_node within the struct.
 */
#define st_hlist_for_each_entry(tpos, pos, head, member)			 \
	for (pos = (head)->first;					 \
	     pos &&							 \
		({ tpos = st_hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = pos->next)

/**
 * st_hlist_for_each_entry_continue - iterate over a hlist continuing after current point
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &struct hlist_node to use as a loop cursor.
 * @member:	the name of the hlist_node within the struct.
 */
#define st_hlist_for_each_entry_continue(tpos, pos, member)		 \
	for (pos = (pos)->next;						 \
	     pos &&							 \
		({ tpos = st_hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = pos->next)

/**
 * st_hlist_for_each_entry_from - iterate over a hlist continuing from current point
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &struct hlist_node to use as a loop cursor.
 * @member:	the name of the hlist_node within the struct.
 */
#define st_hlist_for_each_entry_from(tpos, pos, member)			 \
	for (; pos &&							 \
		({ tpos = st_hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = pos->next)

/**
 * st_hlist_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @tpos:	the type * to use as a loop cursor.
 * @pos:	the &struct hlist_node to use as a loop cursor.
 * @n:		another &struct hlist_node to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the hlist_node within the struct.
 */
#define st_hlist_for_each_entry_safe(tpos, pos, n, head, member) 		 \
	for (pos = (head)->first;					 \
	     pos && ({ n = pos->next; 1; }) && 				 \
		({ tpos = st_hlist_entry(pos, typeof(*tpos), member); 1;}); \
	     pos = n)


	


ST_END_DECLS;	/* __cplusplus */
#endif	/* __ST_DRLIST_H__ */

