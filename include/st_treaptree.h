#ifndef	__ST_TREAP_TREE_H__
#define	__ST_TREAP_TREE_H__

#include "stlib.h"

ST_BEGIN_DECLS;
/* ���ƽ������� */

/*
 *	Treap����������(Sort)��һ�����ݽṹ(Data Structure)��
 *	reap��������Ҷ���ƽ������ Treap����Ϊ+ Heap������˼�壬 
 *	Treap�� BST�� Heap��������������� BSTһ�������������
 *	�����ʣ��������Ŀ�ľ���Ϊ��ά��ƽ�⡣ Treap�� BST�Ļ����ϣ�
 *	�����һ������ֵ�������� BST���ʵĻ�ͼ 5 ���ϣ�Treap�ڵ��
 *	����ֵ��������С������2����С�����ʿ��Ա�����Ϊÿ��������
 *	�ڵ㶼С�ڵ������ӽڵ㡣���ǣ� Treap���Զ���Ϊ���������ʵĶ������� 
 *	1.���������������գ��������������н���ֵ��С�����ĸ�����ֵ��
 *	�������ĸ��ڵ������ֵС�ڵ������������ڵ������ֵ�� 
 *	2. ���������������գ��������������н���ֵ���������ĸ�����ֵ��
 *	�������ĸ��ڵ������ֵС�ڵ������������ڵ������ֵ�� 
 *	3. ������������Ҳ�ֱ�Ϊ Treap��
*/
/*
ΪʲôҪ�� Treap 
(1) Treap���ص� 
1.  Treap�����׶���Treapֻ�����ֵ�����ʽ�����������������Ҽ�ʹû�����ܵ���ѧ֤���ͷ�����
	Treap�Ĺ��췽������ƽ��ԭ��Ҳ�ǲ������ġ�ֻҪ�ܹ���� BST�Ͷѵ�˼�룬��� Treap��Ȼ���ڻ��¡� 
2.  Treap���ڱ�д��Treapֻ��ά��һ��������������ֵ������ֵһ�����������޸ġ���
	�Ƚ���������ƽ������ Treapӵ�����ٵĵ�����ʽ�����������໥�ԳƵ���ת������ Treap��֮�����������ڱ�����Ե�һ��ƽ������ 
3.  Treap�ȶ��Լѡ�Treap��ƽ�����䲻�� AVL��������� SBT��ƽ���������� TreapҲ�����˻������Ա�֤���� O(logN)����ȡ�
	Treap���ȶ���ȡ����������������� 
4.  Treap�������ܵ���ѧ֤����Treap���� O(logN)����ȣ��������ܵ���ѧ֤���ġ����ⲻ�ǽ��ܵ��ص㣬�����ȥ�� 
5.  Treap�������õ�ʵ��Ч��������ʵ��Ӧ���У� Treap���ȶ��Ա��ֵ��൱��ɫ��û����Ϊ�κεĹ���������ݶ��˻���
	��������Ϣѧ�����У�����ѡ��ϰ����ʹ�� Treap����ȡ���˲��׵ı��֡� �����Ҫ����ϸ�����ϣ����Է����䡣
*/


typedef stint TRElemType;

typedef struct _TreapNode
{
	TRElemType 				Element;
	struct _TreapNode*      Left;
	struct _TreapNode*      Right;
	stint         			Priority;
}TreapNode, *Treap, *Position;

Treap st_treap_tree_destroy( Treap T );
Position st_treap_tree_find( TRElemType X, Treap T );
Position st_treap_tree_find_min( Treap T );
Position st_treap_tree_find_max( Treap T );
Treap st_treap_tree_init( void );
Treap st_treap_tree_insert( TRElemType X, Treap T );
Treap st_treap_tree_remove( TRElemType X, Treap T );
TRElemType st_treap_tree_retrieve( Position P );
void st_treap_tree_traverse( Treap T );

extern Position TRNullNode;

ST_END_DECLS ;
#endif	/* __ST_TREAP_TREE_H__ */

