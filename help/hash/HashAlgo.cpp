/////////////////////////////////////////////////////////////////////////////
// Name:        HashAlgo.cpp
// Purpose:     使用魔兽Hash算法，实现索引表的填充和查找功能。
// Author:      陈相礼
// Modified by:
// Created:     07/30/09
// RCS-ID:      $Id: treetest.h 43021 2009-07-30 16:36:51Z VZ $
// Copyright:   (C) Copyright 2009, TSong Corporation, All Rights Reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#include "windows.h"
#include "HashAlgo.h"

//////////////////////////////////////////////////////////////////////////
// 预处理
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
// 求取哈希值
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
// 得到在定长表中的位置
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

    return -1; //没有找到
}
//////////////////////////////////////////////////////////////////////////
// 通过传入字符串，将相应的表项散列到索引表相应位置中去
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
// 取得哈希索引表长
unsigned long CHashAlgo::GetTableLength(void)
{
    return m_tablelength;
}

//////////////////////////////////////////////////////////////////////////
// 设置哈希索引表长
void CHashAlgo::SetTableLength( const unsigned long nLength )
{
    m_tablelength = nLength;
    return;
}


/////////////////////////////////////////////////////////////////////////////
// Name:        DebugMain.cpp
// Purpose:     测试Hash算法封装的类，完成索引表的填充和查找功能的测试。
// Author:      陈相礼
// Modified by:
// Created:     07/30/09
// RCS-ID:      $Id: treetest.h 43021 2009-07-30 16:36:51Z VZ $
// Copyright:   (C) Copyright 2009, TSong Corporation, All Rights Reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 测试参数设定宏
#define TESTNUM 32

#include <iostream>
#include <fstream>
#include "HashAlgo.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
// 测试主函数开始
int main( int argc, char **argv )
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
    cout << "查找测试字符串：/"test/" 的散列位置：" << pos << endl;
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
    system( "pause" );
    //////////////////////////////////////////////////////////////////////////
    // 查找测试
    for ( int i = 0; i < TESTNUM; i++ )
    {
        char buff[32];
        sprintf(buff, "abcdefg%d.", i);
        pos = hash_test.GetHashTablePos( buff );
        pos != -1 ?  cout << "查找测试字符串："<< buff <<" 的散列位置：" << pos << endl : cout << buff << "存在冲突！" << endl;   
    }

    system( "pause" );
    return 0;
}

