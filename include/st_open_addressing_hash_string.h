/*
 * st_open_addressing_hash_string.h
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */

#ifndef ST_OPEN_ADDRESSING_HASH_STRING_H_
#define ST_OPEN_ADDRESSING_HASH_STRING_H_
#include "stlib.h"
#include "st_hash_common.h"

ST_BEGIN_DECLS ;

#define HASH_LENGTH 100               			//��ϣ��ĳ���         
#define NAME_NO 	60                   		//�����ĸ���  

typedef struct _NAME    
{   
	char *py;    				//���ֵ�ƴ��
	char *data;	 				// ����
    int k;       				//ƴ������Ӧ������
    int si;     				//���ҳ���
    enum KindOfEntry info ;		// ���ݵ�״̬
}NAME, *NAMEP;
//   
typedef struct    //��ϣ��
{   
	char *py;   //���ֵ�ƴ��
	char *data;
    int k;      //ƴ������Ӧ������
    int si;     //���ҳ���
    int size ;
}HASH, *HASHP;


void   	Display(HASH *HL) ; 				// ��ʾ��ϣ��       
void  	FindList(HASH *HL, char *name); 	// ����   
void 	CreateHashList(NAME *NL, HASH *HL); // ������ϣ��   
void 	EraseHashList(HASH *HL);			// �����б������


typedef struct _StringHashT
{
	
	int size ;
	NAMEP sname ;
} * StringHashTP, StringHashT ;



/*	����:	��ʼ��һ���ַ���ɢ�б�	*/
/*	����ǰ:	size ��ָ���ַ���ɢ�б�Ĵ�С�ı���	*/
/*	������:	�ñ��������ұ��е����б�Ԫָ�뱻��ʼ��Ϊ��, ���ظñ�	*/
StringHashTP STRHInitializeTable (const int size) ;

/*	����:	����һ��ָ�����ָ���������ڽ���ָ��	*/
/*	����ǰ:	item �Ǳ����ҵ�����, h ��һ���ѳ�ʼ���ı�	*/
/*	������:	�������, ����ָ�����ָ���������ڽ���ָ��; ���򷵻�NULL	*/
NAMEP STRHFind (const STRItem item, const StringHashTP * h) ;

/*	����:	��һ������ָ�������Բ����½��ķ�ʽ���뵽����	*/
/*	����ǰ:	item �Ǵ����������, ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�������, �� item Ϊ���ݴ���һ����㱻���뵽����(�����ͻ, ������λ��), ����1; ���򷵻�0	*/
int STRHInsert (const STRItem item, StringHashTP * const ph) ;	

/*	����:	�ӱ���ɾ��һ�����	*/
/*	����ǰ:	item �Ǵ�ɾ����������, ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�������, item ���ڽ�㱻�ӱ���ɾ��, ����1; ���򷵻�0	*/
int STRHDelete (const STRItem item, StringHashTP * const ph) ;

/*	����:	�ӵ��������������һ�����������ڱ������д��ڵĽ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, pfun ָ��һ��û�з���ֵ, ����һ��ListNode *���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ������ӵ���������������õ����д��ڵĽ��һ��	*/
void STRHDisplay (const StringHashTP * const ph) ;

/*	����:	���һ����	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�ñ���ռ�õ�ȫ���ڴ�ռ䱻�ͷ�	*/
void STRHRelease (StringHashTP * ph) ;

ST_END_DECLS ;

#endif	/* ST_OPEN_ADDRESSING_HASH_STRING_H_ */

