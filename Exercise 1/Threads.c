#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* function( void )
{
	// Get the thread id of the current execution thread
	pthread_t *id = pthread_self();
	// Let the current thread sleep for a random time span
	nsleep( rand() % 50);
	// Print out the current executing thread id
	printf( "This is thread %d\n", id );
	// Return the thread id when exiting this thread
	pthread_exit((void*)id);
}

int main( void )
{
	// Initialise the thread attributes
	pthread_attr_t attr;
	pthread_attr_init( &attr );
	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );

	// Create 2 threads
	pthread_t th1, th2;
	pthread_create( &th1, &attr, &function, NULL );
	pthread_create( &th2, &attr, &function, NULL );

	// Wait for the 2 started threads to exit
	pthread_t *result1, *result2;
	pthread_join( th1, (void**)&result1 );
	pthread_join( th2, (void**)&result2 );

	// Compare the thread id before starting the thread with the thread id after exiting the thread
	if( th1 == result1 && th2 == result2 ) {
		printf( "Thread 1 has the same id before %d and after %d\n", th1, result1 );
		printf( "Thread 2 has the same id before %d and after %d\n", th2, result2 );
	} else {
		printf( "Something went wrong!\nThread 1 (ID-before=%d, ID-after=%d)\nThread 2 (ID-before=%d, ID-after=%d)\n", th1, result1, th2, result2 );
	}

	return EXIT_SUCCESS;
}
