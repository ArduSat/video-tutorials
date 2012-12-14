/* 
   NanoSatisfi_MLX90614.cpp
   
   Lara Booth (Intern at NanoSatisfi)
   17 October 2012
   
   Designed for use with Melexis (C) MLX90614 Infrared Thermometer
   
   Library gathers temperature data over I2C Bus/SM Bus
   
   (c) NanoSatisfi 2012
   
   Tested with MLX90614 from Sparkfun, 4.7k Ohm pull-up resistors, .1uF capacitor, and Arduino Uno
   
*/

#include "NanoSatisfi_MLX90614.h"

//constructor
NanoSatisfi_MLX90614::NanoSatisfi_MLX90614(){
   //sets common values
   factor = 0.02; // MLX90614 has a resolution of .02
   tempData = 0x0000; //zero out the data
   
   }
   
//modifies tempData into temperature in Kelvin
void NanoSatisfi_MLX90614::rawTemperature(unsigned char r)
{
     int data_low, data_high, pec;
     
     Wire.beginTransmission(NS_MLX90614); //begins transmission with device
     Wire.write(r); //sends register address to read
     Wire.endTransmission(0); //repeated start
     
     Wire.requestFrom(NS_MLX90614, 3); //request three bytes from device
     
     while(Wire.available() <3); //wait for three bytes to become available
     data_low = Wire.read(); //read first byte
     data_high = Wire.read(); //read second byte
     pec = Wire.read(); //read checksum 
     
     Wire.endTransmission(); //terminate transmission
     
     // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
     // Taken from bildr forum on MLX90614
     tempData =(double)(((data_high & 0x007F) << 8) + data_low);
     tempData = (tempData * factor)-0.01; //multiply by resolution and account for error to convert to Kelvin
}

//returns temperature in degrees Celsius
float NanoSatisfi_MLX90614::getTemp()
{
      rawTemperature(0x07); //modify tempData
      return (float) tempData - 273.15; //convert from Kelvin to Celsius
}
    
     
     
