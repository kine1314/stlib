#ifndef	__ST_STACK_H__
#define	__ST_STACK_H__

ST_BEGIN_DECLS;	/* __cplusplus */

#include "stlib.h"
#include "st_dlist.h"
#include "st_slist.h"
#include "st_log.h"


/////////////////////////////////////////
//			链表实现堆栈			   //
/////////////////////////////////////////
typedef struct _ST_STACK_LIST
{
	STSList* pData ;
	stint	top ;
}ST_STACK_LIST ;


ST_STACK_LIST* st_stack_list_alloc(void);
void st_stack_list_free(ST_STACK_LIST* stack);
stbool	st_stack_list_push(ST_STACK_LIST* stack, stint data);
stint	st_stack_list_pop(ST_STACK_LIST* stack) ;
void	st_stack_list_dump(ST_STACK_LIST* stack);



/////////////////////////////////////////
//			顺序表实现堆栈			   //
/////////////////////////////////////////
typedef struct _ST_STACK_NODE
{
	stint*	pData ;
	stint	length ;
	stint	top ;
}ST_STACK_NODE ;


ST_STACK_NODE*	st_stack_alloc(stint num);
stbool	*st_stack_free(const ST_STACK_NODE* pStackNode);
stbool	*st_stack_push(ST_STACK_NODE* pStackNode, stint data);
stbool	*st_stack_pop(ST_STACK_NODE* pStackNode, stint* data);
stint	st_count_stack(ST_STACK_NODE* pStackNode);
void	st_stack_dump(ST_STACK_NODE* pStackNode);
stbool st_stack_is_empty(const ST_STACK_NODE* pStackNode);


// 指针实现栈
typedef int GSElemType; // 栈类型 

#define GSTACK_INIT_SIZE 10	// 存储空间初始分配量 
#define GSTACKINCREMENT 2	// 存储空间分配增量 
// 栈的顺序存储表示 P46 
typedef struct _GSqStack
{
	GSElemType *base;	// 在栈构造之前和销毁之后，base的值为NULL 
	GSElemType *top;		// 栈顶指针 
	int stacksize;		// 当前已分配的存储空间，以元素为单位 
}GSqStack;	// 顺序栈

//	构造一个空栈S。
int GInitStack(GSqStack *S);

// 若栈S为空栈（栈顶与栈底相同的），则返回1，否则返回0。
int GStackEmpty(GSqStack S);

//	插入元素e为新的栈顶元素。
int GPush(GSqStack *S, GSElemType e);

//	若栈不空，则删除S的栈顶元素，用e返回其值，并返回1；否则返回0。
int GPop(GSqStack *S,GSElemType *e);

stbool GFreeStack(GSqStack *S);

ST_END_DECLS;
#endif	/* __ST_STACK_H__ */

