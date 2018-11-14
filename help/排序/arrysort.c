#include "stdio.h"

static int arr[8] = {2, 4, 3, 7, 2, 4, 9, 3} ;

int n = 8 ;


static void swap(int **a,int **b)  
{  
    int temp; 
    temp=*a;  
    *a=*b;  
    *b=temp;  
}  

void BubbleSortArray()
{
	int i, j ;
	for(i=1;i<n;i++)
	{
		for(j=0;i<n-i;j++)
		{
			if(arr[j]>arr[j+1])//�ȽϽ�������Ԫ��
			{
				int temp;
				temp=arr[i]; 
				arr[j]=arr[j+1]; 
				arr[j+1]=temp;
			}
		}
	}
}

void bubble_sort(int array[],int n)
{
	int i,j,flag,temp;
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
		if(1 == flag)
			break;
		//printf("%d ",i);
	}
	return;
}


void SelectSortArray(int array[],int n)
{
	int min_index;
	int i, j ;
	for(i=0;i<n-1;i++)
	{
		min_index=i;
		for(j=i+1;j<n;j++)//ÿ��ɨ��ѡ����С��
		if(array[j]<array[min_index])  
			min_index=j;

		if(min_index!=i)//�ҵ���С�����������һ���Ƶ��б��е���ȷλ��
		{
			int temp;
			temp=array[i];  
			array[i]=array[min_index];  
			array[min_index]=temp;
		}
	}
}


void shellSort(int a[],int len)  
{  
    int step;  
    int i,j;  
    int temp;  
    for(step=len/2; step>0;step/=2) //�������Ʋ���,���ݼ���1  
    {  
        // i�ӵ�step��ʼ���У�ӦΪ��������ĵ�һ��Ԫ��  
        // �����Ȳ������ӵڶ�����ʼ����  
        for(i=step;i<len;i++)  
        {  
            temp = a[i];  
            for(j=i-step;(j>=0 && temp < a[j]);j-=step)  
            {  
                a[j+step] = a[j];  
            }  
            a[j+step] = temp; //����һ��λ������  
        }  
        //showArray(a,len);     
    }  
}  



int partition(int* array,int low,int high)  
{  
    int i=0;  
    int pivot = array[low];  
    while(low < high)  
    {  
        while(low<high && array[high] >= pivot )  
        {  
            high--;   
        }  
        if(low < high)  
        {  
            array[low++] = array[high];  
        }  
          
        while(low<high && array[low] <= pivot)  
        {  
            low++;  
        }  
        if(low < high)  
        {  
            array[high--] = array[low];  
        }  
    }  
    array[low] = pivot;  
    printf("partition--- and pivot is %d \n",pivot);  
    for(;i<5;i++)  
    {  
        printf("%d ",array[i]);  
    }  
    printf("\n");  
    return low;  
}  
   
void qsort(int *array,int low,int high)  
{  
    int i;  
    if(low < high)  
    {  
        i = partition(array,low,high);  
        qsort(array, low, i-1);  
        qsort(array, i+1, high);  
    }  
}  


/************************************************ 
 * ���Դ�����0��λ��ʼ�Ķ����� 
 *  
 * �����治ͬ��֪ʶ�� 
 * 1.0���Ǹ�Ԫ�أ�������Ϊ2i+1,�Һ���Ϊ2(i+1); 
 * 2.����Ϊi������Ϊi-1/2 
 *  
 */  

/*** 
 * a            �������� 
 * rootIndex    ���ζѻ��ĸ� 
 * maxHeapIndex ���ζѻ����ﵽ�Ķ������������ 
 */  
void maxHeapify2(int a[], int rootIndex,int maxHeapIndex)  
{  
    int lChild = rootIndex*2+1;  
    int rChild = (rootIndex+1)*2;  
    int largest = rootIndex;  
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
 * a:       ���������� 
 * len:     ���鳤�� 
 */  
void heapSort2(int a[],int len)  
{  
    int i=0;  
    int maxHeapIndex = len-1;  
    //���Ƚ���  
    for(i=(maxHeapIndex-1)/2;i>=0;i--)  
    {  
        maxHeapify2(a,i,maxHeapIndex);  
    }  
    for(i=maxHeapIndex;i>=1;i--)  
    {  
        swap(&a[0],&a[i]);  
        // ����֮�󣬼����ѻ�ʱ���������������Ҫ��1  
        maxHeapify2(a,0,i-1);  
    }  
}  


/** 
 * �������� 
 * source:Դ���� 
 * dest:Ŀ������ 
 * len:Դ���鳤�� 
 * first:Ŀ��������ʼλ�� 
 * 
 */  
void copyArray(int source[], int dest[],int len,int first)  
{  
    int i;  
    int j=first;  
    for(i=0;i<len;i++)  
    {  
        dest[j] = source[i];  
        j++;  
    }  
          
}  
void mergeSort(int a[],int left,int right)  
{  
    int i;  
    // ��֤����������Ԫ��  
    if(left < right)  
    {  
        i = (left+right)/2;  
        mergeSort(a,left,i);  
        mergeSort(a,i+1,right);  
        merge(a,left,right);  
    }  
}  
  
void merge(int a[],int left,int right)  
{  
    int begin1 = left;  
    int mid = (left+right)/2 ;  
    int begin2 = mid+1;  
    int k=0;  
    int newArrayLen = right-left+1;  
    int *b = (int*)malloc(newArrayLen*sizeof(int));  
    while(begin1<=mid && begin2<=right)  
    {  
        if(a[begin1]<=a[begin2])  
            b[k++] = a[begin1++];  
        else  
            b[k++] = a[begin2++];  
    }  
    while(begin1<=mid)  
        b[k++] = a[begin1++];  
    while(begin2<=right)  
        b[k++] = a[begin2++];  
    copyArray(b,a,newArrayLen,left);  
    free(b);  
}  
  


void InsertSortArray(int array[],int n)
{
	int i ;

	for(i=1;i<n;i++)//ѭ���ӵڶ�������Ԫ�ؿ�ʼ����Ϊarr[0]��Ϊ��������򲿷�
	{
		int temp=arr[i];//temp���Ϊδ�����һ��Ԫ��
		int j=i-1;
		while (j>=0 && arr[j]>temp)/*��temp��������Ԫ�ش�С����Ƚϣ�Ѱ��tempӦ�����λ��*/
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=temp;
	}
}





void dump_arry(int array[],int n)
{
	int i ;

	for(i = 0 ; i < n ; i++)
	{
		printf("%d ", array[i]);
	}
}

int main(void)
{
	
	//BubbleSortArray();
	//bubble_sort(arr, 8);
	//SelectSortArray(arr, 8);
	//InsertSortArray(arr, 8);
	//shellSort(arr, 8);
	//qsort(arr, 0, 7) ;
	//heapSort2(arr,8);  
	//mergeSort(arr,0,8-1);     
	InsertSortArray(arr,8) ;

	dump_arry(arr, 8);
	printf("\n");
}


