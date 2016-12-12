// See: https://gist.github.com/chrishulbert/1239034#file-adxl345-c

#include <Wire.h>

#define DEVICE (0x53)    // ADXL345 device address when the SDO pin (12) is grounded

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output
  
  // Wake up the accelerometer
  Wire.beginTransmission(DEVICE); // Start talking to the ADXL345 accelerometer on the SEN-10183 board: http://www.sparkfun.com/products/10183
  Wire.send(0x2D); // The address on the accel we want to set: POWER_CTL
  Wire.send(8); // The value on the address: Measure(8)
  Wire.endTransmission(); 
}

void loop()
{
  // Ask the accel to send us it's XYZ values
  Wire.beginTransmission(DEVICE); // Start talking to the ADXL345 accelerometer on the SEN-10183 board: http://www.sparkfun.com/products/10183
  Wire.send(0x32); // The address on the accel we want to read
  Wire.endTransmission();
  
  // Receive the XYZ values
  Wire.requestFrom(DEVICE, 6);
  byte data[6];
  for (int i=0;i<6 && Wire.available();i++) {
    data[i] = Wire.receive();
  }
  Wire.endTransmission();

  // Parse them
  int x = data[0] | (((int)data[1])<<8);
  int y = data[2] | (((int)data[3])<<8);
  int z = data[4] | (((int)data[5])<<8);
  char buf[100];
  sprintf(buf, "x:%d, y:%d, z:%d\r\n", x,y,z);
  Serial.print(buf);

  delay(200);
}

int main(int argc, char *argv[]) {
	sleep(2); // Wait for Log-Tracer
	
	setup();
	loop();

	return EXIT_SUCCESS;
}
