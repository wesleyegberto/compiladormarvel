/*
                        AnalisadorLexico
                        
  Description: Módulo referente a implementação do autômato que especifica o 
  analisador léxico do compilador Marvel. Sua principal função é proximoToken()
  que verifica a partir da string de entrada, enviada pelo BufferEntrada, os 
  caracteres a formarem um próximo token. Ao encontrar uma string referente 
  a um token, retorna o valor inteiro respectivo - os valores inteiros dos 
  tokens estão definidos em tokens.h.
*/

/* Definição de valores */
#define SPACE           ' '
#define TAB             '\t'
#define LINE            '\n'
#define RETURN          '\r'

/* Inicializa o analizador Lexico */
void inicializaAnalisadorLexico(char *);

/* Finaliza o analisador Lexico */
void finalizaAnalisadorLexico();

/* Função de reconhecimento de token */
/* A função retorna um inteiro referente a um token especificado em tokens.h */
int proxToken();

/*Função que imprime o token*/
void emitirToken(int, char*);

/*Retorna os caracteres correspondentes ao valor numerico do token */
char *retornaToken(int);

/*
 * Retorna os caracteres correspondentes ao valor numerico do token
 */
char *retornaLiteralToken(int token);

int retornaLinha();
