/*
 * st_separate_chaining_hash.h
 *
 *  Created on: 2011-11-28
 *      Author: kine
 */

#ifndef ST_SEPARATE_CHAINING_HASH_H_
#define ST_SEPARATE_CHAINING_HASH_H_
/*	Separate_Chaining_Hash.h -- 分离链接散列表头文件 此版本是采用的key % tablesize的散列方法，　并且不能对表头进行操作	*/

#include "stlib.h"
#include "st_hash_common.h"
ST_BEGIN_DECLS ;

#define MAXTABLESIZE 4096
#define CONSTANT 10

/*
话说这个东西原本以为很快就会写好,即使是前天才看是看的.实现部分用的就是一个表和size个链表.
可事实上我写了不下8小时...写完了就好啊,不然我会很郁闷呢.主要卡壳的地方就是定义数据类型的
时候,我反反复复更改了不下五遍.不想回忆起那些错误的行为,我想把我实现的思想说出来来帮助自己强化记忆.
分离链接散列表用来解决冲突的问题,一旦发生冲突时就可以把数据放入相应索引指针指向的链表中.
在定义完链表结构之后.使Header成为指向链表结点的指针.表定义为指向Header的指针.之所以定义为
指向Header的指针是因为这样做可以避免通过将索引*伸缩因子来访问表中元素,操作更加简单,对用户来说更加方便.
知道了这些,实现就不难了,我知道这些可是做了很多尝试的.虽然往往事后都发现自己当初的自以为是有
多么愚蠢.但我还是非常喜欢现在自以为是的感觉,好了,贴出代码.这些话都是用来强化自己记忆的,代码才最能说明问题!
*/

/*
 * 与开放定址法相比，拉链法有如下几个优点：
　　①拉链法处理冲突简单，且无堆积现象，即非同义词决不会发生冲突，因此平均查找长度较短；
　　②由于拉链法中各链表上的结点空间是动态申请的，故它更适合于造表前无法确定表长的情况；
　　③开放定址法为减少冲突，要求装填因子α较小，故当结点规模较大时会浪费很多空间。
		而拉链法中可取α≥1，且结点较大时，拉链法中增加的指针域可忽略不计，因此节省空间；
　　④在用拉链法构造的散列表中，删除结点的操作易于实现。只要简单地删去链表上相应的结点即可。
		而对开放地址法构造的散列表，删除结点不能简单地将被删结点的空间置为空，否则将截断
		在它之后填人散列表的同义词结点的查找路径。这是因为各种开放地址法中，空地址单元
		(即开放地址)都是查找失败的条件。因此在用开放地址法处理冲突的散列表上执行删除操作，
		只能在被删结点上做删除标记，而不能真正删除结点。

（3）拉链法的缺点
		拉链法的缺点是：指针需要额外的空间，故当结点规模较小时，开放定址法较为节省空间，
		而若将节省的指针空间用来扩大散列表的规模，可使装填因子变小，这又减少了开放定址法中的冲突，从而提高平均查找速度。
 * */

/* 由于分离链接散列需要分配指针，所以导致速度，多少有点减慢，所以需要接下来的开放定址法！ */

/*	数据类型定义	*/

typedef struct sp_list_node
{
	HItem item ;
	struct sp_list_node * next ;
} SPListNode ;
typedef SPListNode * SPHeader ;
typedef struct sp_hashtable
{
	int size ;
	SPHeader * lists ;
} * SPHashTable ;



/*	操作:	初始化一个分离链接散列表	*/
/*	操作前:	size 是指定分离链接散列表的大小的变量	*/
/*	操作后:	该表被创建并且表中的所有表元指针被初始化为空, 返回该表	*/
SPHashTable SPInitializeTable (const int size) ;

/*	操作:	返回一个指向表中指定数据所在结点的指针	*/
/*	操作前:	item 是被查找的数据, h 是一个已初始化的表	*/
/*	操作后:	如果可能, 返回指向表中指定数据所在结点的指针; 否则返回NULL	*/
SPHeader SPFind (const HItem item, const SPHashTable h) ;

/*	操作:	将一个具有指定数据以插入新结点的方式插入到表中	*/
/*	操作前:	item 是待插入的数据, ph 指向一个已初始化的表	*/
/*	操作后:	如果可能, 以 item 为数据创建一个结点被插入到表中(如果冲突, 它将出现在链表的最前面的位置), 返回1; 否则返回0	*/
int SPInsert (const HItem item, SPHashTable * const ph) ;

/*	操作:	从表中删除一个结点	*/
/*	操作前:	item 是待删除结点的数据, ph 指向一个已初始化的表	*/
/*	操作后:	如果可能, item 所在结点被从表中删除, 返回1; 否则返回0	*/
int Delete (const HItem item, SPHashTable * const ph) ;

/*	操作:	从低索引向高索引将一个函数作用于表中所有存在的结点	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个ListNode *类型参数的函数	*/
/*	操作后:	pfun 指向的函数被从低索引向高索引作用到所有存在的结点一次	*/
void SPTraversal (const SPHashTable * const ph, void (* pfun) (const SPListNode * const pnode)) ;

/*	操作:	清空一个表	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	该表所占用的全部内存空间被释放	*/
void SPRelease (SPHashTable * ph) ;

ST_END_DECLS ;

#endif /* ST_SEPARATE_CHAINING_HASH_H_ */
