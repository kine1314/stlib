#include <stdio.h>

void quick_sort(int[], int, int, int);

void quicksort()
{
	int data[50];
	int size = 0, i,s;

	/* Ҫ����������ֱ����������Ϊ�� */
	printf("-----------------------���������㷨��ʾ-----------------------");
	printf("��д�ˣ����ƴ�         ѧ�ţ�20082556");
	printf("\n������Ҫ������������У������Կո�Ϊ��� ( ��0�������� ):\n");
	printf("�������� : ");
	do
	{
		scanf("%d", &data[size]);

	}  while(data[size++] != 0);
	printf("\n");
	quick_sort(data, 0, --size-1, size-1);
	printf("��ѡ������ʽ:\n ") ;
	printf("\n");
	printf("1�� ��С����\n");
	printf("2�� �Ӵ�С\n");
	scanf("%d",&s);
	printf("\n ");
	switch(s)
	{ 
		case 1:
			for(i = 0; i < size; i++)
			{
				printf("%d  ", data[i]);
				printf("\n ");
			}
		break;
		case 2:
			for(i =size-1 ; i >=0 ; i--)
			{
				printf("%d ", data[i]);
				printf("\n ");
			}
		break;
		default:
			printf("����\n");
	}
	//            getch();
}
void quick_sort(int data[], int left, int right, int size)
{   
	/* left��right�ֱ���������������� */
	int lbase, rbase, temp, i;
	if(left < right)
	{
		lbase = left+1;
		while(data[lbase] < data[left]) 
		{
			lbase++;
		}
		rbase = right;
		while(data[rbase] > data[left]) 
		{
			rbase--;
		}
		while(lbase < rbase)  /* ��lbaseС��rbase���������ݶԵ� */
		{
			temp = data[lbase];
			data[lbase] = data[rbase];
			data[rbase] = temp;
			lbase++;
			while(data[lbase] < data[left]) 
			{
				lbase++;
			}
			rbase--;
			while(data[rbase] > data[left]) 
			{
				rbase--;
			}
		}
		temp = data[left];  /* ��ʱlbase����rbase����rbase���������һ�ʶԵ� */
		data[left] = data[rbase];
		data[rbase] = temp;
		printf("\n");
		for(i = 0; i < size; i++)
		{
			printf("%d  ", data[i]);
			printf("\n");
		}
		quick_sort(data, left, rbase-1, size);
		quick_sort(data, rbase+1, right, size);
	}
}



int main(void)
{
	quicksort();
	return 1;
}


