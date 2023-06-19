#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED


/************************
 leds_setup
 Configura os leds 
 entradas
   pin i: pinos das cores vermelho, verde e azul
 saidas
   nenhuma
*************************/
extern void leds_setup(int pin1, int pin2, int pin3);


/************************
 activate_leds
 Acende o led strip uma com uma cor especifica
 entradas
   n: número cuja representação em binário determina a combinação de cores 
 saidas
   nenhuma
*************************/
extern void activate_leds(int n);









#endif 