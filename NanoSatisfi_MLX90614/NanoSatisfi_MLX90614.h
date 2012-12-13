/* 
   NanoSatisfi_MLX90614.h
   
   Lara Booth (Intern at NanoSatisfi)
   17 October 2012
   
   Designed for use with Melexis (C) MLX90614 Infrared Thermometer
   
   Library gathers temperature data over I2C Bus/SM Bus
   
   (c) NanoSatisfi 2012
   
   Tested with MLX90614 from Sparkfun, 4.7k Ohm pull-up resistors, .1uF capacitor, and Arduino Uno
   
*/

#ifndef NanoSatisfi_MLX90614_h
#define NanoSatisfi_MLX90614_h

#define NS_MLX90614 0x5A //I2C address

#include <Arduino.h>
#include <Wire.h>

class NanoSatisfi_MLX90614
{
  public:
  //constructor
  NanoSatisfi_MLX90614(); 
    
  //public methods
  float getTemp();
  
   
  private:
  
  //class-only methods
  void rawTemperature(unsigned char r);
  
  //global variable
  double factor;
  double tempData;
 
};

#endif
