#ifndef	__ST_QSORT_H__
#define	__ST_QSORT_H__
ST_BEGIN_DECLS;

#include "stlib.h"

void st_qsort_with_data (stconstpointer    pbase,
			stint             	total_elems,
			stuint32            size,
			STCompareDataFunc 	compare_func,
			stpointer         	user_data);



ST_END_DECLS;
#endif	/* __ST_QSORT_H__ */

