/*	adjacenty_list.c -- 邻接表实现文件	*/
#include <stdio.h>
#include <stdlib.h>
#include "adjacenty_list.h"

/*	局部函数声明	*/

Vertex * Make_Vertex (const Name vertex) ;

/*	接口函数定义	*/

int CreateAdjacent_List (Adjacent_List * const padj, const int capacity)
{
	int lenth_list = sizeof (Vertex), lenth_indegree = sizeof (int) ;
	if (capacity <= 0)
		return 0 ;
	*padj = (struct adjacency_list *) malloc (sizeof (struct adjacency_list)) ;
	if (NULL == *padj)
		return 0 ;
	(*padj) -> list = (Vertex *) malloc (lenth_list * capacity) ;
	if (NULL == (*padj) -> list)
	{
		free (*padj) ;
		return 0 ;
	}
	(*padj) -> indegree = (int *) malloc (lenth_indegree * capacity) ;
	if (NULL == (*padj) -> indegree)
	{
		free ((*padj) -> list) ;
		free (*padj) ;
		return 0 ;
	}
	(*padj) -> capacity = capacity ;

	return 1 ;
}

int InitializeALineOfAdjacent_List (const Adjacent_List * const padj, const int index, const Name name, const int indegree, const int sub, ...)
{
	va_list ap ;
	Vertex * temp ;
	Name others ;
	int i ;

	if (index >= (*padj) -> capacity || sub < 0)
		return 0 ;
	va_start (ap, sub) ;
	(*padj) -> indegree[index] = indegree ;
	(*padj) -> list[index].name = name ;
	if (0 == sub)
	{
		(*padj) -> list[index].next = NULL ;
		va_end (ap) ;
		return 1 ;
	}
	else
	{
		others = va_arg (ap, Name) ;
		temp = (*padj) -> list[index].next = Make_Vertex (others) ;
		if (NULL == temp)
		{
			va_end (ap) ;
			return 0 ;
		}
		for (i = 1; i < sub; i++)
		{
			others = va_arg (ap, Name) ;
			temp -> next = Make_Vertex (others) ;
			temp = temp -> next ;
		}
		va_end (ap) ;
		return 1 ;
	}
}

void PrintAdjacent_List (const Adjacent_List * const padj)
{
	Vertex scan ;
	int i, capacity ;

	capacity = (*padj) -> capacity ;
	for (i = 0; i < capacity; i++)
	{
		printf ("Indegree:%-2d", (*padj) -> indegree[i]) ;
		scan = (*padj) -> list[i] ;
		while (scan.next)
		{
			printf ("%c ", scan.name) ;
			scan = *scan.next ;
		}
		printf ("%c ", scan.name) ;
		putchar ('/n') ;
	}
}

void ReleaseForAdjacent_List (const Adjacent_List * const padj)
{
	Vertex * scan, * temp ;
	int i, capacity ;

	capacity = (*padj) -> capacity ;
	for (i = 0; i < capacity; i++)
	{
		scan = (*padj) -> list[i].next ;
		while (scan)
		{
			temp = scan ;
			scan = scan -> next ;
			free (temp) ;
		}
	}
	free ((*padj) -> list) ;
	free ((*padj) -> indegree) ;
	free (*padj) ;
}

/*	局部函数定义	*/

Vertex * Make_Vertex (const Name vertex)
{
	Vertex * new_vertex = (Vertex *) malloc (sizeof (Vertex)) ;

	if (new_vertex)
	{
		new_vertex -> name = vertex ;
		new_vertex -> next = NULL ;
	}

	return new_vertex ;
}