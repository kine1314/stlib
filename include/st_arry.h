#ifndef	__ST_ARRY_H__
#define	__ST_ARRY_H__
#include "stlib.h"

ST_BEGIN_DECLS;

void st_arry_recursive_merge_sort(stint a[],stint left,stint right);	/* 二路归并， 递归recursion，  */
void st_arry_iteration_merge_sort(stint a[], stint n);					/* 迭代Iteration */
void st_arry_head_sort(stint array[], stint n);				
void st_arry_qsort(stint *array,stint low,stint high);
void st_arry_shell_sort(stint array[], stint n);
void st_arry_select_sort(stint array[], stint n);
void st_arry_bubble_sort(stint array[], stint n);
void st_arry_bubble_sort_1(stint array[], stint n);
void st_arry_insert_sort(stint array[], stint n);			/* 直接插入排序 */
void st_arry_binary_insert_sort(stint array[], stint n);	/* 折半插入排序 */
void st_arry_radix_sort(stint array[], stint n);					/* 基数排序 */
void st_arry_tournament_sort(stint array[], stint n/*个数*/);		/* 锦标赛排序 */

ST_END_DECLS;
#endif	/* __ST_ARRY_H__ */

