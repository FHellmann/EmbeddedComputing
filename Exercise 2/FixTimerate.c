#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main( void )
{
	struct timespec timeout;
	
	const int NSEC_IN_SEC = 1000000;
	clock_gettime(CLOCK_MONOTONIC, &timeout);
	while(1) {
		if(timeout.tv_nsec >= NSEC_IN_SEC) {
			timeout.tv_nsec -= NSEC_IN_SEC;
			timeout.tv_sec++;
		}
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &timeout, NULL);
	}

	return EXIT_SUCCESS;
}