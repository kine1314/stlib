#include <stdio.h>
#include <malloc.h>
int g_i = 100;
int g_j = 200;
int g_k, g_h;
int main()
{
	const int MAXN = 100;
	int *p = (int*)malloc(MAXN * sizeof(int));
	static int s_i = 5;
	static int s_j = 10;
	static int s_k;
	static int s_h;
	int i = 5;
	int j = 10;
	int k = 20;
	int f, h;
	char *pstr1 = "MoreWindows123456789";
	char *pstr2 = "MoreWindows123456789";
	char *pstr3 = "Hello";
	
	
	printf("堆中数据地址：0x%08x\n", p);
	
	putchar('\n');
	printf("栈中数据地址(有初值)：0x%08x = %d\n", &i, i);
	printf("栈中数据地址(有初值)：0x%08x = %d\n", &j, j);
	printf("栈中数据地址(有初值)：0x%08x = %d\n", &k, k);
	printf("栈中数据地址(无初值)：0x%08x = %d\n", &f, f);
	printf("栈中数据地址(无初值)：0x%08x = %d\n", &h, h);
	
	putchar('\n');
	printf("静态数据地址(有初值)：0x%08x = %d\n", &s_i, s_i);
	printf("静态数据地址(有初值)：0x%08x = %d\n", &s_j, s_j);
	printf("静态数据地址(无初值)：0x%08x = %d\n", &s_k, s_k);
	printf("静态数据地址(无初值)：0x%08x = %d\n", &s_h, s_h);
	
	putchar('\n');
	printf("全局数据地址(有初值)：0x%08x = %d\n", &g_i, g_i);
	printf("全局数据地址(有初值)：0x%08x = %d\n", &g_j, g_j);
	printf("全局数据地址(无初值)：0x%08x = %d\n", &g_k, g_k);
	printf("全局数据地址(无初值)：0x%08x = %d\n", &g_h, g_h);
	
	putchar('\n');
	printf("字符串常量数据地址：0x%08x 指向 0x%08x 内容为-%s\n", &pstr1, pstr1, pstr1);
	printf("字符串常量数据地址：0x%08x 指向 0x%08x 内容为-%s\n", &pstr2, pstr2, pstr2);
	printf("字符串常量数据地址：0x%08x 指向 0x%08x 内容为-%s\n", &pstr3, pstr3, pstr3);
	free(p);
	return 0;
}