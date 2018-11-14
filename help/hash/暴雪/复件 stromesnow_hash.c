#include <string.h>
#include <stdio.h>
#define nTableSize  409600

unsigned long cryptTable[0x1000];

typedef struct _MPQHASHTABLE
{    
	char bExists;
}MPQHASHTABLE;

MPQHASHTABLE    HashTable[nTableSize];
int                HashATable[nTableSize];
int                HashBTable[nTableSize];
char            data[nTableSize][11];


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


int SearchWithInsert(const char *lpszString, MPQHASHTABLE * lpTable, int bInsert, char* str)
{
    const int HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
    
    unsigned int nHash = HashString(lpszString, HASH_OFFSET);
    unsigned int nHashA = HashString(lpszString, HASH_A);
    unsigned int nHashB = HashString(lpszString, HASH_B);
    unsigned int nHashStart = nHash % nTableSize, nHashPos = nHashStart;
    
    while (lpTable[nHashPos].bExists)
    { 
       if (HashATable[nHashPos]  == nHashA && HashBTable[nHashPos] == nHashB) 
        break; 
       else 
        nHashPos = (nHashPos + 1) % nTableSize;
      
       if (nHashPos == nHashStart) 
        return -1; 
    }
    
    if (!lpTable[nHashPos].bExists && bInsert)
    {
        HashATable[nHashPos] = nHashA;
        HashBTable[nHashPos] = nHashB;
        lpTable[nHashPos].bExists = 1;
        strcpy(data[nHashPos], str);
    }
    return nHashPos;
    
}


int main()
{
    char eng[11], mouse[11];
    char line[32];
    int i;
    prepareCryptTable();
    while (1)
    {
        gets(line);
        if (line[0] == 0) 
			break;
        sscanf(line, "%s%s", eng, mouse);
		SearchWithInsert(mouse, HashTable, 1, eng);
    }
    while (scanf("%s", mouse) == 1)
    {
        int pos = SearchWithInsert(mouse, HashTable, 0, 0);
        if (HashTable[pos].bExists) 
			puts(data[pos]);
        else 
			puts("eh");
    }
}
