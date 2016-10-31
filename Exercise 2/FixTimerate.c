#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	struct timespec frequency, requestStart, requestEnd;
	frequency.tv_sec = 0;
	while(1) {
		// Get the difference of the start and end time from the last iteration
		if(requestEnd.tv_nsec > 0) {
			long diff = requestEnd.tv_nsec - requestStart.tv_nsec - 1000;
			// Sample: diff = end - start - 1000 = 1050 - 10 - 1000 = 40
		}
		
		// Get time when starting loop
		clock_gettime(CLOCK_REALTIME, &requestStart);
		// Sample: start = 10
		
		frequency.tv_nsec = 1000 - diff;
		clock_nanosleep(CLOCK_REALTIME, 0, &frequency, NULL);
		
		// Get time when loop ends
		clock_gettime(CLOCK_REALTIME, &requestEnd);
		// Sample: end = 1050
	}

	return EXIT_SUCCESS;
}