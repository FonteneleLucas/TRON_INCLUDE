#include <Tron.h>

Tron sensor;
void setup() {
  Serial.begin(9600);
}

void loop() {

  if (!sensor.inclinacao('C')) {
//    Serial.println("1");
    sensor.led_acender('B', "blue");
    sensor.buzzer('D', 300);
    sensor.lazer('A');
  }
  else {
//    Serial.println("0");
    sensor.led_apagar('B');
    sensor.buzzer_apagar('D');
    sensor.lazer_apagar('A');
  }


  //sensor.umidade('B');
  /*
    if (sensor.inclinacao('C')) {
    sensor.led_acender('D', "blue");
    sensor.buzzer('B', 300);
    sensor.lazer('A');
    }
    else {
    sensor.led_apagar('D');
    sensor.buzzer_apagar('B');
    sensor.lazer_apagar('A');
    }
  */
}
