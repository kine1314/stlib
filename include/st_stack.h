#ifndef	__ST_STACK_H__
#define	__ST_STACK_H__

ST_BEGIN_DECLS;	/* __cplusplus */

#include "stlib.h"
#include "st_dlist.h"
#include "st_slist.h"
#include "st_log.h"


/////////////////////////////////////////
//			����ʵ�ֶ�ջ			   //
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
//			˳���ʵ�ֶ�ջ			   //
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


// ָ��ʵ��ջ
typedef int GSElemType; // ջ���� 

#define GSTACK_INIT_SIZE 10	// �洢�ռ��ʼ������ 
#define GSTACKINCREMENT 2	// �洢�ռ�������� 
// ջ��˳��洢��ʾ P46 
typedef struct _GSqStack
{
	GSElemType *base;	// ��ջ����֮ǰ������֮��base��ֵΪNULL 
	GSElemType *top;		// ջ��ָ�� 
	int stacksize;		// ��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ 
}GSqStack;	// ˳��ջ

//	����һ����ջS��
int GInitStack(GSqStack *S);

// ��ջSΪ��ջ��ջ����ջ����ͬ�ģ����򷵻�1�����򷵻�0��
int GStackEmpty(GSqStack S);

//	����Ԫ��eΪ�µ�ջ��Ԫ�ء�
int GPush(GSqStack *S, GSElemType e);

//	��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0��
int GPop(GSqStack *S,GSElemType *e);

stbool GFreeStack(GSqStack *S);

ST_END_DECLS;
#endif	/* __ST_STACK_H__ */

