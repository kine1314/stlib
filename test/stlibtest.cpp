/*
 * stlibtest.cpp
 *
 *  Created on: 2011-12-5
 *      Author: kine
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <time.h>
#include <stdio.h>
#include "st_log.h"
#include "st_b+_tree_cpp.h"
#include "st_HashAlgo_cpp.h"

using namespace std;
//---------------------------------------
//			b+ tree
//---------------------------------------


void st_bb_tree_cpp_test(void)
{
	int choice;
	do
	{
		system("cls");
		cout<<"*******************************************************************"<<endl;
		cout<<"*           欢迎进入B+树演示程序，请选择相应功能。                *"<<endl;
		cout<<"*           1。随机建立一棵B+树；                                 *"<<endl;
 		cout<<"*           2。在B+树中利用叶子链一个数；                         *"<<endl;
		cout<<"*           3。在B+树中利用根查找一个数；                         *"<<endl;
		cout<<"*           4。在B+树中插入一个数；                               *"<<endl;
		cout<<"*           5。在B+树中删除一个数；                               *"<<endl;
		cout<<"*           6。显示整个B+树；                                     *"<<endl;
		cout<<"*           0。退出程序；                                         *"<<endl;
		cout<<"*******************************************************************"<<endl;
		cout<<"请选择："<<endl;
		cin>>choice;
		int m;
		switch (choice)
		{
			case 1:
				system("cls");
				cout<<"您选择的是创建B+树"<<endl;
				cout<<"请输入阶数(>=3)"<<endl;
				cin>>BTree::number;
				cout<<"请输入数据个数(10-150)："<<endl;
				cin>>m;
				Create(m);
				cout<<"创建成功"<<endl;
				bbprinttree(BTree::root);
				getchar();
				break;

			case 2:
				system("cls");
				cout<<"在B+树中利用叶子链查找一个数"<<endl;
				cout<<"请输入要查找的数值："<<endl;
				cin>>m;
				searchlink(m);
				getchar();
				break;
			case 3:
				system("cls");
				cout<<"在B+树中利用根查找一个数"<<endl;
				cout<<"请输入要查找的数值："<<endl;
				cin>>m;
				searchroot(m);
				getchar();
				break;

			case 4:
				system("cls");
				cout<<"您选择的是插入一个自定义的数"<<endl;
				cout<<"插入前的树如下:"<<endl;
				bbprinttree(BTree::root);
				cout<<"请输入要插入的数值："<<endl;
				cin>>m;
				if(BTree::inserttree(m)==1)cout<<"插入成功"<<endl;
				else cout<<"插入失败，存在相同元素"<<endl;
				cout<<"插入后的树如下"<<endl;
				bbprinttree(BTree::root);
				getchar();
				break;

			case 5:
				system("cls");
				cout<<"您选择的是删除一个自定义的数"<<endl;
				cout<<"删除前的树如下:"<<endl;
				bbprinttree(BTree::root);
				cout<<"请输入要删除的数值："<<endl;
				cin>>m;
				BTree::treedel(m);
				cout<<"删除后的树如下:"<<endl;
				bbprinttree(BTree::root);
				getchar();
				break;

			case 6:
				system("cls");
				bbprinttree(BTree::root);
				getchar();
			break;
		}
	}while(choice);

}



#define TESTNUM 32
int st_stomesnow_hash_test(void)
{
	CHashAlgo hash_test( TESTNUM );
	cout << "取得初始化散列索引表长为：" << hash_test.GetTableLength() << endl;
	bool is_success = hash_test.SetHashTable( "test" );

	if ( is_success )
	{
		cout << "散列结果一：成功！" << endl;
	}
	else
	{
		cout << "散列结果一：失败！" << endl;
	}

	is_success = hash_test.SetHashTable( "测试" );

	if ( is_success )
	{
		cout << "散列结果二：成功！" << endl;
	}
	else
	{
		cout << "散列结果二：失败！" << endl;
	}

	long pos = hash_test.GetHashTablePos( "test" );
	cout << "查找测试字符串：\"test\" 的散列位置：" << pos << endl;
	pos = hash_test.GetHashTablePos( "测试" );
	cout << "查找测试字符串：“测试” 的散列位置：" << pos << endl;

	//////////////////////////////////////////////////////////////////////////

	// 散列测试

	for ( int i = 0; i < TESTNUM; i++ )
	{
		char buff[32];
		sprintf(buff, "abcdefg%d.", i);
		is_success = hash_test.SetHashTable(buff);
		is_success ? cout << buff << "散列结果：成功！位置：" << hash_test.testid << endl : cout << buff << "散列结果：失败！" << endl;
	}

	//system( "pause" );

	//////////////////////////////////////////////////////////////////////////

	// 查找测试

	for ( int i = 0; i < TESTNUM; i++ )
	{
		char buff[32];
		sprintf(buff, "abcdefg%d.", i);
		pos = hash_test.GetHashTablePos( buff );
		pos != -1 ?  cout << "查找测试字符串："<< buff <<" 的散列位置：" << pos << endl : cout << buff << "存在冲突！" << endl;
	}

	//system( "pause" );

	return 0;
}


int main(void)
{
#if 0
	__msg("------------st b+ tree cpp test------------\n");
	st_bb_tree_cpp_test();
#elif 1
	__msg("------------strome snow hash cpp test------------\n");
	st_stomesnow_hash_test( );
#endif
}
