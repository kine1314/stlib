#include <stdio.h>
void shell_sort1(int arr[],int size)//�����С����
{
	int i,j,k,temp,m,n=0;
	for(i=size/2;i>0;i/=2)         
	{
		n++;
		for(j=i;j<size;j++)
		{
			temp=arr[j];
			for(k=j-i;k>=0&&temp<arr[k];k-=i)
			{
				arr[k+i]=arr[k];
				//arr[k]=temp;
			}
			arr[k+i]=temp;

		}
		printf("��%d��������������\n",n);
		printf("�����ǣ�%d\n",i);
		for(m=0;m<j;m++)
		{
			printf("%d ",arr[m]);

		}
		printf("\n");
	}
	for(i=0;i<size;i++)
	{
		printf("%d\t ",arr[i]);

	}
}

void shell_sort2(int arr[],int size)//����Ӵ�С
{
	int i,j,k,temp,m,n=0;
	for(i=size/2;i>0;i/=2)         
	{
		for(j=i;j<size;j++,n++)
		{
			temp=arr[j];
			for(k=j-i;k>=0&&temp>arr[k];k-=i)
			{
				arr[k+i]=arr[k];
				//arr[k]=temp;
			}
			arr[k+i]=temp;
		}
		printf("ÿ��������������(��������  ��Ӧ������\n");
		for(m=0;m<j;m++)
		{
			printf("%d ",arr[m]);
		}
		printf("\n");
		printf("����������%d ��Ӧ������ %d",n,i);
	}
	for(i=0;i<size;i++)
	{
		printf("%d ",arr[i]);
	}
}

void xierpaixu11()
{
	int i , j;
	int arr[10];
	printf("----------------------------ϣ�������㷨��ʾ����----------------------------\n");
	printf("\n�����ˣ� ��           ѧ�ţ� 20082554            �༶����0801-3��\n");  
	printf("\n����˵����\n");

	printf("�������ƣ�ֻ����10����,���Իس������\n");
	printf("\n��������Ҫ����ϣ����������У�\n");
	for(i=0;i<10;i++)
	{
		scanf("%d",&arr[i]);
	}

	printf("��ѡ����ϣ���ܽ��������򣨴Ӵ�С���С����\n");
	printf("1����С����\n");
	printf("2:�Ӵ�С\n");
	printf("���������ѡ��");
	scanf("%d",&j);
loop :
	switch(j)
	{
		case 1 :
			shell_sort1(arr,10);break;
		case 2 :
			shell_sort2(arr,10);break;
		default :
		{
			printf("��������������������룡\n");
			scanf("%d",&j);
			goto loop;
		}
	}
	getchar();
}

int main(void)
{
	xierpaixu11();
	return 1 ;
}
