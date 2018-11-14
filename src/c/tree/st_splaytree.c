#include <stdio.h>
#include <malloc.h>
#include "st_splaytree.h"
#include "st_log.h"


/*	�ⲿ��������	*/

extern SPYNode * NullNode ;

/*	�ֲ���������	*/

static SPYNode * singleRotateWithLeft (SPYNode * const position) ;
static SPYNode * singleRotateWithRight (SPYNode * const position) ;
static void upDataLeftSubTreeCount (SPYNode * const headerRight) ;
static void upDataRightSubTreeCount (SPYNode * const headerLeft) ;
static SPYNode * splay (SPYNode * root, const SPYItem * const pi) ;
static void release (SPYNode * const root) ;

/*	�ӿں�������	*/

/*	����:	����һ����չ��, ��ʼ��Ϊ��, ����Ϊ NullNode �����ڴ�ռ�	*/
/*	����ǰ:	pst ָ��һ����չ��	*/
/*	������:	����ڴ����ɹ�, ����һ����չ��, �����ʼΪ��, ��Ϊ NullNode �����ڴ�ռ�, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool st_splay_tree_create (SplayTree * const pst) 
{
	NullNode = (SPYNode *) malloc (sizeof (SPYNode)) ;
	if (NULL == NullNode)
		return FALSE ;
	*pst = (SplayTree) malloc (sizeof (SplayNode)) ;
	if (NULL == *pst)
	{
		free (NullNode) ;
		NullNode = NULL ;
		return FALSE ;
	}
	else
	{
		NullNode->left = NullNode->right = NullNode ;
		NullNode->leftSubTreeCount = NullNode->rightSubTreeCount = 0 ;
		(*pst)->root = NullNode ;
		(*pst)->current = 0 ;
		return TRUE ;
	}
}


/*	����:	ȷ��һ����չ���Ƿ�Ϊ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	�������չ��Ϊ��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool st_splay_tree_empty (const SplayTree * const pst) 
{
	if (NullNode == (*pst)->root)
		return TRUE ;
	else
		return FALSE ;
}




/*	����:	����չ���в���һ��Ԫ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, pi ָ����������	*/
/*	������:	����ڴ����ɹ�, �����չ�������������Ϊ *pi ���½��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool st_splay_tree_insert (const SplayTree * const pst, const SPYItem * const pi) 
{
	static SPYNode * newNode = NULL ;
	SPYNode * root ;

	/*	If it had tried to insert a item that has been inserted to the tree just now,	*/
	/*	it won't need allocate memory space.	*/
	if (NULL == newNode)
	{
		newNode = (SPYNode *) malloc (sizeof (SPYNode)) ;
		if (NULL == newNode)
			return FALSE ;
	}
	newNode->item = *pi ;
	
	if (NullNode == (*pst)->root)
	{
		newNode->left = newNode->right = NullNode ;
		newNode->leftSubTreeCount = newNode->rightSubTreeCount = 0 ;
		(*pst)->root = newNode ;
	}
	else
	{
		(*pst)->root = splay((*pst)->root, pi) ;
		root = (*pst)->root ;
		if (*pi < root->item)
		{
			newNode->leftSubTreeCount = root->leftSubTreeCount ;
			newNode->left = root->left ;
			root->leftSubTreeCount = 0 ;
			root->left = NullNode ;
			newNode->rightSubTreeCount = root->rightSubTreeCount + 1 ;
			newNode->right = root ;
			(*pst)->root = newNode ;
		}
		else if (*pi > (*pst)->root->item)
		{
			newNode->rightSubTreeCount = root->rightSubTreeCount ;
			newNode->right = root->right ;
			root->rightSubTreeCount = 0 ;
			root->right = NullNode ;
			newNode->leftSubTreeCount = root->leftSubTreeCount + 1 ;
			newNode->left = root ;
			(*pst)->root = newNode ;
		}
		else
			/*	Already in the tree.	*/
			return FALSE ;
	}

	/*	So next insert will call malloc.	*/
	newNode = NULL ;

	(*pst)->current++ ;
	return TRUE ;
}




/*	����:	����ָ����չ���и��ڵ��ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	�������չ����Ϊ��, ����ָ�����չ��������ָ��; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
SPYNode * st_splay_tree_retrieve (const SplayTree * const pst) 
{
	if (st_splay_tree_empty (pst))
		return NULL ;
	else
		return (*pst)->root ;
}




/*	����:	����չ���в���ָ������	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, pi ָ�����������	*/
/*	������:	�������չ����Ϊ�� && �ҵ�������, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool st_splay_tree_find (const SplayTree * const pst, const SPYItem * const pi) 
{
	splay ((*pst)->root, pi) ;
	if (*pi == (*pst)->root->item)
		return TRUE ;
	else
		return FALSE ;
}


/*	����:	����ָ����չ�����������kС����ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, k ָʾ���������ݵ�����	*/
/*	������:	�������չ���Ĵ�С >= k && k > 0, ����ָ�����չ����������� k С�Ľ���ָ�� ; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
SPYNode * st_splay_tree_find_kthmin (const SplayTree * const pst, int k) 
{
	SPYNode * scan ;

	if (k > (*pst)->current || k <= 0)
		return NULL ;
	scan = (*pst)->root ;

	while (1)
	{
		if (scan->leftSubTreeCount + 1 == k)
			break ;
		else if (scan->leftSubTreeCount >= k)
			scan = scan->left ;
		else
		{
			k = k - scan->leftSubTreeCount - 1 ;
			scan = scan->right ;
		}
	}
	/*	Not must to do.	*/
	(*pst)->root = splay ((*pst)->root, &scan->item) ;
	
	return scan ;
}



/*	����:	����ָ����չ�����������k�����ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, k ָʾ���������ݵ�����	*/
/*	������:	�������չ���Ĵ�С >= k && k > 0, ����ָ�����չ����������� k ��Ľ���ָ�� ; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
SPYNode * st_splay_tree_find_kthmax (const SplayTree * const pst, int k) 
{
	SPYNode * scan ;

	if (k > (*pst)->current || k <= 0)
		return NULL ;
	scan = (*pst)->root ;

	while (1)
	{
		if (scan->rightSubTreeCount + 1 == k)
			break ;
		else if (scan->rightSubTreeCount >= k)
			scan = scan->right ;
		else
		{
			k = k - scan->rightSubTreeCount - 1 ;
			scan = scan->left ;
		}
	}
	(*pst)->root = splay ((*pst)->root, &scan->item) ;

	return scan ;
}


/*	����:	����ָ����չ������С����ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	�������չ����Ϊ��, ����ָ�����չ������С����ָ�� ; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
SPYNode * st_splay_tree_find_min (const SplayTree * const pst) 
{
	SPYNode * scan = (*pst)->root ;
	
	while (scan->left != NullNode)
		scan = scan->left ;

	return scan ;
}


/*	����:	����ָ����չ����������ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	�������չ����Ϊ��, ����ָ�����չ����������ָ�� ; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
SPYNode * st_splay_tree_find_max (const SplayTree * const pst) 
{
	SPYNode * scan = (*pst)->root ;

	while (scan->right != NullNode)
		scan = scan->right ;

	return scan ;
}


/*	����:	ɾ����չ����������Ϊָ�����ݵĽ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, pi ָ���ɾ������	*/
/*	������:	�������չ����Ϊ�� && �ҵ��ý��, ɾ���ý��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool st_splay_tree_delete (const SplayTree * const pst, const SPYItem * const pi) 
{
	SPYNode * root ;

	if (st_splay_tree_empty (pst))
		return FALSE ;
	(*pst)->root = splay ((*pst)->root, pi) ;
	root = (*pst)->root ;
	if (*pi == root->item)
	{
		/*	Found it!	*/
		if (NullNode == root->left)
			(*pst)->root = root->right ;
		else
		{
			(*pst)->root = root->left ;
			/*	To set (*pst)->root->right = NullNode.	*/
			(*pst)->root = splay ((*pst)->root, pi) ;
			(*pst)->root->right = root->right ;
		}
		free (root) ;
		(*pst)->current-- ;
		return TRUE ;
	}
	else
		return FALSE ;
}


/*	����:	������һ������������������չ�������н��1��	*/
/*	����ǰ:	pr ָ��һ���ѳ�ʼ������չ���ĸ�, pfun ָ��һ��û�з���ֵ, ����һ�� SPYNode * ���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ��������������ڸ���չ�������н��1��	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
void st_splay_tree_traverse (const SPYNode * const pr, void (* pfun) (const SPYNode * const pn)) 
{
	if (pr != NullNode)
	{
		st_splay_tree_traverse (pr->left, pfun) ;
		(* pfun) (pr) ;
		st_splay_tree_traverse (pr->right, pfun) ;
	}
}


/*	����:	�ͷ�һ����չ��ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	����չ��ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
void st_splay_tree_release (const SplayTree * const pst) 
{
	release ((*pst)->root) ;
	free (*pst) ;
	free (NullNode) ;
}

/*	�ֲ���������	*/

static SPYNode * singleRotateWithLeft (SPYNode * const position)
{
	SPYNode * child ;

	child = position->left ;
	position->leftSubTreeCount = child->rightSubTreeCount ;
	position->left = child->right ;
	
	child->rightSubTreeCount = position->leftSubTreeCount + position->rightSubTreeCount + 1 ;
	child->right = position ;

	return child ;
}

static SPYNode * singleRotateWithRight (SPYNode * const position)
{
	SPYNode * child ;
	
	child = position->right ;
	position->rightSubTreeCount = child->leftSubTreeCount ;
	position->right = child->left ;
	child->leftSubTreeCount = position->leftSubTreeCount + position->rightSubTreeCount + 1 ;
	child->left = position ;

	return child ;
}

static void upDataLeftSubTreeCount (SPYNode * const headerRight)
{
	if (headerRight != NullNode)
	{
		if (headerRight->left != NullNode)
		{
			upDataLeftSubTreeCount (headerRight->left) ;
			headerRight->leftSubTreeCount = headerRight->left->leftSubTreeCount + headerRight->left->rightSubTreeCount + 1 ;
		}
		else
			headerRight->leftSubTreeCount = 0 ;
	}
}

static void upDataRightSubTreeCount (SPYNode * const headerLeft)
{
	if (headerLeft != NullNode)
	{
		if (headerLeft->right != NullNode)
		{
			upDataRightSubTreeCount (headerLeft->right) ;
			headerLeft->rightSubTreeCount = headerLeft->right->leftSubTreeCount + headerLeft->right->rightSubTreeCount + 1 ;
		}
		else
			headerLeft->rightSubTreeCount = 0 ;
	}
}

/*	NullNode->leftSubTreeCount = NullNode->rightSubTreeCount = 0.	*/
static SPYNode * splay (SPYNode * root, const SPYItem * const pi)
{
	SPYNode header ;
	SPYNode * left_tree_max, * right_tree_min ;

	header.left = header.right = NullNode ;
	left_tree_max = right_tree_min = &header ;
	NullNode->item = *pi ;

	while (*pi != root->item)
	{
		if (*pi < root->item)
		{
			if (*pi < root->left->item)
				root = singleRotateWithLeft (root) ;
			if (NullNode == root->left)
				break ;
			/*	Link right.	*/
			right_tree_min->left = root ;
			right_tree_min = root ;
			root = root->left ;
		}
		else
		{
			if (*pi > root->right->item)
				root = singleRotateWithRight (root) ;
			if (NullNode == root->right)
				break ;
			/*	Link left.	*/
			left_tree_max->right = root ;
			left_tree_max = root ;
			root = root->right ;
		}
	}
	/*	Reassemble.	*/
	left_tree_max->right = root->left ;
	right_tree_min->left = root->right ;
	root->left = header.right ;
	root->right = header.left ;
	upDataLeftSubTreeCount (root->right) ;
	upDataRightSubTreeCount (root->left) ;
	if (root->left != NullNode)
		root->leftSubTreeCount = root->left->leftSubTreeCount + root->left->rightSubTreeCount + 1 ;
	else
		root->leftSubTreeCount = 0 ;
	if (root->right != NullNode)
		root->rightSubTreeCount = root->right->leftSubTreeCount + root->right->rightSubTreeCount + 1 ;
	else
		root->rightSubTreeCount = 0 ;

	return root ;
}

static void release (SPYNode * const root)
{
	if (root != NullNode)
	{
		release (root->left) ;
		release (root->right) ;
		free (root) ;
	}
}




