#include <Arduino.h>

#include "definicoes.h"
#include "leds.h"

int pinR;
int pinG;
int pinB;



/************************
 leds_setup
 Configura os leds 
 entradas
   pin i: pinos das cores vermelho, verde e azul
 saidas
   nenhuma
*************************/
void leds_setup(int pin1, int pin2, int pin3){
    pinR = pin1;
    pinG = pin1;
    pinB = pin1;
    pinMode(pinR, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinG, OUTPUT);    
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
    digitalWrite(pinR, bit0);
    digitalWrite(pinG, bit1);
    digitalWrite(pinB, bit2);    
}



