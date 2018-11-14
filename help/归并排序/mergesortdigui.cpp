/*
* =====================================================================================
*
*       Filename:  MergeSort.cpp
*
*    Description:  MergeSort,�鲢����,�õݹ�ʵ��
*
*        Version:  1.0
*        Created:  2010��08��31�� 14ʱ47��14��
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
int array[N] = { 4, 67, 456, 23, 1, 78, 26, 222, 34, 432, 12 }; //����������
int other[N]; //�����ռ�,�����ݴ��Ѿ����������Ԫ��

void Swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}


/* array ����������
* begin ���鿪ʼ���±�
*   end �������һ��Ԫ�ص��±�
*/
void MergeSort(int *array, int begin, int end)
{
    if(end-begin+1 > 2) //������Ԫ�ظ�������2ʱ,��Ҫ�������»���(�ݹ�)
    {
        MergeSort(array, begin, (end+begin)/2);
        MergeSort(array, (end+begin)/2+1, end);

        //�ϲ�������õ�������(begin,(end+begin)/2) �� ((end+bigin)/2+1,end)
        int i = begin, j = (end+begin)/2+1, k=begin;
        while(i<=(begin+end)/2 && j<=end)
        {//�Ƚ������±�i��j�������Ԫ��,ѡ�����С��Ԫ�ط��뵽�����ռ�other������,���ƶ��±굽��һλ��
            if(array[i] < array[j])
                other[k++] = array[i++];
            else
                other[k++] = array[j++];
        }
        while(i <= (begin+end)/2)   //��ʣ��Ԫ�ؿ�����other����
            other[k++] = array[i++];
        while(j <= end)             //��ʣ��Ԫ�ؿ�����other����
            other[k++] = array[j++];
        for(k=begin; k<=end; ++k)   //������õ����п���������array��
            array[k] = other[k];
    }
    else //������Ԫ�ظ���Ϊ2��1ʱ,ֱ������
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