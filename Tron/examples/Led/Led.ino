/*
  Teste de LED - RGB
  Porta: B
*/

#include <Tron.h>

Tron sensor;

void setup() {
  Serial.begin(9600);
}

void loop() {

  sensor.led_acender('B', "blue");
  delay(500);
  sensor.led_apagar('B');

  sensor.led_acender('B', "red");
  delay(500);
  sensor.led_apagar('B');

  sensor.led_acender('B', "green");
  delay(500);
  sensor.led_apagar('B');

}
