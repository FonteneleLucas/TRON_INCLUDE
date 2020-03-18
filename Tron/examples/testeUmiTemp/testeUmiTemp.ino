/*
  Teste sensor Umidadete/Temperatura
  Porta: B
  Pin: A0
*/


#include "dht.h"
#define dht_apin A0 // Analog Pin sensor is connected to
 
dht DHT;
 
void setup(){
  Serial.begin(9600);
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
}
 
void loop(){
 
    DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(2000);
} 
