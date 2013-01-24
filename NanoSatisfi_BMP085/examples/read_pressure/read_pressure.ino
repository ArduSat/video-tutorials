/* 
    read_pressure.ino - Returns pressure data from BMP085 sensor over I2C
    Copyright (C) 2012  Lara Booth for NanoSatisfi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.   
*/

#include <Wire.h> //for I2C
#include "NanoSatisfi_BMP085.h"

NanoSatisfi_BMP085 bmp;

void setup(){

  Serial.begin(9600);
  Wire.begin();
  
  bmp.calibrateData(); //set the calibration registers on the sensor
  
}

//print pressure in Pascals
void loop(){
  
  bmp.getTemperature(); //for an accurate reading, we must read temperature before returning pressure
  long pressure = bmp.getPressure(); 
  
  Serial.print("Pressure: ");
  Serial.print(pressure); //print pressure
  Serial.println(" in Pa"); //indictate units
  
  delay(1000); //delay
  
}
