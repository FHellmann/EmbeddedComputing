#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>

const int PROFILE_AUTOMATIC = 1;
const int PROFILE_MANUAL = 2;

const int ROTATE_0_HIGH_NANO = 500*1000;
const int ROTATE_0_LOW_NANO = 20*1000000-ROTATE_0_HIGH_NANO;
const int ROTATE_90_HIGH_NANO = 1500*1000;
const int ROTATE_90_LOW_NANO = 20*1000000-ROTATE_90_HIGH_NANO;
const int ROTATE_180_HIGH_NANO = 2500*1000;
const int ROTATE_180_LOW_NANO = 20*1000000-ROTATE_180_HIGH_NANO;

int gProfile = PROFILE_AUTOMATIC, gMinAngle, gMaxAngle;

void* userCommunicationThread( void )
{
	while(1) {
		int profile;

		printf( "Which profile you like to use (0=Quit, 1=Automatic, 2=Manual): ");
		scanf("%d", &profile);
		
		if(profile == 1) {
			// Automatic
			gProfile = profile;
			printf( "\nYou entered the automatic profile: Linear\n");
		} else if(profile == 2) {
			// Manual
			printf( "\nYou entered the manual profile. Enter min and max angle: ", str, i);
			int minAngle, maxAngle;
			scanf("%d %d", &minAngle, &maxAngle);
			gMinAngle = minAngle;
			gMaxAngle = maxAngle;
			gProfile = profile;
			printf( "\nThe servo will rotate between: min angle=%d, max angle=%d \n", minAngle, maxAngle);
		} else {
			// Quit
			gProfile = profile;
			printf( "\nQuit" );
			return;
		}
	}
}

int main( void )
{
	// Initialise the thread attributes
	pthread_attr_t attr;
	pthread_attr_init( &attr );
	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );

	// Create thread for user input
	pthread_t th1;
	pthread_create( &th1, &attr, &userCommunicationThread, NULL );
	
	int direction = 1;
	
	while(1) {
		switch(gProfile) {
			case PROFILE_AUTOMATIC:
				// --- Linear Profile Start ---
				setServoHigh(getRotationVoltage(&direction, &ROTATE_0_HIGH_NANO, &ROTATE_180_HIGH_NANO);
				setServoHigh(getRotationVoltage(&direction, &ROTATE_0_LOW_NANO, &ROTATE_180_LOW_NANO);
				// --- Linear Profile End ---
				break;
			case PROFILE_MANUAL:
				// --- Manual Profile Start ---
				
				// --- Manual Profile End ---
				break;
			default:
				return EXIT_SUCCESS;
		}
		
		direction *= -1;
	}
}

int getRotationVoltage(int* direction, int* minAngle, int* maxAngle) {
	if(direction > 0) {
		return maxAngle;
	} else {
		return minAngle;
	}
}

void setServoHigh(int timeInNano) {
	int file = open("/sys/class/gpio/gpio44/value", O_RDWR, S_IWRITE | S_IREAD);
	if(file != -1) {
		// File is open
		write(file, "1", 1);
		wasteTime(timeInNano);
	}
}

void setServoLow(int timeInNano) {
	int file = open("/sys/class/gpio/gpio44/value", O_RDWR, S_IWRITE | S_IREAD);
	if(file != -1) {
		// File is open
		write(file, "0", 1);
		wasteTime(timeInNano);
	}
}

void wasteTime(long duration) {
	//Workload for the proccessor
	//number of loops is calculated with magic values
	//9000(outer Loop) and 560(inner Loop)
	float bla = 1.58694;
	long end = duration / 9000;
	long loops = 0;
	#if defined(__QNX__)
	int innerLoop = 560;
	#elif defined(__linux__)
	int innerLoop=40;
	#endif
	for (; loops < end; loops++) {
		int i2 = 0;
		for (; i2 < innerLoop; i2++) {
			bla *= i2;
		}
	}
}
