/* 
    read_ch1.ino - Example reads data from piezo vibration sensor over a MCP3424 ADC
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
#include "NanoSatisfi_MCP3424.h"

#define address 0X69
byte gain = 0; //sets gain to x1
byte resolution = 3; //sets resolution to 18bits

NanoSatisfi_MCP3424 mcp(address, gain, resolution);

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  double CH1 = mcp.getChannelmV(0); //reads data from channel 1
  
  Serial.print("Channel 1: ");
  Serial.print(CH1); //print data
  Serial.println(" mV"); //indicate units
  
  delay(250);
}
  
