/*	PriorityQueue.h -- 最小堆头文件	*/
#include "Head.h"

/*	接口函数声明	*/

/*	操作:	创建并初始化一个优先队列	*/
/*	操作前:	ppq 指向一个优先队列, size 是指定该优先队列大小的变量	*/
/*	操作后:	如果 size > 0 && 内存分配成功, 创建并初始化该优先队列, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
BOOL Initialize_P (PriorityQueue * const ppq, const int size) ;

/*	操作:	确定一个优先队列是否为空	*/
/*	操作前:	ppq 指向一个已初始化的优先队列	*/
/*	操作后:	如果该优先队列为空, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
BOOL IsEmpty_P (const PriorityQueue * const ppq) ;

/*	操作:	确定一个优先队列是否已满	*/
/*	操作前:	ppq 指向一个已初始化的优先队列	*/
/*	操作后:	如果该优先队列已满, 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (1)	*/
BOOL IsFull_P (const PriorityQueue * const ppq) ;

/*	操作:	向一个优先队列中插入一个结点	*/
/*	操作前:	ppq 指向一个已初始化的优先队列, pn 是待添加到队列中的结点	*/
/*	操作后:	如果该优先队列未满, 向该优先队列中添加 pn , 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
BOOL Insert_P (const PriorityQueue * const ppq, const PriorityNode pn) ;

/*	操作:	删除并返回优先队列中数据域最小的结点	*/
/*	操作前:	ppq 指向一个已初始化的优先队列	*/
/*	操作后:	如果该优先队列不为空, 删除并返回数据域最小的结点; 否则返回 NULL	*/
/*	时间复杂度:	O (log N)	*/
PriorityNode DeleteMin_P (const PriorityQueue * const ppq) ;

/*	操作:	增加优先队列中指定位置的结点的数据指定值	*/
/*	操作前:	ppq 指向一个已初始化的优先队列, position 指定位置, delta 是改变量	*/
/*	操作前:	如果 position 为有效位置 && delta > 0, 将优先队列中 position 位置的结点的数据增加 delta , 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
BOOL IncreaseKey_P (const PriorityQueue * const ppq, const int position, const Item delta) ;

/*	操作:	减少优先队列中指定位置结点的数据指定值	*/
/*	操作前:	ppq 指向一个已初始化的优先队列, position 指定位置, delta 是改变量	*/
/*	操作后:	如果 position 是有效位置 && delta > 0, 将优先队列中 position 位置的结点的数据减少 delta , 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
BOOL DecreaseKey_P (const PriorityQueue * const ppq, const int position, const Item delta) ;

/*	操作:	释放一个优先队列占用的内存空间	*/
/*	操作前:	ppq 指向一个已初始化的优先队列	*/
/*	操作后:	该优先队列占用的内存空间被释放	*/
/*	时间复杂度:	O (N)	*/
void Release_P (const PriorityQueue * const ppq) ;