/* 
    user_read_adc.ino - Example reads data over a MCP3424 ADC at user-specified gain, resolution, and channel
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
byte gain, resolution, chan;
 
void setup()
  {
    
   Serial.begin(9600); 
   Wire.begin();
   
//prompt user for channel
   do{
       Serial.flush();
       Serial.println();
       Serial.print("Channel? (1, 2, 3, 4) ");
       while (Serial.available() == 0);
       chan = Serial.read() - '1';
   } while (chan < 0 && chan > 3);

//prompt user for gain       
  do{
    Serial.flush();
    Serial.println();
    Serial.print("Gain? (1, 2, 4, or 8) ");
    while(Serial.available() < 1);
    //translate options
    switch (Serial.read()) {
     case '1': gain = 0; break;
     case '2': gain = 1; break;
     case '4': gain = 2; break;
     case '8': gain = 3; break;
    }
   } while (gain < 0 && gain > 3);
   
//prompt user for resolution   
   do {
    Serial.flush();
    Serial.println();
    Serial.print("Resolution? (12, 14, 16, or 18) ");
    while (Serial.available() < 2);
    if (Serial.read() != '1') continue; //filter for important digit
    //translate options
    switch (Serial.read()) {
     case '2': resolution = 0; break;
     case '4': resolution = 1; break;
     case '6': resolution = 2; break;
     case '8': resolution = 3; break;
    }
   } while (resolution < 0 && resolution > 3);

  }

void loop()
{
  NanoSatisfi_MCP3424 mcp(address, gain, resolution);
  double CH = mcp.getChannelmV(chan); //reads data from channel 1
  
  Serial.print("Channel ");
  Serial.print(chan + 1, DEC);
  Serial.print(" : ");
  Serial.print(CH); //print data
  Serial.println(" mV"); //indicate units
  
  delay(250);
}
