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
 * �������� 
 * source:Դ���� 
 * dest:Ŀ������ 
 * len:Դ���鳤�� 
 * first:Ŀ��������ʼλ�� 
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

/* ��·�鲢����,�����������������ϲ���һ���������� */
void merge(stint a[],stint left,stint right)  
{  
    stint begin1 = left;  
    stint mid = (left+right)/2 ;  
    stint begin2 = mid+1;  
    stint k=0;  
    stint newArrayLen = right-left+1;  
    stint *b = (stint*)malloc(newArrayLen*sizeof(stint));  	//�����ռ�,�����ݴ��Ѿ����������Ԫ��
    
    while(begin1<=mid && begin2<=right)  
    {  
		//�Ƚ������±�begin1��begin2�������Ԫ��,ѡ�����С��Ԫ�ط��뵽�����ռ�b������,���ƶ��±굽��һλ��
        if(a[begin1]<=a[begin2])  
            b[k++] = a[begin1++];  
        else  
            b[k++] = a[begin2++];  
    }  
    while(begin1<=mid)  				//��ʣ��Ԫ�ؿ�����b����
        b[k++] = a[begin1++];  
    while(begin2<=right)  				//��ʣ��Ԫ�ؿ�����b����
        b[k++] = a[begin2++];  
    copyArray(b,a,newArrayLen,left);  	//������õ����п���������a��
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
    // ��֤����������Ԫ��  
    if(left < right)  			//������Ԫ�ظ�������2ʱ,��Ҫ�������»���(�ݹ�)
    {  
        i = (left+right)/2;  
        st_arry_recursive_merge_sort(a,left,i);  
        st_arry_recursive_merge_sort(a,i+1,right);  
        
        //�ϲ�������õ�������(left,(right+left)/2) �� ((right+left)/2+1,right)
        merge(a,left,right);  
    }  
}  


/*��·�鲢������������*/
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

/* ��a[]�����ڳ���Ϊlen�������������鲢��b[] */  
void i_mergeall(stint *a,stint *b,stint len,stint n) 

{ 
	stint i = 0; 
	while((i + 2*len) <= n) 
	{ 
		i_merge(a,i,i+len-1,b,i+len,i + 2*len -1); 			/* �����鲢 */ 
		i = i + 2*len; 
	} 
	if((i + len) > n) 										/* �����ֻʣ�µ��������� */  
	{ 
		while(i < n) 
		{ 
			b[i] = a[i]; 
			i++; 
		} 
	} 
	else 													/* �鲢����������� */
	{
		i_merge(a,i,i+len-1,b,i+len,n-1); 
	}
} 
 
 
void st_arry_iteration_merge_sort(stint a[], stint n)
{
	stint len = 1; 
	stint *temp; 

	temp = (stint *)malloc(n*sizeof(stint)); 				//�����ռ�,�����ݴ��Ѿ����������Ԫ��

	while(len < n) 
	{ 
		i_mergeall(a,temp,len,n); 
		len = len * 2; 										/* �����г��ȼӱ� */  
		i_mergeall(temp,a,len,n); 
		len = len * 2; 										/* �����г��ȼӱ� */  
	} 
	free(temp);
	temp = NULL ;
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
 * a:       ���������� 
 * len:     ���鳤�� 
 */  
void st_arry_head_sort(stint a[],stint len)  
{  
    stint i=0;  
    stint maxHeapIndex = len-1;  
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

stint partition(stint* array,stint low,stint high)  
{  
    stint i=0;  
    stint pivot = array[low];  
    while(low < high)  
    {  
        while(low<high && array[high] >= pivot )  // �ұ���С��
        {  
            high--;   
        }  
        if(low < high)  
        {  
            array[low++] = array[high];  
        }  
          
        while(low<high && array[low] <= pivot)  	// �ұ�����
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


/* Ч��O��n?��������������С���б� */
void st_arry_select_sort(stint array[], stint n)
{
	stint min_index;
	stint i, j ;
	for(i=0;i<n-1;i++)
	{
		min_index=i;
		for(j=i+1;j<n;j++)//ÿ��ɨ��ѡ����С��
		if(array[j]<array[min_index])  
			min_index=j;

		if(min_index!=i)//�ҵ���С�����������һ���Ƶ��б��е���ȷλ��
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
/* Ч�� O��n?��,����������С�б� �൱��ÿ�ΰ������ݳ���*/
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
		if(1 == flag)			// �Ƿ��˳�ѭ���ı�־
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


/* ���Ч��O��n��������Ч��O��n?����ð�ݡ�ѡ����ͬ������������С�б�
 * ���б������������������ð�ݡ�ѡ�����Ч�ʡ�
 */
void st_arry_insert_sort(stint arr[], stint n)
{
	stint i ;

	for(i=1;i<n;i++)//ѭ���ӵڶ�������Ԫ�ؿ�ʼ����Ϊarr[0]��Ϊ��������򲿷�
	{
		stint temp=arr[i];//temp���Ϊδ�����һ��Ԫ��
		stint j=i-1;
		while (j>=0 && arr[j]>temp)/*��temp��������Ԫ�ش�С����Ƚϣ�Ѱ��tempӦ�����λ��*/
		{
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=temp;
	}	
}

/* ���ڲ�������Ļ�����������һ��������н��в��ҺͲ��룬
 * ��������Ҳ������������۰������ʵ�֡������۰��������
 * ��������Ԫ�ؼ�ıȽϴ�������Ԫ�ص��ƶ��������䣬�����
 * ��������򷨵�ʱ�临�Ӷ���ΪO(n^2)���㷨���£� 
 */
void st_arry_binary_insert_sort(stint array[], stint n)
{
	stint i,j,low,high,mid;
    for(i=1;i<=n;i++)
    {
        array[0] = array[i];                        
        low = 1;
        high = i-1;
        while(low <= high)                     //ȷ������λ��
        {
            mid = (low + high)/2;
            if(array[0] > array[mid])          //����λ���ڸ߰���
                low = mid + 1;    
            else
                high = mid - 1;                  //����λ���ڵͰ���
        }
        for(j = i-1;j >= high + 1;j--)           
            array[j+1] = array[j];                     //����Ԫ�����������λ
            
        array[high+1] = array[0];                      //��Ԫ�ز���
    }
}


void st_arry_radix_sort(stint array[], stint en)
{
	stint temp[10][10]={0} ;
	stint order[10]={0} ;
	stint i, j, k, n, lsd;
	k = 0;
	n = 1;

	printf("�����������������: \n");
	for(i = 0; i < en; i++)
	{
		printf("%d ", array[i]);
	}
	putchar('\n');
	//����λ�����䵽��ͬ��Ͱ��
	while (n <= 100)
	{
		stint r= 0;
		stint m= 1;

		for (i = 0; i < en; i++)
		{
			lsd = ((array[i]/n)%en);				//ĩβ��Ч����
			temp[lsd][order[lsd]] = array[i];	//��data�е����ݰ���ĩβ���ڲ�ͬ��Ͱ��
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
					array[k] = temp[i][j];		//��Ͱ�е�Ԫ���ռ���������data[k]��
					printf("%d ", array[k]);
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
		printf("%d ", array[i]);
	}
	putchar('\n');

	return ;
	
}

#define M       	50        /* �����Ĵ�СҪ�� */
//#define N       	10        /* Ҫ��������ֵĸ��� */
#define MIN_VALUE 	-10000    /* �����в����ܴﵽ����С���� */


/* ����������Ҳ����ѡ��������һ�ְ��ս�������˼�����ѡ������򷽷���
 * �÷������ڼ�ѡ�����򷽷��ϵĸĽ�������֪����ѡ������ʱ��󲿷�
 * ���˷���ֵ�ıȽ����棬������������պ�����������ǰ��ȽϵĽ������
 * һ�αȽ�ʱֱ������ǰ��ȽϵĽ�������ٱȽϵ�ʱ�䣬�Ӷ�������ʱ��
 * ���Ӷȣ���O(n^2)����O(nlogn)�������˷��˱Ƚ϶�Ŀռ䣬������ֵ��Ҳ�Ƚ��˶�Ρ�
 */
void st_arry_tournament_sort(stint arr[],stint n)
{
    stint *tree = NULL;    /* �� */
    stint baseSize;    /* ��n��2���ݴ�ʱ,baseSize��n */
            /* ��n����ʱ,baseSize�Ǵ���n����С��2���ݴ� */
            /* ���ǹ�����������������²�Ĵ�С����Ҷ���� */
    stint i;
    stint max;    /* ���ֵ */
    stint maxIndex;    /* ��������±� */
    stint treeSize;    /* �����������ﵽ�Ĵ�С */


	tree = (stint *)malloc(sizeof(stint)*M);
    baseSize = 1;
    while (baseSize < n)
    {
        baseSize *= 2;
    }
    
    /* �������������н���������Ҷ������2����һ */
    treeSize = baseSize * 2 - 1;
    
    /* ������ĺ��沿�ֿ�ʼ��� */
    /* ��ʹ��tree[0] */
    /* �������Ա�����α�һ�� */
    /* �Ӷ�ֱ�����ÿα���������洢������������ */
    for (i = 0;i < n;i++)
    {
        tree[treeSize - i] = arr[i];
    }

    /* ��MIN_VALUE���tree,ֱ��һ����baseSize�� */
    for (;i < baseSize;i++)
    {
        tree[treeSize - i] = MIN_VALUE;
    }
    
    /* ����һ���� */
    for (i = treeSize;i > 1;i -= 2)
    {
        /* ��������ѡ������ĸ��� */
        /* ��arr[i]��arr[i + 1]Ϊ�ӽ������ĸ���arr[i]��arr[i + 1]�еĽϴ��� */
        /* �ٸ��ݶ������и������ӽ���λ�ù�ϵ�У� */
        tree[i / 2] = (tree[i] > tree[i - 1] ? tree[i] : tree[i - 1]);
    }
    
    n = n - 1;    /* ��ʱ��n��ʾ��ǰtree[1]Ӧ�÷ŵ�arr�е�λ�� */
    /* ���ϰ�����ֵΪ���ֵ�Ľ������ */
    /* ֱ��n��ֵΪ-1 */
    /* ��ʱ������Ҫ����Ľ�㶼�Ѿ���ѡ���� */
    while (n != -1)
    {
        max     = tree[1];
        arr[n--] = max;
        maxIndex = treeSize;
        
        /* ��Ҷ�����ҵ����ֵ��Ӧ���±� */
        while (tree[maxIndex] != max)
        {
            maxIndex--;
        }
        tree[maxIndex] = MIN_VALUE;
        
        /* ����Ҷ���ϵĽ�㵽����·������ */
        
        while (maxIndex > 1)    /* ����㻹�и����ʱ */
        {
            if (maxIndex % 2 == 0)    /* ���ֵΪ���ֵ�Ľ�������ӽ�� */
            {
                /* ���ӽ���нϴ�ֵ���游��� */
                tree[maxIndex / 2] = (tree[maxIndex] > tree[maxIndex + 1] ? tree[maxIndex] : tree[maxIndex + 1]);
            }
            else        /* ����������ӽ�� */
            {
                /* ���ӽ���нϴ�ֵ���游��� */
                tree[maxIndex / 2] = (tree[maxIndex] > tree[maxIndex - 1] ? tree[maxIndex] : tree[maxIndex - 1]);
            }
            maxIndex /= 2;    /* ����������� */
        }
    }
}




