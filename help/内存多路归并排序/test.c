//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "merge.h"

#pragma hdrstop

#define TOPSTRING       "湖北省公安县统计局  毛 泽 发"
#define TOP_SIZE        30
#define RECORD_SIZE     53
#define RECORD_COUNT    10000

//---------------------------------------------------------------------------
/* 为了方便观察，随机生成了一个RECORD_COUNT行的文本文件 */
void MakeFile(char *filename)
{
    int i, j;
    long v[4];
    FILE *f;
    f = fopen(filename, "w");
    fprintf(f, "%s\n", TOPSTRING);
    //randomize();
	srand(time(0));
    for (i = 0; i < RECORD_COUNT; i ++)
    {
        for (j = 0; j < 4; j ++)
            v[j] = rand();
        fprintf(f, "%12ld %12ld %12ld %12ld\n", v[0], v[1], v[2], v[3]);
    }
    fclose(f);
}


int cdecl CompRecord(const void *ra, const void *rb)
{
    int a[4], b[4];
    int i, n;
    sscanf((char*)ra, "%ld%ld%ld%ld", &a[0], &a[1], &a[2], &a[3]);
    sscanf((char*)rb, "%ld%ld%ld%ld", &b[0], &b[1], &b[2], &b[3]);
    for (n = 0, i = 0; i < 4 && n == 0; i ++)
        n = a[i] - b[i];
    return n;
}

#pragma argsused
int main(int argc, char* argv[])
{
    printf("正在随机制造一个文本文件d:/test.txt... ");
    MakeFile("d:/test.txt");
    printf("正在进行磁盘文件排序，排序文件d:/sort.text... ");
    fmerge("d:/sort.txt", "d:/test.txt", TOP_SIZE, RECORD_SIZE, CompRecord);
    printf("磁盘文件排序完毕! ");
    system("pause");
    return 0;
}
//---------------------------------------------------------------------------