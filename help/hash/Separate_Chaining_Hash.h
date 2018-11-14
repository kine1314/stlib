/*	Separate_Chaining_Hash.h -- 分离链接散列表头文件 此版本是采用的key % tablesize的散列方法，　并且不能对表头进行操作	*/
#define MAXTABLESIZE 4096
#define CONSTANT 10
#define NUL '\0'

/*
话说这个东西原本以为很快就会写好,即使是前天才看是看的.实现部分用的就是一个表和size个链表.
可事实上我写了不下8小时...写完了就好啊,不然我会很郁闷呢.主要卡壳的地方就是定义数据类型的
时候,我反反复复更改了不下五遍.不想回忆起那些错误的行为,我想把我实现的思想说出来来帮助自己强化记忆.
分离链接散列表用来解决冲突的问题,一旦发生冲突时就可以把数据放入相应索引指针指向的链表中.
在定义完链表结构之后.使Header成为指向链表结点的指针.表定义为指向Header的指针.之所以定义为
指向Header的指针是因为这样做可以避免通过将索引*伸缩因子来访问表中元素,操作更加简单,对用户来说更加方便.
知道了这些,实现就不难了,我知道这些可是做了很多尝试的.虽然往往事后都发现自己当初的自以为是有
多么愚蠢.但我还是非常喜欢现在自以为是的感觉,好了,贴出代码.这些话都是用来强化自己记忆的,代码才最能说明问题!
*/

/*	数据类型定义	*/

typedef int SPItem ;
typedef struct sp_list_node
{
	SPItem item ;
	struct sp_list_node * next ;
} SPListNode ;
typedef SPListNode * SPHeader ;
typedef struct sp_hashtable
{
	int size ;
	SPHeader * lists ;
} * SPHashTable ;

/*	操作:	初始化一个分离链接散列表	*/
/*	操作前:	size 是指定分离链接散列表的大小的变量	*/
/*	操作后:	该表被创建并且表中的所有表元指针被初始化为空, 返回该表	*/
SPHashTable InitializeTable (const int size) ;

/*	操作:	根据传递来的参数产生并返回一个索引值	*/
/*	操作前:	item 是数据, size 表示表的大小	*/
/*	操作后:	返回一个索引值	*/
int Hash (const SPItem item, const int size) ;

/*	操作:	返回一个指向表中指定数据所在结点的指针	*/
/*	操作前:	item 是被查找的数据, h 是一个已初始化的表	*/
/*	操作后:	如果可能, 返回指向表中指定数据所在结点的指针; 否则返回NULL	*/
SPHeader Find (const SPItem item, const SPHashTable h) ;

/*	操作:	将一个具有指定数据以插入新结点的方式插入到表中	*/
/*	操作前:	item 是待插入的数据, ph 指向一个已初始化的表	*/
/*	操作后:	如果可能, 以 item 为数据创建一个结点被插入到表中(如果冲突, 它将出现在链表的最前面的位置), 返回1; 否则返回0	*/
int Insert (const SPItem item, SPHashTable * const ph) ;

/*	操作:	从表中删除一个结点	*/
/*	操作前:	item 是待删除结点的数据, ph 指向一个已初始化的表	*/
/*	操作后:	如果可能, item 所在结点被从表中删除, 返回1; 否则返回0	*/
int Delete (const SPItem item, SPHashTable * const ph) ;

/*	操作:	从低索引向高索引将一个函数作用于表中所有存在的结点	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个ListNode *类型参数的函数	*/
/*	操作后:	pfun 指向的函数被从低索引向高索引作用到所有存在的结点一次	*/
void Traversal (const SPHashTable * const ph, void (* pfun) (const SPListNode * const pnode)) ;

/*	操作:	清空一个表	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	该表所占用的全部内存空间被释放	*/
void Release (SPHashTable * ph) ;
