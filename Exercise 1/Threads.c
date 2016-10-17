#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* function( void )
{
	int *id = pthread_self();
	sleep( 30 );
	printf( "This is thread %d\n", id );
	pthread_exit((void*)id);
}

int main( void )
{
	pthread_attr_t attr;

	pthread_attr_init( &attr );
	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
	// Wenn DETACHTED anstatt JOINABLE verwendet wird, kann hinterher die Funktion pthread_join nicht verwendet werden.

	int *result1, *result2;
	pthread_t th1, th2;

	pthread_create( &th1, &attr, &function, NULL );
	pthread_create( &th2, &attr, &function, NULL );

	pthread_join( th1, (void**)&result1 );
	pthread_join( th2, (void**)&result2 );

	printf( "th1 is %d & th2 is %d\n", result1, result2 );

	return EXIT_SUCCESS;
}
