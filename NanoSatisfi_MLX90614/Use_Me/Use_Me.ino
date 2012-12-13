#include "NanoSatisfi_MLX90614.h"
#include <Wire.h> // include Wire library


NanoSatisfi_MLX90614 mlx;

void setup(){
	Serial.begin(9600); //begin Serial monitor 
        Wire.begin(); //begin Wire
        
	Serial.println("Setup..."); //print message to let user know it's initialized
}

void loop(){
    float celsius = 0;
    
    celsius = mlx.getTemp();
    Serial.print(celsius);
    Serial.println(" * C");

    delay(1000); // wait a second before printing again
}
