#ifndef	__ST_HASHALGO_H__
#define	__ST_HASHALGO_H__


#define DEBUGTEST 1

typedef struct _MPQHASHTABLE_C	MPQHASHTABLE_C ;




MPQHASHTABLE_C * MPQHConstruct(int size);
void MPQHDestruct(void);
void prepareCryptTable_C();                                               // 对哈希索引表预处理
unsigned long HashString_C(const char *lpszFileName, unsigned long dwHashType ); // 求取哈希值
long GetHashTablePos_C( char *lpszString );                               // 得到在定长表中的位置
stbool SetHashTable_C( char *lpszString );                                  // 将字符串散列到哈希表中
unsigned long GetTableLength_C(void);
void SetTableLength_C( const unsigned long nLength );





#endif	/* __ST_HASHALGO_H__ */

