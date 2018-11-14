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
		cout<<"*           ��ӭ����B+����ʾ������ѡ����Ӧ���ܡ�                *"<<endl;
		cout<<"*           1���������һ��B+����                                 *"<<endl;
 		cout<<"*           2����B+��������Ҷ����һ������                         *"<<endl;
		cout<<"*           3����B+�������ø�����һ������                         *"<<endl;
		cout<<"*           4����B+���в���һ������                               *"<<endl;
		cout<<"*           5����B+����ɾ��һ������                               *"<<endl;
		cout<<"*           6����ʾ����B+����                                     *"<<endl;
		cout<<"*           0���˳�����                                         *"<<endl;
		cout<<"*******************************************************************"<<endl;
		cout<<"��ѡ��"<<endl;
		cin>>choice;
		int m;
		switch (choice)
		{
			case 1:
				system("cls");
				cout<<"��ѡ����Ǵ���B+��"<<endl;
				cout<<"���������(>=3)"<<endl;
				cin>>BTree::number;
				cout<<"���������ݸ���(10-150)��"<<endl;
				cin>>m;
				Create(m);
				cout<<"�����ɹ�"<<endl;
				bbprinttree(BTree::root);
				getchar();
				break;

			case 2:
				system("cls");
				cout<<"��B+��������Ҷ��������һ����"<<endl;
				cout<<"������Ҫ���ҵ���ֵ��"<<endl;
				cin>>m;
				searchlink(m);
				getchar();
				break;
			case 3:
				system("cls");
				cout<<"��B+�������ø�����һ����"<<endl;
				cout<<"������Ҫ���ҵ���ֵ��"<<endl;
				cin>>m;
				searchroot(m);
				getchar();
				break;

			case 4:
				system("cls");
				cout<<"��ѡ����ǲ���һ���Զ������"<<endl;
				cout<<"����ǰ��������:"<<endl;
				bbprinttree(BTree::root);
				cout<<"������Ҫ�������ֵ��"<<endl;
				cin>>m;
				if(BTree::inserttree(m)==1)cout<<"����ɹ�"<<endl;
				else cout<<"����ʧ�ܣ�������ͬԪ��"<<endl;
				cout<<"������������"<<endl;
				bbprinttree(BTree::root);
				getchar();
				break;

			case 5:
				system("cls");
				cout<<"��ѡ�����ɾ��һ���Զ������"<<endl;
				cout<<"ɾ��ǰ��������:"<<endl;
				bbprinttree(BTree::root);
				cout<<"������Ҫɾ������ֵ��"<<endl;
				cin>>m;
				BTree::treedel(m);
				cout<<"ɾ�����������:"<<endl;
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
	cout << "ȡ�ó�ʼ��ɢ��������Ϊ��" << hash_test.GetTableLength() << endl;
	bool is_success = hash_test.SetHashTable( "test" );

	if ( is_success )
	{
		cout << "ɢ�н��һ���ɹ���" << endl;
	}
	else
	{
		cout << "ɢ�н��һ��ʧ�ܣ�" << endl;
	}

	is_success = hash_test.SetHashTable( "����" );

	if ( is_success )
	{
		cout << "ɢ�н�������ɹ���" << endl;
	}
	else
	{
		cout << "ɢ�н������ʧ�ܣ�" << endl;
	}

	long pos = hash_test.GetHashTablePos( "test" );
	cout << "���Ҳ����ַ�����\"test\" ��ɢ��λ�ã�" << pos << endl;
	pos = hash_test.GetHashTablePos( "����" );
	cout << "���Ҳ����ַ����������ԡ� ��ɢ��λ�ã�" << pos << endl;

	//////////////////////////////////////////////////////////////////////////

	// ɢ�в���

	for ( int i = 0; i < TESTNUM; i++ )
	{
		char buff[32];
		sprintf(buff, "abcdefg%d.", i);
		is_success = hash_test.SetHashTable(buff);
		is_success ? cout << buff << "ɢ�н�����ɹ���λ�ã�" << hash_test.testid << endl : cout << buff << "ɢ�н����ʧ�ܣ�" << endl;
	}

	//system( "pause" );

	//////////////////////////////////////////////////////////////////////////

	// ���Ҳ���

	for ( int i = 0; i < TESTNUM; i++ )
	{
		char buff[32];
		sprintf(buff, "abcdefg%d.", i);
		pos = hash_test.GetHashTablePos( buff );
		pos != -1 ?  cout << "���Ҳ����ַ�����"<< buff <<" ��ɢ��λ�ã�" << pos << endl : cout << buff << "���ڳ�ͻ��" << endl;
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
