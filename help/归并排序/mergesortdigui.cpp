/*
* =====================================================================================
*
*       Filename:  MergeSort.cpp
*
*    Description:  MergeSort,归并排序,用递归实现
*
*        Version:  1.0
*        Created:  2010年08月31日 14时47分14秒
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  glq2000 (), glq2000@126.com
*        Company:  HUE ISRC
*
* =====================================================================================
*/
#include <iostream>
using namespace std;
#define N 11
int array[N] = { 4, 67, 456, 23, 1, 78, 26, 222, 34, 432, 12 }; //待排序数组
int other[N]; //辅助空间,用以暂存已经排序的数组元素

void Swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}


/* array 待排序数组
* begin 数组开始的下标
*   end 数组最后一个元素的下标
*/
void MergeSort(int *array, int begin, int end)
{
    if(end-begin+1 > 2) //当数组元素个数大于2时,需要继续向下划分(递归)
    {
        MergeSort(array, begin, (end+begin)/2);
        MergeSort(array, (end+begin)/2+1, end);

        //合并已排序好的两部分(begin,(end+begin)/2) 和 ((end+bigin)/2+1,end)
        int i = begin, j = (end+begin)/2+1, k=begin;
        while(i<=(begin+end)/2 && j<=end)
        {//比较两个下标i和j所代表的元素,选择相对小的元素放入到辅助空间other数组中,并移动下标到下一位置
            if(array[i] < array[j])
                other[k++] = array[i++];
            else
                other[k++] = array[j++];
        }
        while(i <= (begin+end)/2)   //将剩余元素拷贝至other数组
            other[k++] = array[i++];
        while(j <= end)             //将剩余元素拷贝至other数组
            other[k++] = array[j++];
        for(k=begin; k<=end; ++k)   //将排序好的序列拷贝回数组array中
            array[k] = other[k];
    }
    else //当数组元素个数为2或1时,直接排序
        if(array[end] < array[begin])  Swap(array[end], array[begin]);
}


void Output(int *array, int n)
{
    for(int i=0; i<n; ++i)
        cout<<array[i]<<" ";
    cout<<endl;
}


int main()
{
    MergeSort(array, 0, N-1);
    Output(array, N);
    return 0;
}