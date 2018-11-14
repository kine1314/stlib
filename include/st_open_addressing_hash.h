/*
 * st_open_addressing_hash.h
 *
 *  Created on: 2011-11-28
 *      Author: kine
 */

#ifndef ST_OPEN_ADDRESSING_HASH_H_
#define ST_OPEN_ADDRESSING_HASH_H_
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;

/*	open_addressing_hash.h -- 开放定址散列表头文件	开放定址散列表(线性探测法)头文件C语言*/
/*
 * 用线性探测法处理冲突，思路清晰，算法简单，但存在下列缺点：
　　① 处理溢出需另编程序。一般可另外设立一个溢出表，专门用来存放上述哈希表中放不下的记录。
		此溢出表最简单的结构是顺序表，查找方法可用顺序查找。
　　② 按上述算法建立起来的哈希表，删除工作非常困难。假如要从哈希表 HT 中删除一个记录，
		按理应将这个记录所在位置置为空，但我们不能这样做，而只能标上已被删除的标记，否则，将会影响以后的查找。
　　③ 线性探测法很容易产生堆聚现象。所谓堆聚现象，就是存入哈希表的记录在表中连成一片。
		按照线性探测法处理冲突，如果生成哈希地址的连续序列愈长 ( 即不同关键字值的哈希地址相邻在一起愈长 ) ，
		则当新的记录加入该表时，与这个序列发生冲突的可能性愈大。因此，哈希地址的较长连续序列比较短连续序列生长得快，
		这就意味着，一旦出现堆聚 ( 伴随着冲突 ) ，就将引起进一步的堆聚。
 * */


/*	接口函数声明	*/


/*	操作:	创建并初始化一个表	*/
/*	操作前:	ph 指向一个表, size 是指定表大小的变量	*/
/*	操作后:	如果可能, 该表被创建并且所有表元数据域被置为空(如果 size 不是素数, 则取大于 size 的最小素数作为表的大小), 返回1; 否则返回0	*/
int OAInitializeTable (OAHashTable * const ph, const int size) ;

/*	操作:	返回一个指向数据域为被查找数据的元素在表中的位置的指针	*/
/*	操作前:	ph 指向一个已初始化的表, item 是被查找的数据	*/
/*	操作后:	如果可能, 返回该指针; 否则返回指向遍历的最后的一个元素的指针	*/
Cell * OAFind (const OAHashTable * const ph, const HItem item) ;

/*	操作:	向表中添加一个数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定被添加的数据	*/
/*	操作后:	如果可能, 创建一个数据域为 item 的元素添加的表中, 返回1; 否则返回0	*/
int OAInsert (OAHashTable * const ph, const HItem item) ;

/*	操作:	从表中懒惰删除一个数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定被删除的数据	*/
/*	操作后:	如果可能, 数据域为该指定数据的元素被从表中懒惰删除, 返回1; 否则返回0	*/
int OADelete (OAHashTable * const ph, const HItem item) ;

/*	操作:	从低索引向高索引将一个函数依次作用于表中的所有元素一次	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个Cell类型参数的函数	*/
/*	操作后:	pfun 指向的函数从表的低索引向高索引依次作用于表中的所有元素一次	*/
void OATraversal (const OAHashTable * const ph, void (* pfun) (const Cell cell)) ;

/*	操作:	清空一个表	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	该表所占用的内存空间被释放	*/
void OARelease (OAHashTable * const ph) ;

ST_END_DECLS ;
#endif /* ST_OPEN_ADDRESSING_HASH_H_ */
