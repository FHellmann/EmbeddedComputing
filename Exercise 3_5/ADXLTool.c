#include <ADXL345.h>

int main(int argc, char *argv[]) {
	sleep(2); // Wait for Log-Tracer
	
	// Wake Up
	ADXL345_SetPowerMode(ADXL345_PCTL_MEASURE);
	
	short x, y, z;
	for(int i = 0; i < 10000; i++) {
		ADXL345_GetXyz(&x, &y, &z);
		printf("Coordinates: X=%hd, Y=%hd, Z=%hd\n", x, y, z);
		sleep(20);
	}
	
	// Sleep
	ADXL345_SetPowerMode(ADXL345_PCTL_SLEEP);

	return EXIT_SUCCESS;
}
