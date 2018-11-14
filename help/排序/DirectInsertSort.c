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
        if(L->data[i] < L->data[i-1])                           // �����ѡ���������������һ��С�ż�¼�ڱ�;
        {
            L->data[0] = L->data[i] ;                           // ��¼�ڱ�
            for(j = i-1 ; L->data[0] < L->data[j] ; --j)        // �ҵ��ʵ��Ĳ���λ��,�������������!
            {
                L->data[j+1] = L->data[j] ;                     // ����
            }
            L->data[j] = L->data[0] ;                           // ���뵽�ʵ���λ��
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
            while(low <= high)                  // ��low����high��ʱ��,
            {
                mid = (low + high)/2 ;
                if(L->data[0] > L->data[mid])
                    low = mid + 1 ;
                else
                    high = mid - 1 ;
            }
            for(j=i-1 ; j >= high+1 ; --j)
            {
                L->data[j+1] = L->data[j] ;     // ��high���������data����
            }
            L->data[high+1] = L->data[0] ;      // high+1 is the insert value
        }
    }
    
}

void SInsertSort(SqList *L)
{
    int i,j,k;

    k = (L->length)/2;                                   //kֵ��������ֵ
    while(k>=1)                              //������kֵ�仯��0������ѭ������
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
    static char *week[]={"һ","��","��","��","��","��","��"};
    t=time(NULL);
    tp=localtime(&t);
    printf("\t��          ������������������������������������������\n");
    printf("\t\t       ������:%d��%d��%d��",tp->tm_year+1900,tp->tm_mon+1,tp->tm_mday);   
    printf(" %d:%d:%d ",tp->tm_hour,tp->tm_min,tp->tm_sec);
    printf("����%s\n",week[(tp->tm_wday)-1]);
    printf("\t��          ������������������������������������������\n");
}
*/

void Menu(void)
{
    int num;
    char c;
    printf("\n\t\t\t         1.     ֱ�Ӳ�������\n");
    printf("\t\t\t         2.     �۰��������\n");
    printf("\t\t\t         3.     ϣ������\n");
    printf("\t\t\t         4.     ��������\n");
    printf("\t\t\t         5.     �鲢����\n");
    printf("\t\t\t         6.     ð������\n");
    printf("\t\t\t         7.     ѡ������\n");
    printf("\t\t\t         8.     ������(������randrom()��ʼ������)\n");
    printf("\t\t\t         9.     ���������\n");
    printf("\t\t\t         10. ע��\n");
    printf("\t\t     ----------------------------------------");
    printf("\n\t\t       ��ѡ������Ķ���<1,2>...\n");
    printf("\t\t       ������:");    

    while(scanf("%d", &num)!=1)                     //����Ƿ�Ϊ��ȷ������
    {
        while ((c=getchar())!='\n');
        printf("\n\n\t\t\t������Error:��������,������ѡ��!");
        getchar();
        system("clear");
        Menu();
    }

    switch(num)
    {
        case 1:
            DirectInsertSort();
            printf("\n\n\t\t\t        ���������������...");
            getchar();
            system("clear");
            Menu();
            break ;
        case 2:
            BinaryInsertSort();
            printf("\n\n\t\t\t        ���������������...");
            getchar();
            system("clear");
            Menu();
            break ;
        case 3:
            ShellInsertSort();
            printf("\n\n\t\t\t        ���������������...");
            getchar();
            system("clear");
            Menu();
            break ;
        case 4:
            QuitSort();
            printf("\n\n\t\t\t        ���������������...");
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
            printf("\n\n\n\n\n\t\t\t       \3��ӭʹ�ñ��β���!\3");
            printf("\n\n\t\t\t        ���������������...");
            getchar();
            system("clear");
            exit(0);
            break ;
        default:
            printf("\n\n\t\t\t������Error:��������,������ѡ��!");
            Menu();
            break ;
    }
}


int main(void)
{
    //Time();
    Menu();
}
