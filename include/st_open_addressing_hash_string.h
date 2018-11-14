/*
 * st_open_addressing_hash_string.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_OPEN_ADDRESSING_HASH_STRING_H_
#define ST_OPEN_ADDRESSING_HASH_STRING_H_
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;

#define HASH_LENGTH 100               			//哈希表的长度         
#define NAME_NO 	60                   		//人名的个数  

typedef struct _NAME    
{   
	char *py;    				//名字的拼音
	char *data;	 				// 数据
    int k;       				//拼音所对应的整数
    int si;     				//查找长度
    enum KindOfEntry info ;		// 数据的状态
}NAME, *NAMEP;
//   
typedef struct    //哈希表
{   
	char *py;   //名字的拼音
	char *data;
    int k;      //拼音所对应的整数
    int si;     //查找长度
    int size ;
}HASH, *HASHP;


void   	Display(HASH *HL) ; 				// 显示哈希表       
void  	FindList(HASH *HL, char *name); 	// 查找   
void 	CreateHashList(NAME *NL, HASH *HL); // 建立哈希表   
void 	EraseHashList(HASH *HL);			// 擦出列表的数据


typedef struct _StringHashT
{
	
	int size ;
	NAMEP sname ;
} * StringHashTP, StringHashT ;



/*	操作:	初始化一个字符串散列表	*/
/*	操作前:	size 是指定字符串散列表的大小的变量	*/
/*	操作后:	该表被创建并且表中的所有表元指针被初始化为空, 返回该表	*/
StringHashTP STRHInitializeTable (const int size) ;

/*	操作:	返回一个指向表中指定数据所在结点的指针	*/
/*	操作前:	item 是被查找的数据, h 是一个已初始化的表	*/
/*	操作后:	如果可能, 返回指向表中指定数据所在结点的指针; 否则返回NULL	*/
NAMEP STRHFind (const STRItem item, const StringHashTP * h) ;

/*	操作:	将一个具有指定数据以插入新结点的方式插入到表中	*/
/*	操作前:	item 是待插入的数据, ph 指向一个已初始化的表	*/
/*	操作后:	如果可能, 以 item 为数据创建一个结点被插入到表中(如果冲突, 继续找位置), 返回1; 否则返回0	*/
int STRHInsert (const STRItem item, StringHashTP * const ph) ;	

/*	操作:	从表中删除一个结点	*/
/*	操作前:	item 是待删除结点的数据, ph 指向一个已初始化的表	*/
/*	操作后:	如果可能, item 所在结点被从表中删除, 返回1; 否则返回0	*/
int STRHDelete (const STRItem item, StringHashTP * const ph) ;

/*	操作:	从低索引向高索引将一个函数作用于表中所有存在的结点	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个ListNode *类型参数的函数	*/
/*	操作后:	pfun 指向的函数被从低索引向高索引作用到所有存在的结点一次	*/
void STRHDisplay (const StringHashTP * const ph) ;

/*	操作:	清空一个表	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	该表所占用的全部内存空间被释放	*/
void STRHRelease (StringHashTP * ph) ;

ST_END_DECLS ;

#endif	/* ST_OPEN_ADDRESSING_HASH_STRING_H_ */

