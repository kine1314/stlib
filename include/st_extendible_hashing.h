/*
 * st_extendible_hashing.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_EXTENDIBLE_HASHING_H_
#define ST_EXTENDIBLE_HASHING_H_
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;
#define EX_M 		4				// 定义子目录的大小
#define EX_LENTH 	8
#define NO 			0
#define YES 		1

/*	数据类型定义	*/

typedef unsigned char EXItem ;		/*	数据	*/
typedef struct ex_unit
{
	EXItem * array ;				/*	数据数组	*/
	char sub ;						/*	使用中表元的数量	*/
} EXUnit ;							/*	数据单元	*/
typedef struct ex_subdir
{
	EXUnit * point ;				/*	指向数据单元的指针	*/
	char point_to_itself ;			/*	标记是否指向的其本身的数据空间	*/
	char byte_index ;				/*	位索引值	*/
} EXSubdir ;						/*	子目录	*/
typedef struct ex_htable
{
	EXSubdir * directory ;			/*	目录(子目录数组)	*/
	char directory_size ;			/*	目录大小	*/
	char index_digit ;				/*	索引位数	*/
	char item_digit ;				/*	数据位数	*/
	char array_size ;				/*	数据数组大小	*/
} * EXHTable ;


/*	将数据类型限制为char类型.有符号8位二进制,这样利于操作	*/

/*	接口函数声明	*/

/*	操作:	根据二个输入数据产生一个数值并返回	*/
/*	操作前:	pitem 指向指定数据, constant 是被移位的数值	*/
/*	操作后:	产生一个数值并返回	*/
int EXHash (const EXItem * const pitem, const char constant) ;

/*	操作:	创建并初始化一个可扩散列表	*/
/*	操作前:	ptable 指向一个可扩散列表	*/
/*	操作后:	如果内存分配成功, 创建该可扩散列表, 目录大小初始化为4, 索引位数初始化为2, 数据数组大小初始化为4, 返回1; 否则返回0	*/
int EXInitializeTable (EXHTable * const ptable) ;

/*	操作:	向可扩散列表中添加一个元素	*/
/*	操作前:	ptable 指向一个已初始化的可扩散列表, pitem 指向指定的数据	*/
/*	操作后:	如果未重复添加, 如果内存分配成功, 将指定的数据添加到可扩散列表中, 返回1; 否则返回0	*/
int EXInsert (const EXHTable * const ptable, const EXItem * const pitem) ;

/*	操作:	查找并返回可扩散列表中的一个指定数据	*/
/*	操作前:	ptable 指向一个已初始化的可扩散列表, pitem 指向指定的数据	*/
/*	操作后:	如果找到, 返回1; 否则返回0	*/
int EXFind (const EXHTable * const ptable, const EXItem * const pitem) ;

/*	操作:	从可扩散列表目录的低索引向高索引依次将一个函数作用于point指针指向其自身数据空间的的子目录	*/
/*	操作前:	ptable 指向一个已初始化的可扩散列表, pfun 指向一个没有返回值, 接受一个Subdirectories类型参数的函数	*/
/*	操作后:	从可扩散列表目录的低索引向高索引依次将一个函数作用于point指针指向其自身数据空间的的子目录	*/
void EXTraversal (const EXHTable * const ptable, void (* pfun) (const EXSubdir ex_subdir)) ;

/*	操作:	从可扩散列表中删除一个指定数据	*/
/*	操作前:	ptable 指向一个已初始化的可扩散列表, pitem 是准备删除的数据	*/
/*	操作后:	如果找到该数据, 将该数据从可扩散列表中删除, 返回1; 否则返回0	*/
int EXDelete (const EXHTable * const ptable, const EXItem * const pitem) ;

/*	操作:	清空可扩散列表占用的内存空间	*/
/*	操作前:	pteble 指向一个已初始化的可扩散列表	*/
/*	操作后:	该可扩散列表占用的内存空间被释放	*/
void EXRelease (const EXHTable * const ptable) ;


ST_END_DECLS ;
#endif /* ST_EXTENDIBLE_HASHING_H_ */
