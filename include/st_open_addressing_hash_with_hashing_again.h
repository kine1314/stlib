/*
 * st_open_addressing_hash_with_hashing_again.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_OPEN_ADDRESSING_HASH_WITH_HASHING_AGAIN_H_
#define ST_OPEN_ADDRESSING_HASH_WITH_HASHING_AGAIN_H_
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;


/*	操作:	根据传递来的参数产生一个int类型值并返回	*/
/*	操作前:	item 是传递来的参数	*/
/*	操作后:	产生一个int类型值并返回	*/
int OAAChange (const HItem item) ;

/*	操作:	创建并初始化一个表	*/
/*	操作前:	ph 指向一个未初始化的表, size 是用来指示表大小的变量	*/
/*	操作后:	如果内存空间分配成功, 表被创建, 并将所有元素数据域置为空, 如果 size 不是素数则取大于 size 的最小素数为表的大小, 返回1; 否则不创建表, 返回0	*/
int OAAInitializeTable (OAHashTable * const ph, const int size) ;

/*	操作:	查找一个数据域为指定数据的元素在表中的位置并返回指向该位置的指针	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定数据	*/
/*	操作后:	如果找到, 返回一个指向数据域为指定数据的元素的指针; 否则返回一个指向查找结束时停留元素处的指针	*/
Cell * OAAFind (const OAHashTable * const ph, const HItem item) ;

/*	操作:	向表中添加一个数据域为指定数据的元素	*/
/*	操作前:	ph 指向一个已初始化的表, item 是指定数据	*/
/*	操作后:	如果找到可容纳新元素的位置, 将数据域为指定数据的元素添加到表中, 如重复则添加出现次数, 返回1; 否则返回0	*/
int OAAInsert (const OAHashTable * const ph, const HItem item) ;

/*	操作:	将一个表再散列为大小为大于等于原表大小2倍的最小素数的表, 并将数据拷贝到新表, 释放原表占用的内存空间	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	如果内存空间分配成功, 新表被创建, 大小为大于等于原表大小2倍的最小素数的表, 原表数据拷贝到新表, 返回1; 否则不改变原表, 返回0	*/
int OAAHashAgain (const OAHashTable * const ph) ;

/*	操作:	将一个数据域为指定数据的元素从表中删除	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作前:	如果找到数据域为指定数据的元素, 将其从表中删除, 返回1; 否则返回0	*/
int OAADelete (const OAHashTable * const ph, const HItem item) ;

/*	操作:	从低索引向高索引依次将一个函数作用于表中所有元素1次	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个Cell类型参数的函数	*/
/*	操作后:	从低索引向高索引一次将pfun指向的函数作用于表中所有元素1次	*/
void OAATraversal (const OAHashTable * const ph, void (* pfun) (const Cell cell)) ;

/*	操作:	释放一个表占用的内存空间	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	该表占用的内存空间被释放	*/
void OAARelease (const OAHashTable * const ph) ;


ST_END_DECLS ;
#endif /* ST_OPEN_ADDRESSING_HASH_WITH_HASHING_AGAIN_H_ */
