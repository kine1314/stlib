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
	
	
	printf("�������ݵ�ַ��0x%08x\n", p);
	
	putchar('\n');
	printf("ջ�����ݵ�ַ(�г�ֵ)��0x%08x = %d\n", &i, i);
	printf("ջ�����ݵ�ַ(�г�ֵ)��0x%08x = %d\n", &j, j);
	printf("ջ�����ݵ�ַ(�г�ֵ)��0x%08x = %d\n", &k, k);
	printf("ջ�����ݵ�ַ(�޳�ֵ)��0x%08x = %d\n", &f, f);
	printf("ջ�����ݵ�ַ(�޳�ֵ)��0x%08x = %d\n", &h, h);
	
	putchar('\n');
	printf("��̬���ݵ�ַ(�г�ֵ)��0x%08x = %d\n", &s_i, s_i);
	printf("��̬���ݵ�ַ(�г�ֵ)��0x%08x = %d\n", &s_j, s_j);
	printf("��̬���ݵ�ַ(�޳�ֵ)��0x%08x = %d\n", &s_k, s_k);
	printf("��̬���ݵ�ַ(�޳�ֵ)��0x%08x = %d\n", &s_h, s_h);
	
	putchar('\n');
	printf("ȫ�����ݵ�ַ(�г�ֵ)��0x%08x = %d\n", &g_i, g_i);
	printf("ȫ�����ݵ�ַ(�г�ֵ)��0x%08x = %d\n", &g_j, g_j);
	printf("ȫ�����ݵ�ַ(�޳�ֵ)��0x%08x = %d\n", &g_k, g_k);
	printf("ȫ�����ݵ�ַ(�޳�ֵ)��0x%08x = %d\n", &g_h, g_h);
	
	putchar('\n');
	printf("�ַ����������ݵ�ַ��0x%08x ָ�� 0x%08x ����Ϊ-%s\n", &pstr1, pstr1, pstr1);
	printf("�ַ����������ݵ�ַ��0x%08x ָ�� 0x%08x ����Ϊ-%s\n", &pstr2, pstr2, pstr2);
	printf("�ַ����������ݵ�ַ��0x%08x ָ�� 0x%08x ����Ϊ-%s\n", &pstr3, pstr3, pstr3);
	free(p);
	return 0;
}