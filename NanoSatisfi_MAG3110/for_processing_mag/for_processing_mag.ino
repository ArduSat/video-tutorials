/* HMC Readout Program for Arduino

Hacked together by Windell H. Oskay

Based on the HMC readout library: 
http://eclecti.cc/hardware/hmc5843-magnetometer-library-for-arduino

*/

#include "NanoSatisfi_MAG3110.h"
#include <Wire.h>

NanoSatisfi_MAG3110 mag;

byte ledPin = 13; // LED connected to digital pin 13
byte delaytime = 50; // There will be new values every n ms

int inByte = 0; // incoming serial byte

void setup()
{

Serial.begin(57600);
delay(50); // The HMC5843 needs 5ms before it will communicate
pinMode(ledPin, OUTPUT); 
mag.configMag();
establishContact();
}

void loop()
{

int x,y,z; 


if (Serial.available() > 0) {
  
  digitalWrite(ledPin, HIGH); // set the LED on 

  x = (int) mag.readx();
  y = (int) mag.ready();
  z = (int) mag.readz();

if (x < 0)
{
x = -x;
x += 32767;
}

if (y < 0)
{
y = -y;
y += 32767;
}

if (z < 0)
{
z = -z;
z += 32767;
}

Serial.write(byte(x >> 8));
Serial.write(byte(x & 255));

Serial.write(byte(y >> 8));
Serial.write(byte(y & 255));

Serial.write(byte(z >> 8));
Serial.write(byte(z & 255)); 

delay(10); // LED on at least 10 ms
digitalWrite(ledPin, LOW); // set the LED off

delay(delaytime - 10); // LED off at least 90 ms
}
}

void establishContact() {
while (Serial.available() <= 0) {
Serial.write('A'); // send a capital A
delay(300);
}
}
