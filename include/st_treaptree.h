#ifndef	__ST_TREAP_TREE_H__
#define	__ST_TREAP_TREE_H__

#include "stlib.h"

ST_BEGIN_DECLS;
/* 随机平衡二叉树 */

/*
 *	Treap是用来排序(Sort)的一种数据结构(Data Structure)。
 *	reap是随机查找二叉平衡树。 Treap发音为+ Heap。顾名思义， 
 *	Treap把 BST和 Heap结合了起来。它和 BST一样满足许多优美
 *	的性质，而引入堆目的就是为了维护平衡。 Treap在 BST的基础上，
 *	添加了一个修正值。在满足 BST性质的基图 5 础上，Treap节点的
 *	修正值还满足最小堆性质2。最小堆性质可以被描述为每个子树根
 *	节点都小于等于其子节点。于是， Treap可以定义为有以下性质的二叉树： 
 *	1.若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值，
 *	而且它的根节点的修正值小于等于左子树根节点的修正值； 
 *	2. 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值，
 *	而且它的根节点的修正值小于等于右子树根节点的修正值； 
 *	3. 它的左、右子树也分别为 Treap。
*/
/*
为什么要用 Treap 
(1) Treap的特点 
1.  Treap简明易懂。Treap只有两种调整方式，左旋和右旋。而且即使没有严密的数学证明和分析，
	Treap的构造方法啊，平衡原理也是不难理解的。只要能够理解 BST和堆的思想，理解 Treap当然不在话下。 
2.  Treap易于编写。Treap只需维护一个满足堆序的修正值，修正值一经生成无需修改。相
	比较其他各种平衡树， Treap拥有最少的调整方式，仅仅两种相互对称的旋转。所以 Treap当之无愧是最易于编码调试的一种平衡树。 
3.  Treap稳定性佳。Treap的平衡性虽不如 AVL，红黑树， SBT等平衡树，但是 Treap也不会退化，可以保证期望 O(logN)的深度。
	Treap的稳定性取决于随机数发生器。 
4.  Treap具有严密的数学证明。Treap期望 O(logN)的深度，是有严密的数学证明的。但这不是介绍的重点，大多略去。 
5.  Treap具有良好的实践效果。各种实际应用中， Treap的稳定性表现得相当出色，没有因为任何的构造出的数据而退化。
	于是在信息学竞赛中，不少选手习惯于使用 Treap，均取得了不俗的表现。 如果需要更详细的资料，可以发邮箱。
*/


typedef stint TRElemType;

typedef struct _TreapNode
{
	TRElemType 				Element;
	struct _TreapNode*      Left;
	struct _TreapNode*      Right;
	stint         			Priority;
}TreapNode, *Treap, *Position;

Treap st_treap_tree_destroy( Treap T );
Position st_treap_tree_find( TRElemType X, Treap T );
Position st_treap_tree_find_min( Treap T );
Position st_treap_tree_find_max( Treap T );
Treap st_treap_tree_init( void );
Treap st_treap_tree_insert( TRElemType X, Treap T );
Treap st_treap_tree_remove( TRElemType X, Treap T );
TRElemType st_treap_tree_retrieve( Position P );
void st_treap_tree_traverse( Treap T );

extern Position TRNullNode;

ST_END_DECLS ;
#endif	/* __ST_TREAP_TREE_H__ */

