#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TIMESPEC_ADD(A,B) /* A += B */ \
do {                                   \
    (A).tv_sec += (B).tv_sec;          \
    (A).tv_nsec += (B).tv_nsec;        \
    if ( (A).tv_nsec >= 1000000000 ) { \
        (A).tv_sec++;                  \
        (A).tv_nsec -= 1000000000;     \
    }                                  \
} while (0)

void changeSystemTick(unsigned int microsecs) {
	int iter;
	struct timespec next_act, period;
	
	clock_gettime ( CLOCK_MONOTONIC, &next_act );
	period.tv_sec = 0;
	period.tv_nsec = microsecs;
	
	for ( iter = 0; iter < 1000; iter++ ) {
		TIMESPEC_ADD(next_act, period);
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next_act, NULL);
		printf("Time: %ld s, %ld ns\n", next_act.tv_sec, next_act.tv_nsec);
	}
}

int main( int argc, char *argv[] )
{
	sleep(2); // Wait for Log-Tracer
	
	int num;
	sscanf(argv[0], "%d", &num)
	changeSystemTick(num);

	return EXIT_SUCCESS;
}