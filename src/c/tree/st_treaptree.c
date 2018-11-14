#include <stdio.h>
#include <malloc.h>
#include "st_treaptree.h"
#include "st_log.h"


#define Infinity 32767

/* ȫ�ֱ������� */
Position TRNullNode = NULL;  /* Needs initialization */
static Position SingleRotateWithLeft( Position K2 ) ;
static Position SingleRotateWithRight( Position K1 ) ;


/*	�ֲ���������	*/
static int Random( void ) ;


/*	�ӿں�������	*/
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

/* �������е�ָ���ڵ㣬ƽ����� */
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

/* ����treap�е���С�ڵ㣬��Ѱ������Ľڵ� */
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

/* ����treap�����Ľڵ㣬��treap�е����ҽڵ� */
Position
st_treap_tree_find_max( Treap T )
{
	if( T != TRNullNode )
		while( T->Right != TRNullNode )
			T = T->Right;

	return T;
}

/* ����ڵ㵽treap�� */
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


/* �Ƴ�treap��ָ���ڵ� */
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

/* ����treap�ĸ��ڵ� */
TRElemType
st_treap_tree_retrieve( Position P )
{
	return P->Element;
}

/* ��treap����������� */
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


/* �ֲ��������� */

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

	K1 = K2->Left;								// ��ʱ����������
	K2->Left = K1->Right;						// ����������������Ϊ���ڵ��������
	K1->Right = K2;								// k2��Ϊk1����������k1��Ϊ�µĸ��ڵ�

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

















