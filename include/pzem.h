#ifndef PZEM_H_INCLUDED
#define PZEM_H_INCLUDED



/************************
 read_power
 Retorna leitura da potência pelo pzem 
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
extern float read_power();
/************************
 read_power
 Retorna leitura da corrente pelo pzem 
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
extern float read_current();
/************************
 isPluggged
 Retorna caso o carro esteja sendo carregado
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
extern int isPlugged();


#endif