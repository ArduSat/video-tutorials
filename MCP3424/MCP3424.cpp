/* 
    MCP3424.cpp - Library for MCP3424 returns readings from analog to digital converter
    Copyright (C) 2012  Jeroen Cappaert for NanoSatisfi

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
    
////////////////////////////////////////////////////////////////////////////////    
          Notes:
          Designed for use with Jeelabs Analog Plug (MCP3424 ADC) 
              
          Make an instance of MCP3423 by:
          MCP3424 ADC1(I2Caddress, gain, resolution)
          - gain values 0-3 represent {x1,x2,x4,x8}
          - resolution 0-3 represents {12bits, 14bits, 16bits, 18bits}

          User functions:
           - setChannel(channelnr.) - for channel 1-4, enter a value 0-1
           - getMvDivisor() - get the conversion value between the ADC value and mV
           - readData() - read data from the I2C channel
           - getChannelmV(channelnr.) - get data in mV directly from the I2C channel chosen by channelnr.
////////////////////////////////////////////////////////////////////////////////   
   
*/

#include "MCP3424.h"

// constructor takes I2C address, required channel, gain and resolution and configures chip.
MCP3424::MCP3424(byte address, byte gain, byte res)
{ 
   _address = address;
   _gain = gain;
   _res = res;
}


// sets channel
void MCP3424::setChannel(byte chan) 
{
  byte adcConfig = MCP342X_START | MCP342X_CHANNEL_1 | MCP342X_CONTINUOUS;
  adcConfig |= chan << 5 | _res << 2 | _gain;
  //writes to a register based on user input (channel, resolution, and gain)
  MCP3424Write(adcConfig);
}


// calculates and returns milliVolt devisor based on gain and resolution.
int MCP3424::getMvDivisor()
{
  int mvDivisor = 1 << (_gain + 2*_res);
  return mvDivisor;
}

// I2C Writes byte to specific register (parameter) on MCP3424 
// REQUIRES hardcoded address - else, does not work
void MCP3424::MCP3424Write(byte r) 
{
 //Serial.println(_address,HEX); //if necessary, use this to check which address we're writing to
 Wire.beginTransmission(_address);
 Wire.write(r);
 Wire.endTransmission(); 
  
}

// Reads data from MCP3424
long MCP3424::readData()
{
  long data;
  // pointer used to form int32 data
  byte *p = (byte *)&data;
  
  // timeout - not really needed?
  long start = millis();
  
  //do-while loop
  do {
    // assume 18-bit mode and addres 0x69
    Wire.requestFrom(MCP3424_ADDRESS, 4);
    if (Wire.available() != 4) {
      Serial.println("read failed");
      return false;
    }
    
    //read three bytes 
    for (int i = 2; i >= 0; i--) {
      p[i] = Wire.read();
    }
    
    // extend sign bits
    p[3] = p[2] & 0X80 ? 0XFF : 0;
    
    // read config/status byte
    byte s = Wire.read();
    if ((s & MCP342X_RES_FIELD) != MCP342X_18_BIT) {
      // not 18 bits - shift bytes for 12, 14, or 16 bits
      p[0] = p[1];
      p[1] = p[2];
      p[2] = p[3];
    }
    if ((s & MCP342X_BUSY) == 0) return data;
  }
  while (millis() - start < 500); //allows rollover of millis()
  Serial.println("read timeout"); 
  return false; 
}

// returns formatted data from MCP3424 from a specific channel (chan: 0, 1, 2, 3)
double MCP3424::getChannelmV(byte chan)
{
  long data;
  setChannel(chan); //sets channel to match parameter 
  int mvDivisor = getMvDivisor(); //sets divisor
  //checks if readData() returns false; reads a datum if not
    if (readData()!=0){ 
    data = readData();
    }
  //if readData() returns false - return error message
    else Serial.println("Read error");
    
  double mv = (double)data/mvDivisor;
  return mv; //returns datum in milliVolts
}



