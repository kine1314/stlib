#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "st_disjoint_sets.h"
#include "st_log.h"


/*	接口函数定义	*/

void DJSInitializeAsHeight (DisjiontSet gather, const int size)
{
	int i ;

	gather[0] = size ;
	for (i = 1; i <= size; i++)
		gather[i] = DJSHEIGHT ;
}

void DJSInitializeAsSize (DisjiontSet gather, const int size)
{
	int i ;

	gather[0] = size ;
	for (i = 1; i <= size; i++)
		gather[i] = DJSSIZE ;
}

// 使得浅的树成为深的树的子树，保证所有树的深度O(logN)，这是一种平缓算法，因为只有两颗深度相等的树求合并的时候深度才+1；
int DJSSetUnionAsHeight (DisjiontSet gather, DJSType root1, DJSType root2)
{
	if (gather[root1] > 0 || gather[root2] > 0)
		return 0 ;
	
	if (gather[root2] < gather[root1])
		gather[root1] = root2 ;
	else
	{
		if (gather[root1] == gather[root2])
			gather[root1]-- ;
		gather[root2] = root1 ;
	}

	return 1 ;
}

// 使得总让较小的树成为较大树的子树，保证所有树的深度O(logN)
int DJSSetUnionAsSize (DisjiontSet gather, DJSType root1, DJSType root2)
{
	if (gather[root1] > 0 || gather[root2] > 0)
		return 0 ;
	if (gather[root2] < gather[root1])
	{
		gather[root2] += gather[root1] ;
		gather[root1] = root2 ;
	}
	else
	{
		gather[root1] += gather[root2] ;
		gather[root2] = root1 ;
	}

	return 1 ;
}

DJSType DJSFind (DisjiontSet gather, const DJSItem item)
{
	if (item > gather[0])
		return DJSOOS ;
	else if (gather[item] <= 0)
		return item ;
	else
		return gather[item] = DJSFind (gather, gather[item]) ;		// 返回X所在集合树的根！
}






