#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "st_stack.h"


/////////////////////////////////////////
//			����ʵ�ֶ�ջ			   //
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


/* ����ջ��push��ǰ��� */
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
//			˳���ʵ�ֶ�ջ			   //
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
	if(NULL == pStackNode || pStackNode->length == pStackNode->top)			/* ջ�� */
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





//	����һ����ջS��
int GInitStack(GSqStack *S)
{
	// Ϊջ�׷���һ��ָ����С�Ĵ洢�ռ�
	(*S).base = (GSElemType *)malloc(GSTACK_INIT_SIZE*sizeof(GSElemType));
	if( !(*S).base )
		exit(0);		// �洢����ʧ�� 
	(*S).top = (*S).base;	// ջ����ջ����ͬ��ʾһ����ջ
	(*S).stacksize = GSTACK_INIT_SIZE;
	return 1;
}

// ��ջSΪ��ջ��ջ����ջ����ͬ�ģ����򷵻�1�����򷵻�0��
int GStackEmpty(GSqStack S)
{
	if(S.top == S.base)
		return 1;
	else
		return 0;
}

//	����Ԫ��eΪ�µ�ջ��Ԫ�ء�
int GPush(GSqStack *S, GSElemType e)
{
	if((*S).top - (*S).base >= (*S).stacksize)	// ջ����׷�Ӵ洢�ռ� 
	{
		(*S).base = (GSElemType *)realloc((*S).base, 
			((*S).stacksize + GSTACKINCREMENT) * sizeof(GSElemType));
		if( !(*S).base )
			exit(0); // �洢����ʧ�� 
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += GSTACKINCREMENT;
	}
	*((*S).top)++=e;
	// �����ʽ��++ * ���ȼ���ͬ���������ǵ����㷽ʽ������������
	return 1;
}

//	��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0��
int GPop(GSqStack *S,GSElemType *e)
{
	if((*S).top == (*S).base)
		return 0;
	*e = *--(*S).top;
	// �����ʽ��++ * ���ȼ���ͬ���������ǵ����㷽ʽ������������
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



