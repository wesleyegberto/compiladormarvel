#include "TabSimbolos.h"
#include <stdlib.h>
#include "Tokens.h"
#include <string.h>
#include "Erro.h"

char *retornaToken(int);

REGISTRO *tabelaSimbolos[HASHPRIME];
ARRAY_LEXEMAS arrayLexemas;
int indiceLexemaAtual;
REGISTRO *registroAtual;

// Inicializa a Tabela de Simbolos
void inicializaTabSimbolos() {
    arrayLexemas.caracteres = (char *) calloc(LEXINI, sizeof(char));
    arrayLexemas.tamanho    = LEXINI;
    arrayLexemas.proxIndice = 0;
    registroAtual = NULL;
    
    // Inicializa tabela de Simbolos com valores nulos
    int i;
    for (i = 0; i < HASHPRIME; i++) tabelaSimbolos[i] = NULL;
    
    // Inicializa palavras chaves
    insereTabSimbolos(INTEGER,"INTEGER");
    insereTabSimbolos(PARAM,"PARAM");
    insereTabSimbolos(VECTOR,"VECTOR");
    insereTabSimbolos(FRAGMENT,"FRAGMENT");
    insereTabSimbolos(ENDFRAGMENT,"ENDFRAGMENT");
    insereTabSimbolos(IF,"IF");
    insereTabSimbolos(ELSE,"ELSE");
    insereTabSimbolos(FLOAT,"FLOAT");
    insereTabSimbolos(WHILE,"WHILE");
    insereTabSimbolos(WRITE,"WRITE");
    insereTabSimbolos(READ,"READ");
   

    
}

// Retorna o indicie da tabela hash
// Retirado do livro C & Data Structures by P.S. Deshpande and O.G. Kakde
int hash(char *key) {
   /**
	 * returns index into hashtable applying hash function. uses shift-folding
	 * followed by mod function for hashing.
	 */
   int i, n, finaln=0;
   char *keyptr;
   const int SHIFTBY = 3;

   for(keyptr=key; *keyptr; finaln+=n)
       for(i=0, n=0; i<SHIFTBY && *keyptr; ++i, ++keyptr)
              n = n*10 + *keyptr;
   finaln %= HASHPRIME;

   return finaln;
}

// Verifica se jแ existe o registro para o lexema na tabela de sํmbolos. Caso
// exista, retorna o mesmo, senใo retorna 0.
REGISTRO *buscaTabSimbolos(char *lexema) {
    int index = hash(lexema);
    if (tabelaSimbolos[index] == NULL) return NULL;

    REGISTRO *registro;
    for(registro = tabelaSimbolos[index]; registro != NULL; registro = registro->prox)
        if (strcmp(&arrayLexemas.caracteres[registro->indiceLexema], lexema) == 0) return registro;

    return NULL;
}

// Insere um lexema na ๚ltima posi็ใo do array de lexemas
void insereArrayLexemas(char *lexema) {
    int tamanhoLexema = strlen(lexema);
    // Se o tamanho do lexema for maior q o tamanho do array, realoca o array
    if (tamanhoLexema + arrayLexemas.proxIndice > arrayLexemas.tamanho) {
        if (LEXINI > (tamanhoLexema + 1)) arrayLexemas.tamanho += LEXINI;
        else arrayLexemas.tamanho += (tamanhoLexema + 1);
        arrayLexemas.caracteres = (char *) realloc(arrayLexemas.caracteres, sizeof(char) * arrayLexemas.tamanho);
        if (arrayLexemas.caracteres == NULL) {
            emiteErroLexico(ERRO_MEMORIA_INSUF, 0);
            exit(1);
        }
    }
        
    int i = 0;
    // Faz a c๓pia caracter a caracter
    while((arrayLexemas.caracteres[arrayLexemas.proxIndice++] = lexema[i++]) != '\0');
}

// Insere o token e respectivo lexema na tabela de sํmbolos
int insereTabSimbolos(int token, char *lexema) {
    // Se existe o lexema na tabela de sํmbolos retorna 0 e armazena o indice do
    // ultimo lexema lido
    REGISTRO *registro;
    if((registro = buscaTabSimbolos(lexema)) != NULL) {
       indiceLexemaAtual = registro->indiceLexema;      // Armazena o indice do lexema lido
       if (registro->token != ID) return 0;
    } else {
       indiceLexemaAtual = arrayLexemas.proxIndice;
       insereArrayLexemas(lexema);
    }

    int index = hash(lexema);                            // Retorna o hash do lexema

    registro = (REGISTRO *) calloc(1, sizeof(REGISTRO)); // Aloca espa็o para o novo registro
    if (registro == NULL) {
        emiteErroLexico(ERRO_MEMORIA_INSUF, 0);
        exit(1);
    }

    // Preenche o registro
    registro->indiceLexema = indiceLexemaAtual;
    registro->token = token;
    registro->ativo = 0;
    registro->escopo = -1;
    registro->prox = tabelaSimbolos[index];              // Aponta o registro atual como pr๓ximo
    registroAtual = registro;
    tabelaSimbolos[index] = registro;                    // Coloca o registro no inicio da fila
    
    indiceLexemaAtual = registro->indiceLexema;          // Armazena indice do lexema atual
    
    return 1;
}

// Finaliza a Tabela de Simbolos
void finalizaTabSimbolos() {
    free(arrayLexemas.caracteres);
    free(tabelaSimbolos);
}

//Imprime a tabela de Simbolos
void imprimeTabSimbolos(){
    printf("\nษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป\n");
    printf("บ                      TABELA DE SIMBOLOS                        บ\n");
    printf("ฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน\n");
    printf("บ %-21s %-30s %-10sบ","Token","Atributo","Numerico");
    printf("\nฬออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออน\n");

    REGISTRO *registro;
    int i;
    for(i = 0; i < HASHPRIME; i++)
        if (tabelaSimbolos[i] != NULL)
            for(registro = tabelaSimbolos[i]; registro != NULL; registro = registro->prox)
                printf("บ %-21s %-30s %-10dบ\n", retornaToken(registro->token), &arrayLexemas.caracteres[registro->indiceLexema], registro->token);
   printf("ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ\n");
}

// Retorna o indice do lexema buscado
int retornaIndiceLexemaAtual() {
   // printf("%s",&arrayLexemas.caracteres[indiceLexemaAtual] );
    return indiceLexemaAtual;
}


// Retorna o registro atual
REGISTRO *retornaRegistroAtual() {
   // printf("%s",&arrayLexemas.caracteres[indiceLexemaAtual] );
    return registroAtual;
}

// Retorna o char correspondente a posi็ao pos
char* retornaCharToken(int pos){
    return &arrayLexemas.caracteres[pos];
}
