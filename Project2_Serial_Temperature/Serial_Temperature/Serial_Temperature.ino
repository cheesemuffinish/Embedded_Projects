#include <dht.h>


#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
 
void setup(){
 
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 
}//end "setup()"
 
void loop(){
  //Start of Program 
 
    DHT.read11(dht_apin);
    

    Serial.print("temperature = ");
    Serial.print((DHT.temperature * 1.8) + 32); 
    Serial.println("F  ");
    
    delay(10000);//Wait 10 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop(
