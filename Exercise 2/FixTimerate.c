#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main( void )
{
	struct timespec loop;
	
	const int INTERVAL = 1000000;
	
	loop.tv_nsec = INTERVAL;
	loop.tv_sec = 0;
	
	while(1) {
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &loop, NULL);
	}

	return EXIT_SUCCESS;
}