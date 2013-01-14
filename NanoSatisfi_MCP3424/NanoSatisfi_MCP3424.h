/* 
    NanoSatisfi_MCP3424.h - Library for MCP3424 returns readings from analog to digital converter
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

#ifndef NanoSatisfi_MCP3424_h
#define NanoSatisfi_MCP3424_h

#include <Arduino.h>
#include <Wire.h>

#define MCP3424_ADDRESS 0X69

// Define configuration register bits and addresses
#define MCP342X_GAIN_FIELD 0X03 // PGA field
#define MCP342X_GAIN_X1    0X00 // PGA gain X1
#define MCP342X_GAIN_X2    0X01 // PGA gain X2
#define MCP342X_GAIN_X4    0X02 // PGA gain X4
#define MCP342X_GAIN_X8    0X03 // PGA gain X8

#define MCP342X_RES_FIELD  0X0C // resolution/rate field
#define MCP342X_RES_SHIFT  2    // shift to low bits
#define MCP342X_12_BIT     0X00 // 12-bit 240 SPS
#define MCP342X_14_BIT     0X04 // 14-bit 60 SPS
#define MCP342X_16_BIT     0X08 // 16-bit 15 SPS
#define MCP342X_18_BIT     0X0C // 18-bit 3.75 SPS

#define MCP342X_CONTINUOUS 0X10 // 1 = continuous, 0 = one-shot

#define MCP342X_CHAN_FIELD 0X60 // channel field
#define MCP342X_CHANNEL_1  0X00 // select MUX channel 1
#define MCP342X_CHANNEL_2  0X20 // select MUX channel 2
#define MCP342X_CHANNEL_3  0X40 // select MUX channel 3
#define MCP342X_CHANNEL_4  0X60 // select MUX channel 4

#define MCP342X_START      0X80 // write: start a conversion
#define MCP342X_BUSY       0X80 // read: output not ready


// constructor
class NanoSatisfi_MCP3424
{
  public:
     // constructor
     NanoSatisfi_MCP3424(byte address, byte gain, byte res);
     // functions
     void MCP3424Write(byte msg);
     int getMvDivisor();
     long readData();
     void setChannel(byte chan);
     double getChannelmV(byte chan);
     // variables
     byte adcConfig;
     uint16_t mvDivisor;
  private:
     // private variables
     byte _address;
     byte _res;
     byte _gain;

};


#endif
