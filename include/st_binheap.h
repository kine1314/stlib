#ifndef	__ST_BINHEAP_H__
#define	__ST_BINHEAP_H__

#include "stlib.h"
#include "st_type.h"

ST_BEGIN_DECLS;

/* ������ǿ���ȫ���������������ֹ��ɣ�����ʹ�������������
 * ��������������λ��i�ϵ�Ԫ�أ����������λ��2i�ϣ��Ҷ���
 * ��2i+1�ϣ����ø�������[i/2]�ϡ�ȱ����Ƕѵô�СҪ���ȶ��壻
 * ��С�����Ǵ��ϵ���������������ڵ㶼ӦС�������Һ��᣻
 */


struct STBinHeap_s;
typedef struct STBinHeap_s *BHPriorityQueue;

/*	����:	��ʼ��һ�������	*/
/*	����ǰ:	size ��ָ������ѵĴ�С�ı���	*/
/*	������:	�ñ��������ұ��е����б�Ԫָ�뱻��ʼ��Ϊ��, ���ظñ�	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
BHPriorityQueue BHInitialize( int MaxElements );

/*	����:	���ٶ����	*/
/*	����ǰ:	H ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�ñ���ռ�õ�ȫ���ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
void BHDestroy( BHPriorityQueue H );

/*	����:	��ն����	*/
/*	����ǰ:	H ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	���sizeΪ0	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
void BHMakeEmpty( BHPriorityQueue H );

/*	����:	��һ�����ȶ����в���һ�����	*/
/*	����ǰ:	H ָ��һ���ѳ�ʼ�������ȶ���, pn �Ǵ���ӵ������еĽ��	*/
/*	������:	��������ȶ���δ��, ������ȶ�������� X , ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)�����ֲ���	*/
stbool BHInsert( BinHeadET X, BHPriorityQueue H );

/*	����:	�ж϶�����Ƿ�Ϊ��	*/
/*	����ǰ:	H ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�����Ƿ���	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool BHIsFull( BHPriorityQueue H );

/*	����:	ɾ�����������ȶ�������������С�Ľ��	*/
/*	����ǰ:	H ָ��һ���ѳ�ʼ�������ȶ���	*/
/*	������:	��������ȶ��в�Ϊ��, ɾ����������������С�Ľ��; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N),���ֲ���	*/
BinHeadET BHDeleteMin( BHPriorityQueue H );

/*	����:	��ȡ���ȶ����е���Сֵ	*/
/*	����ǰ:	H ָ��һ���ѳ�ʼ�������ȶ���	*/
/*	������:	��������ȶ��в�Ϊ��, ���ض��еĵ�һ���ڵ�	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
BinHeadET BHFindMin( BHPriorityQueue H );

/*	����:	ȷ��һ�����ȶ����Ƿ�Ϊ��	*/
/*	����ǰ:	H ָ��һ���ѳ�ʼ�������ȶ���	*/
/*	������:	��������ȶ���Ϊ��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool BHIsEmpty( BHPriorityQueue H );

/*	����:	ȷ��һ�����ȶ����Ƿ�����	*/
/*	����ǰ:	H ָ��һ���ѳ�ʼ�������ȶ���	*/
/*	������:	��������ȶ�������, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
stbool BHIsFull( BHPriorityQueue H );

/*	����:	�������ȶ�����ָ��λ�õĽ�������ָ��ֵ	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���, position ָ��λ��, delta �Ǹı���	*/
/*	����ǰ:	��� position Ϊ��Чλ�� && delta > 0, �����ȶ����� position λ�õĽ����������� delta , ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool BHIncreaseKey_P (const BHPriorityQueue const ppq, const int position, const int delta) ;

/*	����:	�������ȶ�����ָ��λ�ý�������ָ��ֵ	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���, position ָ��λ��, delta �Ǹı���	*/
/*	������:	��� position ����Чλ�� && delta > 0, �����ȶ����� position λ�õĽ������ݼ��� delta , ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
stbool DecreaseKey_P (const BHPriorityQueue const ppq, const int position, const int delta) ;

stbool BHDisplayHead(BHPriorityQueue H);

ST_END_DECLS ;
#endif	/* __ST_BINHEAP_H__ */

