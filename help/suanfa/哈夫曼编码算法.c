#include   <stdio.h>   
#include   <string.h>   
#include   <stdlib.h>   
#include   <malloc.h>   
#include   <conio.h>   
typedef   struct   
{   
	unsigned   int   weight;   
	unsigned   int   parent,lchild,rchild;   
}   HTNode,*HuffmanTree;   

typedef   char   **HuffmanCode;   

typedef   struct   
{   
	unsigned   int   s1;   
	unsigned   int   s2;   
}   MinCode;   

void   Error(char   *message);   
HuffmanCode   HuffmanCoding(HuffmanTree   HT,HuffmanCode   HC,unsigned   int   *w,unsigned   int   n);   
MinCode   Select(HuffmanTree   HT,unsigned   int   n);   

void   Error(char   *message)   
{   
	fprintf(stderr,"Error:%s\n",message);   
	exit(1);   
}   

HuffmanCode   HuffmanCoding(HuffmanTree   HT,HuffmanCode   HC,unsigned   int   *w,unsigned   int   n)   
{   
	unsigned   int   i,s1=0,s2=0;   
	HuffmanTree   p;   
	char   *cd;   
	unsigned   int   f,c,start,m;   
	MinCode   min;   
	if(n<=1)   
	{
		Error("Code   too   small!");   
	}
	m=2*n-1;   
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));   

	for(p=HT,i=0;i<=n;i++,p++,w++)   
	{   
		p->weight=*w;   
		p->parent=0;   
		p->lchild=0;   
		p->rchild=0;   
	}   

	for(;i<=m;i++,p++)   
	{   
		p->weight=0;   
		p->parent=0;   
		p->lchild=0;   
		p->rchild=0;   
	}   

	for(i=n+1;i<=m;i++)   
	{   
		min=Select(HT,i-1);   
		s1=min.s1;   
		s2=min.s2;   
		HT[s1].parent=i;   
		HT[s2].parent=i;   
		HT[i].lchild=s1;   
		HT[i].rchild=s2;   
		HT[i].weight=HT[s1].weight+HT[s2].weight;   
	}   
	printf("HT   List:\n");   
	printf("Number\t\tweight\t\tparent\t\tlchild\t\trchild\n");   
	for(i=1;i<=m;i++)   
	{
		printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	}

	HC=(HuffmanCode)malloc((n+1)*sizeof(char   *));   
	cd=(char   *)malloc(n*sizeof(char   *));   
	cd[n-1]='\0';   
	for(i=1;i<=n;i++)   
	{   
		start=n-1;   
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)   
		{
			if(HT[f].lchild==c)   
			{
				cd[--start]='0';   
			}
			else   
			{
				cd[--start]='1';
			}
		}

		HC[i]=(char   *)malloc((n-start)*sizeof(char   *));   
		strcpy(HC[i],&cd[start]);   
	}   
	free(cd);   
	return   HC;   
}   



MinCode   Select(HuffmanTree   HT,unsigned   int   n)   
{   
	unsigned   int   min,secmin;   
	unsigned   int   temp;   
	unsigned   int   i,s1,s2,tempi;   
	MinCode   code;   
	s1=1;s2=1;   

	for(i=1;i<=n;i++)   
	{
		if(HT[i].parent==0)   
		{   
			min=HT[i].weight;   
			s1=i;   
			break;   
		}   
		tempi=i++;   
	}

	for(;i<=n;i++)   
	{
		if(HT[i].weight<min&&HT[i].parent==0)   
		{   
			min=HT[i].weight;   
			s1=i;   
		}   
	}

	for(i=tempi;i<=n;i++)  
	{
		if(HT[i].parent==0&&i!=s1)   
		{   
			secmin=HT[i].weight;   
			s2=i;   
			break;   
		}   
	}

	for(i=1;i<=n;i++)   
	{
		if(HT[i].weight<secmin&&i!=s1&&HT[i].parent==0)   
		{   
			secmin=HT[i].weight;   
			s2=i;   
		}   
		if(s1>s2)   
		{   
			temp=s1;   
			s1=s2;   
			s2=temp;   
		}   
		code.s1=s1;   
		code.s2=s2;   
	}
	return   code;   
}   

void   hfm()   
{   
	HuffmanTree   HT=NULL;   
	HuffmanCode   HC=NULL;   
	unsigned   int   *w=NULL;   
	unsigned   int   i,n; 
	printf("¹þ¸¥Âü´úÂë\n");
	printf("ÁºöÎ20082557\n");
	printf("Input   n:\n");   
	scanf("%d",&n);   
	w=(unsigned   int   *)malloc((n+1)*sizeof(unsigned   int   *));   
	w[0]=0;   
	printf("Enter   weight:\n");   
	for(i=1;i<=n;i++)   
	{   
		printf("w[%d]=",i);   
		scanf("%d",&w[i]);   
	}   
	HC=HuffmanCoding(HT,HC,w,n);   
	printf("HuffmanCode:\n");   
	printf("Number\t\tWeight\t\tCode\n");   
	for(i=1;i<=n;i++)   
	{
		printf("%d\t\t%d\t\t%s\n",i,w[i],HC[i]);   
	}

} 

int main(void)
{
	hfm();
	return 1 ;
}