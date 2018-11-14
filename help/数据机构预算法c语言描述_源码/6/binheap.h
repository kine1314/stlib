
typedef int ElementType;

/* START: fig6_4.txt */
#ifndef _BinHeap_H
#define _BinHeap_H

/* ������ǿ���ȫ���������������ֹ��ɣ�����ʹ�������������
 * ��������������λ��i�ϵ�Ԫ�أ����������λ��2i�ϣ��Ҷ���
 * ��2i+1�ϣ����ø�������[i/2]�ϡ�ȱ����Ƕѵô�СҪ���ȶ��壻
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
