#include<stdio.h>
#include<conio.h>
#define HASH_LEN 50                      //��ϣ��ĳ��� 
#define M 47                            //�����
#define NAME_NO 15                      //�����ĸ���        

typedef struct      
{
	char *py;    //���ֵ�ƴ��
	int k;       //ƴ������Ӧ������
}NAME;

NAME NameList[HASH_LEN];    //ȫ�ֱ���NAME             
typedef struct    //��ϣ��
{
	char *py;   //���ֵ�ƴ��
	int k;      //ƴ������Ӧ������
	int si;     //���ҳ���
}HASH;
HASH HashList[HASH_LEN];        //ȫ�ֱ���HASH                     

void InitNameList() //�������ṹ�����飩��ʼ��          
{
	char *f;
	int r,s0,i;
	NameList[0].py="liangxin";
	NameList[1].py="huayongpan";
	NameList[2].py="liufeng";
	NameList[3].py="dingxiao";
	NameList[4].py="gaoyunchuan";
	NameList[5].py="liqingbo";	
	NameList[6].py="liujunpeng";
	NameList[7].py="jiangquanlei";
	NameList[8].py="xingzhengchuan";
	NameList[9].py="luzhaoqian";
	NameList[10].py="gaowenhu";
	NameList[11].py="zhuhaoyin";
	NameList[12].py="chenli";
	NameList[13].py="wuyunyun";
	NameList[14].py="huangjuanxia";
	NameList[15].py="wangying";
	for (i=0;i<NAME_NO;i++)
	{
		s0=0;
		f=NameList[i].py;
		for (r=0;*(f+r)!='\0';r++)
		{
			/* ���������ַ����ĸ����ַ�����Ӧ��ASCII����ӣ����õ�������Ϊ��ϣ��Ĺؼ���*/
			s0=*(f+r)+s0;
			NameList[i].k=s0;
		}
	}
}

void CreateHashList() //������ϣ��   
{
	int i;
	for (i=0; i<HASH_LEN;i++) 
	{
		HashList[i].py="";
		HashList[i].k=0;
		HashList[i].si=0;
	}
	for (i=0;i<HASH_LEN;i++)
	{
		int sum=0;
		int adr=(NameList[i].k)%M;  //��ϣ����
		int d=adr;
		if(HashList[adr].si==0)     //�������ͻ
		{
			HashList[adr].k=NameList[i].k;
			HashList[adr].py=NameList[i].py;
			HashList[adr].si=1;
		}
		else   //��ͻ  
		{
			do
			{
				d=(d+NameList[i].k%10+1)%M;   //α���̽����ɢ�з������ͻ    
				sum=sum+1;   //���Ҵ�����1    
			}while (HashList[d].k!=0);

			HashList[d].k=NameList[i].k;
			HashList[d].py=NameList[i].py;
			HashList[d].si=sum+1;
		}
	}
}
void   FindList() //����    
{  
	char name[20]={0}; 
	int s0=0,r,sum=1,adr,d;
	printf("\n������������ƴ��:");     
	scanf("%s",name); 
	for (r=0;r<20;r++)   //���������ƴ������Ӧ������(�ؼ���)
	{
		s0+=name[r]; 
		adr=s0%M;   //ʹ�ù�ϣ����
		d=adr;
	}
	if(HashList[adr].k==s0)          //��3����������ж�
	{
		printf("\n����:%s   �ؼ���:%d   ���ҳ���Ϊ: 1",HashList[d].py,s0); 
	}
	else if (HashList[adr].k==0) 
	{
		printf("�޴˼�¼!");
	}
	else
	{
		int g=0;
		do
		{
			d=(d+s0%10+1)%M;       //α���̽����ɢ�з������ͻ                     
			sum=sum+1;
			if (HashList[d].k==0)
			{
				printf("�޴˼�¼! ");  
				g=1;     
			}
			if (HashList[d].k==s0)
			{    
				printf("\n����:%s   �ؼ���:%d   ���ҳ���Ϊ:%d",HashList[d].py,s0,sum); 
				g=1;  
			}
		}while(g==0);   
	}
}

void   Display() // ��ʾ��ϣ��       
{
	int i;
	float average=0;
	printf("\n\n��ַ\t�ؼ���\t\t�������� \t����\n"); //��ʾ�ĸ�ʽ
	for(i=0; i<50; i++)
	{
		printf("%d ",i); 
		printf("\t%d ",HashList[i].k);
		printf("\t\t%d ",HashList[i].si); 
		printf("\t\t %s ",HashList[i].py);
		printf("\n");
	}

	for (i=0;i<HASH_LEN;i++)
	{
		average+=HashList[i].si; 
		average/=NAME_NO;
		printf("\n\nƽ�����ҳ��ȣ�ASL(%d)=%f \n\n",NAME_NO,average); 
	}
}

void haxi()
{
	char ch1;
	printf("\n                           ��ϣ�����ɼ���ϣ�����㷨\n");
	printf(" **********************************����20082557******************************\n");
	printf("                                                         \n"); 
	printf("                            1. ��ʾ�����Ĺ�ϣ��                 \n"); 
	printf("                            2. ��ϣ��Ĳ���                       \n"); 
	printf("                            3. �˳�                       \n");
	printf("                                                           \n"); 
	InitNameList();                                
	CreateHashList ();                        
	while(1)
	{
		printf("\n����������ѡ��:");
		fflush(stdin);
		ch1=getchar();
		if (ch1=='1') 
		{
			Display();   
		}
		else if (ch1=='2') 
		{
			FindList();
		}
		else if (ch1=='3') 
		{
			return;
		}
		else 
		{ 
			printf("\n��������ȷ��ѡ��!"); 
		}
	}
}


void hash()
{
	haxi();

}

int main(void)
{
	hash();
	return 1 ;
}

