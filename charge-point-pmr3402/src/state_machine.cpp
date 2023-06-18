#include "definicoes.h"
#include "rele.h"
#include "leds.h"




/***********************************************************************
 Definições dos pinos
 ***********************************************************************/
#define RELE_PIN 0
#define LED1_PIN 1
#define LED2_PIN 2
#define LED3_PIN 3
#define LED4_PIN 4
#define LED5_PIN 5
#define LED6_PIN 6
#define LED7_PIN 7

/***********************************************************************
 Variáveis globais
 ***********************************************************************/
  int codigoEvento = NENHUM_EVENTO;
  int eventoInterno = NENHUM_EVENTO;
  int estado = DESCONECTADO;
  int codigoAcao;
  int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
  int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];


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

  proximo_estado_matrizTransicaoEstados[CARREGAMENTO_PROGRESSO][ATUALIZAR_DADOS] = CARREGAMENTO_PROGRESSO;
  acao_matrizTransicaoEstados[CARREGAMENTO_PROGRESSO][ATUALIZAR_DADOS] = A09;

  proximo_estado_matrizTransicaoEstados[CARREGAMENTO_PROGRESSO][DESPLUGAR_CARRO] = CHECANDO_CARTOES;
  acao_matrizTransicaoEstados[CARREGAMENTO_PROGRESSO][DESPLUGAR_CARRO] = A10;

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
    case A08:
        rele_activate();
        break;
    case A09:
        //ler pzem e calcular energia consumida 
        break;
    case A10:
        rele_deactivate();
        break;
    }
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



int obterEvento()           //completar
{
  int retval = NENHUM_EVENTO;



} // obterEvento


void setup() {
  iniciaSistema();
  rele_setup(RELE_PIN);
  leds_setup(LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN, LED5_PIN, LED6_PIN, LED7_PIN);

}

void loop() {
    codigoEvento = obterEvento();
}