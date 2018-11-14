
typedef int ElementType;

/* START: fig6_4.txt */
#ifndef _BinHeap_H
#define _BinHeap_H

/* 二叉堆是棵完全二叉树，基于这种规律，所以使用数组比描述，
 * 对于数组上任意位置i上的元素，其左儿子在位置2i上，右儿子
 * 在2i+1上，他得父亲则在[i/2]上。缺点就是堆得大小要事先定义；
 */


struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize( int MaxElements );
void Destroy( PriorityQueue H );
void MakeEmpty( PriorityQueue H );
void Insert( ElementType X, PriorityQueue H );
ElementType DeleteMin( PriorityQueue H );
ElementType FindMin( PriorityQueue H );
int IsEmpty( PriorityQueue H );
int IsFull( PriorityQueue H );

#endif

/* END */
