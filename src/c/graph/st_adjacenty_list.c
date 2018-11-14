/*	st_adjacenty_list.c -- 邻接表实现文件	*/
#include <stdio.h>
#include <stdlib.h>
//#include "st_config.h"
#include "st_adjacenty_list.h"
//#include "st_log.h"

/*	局部函数声明	*/

ADJLVertex * ADJLMake_Vertex (const ADJLName vertex) ;
int get_index (const Adjacent_List * const padj, const GSName name) ;

/*	接口函数定义	*/

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
	
	(*padj)->indegree = (int *) malloc (lenth_indegree * capacity) ;		// 入度的最大值
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

	(*padj)->indegree[index] = indegree ;		// 保存一个点的入度
	(*padj)->list[index].name = name ;
	(*padj)->list[index].known = UNKNOWN ; 
	(*padj)->list[index].dist = GINFINITY ;
	(*padj)->list[index].path = UNKNOWN ;  
	if (0 == sub)								// 如果没有邻接点
	{
		(*padj)->list[index].next = NULL ;
		va_end (ap) ;
		return 1 ;
	}
	else
	{
		others = va_arg(ap, int) ;

		temp = (*padj)->list[index].next = ADJLMake_Vertex (others) ;	// 将邻接点保存到链表中
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

/*	局部函数定义	*/

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
	ADJLVertex * scan ;		// 链表的临时搜索变量
	ADJLName v ;

	InitializeGStack (&stack) ;					// 初始化一个栈用来保存入度为0的点
	
	for (i = 0; i < capacity; i++)				// 扫描图的所有节点，找出第一个入度为零的节点
	{
		if (0 == (*padj)->indegree[i])			// 如果入度是0，则入栈
			GSPush (&stack, &(*padj)->list[i].name) ;
	}
	
	while (!GStackIsEmpty (&stack))				// 检测栈是否空
	{
		GSPop (&stack, &v) ;					// 出栈
		topological[counter++] = v ;			// 将出栈的数据输出到排序数组中
		scan = (*padj)->list[get_index (padj, v)].next ;		// 找出该店所在的链表
		
		while (scan)
		{
			if (0 == --(*padj)->indegree[get_index (padj, scan->name)])		// 该链表中的所有邻接点的入度减一
				GSPush (&stack, &(*padj)->list[get_index (padj, scan->name)].name) ;		// 在减的过程中，如果有点的入度为零，入栈
			scan = scan->next ;
		}
	}
	if (counter != capacity)
		puts ("Graph has cycle.") ;				// 因为圈不可能存在入度为0；
	
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
	v = &(*padj)->list[0] ;				// 默认为第一个点
	EnGQueue (&queue, &v) ;

	while (!GQueueIsEmpty (&queue))
	{
		DeQueue (&queue, &v) ;			
		v->known = KNOWN ;
		scan = v->next ;				// 开始搜索该点的邻接点
		while (scan)					// 对点进行标志
		{
			w = &(*padj)->list[get_index (padj, scan->name)] ;		// 找出点索引
			if (GINFINITY == w->dist)		// 没有进行标记的才入队
			{
				w->dist = v->dist + 1 ;
				w->path = v->name ;
				EnGQueue (&queue, &w) ;		// 入队等待搜索
			}
			scan = scan->next ;
		}
	}
	ReleaseGQueue (&queue) ;
}

