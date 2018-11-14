/*
 * st_hash_common.h
 *
 *  Created on: 2011-11-28
 *      Author: kine
 */

#ifndef ST_HASH_COMMON_H_
#define ST_HASH_COMMON_H_
#include "stlib.h"

ST_BEGIN_DECLS ;




/*	数据类型定义	*/
typedef int HItem ;
typedef char*	STRItem ;

enum KindOfEntry
{
	Legitimate, 		// 合法的
	Empty,
	Deleted
} ;

typedef struct cell
{
	HItem item ;
	enum KindOfEntry info ;
	int times ;
} Cell ;

typedef struct oa_hashtable
{
	int size ;
	int used ;					/*	使用中元素的数量, 重复添加不增加此数据	*/
	Cell * lists ;
} * OAHashTable ;

/*	操作:	根据传递来的数据产生一个值并返回	*/
/*	操作前:	item , size 是用来计算产生数值的数据	*/
/*	操作后:	通过计算产生一个值并返回	*/
int STHash (const int item, const int size);

/*	操作:	根据两个传递来的数据产生一个数据并返回	*/
/*	操作前: item 和 prime 是接受的数据	*/
/*	操作后:	根据item 和 prime 产生一个数据并返回	*/
int STHash2 (const int item, const int prime) ;				// 用于开定地址双散列方法中

/*	操作:	根据传递来的数据产生一个值并返回,直接使用字符串的andII码	*/
/*	操作前:	item , size 是用来计算产生数值的数据	*/
/*	操作后:	通过计算产生一个值并返回	*/
// 直接用字符串的ancii码作为键值
int STRHash(char *string);

/*
这是一位牛人对这些字符串hash函数的测试数据
Hash函数	数据1	数据2	数据3	数据4	数据1得分	数据2得分	数据3得分	数据4得分	平均分
BKDRHash	2		0		4774	481		96.55		100			90.95		82.05		92.64
APHash		2		3		4754	493		96.55		88.46		100			51.28		86.28
DJBHash		2		2		4975	474		96.55		92.31		0			100			83.43
JSHash		1		4		4761	506		100			84.62		96.83		17.95		81.94
RSHash		1		0		4861	505		100			100			51.58		20.51		75.96
SDBMHash	3		2		4849	504		93.1		92.31		57.01		23.08		72.41
PJWHash		30		26		4878	513		0			0			43.89		0			21.95
ELFHash		30		26		4878	513		0			0			43.89		0			21.95
*/
// BKDR Hash Function
unsigned int BKDRHash(char *str);

unsigned int SDBMHash(char *str);

// RS Hash Function
unsigned int RSHash(char *str);

// JS Hash Function
unsigned int JSHash(char *str);

// P. J. Weinberger Hash Function
unsigned int PJWHash(char *str);

// ELF Hash Function
unsigned int ELFHash(char *str);

// DJB Hash Function
unsigned int DJBHash(char *str);

// AP Hash Function
unsigned int APHash(char *str);

// OpenSSL中出现的字符串Hash函数
unsigned long OPENSSLHash(char *str);

// 来自暴雪的高效hash算法
//unsigned long SNHash(const char *lpszFileName, unsigned long dwHashType );


int Get_Prime_Size (const int size) ;
int Is_A_Prime_Number (const int number) ;
int Square_ (const int i);


ST_END_DECLS ;
#endif /* ST_HASH_COMMON_H_ */
