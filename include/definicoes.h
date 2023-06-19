#ifndef DEFINICOES_H_INCLUDED
#define DEFINICOES_H_INCLUDED


#define NUM_ESTADOS 5
#define NUM_EVENTOS 9

//ESTADOS 
#define DESCONECTADO 0
#define INOPERATIVO 1
#define CHECANDO_CARTOES 2
#define CARREGAMENTO_LIBERADO 3
#define CARREGAMENTO_PROGRESSO 4





//EVENTOS 
#define NENHUM_EVENTO -1
#define CONECTOU_SERVIDOR 0
#define CONEXAO_FALHA 1
#define TOTEM_LIBERADO 2
#define TOTEM_BLOQUEADO 3
#define CARTAO_INVALIDO 4
#define CARTAO_VALIDO 5
#define CANCELAMENTO 6
#define PLUGAR_CARRO 7
#define DESPLUGAR_CARRO 8



//ACOES 
#define NENHUMA_ACAO -1
#define A01 0 //acender led_strip com 1       
#define A02 1 //acender led_strip com 2     
#define A03 2 //acender led_strip com 3    
#define A04 3 //acender led_strip com 4    
#define A05 4 //acender led_strip com 5    
#define A06 5 //acender led_strip com 6    
#define A07 6 //acender led_strip com 7  
#define A08 7 //liberar rele (evento plugar_carro)
#define A09 8 //desativar o relê (evento desplugar_carro )






#endif 