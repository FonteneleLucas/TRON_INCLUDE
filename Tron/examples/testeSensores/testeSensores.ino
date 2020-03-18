#include <Tron.h>

Tron sensor;

void setup() {
  Serial.begin(9600);
}

void loop() {

  sensor.led_acender('B', "blue");
  delay(1000);
  sensor.led_apagar('B');
  delay(1000);

  sensor.led_acender('B', "red");
  delay(1000);
  sensor.led_apagar('B');
  delay(1000);

  sensor.led_acender('B', "green");
  delay(1000);
  sensor.led_apagar('B');
  delay(1000);
  
}
