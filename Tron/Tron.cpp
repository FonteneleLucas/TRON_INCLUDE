#include "Tron.h"  
#include <Ultrasonic.h>
#include <EEPROM.h> 
#include<Wire.h>   
#include <dht.h>

dht DHT;
int count_umidade = 0;
int count_temperatura = 0;

Tron::Tron() {
}

/*TABELA SENSORES ALPHA
  Sensor/ID/EEPROM 
  RGB -  1  - 100
  INC -  2  - 101
*/

//###################################-EEPROM-###################################
void Tron::EEPROMWriteInt(int address, int value) {
   byte hiByte = highByte(value);
   byte loByte = lowByte(value);

   EEPROM.write(address, hiByte);
   EEPROM.write(address + 1, loByte);   
}

int Tron::EEPROMReadInt(int address) {
   byte hiByte = EEPROM.read(address);
   byte loByte = EEPROM.read(address + 1);
   
   return word(hiByte, loByte); 
}


//#####################################-LED PORTA-#####################################
void Tron::led_porta(char GATE) {
  switch (GATE){
    case 'A':
      EEPROMWriteInt(100, 1);
      break;
    case 'B':
      EEPROMWriteInt(100, 2);    
      break;
    case 'C':
      EEPROMWriteInt(100, 3);
      break;
    case 'D':
      EEPROMWriteInt(100, 4);
      break;
    default:
        Serial.println("MÓDULO LED: PARÂMETRO INVÁLIDO");  
      break;
  }  
}

//#####################################-LED RGB-#####################################
void Tron::led_rgb(char GATE, int red, int green, int blue) {
  
  led_porta(GATE);

  int gate = EEPROMReadInt(100);

  switch (gate){
    case 1:
      onColor_rgb(red, green, blue, 19, 18, 16);  
      //ligar_RGB(aux, 18, 19, 21);
      break;
    case 2:
      onColor_rgb(red, green, blue, 5, 2, 7); 
      //ligar_RGB(aux, 2, 5, 7);    
      break;
    case 3:
      onColor_rgb(red, green, blue, 9, 12, 8); 
      //ligar_RGB(aux, 9, 8, 12);
      break;
    case 4:
      onColor_rgb(red, green, blue, 10, 11, 13); 
      //ligar_RGB(aux, 9, 8, 12);
      break;
  }  
}

void Tron::onColor_rgb(int red, int green, int blue, int r, int g, int b){

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  digitalWrite(r, red);
  digitalWrite(g, green);
  digitalWrite(b, blue);
}

//#####################################-LED ACENDER-#####################################
void Tron::led_acender(char GATE, String color) {
  
  led_porta(GATE);

  int gate = EEPROMReadInt(100);

  switch (gate){
    case 1:
      onColor(color, 19, 18, 16);  
      //ligar_RGB(aux, 18, 19, 21);
      break;
    case 2:
      onColor(color, 5, 2, 7); 
      //ligar_RGB(aux, 2, 5, 7);    
      break;
    case 3:
      onColor(color, 9, 12, 8); 
      //ligar_RGB(aux, 9, 8, 12);
      break;
    case 4:
      onColor(color, 10, 11, 13); 
      //ligar_RGB(aux, 9, 8, 12);
      break;
  }  
}

void Tron::onColor(String color, int r, int g, int b){

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  if(color == "red"){
    digitalWrite(r, HIGH);
    digitalWrite(g, LOW);
    digitalWrite(b, LOW);
  }
  else if(color == "green"){
     digitalWrite(r, LOW);
      digitalWrite(g, HIGH);
      digitalWrite(b, LOW); 
  }
  else if(color == "blue"){
    digitalWrite(r, LOW);
    digitalWrite(g, LOW);
    digitalWrite(b, HIGH);
  }
  else if(color == "orange"){
    digitalWrite(r, 143);
    digitalWrite(g, 143);
    digitalWrite(b, 189); 
  }
  else{
    Serial.println("COR INVALIDA");
  }
}

//#####################################-LED APAGAR-#####################################
void Tron::led_apagar(char GATE) {
  
  if(GATE == 'A'){
    offColor(19, 18, 16);
  }
  else if(GATE == 'B'){
    offColor(5, 2, 7); 
  }
  else if(GATE == 'C'){
    offColor(9, 12, 8); 
  }
  else if(GATE == 'D'){
    offColor(10, 11, 13); 
  }
}

void Tron::offColor(int r, int g, int b){

  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);

  digitalWrite(r, LOW);
  digitalWrite(g, LOW);
  digitalWrite(b, LOW);
}


//#########################################-BEGIN INCLINAÇÃO-#########################################

bool Tron::inclinacao(char GATE) {

  bool check;
  
  inclinacao_porta(GATE);
  int gate = EEPROMReadInt(105);
  

  switch (gate){
    case 1:
      check = inclinacao_check(16);
      return check;
      break;
    case 2:
      check = inclinacao_check(7);
      return check;
      break;
    case 3:
      check = inclinacao_check(8);
      return check;
      break;
    case 4:
      check = inclinacao_check(13);
      return check;
      break;
  }  
}

void Tron::inclinacao_porta(char GATE) {
  switch (GATE){
    case 'A':
      EEPROMWriteInt(105, 1);
      break;
    case 'B':
      EEPROMWriteInt(105, 2);    
      break;
    case 'C':
      EEPROMWriteInt(105, 3);
      break;
    case 'D':
      EEPROMWriteInt(105, 4);
      break;
    default:
        Serial.println("MÓDULO INCLINAÇÃO: PARÂMETRO INVÁLIDO");  
      break;
  }  
}

bool Tron::inclinacao_check(int pin) {
  pinMode(pin, INPUT); 
  
  if(digitalRead(pin) == HIGH){
    return false;
  }
  else{
    return true;
  }
}

//#########################################-END INCLINAÇÃO-###########################################

//###########################################-BEGIN BUZZER-###########################################

void Tron::buzzer_tocar(char GATE, int RATE) {
 
  buzzer_porta(GATE);
  int gate = EEPROMReadInt(110);  

  switch (gate){
    case 1:
      pinMode(16, OUTPUT);
      tone(16, RATE);   
      break;
    case 2:
      pinMode(7, OUTPUT);
      tone(7, RATE);
      break;
    case 3:
      pinMode(8, OUTPUT);
      tone(8, RATE);
      break;
    case 4:
      pinMode(13, OUTPUT);
      tone(13, RATE);
      break;
  }  
}

void Tron::buzzer_desligar(char GATE) {
 
  switch (GATE){
    case 'A':
      pinMode(16, OUTPUT);
      noTone(16);   
      break;
    case 'B':
      pinMode(7, OUTPUT);
      noTone(7);
      break;
    case 'C':
      pinMode(8, OUTPUT);
      noTone(8);
      break;
    case 'D':
      pinMode(13, OUTPUT);
      noTone(13);
      break;
    default:
        Serial.println("MÓDULO BUZZER: PARÂMETRO INVÁLIDO");  
      break;
  }  
}

void Tron::buzzer_porta(char GATE) {
  switch (GATE){
    case 'A':
      EEPROMWriteInt(110, 1);
      break;
    case 'B':
      EEPROMWriteInt(110, 2);    
      break;
    case 'C':
      EEPROMWriteInt(110, 3);
      break;
    case 'D':
      EEPROMWriteInt(110, 4);
      break;
    default:
        Serial.println("MÓDULO BUZZER: PARÂMETRO INVÁLIDO");  
      break;
  }  
}

//############################################-END BUZZER-############################################

//#########################################-BEGIN SEGUIDOR-#########################################

bool Tron::seguidor_linha(char GATE) {

  bool check;

  seguidor_porta(GATE);
  int gate = EEPROMReadInt(115);
  

  switch (gate){
    case 1:
      check = seguidor_check(16);
      return check;
      break;
    case 2:
      check = seguidor_check(7);
      return check;
      break;
    case 3:
      check = seguidor_check(8);
      return check;
      break;
    case 4:
      check = seguidor_check(13);
      return check;
      break;
  }  
}

void Tron::seguidor_porta(char GATE) {
  switch (GATE){
    case 'A':
      EEPROMWriteInt(115, 1);
      break;
    case 'B':
      EEPROMWriteInt(115, 2);    
      break;
    case 'C':
      EEPROMWriteInt(115, 3);
      break;
    case 'D':
      EEPROMWriteInt(115, 4);
      break;
    default:
        Serial.println("MÓDULO SEGUIDOR: PARÂMETRO INVÁLIDO");  
      break;
  }  
}

bool Tron::seguidor_check(int pin) {
  pinMode(pin, INPUT); 
  
  if(digitalRead(pin) == HIGH){
    return true;
  }
  else{
    return false;
  }
}

//#########################################-END SEGUIDOR-###########################################

//#########################################-BEGIN LASER-#########################################

void Tron::laser_acender(char GATE) {

  laser_porta(GATE);
  int gate = EEPROMReadInt(120);
  
  switch (gate){
    case 1:
      pinMode(16, OUTPUT);
      digitalWrite(16, HIGH); 
      break;
    case 2:
      pinMode(7, OUTPUT);
      digitalWrite(7, HIGH); 
      break;
    case 3:
      pinMode(8, OUTPUT);
      digitalWrite(8, HIGH);
      break;
    case 4:
      pinMode(13, OUTPUT);
      digitalWrite(13, HIGH); 
      break;
  }  
}

void Tron::laser_apagar(char GATE) {
 
  switch (GATE){
    case 'A':
      pinMode(16, OUTPUT);
      digitalWrite(16, LOW);   
      break;
    case 'B':
      pinMode(7, OUTPUT);
      digitalWrite(7, LOW);
      break;
    case 'C':
      pinMode(8, OUTPUT);
      digitalWrite(8, LOW);
      break;
    case 'D':
      pinMode(13, OUTPUT);
      digitalWrite(13, LOW);
      break;
    default:
        Serial.println("MÓDULO LASER: PARÂMETRO INVÁLIDO");  
      break;
  }  
}

void Tron::laser_porta(char GATE) {
  switch (GATE){
    case 'A':
      EEPROMWriteInt(120, 1);
      break;
    case 'B':
      EEPROMWriteInt(120, 2);    
      break;
    case 'C':
      EEPROMWriteInt(120, 3);
      break;
    case 'D':
      EEPROMWriteInt(120, 4);
      break;
    default:
        Serial.println("MÓDULO LASER: PARÂMETRO INVÁLIDO");  
      break;
  }  
}

//#########################################-END LASER-###########################################

//###########################################-BEGIN HUMIDADE/TEMPERATURA-###########################################

float Tron::umidade(char GATE) {
  
  delay(1);

  if(count_umidade >= 2000){
    count_umidade = 0;
    float umidade = 0;

    umidade_porta(GATE);
    int gate = EEPROMReadInt(125); 

    if(gate == 2){
      DHT.read11(14);
      umidade = DHT.humidity;    
      Serial.println(umidade);       
    }
    else if(gate == 3){
      DHT.read11(15);
      umidade = DHT.humidity;
      return umidade;
    }      
  }
  else if(count_umidade < 2000){
    count_umidade++;
  }
}

float Tron::temperatura(char GATE){
  
  //temperatura_porta(GATE);
  //int gate = EEPROMReadInt(130); 
  
  delay(1);

  if(count_temperatura >= 2000){
    count_temperatura = 0;
    float temperatura = 0;

    if(GATE == 'B'){
      DHT.read11(14);
      temperatura = DHT.temperature;    
      return temperatura;       
    }
    else if(GATE == 'C'){
      DHT.read11(15);
      temperatura = DHT.temperature;    
      return temperatura;  
    }      
  }
  else if(count_temperatura < 2000){
    count_temperatura++;
  }
}


void Tron::umidade_porta(char GATE) {
  switch (GATE){
    case 'A':
      EEPROMWriteInt(125, 1);
      break;
    case 'B':
      EEPROMWriteInt(125, 2);    
      break;
    case 'C':
      EEPROMWriteInt(125, 3);
      break;
    case 'D':
      EEPROMWriteInt(125, 4);
      break;
    default:
        Serial.println("MÓDULO UMIDADE: PARÂMETRO INVÁLIDO");  
      break;
  }  
}

void Tron::temperatura_porta(char GATE) {
  switch (GATE){
    case 'A':
      EEPROMWriteInt(130, 1);
      break;
    case 'B':
      EEPROMWriteInt(130, 2);    
      break;
    case 'C':
      EEPROMWriteInt(130, 3);
      break;
    case 'D':
      EEPROMWriteInt(130, 4);
      break;
    default:
        Serial.println("MÓDULO TEMPERATURA: PARÂMETRO INVÁLIDO");  
      break;
  }  
}

//############################################-END HUMIDADE/TEMPERATURA-############################################

//#########################################-BEGIN ULTRASSONICO-#########################################

float Tron::ultrassonico(char GATE) {

  float cm;
  //laser_porta(GATE);
  //int gate = EEPROMReadInt(120);
  
  switch (GATE){
    case 'A':
      cm = ultrassonico_ligar(16, 18); 
      break;
    case 'B':
      cm = ultrassonico_ligar(7, 2); 
      break;
    case 'C':
      cm = ultrassonico_ligar(8, 12); 
      break;
    case 'D':
      cm = ultrassonico_ligar(13, 11); 
      break;
    default:
        Serial.println("MÓDULO ULTRASSÔNICO: PARÂMETRO INVÁLIDO");  
      break;
  }  

  return cm;
}

float Tron::ultrassonico_ligar(int triger, int echo) {

  Ultrasonic ultrasonic(triger, echo);

  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

  
  return cmMsec;
}

//#########################################-END ULTRASSONICO-###########################################

//#########################################-BEGIN ACELEROMETRO-#########################################

int Tron::acelerometro(String parametro) {

  //Endereco I2C do MPU6050
  const int MPU=0x68;

  //Variaveis para armazenar valores dos sensores
  int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0); 
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  if(parametro == "ax"){
    return AcX;
  }
  else if(parametro == "ay"){
    return AcY;
  }
  else if(parametro == "az"){
    return AcZ;
  }
  else if(parametro == "gx"){
    return GyX;
  }
  else if(parametro == "gy"){
    return GyY;
  }
  else if(parametro == "gz"){
    return GyZ;
  }
}

//#########################################-END ACELEROMETRO-###########################################



//#########################################-BEGIN UMIDADE SOLO-#########################################

int Tron::umidade_solo(char GATE) {

  int umidade_solo;
  //laser_porta(GATE);
  //int gate = EEPROMReadInt(120);
  
  switch (GATE){
    case 'A':
      umidade_solo = analogRead(21);
      break;
    case 'B':
      umidade_solo = analogRead(14);
      break;
    case 'C':
      umidade_solo = analogRead(15);
      break;
    case 'D':
      umidade_solo = analogRead(20);
      break;
    case 'E':
      umidade_solo = analogRead(17);
      break;
    default:
        Serial.println("MÓDULO UMIDADE SOLO: PARÂMETRO INVÁLIDO");  
      break;
  }  

  return umidade_solo;
}

//#########################################-END UMIDADE SOLO-###########################################


//#########################################-BEGIN RUIDO-#########################################

bool Tron::ruido(char GATE) {

  bool ruido;
  //laser_porta(GATE);
  //int gate = EEPROMReadInt(120);
  
  switch (GATE){
    case 'A':
      ruido = digitalRead(16);
      break;
    case 'B':
      ruido = digitalRead(7);
      break;
    case 'C':
      ruido = digitalRead(8);
      break;
    default:
        Serial.println("MÓDULO RUÍDO: PARÂMETRO INVÁLIDO");  
      break;
    
  }  

  return ruido;
}

//#########################################-END RUIDO-###########################################

//#########################################-BEGIN PRESENÇA-#########################################

bool Tron::presenca(char GATE) {

  bool presenca;

  switch (GATE){
    case 'A':
      pinMode(16, INPUT);
      presenca = digitalRead(16);
      break;
    case 'B':
      pinMode(7, INPUT);
      presenca = digitalRead(7);
      break;
    case 'C':
      pinMode(8, INPUT);
      presenca = digitalRead(8);
      break;
    default:
        Serial.println("MÓDULO PRESENÇA: PARÂMETRO INVÁLIDO");  
      break;
  }  

  return presenca;
}

//#########################################-END PRESENÇA-###########################################

//#########################################-BEGIN LDR-#########################################

int Tron::ldr(char GATE) {

  int presenca;
  
  switch (GATE){
    case 'A':
      pinMode(21, INPUT);
      presenca = analogRead(21);
      break;
    case 'B':
      pinMode(14, INPUT);
      presenca = analogRead(14);
      break;
    case 'C':
      pinMode(15, INPUT);
      presenca = analogRead(15);
      break;
    case 'D':
      pinMode(20, INPUT);
      presenca = analogRead(20);
      break;
    case 'E':
      pinMode(17, INPUT);
      presenca = analogRead(17);
      break;
    default:
        Serial.println("MÓDULO LDR: PARÂMETRO INVÁLIDO");  
      break;
  }  


  return presenca;
}

//#########################################-END LDR-###########################################

//#########################################-BEGIN CHUVA-#########################################

int Tron::chuva(char GATE) {

  int presenca;

  switch (GATE){
    case 'A':
      pinMode(21, INPUT);
      presenca = analogRead(21);
      break;
    case 'B':
      pinMode(14, INPUT);
      presenca = analogRead(14);
      break;
    case 'C':
      pinMode(15, INPUT);
      presenca = analogRead(15);
      break;
    case 'D':
      pinMode(20, INPUT);
      presenca = analogRead(20);
      break;
    case 'E':
      pinMode(17, INPUT);
      presenca = analogRead(17);
      break;
    default:
        Serial.println("MÓDULO CHUVA: PARÂMETRO INVÁLIDO");  
      break;
  }  

  return presenca;
}

//#########################################-END CHUVA-###########################################
