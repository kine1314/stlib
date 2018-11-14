#include <stdio.h>
#include <stdlib.h>

void jishupaixu1(int data[],int en)
{
	int temp[10][10]={0} ;
	int order[10]={0} ;
	int i, j, k, n, lsd;
	k = 0;
	n = 1;

	printf("你输入的排序序列是: \n");
	for(i = 0; i < en; i++)
	{
		printf("%d ", data[i]);
	}
	putchar('\n');
	//按个位数分配到不同的桶中
	/*  22 44 24 32 55 65 56 77 43 89 
	 */
	while (n <= 100)
	{
		int r= 0;
		int m= 1;

		for (i = 0; i < en; i++)
		{
			lsd = ((data[i]/n)%en);				//末尾有效数字
			temp[lsd][order[lsd]] = data[i];	//将data中的数据按其末尾放在不同的桶中
			order[lsd]++;						//桶中的容量加1
		}
		m=n;
		while(m!=0)
		{
			m=m/10;
			r++;
		}
		printf("\n第%d趟排序结果:\n",r);
		for (i = 0; i < en; i++)
		{
			if (order[i] != 0)					//若桶中有元素时之下下列操作 
			{
				for(j = 0 ; j<order[i] ; j++)	//order[i]为第i个桶中元素的个数
				{
					data[k] = temp[i][j];		//将桶中的元素收集起来放在data[k]中
					printf("%d ", data[k]);
					k++;
				}
				order[i] = 0;					//元素取完后，置为空，退出循环。
			} 
		}
		printf("\n");
		n *= 10;
		k = 0;
	}
	printf("\n最后的排序结果是:\n");

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

	printf("你输入的排序序列是: \n");
	for(i = 0; i < en; i++)
	{
		printf("%d ", data[i]);
	}
	putchar('\n');
	//按个位数分配到不同的桶中
	while (n <= 100)
	{
		int r=0;
		int m=1;
		for (i = 0; i < en; i++)
		{
			lsd = ((data[i]/n)%en);				//末尾有效数字
			temp[lsd][order[lsd]] = data[i];	//将data中的数据按其末尾放在不同的桶中
			order[lsd]++;						//桶中的容量加1
		}
		m=n;
		while(m!=0)
		{

			m=m/10;
			r++;
		}
		printf("\n第%d趟排序结果:\n",r);
		for (i = 0; i < en; i++)
		{
			if (order[i] != 0)					//若桶中有元素时,下列操作 
			{
				for(j = 0; j<order[i] ; j++)	//order[i]为第i个桶中元素的个数
				{
					data[k] = temp[i][j];       //将桶中的元素收集起来放在data[k]中
					printf("%d ", data[k]);
					k++;
				}
				order[i] = 0;					//元素取完后，置为空，退出循环。
			}
		}
		printf("\n");
		n *= 10;
		k = 0;
	}

	printf("\n最后的排序结果是:\n");

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
	printf("-----------------------------基数排序算法演示程序---------------------------\n");

	printf("排序说明：\n输入10个数字，输出输出每步骤排序情况；希望能进行排序方向的选择（从大到小或从小到大）\n");
	printf("\n制作人：马静　　　学号：20082554        班级：计0805-3班\n");

	printf("\n请输入待排序的数字序列(每个数字键用回车间隔)：\n\n");
	for(i=0;i<10;i++)
	{
		printf("第%d个数字:",i+1);
		scanf("%d",&data[i]);
	} 
	printf("\n输入完毕！\n");
	printf("请选择进行排序的方向：\n");
	printf("1：从小到大\n2:从大到小\n");
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
			printf("你输入正确的数字选择！\n");
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

