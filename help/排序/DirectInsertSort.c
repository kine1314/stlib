//#include <curses.h>
#include <string.h>
//#include <time.h>
#include <stdlib.h>

#define MAXSIZE         20
#define MAXLENGTH       100

typedef struct _SqList
{
    int data[MAXSIZE+1] ;
    int length ;
}SqList ;

void DInsertSort(SqList *L)
{
    int i, j ;

    for(i = 2 ; i <= L->length ; ++i)
    {
        if(L->data[i] < L->data[i-1])                           // 如果待选项比有序区域的最后一个小才记录哨兵;
        {
            L->data[0] = L->data[i] ;                           // 记录哨兵
            for(j = i-1 ; L->data[0] < L->data[j] ; --j)        // 找到适当的插入位置,其余的往后推移!
            {
                L->data[j+1] = L->data[j] ;                     // 推移
            }
            L->data[j] = L->data[0] ;                           // 插入到适当的位置
        }
    }
}

void BInsertSort(SqList *L)
{
    int i, j, low, high, mid ;

    for(i = 2 ; i <= L->length ; ++i)
    {
        if(L->data[i] < L->data[i-1])
        {
            L->data[0] = L->data[i] ;
            low = 1 ;
            high = i - 1 ;
            while(low <= high)                  // 当low大于high的时候,
            {
                mid = (low + high)/2 ;
                if(L->data[0] > L->data[mid])
                    low = mid + 1 ;
                else
                    high = mid - 1 ;
            }
            for(j=i-1 ; j >= high+1 ; --j)
            {
                L->data[j+1] = L->data[j] ;     // 将high往后的所有data后移
            }
            L->data[high+1] = L->data[0] ;      // high+1 is the insert value
        }
    }
    
}

void SInsertSort(SqList *L)
{
    int i,j,k;

    k = (L->length)/2;                                   //k值代表增量值
    while(k>=1)                              //当增量k值变化到0，结束循环……
    {
        for(i = k+1 ; i <= L->length ; i++)
        {
            L->data[0] = L->data[i] ;
            j=i-k;
            while((L->data[j] > L->data[0]) && (j >= 0))
            {
                L->data[j+k] = L->data[j] ;
                j=j-k;
            }
            L->data[j+k] = L->data[0] ;
        }
        k=k/2;
    } 
}

void dump_order(SqList *L, int start)
{
    int i ;

    for(i = start ; i <= L->length ; ++i)
    {
        printf("%d ", L->data[i]);
    }
}

int DirectInsertSort(void)
{
    int i ;
    SqList L ;

    memset(&L, 0, sizeof(SqList));
    printf("DirectInsertSort\n");
    printf("===================\n");
    printf("Please input the length of SqList (eg, 5): ");
    scanf("%d", &L.length);

    for(i=1;i<=L.length;++i) 
    {
        printf("Please input the %d th integer (eg, 58): ", i);
        scanf("%d", &L.data[i]);
    }

    
    printf("\nThe disordered is :\t");
    dump_order(&L, 1);

    DInsertSort(&L);

    printf("\nThe ordered is :\t");
    dump_order(&L, 1);
    printf("\n__~0~__\n");
    getchar();
}

void BinaryInsertSort(void)
{
    int i ;
    SqList L ;

    memset(&L, 0, sizeof(SqList));
    printf("BinaryInsertSorty\n");
    printf("===================\n");
    printf("Please input the length of SqList (eg, 5): ");
    scanf("%d", &L.length);

    for(i=1;i<=L.length;++i) 
    {
        printf("Please input the %d th integer (eg, 58): ", i);
        scanf("%d", &L.data[i]);
    }
    
    printf("\nThe disordered is :\t");
    dump_order(&L, 1);

    BInsertSort(&L);

    printf("\nThe ordered is :\t");
    dump_order(&L, 1);
    printf("\n__~0~__\n");
    getchar();
}

void ShellInsertSort(void)
{
    int i ;
    SqList L ;

    memset(&L, 0, sizeof(SqList));
    printf("BinaryInsertSorty\n");
    printf("===================\n");
    printf("Please input the length of SqList (eg, 5): ");
    scanf("%d", &L.length);

    for(i=1;i<=L.length;++i) 
    {
        printf("Please input the %d th integer (eg, 58): ", i);
        scanf("%d", &L.data[i]);
    }
    
    printf("\nThe disordered is :\t");
    dump_order(&L, 1);

    SInsertSort(&L);

    printf("\nThe ordered is :\t");
    dump_order(&L, 1);
    printf("\n__~0~__\n");
    getchar();
}

void QuitSort(void)
{

}

/*
void Time(void)
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
*/

void Menu(void)
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
        system("clear");
        Menu();
    }

    switch(num)
    {
        case 1:
            DirectInsertSort();
            printf("\n\n\t\t\t        请输入任意键继续...");
            getchar();
            system("clear");
            Menu();
            break ;
        case 2:
            BinaryInsertSort();
            printf("\n\n\t\t\t        请输入任意键继续...");
            getchar();
            system("clear");
            Menu();
            break ;
        case 3:
            ShellInsertSort();
            printf("\n\n\t\t\t        请输入任意键继续...");
            getchar();
            system("clear");
            Menu();
            break ;
        case 4:
            QuitSort();
            printf("\n\n\t\t\t        请输入任意键继续...");
            getchar();
            system("clear");
            Menu();
            break ;
        case 5:
            break ;
        case 6:
            break ;
        case 7:
            break ;
        case 8:
            break ;
        case 9:
            break ;
        case 10:
            printf("\n\n\n\n\n\t\t\t       \3欢迎使用本次操作!\3");
            printf("\n\n\t\t\t        请输入任意键继续...");
            getchar();
            system("clear");
            exit(0);
            break ;
        default:
            printf("\n\n\t\t\t【×】Error:输入有误,请重新选择!");
            Menu();
            break ;
    }
}


int main(void)
{
    //Time();
    Menu();
}
