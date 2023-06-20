#include <Arduino.h>
#include <PZEM004Tv30.h>
#include "definicoes.h"
#include "pzem.h"

/* Use software serial for the PZEM
 * Pin D1 Rx (Connects to the Tx pin on the PZEM)
 * Pin D2 Tx (Connects to the Rx pin on the PZEM)
*/
PZEM004Tv30 pzem(Serial2, 16, 17);


/************************
 read_power
 Retorna leitura da potência pelo pzem 
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
float read_power(){
    return pzem.power(); //return pzem.power();
}

/************************
 read_power
 Retorna leitura da corrente pelo pzem 
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
float read_current(){
    return pzem.current(); //return pzem.power();
}
/************************
 isPluggged
 Retorna caso o carro esteja sendo carregado
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
int isPlugged(){
    return !isnan(pzem.power());
}
