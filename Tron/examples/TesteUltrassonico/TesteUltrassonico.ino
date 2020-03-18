/*
  Teste Ultrassônico
  Porta: B
  
*/

#define trig 7
#define echo 2

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  Serial.print("Dist: \t");
  Serial.println(dist());
}

int dist() {
  digitalWrite(trig, 1);
  delayMicroseconds(7);
  digitalWrite(trig, 0);
  int duracao = pulseIn(echo, 1);
  int dist = ((duracao / 2) / 29.411);
  return dist;
}
