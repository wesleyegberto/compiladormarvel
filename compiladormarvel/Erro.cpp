#include "Erro.h"

char *retornaLiteralToken(int token);

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
#define MSG_TOKEN_ESPERADO(token,linha)             fprintf(stderr, "\nERRO: %s ESPERADO E NAO ENCONTRADO NA INSTRUCAO DA LINHA %d.\n",token,linha)
#define MSG_TOKEN_INVALIDO(token,linha)             fprintf(stderr, "\nERRO: %s NAO ESPERADO VALIDO NA INSTRUCAO DA LINHA %d.\n",token,linha)
#define MSG_ERRO_EOF_SINTATICO(linha)               fprintf(stderr, "\nFIM DE ARQUIVO NAO ESPERADO NA LINHA %d.\n", linha)

/* Definicao de mensagens para erro durante analise semântica */
#define MSG_TIPOS_INCOMPATIVEIS_OPERACAO(string, linha)     fprintf(stderr, "\nERRO: TIPO DO IDENTIFICADOR %s NAO E ESPERADO OU E INCOMPATIVEL COM A OPERACAO NA LINHA %d.\n", string, linha)
#define MSG_TIPOS_INCOMPATIVEIS(linha)                      fprintf(stderr, "\nERRO: TIPOS NAO COMPATIVEIS NA OPERACAO DA LINHA %d.\n", linha)
#define MSG_TIPO_INCOMPATIVEL_INDICE_ARRAY(linha)           fprintf(stderr, "\nERRO: TIPO INCOMPATIVEL COM INDICE DE ARRAY SENDO RETORNADO NA EXPRESSAO OU INSTRUCAO DA LINHA %d. O TIPO ESPERADO E INTEIRO.\n", linha)
#define MSG_TIPO_INCOMPATIVEL_ATRIBUICAO(linha)             fprintf(stderr, "\nERRO: TIPOS INCOMPATIVEIS COM O IDENTIFICADOR DURANTE A ATRIBUICAO NA LINHA %d.\n", linha)
#define MSG_ERRO_EXPRESSAO_NAO_BOOLEANA(linha)              fprintf(stderr, "\nERRO: EXPRESSAO NAO BOOLEANA EM TESTE CONDICIONAL IF NA NA LINHA %d.\n", linha)
#define MSG_ERRO_COMANDO_SEM_EXPRESSAO(string, linha)       fprintf(stderr, "\nERRO: COMANDO %s SEM EXPRESSAO NA LINHA %d.\n", string, linha)
#define MSG_ERRO_TIPO_INCOMPATIVEL_CHAMADA_FRAG(linha)      fprintf(stderr, "\nERRO: TIPO INCOMPATIVEL NA CHAMADA DO FRAGMENTO, LINHA %d.\n", linha)
#define MSG_ERRO_VARIAVEL_NAO_DECLARADA(linha, string)      fprintf(stderr, "\nERRO: VARIAVEL %s NAO DECLARADA NA LINHA %d.\n", string, linha)
#define MSG_ERRO_VARIAVEL_JA_DECLARADA(linha, string)       fprintf(stderr, "\nERRO: VARIAVEL %s NA LINHA %d JA DECLARADA ANTES.\n", string, linha)

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
            MSG_TOKEN_ESPERADO(retornaLiteralToken(token), linha);
            break;
        case(ERRO_TOKEN_INVALIDO): 
            MSG_TOKEN_INVALIDO(retornaLiteralToken(token), linha);
            break;
        case(ERRO_EOF):
            MSG_ERRO_EOF_SINTATICO(linha);
            break;
        } // end switch 
              
} // fim funcao

// Envia uma mensagem de erro para stderr referente a erro semântico
void emiteErroSemantico(int codigo, char* string, int linha){

     switch(codigo) {
         case(ERRO_INCOMPATIBILIDADE_TIPO):
            MSG_TIPOS_INCOMPATIVEIS(linha);
            break;
         case(ERRO_TIPO_NAO_ESPERADO_OPERACAO):
            MSG_TIPOS_INCOMPATIVEIS_OPERACAO(string, linha);
            break;
         case(ERRO_TIPO_INCOMPATIVEL_INDICE_ARRAY):
            MSG_TIPO_INCOMPATIVEL_INDICE_ARRAY(linha);
            break;
         case(ERRO_TIPO_INCOMPATIVEL_ATRIBUICAO):
            MSG_TIPO_INCOMPATIVEL_ATRIBUICAO(linha);                                                                                                                                     
            break;
         case(ERRO_EXPRESSAO_NAO_BOOLEANA):
            MSG_ERRO_EXPRESSAO_NAO_BOOLEANA(linha);
            break;
         case(ERRO_COMANDO_SEM_EXPRESSAO):
            MSG_ERRO_COMANDO_SEM_EXPRESSAO(string, linha);
            break;
         case(ERRO_TIPO_INCOMPATIVEL_CHAMADA_FRAG):
            MSG_ERRO_TIPO_INCOMPATIVEL_CHAMADA_FRAG(linha);
            break;
         case(ERRO_VARIAVEL_NAO_DECLARADA):
            MSG_ERRO_VARIAVEL_NAO_DECLARADA(linha, string);
            break;
         case(ERRO_VARIAVEL_JA_DECLARADA):
            MSG_ERRO_VARIAVEL_JA_DECLARADA(linha, string);
            break;
         } // end switch
} // fim da função
