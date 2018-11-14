#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "st_binheap.h"
#include "st_log.h"
#include "st_head_common.h"


#define MinPQSize (10)				// 最小队列值
#define MinData (-32767)

struct STBinHeap_s
{
	int Capacity;				// 总容量
	int Size;					// 当前的大小
	BinHeadET *Elements;		// 保存对节点的数组
};

static stbool BHpercolateUp_P (BHPriorityQueue const H, const int position, const int size);
static stbool BHpercolateDown_P (BHPriorityQueue const H, const int position, const int size);


BHPriorityQueue BHInitialize( int MaxElements )
{
	BHPriorityQueue H;

	if( MaxElements < MinPQSize )
		__err( "Priority queue size is too small" );

	H = (struct STBinHeap_s *)malloc( sizeof( struct STBinHeap_s ) );
	if( H ==NULL )
		__err( "Out of space!!!" );

	/* Allocate the array plus one extra for sentinel */
	H->Elements = ( BinHeadET * )malloc( ( MaxElements + 1 ) * sizeof( BinHeadET ) );
	if( H->Elements == NULL )
		__err( "Out of space!!!" );

	H->Capacity = MaxElements;		// 初始化二叉堆的容量
	H->Size = 0;					// 当前堆得小是0
	H->Elements[ 0 ] = MinData;

	return H;
}

void BHDestroy( BHPriorityQueue H )
{
	free( H->Elements );
	free( H );
}

void BHMakeEmpty( BHPriorityQueue H )
{
	H->Size = 0;
}


// percolate up
stbool BHInsert( BinHeadET X, BHPriorityQueue H )
{
	int i;

	if( BHIsFull( H ) )
	{
		__err( "Priority queue is full" );
		return FALSE;
	}
	
	H->Elements[++H->Size] = X ;
	BHpercolateUp_P(H, H->Size, H->Size);
	
	return TRUE ;
}

stbool BHIsFull( BHPriorityQueue H )
{
	return H->Size == H->Capacity;
}

// percolate down
BinHeadET BHDeleteMin( BHPriorityQueue H )
{
	int i, Child;
	BinHeadET MinElement, LastElement;

	if( BHIsEmpty( H ) )
	{
		__err( "Priority queue is empty" );
		return H->Elements[ 0 ];
	}
	MinElement = H->Elements[ 1 ];					// 获取最小值，根节点

	H->Elements[ 1 ] = H->Elements[ H->Size-- ];	// 将堆的最后的一个值放到根节点，待以下滤
	BHpercolateDown_P(H, 1, H->Size);
	
	return MinElement;
}

stbool BHIsEmpty( BHPriorityQueue H )
{
	return H->Size == 0;
}

BinHeadET BHFindMin( BHPriorityQueue H )
{
	if( !BHIsEmpty( H ) )
	{
		return H->Elements[ 1 ];
	}
	
	__err( "Priority Queue is Empty" );
	return H->Elements[ 0 ];
}

stbool BHDisplayHead(BHPriorityQueue H)
{
	int i ;
	
	if( BHIsEmpty( H ) )
	{
		__err("the  head is empty !\n");
		return FALSE;
	}
		
	for( i = 1 ; i < H->Size ; i++)
		__inf("index [%d]\tdata [%d] \n", i, H->Elements[i]);

	return TRUE;
}

// 插入是对优先队列的上滤操作
static stbool BHpercolateUp_P (BHPriorityQueue const H, const int position, const int size)
{
	BinHeadET *temp ;
	int i ;
	
	if (position < 1 || position > size)		// 判断位置是否合法
		return FALSE ;
	
	temp = H->Elements[position] ;				// 将要插入的值
	// 寻找合适的位置
	for ( i = position; PARENT(i) >= 1 && H->Elements[PARENT(i)] > temp ; i = PARENT(i) )
		H->Elements[ i ] = H->Elements[ PARENT(i) ] ;
	
	H->Elements[ i ] = temp;
	printf("index [%d]\n", i);
}


// 在delete min 操作中的下滤操作
static stbool BHpercolateDown_P (BHPriorityQueue const H, const int position, const int size)
{
	BinHeadET *temp ;
	int i, Child ;

	if (position < 1 || position > size)
		return FALSE ;

	temp = H->Elements[1] ;									// 获取临时的根节点

	// 对数组往前移动, i代表空穴位置
	for( i = position; LEFT(i) <= H->Size; i = Child )		// 当LEFT(i) 大于size或者LastElement小于
	{
		/* Find smaller child */
		Child = LEFT(i);
		if( Child != H->Size && H->Elements[ RIGHT(i) ] < H->Elements[ LEFT(i) ] )	// 右孩子大于左孩子的情况
			Child++;		// smaller child

		/* Percolate one level "percolate down下滤"*/
		if( temp > H->Elements[ Child ] )
			H->Elements[ i ] = H->Elements[ Child ];		// smaller child 和空穴节点互换
		else
			break;
	}
	H->Elements[ i ] = temp;
	//printf("index [%d]\n", i);
	
	return TRUE ;
}

/*	操作:	增加优先队列中指定位置的结点的数据指定值	*/
/*	操作前:	ppq 指向一个已初始化的优先队列, position 指定位置, delta 是改变量	*/
/*	操作前:	如果 position 为有效位置 && delta > 0, 将优先队列中 position 位置的结点的数据增加 delta , 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool BHIncreaseKey_P (const BHPriorityQueue const ppq, const int position, const int delta) 
{
	if (position < 1 || position > ppq->Size || delta <= 0)
		return FALSE ;

	ppq->Elements[position] += delta ;							// 增加优先级后要下滤
	BHpercolateDown_P (ppq, position, ppq->Size) ;
	
}

/*	操作:	减少优先队列中指定位置结点的数据指定值	*/
/*	操作前:	ppq 指向一个已初始化的优先队列, position 指定位置, delta 是改变量	*/
/*	操作后:	如果 position 是有效位置 && delta > 0, 将优先队列中 position 位置的结点的数据减少 delta , 返回 TRUE ; 否则返回 FALSE	*/
/*	时间复杂度:	O (log N)	*/
stbool DecreaseKey_P (const BHPriorityQueue const ppq, const int position, const int delta) 
{
	if (position < 1 || position > ppq->Size || delta <= 0)
		return FALSE ;

	ppq->Elements[position] -= delta ;							// 减少优先级后要上滤
	BHpercolateUp_P (ppq, position, ppq->Size) ;
}


