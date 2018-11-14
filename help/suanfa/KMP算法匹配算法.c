#include<string.h>
#include<stdio.h> 
#include<stdlib.h> 
#define FALSE 0
#define OK 1
#define ERROR 0  

typedef int Status; 

#define MAXSTRLEN 40 

typedef char SString[MAXSTRLEN+1]; 

Status StrAssign(SString T,char *chars)
{ 
	int i;
	if(strlen(chars)>MAXSTRLEN)
	{
		return ERROR;
	}
	else
	{
		T[0]=strlen(chars);
		for(i=1;i<=T[0];i++)
		{
			T[i]=*(chars+i-1);
		}
		return OK;
	}
}

int StrLength(SString S)
{ 
	return S[0];
}

void get_nextval(SString T,int nextval[])
{ 
	int i=1,j=0;
	nextval[1]=0;
	while(i<T[0])
	{
		if(j==0||T[i]==T[j])
		{
			++i;
			++j;
			if(T[i]!=T[j])
			{
				nextval[i]=j;
			}
			else
			{
				nextval[i]=nextval[j];
			}
		}
		else
		{
			j=nextval[j];
		}
	}
}

int Index_KMP(SString S,SString T,int pos,int next[])
{ 
	int i=pos,j=1;
	while(i<=S[0]&&j<=T[0])
	{
		if(j==0||S[i]==T[j])
		{
			++i;
			++j;
		}
		else 
		{
			j=next[j];
		}
	}

	if(j>T[0]) 
	{
		return i-T[0];
	}
	else
	{
		return 0;
	}
}

void kmp()
{
	int i,j,*p;
	SString s1,s2,s3,s4; 
	printf("                  *****以下是KMP模式匹配算法的演示*****\n");
	printf("\n");
	printf("编写人：孙伟伟     学号：20082547\n");
	printf("\n");
	printf("请输入主串,以回车键结束: ");
	scanf("%s",s3);
	StrAssign(s1,s3); 
	printf("\n");
	printf("请输入模式串，以回车键结束: ");
	scanf("%s",s4);
	StrAssign(s2,s4);   
	i=StrLength(s2);
	p=(int*)malloc((i+1)*sizeof(int)); 
	get_nextval(s2,p);
	printf("\n");
	printf("模式串的nextval函数值为: ");
	for(j=1;j<=i;j++)
	{
	printf("%d ",*(p+j));
	}
	printf("\n");
	printf("主串和子串在第%d个字符处首次匹配\n",Index_KMP(s1,s2,1,p));
}

int main(void)
{
	kmp();
	return 1 ;
}
