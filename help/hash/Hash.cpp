#include<stdio.h>
#include<iostream.h>
#include<stdlib.h>
#define HASH_LENGTH 50               //哈希表的长度         
#define M 47                         //随机数
#define NAME_NO 30                   //人名的个数        
typedef struct      
{   char *py;    //名字的拼音
    int k;       //拼音所对应的整数
}NAME;
NAME NameList[HASH_LENGTH];    //全局变量NAME       
typedef struct    //哈希表
{   char *py;   //名字的拼音
    int k;      //拼音所对应的整数
    int si;     //查找长度
}HASH;
HASH HashList[HASH_LENGTH];        //全局变量HASH                     
void InitNameList() //姓名（结构体数组）初始化          
{   char *f;
    int r,s0,i;
    NameList[0].py="zengqinghui";
    NameList[1].py="mayuelong";
    NameList[2].py="chenzhicheng";
    NameList[3].py="sunpeng";
    NameList[4].py="wanghui";
    NameList[5].py="liqingbo";
    NameList[6].py="liujunpeng";
    NameList[7].py="jiangquanlei";
    NameList[8].py="xingzhengchuan";
    NameList[9].py="luzhaoqian";
    NameList[10].py="gaowenhu";
    NameList[11].py="zhuhaoyin";
    NameList[12].py="chenlili";
    NameList[13].py="wuyunyun";
    NameList[14].py="huangjuanxia";
    NameList[15].py="wangyan";
    NameList[16].py="zhoutao";
    NameList[17].py="jiangzhenyu";
    NameList[18].py="liuxiaolong";
    NameList[19].py="wangziming";
    NameList[20].py="fengjunbo";
    NameList[21].py="lilei"; 
    NameList[22].py="wangjia";
    NameList[23].py="zhangjianguo";
    NameList[24].py="zhuqingqing";
    NameList[25].py="huangmin";
    NameList[26].py="haoyuhan";
    NameList[27].py="zhoutao";
    NameList[28].py="zhujiang";
    NameList[29].py="lixiaojun";
    for(i=0;i<NAME_NO;i++)
	{   s0=0;
        f=NameList[i].py;
        for(r=0;*(f+r)!='\0';r++) 
			/* 方法：将字符串的各个字符所对应的ASCII码相加，所得的整数做为哈希表的关键字*/
            s0=*(f+r)+s0;
        NameList[i].k=s0;
	} 
}
void CreateHashList() //建立哈希表   
{	int i;
    for(i=0; i<HASH_LENGTH;i++) 
	{   HashList[i].py="";
        HashList[i].k=0;
        HashList[i].si=0;
	}
    for(i=0;i<HASH_LENGTH;i++)
	{   int sum=0;
        int adr=(NameList[i].k)%M;  //哈希函数
        int d=adr;
        if(HashList[adr].si==0)     //如果不冲突
		{  HashList[adr].k=NameList[i].k;
           HashList[adr].py=NameList[i].py;
           HashList[adr].si=1;
	   }
       else   //冲突  
	   { do
		  {   d=(d+NameList[i].k%10+1)%M;   //伪随机探测再散列法处理冲突    
              sum=sum+1;                    //查找次数加1    
		  }while (HashList[d].k!=0);
         HashList[d].k=NameList[i].k;
         HashList[d].py=NameList[i].py;
         HashList[d].si=sum+1;
	   }
	}
}
void  FindList() //查找    
{	char name[20]={0}; 
    int s0=0,r,sum=1,adr,d;
    printf("请输入姓名的拼音:");     
    scanf("%s",name); 
    for(r=0;r<20;r++)   //求出姓名的拼音所对应的整数(关键字)
        s0+=name[r]; 
    adr=s0%M;   //使用哈希函数
    d=adr;
    if(HashList[adr].k==s0)          //分3种情况进行判断
       printf("\n姓名:%s   关键字:%d   查找长度为: 1",HashList[d].py,s0); 
    else if (HashList[adr].k==0) 
         printf("无此记录!");
    else
	{   int g=0;
        do
		{   d=(d+s0%10+1)%M;       //伪随机探测再散列法处理冲突                     
            sum=sum+1;
            if(HashList[d].k==0)
			{  printf("无此记录! ");  
               g=1;     
			}
            if(HashList[d].k==s0)
			{  printf("\n姓名:%s   关键字:%d   查找长度为:%d",HashList[d].py,s0,sum); 
               g=1;  
			}
		}while(g==0);   
	}  
}
void   Display() // 显示哈希表       
{	int i;
    float average=0;
    printf("\n地址\t关键字\t\t搜索长度\tH(key)\t 姓名\n"); //显示的格式
    for(i=0; i<50; i++)
	{   printf("%d ",i); 
        printf("\t%d ",HashList[i].k);
        printf("\t\t%d ",HashList[i].si);
        printf("\t\t%d ",HashList[i].k%M);
        printf("\t %s ",HashList[i].py);
        printf("\n");
	}
    for(i=0;i<HASH_LENGTH;i++)
        average+=HashList[i].si; 
    average/=NAME_NO;
    printf("\n平均查找长度：ASL(%d)=%f \n",NAME_NO,average); 
}
void main()
{	char ch1;
	InitNameList();                                
    CreateHashList (); 
	do
	{	printf("D. 显示哈希表\nF. 查找\nQ. 退出\n请选择：");
		cin>>&ch1;
		switch(ch1)
		{
		case 'D':Display(); cout<<endl;break;
		case 'F':FindList();cout<<endl;break;
		case 'Q':exit(0);
		}
		cout<<"come on !(y/n):";
		cin>>&ch1;
	}while(ch1!='n'); 
}