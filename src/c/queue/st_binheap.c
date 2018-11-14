#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "st_binheap.h"
#include "st_log.h"
#include "st_head_common.h"


#define MinPQSize (10)				// ��С����ֵ
#define MinData (-32767)

struct STBinHeap_s
{
	int Capacity;				// ������
	int Size;					// ��ǰ�Ĵ�С
	BinHeadET *Elements;		// ����Խڵ������
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

	H->Capacity = MaxElements;		// ��ʼ������ѵ�����
	H->Size = 0;					// ��ǰ�ѵ�С��0
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
	MinElement = H->Elements[ 1 ];					// ��ȡ��Сֵ�����ڵ�

	H->Elements[ 1 ] = H->Elements[ H->Size-- ];	// ���ѵ�����һ��ֵ�ŵ����ڵ㣬��������
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

// �����Ƕ����ȶ��е����˲���
static stbool BHpercolateUp_P (BHPriorityQueue const H, const int position, const int size)
{
	BinHeadET *temp ;
	int i ;
	
	if (position < 1 || position > size)		// �ж�λ���Ƿ�Ϸ�
		return FALSE ;
	
	temp = H->Elements[position] ;				// ��Ҫ�����ֵ
	// Ѱ�Һ��ʵ�λ��
	for ( i = position; PARENT(i) >= 1 && H->Elements[PARENT(i)] > temp ; i = PARENT(i) )
		H->Elements[ i ] = H->Elements[ PARENT(i) ] ;
	
	H->Elements[ i ] = temp;
	printf("index [%d]\n", i);
}


// ��delete min �����е����˲���
static stbool BHpercolateDown_P (BHPriorityQueue const H, const int position, const int size)
{
	BinHeadET *temp ;
	int i, Child ;

	if (position < 1 || position > size)
		return FALSE ;

	temp = H->Elements[1] ;									// ��ȡ��ʱ�ĸ��ڵ�

	// ��������ǰ�ƶ�, i�����Ѩλ��
	for( i = position; LEFT(i) <= H->Size; i = Child )		// ��LEFT(i) ����size����LastElementС��
	{
		/* Find smaller child */
		Child = LEFT(i);
		if( Child != H->Size && H->Elements[ RIGHT(i) ] < H->Elements[ LEFT(i) ] )	// �Һ��Ӵ������ӵ����
			Child++;		// smaller child

		/* Percolate one level "percolate down����"*/
		if( temp > H->Elements[ Child ] )
			H->Elements[ i ] = H->Elements[ Child ];		// smaller child �Ϳ�Ѩ�ڵ㻥��
		else
			break;
	}
	H->Elements[ i ] = temp;
	//printf("index [%d]\n", i);
	
	return TRUE ;
}

/*	����:	�������ȶ�����ָ��λ�õĽ�������ָ��ֵ	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���, position ָ��λ��, delta �Ǹı���	*/
/*	����ǰ:	��� position Ϊ��Чλ�� && delta > 0, �����ȶ����� position λ�õĽ����������� delta , ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool BHIncreaseKey_P (const BHPriorityQueue const ppq, const int position, const int delta) 
{
	if (position < 1 || position > ppq->Size || delta <= 0)
		return FALSE ;

	ppq->Elements[position] += delta ;							// �������ȼ���Ҫ����
	BHpercolateDown_P (ppq, position, ppq->Size) ;
	
}

/*	����:	�������ȶ�����ָ��λ�ý�������ָ��ֵ	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���, position ָ��λ��, delta �Ǹı���	*/
/*	������:	��� position ����Чλ�� && delta > 0, �����ȶ����� position λ�õĽ������ݼ��� delta , ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool DecreaseKey_P (const BHPriorityQueue const ppq, const int position, const int delta) 
{
	if (position < 1 || position > ppq->Size || delta <= 0)
		return FALSE ;

	ppq->Elements[position] -= delta ;							// �������ȼ���Ҫ����
	BHpercolateUp_P (ppq, position, ppq->Size) ;
}


