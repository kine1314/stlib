#ifndef	__ST_HASHALGO_CPP_H__
#define	__ST_HASHALGO_CPP_H__


/////////////////////////////////////////////////////////////////////////////

#define MAXFILENAME 	255     // ����ļ�������
#define MAXTABLELEN 	1024    // Ĭ�Ϲ�ϣ�������С

//////////////////////////////////////////////////////////////////////////
// ���Ժ궨�壬��ʽʹ��ʱ�ر�

#define DEBUGTEST 	1

//////////////////////////////////////////////////////////////////////////

// ��ϣ��������

typedef struct
{
	long nHashA;
	long nHashB;
	bool bExists;
	char test_filename[MAXFILENAME];
	// ......
} MPQHASHTABLE;

//////////////////////////////////////////////////////////////////////////

// �Թ�ϣ��������㷨���з�װ

class CHashAlgo
{

public:
#if DEBUGTEST
	long  testid;   // ����֮��
#endif
	// ����ָ����С�Ĺ�ϣ���������������Ĺ��캯������Ĭ�ϴ�С�Ĺ�ϣ������
	CHashAlgo( const long nTableLength = MAXTABLELEN )
	{
		prepareCryptTable();
		m_tablelength = nTableLength;
		m_HashIndexTable = new MPQHASHTABLE[nTableLength];
		//printf("size [%d]\n", m_tablelength);

		for ( int i = 0; i < nTableLength; i++ )
		{
			m_HashIndexTable[i].nHashA = -1;
			m_HashIndexTable[i].nHashB = -1;
			m_HashIndexTable[i].bExists = false;
			m_HashIndexTable[i].test_filename[0] = '\0';
		}
	}

	void prepareCryptTable();                                               // �Թ�ϣ������Ԥ����
	unsigned long HashString(char *lpszFileName, unsigned long dwHashType); // ��ȡ��ϣֵ
	long GetHashTablePos( char *lpszString );                               // �õ��ڶ������е�λ��
	bool SetHashTable( char *lpszString );                                  // ���ַ���ɢ�е���ϣ����
	unsigned long GetTableLength(void);
	void SetTableLength( const unsigned long nLength );

	~CHashAlgo()
	{
		if ( NULL != m_HashIndexTable )
		{
			delete []m_HashIndexTable;
			m_HashIndexTable = NULL;
			m_tablelength = 0;	
		}
	}

protected:

private:

	unsigned long cryptTable[0x500];
	unsigned long m_tablelength;    // ��ϣ��������
	MPQHASHTABLE *m_HashIndexTable;

};


#endif	/* __ST_HASHALGO_CPP_H__ */

