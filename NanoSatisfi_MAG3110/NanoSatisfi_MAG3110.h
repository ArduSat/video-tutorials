/* 
   NanoSatisfi_MAG3110.h
   
   Jeroen Cappaert and Lara Booth for NanoSatisfi
   27 November 2012
   
   Designed for use with Freescale (C) MAG3110 Magnetometer
   
   Library gathers x,y,z data on current magnetic field
   
   (c) NanoSatisfi 2012
   
   Tested with MAG3110 Breakout from Sparkfun and Arduino Uno
   Based on Sparkfun's example for the MAG3110 breakout board:
      http://dlnmh9ip6v2uc.cloudfront.net/datasheets/BreakoutBoards/Mag3110_v10.pde
   
*/

#ifndef NanoSatisfi_MAG3110_h
#define NanoSatisfi_MAG3110_h

#include <Arduino.h>
#include <Wire.h>


// define magnetometer I2C address (fixed)
#define NS_MAG3110  0x0E // Magnetometer MAG3110 


class NanoSatisfi_MAG3110
{
  public:
    //constructor
    NanoSatisfi_MAG3110();
    
    //public methods
    void configMag(); 
    int readx();
    int ready();
    int readz();
    float x_value();
    float y_value();
    float z_value();
    int getHeading(float x, float y, float z);

  private:
    //class-only methods:
    int read16Data(char r);
    
    //global variables
    float mag_x_scale;
    float mag_y_scale;
    float mag_z_scale;
    
};


#endif
