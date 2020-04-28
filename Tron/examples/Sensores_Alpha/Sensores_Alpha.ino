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

  if (sensor.inclinacao('C')) {
    sensor.led_acender('B', "blue");
    sensor.buzzer_tocar('D', 300);
    sensor.laser_acender('A');    
  }
  else {
    sensor.led_apagar('B');
    sensor.buzzer_desligar('D');
    sensor.laser_apagar('A');
  }
}
