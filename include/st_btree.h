#ifndef	__ST_BTREE_H__
#define	__ST_BTREE_H__

#include "stlib.h"
#include "st_gquene.h"

ST_BEGIN_DECLS;

///////////////////////////////////////////////////////
//                	  ������		                 //
///////////////////////////////////////////////////////

#define STACK_INIT_SIZE 	10				// �洢�ռ��ʼ������ 
#define STACKINCREMENT 		2				// �洢�ռ�������� 
#define STClearBtree 		st_btree_destroy



//	������洢�ṹ��ʾ��������
typedef char TElemType;
//	���ʽڵ㺯��
typedef	stint(*VisitFunc)(TElemType e) ;
	
typedef struct _ST_BNODE
{
	TElemType data;
	struct _ST_BNODE *lchild, *rchild;		// ���Һ���ָ��
}ST_BNODE, *ST_BTREE;

typedef ST_BTREE QElemType; 				// �����Ԫ������Ϊ��������ָ������
typedef ST_BTREE SElemType; 				// ��ջԪ������Ϊ��������ָ������

#if 0			/* beacuse use st queue */
// �������У������е���ʽ�洢�ṹ
typedef struct _QNode
{
	QElemType data;							// ������
	struct _QNode *next;					// ָ����
}QNode, *QueuePtr; 


typedef struct _LinkQueue
{
	QueuePtr front ;						//��ͷָ�룬ָ����ָ���ͷԪ��
	QueuePtr rear;							//��βָ�룬ָ���βԪ��
}LinkQueue;

#endif

// ջ��˳��洢��ʾ P46 
typedef struct _SqStack
{
	SElemType *base;						// ��ջ����֮ǰ������֮��base��ֵΪNULL 
	SElemType *top;							// ջ��ָ�� 
	stint stacksize;						// ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
}SqStack;	// ˳��ջ




// ����ն�����T 
stint st_btree_init(ST_BTREE *T) ;
// ���ٶ�����T 
void st_btree_destroy(ST_BTREE *T);
// �������������������н���ֵ��������������ʾ�Ķ�����T
// ����Nil��ʾ�գ��ӣ����� 
void st_btree_create(ST_BTREE *T);
// ��TΪ�ն�����,�򷵻�1,����0 
stint st_btree_empty(ST_BTREE T);
// ����T����� 
stint st_btree_depth(ST_BTREE T);
// ����T�ĸ� 
TElemType st_btree_root(ST_BTREE T);
// ����p��ָ����ֵ
TElemType st_btree_value(ST_BTREE p);
// ��p��ָ��㸳ֵΪvalue
void st_btree_assign(ST_BTREE p,TElemType value);
// ��e��T�ķǸ����,�򷵻�����˫��,���򷵻أ��գ�
TElemType st_btree_parent(ST_BTREE T,TElemType e);
// ���ض�����T��ָ��Ԫ��ֵΪs�Ľ���ָ�롣
ST_BTREE st_btree_point(ST_BTREE T,TElemType s);
// ����e�����ӡ���e������,�򷵻أ��գ�
TElemType st_btree_left_child(ST_BTREE T,TElemType e);
// ����e���Һ��ӡ���e���Һ���,�򷵻أ��գ�
TElemType st_btree_right_child(ST_BTREE T,TElemType e);
// ����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ�
TElemType st_btree_left_sibling(ST_BTREE T,TElemType e);
// ����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ�
TElemType st_btree_right_sibling(ST_BTREE T,TElemType e);
//������LRΪ0��1,����cΪT��p��ָ���������������p��ָ���� 
//��ԭ��������������Ϊc�������� 
stint st_btree_insert_child(ST_BTREE p, stint LR,ST_BTREE c); // �β�T���� 
// ����LRΪ0��1,ɾ��T��p��ָ������������� 
stint st_btree_delete_child(ST_BTREE p, stint LR) ;
// ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ��
void st_btree_preorder_traverse(ST_BTREE T, VisitFunc Visit);
// ����ǵݹ����T
void st_btree_preorder_traverse_iteration(ST_BTREE T, VisitFunc Visit);
// ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ��
void st_btree_midorder_traverse(ST_BTREE T, VisitFunc Visit);
/*��������ǵݹ����������*/
void st_btree_midorder_traverse_iteration(ST_BTREE T, VisitFunc Visit) ;
// ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú����� 
// �������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���Visit 
stint st_btree_midorder_iter_traverse(ST_BTREE T, VisitFunc Visit);
// ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú����� 
// �������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���Visit 
stint st_btree_midorder_iter_traverse2(ST_BTREE T, VisitFunc Visit);
// ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� 
void st_btree_posorder_traverse(ST_BTREE T, VisitFunc Visit);
/*���պ���ǵݹ����������*/
void st_btree_posorder_traverse_iteration(ST_BTREE T, VisitFunc Visit) ;
// ����ݹ����T(���ö���),��ÿ�������ú���Visitһ���ҽ�һ��
void st_btree_level_order_traverse(ST_BTREE T, VisitFunc Visit);
/*�ݹ鷨����������������������*/
void st_btree_exchange_LR(ST_BTREE T);
/*�ǵݹ鷨����������������������*/
void st_btree_iteration_exchange_LR(ST_BTREE T);
/*�ݹ鷨��Ҷ�ӽ�����*/
stint st_btree_leaves_num(ST_BTREE T);
/*�ǵݹ鷨��Ҷ�ӽ�����*/
stint st_btree_leaves_num_iteration(ST_BTREE T, VisitFunc Visit);


///////////////////////////////////////////////////////
//                	  ������������	                 //
///////////////////////////////////////////////////////
typedef stint BSTKeyType; 								// ��ؼ�����Ϊ���� 

typedef struct _BSTElemType
{
	BSTKeyType key;
	stint others;
} BSTElemType; 											// ����Ԫ������ 

typedef void(*VisitBST)(BSTElemType) ;					// ���ʽڵ�


// �������Ķ�������洢��ʾ ��̬���ұ�(����������) 
typedef struct _BSTNode
{
	BSTElemType data;
	struct _BSTNode *lchild,*rchild; 					// ���Һ���ָ�� 
}BSTNode,*BSTree;


// ����һ���յĶ�̬���ұ�DT 
stint st_bstree_init(BSTree *DT) ;
//  ���ٶ�̬���ұ�DT 
void st_bstree_destroy(BSTree *DT);
// �ڸ�ָ��T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ�أ� 
// �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ��,���򷵻ؿ�ָ�롣
BSTree st_bstree_search(BSTree T,BSTKeyType key);
// �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ������� 
// �ɹ�����ָ��pָ�������Ԫ�ؽ�㣬������1������ָ��pָ�����·���� 
// ���ʵ����һ����㲢����0,ָ��fָ��T��˫�ף����ʼ����ֵΪNULL 
void st_bstree_search1(BSTree *T, BSTKeyType key, BSTree f, BSTree *p, stint *flag) ;
// ������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ������e������1�� 
// ���򷵻�0��
stint st_bstree_insert(BSTree *T, BSTElemType e);
// �Ӷ�����������ɾ�����p�����ؽ����������������
void st_bstree_delete_node(BSTree *p);
// ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ�㣬 
// ������1�����򷵻�0�� 
stint st_bstree_delete_key(BSTree *T,BSTKeyType key);
// ���ؼ��ֵ�˳���DT��ÿ�������ú���Visit()һ��
void st_bstree_delete_traverse(BSTree DT,VisitBST Visit);


ST_END_DECLS;
#endif	/* __ST_BTREE_H__ */
