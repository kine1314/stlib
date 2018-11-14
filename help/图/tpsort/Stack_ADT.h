/*	Stack_ADT.h -- 栈模型头文件	*/

/*	数据类型定义	*/

typedef char SName ;
typedef struct stack_node
{
	SName name ;
	struct stack_node * next ;
} Stack_Node ;
typedef Stack_Node * Stack ;

/*	接口函数声明	*/

/*	操作:	初始化一个栈	*/
/*	操作前:	pstack 指向一个栈	*/
/*	操作后:	如果内存分配成功, 该栈被初始化并被置为空, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int InitializeStack (Stack * const pstack) ;

/*	操作:	确定一个栈是否为空	*/
/*	操作前:	pstack 指向一个已初始化的栈	*/
/*	操作后:	如果栈为空, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int StackIsEmpty (const Stack * const pstack) ;

/*	操作:	将一个元素入栈	*/
/*	操作前:	pstack 指向一个已初始化的栈, panme 指向入栈的元素的数据	*/
/*	操作后:	如果内存分配成功, 元素数据域为 *pname 的元素入栈, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int Push (Stack * const pstack, const SName * const pname) ;

/*	操作:	从栈中弹出一个元素	*/
/*	操作前:	pstack 指向一个已初始化的栈, pname 指向一个元素数据域的数据	*/
/*	操作后:	如果栈不为空, 栈顶元素出栈并且 *panme 被赋值, 返回1; 否则返回0	*/
/*	时间复杂度:	O(1)	*/
int Pop (Stack * const pstack, SName * const pname) ;

/*	操作:	将一个函数从栈顶到栈底依次作用于栈中所有元素1次	*/
/*	操作前:	pstack 指向一个已初始化的栈, pfun 指向一个没有返回值, 接受一个Stack_Node类型参数的函数	*/
/*	操作后:	pfun 指向的函数被作用于栈中所有元素1次	*/
/*	时间复杂度:	O(N)	*/
void Traversal (const Stack * const pstack, void (* pfun) (const Stack_Node * const pstack_node)) ;

/*	操作:	释放一个栈所用的内存空间	*/
/*	操作前:	pstack 指向一个已初始化的栈	*/
/*	操作后:	该栈所占用的内存空间被释放	*/
/*	时间复杂度:	O(N)	*/
void ReleaseStack (const Stack * const pstack) ;