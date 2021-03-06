#include <stdlib.h>
#include <stdio.h>
#include "st_hash.h"




// 开放定址哈希表的存储结构
static stint hashsize[]={11,19,29,37}; // 哈希表容量递增表，一个合适的素数序列
static stint m=0; // 哈希表表长，全局变量


// 构造一个空的哈希表
stint InitHashTable(HashTable *H)
{
    int i;
    (*H).count=0; 						// 当前元素个数为0
    (*H).sizeindex=0; 					// 初始存储容量为hashsize[0]
    m=hashsize[0];
    (*H).elem=(HashElemType*)malloc(m*sizeof(HashElemType));
    if(!(*H).elem)
        exit(0); 						// 存储分配失败
    for(i=0;i<m;i++)
        (*H).elem[i].key=NULLKEY; 		// 未填记录的标志

    return 1;
}

//  销毁哈希表H
void DestroyHashTable(HashTable *H)
{
    free((*H).elem);
    (*H).elem=NULL;
    (*H).count=0;
    (*H).sizeindex=0;
}

// 一个简单的哈希函数(m为表长，全局变量)
static unsigned int Hash(HashKeyType K)
{
    return K%m;
}

// 开放定址法处理冲突
// Hi = ( H(key) + di ) MOD m i=1, 2, …,s
void collision(int *p,int d) // 线性探测再散列
{
    *p=(*p+d)%m;
}

stint SearchHash(HashTable H,HashKeyType K,int *p,int *c)
{
    *p=Hash(K); 					// 求得哈希地址
    while((H.elem[*p].key!=NULLKEY) && (!(K == H.elem[*p].key)))
    {
        // 该位置中填有记录．并且关键字不相等
        (*c)++;
        if(*c<m)
            collision(p,*c); 		// 求得下一探查地址p
        else
            break;
    }
    //查找成功，p返回待查数据元素位置
    if (K == H.elem[*p].key)
    	return SUCCESS ;
    else
    {
        return UNSUCCESS ;				// 查找不成功(H.elem[p].key==NULLKEY)，p返回的是插入位置
    }
}

void RecreateHashTable(HashTable *H) // 重建哈希表
{
    stint i,count=(*H).count;
    HashElemType *p,*elem=(HashElemType*)malloc(count*sizeof(HashElemType));
    p=elem;
    printf("重建哈希表\n");
    for(i=0;i<m;i++) 						// 保存原有的数据到elem中
        if(((*H).elem+i)->key!=NULLKEY) 	// 该单元有数据
            *p++=*((*H).elem+i);
    (*H).count=0;
    (*H).sizeindex++; 						// 增大存储容量
    m=hashsize[(*H).sizeindex];
    p=(HashElemType*)realloc((*H).elem,m*sizeof(HashElemType));
    if(!p)
        exit(0); 							// 存储分配失败
    (*H).elem=p;
    for(i=0;i<m;i++)
        (*H).elem[i].key=NULLKEY; 			// 未填记录的标志(初始化)
    for(p=elem;p<elem+count;p++) 			// 将原有的数据按照新的表长插入到重建的哈希表中
        InsertHash(H,*p);
}

// 查找不成功时插入数据元素e到开放定址哈希表H中，并返回1；
// 若冲突次数过大，则重建哈希表。
stint InsertHash(HashTable *H,HashElemType e)
{
    stint c,p;
    c=0;

    if(SearchHash(*H,e.key,&p,&c))			// 表中已有与e有相同关键字的元素
    {
    	return DUPLICATE ;
    }
    else if(c<hashsize[(*H).sizeindex]/2)	// 冲突次数c未达到上限,(c的阀值可调)
    {
        // 插入e
        (*H).elem[p]=e;
        ++(*H).count;
        return 1;
    }
    else
    {
        RecreateHashTable(H); // 重建哈希表
    }

    return 0;
}

// 按哈希地址的顺序遍历哈希表
void TraverseHash(HashTable H,void(*Vi)(stint,HashElemType))
{
	stint i;
	printf("哈希地址0～%d\n",m-1);
	for(i=0;i<m;i++)
		if(H.elem[i].key!=NULLKEY) // 有数据
			Vi(i,H.elem[i]);
}

// 在开放定址哈希表H中查找关键码为K的元素,若查找成功,以p指示待查数据
// 元素在表中位置,并返回SUCCESS;否则,返回UNSUCCESS
stint Find(HashTable H,HashKeyType K,stint *p)
{
	stint c=0;
	*p=Hash(K); 					// 求得哈希地址
	while(H.elem[*p].key!=NULLKEY&&!(K == H.elem[*p].key))
	{ 								// 该位置中填有记录．并且关键字不相等
		c++;
		if(c<m)
			collision(p,c); 		// 求得下一探查地址p
		else
			return UNSUCCESS; 		// 查找不成功(H.elem[p].key==NULLKEY)
	}
	if (K == H.elem[*p].key)
		return SUCCESS; 			// 查找成功，p返回待查数据元素位置
	else
		return UNSUCCESS; 			// 查找不成功(H.elem[p].key==NULLKEY)
}



