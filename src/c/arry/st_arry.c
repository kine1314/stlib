#include <stdlib.h>
#include <stdio.h>
#include "st_arry.h"




void st_dump_array(stint a[], stint n)
{
	stint i ;

	for(i = 0 ; i < n ; ++i)
	{
		printf("%o   %d\n", (stuint)a, a[i]);
	}
	printf("\n");
}

static void swap(stint **a,stint **b)  
{  
    stint temp; 
    temp=*a;  
    *a=*b;  
    *b=temp;  
}  




/** 
 * 复制数组 
 * source:源数组 
 * dest:目标数组 
 * len:源数组长度 
 * first:目标数组起始位置 
 * 
 */  
void copyArray(stint source[], stint dest[],stint len,stint first)  
{  
    stint i;  
    stint j=first;  
    for(i=0;i<len;i++)  
    {  
        dest[j] = source[i];  
        j++;  
    }  
          
}  

/* 二路归并排序,把两个已排序的数组合并成一个有序数组 */
void merge(stint a[],stint left,stint right)  
{  
    stint begin1 = left;  
    stint mid = (left+right)/2 ;  
    stint begin2 = mid+1;  
    stint k=0;  
    stint newArrayLen = right-left+1;  
    stint *b = (stint*)malloc(newArrayLen*sizeof(stint));  	//辅助空间,用以暂存已经排序的数组元素
    
    while(begin1<=mid && begin2<=right)  
    {  
		//比较两个下标begin1和begin2所代表的元素,选择相对小的元素放入到辅助空间b数组中,并移动下标到下一位置
        if(a[begin1]<=a[begin2])  
            b[k++] = a[begin1++];  
        else  
            b[k++] = a[begin2++];  
    }  
    while(begin1<=mid)  				//将剩余元素拷贝至b数组
        b[k++] = a[begin1++];  
    while(begin2<=right)  				//将剩余元素拷贝至b数组
        b[k++] = a[begin2++];  
    copyArray(b,a,newArrayLen,left);  	//将排序好的序列拷贝回数组a中
    free(b);  
}  

/*	11/2 = 5											LEFT	RIGHT		
 *	[4, 67, 456, 23, 1, 78, 26, 222, 34, 432, 12]		0		11
 *  [4, 67, 456, 23, 1, 78][26, 222, 34, 432, 12]		0		5
 * 	[4, 67, 456][23, 1, 78][26, 222, 34, 432, 12]		0		2
 *  [4, 67][456][23, 1, 78][26, 222, 34, 432, 12]		0		0
 * 	[4][67][456][23, 1, 78][26, 222, 34, 432, 12]		MERGE(0,1)
 * 	[4, 67][456][23, 1, 78][26, 222, 34, 432, 12]		2		2
 * 	[4, 67, 456][23, 1, 78][26, 222, 34, 432, 12]		MERGE(0,2)	
 * 	[4, 67, 456][23, 1][78][26, 222, 34, 432, 12]		3		4
 * 	[4, 67, 456][23][1][78][26, 222, 34, 432, 12]		3		3
 * 	[4, 67, 456][1, 23][78][26, 222, 34, 432, 12]		MERGE(3,4)
 * 	[4, 67, 456][1, 23, 78][26, 222, 34, 432, 12]		MERGE(3,5)
 * 	[1, 4, 23, 67, 78, 456][26, 222, 34, 432, 12]		MERGE(0,3)
 * 						.
 * 						.
 *  [1, 4, 12, 23, 26, 34, 67, 78, 222, 432, 456]
 */
/* Recursive merge sort */
void st_arry_recursive_merge_sort(stint a[],stint left,stint right)
{  
    stint i;  
    // 保证至少有两个元素  
    if(left < right)  			//当数组元素个数大于2时,需要继续向下划分(递归)
    {  
        i = (left+right)/2;  
        st_arry_recursive_merge_sort(a,left,i);  
        st_arry_recursive_merge_sort(a,i+1,right);  
        
        //合并已排序好的两部分(left,(right+left)/2) 和 ((right+left)/2+1,right)
        merge(a,left,right);  
    }  
}  


/*二路归并两个有序数组*/
void i_merge(stint *a,stint m,stint n,stint *b,stint i,stint j) 
{ 
	stint begin = m,h = m,k = i; 

	while(h <= n && k <= j) 
	{ 
		if(a[h] <= a[k]) 
		{ 
			b[begin++] = a[h++]; 
		}
		else
		{ 
			b[begin++] = a[k++]; 
		} 
	} 
	while(h <= n) 
	{ 
		b[begin++] = a[h++]; 
	} 
	while(k <= j) 
	{ 
		b[begin++] = a[k++]; 
	} 
} 

/* 将a[]中相邻长度为len的子序列两两归并到b[] */  
void i_mergeall(stint *a,stint *b,stint len,stint n) 

{ 
	stint i = 0; 
	while((i + 2*len) <= n) 
	{ 
		i_merge(a,i,i+len-1,b,i+len,i + 2*len -1); 			/* 两两归并 */ 
		i = i + 2*len; 
	} 
	if((i + len) > n) 										/* 若最后只剩下单个子序列 */  
	{ 
		while(i < n) 
		{ 
			b[i] = a[i]; 
			i++; 
		} 
	} 
	else 													/* 归并最后两个序列 */
	{
		i_merge(a,i,i+len-1,b,i+len,n-1); 
	}
} 
 
 
void st_arry_iteration_merge_sort(stint a[], stint n)
{
	stint len = 1; 
	stint *temp; 

	temp = (stint *)malloc(n*sizeof(stint)); 				//辅助空间,用以暂存已经排序的数组元素

	while(len < n) 
	{ 
		i_mergeall(a,temp,len,n); 
		len = len * 2; 										/* 子序列长度加倍 */  
		i_mergeall(temp,a,len,n); 
		len = len * 2; 										/* 子序列长度加倍 */  
	} 
	free(temp);
	temp = NULL ;
}



/************************************************ 
 * 测试从数组0号位开始的堆排序 
 *  
 * 与上面不同的知识点 
 * 1.0号是根元素，则左孩子为2i+1,右孩子为2(i+1); 
 * 2.孩子为i，则父亲为i-1/2 
 *  
 */  

/*** 
 * a            待排数组 
 * rootIndex    本次堆化的跟 
 * maxHeapIndex 本次堆化所达到的堆数组最大索引 
 */  
void maxHeapify2(stint a[], stint rootIndex,stint maxHeapIndex)  
{  
    stint lChild = rootIndex*2+1;  
    stint rChild = (rootIndex+1)*2;  
    stint largest = rootIndex;  
    if(lChild <= maxHeapIndex && a[lChild] > a[rootIndex])  
        largest = lChild;  
    if(rChild <= maxHeapIndex && a[rChild] > a[largest])  
        largest = rChild;  
    if(largest != rootIndex)  
    {  
        swap(&a[largest],&a[rootIndex]);  
        maxHeapify2(a,largest,maxHeapIndex);  
    }  
}  


/** 
 * a:       待排序数组 
 * len:     数组长度 
 */  
void st_arry_head_sort(stint a[],stint len)  
{  
    stint i=0;  
    stint maxHeapIndex = len-1;  
    //首先建堆  
    for(i=(maxHeapIndex-1)/2;i>=0;i--)  
    {  
        maxHeapify2(a,i,maxHeapIndex);  
    }  
    for(i=maxHeapIndex;i>=1;i--)  
    {  
        swap(&a[0],&a[i]);  
        // 交换之后，继续堆化时，堆数组最大索引要减1  
        maxHeapify2(a,0,i-1);  
    }  
}  

stint partition(stint* array,stint low,stint high)  
{  
    stint i=0;  
    stint pivot = array[low];  
    while(low < high)  
    {  
        while(low<high && array[high] >= pivot )  // 找比他小的
        {  
            high--;   
        }  
        if(low < high)  
        {  
            array[low++] = array[high];  
        }  
          
        while(low<high && array[low] <= pivot)  	// 找比他大
        {  
            low++;  
        }  
        if(low < high)  
        {  
            array[high--] = array[low];  
        }  
    }  
    array[low] = pivot;  
#if ST_DBG_
    printf("partition--- and pivot is %d \n",pivot);  
    for(;i<5;i++)  
    {  
        printf("%d ",array[i]);  
    }  
    printf("\n");  
#endif
    return low;  
}  

void st_arry_qsort(stint *array,stint low,stint high)
{
    stint i;  
    if(low < high)  
    {  
        i = partition(array,low,high);  
        st_arry_qsort(array, low, i-1);  
        st_arry_qsort(array, i+1, high);  
    }  
}


void st_arry_shell_sort(stint a[], stint len)
{
    stint step;  
    stint i,j;  
    stint temp;  
    for(step=len/2; step>0;step/=2) //用来控制步长,最后递减到1  
    {  
        // i从第step开始排列，应为插入排序的第一个元素  
        // 可以先不动，从第二个开始排序  
        for(i=step;i<len;i++)  
        {  
            temp = a[i];  
            for(j=i-step;(j>=0 && temp < a[j]);j-=step)  
            {  
                a[j+step] = a[j];  
            }  
            a[j+step] = temp; //将第一个位置填上  
        }  
        //showArray(a,len);     
    }  
}


/* 效率O（n?），适用于排序小的列表。 */
void st_arry_select_sort(stint array[], stint n)
{
	stint min_index;
	stint i, j ;
	for(i=0;i<n-1;i++)
	{
		min_index=i;
		for(j=i+1;j<n;j++)//每次扫描选择最小项
		if(array[j]<array[min_index])  
			min_index=j;

		if(min_index!=i)//找到最小项交换，即将这一项移到列表中的正确位置
		{
			stint temp;
			temp=array[i];  
			array[i]=array[min_index];  
			array[min_index]=temp;
		}
	}
}

/*
4 3 3 2
3 4 2 3
5 2 4 4
2 5 4 4
8 4 5 5
4 6 6 6
6 8 8 8
*/
/* 效率 O（n?）,适用于排序小列表。 相当与每次把最大的泡沉底*/
void st_arry_bubble_sort(stint array[], stint n)
{
	stint i,j,flag,temp;
	for(i = 0; i < n-1; i++)
	{
		flag = 1;
		for(j = 0; j < n-i-1; j++)
		{
			if(array[j] > array[j+1])
			{
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
				flag = 0;
			}
		}
		if(1 == flag)			// 是否退出循环的标志
			break;
	}
	return;
}

void st_arry_bubble_sort_1(stint array[], stint n)
{
	stint i,j,flag,temp ;

	flag = 1 ;
	i = 0 ;

	while((i<(n-1)) && (flag == 1))
	{
		flag = 0 ;
		for(j = n-1 ; j > i ; j--)
		{
			if(array[j] < array[j-1])
			{
				flag = 1 ;
				temp = array[j] ;
				array[j] = array[j-1] ;
				array[j-1] = temp ;
			}
		}
		i++ ;
	}
}


/* 最佳效率O（n）；最糟效率O（n?）与冒泡、选择相同，适用于排序小列表
 * 若列表基本有序，则插入排序比冒泡、选择更有效率。
 */
void st_arry_insert_sort(stint arr[], stint n)
{
	stint i ;

	for(i=1;i<n;i++)//循环从第二个数组元素开始，因为arr[0]作为最初已排序部分
	{
		stint temp=arr[i];//temp标记为未排序第一个元素
		stint j=i-1;
		while (j>=0 && arr[j]>temp)/*将temp与已排序元素从小到大比较，寻找temp应插入的位置*/
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=temp;
	}	
}

/* 由于插入排序的基本操作是在一个有序表中进行查找和插入，
 * 则这个查找操作可以利用折半查找来实现。但是折半插入排序
 * 仅减少了元素间的比较次数，而元素的移动次数不变，因此折
 * 半插入排序法的时间复杂度仍为O(n^2)。算法如下： 
 */
void st_arry_binary_insert_sort(stint array[], stint n)
{
	stint i,j,low,high,mid;
    for(i=1;i<=n;i++)
    {
        array[0] = array[i];                        
        low = 1;
        high = i-1;
        while(low <= high)                     //确定插入位置
        {
            mid = (low + high)/2;
            if(array[0] > array[mid])          //插入位置在高半区
                low = mid + 1;    
            else
                high = mid - 1;                  //插入位置在低半区
        }
        for(j = i-1;j >= high + 1;j--)           
            array[j+1] = array[j];                     //后移元素留出插入空位
            
        array[high+1] = array[0];                      //将元素插入
    }
}


void st_arry_radix_sort(stint array[], stint en)
{
	stint temp[10][10]={0} ;
	stint order[10]={0} ;
	stint i, j, k, n, lsd;
	k = 0;
	n = 1;

	printf("你输入的排序序列是: \n");
	for(i = 0; i < en; i++)
	{
		printf("%d ", array[i]);
	}
	putchar('\n');
	//按个位数分配到不同的桶中
	while (n <= 100)
	{
		stint r= 0;
		stint m= 1;

		for (i = 0; i < en; i++)
		{
			lsd = ((array[i]/n)%en);				//末尾有效数字
			temp[lsd][order[lsd]] = array[i];	//将data中的数据按其末尾放在不同的桶中
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
					array[k] = temp[i][j];		//将桶中的元素收集起来放在data[k]中
					printf("%d ", array[k]);
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
		printf("%d ", array[i]);
	}
	putchar('\n');

	return ;
	
}

#define M       	50        /* 比树的大小要大 */
//#define N       	10        /* 要排序的数字的个数 */
#define MIN_VALUE 	-10000    /* 整数中不可能达到的最小的数 */


/* 锦标赛排序也叫树选择排序，是一种按照锦标赛的思想进行选择的排序方法，
 * 该方法是在简单选择排序方法上的改进，我们知道简单选择排序时间大部分
 * 都浪费在值的比较上面，而锦标赛排序刚好用树保存了前面比较的结果，下
 * 一次比较时直接利用前面比较的结果大大减少比较的时间，从而降低了时间
 * 复杂度，由O(n^2)降到O(nlogn)，但是浪费了比较多的空间，“最大的值”也比较了多次。
 */
void st_arry_tournament_sort(stint arr[],stint n)
{
    stint *tree = NULL;    /* 树 */
    stint baseSize;    /* 当n是2的幂次时,baseSize是n */
            /* 当n不是时,baseSize是大于n的最小的2的幂次 */
            /* 就是构造成满二叉树的最下层的大小，即叶子数 */
    stint i;
    stint max;    /* 最大值 */
    stint maxIndex;    /* 最大数的下标 */
    stint treeSize;    /* 最终这棵树会达到的大小 */


	tree = (stint *)malloc(sizeof(stint)*M);
    baseSize = 1;
    while (baseSize < n)
    {
        baseSize *= 2;
    }
    
    /* 满二叉树的所有结点个数等于叶子数的2倍减一 */
    treeSize = baseSize * 2 - 1;
    
    /* 从数组的后面部分开始填充 */
    /* 不使用tree[0] */
    /* 这样可以保持与课本一致 */
    /* 从而直接利用课本中用数组存储二叉树的性质 */
    for (i = 0;i < n;i++)
    {
        tree[treeSize - i] = arr[i];
    }

    /* 用MIN_VALUE填充tree,直到一共有baseSize个 */
    for (;i < baseSize;i++)
    {
        tree[treeSize - i] = MIN_VALUE;
    }
    
    /* 构造一棵树 */
    for (i = treeSize;i > 1;i -= 2)
    {
        /* 根据树形选择排序的概念 */
        /* 以arr[i]和arr[i + 1]为子结点的数的根是arr[i]和arr[i + 1]中的较大者 */
        /* 再根据二叉树中父结点和子结点的位置关系有： */
        tree[i / 2] = (tree[i] > tree[i - 1] ? tree[i] : tree[i - 1]);
    }
    
    n = n - 1;    /* 此时的n表示当前tree[1]应该放到arr中的位置 */
    /* 不断把树中值为最大值的结点移走 */
    /* 直到n的值为-1 */
    /* 此时，所有要排序的结点都已经被选走了 */
    while (n != -1)
    {
        max     = tree[1];
        arr[n--] = max;
        maxIndex = treeSize;
        
        /* 在叶子上找到最大值对应的下标 */
        while (tree[maxIndex] != max)
        {
            maxIndex--;
        }
        tree[maxIndex] = MIN_VALUE;
        
        /* 沿着叶子上的结点到根的路径更新 */
        
        while (maxIndex > 1)    /* 当结点还有父结点时 */
        {
            if (maxIndex % 2 == 0)    /* 如果值为最大值的结点是左子结点 */
            {
                /* 用子结点中较大值代替父结点 */
                tree[maxIndex / 2] = (tree[maxIndex] > tree[maxIndex + 1] ? tree[maxIndex] : tree[maxIndex + 1]);
            }
            else        /* 如果不是左子结点 */
            {
                /* 用子结点中较大值代替父结点 */
                tree[maxIndex / 2] = (tree[maxIndex] > tree[maxIndex - 1] ? tree[maxIndex] : tree[maxIndex - 1]);
            }
            maxIndex /= 2;    /* 继续处理父结点 */
        }
    }
}




