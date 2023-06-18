#include <Arduino.h>

#include "definicoes.h"
#include "rele.h"

int rele_pin;

/************************
 rele_setup
 Configura a sirene
 entradas
   pin: pino da sirene
 saidas
   nenhuma
*************************/
void rele_setup(int pin){
    rele_pin = pin;
    pinMode(rele_pin, OUTPUT);
}


/************************
 rele_activate
 Ativa a passagem de corrente pelo relê
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
void rele_activate(){
    digitalWrite(rele_pin, HIGH);
}

/************************
 rele_activate
 Desativa a passagem de corrente pelo relê
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
void rele_deactivate(){
    digitalWrite(rele_pin, LOW);
}