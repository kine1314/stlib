#ifndef	__ST_DRLIST_H__
#define	__ST_DRLIST_H__

#include "stlib.h"

ST_BEGIN_DECLS;		/* __cplusplus */


/*保证不在链表中的节点项不可访问*/
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

/* 定义一个已经初始化的表头，其prev和next都是指向自己 */
#define ST_LIST_HEAD_INIT(name) { &(name), &(name) }
#define ST_LIST_HEAD(name) 										\
		st_list_head name = ST_LIST_HEAD_INIT(name)			// name = {.prev = name, .next = name} ;

/* 动态初始化一个已经存在的list_head对象，ptr为一个结构体的指针，
 * 这样可以初始化堆栈以及全局区定义的list_head对象。
 */
/*将list_head做初始化的，它的初始化就是将next和prev这两个栏位设为跟结构的地址相同*/
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
 * 在表头插入是插入在head之后
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
 * 而在表尾插入是插入在head->prev之后
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
 * 删除entry所指向的结点，同时调用LIST_INIT_HEAD()把被删除节点为作为链表头构建一个新的空双循环链表。
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
 * 将list结点前后两个结点互相指向彼此，
 * 删除list指针所指向的结点，再将此结点插入head，
 * 和head->next两个指针所指向的结点之间。
 * 即：将list所指向的结点移动到head所指向的结点的后面。
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
 * 删除了list所指向的结点，将其插入到head所指向的结点的前面，
 * 如果head->prev指向链表的尾结点的话，
 * 就是将list所指向的结点插入到链表的结尾。
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
/* 如果要检查这个list是否是空的， 只要检查hello.next是否等于&hello就可以了*/
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
 * 这主要是为了应付另一个cpu正在处理同一个链表而造成next、prev不一致的情况。
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
 * list 挂接在head的后面
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
 * list挂接在head的前面
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
 * 从pos节点开始遍历，直到pos == head，则遍历结束
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
 * 从pos节点开始向前遍历，直到pos == head 结束 ；
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
 * 与list_for_each()不同，这里的pos是数据项结构指针类型，而不是(struct list_head *)。
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
 * 经过一系列计算后，如果pos有值，则从pos开始遍历，如果没有，则从链表头开始，
 * 为此，Linux专门提供了一个list_prepare_entry(pos,head,member)宏，
 * 将它的返回值作为list_for_each_entry_continue()的pos参数，就可以满足这一要求。
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
 * 如果遍历不是从链表头开始，而是从已知的某个节点pos开始，
 * 则可以使用list_for_each_entry_continue(pos,head,member)
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
 * 与pos同类型的指针n，在for循环中暂存pos下一个节点的地址，避免因pos节点被释放而造成的断链。
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
/*哈希链表结构*/
/** 
 * 认为双头（next、prev）的双链表对于HASH表来说"过于浪费"，
 * 因而另行设计了一套用于HASH表应用的hlist数据结构--单指针表头双循环链表，
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

