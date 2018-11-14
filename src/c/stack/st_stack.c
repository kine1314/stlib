#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "st_stack.h"


/////////////////////////////////////////
//			链表实现堆栈			   //
/////////////////////////////////////////


ST_STACK_LIST* st_stack_list_alloc(void)
{
	ST_STACK_LIST* stack = NULL ;

	stack = (ST_STACK_LIST*)malloc(sizeof(ST_STACK_LIST)) ;
	if(NULL == stack)
	{
		__err("alloc meme for stack failed !\n") ;
		exit(1) ;
	}
	stack->pData = st_slist_alloc() ;
	stack->top = 0 ;

	return stack ;
}



void st_stack_list_free(ST_STACK_LIST* stack)
{
	if(NULL == stack || NULL == stack->pData)
		return ;

	st_slist_free(stack->pData);
	free(stack) ;
	stack = NULL ;
}


/* 链表栈的push向前添加 */
stbool	st_stack_list_push(ST_STACK_LIST* stack, stint data)
{

	STSList* _S = NULL ;

	stack->pData = st_slist_prepend(stack->pData, (stpointer)data) ;
	stack->top++ ;

	return TRUE ;
}



stint	st_stack_list_pop(ST_STACK_LIST* stack) 
{
	STSList* list = NULL ;
	stint	data ;

	if(0 == stack->top)
	{
		__msg("the stack is NULL !\n");
		return FALSE ;
	}
	else
	{
		stack->top-- ;
		list = stack->pData ;
		data = (stint)list->data ;
		stack->pData = stack->pData->next ;
		free(list) ;
		list = NULL ;
		return data ;
	}
}



/*
void	st_stack_list_dump(ST_STACK_LIST* stack);
*/


/////////////////////////////////////////
//			顺序表实现堆栈			   //
/////////////////////////////////////////

ST_STACK_NODE*	st_stack_alloc(stint num)
{
	ST_STACK_NODE* pStackNode = NULL ;
	if(0 == num)
		return NULL ;

	pStackNode = (ST_STACK_NODE *)malloc(sizeof(ST_STACK_NODE)) ;
	if(NULL == pStackNode)
	{
		__err("alloc mem for stack fail! \n");
		exit(1);
	}
	memset(pStackNode, 0, sizeof(ST_STACK_NODE));

	pStackNode->pData = (stint *)malloc(num*sizeof(stint));
	if(NULL == pStackNode->pData)
	{
		free(pStackNode) ;
		pStackNode = NULL ;
		return NULL ;
	}

	memset(pStackNode->pData, 0, sizeof(stint)*num);
	pStackNode->length = num ;
	pStackNode->top = 0 ;

	return pStackNode ;
}

stbool st_stack_is_empty(const ST_STACK_NODE* pStackNode)
{
	if(0 == pStackNode->pData)
		return 1;
	else
		return 0;
}

stbool	*st_stack_free(const ST_STACK_NODE* pStackNode)
{
	if(NULL == pStackNode)
		return FALSE ;

	if(NULL == pStackNode->pData)
		return FALSE ;

	free(pStackNode->pData) ;
	free((void *)pStackNode) ;
	//pStackNode->pData = NULL ;
	pStackNode = NULL ;

	return TRUE ;
}




stbool	*st_stack_push(ST_STACK_NODE* pStackNode, stint data)
{
	if(NULL == pStackNode || pStackNode->length == pStackNode->top)			/* 栈满 */
		return FALSE ;

	pStackNode->pData[pStackNode->top++] = data ;
	return TRUE ;
}




stbool	*st_stack_pop(ST_STACK_NODE* pStackNode, stint* data)
{
	if(NULL == pStackNode || NULL == data)
		return FALSE ;

	if(0 == pStackNode->top)
		return FALSE ;

	*data = pStackNode->pData[--pStackNode->top] ;

	return TRUE ;
}



stint	st_count_stack(ST_STACK_NODE* pStackNode)
{
	return pStackNode->top ;
}


/**
 *	dump the current stack
 **/
void st_stack_dump(ST_STACK_NODE* pStackNode)
{
	stint i ;

	if(NULL == pStackNode || 0 == pStackNode->top)
		goto FAIL ;

	for(i = 0 ; i < pStackNode->top ; i++)
	{
		printf("%d ", pStackNode->pData[i]) ;
	}
	printf("\n") ;
	return ;
	

FAIL:
	;//__err("the stack is NULL! \n");
	return ;
}





//	构造一个空栈S。
int GInitStack(GSqStack *S)
{
	// 为栈底分配一个指定大小的存储空间
	(*S).base = (GSElemType *)malloc(GSTACK_INIT_SIZE*sizeof(GSElemType));
	if( !(*S).base )
		exit(0);		// 存储分配失败 
	(*S).top = (*S).base;	// 栈底与栈顶相同表示一个空栈
	(*S).stacksize = GSTACK_INIT_SIZE;
	return 1;
}

// 若栈S为空栈（栈顶与栈底相同的），则返回1，否则返回0。
int GStackEmpty(GSqStack S)
{
	if(S.top == S.base)
		return 1;
	else
		return 0;
}

//	插入元素e为新的栈顶元素。
int GPush(GSqStack *S, GSElemType e)
{
	if((*S).top - (*S).base >= (*S).stacksize)	// 栈满，追加存储空间 
	{
		(*S).base = (GSElemType *)realloc((*S).base, 
			((*S).stacksize + GSTACKINCREMENT) * sizeof(GSElemType));
		if( !(*S).base )
			exit(0); // 存储分配失败 
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += GSTACKINCREMENT;
	}
	*((*S).top)++=e;
	// 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

//	若栈不空，则删除S的栈顶元素，用e返回其值，并返回1；否则返回0。
int GPop(GSqStack *S,GSElemType *e)
{
	if((*S).top == (*S).base)
		return 0;
	*e = *--(*S).top;
	// 这个等式的++ * 优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

stbool GFreeStack(GSqStack *S)
{
	if(NULL == S)
		return FALSE ;
	if(NULL == S->base)
		return FALSE ;

	free(S->base) ;

	return TRUE ;
}



