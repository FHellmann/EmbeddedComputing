#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <getopt.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

int gProfile, gAngle;

void* function( void )
{
	int file = open("/sys/class/gpio/gpio44/value", O_RDWR, S_IWRITE | S_IREAD);
	if(file == -1) {
		printf("Error: /sys/class/gpio/gpio44/value");
		return;
	}
	
	long ROTATE_0_HIGH_NANO = 500*1000;
	long ROTATE_0_LOW_NANO = 20*1000000-ROTATE_0_HIGH_NANO;
	long ROTATE_90_HIGH_NANO = 1500*1000;
	long ROTATE_90_LOW_NANO = 20*1000000-ROTATE_90_HIGH_NANO;
	long ROTATE_180_HIGH_NANO = 2500*1000;
	long ROTATE_180_LOW_NANO = 20*1000000-ROTATE_180_HIGH_NANO;
	
	long MIN_ROTATION_0 = 500;
	long MAX_ROTATION_180 = 2500;
	long TIME_INTERVALL = 20*1000000;
	
	int direction = 1;
	long angle = MIN_ROTATION_0;
	
	while(1) {
		switch(gProfile) {
			case 1:
				// --- Linear Profile Start ---
				setServoHigh(file, getRotationAngle(angle));
				setServoLow(file, TIME_INTERVALL - getRotationAngle(angle));
				// --- Linear Profile End ---
				break;
			case 2:
				// --- Manual Profile Start ---
				
				// --- Manual Profile End ---
				break;
			default:
				return EXIT_SUCCESS;
		}
		angle+=direction;
		if(angle >= MAX_ROTATION_180) {
			direction = -1;
		} else if(angle <= 0) {
			direction = 1;
		}
	}
}

int getRotationAngle(int angle) {
	return angle*1000;
}

void wasteTime(long duration) {
	//Workload for the proccessor
	//number of loops is calculated with magic values
	//9000(outer Loop) and 560(inner Loop)
	float bla = 1.58694;
	long end = duration / 9000;
	long loops = 0;
	int innerLoop=40;
	for (; loops < end; loops++) {
		int i2 = 0;
		for (; i2 < innerLoop; i2++) {
			bla *= i2;
		}
	}
}

void setServoHigh(int file, long timeInNanoSleep) {
	write(file, "1", 1);
	wasteTime(timeInNanoSleep);
}

void setServoLow(int file, long timeInNanoSleep) {
	write(file, "0", 1);
	wasteTime(timeInNanoSleep);
}

int main( void )
{
	gProfile = 1;
	
	// Initialise the thread attributes
	pthread_attr_t attr;
	pthread_attr_init( &attr );
	pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );

	// Create thread for user input
	pthread_t th1;
	pthread_create( &th1, &attr, &function, NULL );
	
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
			printf( "\nYou entered the manual profile. Enter the angle: ");
			int angle;
			scanf("%d", &angle);
			gAngle = angle;
			gProfile = profile;
			printf( "\nThe servo will move to: %d percent angle \n", angle);
		} else {
			// Quit
			gProfile = profile;
			printf( "\nQuit" );
			return;
		}
	}
}
