#ifndef	__ST_RBTREE_H__
#define	__ST_RBTREE_H__

#include "stlib.h"

/**
 * 1) ÿһ���ڵ�����ź�ɫ,�����ųɺ�ɫ.�0�2
 * 2) ���Ǻ�ɫ�ā0�2
 * 3) ���һ���ڵ��Ǻ�ɫ��,��ô�����ӽڵ�����Ǻ�ɫ��.�0�2
 * 4) ��һ���ڵ㵽һ��NULLָ���ÿһ��·�����������ͬ��Ŀ�ĺ�ɫ�ڵ�
 * */

ST_BEGIN_DECLS;
/*	���Գ�������	*/
#define INFINITY (~(1 << 31))
#define NEGATIVE_INFINITY (1 << 31)

/*	�������Ͷ���	*/

typedef enum colorType {Red, Black} ColorType ;
typedef stint RBItem ;
typedef struct _RBNode
{
	RBItem item ;
	struct _RBNode * left, * right ;
	ColorType color ;
} RBNode ;
typedef struct _RBTree
{
	RBNode * root ;
	stint current ;				// the count of tree node ;
}RBTree, *pRBTree ;

/*	ȫ�ֱ�������	*/

static RBNode * RBNullNode = NULL ;
RBNode * Current, * Sibling, * Parent, * GrParent, * GrGrParent ;

/*	�ӿں�������	*/

/*	����:	��������ʼ��һ�ú������Ϊ RBNullNode �����ڴ�ռ�	*/
/*	����ǰ:	prbt ָ��һ�ú����	*/
/*	������:	����ڴ����ɹ�, �ú��������ʼ��Ϊ��, Ϊ RBNullNode �����ڴ�ռ�, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool st_rbtree_create (pRBTree * const prbt) ;

/*	����:	ȷ��һ�ú�����Ƿ�Ϊ��	*/
/*	����ǰ:	prbt ָ��һ���ѳ�ʼ���ĺ����	*/
/*	������:	����ú����Ϊ��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool st_rbtree_empty (const pRBTree * const prbt) ;

/*	����:	�������в���һ�����	*/
/*	����ǰ:	prbt ָ��һ���ѳ�ʼ���ĺ����, item �Ǵ��������	*/
/*	������:	����ڴ����ɹ� && item ֮ǰ�������ڸú������, ��ú���������1��������Ϊ item �Ľ��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool st_rbtree_insert (pRBTree * const prbt, const RBItem item) ;

/*	����:	�Ӻ������ɾ��һ�����	*/
/*	����ǰ:	prbt ָ��һ���ѳ�ʼ���ĺ����, item �Ǵ�ɾ������	*/
/*	������:	����ҵ��ý��, ɾ����, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool st_rbtree_delete (pRBTree * const prbt, const RBItem item) ;

/*	����:	��һ�����������������ں���������н��1��	*/
/*	����ǰ:	prbt ָ��һ���ѳ�ʼ���ĺ����, pfun ָ��һ��û�з���ֵ, ����һ�� RBNode * ���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ��������������������ڸú���������н��1��	*/
/*	ʱ�临�Ӷ�:	O (N)	*/
void st_rbtree_traverse (const pRBTree * const prbt, void (* pfun) (const RBNode * const pn)) ;

/*	����:	�ͷ�һ�ú����ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	prbt ָ��һ���ѳ�ʼ���ĺ����	*/
/*	������:	�ú����ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O (N)	*/
void st_rbtree_release (const pRBTree * const prbt) ;


// complete the down2up RBTREE ;
typedef stint RBKey_t;
typedef stint data_t;

typedef enum color_t
{
    RED = 0,
    BLACK = 1
}color_t;

typedef struct rb_node_t
{
    struct rb_node_t *left, *right, *parent;
    RBKey_t key;				// this is the value
    data_t data;			// the index
    color_t color;
}rb_node_t;

/* forward declaration */

rb_node_t* st_rbt_insert(RBKey_t key, data_t data, rb_node_t* root);

rb_node_t* st_rbt_search(RBKey_t key, rb_node_t* root);

rb_node_t* st_rbt_erase(RBKey_t key, rb_node_t* root);

void	rb_traverse(rb_node_t* root);




ST_END_DECLS;
#endif	/* __ST_RBTREE_H__ */

