#include <Arduino.h>
#include <PZEM004Tv30.h>
#include "definicoes.h"
#include "pzem.h"

/* Use software serial for the PZEM
 * Pin D1 Rx (Connects to the Tx pin on the PZEM)
 * Pin D2 Tx (Connects to the Rx pin on the PZEM)
*/
#if defined(ESP32)
PZEM004Tv30 pzem(Serial2, 16, 17);
#else
PZEM004Tv30 pzem(Serial2);
#endif


/************************
 read_voltage
 Retorna leitura da voltagem pelo pzem 
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
float read_voltage(){
    return pzem.voltage();
}


/************************
 read_current
 Retorna leitura da corrente pelo pzem
 entradas
   nenhuma
 saidas
   nenhuma
*************************/
float read_current(){
    return pzem.current();
}