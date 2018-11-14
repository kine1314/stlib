/*	st_adjacenty_list.c -- �ڽӱ�ʵ���ļ�	*/
#include <stdio.h>
#include <stdlib.h>
//#include "st_config.h"
#include "st_adjacenty_list.h"
//#include "st_log.h"

/*	�ֲ���������	*/

ADJLVertex * ADJLMake_Vertex (const ADJLName vertex) ;
int get_index (const Adjacent_List * const padj, const GSName name) ;

/*	�ӿں�������	*/

int CreateAdjacent_List (Adjacent_List * const padj, const int capacity)
{
	int lenth_list = sizeof (ADJLVertex), lenth_indegree = sizeof (int) ;
	if (capacity <= 0)
		return 0 ;
	
	*padj = (struct adjacency_list *) malloc (sizeof (struct adjacency_list)) ;
	if (NULL == *padj)
		return 0 ;
	
	(*padj)->list = (ADJLVertex *) malloc (lenth_list * capacity) ;
	if (NULL == (*padj)->list)
	{
		free (*padj) ;
		return 0 ;
	}
	
	(*padj)->indegree = (int *) malloc (lenth_indegree * capacity) ;		// ��ȵ����ֵ
	if (NULL == (*padj)->indegree)
	{
		free ((*padj)->list) ;
		free (*padj) ;
		return 0 ;
	}
	(*padj)->capacity = capacity ;

	return 1 ;
}

int InitializeALineOfAdjacent_List (const Adjacent_List * const padj, const int index, const ADJLName name, const int indegree, const int sub, ...)
{
	va_list ap ;
	ADJLVertex * temp ;
	ADJLName others ;
	int i ;

	if (index >= (*padj)->capacity || sub < 0)
		return 0 ;

	va_start (ap, sub) ;

	(*padj)->indegree[index] = indegree ;		// ����һ��������
	(*padj)->list[index].name = name ;
	(*padj)->list[index].known = UNKNOWN ; 
	(*padj)->list[index].dist = GINFINITY ;
	(*padj)->list[index].path = UNKNOWN ;  
	if (0 == sub)								// ���û���ڽӵ�
	{
		(*padj)->list[index].next = NULL ;
		va_end (ap) ;
		return 1 ;
	}
	else
	{
		others = va_arg(ap, int) ;

		temp = (*padj)->list[index].next = ADJLMake_Vertex (others) ;	// ���ڽӵ㱣�浽������
		if (NULL == temp)
		{
			va_end (ap) ;
			return 0 ;
		}
		for (i = 1; i < sub; i++)
		{
			others = va_arg(ap, int) ;

			temp->next = ADJLMake_Vertex (others) ;
			temp = temp->next ;
		}

		va_end (ap) ;

		return 1 ;
	}
}

void PrintAdjacent_List (const Adjacent_List * const padj)
{
	ADJLVertex scan ;
	int i, capacity ;

	capacity = (*padj)->capacity ;
	for (i = 0; i < capacity; i++)
	{
		printf ("Indegree:%-2d", (*padj)->indegree[i]) ;
		scan = (*padj)->list[i] ;
		while (scan.next)
		{
			printf ("%c ", scan.name) ;
			scan = *scan.next ;
		}
		printf ("%c ", scan.name) ;
		scan = (*padj)->list[i] ;			// ???
		printf ("%-10s \tvertex:%c known:%d dist:%d path:%c", " ", scan.name, scan.known, scan.dist, scan.path) ;  
		putchar ('\n') ;
	}
}

void ReleaseForAdjacent_List (const Adjacent_List * const padj)
{
	ADJLVertex * scan, * temp ;
	int i, capacity ;

	capacity = (*padj)->capacity ;
	for (i = 0; i < capacity; i++)
	{
		scan = (*padj)->list[i].next ;
		while (scan)
		{
			temp = scan ;
			scan = scan->next ;
			free (temp) ;
		}
	}
	free ((*padj)->list) ;
	free ((*padj)->indegree) ;
	free (*padj) ;
}

/*	�ֲ���������	*/

ADJLVertex * ADJLMake_Vertex (const ADJLName vertex)
{
	ADJLVertex * new_vertex = (ADJLVertex *) malloc (sizeof (ADJLVertex)) ;

	if (new_vertex)
	{
		new_vertex->name = vertex ;
		new_vertex->known = UNKNOWN ;
		new_vertex->dist = GINFINITY ;
		new_vertex->path = UNKNOWN ;  
		new_vertex->next = NULL ;
	}

	return new_vertex ;
}

void st_topological_sort (Adjacent_List * padj, GSName * topological)
{
	GStack stack ;
	int counter = 0, capacity = (*padj)->capacity, i ;
	ADJLVertex * scan ;		// �������ʱ��������
	ADJLName v ;

	InitializeGStack (&stack) ;					// ��ʼ��һ��ջ�����������Ϊ0�ĵ�
	
	for (i = 0; i < capacity; i++)				// ɨ��ͼ�����нڵ㣬�ҳ���һ�����Ϊ��Ľڵ�
	{
		if (0 == (*padj)->indegree[i])			// ��������0������ջ
			GSPush (&stack, &(*padj)->list[i].name) ;
	}
	
	while (!GStackIsEmpty (&stack))				// ���ջ�Ƿ��
	{
		GSPop (&stack, &v) ;					// ��ջ
		topological[counter++] = v ;			// ����ջ���������������������
		scan = (*padj)->list[get_index (padj, v)].next ;		// �ҳ��õ����ڵ�����
		
		while (scan)
		{
			if (0 == --(*padj)->indegree[get_index (padj, scan->name)])		// �������е������ڽӵ����ȼ�һ
				GSPush (&stack, &(*padj)->list[get_index (padj, scan->name)].name) ;		// �ڼ��Ĺ����У�����е�����Ϊ�㣬��ջ
			scan = scan->next ;
		}
	}
	if (counter != capacity)
		puts ("Graph has cycle.") ;				// ��ΪȦ�����ܴ������Ϊ0��
	
	ReleaseGStack (&stack) ;
}

int get_index (const Adjacent_List * const padj, const GSName name)
{
	int i, capacity = (*padj)->capacity ;

	for (i = 0; i < capacity; i++)
	{
		if (name == (*padj)->list[i].name)
			return i ;
	}
}

void Unweightd (Adjacent_List * const padj)
{
	GQueue queue ;
	ADJLVertex * v, *w, * scan ;

	InitializeGQueue (&queue) ;
	v = &(*padj)->list[0] ;				// Ĭ��Ϊ��һ����
	EnGQueue (&queue, &v) ;

	while (!GQueueIsEmpty (&queue))
	{
		DeQueue (&queue, &v) ;			
		v->known = KNOWN ;
		scan = v->next ;				// ��ʼ�����õ���ڽӵ�
		while (scan)					// �Ե���б�־
		{
			w = &(*padj)->list[get_index (padj, scan->name)] ;		// �ҳ�������
			if (GINFINITY == w->dist)		// û�н��б�ǵĲ����
			{
				w->dist = v->dist + 1 ;
				w->path = v->name ;
				EnGQueue (&queue, &w) ;		// ��ӵȴ�����
			}
			scan = scan->next ;
		}
	}
	ReleaseGQueue (&queue) ;
}

