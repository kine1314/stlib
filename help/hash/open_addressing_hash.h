/*	open_addressing_hash.h -- 开放定址散列表头文件	开放定址散列表(线性探测法)头文件C语言*/

enum KindOfEntry {Legitimate, Empty, Deleted} ;

/*	数据类型定义	*/

typedef int Item ;
typedef struct cell
{
	Item item ;
	enum KindOfEntry info ;
} Cell ;
typedef struct hashtable
{
	int size ;
	Cell * lists ;
} * HashTable ;

/*	接口函数声明	*/

/*	操作:	接受一个Item类型变量, 以此为基础通过运算产生一个数值并返回用	*/
/*	操作前:	item 是一个Item类型变量, size 是表的大小	*/
/*	操作后:	以接受的参数为基础通过运算产生一个数值并返回	*/
int Hash (const Item item, const int size) ;

/*	操作:	创建并初始化一个表	*/
/*	操作前:	ph 指向一个表, size 是指定表大小的变量	*/
/*	操作后:	如果可能, 该表被创建并且所有表元数据域被置为空(如果 size 不是素数, 则取大于 size 的最小素数作为表的大小), 返回1; 否则返回0	*/
int InitializeTable (HashTable * const ph, const int size) ;

/*	操作:	返回一个指向数据域为被查找数据的元素在表中的位置的指针	*/
/*	操作前:	ph 指向一个已初始化的表, item 是被查找的数据	*/
/*	操作后:	如果可能, 返回该指针; 否则返回指向遍历的最后的一个元素的指针	*/
Cell * Find (const HashTable * const ph, const Item item) ;

/*	操作:	向表中添加一个数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定被添加的数据	*/
/*	操作后:	如果可能, 创建一个数据域为 item 的元素添加的表中, 返回1; 否则返回0	*/
int Insert (HashTable * const ph, const Item item) ;

/*	操作:	从表中懒惰删除一个数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定被删除的数据	*/
/*	操作后:	如果可能, 数据域为该指定数据的元素被从表中懒惰删除, 返回1; 否则返回0	*/
int Delete (HashTable * const ph, const Item item) ;

/*	操作:	从低索引向高索引将一个函数依次作用于表中的所有元素一次	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个Cell类型参数的函数	*/
/*	操作后:	pfun 指向的函数从表的低索引向高索引依次作用于表中的所有元素一次	*/
void Traversal (const HashTable * const ph, void (* pfun) (const Cell cell)) ;

/*	操作:	清空一个表	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	该表所占用的内存空间被释放	*/
void Release (HashTable * const ph) ;
