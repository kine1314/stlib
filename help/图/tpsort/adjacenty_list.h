/*	adjacenty_list.h -- �ڽӱ�ͷ�ļ�	*/
#include <stdarg.h>

/*	�������Ͷ���	*/
typedef char Name ;
typedef struct vertex
{
	Name name ;
	struct vertex * next ;
} Vertex ;
typedef struct adjacency_list
{
	Vertex * list ;
	int * indegree ;
	int capacity ;
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
int InitializeALineOfAdjacent_List (const Adjacent_List * const padj, const int index, const Name name, const int indegree, const int sub, ...) ;

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