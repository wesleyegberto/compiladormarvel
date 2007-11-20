#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Tokens.h"
#include "Erro.h"

#define HASHPRIME           221   /*  tamanho inicial da tabela de simbolos */
#define LEXINI              1024  /*  tamanho inicial do array de lexemas  */

#ifndef REGISTRO_H
#define REGISTRO_H
typedef struct Registro {
    int              indiceLexema;     // Indice do lexema no array de lexemas
    int              token;            // Token do registro
    int              tipo;             // Tipo do Registro
    int              escopo;           // Escopo do Registro
    struct Registro  *param;            // Define a qual registro este esta ligado
    int              offset;           // Offset do Registro
    int              ativo;            //Verifica se a variave esta ativa ou não
    struct Registro  *prox;            // Proximo registro
} REGISTRO;

#endif

#ifndef ARRAY_LEXEMAS_H
#define ARRAY_LEXEMAS_H
typedef struct {
    char  *caracteres;                // Lexema
    int   proxIndice;                 // Proximo indice do array
    int   tamanho;                    // Tamanho atual do array
} ARRAY_LEXEMAS;
#endif

// Inicializa a Tabela de Simbolos
void inicializaTabSimbolos();

// Finaliza a Tabela de Simbolos
void finalizaTabSimbolos();

//Imprime a tabela de Simbolos
void imprimeTabSimbolos();

// Insere o token e respectivo lexema na tabela de símbolos
int insereTabSimbolos(int, char*);

// Verifica se já existe o registro para o lexema na tabela de símbolos. Caso
// exista, retorna o mesmo, senão retorna 0.
REGISTRO *buscaTabSimbolos(char*);

// Retorna o indice do lexema buscado
int retornaIndiceLexemaAtual();

// Retorna o registro atual
REGISTRO *retornaRegistroAtual();

// Retorna o char correspondente a posiçao pos
char* retornaCharToken(int pos);
