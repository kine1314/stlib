#include <stdio.h>
#include <math.h>

//#define M       50        /* 比树的大小要大 */
#define N       10        /* 要排序的数字的个数 */
#define MIN_VALUE -10000    /* 整数中不可能达到的最小的数 */


void tree_select_sort(int arr[],int n, int m)
{
    int *tree = NULL ;    /* 树 */
    int baseSize;    /* 当n是2的幂次时,baseSize是n */
            /* 当n不是时,baseSize是大于n的最小的2的幂次 */
            /* 就是构造成满二叉树的最下层的大小，即叶子数 */
	//int M ;	/* 比树的大小要大 */
    int i;
    int max;    /* 最大值 */
     int maxIndex;    /* 最大数的下标 */
    int treeSize;    /* 最终这棵树会达到的大小 */
    

	tree = (int *)malloc(sizeof(int)*m);
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

int main(void)
{
    int i;
    int arr[N];
    
    printf("请输入十个数：\n");
    for (i = 0;i < N;i++)
    {
        scanf("%d",&arr[i]);
    }
    
    printf("您输入的数组：\n");
    for (i = 0;i < N;i++)
    {
        printf("%5d",arr[i]);
    }
    printf("\n");
    
    tree_select_sort(arr,N, 50);
    
    printf("已经排序的数组：\n");
    for (i = 0;i < N;i++)
    {
        printf("%5d",arr[i]);
    }
    printf("\n");
    return 0;
}
