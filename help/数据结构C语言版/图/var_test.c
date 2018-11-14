#include <stdio.h>
#include <stdarg.h>

void fun(int sub,...)/*......声明不定参数*/
//void fun(const int * const padj, const int index, const char name, const int indegree, int sub, ...)
//问题3：不定参数用什么符号，用的是句号吗，需要几个点？
{
    va_list ap;

//问题4：ap是一个指针变量，还是一个字符变量？

    int t;
    va_start(ap,sub);
    printf("%d",sub);
	//问题5：这个循环是如何运行的？
    while((t=va_arg(ap,int)))
		printf("%c",t);
    va_end(ap);
}

int main(void)
{
    int adj, a=1,b=2,c=3;
    fun(1,'a','c', 'd',NULL);/*以NULL作结束*/
	//fun(&adj, 0, 's', 0, 3, 'a', 'd', 'g') ;
    printf("\n");
    return 0;
}  