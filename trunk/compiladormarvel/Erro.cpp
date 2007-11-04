#include "Erro.h"
#include "Anallex.h"

/* Definicao das mensagens */
#define MSG_ERRO_GETTOKEN(linha)        fprintf(stderr, "ERRO NO RECONHECIMENTO DO TOKEN NA LINHA %d.\n", linha)
#define MSG_ERRO_NUM_DECIMAL(linha)     fprintf(stderr, "\nERRO NO RECONHECIMENTO DE UM NUMERO DECIMAL NA LINHA %d.\n", linha)
#define MSG_ERRO_NUM_REAL(linha)        fprintf(stderr, "\nERRO NO RECONHECIMENTO DE UM NUMERO REAL NA LINHA %d.\n", linha)
#define MSG_ERRO_EOF_LITERAL(linha)     fprintf(stderr, "\nFIM DE ARQUIVO INESPERADO NO RECONHECIMENTO DE UMA LITERAL NA LINHA %d.\n", linha)
#define MSG_ERRO_EOF_COMENTARIO(linha)  fprintf(stderr, "\nFIM DE ARQUIVO INESPERADO DURANTE COMENTARIO INICIADO NA LINHA %d.\n", linha)
#define MSG_ERRO_MEMORIA_INSUF          fprintf(stderr, "\nERRO: MEMORIA INSUFICIENTE.\n")
#define MSG_ERRO_PARAM_INVALIDO         fprintf(stderr, "\nERRO: PARAMETRO INVALIDO NA ALOCACAO DA TABELA.\n")
#define MSG_ERRO_ABRIR_ARQUIVO          fprintf(stderr, "\nERRO AO ABRIR ARQUIVO.\n")
#define MSG_TOKEN_ESPERADO(token,linha) fprintf(stderr, "\nERRO: %s ESPERADO E NAO ENCONTRADO NA LINHA %d.\n",token,linha)
#define MSG_TOKEN_INVALIDO(token,linha) fprintf(stderr, "\nERRO: %s NAO E VALIDO NA LINHA %d.\n",token,linha)
#define MSG_ERRO_EOF_SINTATICO(linha)  fprintf(stderr, "\nFIM DE ARQUIVO NAO ESPERADO NA LINHA %d.\n", linha)

//Envia uma mensagem de erro para stderr
void emiteErroLexico(int codigo, int linha){

    switch(codigo) {
        case(ERRO_EOF_LITERAL):
            MSG_ERRO_EOF_LITERAL(linha);
            break;
        case(ERRO_GETTOKEN): 
            MSG_ERRO_GETTOKEN(linha);
            break;
        case(ERRO_NUM_DECIMAL): 
            MSG_ERRO_NUM_DECIMAL(linha);
            break;
        case(ERRO_NUM_REAL): 
            MSG_ERRO_NUM_REAL(linha);
            break; 
        case(ERRO_EOF_COMENTARIO): 
            MSG_ERRO_EOF_COMENTARIO(linha);
            break;
        case(ERRO_MEMORIA_INSUF):
            MSG_ERRO_MEMORIA_INSUF;
            break;
        case(ERRO_PARAM_INVALIDO):
            MSG_ERRO_PARAM_INVALIDO;
            break;
        } // end switch 
              
} // fim funcao


//Envia uma mensagem de erro para stderr
void emiteErroSintatico(int codigo, int token, int linha){

    switch(codigo) {
        case(ERRO_TOKEN_ESPERADO):
            if(token == EOF) MSG_ERRO_EOF_SINTATICO(linha) ;
            else MSG_TOKEN_ESPERADO(retornaLiteralToken(token), linha);
            break;
        case(ERRO_TOKEN_INVALIDO): 
            MSG_TOKEN_INVALIDO(retornaLiteralToken(token), linha);
            break;
        } // end switch 
              
} // fim funcao


