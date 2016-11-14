#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
	sleep(2); // Wait for Log-Tracer

	uint8_t led1 = 0, led2 = 0, led3 = 0, led4 = 0;
	int input1, input2;
	sscanf(argv[1], "%d", &input1);
	sscanf(argv[2], "%d", &input2);

	if(input1 >= 1) {
		led1 = 1;
	} else {
		led1 = 0;
	}
	if(input2 >= 1) {
		led2 = 2;
	} else {
		led2 = 0;
	}
	if((led1 >= 1 || led2 >= 1) && !(led1 >= 1 && led2 >= 1)) {
		// Xor Condition
		led3 = 4;
	} else {
		led3 = 0;
	}
	if(led1 >= 1 || led2 >= 1) {
		// Or Condition
		led4 = 8;
	} else {
		led4 = 0;
	}

	int file = open("/dev/leds", O_RDWR, S_IWRITE | S_IREAD);
	if(file != -1) {
		// File is open
		uint8_t g = led4+led3+led2+led1;
		write(file, &g, 1);
	}

	return EXIT_SUCCESS;
}
