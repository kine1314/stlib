#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>

#include "st_log.h"
#include "stlib.h"



static void st_external_log_init(void)
{
	static st_external_inited = 0 ;
	if (st_external_inited)
		return ;
	{
		FILE * fp = fopen("st_external.log", "w") ;
		fclose(fp) ;
	}
	st_external_inited = 1 ;
}

void st_external_log(const stint8 * fmt, ...)
{
#if defined(ST_DBG_)
	time_t t ;
	struct tm* pTm ;
    stint8 out[4096];
    va_list body;	
	size_t time_str_len = 0 ;

#if 1
	time(&t) ;
	pTm = localtime(&t) ;
	time_str_len = strftime(out, sizeof(out), "%Y-%m-%d %H:%M:%S : ", pTm) ;
#endif

    va_start(body, fmt);
    vsprintf(out + time_str_len, fmt, body); // 译注：格式化输入的字符串 fmt

    va_end(body); // 到输出字符串 ou

	st_external_log_init() ;
	// 输出到文件st_external.log
	{
		FILE * fp = fopen("st_external.log", "a") ;
		assert(fp) ;
		fprintf(fp, "%s\n", out) ;
		fclose(fp) ;
	}

#endif
}

