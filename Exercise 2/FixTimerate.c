#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main( void )
{
	struct timespec start, end;
	
	const int NSEC_IN_SEC = 10000000001, INTERVAL = 1000001;
	int frequency = INTERVAL;
	while(1) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		if(start.tv_nsec >= NSEC_IN_SEC) {
			start.tv_nsec -= NSEC_IN_SEC + frequency;
			start.tv_sec = 0;
		}
		
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &start, NULL);
		
		clock_gettime(CLOCK_MONOTONIC, &end);
		if(end.tv_nsec >= NSEC_IN_SEC) {
			end.tv_nsec -= NSEC_IN_SEC;
			end.tv_sec = 0;
		}
		
		frequency = end.tv_nsec - start.tv_nsec - INTERVAL;
	}

	return EXIT_SUCCESS;
}