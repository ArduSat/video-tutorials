#include "NanoSatisfi_MAG3110.h"
#include <Wire.h>

NanoSatisfi_MAG3110 mag; //create an object of NS_MAG

//create x, y, z data arrays
int x[200];
int y[200];
int z[200];
int xmin, xmax, ymax, ymin, zmin, zmax; //minimum and maximum variables for each component



void setup()
{
  Wire.begin();        //start the i2c connection
  Serial.begin(9600);  //begin the serial monitor

  mag.configMag();  // turn the MAG3110 on
  
    //collect 600 (200 each) data on x, y, z 
    //find maximum and minimum (offset) values for x, y, z
    for(int i = 0; i < 200; i++){
     
    //read x, y, z values and add to array
    x[i] = mag.readx();
    y[i] = mag.ready();
    z[i] = mag.readz();
    
    //set initial values for all minimums and maximums
    if(i == 0){
      
      xmin = x[i];
      xmax = x[i];
      
      ymin = y[i];
      ymax = y[i];
      
      zmin = z[i];
      zmax = z[i]; 
    }
  
    //check to see if current datum is the minimum or maximum x-value
    if (xmax < x[i]){xmax = x[i];}
    if (xmin > x[i]){xmin = x[i];}

    //check to see if current datum is the minimum or maximum y-value
    if (ymax < y[i]){ymax = y[i];}
    if (ymin > y[i]){ymin = y[i];}
    
    //check to see if current datum is the minimum or maximum z-value
    if (zmax < z[i]){zmax = z[i];}
    if (zmin > z[i]){zmin = z[i];}
    
    Serial.print("x: "); Serial.print(x[i]); //print the current x-value
    Serial.print(" y: "); Serial.print(y[i]); //print the current y-value
    Serial.print(" z: "); Serial.println(z[i]); //print the current z-value
    delay(100); //delay between each datum
  }
    
  Serial.println();
  
  //print the minimum and maximum x-values
  Serial.print("min x: ");
  Serial.print(xmin);
  Serial.print(" max x: ");
  Serial.println(xmax); 
  
  //print the minimum and maximum y-values
  Serial.print("min y: ");
  Serial.print(ymin);
  Serial.print(" max y: ");
  Serial.println(ymax); 
  
  //print the minimum and maximum z-values
  Serial.print("min z: ");
  Serial.print(zmin);
  Serial.print(" max z: ");
  Serial.println(zmax); 
}

//since we're collecting values from a limited amount of data, there's no need to loop
void loop() 
{
}
