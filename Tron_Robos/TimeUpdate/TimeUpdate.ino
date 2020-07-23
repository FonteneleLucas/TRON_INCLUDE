/*
    Update Code Time TRON
    by Lucas Fontenele
*/


//Define os pinos para fita de LED
#define GND 3 //O-1
#define RED 5 //O-2 ANTES 5
#define GRE 6 //O-3
#define BLU 9 //O-4

#define pino_trigger    2
#define pino_echo       4

#define pino_trigger_2  7
#define pino_echo_2     8

int s1 = 0;
int s2 = 0;

int s1_max = 0;
int s2_max = 0;

String key = "";

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2);
  pinMode(GND, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GRE, OUTPUT);
  pinMode(BLU, OUTPUT);
  pinMode(pino_trigger, OUTPUT);
  pinMode(pino_trigger_2, OUTPUT);
  pinMode(pino_echo, INPUT);
  pinMode(pino_echo_2, INPUT);

  /*while (true) {
    Serial.print(dist(pino_trigger, pino_echo));
    Serial.print("\t");
    Serial.println(dist(pino_trigger_2, pino_echo_2));
    }*/

}

void loop() {

  if (Serial.available() > 0) {
    key = Serial.readStringUntil('\n');
    Serial.println(key);
  }



  initSensors();



  if (key == "START") {
    calibrar();
    key = "NEXT";
  }

  if (key == "NEXT") {
    green();
  }


  if (key == "FINISH") {
    if (s1 < (s1_max - 1) || s2 < (s2_max - 1)) {
      red();
    } else {
      green();
    }
  }


}

int dist(int trig, int echo) {
  digitalWrite(trig, 1);
  delayMicroseconds(7);
  digitalWrite(trig, 0);
  int duracao = pulseIn(echo, 1);
  int _dist = ((duracao / 2) / 29.411);
  return _dist;
}

void calibrar() {
  int s1 = 0;
  int s2 = 0;
  for (int i = 0; i < 5; i++) {
    int valueS1 = dist(pino_trigger, pino_echo);
    s1 += valueS1;

    Serial.print("CALIBRANDO --- ");
    Serial.print(i);

    Serial.print(" --- Distancia em cm (Sensor 01): ");
    Serial.print(valueS1);

    int valueS2 = dist(pino_trigger_2, pino_echo_2);
    s2 += valueS2;
    Serial.print("  - Distancia em cm (Sensor 02): ");
    Serial.println(valueS2);

    blue();


    delay(1000);


  }
  s1_max = s1 / 5;
  s2_max = s2 / 5;

  Serial.print("Dist MAX (Sensor 01): ");
  Serial.print(s1_max);

  Serial.print("  - Dist MAX (Sensor 02): ");
  Serial.println(s2_max);

}

void initSensors() {
  int v1 = dist(pino_trigger, pino_echo);
  if (v1 <= (s1_max + 1)) {
    s1 = v1;
  }
  Serial.print("Distancia em cm (Sensor 01): ");
  Serial.print(s1);

  int v2 = dist(pino_trigger_2, pino_echo_2);
  if (v2 <= (s2_max + 1)) {
    s2 = v2;
  }
  Serial.print("  - Distancia em cm (Sensor 02): ");
  Serial.println(s2);
}

void green() {
  analogWrite(GND, 255);
  analogWrite(RED, 255);  //OK
  analogWrite(GRE, 0);  //OK
  analogWrite(BLU, 255);
}

void red() {
  digitalWrite(GND, 255);
  digitalWrite(RED, 0);
  digitalWrite(GRE, 255);
  digitalWrite(BLU, 255);
}

void blue() {
  digitalWrite(GND, 255);
  digitalWrite(RED, 255);
  digitalWrite(GRE, 255);
  digitalWrite(BLU, 0);
}
