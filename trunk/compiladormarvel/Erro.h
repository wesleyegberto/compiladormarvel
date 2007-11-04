#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definição de códigos de erros */
#define ERRO_GETTOKEN       900
#define ERRO_NUM_DECIMAL    901
#define ERRO_NUM_REAL       902
#define ERRO_EOF_LITERAL    903
#define ERRO_EOF_COMENTARIO 904
#define ERRO_MEMORIA_INSUF  905
#define ERRO_PARAM_INVALIDO 906
#define ERRO_ABRIR_ARQUIVO  907
#define ERRO_TOKEN_ESPERADO 908
#define ERRO_TOKEN_INVALIDO 909

/*
  Recebe o codigo do erro e envia a string respectiva ao stderr.
*/
void emiteErroLexico(int codigo, int linha);

//Envia uma mensagem de erro para stderr
void emiteErroSintatico(int codigo, int token, int linha);
