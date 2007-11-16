#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Definição de códigos de erros léxicos */
#define ERRO_GETTOKEN                         900
#define ERRO_NUM_DECIMAL                      901
#define ERRO_NUM_REAL                         902
#define ERRO_EOF_LITERAL                      903
#define ERRO_EOF_COMENTARIO                   904
#define ERRO_MEMORIA_INSUF                    905
#define ERRO_PARAM_INVALIDO                   906
#define ERRO_ABRIR_ARQUIVO                    907

/* Definição de códigos de erros sintáticos */
#define ERRO_TOKEN_ESPERADO                   908
#define ERRO_TOKEN_INVALIDO                   909

/* Definição de códigos de erros semânticos */
#define ERRO_TIPO_NAO_ESPERADO_OPERACAO       910
#define ERRO_INCOMPATIBILIDADE_TIPO           911
#define ERRO_TIPO_INCOMPATIVEL_INDICE_ARRAY   912
#define ERRO_TIPO_INCOMPATIVEL_ATRIBUICAO     913
#define ERRO_EXPRESSAO_NAO_BOOLEANA           914
#define ERRO_COMANDO_SEM_EXPRESSAO            915

// nvia uma mensagem de erro para stderr referente ao erro sintático
void emiteErroLexico(int codigo, int linha);

// Envia uma mensagem de erro para stderr referente ao erro sintático
void emiteErroSintatico(int codigo, int token, int linha);

// Envia uma mensagem de erro para stderr referente ao erro semantico
void emiteErroSematico(int codigo, char* operacao, int linha);


