/*	PriorityQueue.h -- ��С��ͷ�ļ�	*/
#include "Head.h"

/*	�ӿں�������	*/

/*	����:	��������ʼ��һ�����ȶ���	*/
/*	����ǰ:	ppq ָ��һ�����ȶ���, size ��ָ�������ȶ��д�С�ı���	*/
/*	������:	��� size > 0 && �ڴ����ɹ�, ��������ʼ�������ȶ���, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
BOOL Initialize_P (PriorityQueue * const ppq, const int size) ;

/*	����:	ȷ��һ�����ȶ����Ƿ�Ϊ��	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���	*/
/*	������:	��������ȶ���Ϊ��, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
BOOL IsEmpty_P (const PriorityQueue * const ppq) ;

/*	����:	ȷ��һ�����ȶ����Ƿ�����	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���	*/
/*	������:	��������ȶ�������, ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (1)	*/
BOOL IsFull_P (const PriorityQueue * const ppq) ;

/*	����:	��һ�����ȶ����в���һ�����	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���, pn �Ǵ���ӵ������еĽ��	*/
/*	������:	��������ȶ���δ��, ������ȶ�������� pn , ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
BOOL Insert_P (const PriorityQueue * const ppq, const PriorityNode pn) ;

/*	����:	ɾ�����������ȶ�������������С�Ľ��	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���	*/
/*	������:	��������ȶ��в�Ϊ��, ɾ����������������С�Ľ��; ���򷵻� NULL	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
PriorityNode DeleteMin_P (const PriorityQueue * const ppq) ;

/*	����:	�������ȶ�����ָ��λ�õĽ�������ָ��ֵ	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���, position ָ��λ��, delta �Ǹı���	*/
/*	����ǰ:	��� position Ϊ��Чλ�� && delta > 0, �����ȶ����� position λ�õĽ����������� delta , ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
BOOL IncreaseKey_P (const PriorityQueue * const ppq, const int position, const Item delta) ;

/*	����:	�������ȶ�����ָ��λ�ý�������ָ��ֵ	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���, position ָ��λ��, delta �Ǹı���	*/
/*	������:	��� position ����Чλ�� && delta > 0, �����ȶ����� position λ�õĽ������ݼ��� delta , ���� TRUE ; ���򷵻� FALSE	*/
/*	ʱ�临�Ӷ�:	O (log N)	*/
BOOL DecreaseKey_P (const PriorityQueue * const ppq, const int position, const Item delta) ;

/*	����:	�ͷ�һ�����ȶ���ռ�õ��ڴ�ռ�	*/
/*	����ǰ:	ppq ָ��һ���ѳ�ʼ�������ȶ���	*/
/*	������:	�����ȶ���ռ�õ��ڴ�ռ䱻�ͷ�	*/
/*	ʱ�临�Ӷ�:	O (N)	*/
void Release_P (const PriorityQueue * const ppq) ;