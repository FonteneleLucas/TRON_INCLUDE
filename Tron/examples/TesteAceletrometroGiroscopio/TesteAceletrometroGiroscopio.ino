
#include <Tron.h>

Tron sensor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("   AX:   ");
  Serial.print(sensor.acelerometro("ax"));
  Serial.print("   AY:   ");
  Serial.print(sensor.acelerometro("ay"));
  Serial.print("   AZ:   ");
  Serial.print(sensor.acelerometro("az"));
  Serial.print("   GX:   ");
  Serial.print(sensor.acelerometro("gx"));
  Serial.print("   GY:   ");
  Serial.print(sensor.acelerometro("gy"));
  Serial.print("   GZ:   ");
  Serial.print(sensor.acelerometro("gz"));
  
  Serial.println();
}
