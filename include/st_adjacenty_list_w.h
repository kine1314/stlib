#ifndef	__ST_ADJACENTY_LIST_W_H__
#define	__ST_ADJACENTY_LIST_W_H__

#include "stlib.h"

ST_BEGIN_DECLS ;

/*	st_adjacenty_list_w.h -- �洢��Ȩͼ�ڽӱ�ͷ�ļ�	*/

#include <stdarg.h>

#include "st_graph_common.h"

#define INFINITY (~(1 << 31))
#define NEGATIVEINFINITY (-INFINITY - 1)

/*	�������Ͷ���	*/
typedef char ADJLWName ;
typedef struct adjoin_to_vertex
{
	int hash_value ;
	int cvw ;
	struct adjoin_to_vertex * next ;
} Adjoin_To_Vertex ;
typedef struct vertex_w
{
	int hash_value ;
	int known ;
	int dist ;
	int weight ;
	ADJLWName path ;
	Adjoin_To_Vertex * adjoin_to ;
} Vertex_w ;
typedef struct adjacenty_list_w
{
	Vertex_w * list ;
	int * indegree ;
	int capacity ;
} * Adjacenty_List_w ;

/*	�ӿں�������	*/

/*	����:	����һ���ڽӱ�	*/
/*	����ǰ:	padj ָ��һ���ڽӱ�, capacity ָʾ�ڽӱ�Ĵ�С	*/
/*	������:	��� capacity > 0 && �ڴ����ɹ�, �������ڽӱ�, ���� 1; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int Initialize_A_W (Adjacenty_List_w * const padj, const int capacity) ;

/*	����:	��ʼ���ڽӱ��ĳһ��	*/
/*	����ǰ:	padj ָ��һ���ѳ�ʼ�����ڽӱ�, pht ָ��һ���ѳ�ʼ����ɢ�б�, index ָʾ�е�����, name ָʾ��������, indegree ָʾ�������, sub ָʾ�����ĸ���, ... �������ָʾ�ڽӵ��ö���Ķ������ֺͶ��㵽�ö��㹹�ɵıߵ�Ȩ	*/
/*	������:	��� index �ǺϷ������� && indegree >= 0 && sub >= 0, ���б����ղ�����ʼ��, ���� 1; ���򷵻� 0	*/
/*	ʱ�临�Ӷ�:	O(V)	*/
int InitializeALine_A_W (Adjacenty_List_w * const padj, const struct Ghash_table ** const pht, const int index, const ADJLWName name, const int indegree, const int sub, ...) ;

/*	����:	��ӡһ���ڽӱ�	*/
/*	����ǰ:	padj ָ��һ���ѳ�ʼ�����ڽӱ�, pht ָ��һ���ѳ�ʼ����ɢ�б�	*/
/*	������:	���ڽӱ���ӡ	*/
/*	ʱ�临�Ӷ�:	O (V)	*/
void PrintAdjacenty_List_A_W (const Adjacenty_List_w * const padj, const struct Ghash_table ** const pht) ;

/*	����:	�ͷ�һ���ڽӱ���ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	padj ָ��һ���ѳ�ʼ�����ڽӱ�	*/
/*	������:	���ڽӱ���ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O(V)	*/
void Release_A_W (const Adjacenty_List_w * const padj) ;

/* ��תһ���ڽӱ� */
int Reverse_A_W (Adjacenty_List_w * const padj, const struct Ghash_table ** const pht);

/*	����:	���ڽӱ��ҳ���Ȩͼ�����·��	*/
/*	����ǰ:	padj ָ��һ���Ѵ������ڽӱ�	*/
/*	������:	��ʼ���ڽӱ��еĸ�������·��	*/
/*	ʱ�临�Ӷ�:	O(V * V)	*/
int dijkstra (const Adjacenty_List_w * padj, const struct Ghash_table ** const pht, const int start);

/*	����:	���ڽӱ��ҳ���Ȩͼ�����·��,�õ����·���ĸ����������������С��һ�����·��	*/
/*	����ǰ:	padj ָ��һ���Ѵ������ڽӱ�	*/
/*	������:	��ʼ���ڽӱ��еĸ�������·��	*/
/*	ʱ�临�Ӷ�:	O(V * V)	*/
int new_dijkstra (const Adjacenty_List_w * padj, const struct Ghash_table ** const pht, const int start);

/* �ҳ���С������ */
int prim (const Adjacenty_List_w * padj, const struct Ghash_table ** const pht, const int start);

/* ̰��������С������ */
void kruskal (const Adjacenty_List_w * const padj, const struct Ghash_table ** const pht, const int start, char (* const result)[2], int * const weight);

/* ��ͼ�Ĺؽڵ� */
void find_art (const Adjacenty_List_w * const padj, const struct Ghash_table ** const pht, const int v);


ST_END_DECLS;
#endif	/* __ST_ADJACENTY_LIST_W_H__ */
