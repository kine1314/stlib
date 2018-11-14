/*
 * st_hash_common.h
 *
 *  Created on: 2011-11-28
 *      Author: kine
 */

#ifndef ST_HASH_COMMON_H_
#define ST_HASH_COMMON_H_
#include "stlib.h"

ST_BEGIN_DECLS ;




/*	�������Ͷ���	*/
typedef int HItem ;
typedef char*	STRItem ;

enum KindOfEntry
{
	Legitimate, 		// �Ϸ���
	Empty,
	Deleted
} ;

typedef struct cell
{
	HItem item ;
	enum KindOfEntry info ;
	int times ;
} Cell ;

typedef struct oa_hashtable
{
	int size ;
	int used ;					/*	ʹ����Ԫ�ص�����, �ظ���Ӳ����Ӵ�����	*/
	Cell * lists ;
} * OAHashTable ;

/*	����:	���ݴ����������ݲ���һ��ֵ������	*/
/*	����ǰ:	item , size ���������������ֵ������	*/
/*	������:	ͨ���������һ��ֵ������	*/
int STHash (const int item, const int size);

/*	����:	�������������������ݲ���һ�����ݲ�����	*/
/*	����ǰ: item �� prime �ǽ��ܵ�����	*/
/*	������:	����item �� prime ����һ�����ݲ�����	*/
int STHash2 (const int item, const int prime) ;				// ���ڿ�����ַ˫ɢ�з�����

/*	����:	���ݴ����������ݲ���һ��ֵ������,ֱ��ʹ���ַ�����andII��	*/
/*	����ǰ:	item , size ���������������ֵ������	*/
/*	������:	ͨ���������һ��ֵ������	*/
// ֱ�����ַ�����ancii����Ϊ��ֵ
int STRHash(char *string);

/*
����һλţ�˶���Щ�ַ���hash�����Ĳ�������
Hash����	����1	����2	����3	����4	����1�÷�	����2�÷�	����3�÷�	����4�÷�	ƽ����
BKDRHash	2		0		4774	481		96.55		100			90.95		82.05		92.64
APHash		2		3		4754	493		96.55		88.46		100			51.28		86.28
DJBHash		2		2		4975	474		96.55		92.31		0			100			83.43
JSHash		1		4		4761	506		100			84.62		96.83		17.95		81.94
RSHash		1		0		4861	505		100			100			51.58		20.51		75.96
SDBMHash	3		2		4849	504		93.1		92.31		57.01		23.08		72.41
PJWHash		30		26		4878	513		0			0			43.89		0			21.95
ELFHash		30		26		4878	513		0			0			43.89		0			21.95
*/
// BKDR Hash Function
unsigned int BKDRHash(char *str);

unsigned int SDBMHash(char *str);

// RS Hash Function
unsigned int RSHash(char *str);

// JS Hash Function
unsigned int JSHash(char *str);

// P. J. Weinberger Hash Function
unsigned int PJWHash(char *str);

// ELF Hash Function
unsigned int ELFHash(char *str);

// DJB Hash Function
unsigned int DJBHash(char *str);

// AP Hash Function
unsigned int APHash(char *str);

// OpenSSL�г��ֵ��ַ���Hash����
unsigned long OPENSSLHash(char *str);

// ���Ա�ѩ�ĸ�Чhash�㷨
//unsigned long SNHash(const char *lpszFileName, unsigned long dwHashType );


int Get_Prime_Size (const int size) ;
int Is_A_Prime_Number (const int number) ;
int Square_ (const int i);


ST_END_DECLS ;
#endif /* ST_HASH_COMMON_H_ */
