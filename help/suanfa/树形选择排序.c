#include <stdio.h>
#include <math.h>

//#define M       50        /* �����Ĵ�СҪ�� */
#define N       10        /* Ҫ��������ֵĸ��� */
#define MIN_VALUE -10000    /* �����в����ܴﵽ����С���� */


void tree_select_sort(int arr[],int n, int m)
{
    int *tree = NULL ;    /* �� */
    int baseSize;    /* ��n��2���ݴ�ʱ,baseSize��n */
            /* ��n����ʱ,baseSize�Ǵ���n����С��2���ݴ� */
            /* ���ǹ�����������������²�Ĵ�С����Ҷ���� */
	//int M ;	/* �����Ĵ�СҪ�� */
    int i;
    int max;    /* ���ֵ */
     int maxIndex;    /* ��������±� */
    int treeSize;    /* �����������ﵽ�Ĵ�С */
    

	tree = (int *)malloc(sizeof(int)*m);
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

int main(void)
{
    int i;
    int arr[N];
    
    printf("������ʮ������\n");
    for (i = 0;i < N;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    printf("����������飺\n");
    for (i = 0;i < N;i++)
    {
        printf("%5d",arr[i]);
    }
    printf("\n");
    
    tree_select_sort(arr,N, 50);
    
    printf("�Ѿ���������飺\n");
    for (i = 0;i < N;i++)
    {
        printf("%5d",arr[i]);
    }
    printf("\n");
    return 0;
}
