/**************************************************************************
*  文  件  名 : MERGE.C                                                   *
*  编  制  人 : 湖北省公安县统计局  毛 泽 发                              *
*  日      期 : 1991.8                                                    *
**************************************************************************/

#include <io.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "merge.h"

static mercmpf *mercmp = NULL;   /* 比较函数 */

static char *merbuf = NULL;  /* 排序动态缓冲区 */
static char *filetop = NULL; /* 原文件文件头存放动态缓冲区 */
static int filetopchs;       /* 原文件文件头长 */
static int merlrd;           /* 文件记录长 */

static int outfile(char *fname, unsigned size, int flag);
static int formerge(char *foname, char *finame, char *tmp, unsigned m);
static domerge(char *foname, char *tmp1, char *tmp2, int irun);
static void smerge(int *md, int m, char *buf[], int outf, char *outbuf, int size);
static int dopass(char *name1, char *name2, int irun);

/* 通用排序函数.
     参  数:排序文件名;原文件名;原文件头字节数;文件记录长;用户提供的比较函数.
     返回值:成功 > 0;内存不够.记录超长返回 0;文件操作出错 -1 */
int fmerge(char *foname, char *finame, int ftops, int lrd, mercmpf *cmpf)
{
  char tmp1[68], tmp2[68];
  int irun;
  unsigned size;
  if(lrd > MAXMEREC) return 0;   /* 记录超长 */
  merlrd = lrd;
  size = (SSIZE / lrd) * lrd;    /* 排序缓冲区实际长 */
  if((merbuf = (char *)malloc(size)) == NULL) return 0; /* 分配动态缓冲区 */
  if(ftops && (filetop = (char *)malloc(ftops)) == NULL) return 0;
  filetopchs = ftops;
  mercmp = cmpf;
  strcpy(tmp1, "&&&1");   /* 临时文件名 */
  strcpy(tmp2, "&&&2");
  irun = formerge(foname, finame, tmp1, size); /* 分片排序 */
  if(irun > 1)                                 /* 如果排序片大于 1 */
    irun = domerge(foname, tmp1, tmp2, irun);  /* 合并排序片 */
  free(merbuf);
  if(filetopchs) free(filetop);
  return irun;
}
/* 写一排序片文件 */
static int outfile(char *fname, unsigned size, int flag)
{
  int h, c;
  if((h = open(fname, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, S_IWRITE)) == -1)
    return -1;
  if(flag && filetopchs) /* 如果是最终文件同时原文件有文件头 */
    write(h, filetop, filetopchs); /* 写入文件头内容 */
  c = write(h, merbuf, size);      /* 写排序片到文件 */
  close(h);
  return c;
}
/* 分片排序 */
static int formerge(char *foname, char *finame, char *tmp, unsigned m)
{
  unsigned irun, ret;
  int f, flag = 0;
  char tmpname[68];
  if((f = open(finame, O_RDONLY | O_BINARY)) == -1) return -1;/* 打开原文件 */
  if(filetopchs)   /* 如有文件头,保存其内容到缓冲区 */
    read(f, filetop, filetopchs);
  irun = 0;
  do{
    ret = read(f, merbuf, m);  /* 读一排序片到排序缓冲区 */
    if(ret == 0 || ret == 0xffff) break; /* 原文件结束或出错,退出 */
    qsort(merbuf, ret / merlrd, merlrd, mercmp); /* 排序 */
    if(ret == m || irun > 0)   /* 如原文件长大于或等于一排序片长 */
      sprintf(tmpname, "%s.%03d", tmp, irun); /* 采用临时文件名 */
    else{                      /* 否则,直接用排序文件名 */
      strcpy(tmpname, foname);
      flag = 1;                /* 最终文件标记 */
    }
    ret = outfile(tmpname, ret, flag); /* 写排序片 */
    irun ++;
  }while(ret == m);
  close(f);
  if(ret == 0xffff) return ret;  /* 出错返回 -1 */
  return irun;                   /* 返回排序片数 */
}
/* 分配每一合并趟不同临时文件名;控制合并趟数 */
static domerge(char *foname, char *tmp1, char *tmp2, int irun)
{
	char *p;
	while(irun > 1){
		if(irun <= MAXMERGE) strcpy(tmp2, foname);
		irun = dopass(tmp1, tmp2, irun);
		p = tmp1;
		tmp1 = tmp2;
		tmp2 = p;
	}
	return irun;
}
/* 执行合并趟,计算.分配每次合并所需文件数,缓冲区大小,控制每次合并的执行 */
static int dopass(char *name1, char *name2, int irun)
{
	int fi, i, nrun, m, size;
	char oname[68], inname[68], *p[MAXMERGE], *q;
	int md[MAXMERGE], fo;
	size = SSIZE / merlrd;  /* 合并缓冲区容纳记录数 */
	nrun = 0;
	for(fi = 0; fi < irun; fi += MAXMERGE){
		m = irun - fi;    /* 每次合并实际排序片数 */
		if(m > MAXMERGE) m = MAXMERGE;
		for(i = 0; i < m; i ++) p[i] = merbuf + (i * merlrd); /* 分配读缓冲区 */
		if(irun <= MAXMERGE) strcpy(oname, name2); /* 最终合并形成排序文件 */
		else sprintf(oname, "%s.%03d", name2, nrun);/* 中间合并采用临时文件 */
		if((fo = open(oname, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, S_IWRITE)) == -1)
			break;  /* 打开写文件 */
		i = 0;
		do{ /* 分别打开读文件 */
			sprintf(inname, "%s.%03d", name1, fi + i);
			md[i] = open(inname, O_RDONLY | O_BINARY);
		}while(md[i ++] != -1 && i < m);
		if(i != m){
			close(fo);
			for(fi = 0; fi < i; fi ++) close(md[fi]);
			break;
		}
		if(irun <= MAXMERGE && filetopchs) /* 最终合并写文件头(如有) */
			write(fo, filetop, filetopchs);
		q = merbuf + (m * merlrd);        /* 分配写缓冲区 */
		smerge(md, m, p, fo, q, size - m); /* 合并 */
		for(i = 0; i < m; i ++){  /* 删除各排序片文件 */
			close(md[i]);
			sprintf(inname, "%s.%03d", name1, fi + i);
			unlink(inname);
		}
		close(fo);
		nrun ++;
	}
	if(nrun != (irun + MAXMERGE - 1) / MAXMERGE) return -1;
	return nrun;
}
/* 执行实际排序片合并 */
static void smerge(int *md, int m, char *buf[], int outf, char *outbuf, int size)
{
	int i, j, n = merlrd, w = merlrd * size;
	char *s = buf[0], *p, *q = outbuf, *end = q + w;
	for(i = 0; i < m; i ++)   /* 从各片文件中读第一条记录 */
		read(md[i], buf[i], n);
	while(1){
		if(n == merlrd){        /* 如各片文件均有记录,各片记录反向插入排序 */
			for(i = 1; i < m; i ++){
				for(p = buf[i], j = i - 1; j >= 0 && mercmp(p, buf[j]) > 0; j --)
					buf[j + 1] = buf[j];
				buf[j + 1] = p;
			}
		}
		else m --;  /* 一片文件内容结束 */
		if(!m){     /* 如所有片文件结束,写缓冲区残余记录,退出 */
			if(q != outbuf) write(outf, outbuf, q - outbuf);
			break;
		}
		if(q == end){  /* 刷新一次写缓冲区到文件 */
			if(write(outf, outbuf, end - outbuf) != w) break;
			q = outbuf;
		}
		i = m - 1;
		j = (buf[i] - s) / merlrd;
		memmove(q, buf[i], merlrd); /* 将各片记录中值最小(大)者移入写缓冲区 */
		q += merlrd;
		n = read(md[j], buf[i], merlrd); /* 从该片中读下一记录,继续 */
	}
}