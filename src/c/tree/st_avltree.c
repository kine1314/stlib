#include <stdio.h>
#include <malloc.h>
#include "st_avltree.h"
#include "st_log.h"


/*返回节点的平衡度*/
static stint Height(AVLTree pNode)
{
    if (NULL == pNode)
        return -1;

    return pNode->nHeight;
}

/********************************************************************
      pNode pNode->pLeft 
      / \
  pNode->pLeft ==> pNode
      \     /
  pNode->pLeft->pRight pNode->pLeft->pRight
 *********************************************************************/
static AVLTree SingleRotateWithLeft(AVLTree pNode)
{
    AVLTree pNode1;

	/* 一次单旋转后，各节点的位置 */
    pNode1 = pNode->pLeft;
    pNode->pLeft = pNode1->pRight;
    pNode1->pRight = pNode;

    /*结点的位置变了, 要更新结点的高度值*/
    pNode->nHeight = MAX(Height(pNode->pLeft), Height(pNode->pRight)) + 1;
    pNode1->nHeight = MAX(Height(pNode1->pLeft), pNode->nHeight) + 1;
	//printf("!!!!!!!![%d], [%d]\n", pNode->nHeight, pNode1->nHeight) ;

    return pNode1;
}


/********************************************************************
  pNode pNode->pRight
  \ /
  pNode->pRight ==> pNode 
  / \
  pNode->pRight->pLeft pNode->pRight->pLeft
 *********************************************************************/
static AVLTree SingleRotateWithRight(AVLTree pNode)
{
    AVLTree pNode1;

    pNode1 = pNode->pRight;
    pNode->pRight = pNode1->pLeft;
    pNode1->pLeft = pNode;

    /*结点的位置变了, 要更新结点的高度值*/
    pNode->nHeight = MAX(Height(pNode->pLeft), Height(pNode->pRight)) + 1;
    pNode1->nHeight = MAX(Height(pNode1->pRight), pNode->nHeight) + 1;

    return pNode1;
}


static AVLTree DoubleRotateWithLeft(AVLTree pNode)
{
    pNode->pLeft = SingleRotateWithRight(pNode->pLeft);

    return SingleRotateWithLeft(pNode);
}

static AVLTree DoubleRotateWithRight(AVLTree pNode)
{
    pNode->pRight = SingleRotateWithLeft(pNode->pRight);

    return SingleRotateWithRight(pNode);
}	

/*对于单个节点进行的AVL调整*/
static AVLTree Rotate(AVLTree T)
{              
    if(Height(T->pLeft) - Height(T->pRight) == 2){
        if(Height(T->pLeft->pLeft) >= Height(T->pLeft->pRight)){
            T = SingleRotateWithLeft(T);
        }
        else{
            T = DoubleRotateWithLeft(T);
        }
    }
    if(Height(T->pRight) - Height(T->pLeft) ==2){
        if(Height(T->pRight->pRight) >= Height(T->pRight->pLeft)){
            T = SingleRotateWithRight(T);
        }
        else{
            T = DoubleRotateWithRight(T);
        }
    }
    return T;
}


/*插入操作，先添加后平衡*/
AVLTree st_avltree_insert(AVLElemType nData, AVLTree pNode)
{
    if (NULL == pNode)											// 如果是空树直接天加节点
    {
        pNode = (AVLTree)malloc(sizeof(AVLNode));				// 分配新空间，新节点作为根节点
		if(NULL == pNode)
		{
			__err("alloc mem for tree failed !\n");
			exit(0);
		}
        pNode->nData = nData;
        pNode->nHeight = 0;
        pNode->pLeft = pNode->pRight = NULL;
    }
    else if (nData < pNode->nData)    								/*插入到左子树中*/
    {
        pNode->pLeft = st_avltree_insert(nData, pNode->pLeft);
        if (Height(pNode->pLeft) - Height(pNode->pRight) == 2)    	/*AVL树不平衡*/
        {
        	__msg("l[%d]\n", Height(pNode->pLeft) - Height(pNode->pRight));
            if (nData < pNode->pLeft->nData)
            {
                /*插入到了左子树左边, 做单旋转*/
                pNode = SingleRotateWithLeft(pNode);
            }
            else 
            {
                /*插入到了左子树右边, 做双旋转*/
                pNode = DoubleRotateWithLeft(pNode);
            }
        }
    }
    else if (nData > pNode->nData)    								/*插入到右子树中*/
    {
        pNode->pRight = st_avltree_insert(nData, pNode->pRight);
        if (Height(pNode->pRight) - Height(pNode->pLeft) == 2)    	/*AVL树不平衡*/
        {
        	__msg("r[%d]\n", Height(pNode->pRight) - Height(pNode->pLeft));
            if (nData > pNode->pRight->nData)
            {
                /*插入到了右子树右边, 做单旋转*/
                pNode = SingleRotateWithRight(pNode);
            }
            else 
            {
                /*插入到了右子树左边, 做双旋转*/
                pNode = DoubleRotateWithRight(pNode);
            }
        }
    }

    pNode->nHeight = MAX(Height(pNode->pLeft), Height(pNode->pRight)) + 1;

    return pNode;
}


/* 删除节点 */
AVLTree st_avltree_delete(AVLTree pRoot, AVLElemType key)
{
	if(NULL == pRoot)
		return NULL ;

	if(key == pRoot->nData)
	{
#if 0
		if(NULL == pRoot->pLeft)								/*如果T得右儿子为空则直接删除*/
		{
			AVLTree temp = pRoot ;
			pRoot = pRoot->pLeft ;
			free(temp) ;
		}	
		else													/*否则找到T->pRight的最左儿子代替T(或者T->pLeft的最右儿子)*/
		{
			AVLTree temp = pRoot ;
			while(temp->pLeft != NULL)
			{
                temp = temp->pLeft;
            }
			pRoot->nData = temp->nData;
            pRoot->pRight = st_avltree_delete(pRoot->pRight, temp->nData);      /*对于替代后的T及其各个子节点进行一些列调整，正到再次递归到T->pRight的最左儿子，删除它*/
            pRoot->nHeight = MAX(Height(pRoot->pLeft), Height(pRoot->pRight)) + 1;
			free(temp) ;
		}
		return pRoot ;
#else

		AVLTree q, s;
		// 右子树空则只需重接它的左子树（待删结点是叶子也走此分支）
		if(NULL == (pRoot)->pRight) 
		{
			q = pRoot;
			pRoot = (pRoot)->pLeft;
			free(q);
		}
		else if(NULL == (pRoot)->pLeft) 					// 只需重接它的右子树 
		{
			q = pRoot;
			pRoot = (pRoot)->pRight;
			free(q);
		}
		else 												// 左右子树均不空 
		{
			q = pRoot;
			s = (pRoot)->pLeft;
			while(s->pRight) 								// 转左，然后向右到尽头（找待删结点的前驱） 
			{
				q = s;										// 临时保存s节点
				s = s->pRight;
			}
			// s指向被删结点的＂前驱＂（将被删结点前驱的值取代被删结点的值）
			(pRoot)->nData = s->nData; 
			if(q != pRoot)
				q->pRight = s->pLeft; 						// 重接*q的右子树 
			else
				q->pLeft = s->pLeft; 						// 重接*q的左子树 
			free(s);
			s->pLeft = s->pRight = NULL ;
			s = NULL ;
		}
		return pRoot ;
#endif
	}
	else if(key < pRoot->nData)
	{
        pRoot->pLeft = st_avltree_delete(pRoot->pLeft, key);					/* 寻找左子树删除 */
    }
	else
	{
        pRoot->pRight = st_avltree_delete(pRoot->pRight, key);					/* 寻找右子树删除 */
    }
	//;//__msg("~~~~~~\n");
	pRoot->nHeight = MAX(Height(pRoot->pLeft), Height(pRoot->pRight)) + 1;
    if(pRoot->pLeft != NULL){
        pRoot->pLeft = Rotate(pRoot->pLeft);
    }
    if(pRoot->pRight != NULL){
        pRoot->pRight = Rotate(pRoot->pRight);
    }
    pRoot = Rotate(pRoot);

	//pRoot->nHeight = MAX(Height(pRoot->pLeft), Height(pRoot->pRight)) - 1;
    return pRoot;
	
}

/*
 *查找操作，找到返回1，否则，返回0
 *data是待查找的数据
 *pRoot:avl树的指针
 */
stint st_avltree_find(AVLElemType data, AVLTree pRoot)
{
    static stint k=1;    										/*查找次数*/
    if (NULL == pRoot)
    {
        __err("not find %d times\n", k);
        return 0;
    }

    if(data == pRoot->nData)
    {
        __err("find:%d times\n", k);
        return 1;
    }
    else if(data < pRoot->nData)
    {
        ++k;
        return st_avltree_find(data, pRoot->pLeft);
    }
    else if(data > pRoot->nData)
    {
        ++k;
        return st_avltree_find(data, pRoot->pRight);
    }
}

/*删除树*/
void st_avltree_destroy(AVLTree* ppRoot)
{
    if (NULL == ppRoot || NULL == *ppRoot)
        return;

    st_avltree_destroy(&((*ppRoot)->pLeft));
    st_avltree_destroy(&((*ppRoot)->pRight));
    free(*ppRoot);
    *ppRoot = NULL;
}

/*中序遍历打印树的所有结点, 因为左结点 < 父结点 < 右结点, 因此打印出来数据的大小是递增的*/
void st_avltree_traverse(AVLTree pRoot)
{
	static stint n = 0;

    if (NULL == pRoot)
        return;


    st_avltree_traverse(pRoot->pLeft);
    printf("[%d]nData = %u, [%d]\n", ++n, pRoot->nData, pRoot->nHeight);
    st_avltree_traverse(pRoot->pRight);
}



