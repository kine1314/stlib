/*	open_addressing_hash(2).h -- 开放定址散列表头文件	开放定址散列表(平方探测法)头文件C语言*/
enum KindOfEntry {Legitimate, Empty, Deleted} ;

/*	数据类型定义	*/

typedef int Item ;
typedef struct cell
{
	Item item ;
	enum KindOfEntry entry ;
} Cell ;
typedef struct hashtable
{
	int size ;
	Cell * lists ;
} * HashTable ;

/*	接口函数声明	*/

/*	操作:	根据传递来的数据产生一个值并返回	*/
/*	操作前:	item , size 是用来计算产生数值的数据	*/
/*	操作后:	通过计算产生一个值并返回	*/
int Hash (const int item, const int size) ;

/*	操作:	创建并初始化一个表	*/
/*	操作前:	ph 指向一个表, size 是指示表的大小的变量	*/
/*	操作后:	如果可能, 该表被创建并且所有元素数据域被置为空, 如果 size 不是素数, 则取大于 size 的最小素数为表的大小, 返回1; 否则返回0	*/
int InitializeTable (HashTable * const ph, const int size) ;

/*	操作:	查找并返回表中数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定的数据	*/
/*	操作后:	如果可能, 返回一个指向数据域为指定数据的元素的指针; 否则返回一个指向停留在查找过程结束时元素位置的指针	*/
Cell * Find (const HashTable * const ph, const Item item) ;

/*	操作:	向表中添加一个数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定的数据	*/
/*	操作后:	如果可能, 数据域为指定数据的元素被添加到表中, 返回1; 否则返回0	*/
int Insert (const HashTable * const ph, const Item item) ;

/*	操作:	从表中删除一个数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定的数据	*/
/*	操作后:	如果可能, 数据域为指定数据的元素被从表中删除, 返回1; 否则返回0	*/
int Delete (const HashTable * const ph, const Item item) ;

/*	操作:	从低索引向高索引依次将一个函数作用于表中所有元素一次	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个Cell类型参数的函数	*/
/*	操作后:	从低索引向高索引依次将 pfun 指向的函数作用于表中所有元素一次	*/
void Traversal (const HashTable * const ph, void (* pfun) (const Cell cell)) ;

/*	操作:	释放一个表占用的内存空间	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	该表占用的内存空间被释放	*/
void Release (const HashTable * const ph) ;
