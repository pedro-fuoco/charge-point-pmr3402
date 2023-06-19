#include <Arduino.h>

#include "definicoes.h"
#include "leds.h"

int pinR;
int pinG;
int pinB;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;



/************************
 leds_setup
 Configura os leds 
 entradas
   pin i: pinos das cores vermelho, verde e azul
 saidas
   nenhuma
*************************/
void leds_setup(int pin1, int pin2, int pin3){
    // configure LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);
    pinR = pin1;
    pinG = pin2;
    pinB = pin3;
  // attach the channel to the GPIO to be controlled
    ledcAttachPin(pinR, ledChannel);
    ledcAttachPin(pinG, ledChannel);
    ledcAttachPin(pinB, ledChannel);
}

/************************
 activate_leds
 Acende o led strip uma com uma cor especifica
 entradas
   n: número cuja representação em binário determina a combinação de cores 
 saidas
   nenhuma
*************************/
void activate_leds(int n){ // n varia de 1 a 7
    int bit0 = (n & 0b001); 
    int bit1 = (n & 0b010) >> 1;
    int bit2 = (n & 0b100) >> 2;
    int dc0 = (bit0) ? 255:0;    
    int dc1 = (bit1) ? 255:0;
    int dc2 = (bit2) ? 255:0;    
    ledcWrite(pinR, dc0);
    ledcWrite(pinG, dc1);
    ledcWrite(pinB, dc2);    
}





