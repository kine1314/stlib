/*
 * st_b+_tree.h
 *
 *  Created on: 2011-12-5
 *      Author: kine
 */

#ifndef ST_B__TREE_CPP_H_
#define ST_B__TREE_CPP_H_

//#include "stlib.h"

//ST_BEGIN_DECLS;
class BTree
{
public:
	int n;       								//该节点所含关键字的个数  大于等于2
	BTree *father;
	static int number;							//阶数   大于等于3
	static BTree *root;
	BTree();
	int *data;
	BTree **down;

	static bool inserttree(int t);				//在树中插入t
	static	BTree* searchinsert(int t);			//搜索插入到某节点
	bool insertpoint(int t,BTree *p);			//在节点插入
	void split(int t,BTree *p);  				//分裂

	static void treedel(int t);
	void  delpoint(int t);
	static BTree*searchdel(int t);				//搜索删除某节点
	void combine();

	static int deep;  							//深度
	static void deletetree();
};


class dui					// b+tree的堆炒作
{
public :
	BTree * data[200];  	//元素
	int   num[200];    		//该元素是第几层的
	int tp,tl;				//tp为队头，tl为队尾
	dui(){tp=0;tl=0;}		// 初始化构造函数
	BTree* pop();
	void push(BTree*,int);
	bool empty();
};

struct node
{
   BTree* q;
   node *next;
};


extern void Create(int m) ;
extern void searchlink(int t) ;
extern void searchroot(int t) ;
extern void st_bb_tree_cpp_test(void);
extern void bbprinttree(BTree *q);


//ST_END_DECLS;


#endif /* ST_B__TREE_CPP_H_ */
