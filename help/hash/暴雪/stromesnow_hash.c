#include <string.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////

// 测试宏定义，正式使用时关闭

#ifndef bool
#define bool	int
#endif

#ifndef false
#define false	0
#endif

#ifndef	true
#define	true	1
#endif

#define DEBUGTEST 1
#define nTableSize  255
#define MAXFILENAME 255     // 最大文件名长度

#define MAXTABLELEN 1024    // 默认哈希索引表大小
#define TESTNUM 32

typedef struct _MPQHASHTABLE
{    
	long nHashA;
	long nHashB;
	bool bExists;
	char test_filename[MAXFILENAME];
}MPQHASHTABLE;

long  testid;
unsigned long cryptTable[0x500];
unsigned long m_tablelength;    // 哈希索引表长度
MPQHASHTABLE *m_HashIndexTable;


MPQHASHTABLE * create(int size);
void destory(void);
void prepareCryptTable();                                               // 对哈希索引表预处理
unsigned long HashString(const char *lpszFileName, unsigned long dwHashType ); // 求取哈希值
long GetHashTablePos( char *lpszString );                               // 得到在定长表中的位置
bool SetHashTable( char *lpszString );                                  // 将字符串散列到哈希表中
unsigned long GetTableLength(void);
void SetTableLength( const unsigned long nLength );


MPQHASHTABLE * create(int size)
{
	int i ;

	prepareCryptTable();
	m_tablelength = size;
	m_HashIndexTable = (MPQHASHTABLE *)malloc(sizeof(MPQHASHTABLE)*size);

	for ( i = 0; i < size; i++ )
	{
		m_HashIndexTable[i].nHashA = -1;
		m_HashIndexTable[i].nHashB = -1;
		m_HashIndexTable[i].bExists = false;
		m_HashIndexTable[i].test_filename[0] = '\0';
	}
}

void destory(void)
{
	if ( NULL != m_HashIndexTable )
	{
		free(m_HashIndexTable);
		m_HashIndexTable = NULL;
		m_tablelength = 0;	
	}
}

void prepareCryptTable()
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

// 得到在定长表中的位置

long GetHashTablePos(char *lpszString)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString(lpszString, HASH_OFFSET);
	unsigned long nHashA = HashString(lpszString, HASH_A);
	unsigned long nHashB = HashString(lpszString, HASH_B);
	unsigned long nHashStart = nHash % m_tablelength,
	nHashPos = nHashStart;

	while ( m_HashIndexTable[nHashPos].bExists)
	{

		if (m_HashIndexTable[nHashPos].nHashA == nHashA && m_HashIndexTable[nHashPos].nHashB == nHash)
			return nHashPos;
		else
			nHashPos = (nHashPos + 1) % m_tablelength;

		if (nHashPos == nHashStart)
			break;

	}

	return -1; //没有找到

}



unsigned long HashString(const char *lpszFileName, unsigned long dwHashType )
{ 
    unsigned char *key  = (unsigned char *)lpszFileName;
    unsigned long seed1 = 0x7FED7FED;
    unsigned long seed2 = 0xEEEEEEEE;
    int ch;

    while( *key != 0 )
    { 
        ch = *key++;
        seed1 = cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3; 
    }
    return seed1; 
}

//////////////////////////////////////////////////////////////////////////

// 通过传入字符串，将相应的表项散列到索引表相应位置中去

bool SetHashTable( char *lpszString )
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
	m_HashIndexTable[nHashPos].nHashB = nHash;
	strcpy( m_HashIndexTable[nHashPos].test_filename, lpszString );

#if DEBUGTEST
	testid = nHashPos;
#endif

	return true;
}

//////////////////////////////////////////////////////////////////////////

// 取得哈希索引表长

unsigned long GetTableLength(void)
{
	return m_tablelength;
}

//////////////////////////////////////////////////////////////////////////

// 设置哈希索引表长

void SetTableLength( const unsigned long nLength )
{
	m_tablelength = nLength;
	return;
}

//////////////////////////////////////////////////////////////////////////

// 测试主函数开始

int main( int argc, char **argv )
{
	int i ;

	create(TESTNUM);
	printf("取得初始化散列索引表长为：%d\n", GetTableLength());
	bool is_success = SetHashTable( "test" );
	if ( is_success )
	{
		printf("散列结果一：成功！\n");
	}
	else
	{
		printf("散列结果一：失败！\n");
	}
	is_success = SetHashTable( "测试" );
	if ( is_success )
	{
		printf("散列结果二：成功！\n");
	}
	else
	{
		printf("散列结果二：失败！\n");
	}
	long pos = GetHashTablePos( "test" );
	printf("查找测试字符串：\"test\" 的散列位置：%d\n", pos);
	pos = GetHashTablePos( "测试" );
	printf("查找测试字符串：“测试” 的散列位置：%d\n", pos);

	//////////////////////////////////////////////////////////////////////////

	// 散列测试

	for ( i = 0; i < TESTNUM; i++ )
	{
		char buff[32];
		sprintf(buff, "abcdefg%d.", i);
		is_success = SetHashTable(buff);
		//is_success ? cout << buff << "散列结果：成功！位置：" << hash_test.testid << endl : cout << buff << "散列结果：失败！" << endl;

		if(is_success)
			printf("[%s]散列结果：成功！位置：[%d]\n",buff, testid);
		else
			printf("[%s]散列结果：失败！\n", buff);
	}

	//////////////////////////////////////////////////////////////////////////

	// 查找测试

	for ( i = 0; i < TESTNUM; i++ )
	{
		char buff[32];
		sprintf(buff, "abcdefg%d.", i);
		pos = GetHashTablePos( buff );
		//pos != -1 ?  cout << "查找测试字符串："<< buff <<" 的散列位置：" << pos << endl : cout << buff << "存在冲突！" << endl;
		if(pos != -1)
			printf("查找测试字符串：[%s] 的散列位置：[%d]\n", buff, pos);
		else
			printf("[%s]存在冲突！\n", buff);
	}
}
