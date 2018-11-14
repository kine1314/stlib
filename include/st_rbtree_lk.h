#ifndef	__ST_RBTREE_LK_H__
#define	__ST_RBTREE_LK_H__
#include "stlib.h"
ST_BEGIN_DECLS;

/**
 * �������ƽ���������һ�֣����кܺõ����ʣ����еĽ�㶼������ģ�������Ϊ���������
 * ƽ��ģ����Բ���Ҳ������ַǳ����ӵ���������ڶ������Ĳ�����ʱ�临�Ӷ���O(log(N))��
 * Linux�ں��ڹ���vm_area_structʱ���ǲ����˺������ά���ڴ��ġ�
 **/

struct _rb_node
{
	unsigned long  rb_parent_color;				// TODO:���׽ڵ����ɫ
#define	RB_RED		0
#define	RB_BLACK	1
	struct _rb_node *rb_right;
	struct _rb_node *rb_left;
}
#if !defined(WIN32)
__attribute__((aligned(sizeof(long))))		/* aligned with long */
#endif
;
    /* The alignment might seem pointless, but allegedly CRIS needs it */

/**
 * struct rb_rootֻ��struct _rb_node*��һ����װ���������ĺô��ǿ���������
 * ���ݶ���ָ���ˡ������ܼ򵥡��ٿ�һ�����漸����Ҫ�ĺ꣬ϸ�ĵ���һ���ᷢ�֣�
 * rb_parent_color��ʵû��ô�򵥣�Andrea Arcangeli������ʹ����һ��С�ļ�
 * �ɣ������ǳ�����������������ʾ�������Ա��ʵ����ָ��parent��ָ��ʹ˽���
 * ��ɫ��������ô�������أ��ܼ򵥣������������á���Ȼ��sizeof(long)��С�Ķ��룬
 * ��ô��IA-32�ϣ��κ�rb_node�ṹ��ĵ�ַ�ĵ���λ�϶������㣬������Ų��ã�
 * �����������Ǳ�ʾ��ɫ��������ɫ�����֣���ʵһλ���Ѿ����ˡ�
 * */
struct _rb_root
{
	struct _rb_node *rb_node;
};

/*��������ȡparentָ��ֻҪ��rb_parent_color��Ա�ĵ���λ���㼴�ɣ�*/
#define rb_parent(r)   ((struct _rb_node *)((r)->rb_parent_color & ~3))
/*ȡ��ɫֻҪ�����һλ���ɣ�*/
#define rb_color(r)   ((r)->rb_parent_color & 1)
#define rb_is_red(r)   (!rb_color(r))
#define rb_is_black(r) rb_color(r)
#define rb_set_red(r)  do { (r)->rb_parent_color &= ~1; } while (0)
#define rb_set_black(r)  do { (r)->rb_parent_color |= 1; } while (0)


static stinline void rb_set_parent(struct _rb_node *rb, struct _rb_node *p)
{
	rb->rb_parent_color = (rb->rb_parent_color & 3) | (unsigned long)p;
}
static stinline void rb_set_color(struct _rb_node *rb, int color)
{
	rb->rb_parent_color = (rb->rb_parent_color & ~1) | color;
}

#define RB_ROOT	(struct _rb_root) { NULL, }
#define	rb_entry(ptr, type, member) container_of(ptr, type, member)

#define RB_EMPTY_ROOT(root)	((root)->rb_node == NULL)
#define RB_EMPTY_NODE(node)	(rb_parent(node) == node)
#define RB_CLEAR_NODE(node)	(rb_set_parent(node, node))


/**
 * __rb_rotate_left�ǰ���rootΪ�������е�node������������
 * __rb_rotate_right�ǽ���������������������Ϊ����Ĳ����
 * ɾ�����񣬶�����Ϊ�ⲿ�ṩ�ӿڡ� 
 */

/**
 * ����Ľ�㶼��ΪҶ�ӣ�Ⱦ�ɺ�ɫ�����������ƻ�����������ͨ
 * ��������ɫ����ת���Իָ���������������ƽ�⡣��������Ľӿں����� 
 */
/**
 * ������ȷ��������node������뵽��rootΪ���ĺ�����У������㷨
 * �ķ������Բο�[1]�е�14.3�ڣ������ʵ�ֺ����еĽ��⼸����ȫһ����
 * ��ôȷ��node�ĸ����Ӧ���ڵ���rb_insert_color֮ǰͨ���ֹ�����
 * ��ɡ�ֵ��ָ����һ���ǣ���Ȼ���������Ҫһ��ѭ�������������ܵ���ת
 * �������ᳬ�����Σ�����Ч�ʻ��Ǻ��ֹ۵ġ�
 * */
extern void rb_insert_color(struct _rb_node *, struct _rb_root *);

/**
 * ɾ������������ٶ��е��鷳����Ҫ��ִ������ͨ����������ġ�ɾ������
 * Ȼ�����ɾ��������ɫ���ж��Ƿ�ִ�н�һ���Ĳ�����ɾ���Ľӿ��ǣ�
 * ��ʵ����û������ɾ��node����ֻ����������rootΪ�����������ϵ��
 * �������Ҫ�ж��Ƿ����__rb_erase_color��������
 * */
extern void rb_erase(struct _rb_node *, struct _rb_root *);

/* Find logical next and previous nodes in a tree */
/**
 * ����node�����еĺ�̣������΢����һ�㡣���node���Һ��Ӳ�Ϊ�գ�
 * ��ֻҪ����node������������С�Ľ�㼴�ɣ����Ϊ�գ���Ҫ���ϲ��ң�
 * �ҵ�����������丸�׵����ӵĽ�㣬���ظ���㡣���һֱ�������˸���㣬����NULL��
 * */
extern struct _rb_node *rb_next(const struct _rb_node *);
/*����node��ǰ������rb_next�еĲ����Գơ�*/
extern struct _rb_node *rb_prev(const struct _rb_node *);
/*����rootΪ���������ҳ���������С���Ǹ���㣬ֻҪ�Ӹ����һֱ�����߾����ˡ�*/
extern struct _rb_node *rb_first(const struct _rb_root *);
/*���ҳ������������Ǹ���һֱ�����ߡ�*/
extern struct _rb_node *rb_last(const struct _rb_root *);

/* Fast replacement of a single node without remove/rebalance/add/rebalance */
/*��new�滻��rootΪ�������е�victim��㡣*/
extern void rb_replace_node(struct _rb_node *victim, struct _rb_node *new, 
			    struct _rb_root *root);

/*������ɫ��������ɫҲ��ˮ�����ɵ����ˡ���Ҫ�ر�ָ�����������һ������������ */
/**
 * ����parent��Ϊnode�ĸ���㣬������rb_linkָ��node�� 
 * ���ǰ��ص㼯����lib/rbtree.c�ϣ�����һЩ�ͺ������ص���Ҫ�㷨����ʼ֮ǰ����һ�����һ�º�����Ĺ��� 
 * 1. ÿ�����Ҫô�Ǻ�ɫҪô�Ǻ�ɫ�� 
 * 2. ���������Ǻ�ɫ�� 
 * 3. ��������к��ӣ��亢�ӱ��붼�Ǻ�ɫ�� 
 * 4. �Ӹ���㵽Ҷ�ӵ�ÿ��·�����������ͬ��Ŀ�ĺڽ�㡣 
 * �����������������һ����������ƽ��ġ� 
 * */
static stinline void rb_link_node(struct _rb_node * node, struct _rb_node * parent,
				struct _rb_node ** rb_link)
{
	node->rb_parent_color = (unsigned long )parent;
	node->rb_left = node->rb_right = NULL;

	*rb_link = node;
}



ST_END_DECLS;
#endif	/* __ST_RBTREE_LK_H__ */


