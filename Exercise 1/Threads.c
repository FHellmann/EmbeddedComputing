#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* function( void )
{
	pthread_t *id = pthread_self();
	sleep( rand() % 50);
	printf( "This is thread %d\n", id );
	pthread_exit((void*)id);
}

int main( void )
{
	pthread_attr_t attr;

	pthread_attr_init( &attr );
	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
	// Wenn DETACHTED anstatt JOINABLE verwendet wird, kann hinterher die Funktion pthread_join nicht verwendet werden.

	pthread_t th1, th2;

	pthread_create( &th1, &attr, &function, NULL );
	pthread_create( &th2, &attr, &function, NULL );

	pthread_t *result1, *result2;
	pthread_join( th1, (void**)&result1 );
	pthread_join( th2, (void**)&result2 );

	if( th1 == result1 && th2 == result2 ) {
		printf( "Thread 1 has the same id before %d and after %d\n", th1, result1 );
		printf( "Thread 2 has the same id before %d and after %d\n", th2, result2 );
	} else {
		printf( "Something went wrong!\nThread 1 (ID-before=%d, ID-after=%d)\nThread 2 (ID-before=%d, ID-after=%d)\n", th1, result1, th2, result2 );
	}

	return EXIT_SUCCESS;
}
