#include "NanoSatisfi_MAG3110.h"
#include <Wire.h>

NanoSatisfi_MAG3110 mag;


void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output (fast)
  mag.configMag();          // turn the MAG3110 on
}


void loop()
{
  float x, y, z;
  int h;
  x = mag.x_value();
  y = mag.y_value();
  z = mag.z_value();
  h = mag.getHeading(x,y,z);
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.println(z);
  Serial.println(h);
  
  delay(1000);
}


