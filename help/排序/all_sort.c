/*内部排序综合(注:没有嵌入基数排序进来,基数排序一般很少用的,如果有朋友需要,请看上一篇"基数排序,且供参考!")*/
# include <stdio.h>
//# include <curses.h>
# include <stdlib.h>
# include <time.h>
# define maxsize 100
typedef int KeyType;                         //关键字类型
typedef struct 
{ 
    KeyType key;                                //关键字域
}LineList;                                           //线性表元素类型
KeyType n,array[maxsize+1];
LineList r[maxsize+1];                        //结构体(整型)数组
void Time()                                        //获得系统时间
{
    time_t t;
    struct tm *tp;
    static char *week[]={"一","二","三","四","五","六","日"};
    t=time(NULL);
    tp=localtime(&t);
    printf("\t　          ─────────────────────\n");
    printf("\t\t       现在是:%d年%d月%d日",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday);   
    printf(" %d:%d:%d ",tp->tm_hour,tp->tm_min,tp->tm_sec);
    printf("星期%s\n",week[(tp->tm_wday)-1]);
    printf("\t　          ─────────────────────\n");
}
void sInserSort()                            //直接插入排序方法块
{
    int i,j;
    for(i=2;i<=n;i++)                        //以0为开始起点
    { 
        r[0]=r[i];
        j=i-1;                               //从前一个数开始比较
        while(r[j].key>r[0].key)             //元素后移,以便腾出一个位置插入tmp
        { 
            r[j+1]=r[j];
            j--;
        }
        r[j+1]=r[0];                         //在j+1位置处插入tmp
    }
}
void bInserSort()                            //折半插入排序方法块
{
    int i,j,low,high,mid;
    for(i=1;i<=n;i++)
    {
        r[0]=r[i];                        
        low=1;
        high=i-1;
        while(low<=high)                     //确定插入位置
        {
            mid=(low+high)/2;
            if(r[0].key>r[mid].key)          //插入位置在高半区
                low=mid+1;    
            else
                high=mid-1;                  //插入位置在低半区
        }
        for(j=i-1;j>=high+1;j--)           
            r[j+1]=r[j];                     //后移元素留出插入空位
        r[high+1]=r[0];                      //将元素插入
    }
} 
void slSort()                                //希尔排序方法块               
{
    int i,j,k;
    k=n/2;                                   //k值代表增量值
    while(k>=1)                              //当增量k值变化到0，结束循环……
    {
        for(i=k+1;i<=n;i++)
        {
            r[0].key=r[i].key;
            j=i-k;
            while((r[j].key>r[0].key)&&(j>=0))
            {
                r[j+k].key=r[j].key;
                j=j-k;
            }
            r[j+k]=r[0];
        }
        k=k/2;
    }
} 
int partition(int low,int high) 
{
    int tmp=array[low];
    while(low<high) 
    {
        while(low<high&&array[high]>=tmp) --high;
        array[low]=array[high];
        while(low<high&&array[low]<=tmp) ++low;
        array[high]=array[low];
    }
    array[low]=tmp;
    return low;
}
void qSort(int low,int high)                 //快速排序方法块    
{
    if(low<high) 
    {
        int pivotloc=partition(low,high);
        qSort(low,pivotloc-1);
        qSort(pivotloc+1,high);
    }    
}
void merge(int low,int m,int high)
{
    int i=low,j=m+1,p=0;
    LineList *R1;
    R1=(LineList *)malloc((n-low+1)*sizeof(LineList));
    if(!R1)
        printf("Insufficient memory available!");
    while(i<=m&&j<=high)
        R1[p++]=(r[i].key<=r[j].key?r[i++]:r[j++]);
    while(i<=m)
        R1[p++]=r[i++];
    while(j<=high)
        R1[p++]=r[j++];
    for(p=0,i=low;i<=high;p++,i++)
        r[i]=R1[p];
}
void mergePass(int length)
{
    int i;
    for(i=1;i+2*length-1<=n;i=i+2*length)
        merge(i,i+length-1,i+2*length-1);
    if(i+length-1<n)
        merge(i,i+length-1,n);
}
void merSort()                               //二路归并排序方法块
{
    int length;
    for(length=1;length<n;length*=2)
        mergePass(length);
}
beSort()                                     //冒泡排序方法块     
{
    int i,j,temp;
    for(i=1;i<=n-1;i++)
        for(j=1;j<=n-i;j++)
            if(array[j]>array[j+1])
            {temp=array[j];array[j]=array[j+1];array[j+1]=temp;}
}
snSort()                                     //选择排序方法块
{
    int i,j,k,t;
    for(i=1;i<n;i++)
    {
        k=i;
        for(j=i+1;j<=n;j++)
        {
            if(array[j]<array[k])
                k=j;
        }
        t=array[k];array[k]=array[i];array[i]=t;
    }
}
filter(int fj,int c)                         //筛选算法
{
    int i,j,x;
    i=fj;
    j=2*i;
    x=array[i];
    while(j<=c)
    {
        if(j<c&&array[j]>array[j+1]) j++; //将其左孩子和右孩进行比较，得到最大者的下标.
        if(x>array[j])                       //选出最大子节点后和父节点进行比较.
        {
            array[i]=array[j];
            i=j;
            j=2*i;
        }
        else
            j=c+1;                            //若其子节点都比他小就跳出循环.
    }
    array[i]=x;               
}
hSort()                                      //堆排序方法块
{
    int i,j,temp,count=n;
    printf("经过排序后的结果为:\n");
    for(i=1;i<=n;i++)
    {
        for(j=count/2;j>=1;j--)
            filter(j, count);                 //count要自减，需传参
        printf("%d ",array[1]);
        temp=array[1];
        array[1]=array[count];
        array[count]=temp;
        count--;
    }
}
arand()                                      //随机生成数字
{
    int i;
    n=rand()%14;                             //长度<15
    for(i=0;i<n;i++)
    {
        array[i]=rand()%100;                 //为0-100的随机数
    }
    printf("【共%d个数据】如下:\n",n);
}
/*******************************函数调用*************************************/
straightInsertionSort()                      //直接插入排序
{
    int i;
    char c;
loop:printf("\n\n请输入你想要操作数的个数:");
     while(scanf("%d", &n)!=1)                     //检测是否为正确输入数
     {
         while ((c=getchar())!='\n');
         printf("\n\n\t\t\t【×】Error:输入有误,请重新选择!");
         getchar();
         system("cls");
         goto loop;
     }
     printf("请输入这%d个数(回车键结束):\n",n);
     for(i=1;i<=n;i++)
     {
         scanf("%d",&r[i]);
     }
     printf("排序前:\n");
     for(i=1;i<=n;i++)
         printf("%-4d",r[i]);
     printf("\n");
     sInserSort();
     printf("排序后:\n");
     for(i=1;i<=n;i++)
         printf("%-4d",r[i]);
     printf("\n");
}
binaryInsertionSort()                       //折半插入排序
{
    int i;
    printf("\n\n请输入你想要操作数的个数:");
    scanf("%d",&n);
    printf("请输入这%d个数(回车键结束):\n",n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&r[i]);
    }
    printf("排序前:\n");
    for(i=1;i<=n;i++)
        printf("%-4d",r[i]);
    printf("\n");
    bInserSort();
    printf("排序后:\n");
    for(i=1;i<=n;i++)
        printf("%-4d",r[i]);
    printf("\n");
}
shellSort()                                 //希尔排序
{
    int i;
    printf("\n\n请输入你想要操作数的个数:");
    scanf("%d",&n);
    printf("请输入这%d个数(回车键结束):\n",n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&r[i]);
    }
    printf("排序前:\n");
    for(i=1;i<=n;i++)
        printf("%-4d",r[i]);
    printf("\n");
    slSort();
    printf("排序后:\n");
    for(i=1;i<=n;i++)
        printf("%-4d",r[i]);
    printf("\n");
}
quickSort()                                 //快速排序
{
    int i;
    printf("\n\n请输入你想要操作数的个数:");
    scanf("%d",&n);
    printf("请输入这%d个数(回车键结束):\n",n);
    for(i=1;i<=n;i++)
        scanf("%d",&array[i]);
    qSort(1,n);
    printf("排序后:\n");
    for(i=1;i<=n;i++)
        printf("%-4d",array[i]);
    printf("\n");
}
mergeSort()                                 //归并排序
{
    int i;
    printf("\n\n请输入你想要操作数的个数:");
    scanf("%d",&n);
    printf("请输入这%d个数(回车键结束):\n",n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&r[i]);
    }
    printf("排序前:\n");
    for(i=1;i<=n;i++)
        printf("%-4d",r[i]);
    printf("\n");
    merSort();
    printf("排序后:\n");
    for(i=1;i<=n;i++)
        printf("%-4d",r[i]);
    printf("\n");
}
bubbleSort()                                //冒泡排序
{
    int i;
    printf("\n\n请输入你想要操作数的个数:");
    scanf("%d",&n);
    printf("请输入这%d个数(回车键结束):\n",n);
    for(i=1;i<=n;i++)
        scanf("%d",&array[i]);
    beSort();
    printf("排序后:\n");
    for(i=1;i<=n;i++)
        printf("%-4d",array[i]);
    printf("\n");
}
selectionSort()                             //选择排序
{
    int i;
    printf("\n\n请输入你想要操作数的个数:");
    scanf("%d",&n);
    printf("请输入这%d个数(回车键结束):\n",n);
    for(i=1;i<=n;i++)
        scanf("%d",&array[i]);
    snSort();
    printf("排序后:\n");
    for(i=1;i<=n;i++)
        printf("%-4d",array[i]);
    printf("\n");
}
heapSort()                                  //堆排序
{
    /*
       int i;
       printf("\n\n请输入你想要操作数的个数:");
       scanf("%d",&n);
       printf("请输入这%d个数(回车键结束):\n",n);
       for(i=1;i<=n;i++)
       scanf("%d",&array[i]);*/
    hSort();                                //这样写调用了randrom()初始化数据
}
randrom()                                   //随机生成数
{
    int i;
    arand();
    for(i=1;i<=n;i++)
        printf("%-4d",array[i]);
    printf("\n");
}
menu()
{
    int num;
    char c;
    printf("\n\t\t\t         1.     直接插入排序\n");
    printf("\t\t\t         2.     折半插入排序\n");
    printf("\t\t\t         3.     希尔排序\n");
    printf("\t\t\t         4.     快速排序\n");
    printf("\t\t\t         5.     归并排序\n");
    printf("\t\t\t         6.     冒泡排序\n");
    printf("\t\t\t         7.     选择排序\n");
    printf("\t\t\t         8.     堆排序(调用了randrom()初始化数据)\n");
    printf("\t\t\t         9.     随机生成数\n");
    printf("\t\t\t         10. 注销\n");
    printf("\t\t     ----------------------------------------");
    printf("\n\t\t       请选择操作的对象<1,2>...\n");
    printf("\t\t       请输入:");
    while(scanf("%d", &num)!=1)                     //检测是否为正确输入数
    {
        while ((c=getchar())!='\n');
        printf("\n\n\t\t\t【×】Error:输入有误,请重新选择!");
        getchar();
        system("cls");
        menu();
    }
    if(num==1)
    {
        straightInsertionSort();
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        menu();
    }
    else if(num==2)
    {
        binaryInsertionSort();
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        menu();
    }
    else if(num==3)
    {
        shellSort();
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        menu();
    }
    else if(num==4)
    {
        quickSort();
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        menu();
    }
    else if(num==5)
    {
        mergeSort();
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        menu();
    }
    else if(num==6)
    {
        bubbleSort();
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        menu();
    }
    else if(num==7)
    {
        selectionSort();
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        menu();
    }
    else if(num==8)
    {
        heapSort();
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        menu();
    }
    else if(num==9)
    {
        randrom();
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        menu();
    }
    else if(num==10)
    {
        printf("\n\n\n\n\n\t\t\t       \3欢迎使用本次操作!\3");
        printf("\n\n\t\t\t        请输入任意键继续...");
        getchar();
        system("cls");
        exit(0);
    }
}
main()
{
    Time();
    menu();
}


