#ifndef	__ST_RBTREE_LK_H__
#define	__ST_RBTREE_LK_H__
#include "stlib.h"
ST_BEGIN_DECLS;

/**
 * 红黑树是平衡二叉树的一种，它有很好的性质，树中的结点都是有序的，而且因为它本身就是
 * 平衡的，所以查找也不会出现非常恶劣的情况，基于二叉树的操作的时间复杂度是O(log(N))。
 * Linux内核在管理vm_area_struct时就是采用了红黑树来维护内存块的。
 **/

struct _rb_node
{
	unsigned long  rb_parent_color;				// TODO:父亲节点的颜色
#define	RB_RED		0
#define	RB_BLACK	1
	struct _rb_node *rb_right;
	struct _rb_node *rb_left;
}
#if !defined(WIN32)
__attribute__((aligned(sizeof(long))))		/* aligned with long */
#endif
;
    /* The alignment might seem pointless, but allegedly CRIS needs it */

/**
 * struct rb_root只是struct _rb_node*的一个包装，这样做的好处是看起来不用
 * 传递二级指针了。不错，很简单。再看一下下面几个重要的宏，细心的你一定会发现，
 * rb_parent_color其实没那么简单，Andrea Arcangeli在这里使用了一个小的技
 * 巧，不过非常棒。正如名字所暗示，这个成员其实包含指向parent的指针和此结点的
 * 颜色！它是怎么做到的呢？很简单，对齐起了作用。既然是sizeof(long)大小的对齐，
 * 那么在IA-32上，任何rb_node结构体的地址的低两位肯定都是零，与其空着不用，
 * 还不如用它们表示颜色，反正颜色就两种，其实一位就已经够了。
 * */
struct _rb_root
{
	struct _rb_node *rb_node;
};

/*这样，提取parent指针只要把rb_parent_color成员的低两位清零即可：*/
#define rb_parent(r)   ((struct _rb_node *)((r)->rb_parent_color & ~3))
/*取颜色只要看最后一位即可：*/
#define rb_color(r)   ((r)->rb_parent_color & 1)
#define rb_is_red(r)   (!rb_color(r))
#define rb_is_black(r) rb_color(r)
#define rb_set_red(r)  do { (r)->rb_parent_color &= ~1; } while (0)
#define rb_set_black(r)  do { (r)->rb_parent_color |= 1; } while (0)


static stinline void rb_set_parent(struct _rb_node *rb, struct _rb_node *p)
{
	rb->rb_parent_color = (rb->rb_parent_color & 3) | (unsigned long)p;
}
static stinline void rb_set_color(struct _rb_node *rb, int color)
{
	rb->rb_parent_color = (rb->rb_parent_color & ~1) | color;
}

#define RB_ROOT	(struct _rb_root) { NULL, }
#define	rb_entry(ptr, type, member) container_of(ptr, type, member)

#define RB_EMPTY_ROOT(root)	((root)->rb_node == NULL)
#define RB_EMPTY_NODE(node)	(rb_parent(node) == node)
#define RB_CLEAR_NODE(node)	(rb_set_parent(node, node))


/**
 * __rb_rotate_left是把以root为根的树中的node结点进行左旋，
 * __rb_rotate_right是进行右旋。这两个函数是为后面的插入和
 * 删除服务，而不是为外部提供接口。 
 */

/**
 * 插入的结点都设为叶子，染成红色，插入后如果破坏了上述规则，通
 * 过调整颜色和旋转可以恢复，二叉树又重新平衡。插入操作的接口函数是 
 */
/**
 * 它把已确定父结点的node结点融入到以root为根的红黑树中，具体算法
 * 的分析可以参考[1]中第14.3节，这里的实现和书中的讲解几乎完全一样。
 * 怎么确定node的父结点应该在调用rb_insert_color之前通过手工迭带
 * 完成。值得指出的一点是，虽然插入操作需要一个循环迭代，但是总的旋转
 * 次数不会超过两次！所以效率还是很乐观的。
 * */
extern void rb_insert_color(struct _rb_node *, struct _rb_root *);

/**
 * 删除操作多多少少都有点麻烦，它要先执行像普通二叉查找树的“删除”，
 * 然后根据删除结点的颜色来判断是否执行进一步的操作。删除的接口是：
 * 其实它并没有真正删除node，而只是让它和以root为根的树脱离关系，
 * 最后它还要判断是否调用__rb_erase_color来调整。
 * */
extern void rb_erase(struct _rb_node *, struct _rb_root *);

/* Find logical next and previous nodes in a tree */
/**
 * 返回node在树中的后继，这个稍微复杂一点。如果node的右孩子不为空，
 * 它只要返回node的右子树中最小的结点即可；如果为空，它要向上查找，
 * 找到迭带结点是其父亲的左孩子的结点，返回父结点。如果一直上述到了根结点，返回NULL。
 * */
extern struct _rb_node *rb_next(const struct _rb_node *);
/*返回node的前驱，和rb_next中的操作对称。*/
extern struct _rb_node *rb_prev(const struct _rb_node *);
/*在以root为根的树中找出并返回最小的那个结点，只要从根结点一直向左走就是了。*/
extern struct _rb_node *rb_first(const struct _rb_root *);
/*是找出并返回最大的那个，一直向右走。*/
extern struct _rb_node *rb_last(const struct _rb_root *);

/* Fast replacement of a single node without remove/rebalance/add/rebalance */
/*用new替换以root为根的树中的victim结点。*/
extern void rb_replace_node(struct _rb_node *victim, struct _rb_node *new, 
			    struct _rb_root *root);

/*测试颜色和设置颜色也是水到渠成的事了。需要特别指出的是下面的一个内联函数： */
/**
 * 它把parent设为node的父结点，并且让rb_link指向node。 
 * 我们把重点集中在lib/rbtree.c上，看看一些和红黑树相关的重要算法。开始之前我们一起回忆一下红黑树的规则： 
 * 1. 每个结点要么是红色要么是黑色； 
 * 2. 根结点必须是黑色； 
 * 3. 红结点如果有孩子，其孩子必须都是黑色； 
 * 4. 从根结点到叶子的每条路径必须包含相同数目的黑结点。 
 * 这四条规则可以限制一棵排序树是平衡的。 
 * */
static stinline void rb_link_node(struct _rb_node * node, struct _rb_node * parent,
				struct _rb_node ** rb_link)
{
	node->rb_parent_color = (unsigned long )parent;
	node->rb_left = node->rb_right = NULL;

	*rb_link = node;
}



ST_END_DECLS;
#endif	/* __ST_RBTREE_LK_H__ */


