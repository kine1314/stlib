#ifndef	__ST_DISJOINT_SET_H__
#define	__ST_DISJOINT_SET_H__
#include "stlib.h"

ST_BEGIN_DECLS ;
#define NumSets 16

#define DJSOOS 				(-65536)
#define DJSSIZE 			(-1)
#define DJSHEIGHT 			(0)

/*
 * (union-find sets)是一种简单的用途广泛的集合. 并查集是若干个不相交集合，
 * 能够实现较快的合并和判断元素所在集合的操作，应用很多。一般采取树形结构来存储并查集，
 * 并利用一个rank数组来存储集合的深度下界，在查找操作时进行路径压缩使后续的查找操作加速。
 * 这样优化实现的并查集，空间复杂度为O(N)，建立一个集合的时间复杂度为O(1)，N次合并M查找
 * 的时间复杂度为O(M Alpha(N))，这里Alpha是Ackerman函数的某个反函数，在很大的范围内
 * （人类目前观测到的宇宙范围估算有10的80次方个原子，这小于前面所说的范围）这个函数的值
 * 可以看成是不大于4的，所以并查集的操作可以看作是线性的。它支持以下三种操作:
 *　  －Union (Root1, Root2) //并操作；把子集合Root2并入集合Root1中.要求：Root1和 Root2互不相交,否则不执行操作.
 *　　－Find (x) //搜索操作；搜索元素x所在的集合,并返回该集合的名字.
 *　　－UFSets (s) //构造函数。将并查集中s个集合初始化为s个只有一个单元素的子集合.
 */

/*	数据类型定义	*/

typedef int 	DJSItem ;
typedef DJSItem DJSType   ;
//typedef DJSType DisjiontSet[ NumSets + 1 ] ;		// 用数组才存储森林树集合！
typedef DJSType * DisjiontSet ;		// 用数组才存储森林树集合！

/*	接口函数声明	*/

/*	操作:	按高度初始化一个不相交集和	*/
/*	操作前:	gather 是一个不相交集合, size 是指示不相交集合的大小	*/
/*	操作后:	除将第一个集合数据域设置为集合的实际大小外, 将所有集合数据域被初始化为HEIGHT	*/
void DJSInitializeAsHeight (DisjiontSet gather, const int size) ;

/*	操作:	按大小初始化一个不相交集合	*/
/*	操作前:	gather 是一个不相交集合, size 指示不相交集合的大小	*/
/*	操作后:	除将第一个集合数据域位置为集合的实际大小外, 所有集合数据域被初始化为SIZE	*/
void DJSInitializeAsSize (DisjiontSet gather, const int size) ;

/*	操作:	按树的高度求并两个集合	*/
/*	操作前:	gather 是一个已初始化的不相交集合, root1, root2 是两个集合类型的变量	*/
/*	操作后:	如果集合类型在 gather 中, 按高度求并 root1 集合和 root2 集合, 返回1; 否则返回0	*/
int DJSSetUnionAsHeight (DisjiontSet gather, DJSType root1, DJSType root2) ;

/*	操作:	按树的大小求并两个集合	*/
/*	操作前:	gather 是一个已初始化的不相交集合, root1, root2 是两个集合类型的变量	*/
/*	操作后:	如果集合类型在 gather 中, 按大小求并 root1 集合和 root2 集合, 返回1; 否则返回0	*/
int DJSSetUnionAsSize (DisjiontSet gather, DJSType root1, DJSType root2) ;

/*	操作:	根据一个不相交集合和一个数据, 查找并返回该数据所在集合类型, 并进行路径压缩	*/
/*	操作前:	gather 是一个已初始化的不相交集合, item 是一个Item类型变量	*/
/*	操作后:	如果 item 所在集合在 gather 中, 找到并返回 item 所在集合的类型, 并进行路径压缩; 否则返回 OOS	*/
DJSType DJSFind (DisjiontSet gather, const DJSItem item) ;



ST_END_DECLS ;
#endif	/* __ST_DISJOINT_SET_H__ */

