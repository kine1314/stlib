/*
 * st_open_addressing_double_hash.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_OPEN_ADDRESSING_DOUBLE_HASH_H_
#define ST_OPEN_ADDRESSING_DOUBLE_HASH_H_
//开放定址散列表双散列头文件	开放定址散列表（线性探测法（双散列））实现文件C语言
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;
/*	接口函数声明	*/


/*	操作:	创建并初始化一个表	*/
/*	操作前:	ph 指向一个表, size 是用来指示表大小的变量	*/
/*	操作后:	如果可能, 创建该表, 并将所有元素数据域置为空, 如果 size 是素数, 取 size 为表的大小, 否则取大于 size 的最小素数为表的大小, 返回1; 否则返回0	*/
int OADInitializeTable (OAHashTable * const ph, const int size) ;

/*	操作:	查找并返回一个指向数据域为指定数据的元素的指针	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定被查找的数据	*/
/*	操作后:	如果可能, 返回一个指向被查找元素的指针; 否则返回一个指向查找结束时元素位置的指针	*/
Cell * OADFind (const OAHashTable * const ph, const HItem item) ;

/*	操作:	向表中添加一个数据域为指定数据的结点	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定被添加的数据	*/
/*	操作后:	如果可能, 数据域为指定数据的一个新结点被添加到表中, 返回1; 否则不添加, 返回0	*/
int OADInsert (const OAHashTable * const ph, const HItem item) ;

/*	操作:	从表中删除一个数据域为指定数据的结点	*/
/*	操作前: ph 指向一个已初始化的表, item 是指定被删除的数据	*/
/*	操作后:	如果可能, 数据域为指定数据的一个结点被从表中删除, 返回1; 否则不删除, 返回0	*/
int OADDelete (const OAHashTable * const ph, const HItem item) ;

/*	操作:	从低索引向高索引依次将一个函数作用于表中所有元素一次	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个Cell类型参数的函数	*/
/*	操作后:	pfun 指向的函数从低索引向高索引依次作用于表中所有元素一次	*/
void OADTraversal (const OAHashTable * const ph, void (* pfun) (const Cell cell)) ;

/*	操作:	释放一个表占用的内存空间	*/
/*	操作前: ph 指向一个已初始化的表	*/
/*	操作后: 该表占用的内存空间被释放	*/
void OADRelease (const OAHashTable * const ph) ;



ST_END_DECLS ;
#endif /* ST_OPEN_ADDRESSING_DOUBLE_HASH_H_ */
