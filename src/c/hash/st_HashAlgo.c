#include "stlib.h"
#include "string.h"
#include "stdio.h"
#include "st_HashAlgo.h"

#define MAXFILENAME 255     // ����ļ�������
#define MAXTABLELEN 1024    // Ĭ�Ϲ�ϣ�������С

struct _MPQHASHTABLE_C
{    
	stbool nHashA;
	stbool nHashB;
	stbool bExists;
	char test_filename[MAXFILENAME];
};

long  testid;
unsigned long cryptTable[0x500];
unsigned long m_tablelength;    // ��ϣ��������
MPQHASHTABLE_C *m_HashIndexTable;


MPQHASHTABLE_C * MPQHConstruct(int size)
{
	int i ;

	prepareCryptTable_C();
	m_tablelength = size;
	m_HashIndexTable = (MPQHASHTABLE_C *)malloc(sizeof(MPQHASHTABLE_C)*size);

	for ( i = 0; i < size; i++ )
	{
		m_HashIndexTable[i].nHashA = -1;
		m_HashIndexTable[i].nHashB = -1;
		m_HashIndexTable[i].bExists = FALSE;
		m_HashIndexTable[i].test_filename[0] = '\0';
	}
}

void MPQHDestruct(void)
{
	if ( NULL != m_HashIndexTable )
	{
		free(m_HashIndexTable);
		m_HashIndexTable = NULL;
		m_tablelength = 0;	
	}
}

void prepareCryptTable_C()
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

// �õ��ڶ������е�λ��

long GetHashTablePos_C(char *lpszString)
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString_C(lpszString, HASH_OFFSET);
	unsigned long nHashA = HashString_C(lpszString, HASH_A);
	unsigned long nHashB = HashString_C(lpszString, HASH_B);
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

	return -1; //û���ҵ�

}



unsigned long HashString_C(const char *lpszFileName, unsigned long dwHashType )
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

// ͨ�������ַ���������Ӧ�ı���ɢ�е���������Ӧλ����ȥ

stbool SetHashTable_C( char *lpszString )
{
	const unsigned long HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
	unsigned long nHash = HashString_C(lpszString, HASH_OFFSET);
	unsigned long nHashA = HashString_C(lpszString, HASH_A);
	unsigned long nHashB = HashString_C(lpszString, HASH_B);
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
			return FALSE;
		}
	}

	m_HashIndexTable[nHashPos].bExists = TRUE;
	m_HashIndexTable[nHashPos].nHashA = nHashA;
	m_HashIndexTable[nHashPos].nHashB = nHash;
	strcpy( m_HashIndexTable[nHashPos].test_filename, lpszString );

#if DEBUGTEST
	testid = nHashPos;
#endif

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////

// ȡ�ù�ϣ������

unsigned long GetTableLength_C(void)
{
	return m_tablelength;
}

//////////////////////////////////////////////////////////////////////////

// ���ù�ϣ������

void SetTableLength_C( const unsigned long nLength )
{
	m_tablelength = nLength;
	return;
}











