#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct _STACK_NODE
{
    int* pData;
	int length;
	int top;
}STACK_NODE;


STACK_NODE* alloca_stack(int number)
{
    STACK_NODE* pStackNode = NULL;
    if(0 == number)
	    return NULL;
	
    pStackNode = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    assert(NULL != pStackNode);
    memset(pStackNode, 0, sizeof(STACK_NODE));
	
    pStackNode->pData = (int*)malloc(sizeof(int) * number);
    if(NULL == pStackNode->pData){
	    free(pStackNode);
        return NULL;
    }
	
    memset(pStackNode->pData, 0, sizeof(int) * number);
    pStackNode-> length = number;
    pStackNode-> top = 0;
    return pStackNode;
}

int free_stack(const STACK_NODE* pStackNode)
{
    if(NULL == pStackNode)
        return 0;
	
    assert(NULL != pStackNode->pData);	
		
    free(pStackNode->pData);
    free((void*)pStackNode);
    return 1;
}

int stack_push(STACK_NODE* pStackNode, int value)
{
    if(NULL == pStackNode)
        return 0;
		
    if(pStackNode->length == pStackNode->top)
        return 1;
		
    pStackNode->pData[pStackNode->top ++] = value;
    return 1;
}

int stack_pop(STACK_NODE* pStackNode, int* value)
{
    if(NULL == pStackNode || NULL == value)
        return 0;
		
    if(0 == pStackNode->top)
        return 0;
		
    *value = pStackNode->pData[-- pStackNode->top];
    return 1;
}

int count_stack_number(const STACK_NODE* pStackNode)
{
    return pStackNode->top;
}



