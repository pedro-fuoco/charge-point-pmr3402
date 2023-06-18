#include <Arduino.h>

#include "definicoes.h"
#include "leds.h"


int led_pins[N_LEDS];




void leds_setup(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7){
    led_pins[0] = pin1;
    led_pins[1] = pin2;
    led_pins[2] = pin3;
    led_pins[3] = pin4;
    led_pins[4] = pin5;
    led_pins[5] = pin6;
    led_pins[6] = pin7;

    for (int i = 0; i < N_LEDS; i++) {
        pinMode(led_pins[i], OUTPUT);
    }
}


void activate_leds(int n){
    for(int i = 0; i < N_LEDS; i++){
        if(i == n - 1){
            digitalWrite(led_pins[i], HIGH);
        }
        else{
            digitalWrite(led_pins[i], LOW);
        }
    }
}



