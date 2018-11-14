/*
 * st_open_addressing_hash_string.c
 *
 *  Created on: 2011-11-29
 *      Author: kine
 */
#include 	<malloc.h>
#include 	"st_open_addressing_hash_string.h"
#include	<stdio.h>
#include	<stdlib.h>
#include 	"stlib.h"
#include 	"st_log.h"


#define M 			47                         	//�����
  


NAME NameList[HASH_LENGTH];    		//ȫ�ֱ���NAME    
HASH HashList[HASH_LENGTH];        	//ȫ�ֱ���HASH    





void CreateHashList(NAME *NL, HASH *HL) //������ϣ��   
{	
	int i;
	/*
	for(i=0; i<HASH_LENGTH;i++) 
	{   
		(HL+i)->py="";
		(HL+i)->k=0;
		(HL+i)->si=0;
	}
	*/
	memset(HL, 0, sizeof(HASH)*HASH_LENGTH);
	HL->size = HASH_LENGTH ;
	for(i=0;i< HASH_LENGTH;i++)
	{   
		
		int sum=0;
		int adr=((NL+i)->k)%HASH_LENGTH;  //��ϣ����
		int d=adr;
		if(((HL+adr)->si) == 0)     //�������ͻ
		{  
			(HL+adr)->k=(NL+i)->k;
			(HL+adr)->py=(NL+i)->py;
			(HL+adr)->data="a"+i;
			(HL+adr)->si=1;
		}
		else   //��ͻ  
		{ 
			do
			{   
				d=(d+((NL+i)->k)%10+1)%HASH_LENGTH;   //α���̽����ɢ�з������ͻ    
				sum=sum+1;                    //���Ҵ�����1    
			}while ((HL+d)->k!=0);
			(HL+d)->k=(NL+i)->k;
			(HL+d)->py=(NL+i)->py;
			(HL+adr)->data="a"+i;
			(HL+d)->si=sum+1;
		}
	}
}

void  FindList(HASH *HL, char *name) //����    
{	
	
	int s0=0,r,sum=1,adr,d;
	 
	for(r=0;(*(name+r) != '\0');r++)   //���������ƴ������Ӧ������(�ؼ���)
		s0+=name[r]; 
	
	adr=s0%HASH_LENGTH;   //ʹ�ù�ϣ����
	d=adr;
	printf("s0 [%d] ,adr [%d]\n", s0, adr);
	if((HL+adr)->k == s0)          //��3����������ж�
		printf("\n����:%s   data:%s		�ؼ���:%d   ���ҳ���Ϊ: 1",(HL+d)->py, (HL+d)->data,s0); 
	else if ((HL+adr)->k==0) 
		printf("�޴˼�¼!");
	else
	{   
		int g=0;
		do
		{   
			d=(d+s0%10+1)%HASH_LENGTH;       //α���̽����ɢ�з������ͻ                     
			sum=sum+1;
			if((HL+d)->k==0)
			{  
				printf("�޴˼�¼! ");  
				g=1;     
			}
			if((HL+d)->k==s0)
			{  
				printf("\n����:%s   data:%s		�ؼ���:%d   ���ҳ���Ϊ:%d",(HL+d)->py, (HL+d)->data,s0,sum); 
				g=1;  
			}
		}while(g==0);   
	}  
}

void   Display(HASH *HL) // ��ʾ��ϣ��       
{	
	int i;
	float average=0;
	printf("\n��ַ\t�ؼ���\t\t��������\tH(key)\t ����\n"); //��ʾ�ĸ�ʽ
	for(i=0; i<HASH_LENGTH; i++)
	{   
		printf("%d ",i); 
		printf("\t%d ",(HL+i)->k);
		printf("\t\t%d ",(HL+i)->si);
		printf("\t\t%d ",(HL+i)->k%HASH_LENGTH);
		printf("\t %s ",(HL+i)->py);
		printf("\t %s ",(HL+i)->data);
		printf("\n");
	}
	for(i=0;i<HASH_LENGTH;i++)
		average+=(HL+i)->si; 
	
	average/=NAME_NO;
	printf("\nƽ�����ҳ��ȣ�ASL(%d)=%f \n",NAME_NO,average); 
}

void EraseHashList(HASH *HL)
{
	if(NULL != HL)
		memset(HL, 0, sizeof(HASH)*HASH_LENGTH);
}




/*	����:	��ʼ��һ���ַ���ɢ�б�	*/
/*	����ǰ:	size ��ָ���ַ���ɢ�б�Ĵ�С�ı���	*/
/*	������:	�ñ��������ұ��е����б�Ԫָ�뱻��ʼ��Ϊ��, ���ظñ�	*/
StringHashTP STRHInitializeTable (const int size) 
{
	StringHashTP h = NULL ;
	int count ;

	h = (struct _StringHashT *)malloc(sizeof(struct _StringHashT));
	if(NULL == h)
	{
		__err("alooc mem for _StringHashT fail\n");
	}
	h->size = Get_Prime_Size (size) ;	
	h->sname = (struct _NAME *)malloc(sizeof(struct _NAME) * h->size);
	if(NULL == h->sname)
	{
		__err("alooc mem for _NAME fail\n");
	}
	
	for (count = 0; count < h->size; count++)
		((h->sname)+count)->info = Empty ;
	return h ;
}

/*	����:	����һ��ָ�����ָ���������ڽ���ָ��	*/
/*	����ǰ:	item �Ǳ����ҵ�����, h ��һ���ѳ�ʼ���ı�	*/
/*	������:	�������, ����ָ�����ָ���������ڽ���ָ��; ���򷵻�NULL	*/
NAMEP STRHFind (const STRItem item, const StringHashTP *ph) 
{
	int key, size, index, adr, d, critical, sum = 0, i = 0 ;

	size = (*ph)->size ;
	key = STRHash(item);			// ɢ�к���ַ����ؼ�ֵ
	adr = key % size ;			// ��������ڱ���index��������Ϊ��ͻ���������
	d = adr ;
	critical = size / 2 ;

	do
	{
#if 0
		d=(d+key%10+1)%size; 	
		sum=sum+1;

#elif 0	// ����̽�ⷢ�����ͻ��ȱ��Ƚϼ���
		d = (key%10 + (i++)) % size ;
		sum=sum+1;
		
#elif 0	// ƽ��̽�ⷨ�����ͻ
		if(i <= critical)
		{
			d = Square_ (i++) ;
			d = (key + Square_ (i++)) % size ;
			sum=sum+1;
		}
#elif 1	// ˫��ϣ
		if(i < size)
		{
			d = (key + ((i++)*STHash2(item, 27))) % size ;		// ˫ɢ��̽���ַ��
			sum=sum+1;
		}
		else
		{
			break ;
		}
#endif
		
	}while(item != ((*ph)->sname+d)->py && Legitimate == ((*ph)->sname+d)->info);
	((*ph)->sname+d)->k = key ;
	((*ph)->sname+d)->si = sum ;		// �������

	return (*ph)->sname+d ;
}

/*	����:	��һ������ָ�������Բ����½��ķ�ʽ���뵽����	*/
/*	����ǰ:	item �Ǵ����������, ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�������, �� item Ϊ���ݴ���һ����㱻���뵽����(�����ͻ, ������λ��), ����1; ���򷵻�0	*/
int STRHInsert (const STRItem item, StringHashTP * const ph) 
{
	NAMEP position ;	

	position = STRHFind(item, ph);

	/* �ɹ��ҵ�����λ�ã������и�ֵ */
	if(Empty == position->info || Deleted == position->info)
	{
		position->info = Legitimate ;
		position->py = item ;
		return SUCCESS ;
	}
	
	return UNSUCCESS ;
}

/*	����:	�ӱ���ɾ��һ�����	*/
/*	����ǰ:	item �Ǵ�ɾ����������, ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�������, item ���ڽ�㱻�ӱ���ɾ��, ����1; ���򷵻�0	*/
int STRHDelete (const STRItem item, StringHashTP * const ph) 
{
	NAMEP position ;	

	position = STRHFind(item, ph);
	if (Legitimate == position->info && item == position->py)
	{
		position->info = Deleted ;
		// �������գ������Ƕ�̬����ģ�����ʵ������ɾ��
		position->py = NULL ;
		position->k = 0 ;
		return SUCCESS ;
	}

	return UNSUCCESS ;
}

/*	����:	�ӵ��������������һ�����������ڱ������д��ڵĽ��	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�, pfun ָ��һ��û�з���ֵ, ����һ��ListNode *���Ͳ����ĺ���	*/
/*	������:	pfun ָ��ĺ������ӵ���������������õ����д��ڵĽ��һ��	*/
void STRHDisplay (const StringHashTP * const ph) 
{
	int i;
	float average=0;
	
	printf("\n��ַ\t�ؼ���\t\t��������\tH(key)\t ����\n"); //��ʾ�ĸ�ʽ
	for(i=0; i<HASH_LENGTH; i++)
	{   
		printf("%d ",i); 
		printf("\t%d ",((((*ph)->sname)+i)->k));
		printf("\t\t%d ",((((*ph)->sname)+i)->si));
		printf("\t\t%d ",((((*ph)->sname)+i)->k%(*ph)->size));
		printf("\t %s ",((((*ph)->sname)+i)->py));
		printf("\t %s ",((((*ph)->sname)+i)->data));
		printf("\n");
	}
}

/*	����:	���һ����	*/
/*	����ǰ:	ph ָ��һ���ѳ�ʼ���ı�	*/
/*	������:	�ñ���ռ�õ�ȫ���ڴ�ռ䱻�ͷ�	*/
void STRHRelease (StringHashTP * ph) 
{
	free ((*ph)->sname) ;
	free (*ph) ;
	__inf("RELEASE THE STRHTABLE\n");
}









