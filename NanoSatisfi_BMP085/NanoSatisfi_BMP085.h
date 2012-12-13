/* 
   NanoSatisfi_BMP085.h
   
   Lara Booth (Intern at NanoSatisfi)
   26 September 2012
   
   Designed for use with Bosch (C) BMP085 sensor
   
   Library gathers pressure, temperature, and altitude data over I2C Bus
   based on instructions specified in BMP085 datasheet
   
   (c) NanoSatisfi 2012
   
   Tested with Sparkfun BMP085 breakout board and Arduino Uno
   and Saleae Logic Analyzer
   
*/

#ifndef NanoSatisfi_BMP085_h
#define NanoSatisfi_BMP085_h

#define NS_BMP085 0x77

#include <Arduino.h>
#include <Wire.h>

class NanoSatisfi_BMP085
{
  public:
    //constructor
    NanoSatisfi_BMP085(); 
    
    //NanoSatisfi_BMP085 methods
    void calibrateData();
    short getTemperature();
    long getPressure();
    long getAltitude(long pressure);
  
  
  private:
    //class-only methods
    char read8Data(unsigned char reg);
    int read16Data(unsigned char reg);
    void writeData(unsigned char r, unsigned char s);
    unsigned int getRawTemp();
    unsigned long getRawPressure();
          
    //global variables
    float p0;
    unsigned int oss;
    
    //calibration values
    int ac1, ac2, ac3, b1, b2, mb, mc, md;
    unsigned int ac4, ac5, ac6;
    
    //used in both getTemperature() and getPressure()
    int b5;
};

#endif
