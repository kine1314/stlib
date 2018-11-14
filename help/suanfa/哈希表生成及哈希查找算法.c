#include<stdio.h>
#include<conio.h>
#define HASH_LEN 50                      //哈希表的长度 
#define M 47                            //随机数
#define NAME_NO 15                      //人名的个数        

typedef struct      
{
	char *py;    //名字的拼音
	int k;       //拼音所对应的整数
}NAME;

NAME NameList[HASH_LEN];    //全局变量NAME             
typedef struct    //哈希表
{
	char *py;   //名字的拼音
	int k;      //拼音所对应的整数
	int si;     //查找长度
}HASH;
HASH HashList[HASH_LEN];        //全局变量HASH                     

void InitNameList() //姓名（结构体数组）初始化          
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
			/* 方法：将字符串的各个字符所对应的ASCII码相加，所得的整数做为哈希表的关键字*/
			s0=*(f+r)+s0;
			NameList[i].k=s0;
		}
	}
}

void CreateHashList() //建立哈希表   
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
		int adr=(NameList[i].k)%M;  //哈希函数
		int d=adr;
		if(HashList[adr].si==0)     //如果不冲突
		{
			HashList[adr].k=NameList[i].k;
			HashList[adr].py=NameList[i].py;
			HashList[adr].si=1;
		}
		else   //冲突  
		{
			do
			{
				d=(d+NameList[i].k%10+1)%M;   //伪随机探测再散列法处理冲突    
				sum=sum+1;   //查找次数加1    
			}while (HashList[d].k!=0);

			HashList[d].k=NameList[i].k;
			HashList[d].py=NameList[i].py;
			HashList[d].si=sum+1;
		}
	}
}
void   FindList() //查找    
{  
	char name[20]={0}; 
	int s0=0,r,sum=1,adr,d;
	printf("\n请输入姓名的拼音:");     
	scanf("%s",name); 
	for (r=0;r<20;r++)   //求出姓名的拼音所对应的整数(关键字)
	{
		s0+=name[r]; 
		adr=s0%M;   //使用哈希函数
		d=adr;
	}
	if(HashList[adr].k==s0)          //分3种情况进行判断
	{
		printf("\n姓名:%s   关键字:%d   查找长度为: 1",HashList[d].py,s0); 
	}
	else if (HashList[adr].k==0) 
	{
		printf("无此记录!");
	}
	else
	{
		int g=0;
		do
		{
			d=(d+s0%10+1)%M;       //伪随机探测再散列法处理冲突                     
			sum=sum+1;
			if (HashList[d].k==0)
			{
				printf("无此记录! ");  
				g=1;     
			}
			if (HashList[d].k==s0)
			{    
				printf("\n姓名:%s   关键字:%d   查找长度为:%d",HashList[d].py,s0,sum); 
				g=1;  
			}
		}while(g==0);   
	}
}

void   Display() // 显示哈希表       
{
	int i;
	float average=0;
	printf("\n\n地址\t关键字\t\t搜索长度 \t姓名\n"); //显示的格式
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
		printf("\n\n平均查找长度：ASL(%d)=%f \n\n",NAME_NO,average); 
	}
}

void haxi()
{
	char ch1;
	printf("\n                           哈希表生成及哈希查找算法\n");
	printf(" **********************************梁鑫20082557******************************\n");
	printf("                                                         \n"); 
	printf("                            1. 显示创建的哈希表                 \n"); 
	printf("                            2. 哈希表的查找                       \n"); 
	printf("                            3. 退出                       \n");
	printf("                                                           \n"); 
	InitNameList();                                
	CreateHashList ();                        
	while(1)
	{
		printf("\n请输入您的选择:");
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
			printf("\n请输入正确的选择!"); 
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

