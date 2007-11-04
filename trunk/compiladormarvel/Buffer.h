#include <stdio.h>
#include "Erro.h"

#define EOS                '\0'
#define BSIZE              4096            // Tamanho de caracteres lidos por vez (buffer)
#define BTOTAL             (2 * BSIZE) + 1 // Tamanho total do buffer duplo com 2 sentinelas
#define LSIZE              20              // Tamanho inicial do buffer intermediário
#define LINCREASE          10              // Fator de aumento do buffer intermediário

typedef struct {
    char *buffer;
    int  indice;
    int  tamanho;
} LEXEMA;

typedef struct {
    char caracteres[BTOTAL];
    int  indice;
    int  recarregado;
} BUFFER_ENTRADA;

// Inicializa o buffer duplo com os valores de EOS no final de cada
// metade do buffer
void inicializaBuffer(char *);

// Retorna o proximo caractere lido para o analisador lexico
char proxCaractere();

// Devolve o caractere lido
void devolveCaractere();

// Concatena o caractere no buffer intermediário
void concatenaLexema(char caractere);

// Ignora o lexema armazenado
void limpaLexema();

// Retorna o lexema
char *retornaLexema();

// Finaliza o buffer de entrada
void finalizaBuffer();
