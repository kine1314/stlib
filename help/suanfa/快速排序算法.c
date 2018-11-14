#include <stdio.h>

void quick_sort(int[], int, int, int);

void quicksort()
{
	int data[50];
	int size = 0, i,s;

	/* 要求输入数据直到输入数据为零 */
	printf("-----------------------快速排序算法演示-----------------------");
	printf("编写人：高云川         学号：20082556");
	printf("\n请输入要排序的数字序列，数字以空格为间隔 ( 以0结束输入 ):\n");
	printf("数字序列 : ");
	do
	{
		scanf("%d", &data[size]);

	}  while(data[size++] != 0);
	printf("\n");
	quick_sort(data, 0, --size-1, size-1);
	printf("请选择排序方式:\n ") ;
	printf("\n");
	printf("1、 从小到大\n");
	printf("2、 从大到小\n");
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
			printf("错误\n");
	}
	//            getch();
}
void quick_sort(int data[], int left, int right, int size)
{   
	/* left与right分别表欲排序数据两端 */
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
		while(lbase < rbase)  /* 若lbase小于rbase，则两数据对调 */
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
		temp = data[left];  /* 此时lbase大于rbase，则rbase的数据与第一笔对调 */
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


