#ifndef	__ST_AVLTREE_H__
#define	__ST_AVLTREE_H__

#include "stlib.h"

ST_BEGIN_DECLS;
/*
����: 
1>һ��n������AVL������߶ȱ�����0(log2(n)),���ᳬ��3/2log2(n+1) 
2>һ��n������AVL����ƽ���������ȱ�����0(log2(n)). 
3>һ��n������AVL��ɾ��һ�������ƽ�⻯��ת����Ҫ��ʱ��Ϊ0(log2(n)). 
*/

typedef stint AVLElemType;

typedef struct _AVLNode
{
    AVLElemType nData;				/*�洢����*/
    struct _AVLNode* pLeft;			/*ָ��������*/
    struct _AVLNode* pRight;		/*ָ��������*/
    stint nHeight;					/*����ƽ���*/
}AVLNode, *AVLTree;

/*�������*/
AVLTree st_avltree_insert(AVLElemType nData, AVLTree pNode);

/* ɾ���ڵ� */
AVLTree st_avltree_delete(AVLTree pRoot, AVLElemType key);

/*���Ҳ������ҵ�����1�����򣬷���0*/
stint st_avltree_find(AVLElemType data, AVLTree pRoot);

/*ɾ������,ɾ�����нڵ�*/
void st_avltree_destroy(AVLTree* ppRoot);

/*��ӡ����*/
void st_avltree_traverse(AVLTree pRoot);



ST_END_DECLS;
#endif	/* __ST_AVLTREE_H__ */

