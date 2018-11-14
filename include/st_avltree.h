#ifndef	__ST_AVLTREE_H__
#define	__ST_AVLTREE_H__

#include "stlib.h"

ST_BEGIN_DECLS;
/*
性质: 
1>一棵n个结点的AVL树的其高度保持在0(log2(n)),不会超过3/2log2(n+1) 
2>一棵n个结点的AVL树的平均搜索长度保持在0(log2(n)). 
3>一棵n个结点的AVL树删除一个结点做平衡化旋转所需要的时间为0(log2(n)). 
*/

typedef stint AVLElemType;

typedef struct _AVLNode
{
    AVLElemType nData;				/*存储数据*/
    struct _AVLNode* pLeft;			/*指向左子树*/
    struct _AVLNode* pRight;		/*指向右子树*/
    stint nHeight;					/*树的平衡度*/
}AVLNode, *AVLTree;

/*插入操作*/
AVLTree st_avltree_insert(AVLElemType nData, AVLTree pNode);

/* 删除节点 */
AVLTree st_avltree_delete(AVLTree pRoot, AVLElemType key);

/*查找操作，找到返回1，否则，返回0*/
stint st_avltree_find(AVLElemType data, AVLTree pRoot);

/*删除操作,删除所有节点*/
void st_avltree_destroy(AVLTree* ppRoot);

/*打印操作*/
void st_avltree_traverse(AVLTree pRoot);



ST_END_DECLS;
#endif	/* __ST_AVLTREE_H__ */

