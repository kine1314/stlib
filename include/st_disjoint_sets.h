#ifndef	__ST_DISJOINT_SET_H__
#define	__ST_DISJOINT_SET_H__
#include "stlib.h"

ST_BEGIN_DECLS ;
#define NumSets 16

#define DJSOOS 				(-65536)
#define DJSSIZE 			(-1)
#define DJSHEIGHT 			(0)

/*
 * (union-find sets)��һ�ּ򵥵���;�㷺�ļ���. ���鼯�����ɸ����ཻ���ϣ�
 * �ܹ�ʵ�ֽϿ�ĺϲ����ж�Ԫ�����ڼ��ϵĲ�����Ӧ�úܶࡣһ���ȡ���νṹ���洢���鼯��
 * ������һ��rank�������洢���ϵ�����½磬�ڲ��Ҳ���ʱ����·��ѹ��ʹ�����Ĳ��Ҳ������١�
 * �����Ż�ʵ�ֵĲ��鼯���ռ临�Ӷ�ΪO(N)������һ�����ϵ�ʱ�临�Ӷ�ΪO(1)��N�κϲ�M����
 * ��ʱ�临�Ӷ�ΪO(M Alpha(N))������Alpha��Ackerman������ĳ�����������ںܴ�ķ�Χ��
 * ������Ŀǰ�۲⵽�����淶Χ������10��80�η���ԭ�ӣ���С��ǰ����˵�ķ�Χ�����������ֵ
 * ���Կ����ǲ�����4�ģ����Բ��鼯�Ĳ������Կ��������Եġ���֧���������ֲ���:
 *��  ��Union (Root1, Root2) //�����������Ӽ���Root2���뼯��Root1��.Ҫ��Root1�� Root2�����ཻ,����ִ�в���.
 *������Find (x) //��������������Ԫ��x���ڵļ���,�����ظü��ϵ�����.
 *������UFSets (s) //���캯���������鼯��s�����ϳ�ʼ��Ϊs��ֻ��һ����Ԫ�ص��Ӽ���.
 */

/*	�������Ͷ���	*/

typedef int 	DJSItem ;
typedef DJSItem DJSType   ;
//typedef DJSType DisjiontSet[ NumSets + 1 ] ;		// ������Ŵ洢ɭ�������ϣ�
typedef DJSType * DisjiontSet ;		// ������Ŵ洢ɭ�������ϣ�

/*	�ӿں�������	*/

/*	����:	���߶ȳ�ʼ��һ�����ཻ����	*/
/*	����ǰ:	gather ��һ�����ཻ����, size ��ָʾ���ཻ���ϵĴ�С	*/
/*	������:	������һ����������������Ϊ���ϵ�ʵ�ʴ�С��, �����м��������򱻳�ʼ��ΪHEIGHT	*/
void DJSInitializeAsHeight (DisjiontSet gather, const int size) ;

/*	����:	����С��ʼ��һ�����ཻ����	*/
/*	����ǰ:	gather ��һ�����ཻ����, size ָʾ���ཻ���ϵĴ�С	*/
/*	������:	������һ������������λ��Ϊ���ϵ�ʵ�ʴ�С��, ���м��������򱻳�ʼ��ΪSIZE	*/
void DJSInitializeAsSize (DisjiontSet gather, const int size) ;

/*	����:	�����ĸ߶�����������	*/
/*	����ǰ:	gather ��һ���ѳ�ʼ���Ĳ��ཻ����, root1, root2 �������������͵ı���	*/
/*	������:	������������� gather ��, ���߶��� root1 ���Ϻ� root2 ����, ����1; ���򷵻�0	*/
int DJSSetUnionAsHeight (DisjiontSet gather, DJSType root1, DJSType root2) ;

/*	����:	�����Ĵ�С����������	*/
/*	����ǰ:	gather ��һ���ѳ�ʼ���Ĳ��ཻ����, root1, root2 �������������͵ı���	*/
/*	������:	������������� gather ��, ����С�� root1 ���Ϻ� root2 ����, ����1; ���򷵻�0	*/
int DJSSetUnionAsSize (DisjiontSet gather, DJSType root1, DJSType root2) ;

/*	����:	����һ�����ཻ���Ϻ�һ������, ���Ҳ����ظ��������ڼ�������, ������·��ѹ��	*/
/*	����ǰ:	gather ��һ���ѳ�ʼ���Ĳ��ཻ����, item ��һ��Item���ͱ���	*/
/*	������:	��� item ���ڼ����� gather ��, �ҵ������� item ���ڼ��ϵ�����, ������·��ѹ��; ���򷵻� OOS	*/
DJSType DJSFind (DisjiontSet gather, const DJSItem item) ;



ST_END_DECLS ;
#endif	/* __ST_DISJOINT_SET_H__ */

