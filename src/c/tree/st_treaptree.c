#include <stdio.h>
#include <malloc.h>
#include "st_treaptree.h"
#include "st_log.h"


#define Infinity 32767

/* 全局变量定义 */
Position TRNullNode = NULL;  /* Needs initialization */
static Position SingleRotateWithLeft( Position K2 ) ;
static Position SingleRotateWithRight( Position K1 ) ;


/*	局部函数声明	*/
static int Random( void ) ;


/*	接口函数定义	*/
Treap
st_treap_tree_init( void )
{
	if( TRNullNode == NULL )
	{
		TRNullNode = malloc( sizeof( TreapNode ) );
		if( TRNullNode == NULL )
			__err( "Out of space!!!" );
		TRNullNode->Left = TRNullNode->Right = TRNullNode;
		TRNullNode->Priority = Infinity;
	}
	return TRNullNode;
}

Treap
st_treap_tree_destroy( Treap T )
{
	if( T != TRNullNode )
	{
		st_treap_tree_destroy( T->Left );
		st_treap_tree_destroy( T->Right );
		free( T );
	}
	return TRNullNode;
}

/* 超找树中的指定节点，平衡查找 */
Position
st_treap_tree_find( TRElemType X, Treap T )
{
	if( T == TRNullNode )
		return TRNullNode;
	if( X < T->Element )
		return st_treap_tree_find( X, T->Left );
	else
	if( X > T->Element )
		return st_treap_tree_find( X, T->Right );
	else
		return T;
}

/* 查找treap中的最小节点，即寻找最左的节点 */
Position
st_treap_tree_find_min( Treap T )
{
	if( T == TRNullNode )
		return TRNullNode;
	else
	if( T->Left == TRNullNode )
		return T;
	else
		return st_treap_tree_find_min( T->Left );
}

/* 查找treap中最大的节点，即treap中的最右节点 */
Position
st_treap_tree_find_max( Treap T )
{
	if( T != TRNullNode )
		while( T->Right != TRNullNode )
			T = T->Right;

	return T;
}

/* 插入节点到treap中 */
Treap
st_treap_tree_insert( TRElemType Item, Treap T )
{
	if( T == TRNullNode )
	{
		/* Create and return a one-node tree */
		T = malloc( sizeof( TreapNode ) );
		if( T == NULL )
			__err( "Out of space!!!" );
		else
		{
			T->Element = Item; T->Priority = Random( );
			T->Left = T->Right = TRNullNode;
		}
	}
	else
	if( Item < T->Element )
	{
		T->Left = st_treap_tree_insert( Item, T->Left );
		if( T->Left->Priority < T->Priority )
			T = SingleRotateWithLeft( T );
	}
	else
	if( Item > T->Element )
	{
		T->Right = st_treap_tree_insert( Item, T->Right );
		if( T->Right->Priority < T->Priority )
			T = SingleRotateWithRight( T );
	}

	/* Otherwise it's a duplicate; do nothing */

	return T;
}


/* 移除treap的指定节点 */
Treap
st_treap_tree_remove( TRElemType Item, Treap T )
{
	if( T != TRNullNode )
	{
		if( Item < T->Element )
			T->Left = st_treap_tree_remove( Item, T->Left );
		else
		if( Item > T->Element )
			T->Right = st_treap_tree_remove( Item, T->Right );
		else
		{
			/* Match found */
			if( T->Left->Priority < T->Right->Priority )
				T = SingleRotateWithLeft( T );
			else
				T = SingleRotateWithRight( T );

			if( T != TRNullNode )    /* Continue on down */
				T = st_treap_tree_remove( Item, T );
			else
			{
				/* At a leaf */
				free( T->Left );
				T->Left = TRNullNode;
			}
		}
	}
	return T;
}

/* 返回treap的根节点 */
TRElemType
st_treap_tree_retrieve( Position P )
{
	return P->Element;
}

/* 对treap进行中序遍历 */
void
st_treap_tree_traverse( Treap T )
{
	if( T != TRNullNode )
	{
		st_treap_tree_traverse( T->Left );
		printf( "%d ", T->Element );
		st_treap_tree_traverse( T->Right );
	}
}


/* 局部函数定义 */

static stint Random( void )
{
	return rand( ) -  1;
}


/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

static Position
SingleRotateWithLeft( Position K2 )
{
	Position K1;

	K1 = K2->Left;								// 临时保存左子树
	K2->Left = K1->Right;						// 左子树的右子树成为根节点的左子树
	K1->Right = K2;								// k2成为k1的右子树，k1成为新的根节点

	return K1;  /* New root */
}

/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */

static Position
SingleRotateWithRight( Position K1 )
{
	Position K2;

	K2 = K1->Right ;
	K1->Right = K2->Left ;
	K2->Left = K1 ;

	return K2;  /* New root */
}

















