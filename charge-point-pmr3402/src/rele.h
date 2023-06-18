#ifndef RELE_H_INCLUDED
#define RELE_H_INCLUDED


/************************
 rele_setup
 Configura o rele
 entradas
   pin: pino do rele
 saidas
   nenhuma
*************************/
extern void rele_setup(int pin);


/************************
 rele_activate
 Ativa a passagem de corrente pelo relê
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
extern void rele_activate();


/************************
 rele_deactivate
 Impede a passagem de corrente pelo relê
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
extern void rele_deactivate();



#endif