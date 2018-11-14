#ifndef	__ST_LIB_H__
#define	__ST_LIB_H__



/* Guard C code in headers, while including them from C++ */
#ifdef  __cplusplus
#define	ST_BEGIN_DECLS  extern "C" {
#define	ST_END_DECLS    }
#else
#define	ST_BEGIN_DECLS
#define	ST_END_DECLS
#endif

/* Provide definitions for some commonly used macros.
 *  Some of them are only provided if they haven't already
 *  been defined. It is assumed that if they are already
 *  defined then the current definition is correct.
 */
#ifndef NULL
#ifdef __cplusplus
#define	NULL        (0L)
#else /* !__cplusplus */
#define	NULL        ((void*) 0)
#endif /* !__cplusplus */
#endif

#ifndef NUL
#define NUL ('\0')
#endif

#ifndef FAILED
#define FAILED (-2)
#endif

#define PRIME 	7						// 素数
#define ZERO 	0
#define ONE 	1
#define TWO 	2

#include <assert.h>
#define st_assert   				assert

#if	defined(WIN32)
#define	stinline	
#else
#define	stinline	inline
#endif


typedef char                     	stint8 ;
typedef unsigned char             	stuint8 ;
typedef short          				stint16 ;
typedef unsigned short          	stuint16 ;
typedef long                   		stint32 ;
typedef unsigned long          		stuint32 ;
typedef int                      	stint ;
typedef unsigned int				stuint ;
typedef stuint						stsize_t ;
typedef stint  						stbool;

typedef float   					stfloat;
typedef double  					stdouble;

typedef void* 						stpointer;
typedef const void *				stconstpointer;


#ifndef	FALSE
#define	FALSE	(0)
#endif

#ifndef	TRUE
#define	TRUE	(!FALSE)
#endif

#undef	MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#undef	MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

#undef	ABS
#define ABS(a)	   (((a) < 0) ? -(a) : (a))

#undef	CLAMP
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#define cmp(a, b) ( ( ((a)-(b)) >= (0) ) ? (1) : (0) ) //比较a，b大小

#define SUCCESS 	1
#define UNSUCCESS 	0
#define DUPLICATE 	-1


typedef stint 			(*STCompareFunc)(stconstpointer  a,stconstpointer  b);
typedef stint 			(*STCompareDataFunc)(stconstpointer a, stconstpointer  b, stpointer user_data);
typedef void 			(*STFunc)(stpointer data, stpointer user_data);
typedef void            (*STDestroyNotify)       (stpointer       data);
typedef stbool  		(*STHRFunc)  (stpointer  key,
						stpointer  value,
						stpointer  user_data);
typedef stbool        	(*STEqualFunc)           (stconstpointer  a,
        				stconstpointer  b);
typedef stuint			(*STHashFunc)            (stconstpointer  key);
typedef void            (*STHFunc)               (stpointer       key,
						stpointer       value,
						stpointer       user_data);

#define stoffsetof(TYPE, MEMBER) ((unsigned int) &((TYPE *)0)->MEMBER)
#define st_container_of(ptr, type, member) ({                      	\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    	\
        (type *)( (char *)__mptr - stoffsetof(type,member) );})
	

#endif	/* __ST_LIB_H__ */

