/*
  Teste sensores - LED, INCLINAÇÃO, BUZZER, LASER.
  Atuador: "C"  
*/

#include <Tron.h>

Tron sensor;

void setup() {
  Serial.begin(9600);
}

void loop() {

  Serial.println(sensor.inclinacao('C'));

  
}
