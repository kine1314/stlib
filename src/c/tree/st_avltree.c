#include <stdio.h>
#include <malloc.h>
#include "st_avltree.h"
#include "st_log.h"


/*���ؽڵ��ƽ���*/
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

	/* һ�ε���ת�󣬸��ڵ��λ�� */
    pNode1 = pNode->pLeft;
    pNode->pLeft = pNode1->pRight;
    pNode1->pRight = pNode;

    /*����λ�ñ���, Ҫ���½��ĸ߶�ֵ*/
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

    /*����λ�ñ���, Ҫ���½��ĸ߶�ֵ*/
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

/*���ڵ����ڵ���е�AVL����*/
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


/*�������������Ӻ�ƽ��*/
AVLTree st_avltree_insert(AVLElemType nData, AVLTree pNode)
{
    if (NULL == pNode)											// ����ǿ���ֱ����ӽڵ�
    {
        pNode = (AVLTree)malloc(sizeof(AVLNode));				// �����¿ռ䣬�½ڵ���Ϊ���ڵ�
		if(NULL == pNode)
		{
			__err("alloc mem for tree failed !\n");
			exit(0);
		}
        pNode->nData = nData;
        pNode->nHeight = 0;
        pNode->pLeft = pNode->pRight = NULL;
    }
    else if (nData < pNode->nData)    								/*���뵽��������*/
    {
        pNode->pLeft = st_avltree_insert(nData, pNode->pLeft);
        if (Height(pNode->pLeft) - Height(pNode->pRight) == 2)    	/*AVL����ƽ��*/
        {
        	__msg("l[%d]\n", Height(pNode->pLeft) - Height(pNode->pRight));
            if (nData < pNode->pLeft->nData)
            {
                /*���뵽�����������, ������ת*/
                pNode = SingleRotateWithLeft(pNode);
            }
            else 
            {
                /*���뵽���������ұ�, ��˫��ת*/
                pNode = DoubleRotateWithLeft(pNode);
            }
        }
    }
    else if (nData > pNode->nData)    								/*���뵽��������*/
    {
        pNode->pRight = st_avltree_insert(nData, pNode->pRight);
        if (Height(pNode->pRight) - Height(pNode->pLeft) == 2)    	/*AVL����ƽ��*/
        {
        	__msg("r[%d]\n", Height(pNode->pRight) - Height(pNode->pLeft));
            if (nData > pNode->pRight->nData)
            {
                /*���뵽���������ұ�, ������ת*/
                pNode = SingleRotateWithRight(pNode);
            }
            else 
            {
                /*���뵽�����������, ��˫��ת*/
                pNode = DoubleRotateWithRight(pNode);
            }
        }
    }

    pNode->nHeight = MAX(Height(pNode->pLeft), Height(pNode->pRight)) + 1;

    return pNode;
}


/* ɾ���ڵ� */
AVLTree st_avltree_delete(AVLTree pRoot, AVLElemType key)
{
	if(NULL == pRoot)
		return NULL ;

	if(key == pRoot->nData)
	{
#if 0
		if(NULL == pRoot->pLeft)								/*���T���Ҷ���Ϊ����ֱ��ɾ��*/
		{
			AVLTree temp = pRoot ;
			pRoot = pRoot->pLeft ;
			free(temp) ;
		}	
		else													/*�����ҵ�T->pRight��������Ӵ���T(����T->pLeft�����Ҷ���)*/
		{
			AVLTree temp = pRoot ;
			while(temp->pLeft != NULL)
			{
                temp = temp->pLeft;
            }
			pRoot->nData = temp->nData;
            pRoot->pRight = st_avltree_delete(pRoot->pRight, temp->nData);      /*����������T��������ӽڵ����һЩ�е����������ٴεݹ鵽T->pRight��������ӣ�ɾ����*/
            pRoot->nHeight = MAX(Height(pRoot->pLeft), Height(pRoot->pRight)) + 1;
			free(temp) ;
		}
		return pRoot ;
#else

		AVLTree q, s;
		// ����������ֻ���ؽ���������������ɾ�����Ҷ��Ҳ�ߴ˷�֧��
		if(NULL == (pRoot)->pRight) 
		{
			q = pRoot;
			pRoot = (pRoot)->pLeft;
			free(q);
		}
		else if(NULL == (pRoot)->pLeft) 					// ֻ���ؽ����������� 
		{
			q = pRoot;
			pRoot = (pRoot)->pRight;
			free(q);
		}
		else 												// �������������� 
		{
			q = pRoot;
			s = (pRoot)->pLeft;
			while(s->pRight) 								// ת��Ȼ�����ҵ���ͷ���Ҵ�ɾ����ǰ���� 
			{
				q = s;										// ��ʱ����s�ڵ�
				s = s->pRight;
			}
			// sָ��ɾ���ģ�ǰ����������ɾ���ǰ����ֵȡ����ɾ����ֵ��
			(pRoot)->nData = s->nData; 
			if(q != pRoot)
				q->pRight = s->pLeft; 						// �ؽ�*q�������� 
			else
				q->pLeft = s->pLeft; 						// �ؽ�*q�������� 
			free(s);
			s->pLeft = s->pRight = NULL ;
			s = NULL ;
		}
		return pRoot ;
#endif
	}
	else if(key < pRoot->nData)
	{
        pRoot->pLeft = st_avltree_delete(pRoot->pLeft, key);					/* Ѱ��������ɾ�� */
    }
	else
	{
        pRoot->pRight = st_avltree_delete(pRoot->pRight, key);					/* Ѱ��������ɾ�� */
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
 *���Ҳ������ҵ�����1�����򣬷���0
 *data�Ǵ����ҵ�����
 *pRoot:avl����ָ��
 */
stint st_avltree_find(AVLElemType data, AVLTree pRoot)
{
    static stint k=1;    										/*���Ҵ���*/
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

/*ɾ����*/
void st_avltree_destroy(AVLTree* ppRoot)
{
    if (NULL == ppRoot || NULL == *ppRoot)
        return;

    st_avltree_destroy(&((*ppRoot)->pLeft));
    st_avltree_destroy(&((*ppRoot)->pRight));
    free(*ppRoot);
    *ppRoot = NULL;
}

/*���������ӡ�������н��, ��Ϊ���� < ����� < �ҽ��, ��˴�ӡ�������ݵĴ�С�ǵ�����*/
void st_avltree_traverse(AVLTree pRoot)
{
	static stint n = 0;

    if (NULL == pRoot)
        return;


    st_avltree_traverse(pRoot->pLeft);
    printf("[%d]nData = %u, [%d]\n", ++n, pRoot->nData, pRoot->nHeight);
    st_avltree_traverse(pRoot->pRight);
}



