#include <stdio.h>


void Sort( int *p,int n )
{
	int i,j,temp;

	for( i = 0; i < n; i++ )
	{
		for( j = i + 1; j < n; j++ )
		{
			if( *(p+i) < *(p+j) )
			{
				temp  = *(p+i);
				*(p+i)  = *(p+j);
				*(p+j)  = temp;
			}
		}
	}
}

/*连接两个数组*/
void Link_data(int *a,int *b,int *c,int len_a,int len_b)
{
	int i = 0,j = 0, k = 0;

	while( i < len_a &&j < len_b )
	{
		/*如果A数组中的元素大，放进c中并且指针i向下移动，否则B数组中的元素放进C中，指针j向下移动*/
		if( a[i] > b[j] )
		{
			c[k] = a[i];
			k++;
			i++;
		}
		else
		{
			c[k] = b[j];
			j++;
			k++;
		}
	}


	/*如果指针i大于数组a的长度，则表示a已经读完，则把b剩余的放进c*/
	if( i >= len_a )
	{
		for( ; j < len_b; j++)
		{
			c[k] =b[j];
			k++;
		}
	}
	/*如果指针j大于数组b的长度，则表示b已经读完，则把a剩余的放进c*/
	if( j >= len_b )
	{
		for(;i < len_a; i++ )
		{
			c[k] = a[i];
			k++;
		}
	}
}
void gb1()
{
	int  i, a[5],b[5] , c[10],d[10] ;
	for(i=0;i<10;i++)
	{
		scanf("%d",&d[i]);
	}
	for(i=0;i<5;i++)
	{
		a[i]=d[i];
	}
	for(i=5;i<10;i++)
	{
		b[i-5]=d[i];
	}
	Sort(a,5);
	Sort(b,5);
	Link_data(a,b,c,5,5);
	for( i = 0; i < 10; i++ )
	{
		printf("%d ",c[i]);
	}

}
void gb2()
{
	int  i, a[5],b[5] , c[10],d[10] ;
	for(i=0;i<10;i++)
	{
		scanf("%d",&d[i]);
	}
	for(i=0;i<5;i++)
	{
		a[i]=d[i];
	}
	for(i=5;i<10;i++)
	{
		b[i-5]=d[i];
	}
	Sort(a,5);
	Sort(b,5);
	Link_data(a,b,c,5,5);
	for( i = 9; i >=0; i-- )
	{
		printf("%d ",c[i]);
	}

}

void guibing()
{
	char ch1;
	printf("\n                                归并代码\n");
	printf(" **********************************梁鑫20082557******************************\n");
	printf("                            1. 从大到下排序              \n"); 
	printf("                            2. 从小到大排序              \n"); 
	printf("                            3. 退出                       \n");
	printf("                                                           \n"); 
	while(1)
	{
		printf("请输入您需要的顺序:");
		ch1=getchar();
		if (ch1=='1')  
		{
			gb1();   
		}
		else if (ch1=='2') 
		{
			gb2();
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
	printf("请输入10 个数: \n");
}



int main(void)
{
	guibing();
	return 1 ;

}

