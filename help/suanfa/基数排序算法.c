#include <stdio.h>
#include <stdlib.h>

void jishupaixu1(int data[],int en)
{
	int temp[10][10]={0} ;
	int order[10]={0} ;
	int i, j, k, n, lsd;
	k = 0;
	n = 1;

	printf("�����������������: \n");
	for(i = 0; i < en; i++)
	{
		printf("%d ", data[i]);
	}
	putchar('\n');
	//����λ�����䵽��ͬ��Ͱ��
	/*  22 44 24 32 55 65 56 77 43 89 
	 */
	while (n <= 100)
	{
		int r= 0;
		int m= 1;

		for (i = 0; i < en; i++)
		{
			lsd = ((data[i]/n)%en);				//ĩβ��Ч����
			temp[lsd][order[lsd]] = data[i];	//��data�е����ݰ���ĩβ���ڲ�ͬ��Ͱ��
			order[lsd]++;						//Ͱ�е�������1
		}
		m=n;
		while(m!=0)
		{
			m=m/10;
			r++;
		}
		printf("\n��%d��������:\n",r);
		for (i = 0; i < en; i++)
		{
			if (order[i] != 0)					//��Ͱ����Ԫ��ʱ֮�����в��� 
			{
				for(j = 0 ; j<order[i] ; j++)	//order[i]Ϊ��i��Ͱ��Ԫ�صĸ���
				{
					data[k] = temp[i][j];		//��Ͱ�е�Ԫ���ռ���������data[k]��
					printf("%d ", data[k]);
					k++;
				}
				order[i] = 0;					//Ԫ��ȡ�����Ϊ�գ��˳�ѭ����
			} 
		}
		printf("\n");
		n *= 10;
		k = 0;
	}
	printf("\n������������:\n");

	for (i = 0; i <en; i++)
	{
		printf("%d ", data[i]);
	}
	putchar('\n');

	return ;

}


void jishupaixu2(int data[],int en)
{
	int temp[10][10]={0} ;
	int order[10]={0} ;
	int i, j, k, n, lsd;
	k = 0;
	n = 1;

	printf("�����������������: \n");
	for(i = 0; i < en; i++)
	{
		printf("%d ", data[i]);
	}
	putchar('\n');
	//����λ�����䵽��ͬ��Ͱ��
	while (n <= 100)
	{
		int r=0;
		int m=1;
		for (i = 0; i < en; i++)
		{
			lsd = ((data[i]/n)%en);				//ĩβ��Ч����
			temp[lsd][order[lsd]] = data[i];	//��data�е����ݰ���ĩβ���ڲ�ͬ��Ͱ��
			order[lsd]++;						//Ͱ�е�������1
		}
		m=n;
		while(m!=0)
		{

			m=m/10;
			r++;
		}
		printf("\n��%d��������:\n",r);
		for (i = 0; i < en; i++)
		{
			if (order[i] != 0)					//��Ͱ����Ԫ��ʱ,���в��� 
			{
				for(j = 0; j<order[i] ; j++)	//order[i]Ϊ��i��Ͱ��Ԫ�صĸ���
				{
					data[k] = temp[i][j];       //��Ͱ�е�Ԫ���ռ���������data[k]��
					printf("%d ", data[k]);
					k++;
				}
				order[i] = 0;					//Ԫ��ȡ�����Ϊ�գ��˳�ѭ����
			}
		}
		printf("\n");
		n *= 10;
		k = 0;
	}

	printf("\n������������:\n");

	for (i =en-1; i >=0; i--)
	{
		printf("%d ", data[i]);
	}
	putchar('\n');

	return ;
}




void jishupaixu15()
{
	int i,j;

	int data[10] ;
	printf("-----------------------------���������㷨��ʾ����---------------------------\n");

	printf("����˵����\n����10�����֣�������ÿ�������������ϣ���ܽ����������ѡ�񣨴Ӵ�С���С����\n");
	printf("\n�����ˣ���������ѧ�ţ�20082554        �༶����0805-3��\n");

	printf("\n��������������������(ÿ�����ּ��ûس����)��\n\n");
	for(i=0;i<10;i++)
	{
		printf("��%d������:",i+1);
		scanf("%d",&data[i]);
	} 
	printf("\n������ϣ�\n");
	printf("��ѡ���������ķ���\n");
	printf("1����С����\n2:�Ӵ�С\n");
	scanf("%d",&j);
loop:

	switch(j)
	{
		case 1:
			jishupaixu1(data,10);break;
		case 2:
			jishupaixu2(data,10);break;
		default:
		{
			printf("��������ȷ������ѡ��\n");
			scanf("%d",&j);
			goto loop;
		}
	}

} 

int main(void)
{
	jishupaixu15();
	return 1 ;
}

