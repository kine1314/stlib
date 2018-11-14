#ifndef	__ST_LOG_H__
#define	__ST_LOG_H__

#include "stdlib.h"
#include "stlib.h"

ST_BEGIN_DECLS;

#define	ST_DEBUG_LEVEL_GATE				4	

#define ST_DEBUG_LEVEL_NOCHECK       	0            /* No run time checks are performed                             */
#define ST_DEBUG_LEVEL_CHECK_ALL     	1            /* Parameter checks and consistency checks are performed        */
#define ST_DEBUG_LEVEL_LOG_ERRORS    	2            /* Errors are recorded                                          */
#define ST_DEBUG_LEVEL_LOG_WARNINGS  	3            /* Errors & Warnings are recorded                               */
#define ST_DEBUG_LEVEL_LOG_ALL       	4            /* Errors, Warnings and Messages are recorded.                  */


#if(ST_DEBUG_LEVEL_GATE == 0)

#elif(ST_DEBUG_LEVEL_GATE == 1)
    #define __ERR
    #define __ASSERT
#elif(ST_DEBUG_LEVEL_GATE == 2)
    #define __ERR
    #define __ASSERT
#elif(ST_DEBUG_LEVEL_GATE == 3)
    #define __ERR
    #define __ASSERT
    #define __WRN
#elif(ST_DEBUG_LEVEL_GATE == 4)
    #define __ERR
    #define __ASSERT
    #define __WRN
    #define __MSG
    #define __HERE
    #define __INF
	#define __LOG
#endif

#if defined(WIN32)


#ifdef __ASSERT
    #define __ast(condition)    (if(!condition)                                                     \
                                 	fprintf(stderr, "AST:L%d(%s): condition err!", __LINE__, __FILE__), exit( 1 )   )
#else
    #define __ast(condition)
#endif

#ifdef __MSG
	#define __msg( Str )			fprintf( stderr, "MSG:L%d(%s):%s\n", __LINE__, __FILE__, Str )
#endif

#ifdef __ERR
    #define __err( Str )			fprintf( stderr, "ERR:L%d(%s):%s\n", __LINE__, __FILE__, Str ), exit( 1 )
#endif

#ifdef __WRN
    #define __wrn					fprintf( stderr, "WRN:L%d(%s):%s\n", __LINE__, __FILE__, Str )
#endif

#ifdef __HERE
    #define __here__				fprintf(stderr, "@L%d(%s)\n", __LINE__, __FILE__);
    #define __wait__				(fprintf(stderr, "@L%d(%s)(press any key:\n", __LINE__, __FILE__),                 \
									__getc())
#endif

#ifdef __INF
    #define __inf( Str )			fprintf( stderr, "%s\n", Str )
#endif


#else


#ifdef __ASSERT
    #define __ast(condition)    if(!condition)                                                     \
                                 	fprintf(stderr, "AST:L%d(%s): condition err!", __LINE__, __FILE__), exit( 1 )
#else
    #define __ast(condition)
#endif

#ifdef __MSG
	#define __msg(...)    		(fprintf(stderr, "MSG:L%d(%s):", __LINE__, __FILE__),                 \
							     fprintf(stderr, __VA_ARGS__)									        )
#else
    #define __msg(...)
#endif

#ifdef __ERR
    #define __err(...)          (fprintf(stderr, "ERR:L%d(%s):", __LINE__, __FILE__),                 \
    							    fprintf(stderr, __VA_ARGS__), exit( 1 ))
#else
    #define __err(...)    		    
#endif

#ifdef __WRN
    #define __wrn(...)          (fprintf(stderr, "WRN:L%d(%s):", __LINE__, __FILE__),                 \
    						     fprintf(stderr, __VA_ARGS__)									        )
#else
    #define __wrn(...)
#endif

#ifdef __HERE
    #define __here__            fprintf(stderr, "@L%d(%s)\n", __LINE__, __FILE__);
    #define __wait__            (fprintf(stderr, "@L%d(%s)(press any key:\n", __LINE__, __FILE__),                 \
                                __getc())
#else
    #define __here__
    #define __wait__
#endif


#ifdef __INF
    #define __inf(...)           fprintf(stderr, __VA_ARGS__)
#else
    #define __inf(...)
	
#endif

#endif

#ifdef __LOG
	#define __log(a)			 st_external_log a
#else
	#define __log(a)
#endif


ST_END_DECLS;
#endif	/* __ST_LOG_H__ */

