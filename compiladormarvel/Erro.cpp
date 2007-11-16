#include "Erro.h"
#include "Anallex.h"

/* Definicao das mensagens para erro durante análise léxica */
#define MSG_ERRO_GETTOKEN(linha)                    fprintf(stderr, "ERRO NO RECONHECIMENTO DO TOKEN NA LINHA %d.\n", linha)
#define MSG_ERRO_NUM_DECIMAL(linha)                 fprintf(stderr, "\nERRO NO RECONHECIMENTO DE UM NUMERO DECIMAL NA LINHA %d.\n", linha)
#define MSG_ERRO_NUM_REAL(linha)                    fprintf(stderr, "\nERRO NO RECONHECIMENTO DE UM NUMERO REAL NA LINHA %d.\n", linha)
#define MSG_ERRO_EOF_LITERAL(linha)                 fprintf(stderr, "\nFIM DE ARQUIVO INESPERADO NO RECONHECIMENTO DE UMA LITERAL NA LINHA %d.\n", linha)
#define MSG_ERRO_EOF_COMENTARIO(linha)              fprintf(stderr, "\nFIM DE ARQUIVO INESPERADO DURANTE COMENTARIO INICIADO NA LINHA %d.\n", linha)
#define MSG_ERRO_MEMORIA_INSUF                      fprintf(stderr, "\nERRO: MEMORIA INSUFICIENTE.\n")
#define MSG_ERRO_PARAM_INVALIDO                     fprintf(stderr, "\nERRO: PARAMETRO INVALIDO NA ALOCACAO DA TABELA.\n")
#define MSG_ERRO_ABRIR_ARQUIVO                      fprintf(stderr, "\nERRO AO ABRIR ARQUIVO.\n")

/* Definicao de mensagens para erro durante análise sintática */
#define MSG_TOKEN_ESPERADO(token,linha)             fprintf(stderr, "\nERRO: %s ESPERADO E NAO ENCONTRADO NA LINHA %d.\n",token,linha)
#define MSG_TOKEN_INVALIDO(token,linha)             fprintf(stderr, "\nERRO: %s NAO E VALIDO NA LINHA %d.\n",token,linha)
#define MSG_ERRO_EOF_SINTATICO(linha)               fprintf(stderr, "\nFIM DE ARQUIVO NAO ESPERADO NA LINHA %d.\n", linha)

/* Definicao de mensagens para erro durante analise semântica */
#define MSG_TIPOS_INCOMPATIVEIS_OPERACAO(operacao, linha)     fprintf(stderr, "\nOS TIPOS SÃO INCOMPATÍVEIS COM A OPERAÇÃO %s NA LINHA %d.\n", linha, operacao)
#define MSG_TIPOS_INCOMPATIVEIS(linha)                              fprintf(stderr, "\nOS TIPOS DA OPERAÇÃO NA LINHA %d SÃO INCOMPATÍVEIS ENTRE SI.\n",linha)

//Envia uma mensagem de erro para stderr referente a erro lexico
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


//Envia uma mensagem de erro para stderr referente a erro sintatico
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

// Envia uma mensagem de erro para stderr referente a erro semântico
void emiteErroSemantico(int codigo, char* operacao, int linha){
     
     switch(codigo) {
         case(ERRO_INCOMPATIBILIDADE_TIPO):
            MSG_TIPOS_INCOMPATIVEIS(linha);
            break;
         case(ERRO_TIPO_NAO_ESPERADOS_OPERACAO):
            MSG_TIPOS_INCOMPATIVEIS_OPERACAO(operacao, linha);
            break;
         } // end switch
} // fim da função
