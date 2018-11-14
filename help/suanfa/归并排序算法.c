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

/*������������*/
void Link_data(int *a,int *b,int *c,int len_a,int len_b)
{
	int i = 0,j = 0, k = 0;

	while( i < len_a &&j < len_b )
	{
		/*���A�����е�Ԫ�ش󣬷Ž�c�в���ָ��i�����ƶ�������B�����е�Ԫ�طŽ�C�У�ָ��j�����ƶ�*/
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


	/*���ָ��i��������a�ĳ��ȣ����ʾa�Ѿ����꣬���bʣ��ķŽ�c*/
	if( i >= len_a )
	{
		for( ; j < len_b; j++)
		{
			c[k] =b[j];
			k++;
		}
	}
	/*���ָ��j��������b�ĳ��ȣ����ʾb�Ѿ����꣬���aʣ��ķŽ�c*/
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
	printf("\n                                �鲢����\n");
	printf(" **********************************����20082557******************************\n");
	printf("                            1. �Ӵ�������              \n"); 
	printf("                            2. ��С��������              \n"); 
	printf("                            3. �˳�                       \n");
	printf("                                                           \n"); 
	while(1)
	{
		printf("����������Ҫ��˳��:");
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
			printf("\n��������ȷ��ѡ��!"); 
		}
	}
	printf("������10 ����: \n");
}



int main(void)
{
	guibing();
	return 1 ;

}

