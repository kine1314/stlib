	/*	lefttist_heap.h -- 左式堆头文件	*/
#define INSERT(h, x) h = Insert (h, x)			/*	宏和参数之间不能有空格	*/
#define DELETEMIN(h) (h = DeleteMin (h))

/*	数据类型定义	*/

typedef int Item ;
typedef struct node
{
	Item item ;
	struct node * left ;
	struct node * right ;
	int NPL ;
} Node ;
typedef Node * Heap ;

/*	接口函数声明	*/

/*	操作:	创建并初始化一个空左式堆	*/
/*	操作前:	pheap 指向一个左式堆	*/
/*	操作后:	如果内存分配成功, 创建 pheap 指向的左式堆, 将其置为空堆, 返回1; 否则返回0	*/
int CreateANullHeap (Heap * const pheap) ;

/*	操作:	确定一个左式堆是否为空	*/
/*	操作前:	heap 是一个已初始化的堆	*/
/*	操作后:	如果该堆为空, 返回1; 否则返回0	*/
int HeapIsEmpty (const Heap heap) ;

/*	操作:	合并两个左式堆并返回新堆	*/
/*	操作前:	h1, h2 是两个已初始化的左式堆	*/
/*	操作后:	两个堆被合并并且被返回	*/
Heap Merge (const Heap h1, const Heap h2) ;

/*	操作:	将一个新数据添加到左式堆中	*/
/*	操作前:	heap 是一个已初始化的堆, item 是指定的新数据	*/
/*	操作后:	如果内存分配成功, item 被添加到堆中, 返回新堆; 否则返回原堆	*/
Heap Insert (Heap heap, const Item item) ;

/*	操作:	删除左式堆中的最小元素	*/
/*	操作前:	heap 是一个已初始化的堆	*/
/*	操作后:	如果堆不为空, 删除最小元素, 返回新堆; 否则返回原堆	*/
Heap DeleteMin (const Heap heap) ;

/*	操作:	查找并返回左式堆中的一个具有指定关键字的节点	*/
/*	操作前:	heap 是一个已初始化的左式堆, item 是指定的关键字	*/
/*	操作后:	如果找到, 返回指向该节点的指针; 否则返回NULL	*/
Node * Find (const Heap heap, const Item item) ;

/*	操作:	根据一个数据数组构建一个左式堆	*/
/*	操作前:	heap 是一个已初始化的堆, array 是一个数据数组, size 是数组大小	*/
/*	操作后:	如果内存分配成功, 构建以数组 array 为元素关键字的左式堆, 返回该堆; 否则返回NULL	*/
Heap Bulid (Heap heap, const Item * array, const int size) ;

/*	操作:	层序遍历一个左式堆	*/
/*	操作前:	heap 是一个已初始化的左式堆	*/
/*	操作后:	层序遍历该堆	*/
void LevelOrderTraversal (const Heap heap) ;