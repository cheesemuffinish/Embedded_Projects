#include <Arduino_FreeRTOS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
  
Adafruit_BNO055 bno = Adafruit_BNO055(55);

void TaskYawPitchRoll( void *pvParameters );
void WireToRPi(void *param);
char yaw[32];
char pitch[32];
char roll[32];
char data[256];

int addr = 0x28;

void setup(void) 
{
  Serial.begin(9600);
  Wire.begin(addr);
  
  while (!Serial) {
    ; // wait for serial port to connect
  }
  
  Serial.println("Orientation Sensor Test"); Serial.println("");

  // Create RTOS Task
  xTaskCreate(TaskYawPitchRoll
    ,  "YawPitchRoll"   // Name
    ,  256  // Stack size
    ,  NULL  
    ,  2  // priority
    ,  NULL );

     // Create RTOS Task
  xTaskCreate(WireToRPi
    ,  "Wire"   // Name
    ,  256  // Stack size
    ,  NULL  
    ,  1  // priority
    ,  NULL );

}
 
void loop(void) 
{
  // Empty on purpose
}

void WireToRPi (void *param) {
  (void) param;
  
  Wire.onRequest(sendM);
  
  for(;;) {}
}

void sendM() {
  Wire.write(data);
}

void TaskYawPitchRoll( void *pvParameters ) {
  (void) pvParameters;

  /* Initialise the sensor */
  while(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    delay(1000);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);

  // Loop
  for(;;) {
    /* Get a new sensor event */ 
    sensors_event_t event; 
    bno.getEvent(&event);
    
    dtostrf(event.orientation.x, 0, 2, yaw);
    dtostrf(event.orientation.y, 0, 2, pitch);
    dtostrf(event.orientation.z, 0, 2, roll);
    sprintf(data, "%s|%s|%s", yaw, pitch, roll);
    Serial.println(data);
    vTaskDelay(5);
  }
}
