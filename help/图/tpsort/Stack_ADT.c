/*	Stack_ADT.c -- ջģ��ʵ���ļ�	*/
#include <stdio.h>
#include <stdlib.h>
#include "Stack_ADT.h"

/*	�ֲ���������	*/
 
static Stack_Node * Make_Node (const SName * const panme) ;

/*	�ӿں�������	*/

int InitializeStack (Stack * const pstack)
{
	*pstack = (Stack_Node *) malloc (sizeof (Stack_Node)) ;
	if (NULL == *pstack)
		return 0 ;
	else
	{
		*pstack = NULL ;
		return 1 ;
	}
}

int StackIsEmpty (const Stack * const pstack)
{
	return NULL == *pstack ;
}

int Push (Stack * const pstack, const SName * const pname)
{
	Stack_Node * new_node ;

	new_node = Make_Node (pname) ;
	if (new_node)
	{
		new_node -> next = *pstack ;
		*pstack = new_node ;
		return 1 ;
	}
	else
		return 0 ;
}

int Pop (Stack * const pstack, SName * const pname)
{
	Stack_Node * temp ;

	if (StackIsEmpty (pstack))
		return 0 ;
	else
	{
		*pname = (*pstack) -> name ;
		temp = *pstack ;
		*pstack = (*pstack) -> next ;
		free (temp) ;
		return 1 ;
	}
}

void Traversal (const Stack * const pstack, void (* pfun) (const Stack_Node * const stack_node))
{
	Stack_Node * scan = *pstack ;

	while (scan)
	{
		(* pfun) (scan) ;
		scan = scan -> next ;
	}
}

void ReleaseStack (const Stack * const pstack)
{
	Stack_Node * temp, * scan = *pstack ;

	while (scan)
	{
		temp = scan ;
		scan = scan -> next ;
		free (temp) ;
	}
}

/*	�ֲ���������	*/

static Stack_Node * Make_Node (const SName * const pname)
{
	Stack_Node * new_node ;

	new_node = (Stack_Node *) malloc (sizeof (Stack_Node)) ;
	if (new_node)
	{
		new_node -> name = *pname ;
	}

	return new_node ;
}