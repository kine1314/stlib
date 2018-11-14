/*
 * st_open_addressing_hash_2.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_OPEN_ADDRESSING_HASH_2_H_
#define ST_OPEN_ADDRESSING_HASH_2_H_
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;


/*	接口函数声明	*/


/*	操作:	创建并初始化一个表	*/
/*	操作前:	ph 指向一个表, size 是指示表的大小的变量	*/
/*	操作后:	如果可能, 该表被创建并且所有元素数据域被置为空, 如果 size 不是素数, 则取大于 size 的最小素数为表的大小, 返回1; 否则返回0	*/
int OA2InitializeTable (OAHashTable * const ph, const int size) ;

/*	操作:	查找并返回表中数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定的数据	*/
/*	操作后:	如果可能, 返回一个指向数据域为指定数据的元素的指针; 否则返回一个指向停留在查找过程结束时元素位置的指针	*/
Cell * OA2Find (const OAHashTable * const ph, const HItem item) ;

/*	操作:	向表中添加一个数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定的数据	*/
/*	操作后:	如果可能, 数据域为指定数据的元素被添加到表中, 返回1; 否则返回0	*/
int OA2Insert (const OAHashTable * const ph, const HItem item) ;

/*	操作:	从表中删除一个数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定的数据	*/
/*	操作后:	如果可能, 数据域为指定数据的元素被从表中删除, 返回1; 否则返回0	*/
int OA2Delete (const OAHashTable * const ph, const HItem item) ;

/*	操作:	从低索引向高索引依次将一个函数作用于表中所有元素一次	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个Cell类型参数的函数	*/
/*	操作后:	从低索引向高索引依次将 pfun 指向的函数作用于表中所有元素一次	*/
void OA2Traversal (const OAHashTable * const ph, void (* pfun) (const Cell cell)) ;

/*	操作:	释放一个表占用的内存空间	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	该表占用的内存空间被释放	*/
void OA2Release (const OAHashTable * const ph) ;



ST_END_DECLS ;
#endif /* ST_OPEN_ADDRESSING_HASH_2_H_ */
