/* 
    photo_logger.ino - Example saves and prints data on light intensity from a photoresistor (to an SD card and the Serial monitor, respectively)
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

#include <SD.h> //include the SD card

const int CS = 8; //set chip select pin to 8 for Sparkfun microSD shield
int sensorPin = A0; //analog pin 0
 
void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);

  pinMode(CS, OUTPUT); //set chip select to output   
  pinMode(10, OUTPUT); //set SPI's default CS pin to output
  
  if(!SD.begin(CS)){ 
    //return a failure message if card can't be found
    Serial.println("Card failed :(");
    return;}
    
  //if everything's fine 
  Serial.println("Card ready!"); 
}

void loop() {
  
  int lightReading = analogRead(sensorPin); //read light intensity data
  lightReading = map(lightReading, 0, 1023, 0, 255); // map to 0 to 255
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE); //create or open a datalog file
  
  if(dataFile){ //check for dataFile
    dataFile.print(lightReading); //print to SD
    dataFile.println(",");
    dataFile.close(); //close to save data
    
    Serial.print(lightReading); //print to Serial
    Serial.println(",");
  }
  
  //if dataFile cannot be found
  else Serial.println("unable to access file");
  
  delay(1000);//wait a second
  
}
