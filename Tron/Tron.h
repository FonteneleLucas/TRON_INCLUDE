#ifndef rgb
#define rgb

#if (ARDUINO >=100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Tron  {
  public: 
    // Constructor
    Tron();

    //LED
    void led_acender(char GATE, String color);
    void led_apagar(char GATE);
    void led_rgb(char GATE, int red, int green, int blue);
    
    //Inclinação
    bool inclinacao(char GATE);
    
    //Buzzer
    void buzzer_tocar(char GATE, int RATE);
    void buzzer_desligar(char GATE);

    //Linha
    bool seguidor_linha(char GATE);

    //Laser
    void laser_acender(char GATE);
    void laser_apagar(char GATE);

    //Umidade/Temperatura
    float umidade(char GATE);
    float temperatura(char GATE);

    //Ultrassônico
    float ultrassonico(char GATE);

    //Acelerometro
    int acelerometro(String parametro);

    //Umidade do solo
    int umidade_solo(char GATE);

    //Ruído
    bool ruido(char GATE);

    //Presença
    bool presenca(char GATE);

    //LDR
    int ldr(char GATE);

    //Chuva
    int chuva(char GATE);

  private:

    //EEPROM
    void EEPROMWriteInt(int address, int value);
    int  EEPROMReadInt(int address);  

    //LED
    void led_porta(char GATE);
    void onColor(String color, int r, int g, int b);
    void offColor(int r, int g, int b);
    void onColor_rgb(int red, int green, int blue, int r, int g, int b);

    //Inclinação
    void inclinacao_porta(char GATE);
    bool inclinacao_check(int pin);

    //Buzzer
    void buzzer_porta(char GATE); 

    //Linha
    void seguidor_porta(char GATE); 
    bool seguidor_check(int pin);

    //Laser
    void laser_porta(char GATE);

    //Umidade/Temperatura
    void umidade_porta(char GATE);
    void temperatura_porta(char GATE);

    //Ultrassônico
    float ultrassonico_ligar(int triger, int echo);
};
#endif
