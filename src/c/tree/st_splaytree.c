#include <stdio.h>
#include <malloc.h>
#include "st_splaytree.h"
#include "st_log.h"


/*	外部变量引用	*/

extern SPYNode * NullNode ;

/*	局部函数声明	*/

static SPYNode * singleRotateWithLeft (SPYNode * const position) ;
static SPYNode * singleRotateWithRight (SPYNode * const position) ;
static void upDataLeftSubTreeCount (SPYNode * const headerRight) ;
static void upDataRightSubTreeCount (SPYNode * const headerLeft) ;
static SPYNode * splay (SPYNode * root, const SPYItem * const pi) ;
static void release (SPYNode * const root) ;

/*	接口函数定义	*/

/*	操作:	创建一棵伸展树, 初始化为空, 并且为 NullNode 分配内存空间	*/
/*	操作前:	pst 指向一棵伸展树	*/
/*	操作后:	如果内存分配成功, 创建一棵伸展树, 将其初始为空, 并为 NullNode 分配内存空间, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
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


/*	操作:	确定一棵伸展树是否为空	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	如果该伸展树为空, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
stbool st_splay_tree_empty (const SplayTree * const pst) 
{
	if (NullNode == (*pst)->root)
		return TRUE ;
	else
		return FALSE ;
}




/*	操作:	向伸展树中插入一个元素	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, pi 指向待添加数据	*/
/*	操作后:	如果内存分配成功, 向该伸展树中添加数据域为 *pi 的新结点, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
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




/*	操作:	返回指向伸展树中根节点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	如果该伸展树不为空, 返回指向该伸展树根结点的指针; 否则返回 NULL	*/
/*	时间复杂度:	O (1)	*/
SPYNode * st_splay_tree_retrieve (const SplayTree * const pst) 
{
	if (st_splay_tree_empty (pst))
		return NULL ;
	else
		return (*pst)->root ;
}




/*	操作:	在伸展树中查找指定数据	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, pi 指向待查找数据	*/
/*	操作后:	如果该伸展树不为空 && 找到该数据, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool st_splay_tree_find (const SplayTree * const pst, const SPYItem * const pi) 
{
	splay ((*pst)->root, pi) ;
	if (*pi == (*pst)->root->item)
		return TRUE ;
	else
		return FALSE ;
}


/*	操作:	返回指向伸展树中数据域第k小结点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, k 指示待查找数据的序数	*/
/*	操作后:	如果该伸展树的大小 >= k && k > 0, 返回指向该伸展树中数据域第 k 小的结点的指针 ; 否则返回 NULL	*/
/*	时间复杂度:	O (log N)	*/
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



/*	操作:	返回指向伸展树中数据域第k大结点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, k 指示待查找数据的序数	*/
/*	操作后:	如果该伸展树的大小 >= k && k > 0, 返回指向该伸展树中数据域第 k 大的结点的指针 ; 否则返回 NULL	*/
/*	时间复杂度:	O (log N)	*/
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


/*	操作:	返回指向伸展树中最小结点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	如果该伸展树不为空, 返回指向该伸展树中最小结点的指针 ; 否则返回 NULL	*/
/*	时间复杂度:	O (log N)	*/
SPYNode * st_splay_tree_find_min (const SplayTree * const pst) 
{
	SPYNode * scan = (*pst)->root ;
	
	while (scan->left != NullNode)
		scan = scan->left ;

	return scan ;
}


/*	操作:	返回指向伸展树中最大结点的指针	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	如果该伸展树不为空, 返回指向该伸展树中最大结点的指针 ; 否则返回 NULL	*/
/*	时间复杂度:	O (log N)	*/
SPYNode * st_splay_tree_find_max (const SplayTree * const pst) 
{
	SPYNode * scan = (*pst)->root ;

	while (scan->right != NullNode)
		scan = scan->right ;

	return scan ;
}


/*	操作:	删除伸展树中数据域为指定数据的结点	*/
/*	操作前:	pst 指向一棵已初始化的伸展树, pi 指向待删除数据	*/
/*	操作后:	如果该伸展树不为空 && 找到该结点, 删除该结点, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
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


/*	操作:	以中序将一个函数依次作用于伸展树中所有结点1次	*/
/*	操作前:	pr 指向一棵已初始化的伸展树的根, pfun 指向一个没有返回值, 接受一个 SPYNode * 类型参数的函数	*/
/*	操作后:	pfun 指向的函数以中序作用于该伸展树中所有结点1次	*/
/*	时间复杂度:	O (log N)	*/
void st_splay_tree_traverse (const SPYNode * const pr, void (* pfun) (const SPYNode * const pn)) 
{
	if (pr != NullNode)
	{
		st_splay_tree_traverse (pr->left, pfun) ;
		(* pfun) (pr) ;
		st_splay_tree_traverse (pr->right, pfun) ;
	}
}


/*	操作:	释放一棵伸展树占用的内存空间	*/
/*	操作前:	pst 指向一棵已初始化的伸展树	*/
/*	操作后:	该伸展树占用的内存空间被释放	*/
/*	时间复杂度:	O (log N)	*/
void st_splay_tree_release (const SplayTree * const pst) 
{
	release ((*pst)->root) ;
	free (*pst) ;
	free (NullNode) ;
}

/*	局部函数定义	*/

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




