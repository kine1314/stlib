#ifndef	__ST_RBTREE_H__
#define	__ST_RBTREE_H__

#include "stlib.h"

/**
 * 1) 每一个节点或者着红色,或者着成黑色. 
 * 2) 根是黑色的 
 * 3) 如果一个节点是红色的,那么它的子节点必须是黑色的. 
 * 4) 从一个节点到一个NULL指针的每一条路径必须包含相同数目的黑色节点
 * */

ST_BEGIN_DECLS;
/*	明显常量定义	*/
#define INFINITY (~(1 << 31))
#define NEGATIVE_INFINITY (1 << 31)

/*	数据类型定义	*/

typedef enum colorType {Red, Black} ColorType ;
typedef stint RBItem ;
typedef struct _RBNode
{
	RBItem item ;
	struct _RBNode * left, * right ;
	ColorType color ;
} RBNode ;
typedef struct _RBTree
{
	RBNode * root ;
	stint current ;				// the count of tree node ;
}RBTree, *pRBTree ;

/*	全局变量声明	*/

static RBNode * RBNullNode = NULL ;
RBNode * Current, * Sibling, * Parent, * GrParent, * GrGrParent ;

/*	接口函数声明	*/

/*	操作:	创建并初始化一棵红黑树并为 RBNullNode 分配内存空间	*/
/*	操作前:	prbt 指向一棵红黑树	*/
/*	操作后:	如果内存分配成功, 该红黑树被初始化为空, 为 RBNullNode 分配内存空间, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool st_rbtree_create (pRBTree * const prbt) ;

/*	操作:	确定一棵红黑树是否为空	*/
/*	操作前:	prbt 指向一棵已初始化的红黑树	*/
/*	操作后:	如果该红黑树为空, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool st_rbtree_empty (const pRBTree * const prbt) ;

/*	操作:	向红黑树中插入一个结点	*/
/*	操作前:	prbt 指向一棵已初始化的红黑树, item 是待添加数据	*/
/*	操作后:	如果内存分配成功 && item 之前不存在于该红黑树中, 向该红黑树中添加1个数据域为 item 的结点, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool st_rbtree_insert (pRBTree * const prbt, const RBItem item) ;

/*	操作:	从红黑树中删除一个结点	*/
/*	操作前:	prbt 指向一棵已初始化的红黑树, item 是待删除数据	*/
/*	操作后:	如果找到该结点, 删除它, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool st_rbtree_delete (pRBTree * const prbt, const RBItem item) ;

/*	操作:	将一个函数以中序作用于红黑树中所有结点1次	*/
/*	操作前:	prbt 指向一棵已初始化的红黑树, pfun 指向一个没有返回值, 接受一个 RBNode * 类型参数的函数	*/
/*	操作后:	pfun 指向的函数被以中序依次作用于该红黑树中所有结点1次	*/
/*	时间复杂度:	O (N)	*/
void st_rbtree_traverse (const pRBTree * const prbt, void (* pfun) (const RBNode * const pn)) ;

/*	操作:	释放一棵红黑树占用的内存空间	*/
/*	操作前:	prbt 指向一棵已初始化的红黑树	*/
/*	操作后:	该红黑树占用的内存空间被释放	*/
/*	时间复杂度:	O (N)	*/
void st_rbtree_release (const pRBTree * const prbt) ;


// complete the down2up RBTREE ;
typedef stint RBKey_t;
typedef stint data_t;

typedef enum color_t
{
    RED = 0,
    BLACK = 1
}color_t;

typedef struct rb_node_t
{
    struct rb_node_t *left, *right, *parent;
    RBKey_t key;				// this is the value
    data_t data;			// the index
    color_t color;
}rb_node_t;

/* forward declaration */

rb_node_t* st_rbt_insert(RBKey_t key, data_t data, rb_node_t* root);

rb_node_t* st_rbt_search(RBKey_t key, rb_node_t* root);

rb_node_t* st_rbt_erase(RBKey_t key, rb_node_t* root);

void	rb_traverse(rb_node_t* root);




ST_END_DECLS;
#endif	/* __ST_RBTREE_H__ */

