/*	binomial-queue.c --  二项队列实现文件	*/
#include <malloc.h>
#include "st_binomial_queue.h"


/*	局部函数声明	*/

static SubTree BQCombine_Trees (SubTree t1, SubTree t2) ;
static BQNode * BQMake_Node (const BQItem item) ;
static void BQRecursively (const SubTree t, void (* pfun) (const BQItem item)) ;

/*	接口函数定义	*/

int BQInitialize (BinQueue * const pbq, const int size)
{
	int i ;

	if (size <= 0)
		return 0 ;
	*pbq = (struct binqueue *) malloc (sizeof (struct binqueue)) ;
	if (NULL == *pbq)
		return 0 ;
	(*pbq)->forest = (SubTree *) malloc (sizeof (SubTree) * size) ;
	if (NULL == (*pbq)->forest)
	{
		free (*pbq) ;
		return 0 ;
	}
	for (i = 0; i < size; i++)
		(*pbq)->forest[i] = NULL ;
	(*pbq)->size = size ;
	(*pbq)->current = 0 ;

	return 1 ;
}

int BQIsEmpty (const BinQueue bq)
{
	return 0 == bq->current ;
}

BinQueue BQMerge (BinQueue bq1, BinQueue bq2)
{
	BinQueue temp ;
	SubTree t1, t2, carry = NULL ;
	int i, j, ct, index = 0 ;

	//	此处的检测, 很重要.
	if (bq1 == bq2)
		return bq1 ;
	if (bq1->current + bq2->current > bq1->size)
		return bq1 ;
	bq1->current += bq2->current ;
	//	保障 bq1 -> current > bq2 -> current								-->
	if (bq1->current < bq2->current)
	{
		temp = bq1 ;
		bq1 = bq2 ;
		bq2 = temp ;
	}
	//	这样就可以通过下面的 bq2 所有子树都已被合并过的条件检测有
	//	效地避免当 bq2 -> current 很小的时候将造成的太多次不必要的条件检测	-->
	for (i = 0, j = 1, ct = 0; j <= bq1->current; i++, j *= 2)
	{
		t1 = bq1->forest[i] ;
		//	以下判断是为了应对Insert的情况, 因为我在Insert时只分配了1棵子树的空间
		if (1 == index)
			t2 = NULL ;
		else if (1 == bq2->size)
		{
			index = 1 ;
			t2 = bq2->forest[i] ;
		}
		else
			t2 = bq2->forest[i] ;
		//	这个方法真的很巧妙, 开了眼界
		switch (!!t1 + 2 * !!t2 + 4 * !!carry)
		{
			//	no trees
			case 0 :	break ;
			//	only bq1
			case 1 :	if (ct == bq2->size)
						{
							BQRelease(bq2) ;
							return bq1 ;
						}
						break ;
			//	only bq2
			case 2 :	bq1->forest[i] = t2 ;
						bq2->forest[i] = NULL ;
						ct++ ;
						break ;
			//	only carry
			case 4 :	bq1->forest[i] = carry ;
						carry = NULL ;
						break ;
			//	bq1 and bq2
			case 3 :	carry = BQCombine_Trees (t1, t2) ;
						bq1->forest[i] = bq2->forest[i] = NULL ;
						ct++ ;
						break ;
			//	bq1 and carry
			case 5 :	carry = BQCombine_Trees (t1, carry) ;
						bq1->forest[i] = NULL ;
						break ;
			//	bq2 and carry
			case 6 :	carry = BQCombine_Trees (t2, carry) ;
						bq2->forest[i] = NULL ;
						ct++ ;
						break ;
			//	all there
			case 7 :	bq1->forest[i] = carry ;
						carry = BQCombine_Trees (t1, t2) ;
						bq2->forest[i] = NULL ;
						break ;
		}
	}

	return bq1 ;
}


BinQueue BQInsert (BinQueue bq, const BQItem item)
{
	BinQueue temp ;
	int size = 1 ;

	if (bq->size == bq->current)
		return bq ;
	if (!BQInitialize (&temp, size))
	{
		free (temp->forest) ;
		free (temp) ;
		return bq ;
	}
	temp->forest[0] = BQMake_Node (item) ;
	if (NULL == temp->forest[0])	// 话说这个位置原先有一个";"
	{
		free (temp->forest[0]) ;
		free (temp) ;
		return bq ;
	}
 	temp->current = 1 ;
	bq = BQMerge (bq, temp) ;

	return bq ;
}

BQItem BQDeleteMin (BinQueue bq)
{
	BinQueue deleted_queue ;
	SubTree deleted_tree, old_root ;
	BQItem min ;
	int i, j, size, min_index ;

	if (BQIsEmpty (bq))
		return -BQINFINITY ;
	
	min = BQINFINITY ;
	for (i = 0, size = bq->size; i < size; i++)
	{
		if (bq->forest[i] && bq->forest[i]->item < min)
		{
			min = bq->forest[i]->item ;
			min_index = i ;
		}
	}
	if (BQINFINITY == min)
		return BQINFINITY ;
	
	deleted_tree = bq->forest[min_index] ;
	old_root = deleted_tree ;
	deleted_tree = deleted_tree->left ;
	free (old_root) ;
	BQInitialize (&deleted_queue, (1 << min_index) - 1) ;
	for (j = min_index - 1; j >= 0; j--)
	{
		deleted_queue->forest[j] = deleted_tree ;
		deleted_tree = deleted_tree->nextsibling ;
		deleted_queue->forest[j] ->nextsibling = NULL ;
	}
	bq->forest[min_index] = NULL ;
	bq->current -= deleted_queue->current + 1 ;

	bq = BQMerge (bq, deleted_queue) ;

	return min ;
}

void BQTraversal (const BinQueue bq, void (* pfun) (const BQItem item))
{
	int i, size ;

	for (i = 0, size = bq->size; i < size; i++)
		if (bq->forest[i])
			BQRecursively (bq->forest[i], pfun) ;
}

void BQRelease (const BinQueue bq)
{
	int i, size ;

	for (i = 0, size = bq -> size; i < size; i++)
	{
		if (bq->forest[i])
			free (bq->forest[i]) ;
	}
	free (bq) ;
}


/*	局部函数定义	*/

static SubTree BQCombine_Trees (SubTree t1, SubTree t2)
{
	if (t1->item > t2->item)
		return BQCombine_Trees (t2, t1) ;	//	话说这个地方的 t1 原来是 t2, 真不知道我这一天都在想些什么
	t2->nextsibling = t1->left ;
	t1->left = t2 ;

	return t1 ;
}

static BQNode * BQMake_Node (const BQItem item)
{
	BQNode * new_node ;

	new_node = (BQNode *) malloc (sizeof (BQNode)) ;
	if (NULL == new_node)
		return NULL ;
	new_node->item = item ;
	new_node->left = new_node->nextsibling = NULL ;

	return new_node ;
}

static void BQRecursively (const SubTree t, void (* pfun) (const BQItem item))
{
	if (t->left)
		BQRecursively (t->left, pfun) ;
	if (t->nextsibling)
		BQRecursively (t->nextsibling, pfun) ;
	(* pfun) (t->item) ;
}




