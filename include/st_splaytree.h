#ifndef	__ST_SPLAYTREE_H__
#define	__ST_SPLAYTREE_H__
/*	 -- �Զ�������չ��ͷ�ļ�	*/
/*
 * ��չ������Ҫ�ص㣺ÿ�η���ĳ���ڵ�ʱ�����Ѵ˽ڵ���ת��������
 * ��֤�ӿ�����ʼ����M�β�����໨��O(MlogN)��ʱ�䣬Ҳ����˵����̯��ʱ��ΪO��F��N������
 */
#include "stlib.h"

ST_BEGIN_DECLS;

typedef stint SPYItem ;
typedef struct _SPYNode
{
	SPYItem item ;
	struct _SPYNode * left, * right ;
	stint leftSubTreeCount, rightSubTreeCount ;
} SPYNode ;
typedef struct _SplayTree
{
	SPYNode * root ;
	stint current ;									// count the node num
}SplayNode, * SplayTree ;

/*	ȫ�ֱ�������	*/

static SPYNode * NullNode = NULL ;

/*	�ӿں�������	*/

/*	����:	����һ����չ��, ��ʼ��Ϊ��, ����Ϊ NullNode �����ڴ�ռ�	*/
/*	����ǰ:	pst ָ��һ����չ��	*/
/*	������:	����ڴ����ɹ�, ����һ����չ��, �����ʼΪ��, ��Ϊ NullNode �����ڴ�ռ�, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool st_splay_tree_create (SplayTree * const pst) ;

/*	����:	ȷ��һ����չ���Ƿ�Ϊ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	�������չ��Ϊ��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool st_splay_tree_empty (const SplayTree * const pst) ;

/*	����:	����չ���в���һ��Ԫ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, pi ָ����������	*/
/*	������:	����ڴ����ɹ�, �����չ�������������Ϊ *pi ���½��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool st_splay_tree_insert (const SplayTree * const pst, const SPYItem * const pi) ;

/*	����:	����ָ����չ���и��ڵ��ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	�������չ����Ϊ��, ����ָ�����չ��������ָ��; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
SPYNode * st_splay_tree_retrieve (const SplayTree * const pst) ;

/*	����:	����չ���в���ָ������	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, pi ָ�����������	*/
/*	������:	�������չ����Ϊ�� && �ҵ�������, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool st_splay_tree_find (const SplayTree * const pst, const SPYItem * const pi) ;

/*	����:	����ָ����չ�����������kС����ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, k ָʾ���������ݵ�����	*/
/*	������:	�������չ���Ĵ�С >= k && k > 0, ����ָ�����չ����������� k С�Ľ���ָ�� ; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
SPYNode * st_splay_tree_find_kthmin (const SplayTree * const pst, int k) ;

/*	����:	����ָ����չ�����������k�����ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, k ָʾ���������ݵ�����	*/
/*	������:	�������չ���Ĵ�С >= k && k > 0, ����ָ�����չ����������� k ��Ľ���ָ�� ; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
SPYNode * st_splay_tree_find_kthmax (const SplayTree * const pst, int k) ;

/*	����:	����ָ����չ������С����ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	�������չ����Ϊ��, ����ָ�����չ������С����ָ�� ; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
SPYNode * st_splay_tree_find_min (const SplayTree * const pst) ;

/*	����:	����ָ����չ����������ָ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	�������չ����Ϊ��, ����ָ�����չ����������ָ�� ; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
SPYNode * st_splay_tree_find_max (const SplayTree * const pst) ;

/*	����:	ɾ����չ����������Ϊָ�����ݵĽ��	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��, pi ָ���ɾ������	*/
/*	������:	�������չ����Ϊ�� && �ҵ��ý��, ɾ���ý��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool st_splay_tree_delete (const SplayTree * const pst, const SPYItem * const pi) ;

/*	����:	������һ������������������չ�������н��1��	*/
/*	����ǰ:	pr ָ��һ���ѳ�ʼ������չ���ĸ�, pfun ָ��һ��û�з���ֵ, ����һ�� SPYNode * ���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ��������������ڸ���չ�������н��1��	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
void st_splay_tree_traverse (const SPYNode * const pr, void (* pfun) (const SPYNode * const pn)) ;

/*	����:	�ͷ�һ����չ��ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	pst ָ��һ���ѳ�ʼ������չ��	*/
/*	������:	����չ��ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
void st_splay_tree_release (const SplayTree * const pst) ;






ST_END_DECLS;
#endif	/* __ST_SPLAYTREE_H__ */

