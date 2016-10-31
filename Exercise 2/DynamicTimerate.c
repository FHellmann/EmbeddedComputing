#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void changeSystemTick(unsigned int microsecs) {
	struct timespec frequency, requestStart, requestEnd;
	frequency.tv_sec = 0;
	
	while(1) {
		// Get the difference of the start and end time from the last iteration
		long diff = requestEnd.tv_nsec - requestStart.tv_nsec - microsecs;
		// Sample: diff = end - start - 1000 = 1050 - 10 - 1000 = 40
		
		// Get time when starting loop
		clock_gettime(CLOCK_REALTIME, &requestStart);
		printf("Time taken (nanoseconds): %ld\n", requestStart);
		// Sample: start = 10
		
		frequency.tv_nsec = microsecs - diff;
		clock_nanosleep(CLOCK_REALTIME, 0, &frequency, NULL);
		
		// Get time when loop ends
		clock_gettime(CLOCK_REALTIME, &requestEnd);
		printf("Time taken (nanoseconds): %ld\n", requestEnd);
		// Sample: end = 1050
	}
}

int main( int argc, char *argv[] )
{
	changeSystemTick(strtol(argv[0], NULL, 10));

	return EXIT_SUCCESS;
}