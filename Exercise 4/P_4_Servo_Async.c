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
#include <time.h>

char HIGH = '1';
char LOW = '0';

long MIN_ROTATION_0 = 500;
long MAX_ROTATION_180 = 2500;

int gProfile, gAngle;

void* function( void )
{
	int file = open("/sys/class/gpio/gpio44/value", O_RDWR, S_IWRITE | S_IREAD);
	if(file == -1) {
		printf("Error: /sys/class/gpio/gpio44/value");
		return;
	}
	
	int direction = (MAX_ROTATION_180 - MIN_ROTATION_0) / 100;
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
				sleep(200);
				break;
		}
	}
}

void sleep(long duration) {
	struct timespec tim;
	tim.tv_sec = 0;
	tim.tv_nsec = duration;
	nanosleep(&tim , (struct timespec *)NULL);
}

void rotateServo(int file, long angleInTime) {
	long TIME_INTERVALL = 20*1000; // 20ms = high + low
	// Set HIGH value
	while(write(file, "1", 1) != 1);
	// Wait specified time
	sleep(angleInTime*1000);
	// Set LOW value
	while(write(file, "0", 1) != 1);
	// Wait specified time
	sleep((TIME_INTERVALL-angleInTime)*1000);
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

		printf( "Choose the profile (0=Quit, 1=Automatic, 2=Manual): ");
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
			printf( "\nAutomatic profile: Linear\n");
		} else if(profile == 2) {
			// Manual
			printf( "\nManual profile. Enter the angle: ");
			int angle;
			scanf("%d", &angle);
			dump_line(stdin);
			gAngle = (angle * 2000) / 100 + 500;
			gProfile = profile;
			printf( "\nThe servo moves to %d percent.\n", angle);
		} 
	}
}
