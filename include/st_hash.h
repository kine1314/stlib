#ifndef	__ST_HASH_H__
#define	__ST_HASH_H__
#include "stlib.h"
#include "st_hash_common.h"


ST_BEGIN_DECLS ;


/*
 * 哈希表主要可以在O(1)时间内对查找对象定位，但是事实上，
 * 如果输入集合不确定的情况下，可能出现大量的冲突，虽然有
 * 很多好的哈希函数，但是随着随机输入，大量冲突还是不可避免，
 * 可能出现最差情况。所以，哈希表如果用在输入集合确定（即以
 * 后只会做查询操作）的情况下，选择合适的函数函数和解决冲突
 * 的方法（perfect hash）可以在O(1)时间内完成查找二叉树
 * 支持动态的插入和查找，保证操作在O(height)时间，这就是完
 * 成了哈希表不便完成的工作，动态性。但是二叉树有可能出现
 * worst-case，如果输入序列已经排序，则时间复杂度为O(N)
 * 哈希表：哈希表查找速度比较快，但是要耗比较多的内存。所以比较适用于对查找速度要求比较高、且内存空间足够的时候
 * 平衡二叉树：如果想在以后用二分法查找的时候查找速度比较快的话用建立平衡二叉树的方法
 * 以下三种情况，很不应该用哈希方法:
	1.内存不足时；
	2.输入数据重复太多或哈希冲突太多时；
	3.没有合适的哈希方法或数据本身就不能哈希时.(如某类型只定义了相等，大于，小于三个操作时......那你怎么去哈希呢？？？？)
 * 选择其它位置的方法有：
	１、开放定址法
		Hi=(H(key)+di) MOD m i=1,2,...,k(k<=m-1)
		其中m为表长，di为增量序列
		如果di值可能为1,2,3,...m-1，称线性探测再散列。
		如果di取值可能为1,-1,2,-2,4,-4,9,-9,16,-16,...k*k,-k*k(k<=m/2)
		称二次探测再散列。
		如果di取值可能为伪随机数列。称伪随机探测再散列。
 *
 * */
#define NULLKEY 	0			// 0为无记录标志


typedef int HashKeyType;// 设关键字域为整型

typedef struct
{
	HashKeyType key;
	stint ord;
}HashElemType; // 数据元素类型

typedef struct
{
	HashElemType *elem; // 数据元素存储基址，动态分配数组
	stint count; // 当前数据元素个数
	stint sizeindex; // hashsize[sizeindex]为当前容量
}HashTable;



// 构造一个空的哈希表
stint InitHashTable(HashTable *H) ;
//  销毁哈希表H
void DestroyHashTable(HashTable *H);
// 在开放定址哈希表H中查找关键码为K的元素,若查找成功,以p指示待查数据
// 元素在表中位置,并返回SUCCESS;否则,以p指示插入位置,并返回UNSUCCESS
// c用以计冲突次数，其初值置零，供建表插入时参考。
stint SearchHash(HashTable H, HashKeyType K, stint *p, stint *c);
// 查找不成功时插入数据元素e到开放定址哈希表H中，并返回1；
// 若冲突次数过大，则重建哈希表。
int InsertHash(HashTable *,HashElemType); // 对函数的声明
// 重建哈希表
void RecreateHashTable(HashTable *H);
// 按哈希地址的顺序遍历哈希表
void TraverseHash(HashTable H,void(*Vi)(stint,HashElemType));
// 在开放定址哈希表H中查找关键码为K的元素,若查找成功,以p指示待查数据
// 元素在表中位置,并返回SUCCESS;否则,返回UNSUCCESS
stint Find(HashTable H,HashKeyType K,stint *p);

ST_END_DECLS ;
#endif	/* __ST_HASH_H__ */
