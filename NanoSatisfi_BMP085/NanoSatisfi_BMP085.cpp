/* 
   NanoSatisfi_BMP085.cpp
   
   Lara Booth (Intern at NanoSatisfi)
   26 September 2012
   
   Designed for use with Bosch (C) BMP085 sensor
   
   Library gathers pressure, temperature, and altitude data over I2C Bus
   based on instructions specified in BMP085 datasheet
   
   (c) NanoSatisfi 2012
   
   Tested with Sparkfun BMP085 breakout board and Arduino Uno
   and Saleae Logic Analyzer
   
*/

#include "NanoSatisfi_BMP085.h"

//constructor
NanoSatisfi_BMP085::NanoSatisfi_BMP085(){
   //sets common values
   
   p0 = 101325; //standard pressure at sea level
   
   /*oversampling setting
   0 = very low power
   1 = standard
   2 = high
   3 = ultra high resolution*/
   oss = 3; //use ultra high resolution by default
   
   }
   
// set the calibration values
// call method in setup()
void NanoSatisfi_BMP085::calibrateData()
{
     //reads data from specified register for each calibration value
     ac1 = read16Data(0xAA);
     ac2 = read16Data(0xAC);
     ac3 = read16Data(0xAE);
     ac4 = read16Data(0xB0);
     ac5 = read16Data(0xB2);
     ac6 = read16Data(0xB4);
     b1 = read16Data(0xB6);
     b2 = read16Data(0xB8);
     mb = read16Data(0xBA);
     mc = read16Data(0xBC);
     md = read16Data(0xBE);
}

//reads raw temperature
unsigned int NanoSatisfi_BMP085::getRawTemp()
{
     writeData(0xF4, 0x2E); //write a datum to the cntrl register 0xF4
     
     delay(5); //data sheet suggest 4.5ms
     
     return read16Data(0xF6); //return raw temp
}

//reads raw pressure
unsigned long NanoSatisfi_BMP085::getRawPressure()
{
     //declare variable rp for raw pressure (the operation's a little long to include after return)
     unsigned char msb, lsb, xlsb;
     unsigned long rp = 0;
     
     writeData(0xF4, 0x34 + (oss<<6));//write a datum to the cntrl register 0xF4
     delay(2 + (3<<oss)); //wait... dependent on oversampling setting
     
     Wire.beginTransmission(NS_BMP085); //begin transmission
     Wire.write(0xF6); //sends register address to read data from
     Wire.endTransmission(); //terminate transmission 
     
     Wire.requestFrom(NS_BMP085, 3); //request 3 bytes of data from device
     
     while(Wire.available() < 3); //wait for 3 bytes of data to become available
     //read three bytes
     msb = Wire.read(); //from 0xF6
     lsb = Wire.read(); //from 0xF7
     xlsb = Wire.read(); //from 0xF8

     //long calculation for raw pressure (doesn't *need* a varaible...)
     rp = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-oss);
     
     return rp; // return raw pressure
}

//calls getRawTemp() for ease of use;
//calculates temperature from raw temp according to datasheet operations
//call getTemperature() before getPressure() because getTemp..() modifies variable b5 that is also used in getPress..()
short NanoSatisfi_BMP085::getTemperature()
{
     //declare local variables prescribed in datasheet
     long x1, x2;
     unsigned int rt = getRawTemp();
     
     x1 = (((long)rt - (long)ac6)* (long)ac5) >> 15;
     x2 = ((long)mc << 11)/(x1 + md);
     
     b5 = x1 + x2; //calculate (modify) b5
     
     return ((b5 + 8)>>4) * .1; //returns the temperature in degrees Celsius
}

//calls getRawPressure() for ease of use;
//calculates pressure from raw pressure according to datasheet operations
//call getTemperature() before getPressure() because getTemp..() modifies variable b5 that is also used in getPress..()
long NanoSatisfi_BMP085::getPressure()
{
     //declare local variables prescribed in datasheet
     long x1, x2, x3, b3, b6, p;
     unsigned long b4, b7;
     unsigned long rp = getRawPressure();
     
     b6 = b5 - 4000; //calculate b6 (note b5)
     
     //Math (coded from datasheet)
     x1 = (b2 * (b6 * b6)>>12)>>11;
     x2 = (ac2 * b6)>>11;
     x3 = x1 + x2;
     b3 = (((((long)ac1)*4 + x3)<<oss) + 2)>>2; //calculate b3
     x1 = (ac3 * b6)>>13;
     x2 = (b1 * ((b6 * b6)>>12))>>16;
     x3 = ((x1 + x2) + 2)>>2;
     b4 = (ac4 * (unsigned long)(x3 + 32768))>>15; //calculate b4
     b7 = ((unsigned long)(rp - b3) * (50000>>oss)); //calculate b7
     
     p = (b7 < 0x80000000) ? (b7<<1)/b4 : (b7/b4)<<1;
     x1 = (p>>8) * (p>>8);
     x1 = (x1 * 3038)>>16;
     x2 = (-7357 * p)>>16;
     
     p += (x1 + x2 + 3791)>>4; //calculate p
     
     return p; //return pressure
}

//uses standard formula (provided by datasheet) to calculate altitude
//var: average pressure at sea level (p0)
//parameter: need to calculate pressure first - can call getAltitude(getPressure()); or have a variable pressure = getPressure();
long NanoSatisfi_BMP085::getAltitude(long pressure){
     float r = (float) pressure/p0; //create a ratio to simplify the following formula
     return (long) 44330 * (1.0 - pow(r,0.1903));
}

//reads 8 bit data from specified register 
char NanoSatisfi_BMP085::read8Data(unsigned char reg)
{
     Wire.beginTransmission(NS_BMP085); //begins transmission with device
     Wire.write(reg); //sends register address to read
     Wire.endTransmission(); //terminates transmission
     
     Wire.requestFrom(NS_BMP085, 1); //request 1 byte of data from device
     
     while(!Wire.available()); //waits for 1 byte of data to become available
     return Wire.read(); //return byte
}

//reads 16 bit data from specified register 
int NanoSatisfi_BMP085::read16Data(unsigned char reg)
{
     unsigned char msb, lsb;
     
     Wire.beginTransmission(NS_BMP085); //begins transmission with device
     Wire.write(reg); //sends register address to read
     Wire.endTransmission(); //terminates transmission
     
     Wire.requestFrom(NS_BMP085, 2); //request 2 bytes of data from device
     
     while(!Wire.available()); //waits for 2 bytes of data to become available
     msb = Wire.read(); //read first byte
     lsb = Wire.read(); //read second byte
     return ((int)msb<<8 | (int)lsb);
}

//writes data to device
void NanoSatisfi_BMP085::writeData(unsigned char r, unsigned char s)
{
     Wire.beginTransmission(NS_BMP085); //begins transmission with device
     Wire.write(r); //sends register address to read
     Wire.write(s); //writes data to register r
     Wire.endTransmission(); //terminates transmission

}
    
     
     
