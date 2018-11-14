#ifndef	__ST_BTREE_H__
#define	__ST_BTREE_H__

#include "stlib.h"
#include "st_gquene.h"

ST_BEGIN_DECLS;

///////////////////////////////////////////////////////
//                	  二叉树		                 //
///////////////////////////////////////////////////////

#define STACK_INIT_SIZE 	10				// 存储空间初始分配量 
#define STACKINCREMENT 		2				// 存储空间分配增量 
#define STClearBtree 		st_btree_destroy



//	用链表存储结构表示二叉树。
typedef char TElemType;
//	访问节点函数
typedef	stint(*VisitFunc)(TElemType e) ;
	
typedef struct _ST_BNODE
{
	TElemType data;
	struct _ST_BNODE *lchild, *rchild;		// 左右孩子指针
}ST_BNODE, *ST_BTREE;

typedef ST_BTREE QElemType; 				// 设队列元素类型为二叉树的指针类型
typedef ST_BTREE SElemType; 				// 设栈元素类型为二叉树的指针类型

#if 0			/* beacuse use st queue */
// 单链队列－－队列的链式存储结构
typedef struct _QNode
{
	QElemType data;							// 数据域
	struct _QNode *next;					// 指针域
}QNode, *QueuePtr; 


typedef struct _LinkQueue
{
	QueuePtr front ;						//队头指针，指针域指向队头元素
	QueuePtr rear;							//队尾指针，指向队尾元素
}LinkQueue;

#endif

// 栈的顺序存储表示 P46 
typedef struct _SqStack
{
	SElemType *base;						// 在栈构造之前和销毁之后，base的值为NULL 
	SElemType *top;							// 栈顶指针 
	stint stacksize;						// 当前已分配的存储空间，以元素为单位 
}SqStack;	// 顺序栈




// 构造空二叉树T 
stint st_btree_init(ST_BTREE *T) ;
// 销毁二叉树T 
void st_btree_destroy(ST_BTREE *T);
// 按先序次序输入二叉树中结点的值，构造二叉链表表示的二叉树T
// 变量Nil表示空（子）树。 
void st_btree_create(ST_BTREE *T);
// 若T为空二叉树,则返回1,否则0 
stint st_btree_empty(ST_BTREE T);
// 返回T的深度 
stint st_btree_depth(ST_BTREE T);
// 返回T的根 
TElemType st_btree_root(ST_BTREE T);
// 返回p所指结点的值
TElemType st_btree_value(ST_BTREE p);
// 给p所指结点赋值为value
void st_btree_assign(ST_BTREE p,TElemType value);
// 若e是T的非根结点,则返回它的双亲,否则返回＂空＂
TElemType st_btree_parent(ST_BTREE T,TElemType e);
// 返回二叉树T中指向元素值为s的结点的指针。
ST_BTREE st_btree_point(ST_BTREE T,TElemType s);
// 返回e的左孩子。若e无左孩子,则返回＂空＂
TElemType st_btree_left_child(ST_BTREE T,TElemType e);
// 返回e的右孩子。若e无右孩子,则返回＂空＂
TElemType st_btree_right_child(ST_BTREE T,TElemType e);
// 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂
TElemType st_btree_left_sibling(ST_BTREE T,TElemType e);
// 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂
TElemType st_btree_right_sibling(ST_BTREE T,TElemType e);
//　根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点的 
//　原有左或右子树则成为c的右子树 
stint st_btree_insert_child(ST_BTREE p, stint LR,ST_BTREE c); // 形参T无用 
// 根据LR为0或1,删除T中p所指结点的左或右子树 
stint st_btree_delete_child(ST_BTREE p, stint LR) ;
// 先序递归遍历T,对每个结点调用函数Visit一次且仅一次
void st_btree_preorder_traverse(ST_BTREE T, VisitFunc Visit);
// 先序非递归遍历T
void st_btree_preorder_traverse_iteration(ST_BTREE T, VisitFunc Visit);
// 中序递归遍历T,对每个结点调用函数Visit一次且仅一次
void st_btree_midorder_traverse(ST_BTREE T, VisitFunc Visit);
/*按照中序非递归遍历二叉树*/
void st_btree_midorder_traverse_iteration(ST_BTREE T, VisitFunc Visit) ;
// 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。 
// 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit 
stint st_btree_midorder_iter_traverse(ST_BTREE T, VisitFunc Visit);
// 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。 
// 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit 
stint st_btree_midorder_iter_traverse2(ST_BTREE T, VisitFunc Visit);
// 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 
void st_btree_posorder_traverse(ST_BTREE T, VisitFunc Visit);
/*按照后序非递归遍历二叉树*/
void st_btree_posorder_traverse_iteration(ST_BTREE T, VisitFunc Visit) ;
// 层序递归遍历T(利用队列),对每个结点调用函数Visit一次且仅一次
void st_btree_level_order_traverse(ST_BTREE T, VisitFunc Visit);
/*递归法将二叉树的左右子树互换*/
void st_btree_exchange_LR(ST_BTREE T);
/*非递归法将二叉树的左右子树互换*/
void st_btree_iteration_exchange_LR(ST_BTREE T);
/*递归法求叶子结点个数*/
stint st_btree_leaves_num(ST_BTREE T);
/*非递归法求叶子结点个数*/
stint st_btree_leaves_num_iteration(ST_BTREE T, VisitFunc Visit);


///////////////////////////////////////////////////////
//                	  二叉树查找树	                 //
///////////////////////////////////////////////////////
typedef stint BSTKeyType; 								// 设关键字域为整型 

typedef struct _BSTElemType
{
	BSTKeyType key;
	stint others;
} BSTElemType; 											// 数据元素类型 

typedef void(*VisitBST)(BSTElemType) ;					// 访问节点


// 二叉树的二叉链表存储表示 动态查找表(二叉排序树) 
typedef struct _BSTNode
{
	BSTElemType data;
	struct _BSTNode *lchild,*rchild; 					// 左右孩子指针 
}BSTNode,*BSTree;


// 构造一个空的动态查找表DT 
stint st_bstree_init(BSTree *DT) ;
//  销毁动态查找表DT 
void st_bstree_destroy(BSTree *DT);
// 在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素， 
// 若查找成功，则返回指向该数据元素结点的指针,否则返回空指针。
BSTree st_bstree_search(BSTree T,BSTKeyType key);
// 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，若查找 
// 成功，则指针p指向该数据元素结点，并返回1，否则指针p指向查找路径上 
// 访问的最后一个结点并返回0,指针f指向T的双亲，其初始调用值为NULL 
void st_bstree_search1(BSTree *T, BSTKeyType key, BSTree f, BSTree *p, stint *flag) ;
// 当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回1， 
// 否则返回0。
stint st_bstree_insert(BSTree *T, BSTElemType e);
// 从二叉排序树中删除结点p，并重接它的左或右子树。
void st_bstree_delete_node(BSTree *p);
// 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点， 
// 并返回1；否则返回0。 
stint st_bstree_delete_key(BSTree *T,BSTKeyType key);
// 按关键字的顺序对DT的每个结点调用函数Visit()一次
void st_bstree_delete_traverse(BSTree DT,VisitBST Visit);


ST_END_DECLS;
#endif	/* __ST_BTREE_H__ */
