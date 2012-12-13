#include <SD.h>

const int CS = 8; //varies from slave to slave - chip select is 8 for sparkfun microSD shield

int sensorPin = A0; //we read data over analog input 0

void setup()
{
  Serial.begin(9600);
  
  pinMode(10, OUTPUT); //always set 10 to output
  
  if (!SD.begin(CS)) //check if SD is available
  {
    Serial.println("Card failed...:(");
    return; //end the program here if we can't access the card
  }
  
  //if everything's fine
  Serial.println("Card ready!");
  
}

void loop()
{
  String dataString;
  int lightReading = analogRead(sensorPin);
  
  lightReading = map(lightReading, 0, 1023, 0, 255); //map values from 0-1023 to 0-255
  dataString += String(lightReading);
  dataString += ",";
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE); //open or create a new text file called datalog and set it to WRITE mode
  
  if(dataFile)
  {
    dataFile.println(dataString);
    Serial.println(dataString);
    dataFile.close(); //close dataFile to save data to it
  }
  
  else Serial.println("Unable to access card :(");
  delay(1000);
  
}
  
    
