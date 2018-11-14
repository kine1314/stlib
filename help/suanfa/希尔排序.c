#include <stdio.h>
void shell_sort1(int arr[],int size)//排序从小到大
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
		printf("第%d步骤的排序情况：\n",n);
		printf("步长是：%d\n",i);
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

void shell_sort2(int arr[],int size)//排序从大到小
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
		printf("每个步骤的排序情况(排序趟数  相应步长：\n");
		for(m=0;m<j;m++)
		{
			printf("%d ",arr[m]);
		}
		printf("\n");
		printf("排序趟数：%d 相应步长： %d",n,i);
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
	printf("----------------------------希尔排序算法演示程序----------------------------\n");
	printf("\n制作人： 马静           学号： 20082554            班级：计0801-3班\n");  
	printf("\n排序说明：\n");

	printf("排序限制：只可输10个数,并以回车间隔。\n");
	printf("\n请输入你要进行希尔排序的序列：\n");
	for(i=0;i<10;i++)
	{
		scanf("%d",&arr[i]);
	}

	printf("请选择你希望能进行排序方向（从大到小或从小到大）\n");
	printf("1：从小到大\n");
	printf("2:从大到小\n");
	printf("请输入你的选择：");
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
			printf("你的输入有误，请重新输入！\n");
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
