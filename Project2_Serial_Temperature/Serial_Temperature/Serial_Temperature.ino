#include <dht.h>
#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
float previous_value = -1;
int counter = 0;
int stabilization_counter = 0;
int stablization_threshold = 5; //todo maybe change this to a higher number

void setup(){
 
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 
}//end "setup()"

void loop(){
  //Start of Program 
 
    DHT.read11(dht_apin);
    float dht_temperature = DHT.temperature;
    Serial.println(((dht_temperature - 1) * 1.8) + 32); // subtracting a 1 for more accurate temperature results 

    if(dht_temperature == previous_value)
    {
      counter ++;
    }
    else
    {
      counter = 0;
    }
    previous_value = dht_temperature;
    
    if (counter >= stablization_threshold)
    {
      Serial.print("The temperature has been stabalized!");
      stabilization_counter ++;
      if(stabilization_counter > 0)
      {
        Serial.print(((dht_temperature - 1) * 1.8) + 32); // subtracting a 1 for more accurate temperature results 
      }
    }
    delay(10000);//Wait 10 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop(
