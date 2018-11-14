#ifndef	__ST_SPLAYTREE_H__
#define	__ST_SPLAYTREE_H__
/*	 -- 自顶向下伸展树头文件	*/
/*
 * 伸展树的主要特点：每次访问某个节点时，都把此节点旋转到根部。
 * 保证从空树开始任意M次操作最多花费O(MlogN)的时间，也就是说它的摊还时间为O（F（N））。
 */
#include "stlib.h"

ST_BEGIN_DECLS;

typedef stint SPYItem ;
typedef struct _SPYNode
{
	SPYItem item ;
	struct _SPYNode * left, * right ;
	stint leftSubTreeCount, rightSubTreeCount ;
} SPYNode ;
typedef struct _SplayTree
{
	SPYNode * root ;
	stint current ;									// count the node num
}SplayNode, * SplayTree ;

/*	全局变量声明	*/

static SPYNode * NullNode = NULL ;

/*	接口函数声明	*/

/*	操作:	创建一棵伸展树, 初始化为空, 并且为 NullNode 分配内存空间	*/
/*	操作前:	pst 指向一棵伸展树	*/
/*	操作后:	如果内存分配成功, 创建一棵伸展树, 将其初始为空, 并为 NullNode 分配内存空间, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool st_splay_tree_create (SplayTree * const pst) ;

/*	操作:	确定一棵伸展树是否为空	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	如果该伸展树为空, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool st_splay_tree_empty (const SplayTree * const pst) ;

/*	操作:	向伸展树中插入一个元素	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, pi 指向待添加数据	*/
/*	操作后:	如果内存分配成功, 向该伸展树中添加数据域为 *pi 的新结点, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool st_splay_tree_insert (const SplayTree * const pst, const SPYItem * const pi) ;

/*	操作:	返回指向伸展树中根节点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	如果该伸展树不为空, 返回指向该伸展树根结点的指针; 否则返回 NULL	*/
/*	时间复杂度:	O (1)	*/
SPYNode * st_splay_tree_retrieve (const SplayTree * const pst) ;

/*	操作:	在伸展树中查找指定数据	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, pi 指向待查找数据	*/
/*	操作后:	如果该伸展树不为空 && 找到该数据, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool st_splay_tree_find (const SplayTree * const pst, const SPYItem * const pi) ;

/*	操作:	返回指向伸展树中数据域第k小结点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, k 指示待查找数据的序数	*/
/*	操作后:	如果该伸展树的大小 >= k && k > 0, 返回指向该伸展树中数据域第 k 小的结点的指针 ; 否则返回 NULL	*/
/*	时间复杂度:	O (log N)	*/
SPYNode * st_splay_tree_find_kthmin (const SplayTree * const pst, int k) ;

/*	操作:	返回指向伸展树中数据域第k大结点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, k 指示待查找数据的序数	*/
/*	操作后:	如果该伸展树的大小 >= k && k > 0, 返回指向该伸展树中数据域第 k 大的结点的指针 ; 否则返回 NULL	*/
/*	时间复杂度:	O (log N)	*/
SPYNode * st_splay_tree_find_kthmax (const SplayTree * const pst, int k) ;

/*	操作:	返回指向伸展树中最小结点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	如果该伸展树不为空, 返回指向该伸展树中最小结点的指针 ; 否则返回 NULL	*/
/*	时间复杂度:	O (log N)	*/
SPYNode * st_splay_tree_find_min (const SplayTree * const pst) ;

/*	操作:	返回指向伸展树中最大结点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	如果该伸展树不为空, 返回指向该伸展树中最大结点的指针 ; 否则返回 NULL	*/
/*	时间复杂度:	O (log N)	*/
SPYNode * st_splay_tree_find_max (const SplayTree * const pst) ;

/*	操作:	删除伸展树中数据域为指定数据的结点	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, pi 指向待删除数据	*/
/*	操作后:	如果该伸展树不为空 && 找到该结点, 删除该结点, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool st_splay_tree_delete (const SplayTree * const pst, const SPYItem * const pi) ;

/*	操作:	以中序将一个函数依次作用于伸展树中所有结点1次	*/
/*	操作前:	pr 指向一棵已初始化的伸展树的根, pfun 指向一个没有返回值, 接受一个 SPYNode * 类型参数的函数	*/
/*	操作后:	pfun 指向的函数以中序作用于该伸展树中所有结点1次	*/
/*	时间复杂度:	O (log N)	*/
void st_splay_tree_traverse (const SPYNode * const pr, void (* pfun) (const SPYNode * const pn)) ;

/*	操作:	释放一棵伸展树占用的内存空间	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	该伸展树占用的内存空间被释放	*/
/*	时间复杂度:	O (log N)	*/
void st_splay_tree_release (const SplayTree * const pst) ;






ST_END_DECLS;
#endif	/* __ST_SPLAYTREE_H__ */

