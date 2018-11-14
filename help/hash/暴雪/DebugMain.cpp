/////////////////////////////////////////////////////////////////////////////

// Name:        DebugMain.cpp

// Purpose:     ����Hash�㷨��װ���࣬�������������Ͳ��ҹ��ܵĲ��ԡ�

// Author:      ������

// Modified by:

// Created:     07/30/09

// RCS-ID:      $Id: treetest.h 43021 2009-07-30 16:36:51Z VZ $

// Copyright:   (C) Copyright 2009, TSong Corporation, All Rights Reserved.

// Licence:

/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

// ���Բ����趨��

#define TESTNUM 32
#include <iostream>
#include <fstream>
#include "HashAlgo.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////

// ������������ʼ

int main( int argc, char **argv )
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
