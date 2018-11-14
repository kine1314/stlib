/*
 * st_hash_common.c
 *
 *  Created on: 2011-11-28
 *      Author: kine
 */
#include "st_hash_common.h"

/* 返回素数 */
int Get_Prime_Size (const int size)
{
	int temp = size ;

	while (!Is_A_Prime_Number (temp))
		temp++ ;

	return temp ;
}

int Is_A_Prime_Number (const int number)
{
	int count, value ;

	if (number < 2)
		puts ("Input wrong!") ;
	value = number / 2 + 1 ;
	for (count = 2; count < value; count++)
		if (0 == number % count)
			return 0 ;

	return 1 ;
}

int Square_ (const int i)
{
	return i * i ;
}

int STHash (const int item, const int size)
{
	return item % size ;
}

int STHash2 (const int item, const int prime)
{
	return prime - (item % prime) ;
}

/*	操作:	根据传递来的数据产生一个值并返回,直接使用字符串的andII码	*/
/*	操作前:	item , size 是用来计算产生数值的数据	*/
/*	操作后:	通过计算产生一个值并返回	*/
// 直接用字符串的ancii码作为键值
int STRHash(char *string)
{
    int s0;

	s0 = 0 ;
	printf("name [%s]\n", string);

	while(*string/* != '\0'*/)
	{
		s0=*(string)+s0;
		string++ ;
	}
	return s0 ;
}

// BKDR Hash Function
unsigned int BKDRHash(char *str)
{
	unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;
 
	while (*str)
	{
		hash = hash * seed + (*str++);
	}
 
	return (hash & 0x7FFFFFFF);
}

unsigned int SDBMHash(char *str)
{
	unsigned int hash = 0;
 
	while (*str)
	{
		// equivalent to: hash = 65599*hash + (*str++);
		hash = (*str++) + (hash << 6) + (hash << 16) - hash;
	}
 
	return (hash & 0x7FFFFFFF);
}

// RS Hash Function
unsigned int RSHash(char *str)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
 
	while (*str)
	{
		hash = hash * a + (*str++);
		a *= b;
	}
 
	return (hash & 0x7FFFFFFF);
}

// JS Hash Function
unsigned int JSHash(char *str)
{
	unsigned int hash = 1315423911;
 
	while (*str)
	{
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}
 
	return (hash & 0x7FFFFFFF);
}

// P. J. Weinberger Hash Function
unsigned int PJWHash(char *str)
{
	unsigned int BitsInUnignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	unsigned int ThreeQuarters	= (unsigned int)((BitsInUnignedInt  * 3) / 4);
	unsigned int OneEighth		= (unsigned int)(BitsInUnignedInt / 8);
	unsigned int HighBits		 = (unsigned int)(0xFFFFFFFF) << (BitsInUnignedInt - OneEighth);
	unsigned int hash			 = 0;
	unsigned int test			 = 0;
 
	while (*str)
	{
		hash = (hash << OneEighth) + (*str++);
		if ((test = hash & HighBits) != 0)
		{
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}
 
	return (hash & 0x7FFFFFFF);
}

// ELF Hash Function
unsigned int ELFHash(char *str)
{
	unsigned int hash = 0;
	unsigned int x	= 0;
 
	while (*str)
	{
		hash = (hash << 4) + (*str++);
		if ((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
			hash &= ~x;
		}
	}
 
	return (hash & 0x7FFFFFFF);
}

// DJB Hash Function
unsigned int DJBHash(char *str)
{
	unsigned int hash = 5381;
 
	while (*str)
	{
		hash += (hash << 5) + (*str++);
	}
 
	return (hash & 0x7FFFFFFF);
}

// AP Hash Function
unsigned int APHash(char *str)
{
	unsigned int hash = 0;
	int i;
 
	for (i=0; *str; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}
 
	return (hash & 0x7FFFFFFF);
}


unsigned long OPENSSLHash(char *str)
{
    int i,l;
    unsigned long ret=0;
    unsigned short *s;

    if (str == NULL)
        return(0);
	
    l=(strlen(str)+1)/2;
    s=(unsigned short *)str;
    for (i=0; i<l; i++)
        ret^=(s[i]<<(i&0x0f));
	
    return(ret);
} 

/*
unsigned long cryptTable[0x1000];
unsigned long SNHash(const char *lpszFileName, unsigned long dwHashType )
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
*/



