#include "binomial-queue.h"
#include <stdio.h>

#define MaxSize (32)

main( )
{
    BinQueue H;
    int i, j;
    Item AnItem;

    InitializeBinQueue(&H, 256 );
    for( i=0, j=MaxSize/2; i<MaxSize; i++, j=( j+71)%MaxSize )
    {
        printf( "Inserting %d\n", j );
        H = Insert( H, j );
    }
 #if 1
    j = 0;
    while( !BinQueueIsEmpty( H ) )
    {
#if 1
        
        AnItem = DeleteMin( H );
		printf( "DeleteMin item [%d]\n", AnItem );
#else
	    if( DeleteMin( H ) != j++ )
            printf( "Error in DeleteMin, %d\n", j );
#endif
    }
    if( j != 256 )
        printf( "Error in counting\n" );
#endif
    printf( "Done...\n" );
    return 0;
}
