#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main( void )
{
	struct timespec frequency, requestStart, requestEnd;
	frequency.tv_sec = 0;
	long diff = 0;
	long sleepTime = 1000000;
	while(1) {
		// Get time when starting loop
		clock_gettime(CLOCK_MONOTONIC, &requestStart);
		
		frequency.tv_nsec = sleepTime - diff;
		clock_nanosleep(CLOCK_MONOTONIC, 0, &frequency, NULL);
		
		// Get time when loop ends
		clock_gettime(CLOCK_MONOTONIC, &requestEnd);
		
		// Get the difference of the start and end time from the last iteration
		diff = requestEnd.tv_nsec - requestStart.tv_nsec - sleepTime;
	}

	return EXIT_SUCCESS;
}