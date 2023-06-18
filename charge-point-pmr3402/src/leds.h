#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED


#define N_LEDS 7


/************************
 leds_setup
 Configura os leds 
 entradas
   pin i: pino do led i
 saidas
   nenhuma
*************************/
extern void leds_setup(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7);


/************************
 activate_leds
 Liga um led específico e desliga os demais 
 entradas
   n: led que se deseja acender
 saidas
   nenhuma
*************************/
extern void activate_leds(int n);









#endif 