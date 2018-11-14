#ifndef	__ST_HASHALGO_H__
#define	__ST_HASHALGO_H__


#define DEBUGTEST 1

typedef struct _MPQHASHTABLE_C	MPQHASHTABLE_C ;




MPQHASHTABLE_C * MPQHConstruct(int size);
void MPQHDestruct(void);
void prepareCryptTable_C();                                               // �Թ�ϣ������Ԥ����
unsigned long HashString_C(const char *lpszFileName, unsigned long dwHashType ); // ��ȡ��ϣֵ
long GetHashTablePos_C( char *lpszString );                               // �õ��ڶ������е�λ��
stbool SetHashTable_C( char *lpszString );                                  // ���ַ���ɢ�е���ϣ����
unsigned long GetTableLength_C(void);
void SetTableLength_C( const unsigned long nLength );





#endif	/* __ST_HASHALGO_H__ */

