#ifndef	__ST_ADJACENTY_LIST_H__
#define	__ST_ADJACENTY_LIST_H__

#include "stlib.h"

ST_BEGIN_DECLS ;

/*	st_adjacenty_list.h -- �ڽӱ�ͷ�ļ�	*/
/* һ������ͼG=(V,E)�ж��㼯(vertex)V�ͱ�(edge)��E��ɡ� */


#include <stdarg.h>

#include "st_graph_common.h"

#define GINFINITY 	0//(~(1 << 31))
#define UNKNOWN 	0
#define KNOWN 		1

/*	�������Ͷ���	*/
typedef char ADJLName ;
typedef struct vertex
{
	ADJLName name ;
	int known ;
	int	dist ;
	ADJLName path ;
	struct vertex * next ;
} ADJLVertex ;
typedef struct adjacency_list
{
	ADJLVertex * list ;			// ��¼��ı�
	int * indegree ;			// �õ������������������������
	int capacity ;				// ��¼��С����
} * Adjacent_List ;

/*	�ӿں�������	*/

/*	����:	Ϊһ���ڽӱ����洢�ռ�	*/
/*	����ǰ:	padj ָ��һ���ڽӱ�, capacity ָʾ�ڽӱ�Ĵ�С	*/
/*	������:	��� capacity > 0 && �ڷַ���ɹ�, �������ڽӱ�, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int CreateAdjacent_List (Adjacent_List * const padj, const int capacity) ;

/*	����:	��ʼ���ڽӱ�ĵ� index ��	*/
/*	����ǰ:	padj ָ��һ���Ѵ������ڽӱ�, index ָʾ�е�����, name ָʾ��ͷ��������, indegree ָʾ�ö�������, sub ָʾ�����ĸ���, ... ָʾ�ڽӵ��ö���Ķ���	*/
/*	������:	������ڽӱ���ڵ� index ��, ��������, ���ʼ������, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(N)	*/
int InitializeALineOfAdjacent_List (const Adjacent_List * const padj, const int index, const ADJLName name, const int indegree, const int sub, ...) ;

/*	����:	�ӵ���������������δ�ӡ�ڽӱ������ж���1��	*/
/*	����ǰ:	padj ָ��һ���Ѵ�����ϵ��ڽӱ�	*/
/*	������:	���ڽӱ��е����ж������α���ӡ1��	*/
/*	ʱ�临�Ӷ�:	O(N * N)	*/
void PrintAdjacent_List (const Adjacent_List * const padj) ;

/*	����:	�ͷ�һ���ڽӱ���ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	padj ָ��һ���Ѵ������ڽӱ�	*/
/*	������:	���ڽӱ���ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O(N * N)	*/
void ReleaseForAdjacent_List (const Adjacent_List * const padj) ;

/*	����:	���ڽӱ����һ����������	*/
/*	����ǰ:	padj ָ��һ���Ѵ������ڽӱ� topological����һ����������Ԫ�ص�����	*/
/*	������:	���һ����������topological	*/
/*	ʱ�临�Ӷ�:	O(N * N)	*/
void st_topological_sort (Adjacent_List * padj, ADJLName * topological);

/*	����:	���ڽӱ��ҳ���Ȩͼ�����·��	*/
/*	����ǰ:	padj ָ��һ���Ѵ������ڽӱ�	*/
/*	������:	��ʼ���ڽӱ��еĸ�������·��	*/
/*	ʱ�临�Ӷ�:	O(N * N)	*/
void Unweightd (Adjacent_List * const padj) ;

ST_END_DECLS ;
#endif	/* __ST_ADJACENTY_LIST_H__ */

