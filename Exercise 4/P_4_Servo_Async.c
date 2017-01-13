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
	
	char HIGH = '1';
	char LOW = '0';
	
	long MIN_ROTATION_0 = 500;
	long MAX_ROTATION_180 = 2500;
	int movementAngle = (MAX_ROTATION_180 - MIN_ROTATION_0) / 100;
	
	int direction = movementAngle;
	long angle = MIN_ROTATION_0;
	
	while(1) {
		switch(gProfile) {
			case 0:
				close(file);
				return EXIT_SUCCESS;
			case 1:
				// --- Automatic Profile: Linear ---
				rotateServo(file, angle);
				
				if(angle >= MAX_ROTATION_180 || angle <= 0) {
					direction *= -1;
				}
				angle+=direction;
				break;
			case 2:
				// --- Manual Profile ---
				rotateServo(file, gAngle);
				break;
			default:
				wasteTime(200);
				break;
		}
	}
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

void rotateServo(int file, long angleInTime) {
	long TIME_INTERVALL = 20*1000;
	// Set HIGH value
	while(write(file, "1", 1) != 1);
	// Wait specified time
	wasteTime(angleInTime*1000);
	// Set LOW value
	while(write(file, "0", 1) != 1);
	// Wait specified time
	wasteTime((TIME_INTERVALL-angleInTime)*1000);
}

void dump_line( FILE * fp )
{
  int ch;

  while( (ch = fgetc(fp)) != EOF && ch != '\n' )
    /* null body */;
}

int main( void )
{
	gProfile = 3;
	
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
		dump_line(stdin);
		
		if(profile == 0) {
			// Quit
			gProfile = profile;
			printf( "\nQuit" );
			return;
		} else if(profile == 1) {
			// Automatic
			gProfile = profile;
			printf( "\nYou entered the automatic profile: Linear\n");
		} else if(profile == 2) {
			// Manual
			printf( "\nYou entered the manual profile. Enter the angle: ");
			int angle;
			scanf("%d", &angle);
			dump_line(stdin);
			gAngle = angle / 100 * 3000 - 500;
			gProfile = profile;
			printf( "\nThe servo will move to: %d percent angle \n", angle);
		} 
	}
}
