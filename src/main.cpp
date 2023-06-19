#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include "definicoes.h"
#include "ocpp.h"
#include "rele.h"
#include "leds.h"
#include "pzem.h"
#include "RFID.h"

/***********************************************************************
 Definições dos pinos
 ***********************************************************************/
#define RELE_PIN 27
#define BLUEPIN 25
#define REDPIN 33
#define GREENPIN 32

/***********************************************************************
 Variáveis globais
 ***********************************************************************/
  int codigoEvento = NENHUM_EVENTO;
  int eventoInterno = NENHUM_EVENTO; 
  int estado = DESCONECTADO;
  int codigoAcao;
  int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
  int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
  unsigned long startMillis = 0;
  unsigned long currentMillis = 0;
  const unsigned long interval = 30000; // intervalo de 30s para leituras
  float energia = 0;
  QueueHandle_t xQueue;


void iniciaSistema()
{
  int i;
  int j;

  for (i=0; i < NUM_ESTADOS; i++) {
    for (j=0; j < NUM_EVENTOS; j++) {
       acao_matrizTransicaoEstados[i][j] = NENHUMA_ACAO;
       proximo_estado_matrizTransicaoEstados[i][j] = i;
    }
  }
  proximo_estado_matrizTransicaoEstados[DESCONECTADO][CONECTAR_SERVIDOR] = INOPERATIVO;
  acao_matrizTransicaoEstados[DESCONECTADO][CONECTAR_SERVIDOR] = A01;

  proximo_estado_matrizTransicaoEstados[INOPERATIVO][CONEXAO_FALHA] = DESCONECTADO;
  acao_matrizTransicaoEstados[INOPERATIVO][DESCONECTADO] = A02;

  proximo_estado_matrizTransicaoEstados[INOPERATIVO][TOTEM_LIBERADO] = CHECANDO_CARTOES;
  acao_matrizTransicaoEstados[INOPERATIVO][TOTEM_BLOQUEADO] = A03;

  proximo_estado_matrizTransicaoEstados[INOPERATIVO][TOTEM_BLOQUEADO] = INOPERATIVO;
  acao_matrizTransicaoEstados[INOPERATIVO][TOTEM_BLOQUEADO] = A04;

  proximo_estado_matrizTransicaoEstados[CHECANDO_CARTOES][CARTAO_VALIDO] = CARREGAMENTO_LIBERADO;
  acao_matrizTransicaoEstados[CHECANDO_CARTOES][CARTAO_VALIDO] = A05;

  proximo_estado_matrizTransicaoEstados[CHECANDO_CARTOES][CARTAO_INVALIDO] = CHECANDO_CARTOES;
  acao_matrizTransicaoEstados[CHECANDO_CARTOES][CARTAO_INVALIDO] = A06;

  proximo_estado_matrizTransicaoEstados[CARREGAMENTO_LIBERADO][CANCELAMENTO] = CARREGAMENTO_PROGRESSO;
  acao_matrizTransicaoEstados[CARREGAMENTO_LIBERADO][CANCELAMENTO] = A07;

  proximo_estado_matrizTransicaoEstados[CARREGAMENTO_LIBERADO][PLUGAR_CARRO] = CARREGAMENTO_PROGRESSO;
  acao_matrizTransicaoEstados[CARREGAMENTO_LIBERADO][PLUGAR_CARRO] = A08;

  proximo_estado_matrizTransicaoEstados[CARREGAMENTO_PROGRESSO][DESPLUGAR_CARRO] = CHECANDO_CARTOES;
  acao_matrizTransicaoEstados[CARREGAMENTO_PROGRESSO][DESPLUGAR_CARRO] = A09;

} // initStateMachine



int executarAcao(int codigoAcao)
{
    int retval;

    retval = NENHUM_EVENTO;
    if (codigoAcao == NENHUMA_ACAO)
        return retval;

    switch(codigoAcao)
    {
    case A01:
        activate_leds(1);
        break;
    case A02:
        activate_leds(2);
        break;
    case A03:
        activate_leds(3);
        break;
    case A04:
        activate_leds(4);
        break;
    case A05:
        activate_leds(5);
        break;
    case A06:
        activate_leds(6);
        break;
    case A07:
        activate_leds(7);
        break;
     // switch
    case A08:           //carro plugado - ativar rele e iniciar contagem de tempo
        rele_activate();
        //startMillis = millis();
        break;
    case A09:
        rele_deactivate();
        break;
    }
    return retval;
} // executarAcao


/************************************************************************
 obterAcao
 Obtem uma acao da Matriz de transicao de estados
 Parametros de entrada: estado (int)
                        evento (int)
 Retorno: codigo da acao
*************************************************************************/
int obterAcao(int estado, int codigoEvento) {
  return acao_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao


/************************************************************************
 obterProximoEstado
 Obtem o proximo estado da Matriz de transicao de estados
 Parametros de entrada: estado (int)
                        evento (int)
 Retorno: codigo do estado
*************************************************************************/
int obterProximoEstado(int estado, int codigoEvento) {
  return proximo_estado_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao


void taskMaquinaEstados(void *pvParameters){
  int codigoEvento;

  for( ;; ) {
    if( xQueueReceive( xQueue, &codigoEvento, portMAX_DELAY ) == pdPASS ) {
      if (codigoEvento != NENHUM_EVENTO)
      {
        codigoAcao = obterAcao(estado, codigoEvento);
        estado = obterProximoEstado(estado, codigoEvento);
        executarAcao(codigoAcao);
        Serial.print("Estado: "); Serial.print(estado);
        Serial.print(" Evento: "); Serial.print(codigoEvento);
        Serial.print("Acao: "); Serial.println(codigoAcao);
      }
    }
    else {
      Serial.println("Erro ao receber evento da fila\n");
    }
  }
}

void taskOcpp(void *pvParameters){
  int codigoEvento;
  int operationStatus = 0; // INOPERATIVO
  int pluggedStatus = 0; //DESPLUGADO
  Serial.print(F("[main] Wait for WiFi: "));
  WiFi.begin(STASSID, STAPSK);
  while (!WiFi.isConnected()) {
      Serial.print('.');
      delay(1000);
  }
  Serial.println(F(" connected!"));

  OCPP_initialize(OCPP_HOST, OCPP_PORT, OCPP_URL);
    

  setPowerMeterInput([]() {
    //take the energy register of the main electricity meter and return the value in watt-hours
    return read_power();
  });

  bootNotification("PROTOTIPO-01", "PMR3402", [&codigoEvento] (JsonObject response) {
    if (response["status"].as<String>().equals("Accepted")) {
        codigoEvento = CONECTAR_SERVIDOR;
        xQueueSendToBack( xQueue, &codigoEvento, 0 );
    }
  });

  while(true) // task loop
  {
    if (!WiFi.isConnected())
    {
        codigoEvento = CONEXAO_FALHA;
        xQueueSendToBack( xQueue, &codigoEvento, 0 );
        while (!WiFi.isConnected()) {
            Serial.print('.');
            delay(1000);
        }
        bootNotification("PROTOTIPO-01", "PMR3402", [&codigoEvento] (JsonObject response) {
          if (response["status"].as<String>().equals("Accepted")) {
            codigoEvento = CONECTAR_SERVIDOR;
            xQueueSendToBack( xQueue, &codigoEvento, 0 );
          }
        });
    }

    OCPP_loop();

    if (isOperative() != operationStatus)
    {
      if(isOperative())
      {
        codigoEvento = TOTEM_LIBERADO;
      }
      else
      {
        codigoEvento = TOTEM_BLOQUEADO;
      }
      xQueueSendToBack( xQueue, &codigoEvento, 0 );
    }
    operationStatus = isOperative();


    if (pluggedStatus) //!= isPlugged()
    {
      // if(isPlugged())
      // {
      //   codigoEvento = PLUGAR_CARRO;
      // }
      // else
      // {
      //   codigoEvento = DESPLUGAR_CARRO;
      // }
      // xQueueSendToBack( xQueue, &codigoEvento, 0 );
    }

    if (touchedRFID()) {
        String idTag = "0123456789ABCD"; //e.g. idTag = RFID.readIdTag();
        if (!getTransactionIdTag()) {
            //no idTag registered yet. Start a new transaction
            authorize(idTag.c_str(), [idTag, &codigoEvento] (JsonObject response) {
                //check if user with idTag is authorized
                if (!strcmp("Accepted", response["idTagInfo"]["status"] | "Invalid")){
                    Serial.println(F("[main] User is authorized to start a transaction"));
                    auto ret = beginTransaction(idTag.c_str()); //begin Tx locally
                    codigoEvento = CARTAO_VALIDO;
                    xQueueSendToBack( xQueue, &codigoEvento, 0 );
                    if (ret) {
                        Serial.println(F("[main] Transaction initiated. StartTransaction will be sent when ConnectorPlugged Input becomes true"));
                    } else {
                        Serial.println(F("[main] No transaction initiated"));
                    }
                } else {
                    Serial.printf("[main] Authorize denied. Reason: %s\n", response["idTagInfo"]["status"] | "");
                    codigoEvento = CARTAO_INVALIDO;
                    xQueueSendToBack( xQueue, &codigoEvento, 0 );
                }
            });
            Serial.printf("[main] Authorizing user with idTag %s\n", idTag.c_str());
        } else {
            //Transaction already initiated. Check if to stop current Tx by RFID card
            if (idTag.equals(getTransactionIdTag())) {
                //card matches -> user can stop Tx
                Serial.println(F("[main] End transaction by RFID card"));
                codigoEvento = CANCELAMENTO;
                xQueueSendToBack( xQueue, &codigoEvento, 0 );
                endTransaction();
            } else {
                Serial.println(F("[main] Cannot end transaction by RFID card (different card?)"));
            }
        }
    } 
  }
}


void setup() {
  Serial.begin(115200);

  // setups
  iniciaSistema();
  rele_setup(RELE_PIN);
  leds_setup(REDPIN, BLUEPIN, GREENPIN);
  setupRFID();


  xQueue = xQueueCreate(5, sizeof(int));

  xTaskCreate(taskMaquinaEstados,"taskMaquinaEstados", 1500, NULL, 0, NULL);
  xTaskCreate(taskOcpp,"taskOcpp", 30000, NULL, 0, NULL);
}

void loop()
{
}