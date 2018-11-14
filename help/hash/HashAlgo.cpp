/////////////////////////////////////////////////////////////////////////////
// Name:        HashAlgo.cpp
// Purpose:     ʹ��ħ��Hash�㷨��ʵ������������Ͳ��ҹ��ܡ�
// Author:      ������
// Modified by:
// Created:     07/30/09
// RCS-ID:      $Id: treetest.h 43021 2009-07-30 16:36:51Z VZ $
// Copyright:   (C) Copyright 2009, TSong Corporation, All Rights Reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "HashAlgo.h"

//////////////////////////////////////////////////////////////////////////
// Ԥ����
void CHashAlgo::prepareCryptTable()
{ 
    unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

    for( index1 = 0; index1 < 0x100; index1++ )
    { 
        for( index2 = index1, i = 0; i < 5; i++, index2 += 0x100 )
        { 
            unsigned long temp1, temp2;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp1 = (seed & 0xFFFF) << 0x10;
            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp2 = (seed & 0xFFFF);
            cryptTable[index2] = ( temp1 | temp2 ); 
        } 
    } 
}

//////////////////////////////////////////////////////////////////////////
// ��ȡ��ϣֵ
unsigned long CHashAlgo::HashString(char *lpszFileName, unsigned long dwHashType)
{ 
    unsigned char *key = (unsigned char *)lpszFileName;
    unsigned long seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;
    int ch;

    while(*key != 0)
    { 
        ch = toupper(*key++);

        seed1 = cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3; 
    }
    return seed1; 
}

//////////////////////////////////////////////////////////////////////////
// �õ��ڶ������е�λ��
long CHashAlgo::GetHashTablePos(char *lpszString)

{ 
    const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
    unsigned long nHash = HashString(lpszString, HASH_OFFSET);
    unsigned long nHashA = HashString(lpszString, HASH_A);
    unsigned long nHashB = HashString(lpszString, HASH_B);
    unsigned long nHashStart = nHash % m_tablelength,
        nHashPos = nHashStart;

    while ( m_HashIndexTable[nHashPos].bExists)
    { 
        if (m_HashIndexTable[nHashPos].nHashA == nHashA && m_HashIndexTable[nHashPos].nHashB == nHashB) 
            return nHashPos; 
        else 
            nHashPos = (nHashPos + 1) % m_tablelength;

        if (nHashPos == nHashStart) 
            break; 
    }

    return -1; //û���ҵ�
}
//////////////////////////////////////////////////////////////////////////
// ͨ�������ַ���������Ӧ�ı���ɢ�е���������Ӧλ����ȥ
bool CHashAlgo::SetHashTable( char *lpszString )
{
    const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
    unsigned long nHash = HashString(lpszString, HASH_OFFSET);
    unsigned long nHashA = HashString(lpszString, HASH_A);
    unsigned long nHashB = HashString(lpszString, HASH_B);
    unsigned long nHashStart = nHash % m_tablelength,
        nHashPos = nHashStart;

    while ( m_HashIndexTable[nHashPos].bExists)
    { 
        nHashPos = (nHashPos + 1) % m_tablelength;
        if (nHashPos == nHashStart) 
        {

#if DEBUGTEST
            testid = -1;
#endif

            return false; 
        }
    }
    m_HashIndexTable[nHashPos].bExists = true;
    m_HashIndexTable[nHashPos].nHashA = nHashA;
    m_HashIndexTable[nHashPos].nHashB = nHashB;
    strcpy( m_HashIndexTable[nHashPos].test_filename, lpszString );

#if DEBUGTEST
    testid = nHashPos;
#endif

    return true;
}

//////////////////////////////////////////////////////////////////////////
// ȡ�ù�ϣ������
unsigned long CHashAlgo::GetTableLength(void)
{
    return m_tablelength;
}

//////////////////////////////////////////////////////////////////////////
// ���ù�ϣ������
void CHashAlgo::SetTableLength( const unsigned long nLength )
{
    m_tablelength = nLength;
    return;
}


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
    cout << "���Ҳ����ַ�����/"test/" ��ɢ��λ�ã�" << pos << endl;
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
    system( "pause" );
    //////////////////////////////////////////////////////////////////////////
    // ���Ҳ���
    for ( int i = 0; i < TESTNUM; i++ )
    {
        char buff[32];
        sprintf(buff, "abcdefg%d.", i);
        pos = hash_test.GetHashTablePos( buff );
        pos != -1 ?  cout << "���Ҳ����ַ�����"<< buff <<" ��ɢ��λ�ã�" << pos << endl : cout << buff << "���ڳ�ͻ��" << endl;   
    }

    system( "pause" );
    return 0;
}

