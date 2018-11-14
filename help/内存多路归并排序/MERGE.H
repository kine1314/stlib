/**************************************************************************
*  文  件  名 : MERGE.H                                                   *
*  编  制  人 : 湖北省公安县统计局  毛 泽 发                              *
*  日      期 : 1991.8                                                    *
**************************************************************************/

#define S_IREAD         0x0100
#define S_IWRITE        0x0080

#if defined(__TINY__) || defined(__SMALL__) || defined(__MENIUM__)
#define SSIZE     25600    /* 排序缓冲区字节 */
#define NULL      0
#else
#define SSIZE     65024    /* 排序缓冲区字节 */
#define NULL      0L
#endif
#define MAXMERGE  4        /* 排序合并每趟每次最大片 */
#define MAXMEREC  (SSIZE / (MAXMERGE + 1)) /* 文件最大记录长 */

typedef int cdecl mercmpf(const void *, const void *);

/* 通用排序函数.
参  数:排序文件名;原文件名;原文件头字节数;文件记录长;用户提供的比较函数.
返回值:成功 > 0;内存不够.记录超长返回 0;文件操作出错 -1 */
int fmerge(char *foname, char *finame, int ftops, int lrd, mercmpf *cmpf);