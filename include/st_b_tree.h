/*
 * st_b_tree.h
 *
 *  Created on: 2011-12-1
 *      Author: kine
 */

#ifndef	__ST_B_TREE_H__
#define	__ST_B_TREE_H__

#include "stlib.h"

ST_BEGIN_DECLS;

/*
阶为M的b-树是一颗具有以下结构特性的树:
(1)树的根就是一片树叶，或者其儿子数在2至M之间
(2)除根外，所有的非树叶节点的儿子数在[M/2]和M之间
(3)所有的树叶都在相同的深度上
*/
/*
 * B 树是为了磁盘或其它存储设备而设计的一种多叉
 * （下面你会看到，相对于二叉，B树每个内结点有多个分支，即多叉）平衡查找树。
 * 主要为了降低磁盘的io操作；在磁盘中，节点-》磁盘块;关键字-》磁盘文件
 * */

/*
 * 模拟下查找文件29的过程：
 * 1.根据根结点指针找到文件目录的根磁盘块1，将其中的信息导入内存。【磁盘IO操作 1次】
 * 2.此时内存中有两个文件名17、35和三个存储其他磁盘页面地址的数据。根据算法我们发现17<29<35，因此我们找到指针p2。
 * 3.根据p2指针，我们定位到磁盘块3，并将其中的信息导入内存。【磁盘IO操作 2次】
 * 4.此时内存中有两个文件名26，30和三个存储其他磁盘页面地址的数据。根据算法我们发,26<29<30，因此我们找到指针p2。
 * 5.根据p2指针，我们定位到磁盘块8，并将其中的信息导入内存。【磁盘IO操作 3次】
 * 6.此时内存中有两个文件名28，29。根据算法我们查找到文,29，并定位了该文件内存的磁盘地址。
 * */

/*
 * 树中每个结点含有最多含有m个孩子，即m满足：ceil(m/2)<=m<=m。
 * 除根结点和叶子结点外，其它每个结点至少有[ceil(m / 2)]个孩子（其中ceil(x)是一个取上限的函数）；
 * 若根结点不是叶子结点，则至少有2个孩子（特殊情况：没有孩子的根结点，即根结点为叶子结点，整棵树只有一个根节点）；
 * 所有叶子结点都出现在同一层，叶子结点不包含任何关键字信息(可以看做是外部接点或查询失败的接点，实际上这些结点不存在，指向这些结点的指针都为null)；
 * 每个非终端结点中包含有n个关键字信息： (n，P0，K1，P1，K2，P2，......，Kn，Pn)。其中：
       a)   Ki (i=1...n)为关键字，且关键字按顺序升序排序K(i-1)< Ki。
       b)   Pi为指向子树根的接点，且指针P(i-1)指向子树种所有结点的关键字均小于Ki，但都大于K(i-1)。
       c)   除根结点之外的结点的关键字的个数n必须满足： [ceil(m / 2)-1]<= n <= m-1（叶子结点也必须满足此条关于关键字数的性质，根结点除外）。
*/

////* 定义m序(阶)B 树的最小度数BTree_D=ceil(m)*/
/// 在这里定义每个节点中关键字的最大数目为:2 * BTree_D - 1，即序(阶)：2 * BTree_D.
#define BTree_D			2
#define ORDER			(BTree_D * 2) 			//定义为4阶B-tree,2-3-4树。最简单为3阶B-tree,2-3树。
//#define ORDER        (BTree_T * 2-1)			//最简单为3阶B-tree,2-3树。

typedef stint KeyType;
typedef struct BTNode{
	stint keynum;								/// 结点中关键字的个数，keynum <= BTree_N（二叉树一个关键字）
	KeyType key[ORDER-1];						/// 关键字向量为key[0..keynum - 1]
	struct BTNode* child[ORDER];				/// 孩子指针向量为child[0..keynum]
	stbool isLeaf;								/// 是否是叶子节点的标志
}BTNode;

typedef BTNode* BTree;	///定义BTree

///给定数据集data,创建BTree。
void BTree_create(BTree* tree, const KeyType* data, int length);

///销毁BTree，释放内存空间。
void BTree_destroy(BTree* tree);

///在BTree中插入关键字key。
void BTree_insert(BTree* tree, KeyType key);

///在BTree中移除关键字key。
void BTree_remove(BTree* tree, KeyType key);

///深度遍历BTree打印各层结点信息。
void BTree_print(const BTree tree, int layer);

/// 在BTree中查找关键字 key，
/// 成功时返回找到的节点的地址及 key 在其中的位置 *pos
/// 失败时返回 NULL 及查找失败时扫描到的节点位置 *pos
BTNode* BTree_search(const BTree tree, int key, int* pos);


ST_END_DECLS ;
#endif	/* __ST_B_TREE_H__ */

#ifndef ST_B_TREE_H_
#define ST_B_TREE_H_


#endif /* ST_B_TREE_H_ */
