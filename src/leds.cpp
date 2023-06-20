#include <Arduino.h>

#include "definicoes.h"
#include "leds.h"

int pin_led1;
int pin_led2;
int pin_led3;

// setting PWM properties
//const int freq = 5000;
//const int ledChannel = 0;
//const int resolution = 8;



/************************
 leds_setup
 Configura os leds 
 entradas
   pin i: pinos das cores vermelho, verde e amarelo
 saidas
   nenhuma
*************************/
void leds_setup(int pin1, int pin2, int pin3){
    pin_led1 = pin1;
    pin_led2 = pin2;
    pin_led3 = pin3;
  // attach the channel to the GPIO to be controlled
    pinMode(pin_led1, OUTPUT);
    pinMode(pin_led2, OUTPUT);
    pinMode(pin_led3, OUTPUT);
    digitalWrite(pin_led1, LOW);
    digitalWrite(pin_led2, LOW);
    digitalWrite(pin_led3, LOW);  
}

/************************
 activate_leds
 Acende o led strip uma com uma cor especifica
 entradas
   n: número que indica qual led se deseja acender 
 saidas
   nenhuma
*************************/
void activate_leds(int n){ 
    //int bit0 = (n & 0b001); 
    //int bit1 = (n & 0b010) >> 1;    //poderia se utilizar o bit shift para acender uma cor diferente para cada acao
    //int bit2 = (n & 0b100) >> 2;
    switch(n){
      case 1: // acemnde vermelho
        digitalWrite(pin_led1, HIGH);
        digitalWrite(pin_led2, LOW);
        digitalWrite(pin_led3, LOW);  
        break; 
      case 2:   //acende verde
        digitalWrite(pin_led1, LOW);
        digitalWrite(pin_led2, HIGH);
        digitalWrite(pin_led3, LOW);  
        break; 
      case 3:   //acende amarelo
        digitalWrite(pin_led1, LOW);
        digitalWrite(pin_led2, LOW);
        digitalWrite(pin_led3, HIGH);  
        break;
    }    
 
}





