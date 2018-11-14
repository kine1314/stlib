/*	9-3-12-07-20.06.c -- 第九章第三题	*/
#include <stdio.h>
#include <stdlib.h>

typedef char TName ;

#include "Stack_ADT.h"
#include "adjacenty_list.h"

#define SIZE 11

int main (void) ;
int get_index (const Adjacent_List * const padj, const TName name) ;
void topological_sort (Adjacent_List * padj, TName * topological) ;
void print_name (const TName vertex) ; 
void print_stack (const Stack_Node * const pstack_node) ;

int main (void)
{
	Adjacent_List adj ;
	int capacity = SIZE, i ;
	TName topological[SIZE] ;

	CreateAdjacent_List (&adj, capacity) ;
	InitializeALineOfAdjacent_List (&adj, 0, 's', 0, 3, 'a', 'd', 'g') ;
	InitializeALineOfAdjacent_List (&adj, 1, 'a', 1, 2, 'b', 'e') ;
	InitializeALineOfAdjacent_List (&adj, 2, 'b', 1, 1, 'c') ;
	InitializeALineOfAdjacent_List (&adj, 3, 'c', 3, 1, 't') ;
	InitializeALineOfAdjacent_List (&adj, 4, 'd', 2, 2, 'a', 'e') ;
	InitializeALineOfAdjacent_List (&adj, 5, 'e', 4, 3, 'c', 'f', 'i') ;
	InitializeALineOfAdjacent_List (&adj, 6, 'f', 2, 2, 'c', 't') ;
	InitializeALineOfAdjacent_List (&adj, 7, 'g', 1, 3, 'd', 'e', 'h') ;
	InitializeALineOfAdjacent_List (&adj, 8, 'h', 1, 2, 'e', 'i') ;
	InitializeALineOfAdjacent_List (&adj, 9, 'i', 2, 2, 'f', 't') ;
	InitializeALineOfAdjacent_List (&adj, 10, 't', 3, 0) ;
//	PrintAdjacent_List (&adj) ;
	topological_sort (&adj, topological) ;
	for (i = 0; i < 11; i++)
		printf ("%c/n", topological[i]) ;
	ReleaseForAdjacent_List (&adj) ;
	
	return 0 ;
}

int get_index (const Adjacent_List * const padj, const TName name)
{
	int i, capacity = (*padj) -> capacity ;

	for (i = 0; i < capacity; i++)
	{
		if (name == (*padj) -> list[i].name)
			return i ;
	}
}

void topological_sort (Adjacent_List * padj, TName * topological)
{
	Stack stack ;
	int counter = 0, capacity = (*padj) -> capacity, i ;
	Vertex * scan ;
	TName v ;

	InitializeStack (&stack) ;
	for (i = 0; i < capacity; i++)
	{
		if (0 == (*padj) -> indegree[i])
			Push (&stack, &(*padj) -> list[i].name) ;
	}
	while (!StackIsEmpty (&stack))
	{
		Pop (&stack, &v) ;
		topological[counter++] = v ;
		scan = (*padj) -> list[get_index (padj, v)].next ;
		while (scan)
		{
			if (0 == --(*padj) -> indegree[get_index (padj, scan -> name)])
				Push (&stack, &(*padj) -> list[get_index (padj, scan -> name)].name) ;
			scan = scan -> next ;
		}
	}
	if (counter != capacity)
		puts ("Graph has cycle.") ;
	ReleaseStack (&stack) ;
}

void print_name (const TName vertex)
{
	printf ("%c ", vertex) ;
}

void print_stack (const Stack_Node * const pstack_node)
{
	printf ("%c/n", pstack_node -> name) ;
}