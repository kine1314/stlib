#include <stdio.h>
#include <stdarg.h>

void fun(int sub,...)/*......������������*/
//void fun(const int * const padj, const int index, const char name, const int indegree, int sub, ...)
//����3������������ʲô���ţ��õ��Ǿ������Ҫ�����㣿
{
    va_list ap;

//����4��ap��һ��ָ�����������һ���ַ�������

    int t;
    va_start(ap,sub);
    printf("%d",sub);
	//����5�����ѭ����������еģ�
    while((t=va_arg(ap,int)))
		printf("%c",t);
    va_end(ap);
}

int main(void)
{
    int adj, a=1,b=2,c=3;
    fun(1,'a','c', 'd',NULL);/*��NULL������*/
	//fun(&adj, 0, 's', 0, 3, 'a', 'd', 'g') ;
    printf("\n");
    return 0;
}  