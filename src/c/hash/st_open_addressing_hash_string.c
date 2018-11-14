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


#define M 			47                         	//随机数
  


NAME NameList[HASH_LENGTH];    		//全局变量NAME    
HASH HashList[HASH_LENGTH];        	//全局变量HASH    





void CreateHashList(NAME *NL, HASH *HL) //建立哈希表   
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
		int adr=((NL+i)->k)%HASH_LENGTH;  //哈希函数
		int d=adr;
		if(((HL+adr)->si) == 0)     //如果不冲突
		{  
			(HL+adr)->k=(NL+i)->k;
			(HL+adr)->py=(NL+i)->py;
			(HL+adr)->data="a"+i;
			(HL+adr)->si=1;
		}
		else   //冲突  
		{ 
			do
			{   
				d=(d+((NL+i)->k)%10+1)%HASH_LENGTH;   //伪随机探测再散列法处理冲突    
				sum=sum+1;                    //查找次数加1    
			}while ((HL+d)->k!=0);
			(HL+d)->k=(NL+i)->k;
			(HL+d)->py=(NL+i)->py;
			(HL+adr)->data="a"+i;
			(HL+d)->si=sum+1;
		}
	}
}

void  FindList(HASH *HL, char *name) //查找    
{	
	
	int s0=0,r,sum=1,adr,d;
	 
	for(r=0;(*(name+r) != '\0');r++)   //求出姓名的拼音所对应的整数(关键字)
		s0+=name[r]; 
	
	adr=s0%HASH_LENGTH;   //使用哈希函数
	d=adr;
	printf("s0 [%d] ,adr [%d]\n", s0, adr);
	if((HL+adr)->k == s0)          //分3种情况进行判断
		printf("\n姓名:%s   data:%s		关键字:%d   查找长度为: 1",(HL+d)->py, (HL+d)->data,s0); 
	else if ((HL+adr)->k==0) 
		printf("无此记录!");
	else
	{   
		int g=0;
		do
		{   
			d=(d+s0%10+1)%HASH_LENGTH;       //伪随机探测再散列法处理冲突                     
			sum=sum+1;
			if((HL+d)->k==0)
			{  
				printf("无此记录! ");  
				g=1;     
			}
			if((HL+d)->k==s0)
			{  
				printf("\n姓名:%s   data:%s		关键字:%d   查找长度为:%d",(HL+d)->py, (HL+d)->data,s0,sum); 
				g=1;  
			}
		}while(g==0);   
	}  
}

void   Display(HASH *HL) // 显示哈希表       
{	
	int i;
	float average=0;
	printf("\n地址\t关键字\t\t搜索长度\tH(key)\t 姓名\n"); //显示的格式
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
	printf("\n平均查找长度：ASL(%d)=%f \n",NAME_NO,average); 
}

void EraseHashList(HASH *HL)
{
	if(NULL != HL)
		memset(HL, 0, sizeof(HASH)*HASH_LENGTH);
}




/*	操作:	初始化一个字符串散列表	*/
/*	操作前:	size 是指定字符串散列表的大小的变量	*/
/*	操作后:	该表被创建并且表中的所有表元指针被初始化为空, 返回该表	*/
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

/*	操作:	返回一个指向表中指定数据所在结点的指针	*/
/*	操作前:	item 是被查找的数据, h 是一个已初始化的表	*/
/*	操作后:	如果可能, 返回指向表中指定数据所在结点的指针; 否则返回NULL	*/
NAMEP STRHFind (const STRItem item, const StringHashTP *ph) 
{
	int key, size, index, adr, d, critical, sum = 0, i = 0 ;

	size = (*ph)->size ;
	key = STRHash(item);			// 散列后的字符串关键值
	adr = key % size ;			// 初次求出在表中index，后续因为冲突会继续挑中
	d = adr ;
	critical = size / 2 ;

	do
	{
#if 0
		d=(d+key%10+1)%size; 	
		sum=sum+1;

#elif 0	// 线性探测发解决冲突，缺点比较集中
		d = (key%10 + (i++)) % size ;
		sum=sum+1;
		
#elif 0	// 平方探测法解决冲突
		if(i <= critical)
		{
			d = Square_ (i++) ;
			d = (key + Square_ (i++)) % size ;
			sum=sum+1;
		}
#elif 1	// 双哈希
		if(i < size)
		{
			d = (key + ((i++)*STHash2(item, 27))) % size ;		// 双散列探测地址法
			sum=sum+1;
		}
		else
		{
			break ;
		}
#endif
		
	}while(item != ((*ph)->sname+d)->py && Legitimate == ((*ph)->sname+d)->info);
	((*ph)->sname+d)->k = key ;
	((*ph)->sname+d)->si = sum ;		// 查找深度

	return (*ph)->sname+d ;
}

/*	操作:	将一个具有指定数据以插入新结点的方式插入到表中	*/
/*	操作前:	item 是待插入的数据, ph 指向一个已初始化的表	*/
/*	操作后:	如果可能, 以 item 为数据创建一个结点被插入到表中(如果冲突, 继续找位置), 返回1; 否则返回0	*/
int STRHInsert (const STRItem item, StringHashTP * const ph) 
{
	NAMEP position ;	

	position = STRHFind(item, ph);

	/* 成功找到插入位置，并进行赋值 */
	if(Empty == position->info || Deleted == position->info)
	{
		position->info = Legitimate ;
		position->py = item ;
		return SUCCESS ;
	}
	
	return UNSUCCESS ;
}

/*	操作:	从表中删除一个结点	*/
/*	操作前:	item 是待删除结点的数据, ph 指向一个已初始化的表	*/
/*	操作后:	如果可能, item 所在结点被从表中删除, 返回1; 否则返回0	*/
int STRHDelete (const STRItem item, StringHashTP * const ph) 
{
	NAMEP position ;	

	position = STRHFind(item, ph);
	if (Legitimate == position->info && item == position->py)
	{
		position->info = Deleted ;
		// 如果不清空，或者是动态申请的，可以实现懒惰删除
		position->py = NULL ;
		position->k = 0 ;
		return SUCCESS ;
	}

	return UNSUCCESS ;
}

/*	操作:	从低索引向高索引将一个函数作用于表中所有存在的结点	*/
/*	操作前:	ph 指向一个已初始化的表, pfun 指向一个没有返回值, 接受一个ListNode *类型参数的函数	*/
/*	操作后:	pfun 指向的函数被从低索引向高索引作用到所有存在的结点一次	*/
void STRHDisplay (const StringHashTP * const ph) 
{
	int i;
	float average=0;
	
	printf("\n地址\t关键字\t\t搜索长度\tH(key)\t 姓名\n"); //显示的格式
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

/*	操作:	清空一个表	*/
/*	操作前:	ph 指向一个已初始化的表	*/
/*	操作后:	该表所占用的全部内存空间被释放	*/
void STRHRelease (StringHashTP * ph) 
{
	free ((*ph)->sname) ;
	free (*ph) ;
	__inf("RELEASE THE STRHTABLE\n");
}









