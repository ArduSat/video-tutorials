#include <Wire.h>
#include "NanoSatisfi_BMP085.h"

NanoSatisfi_BMP085 bmp;

void setup(){
  
  Serial.begin(9600);
  Wire.begin();
  
  bmp.calibrateData();
  
}


void loop(){
  
  long pressure = bmp.getPressure();
  
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" in Pa");
  
  delay(2000);
  
}
