/*	Stack_ADT.h -- ջģ��ͷ�ļ�	*/

/*	�������Ͷ���	*/

typedef char SName ;
typedef struct stack_node
{
	SName name ;
	struct stack_node * next ;
} Stack_Node ;
typedef Stack_Node * Stack ;

/*	�ӿں�������	*/

/*	����:	��ʼ��һ��ջ	*/
/*	����ǰ:	pstack ָ��һ��ջ	*/
/*	������:	����ڴ����ɹ�, ��ջ����ʼ��������Ϊ��, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int InitializeStack (Stack * const pstack) ;

/*	����:	ȷ��һ��ջ�Ƿ�Ϊ��	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ	*/
/*	������:	���ջΪ��, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int StackIsEmpty (const Stack * const pstack) ;

/*	����:	��һ��Ԫ����ջ	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ, panme ָ����ջ��Ԫ�ص�����	*/
/*	������:	����ڴ����ɹ�, Ԫ��������Ϊ *pname ��Ԫ����ջ, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int Push (Stack * const pstack, const SName * const pname) ;

/*	����:	��ջ�е���һ��Ԫ��	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ, pname ָ��һ��Ԫ�������������	*/
/*	������:	���ջ��Ϊ��, ջ��Ԫ�س�ջ���� *panme ����ֵ, ����1; ���򷵻�0	*/
/*	ʱ�临�Ӷ�:	O(1)	*/
int Pop (Stack * const pstack, SName * const pname) ;

/*	����:	��һ��������ջ����ջ������������ջ������Ԫ��1��	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ, pfun ָ��һ��û�з���ֵ, ����һ��Stack_Node���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ�����������ջ������Ԫ��1��	*/
/*	ʱ�临�Ӷ�:	O(N)	*/
void Traversal (const Stack * const pstack, void (* pfun) (const Stack_Node * const pstack_node)) ;

/*	����:	�ͷ�һ��ջ���õ��ڴ�ռ�	*/
/*	����ǰ:	pstack ָ��һ���ѳ�ʼ����ջ	*/
/*	������:	��ջ��ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O(N)	*/
void ReleaseStack (const Stack * const pstack) ;