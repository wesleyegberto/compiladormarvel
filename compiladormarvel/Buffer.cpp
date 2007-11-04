#include "Buffer.h"

/* Entrada do buffer. Caso não tenha um arquivo como parâmetro, receberá o stdin */
FILE *fonte;

/* Buffer duplo de entrada que guardará dados lidos do fonte */
BUFFER_ENTRADA buffer;

/* Lexema */
LEXEMA lexema;

// Recarrega primeira parte do buffer
void recarregaInicioBuffer() {
    if (buffer.recarregado != 1) {
        int lidos = fread(buffer.caracteres, sizeof(char), BSIZE, fonte);
        buffer.recarregado = 1;
        if (feof(fonte)) {
            buffer.caracteres[lidos] = EOF;
        }
    }
}

// Recarrega segunda metade do buffer
void recarregaFinalBuffer() {
    if (buffer.recarregado != 2) {
        int lidos = fread(&buffer.caracteres[BSIZE + 1], sizeof(char), BSIZE, fonte);
        buffer.recarregado = 2;
        if (feof(fonte)) {
            buffer.caracteres[(BSIZE + 1) + lidos] = EOF;
        }
    }
}

// Abre o arquivo fonte para leitura
void carregaFonte(char *arquivo) {
    if (arquivo) {
       if (!(fonte = fopen(arquivo, "r"))) {           // Tenta abrir o parametro
          strcat(arquivo, ".fra");                     // Concatena extensão
          if (!(fonte = fopen(arquivo, "r")))          // Tenta abrir o parametro com extensao
             emiteErroLexico(ERRO_ABRIR_ARQUIVO, 0);   // ERRO ao abrir o parametro informado
       }
    } else fonte = stdin;                              // Sem parametro, lê do stdin
}

// Inicializa o buffer duplo com os valores de EOS no final de cada
// metade do buffer
void inicializaBuffer(char *arquivo) {
     carregaFonte(arquivo);
     
     buffer.caracteres[BSIZE] = EOS;           // Define sentinela no final da primeira metade do buffer
     buffer.indice = -1;                       // Inicializa o indice
     buffer.recarregado = -1;                  // Inicializa variável de controle

     // Inicializa o buffer intermediário de lexema
     lexema.buffer = (char *) calloc(LSIZE, sizeof(char));
     lexema.indice = -1;
     lexema.tamanho = LSIZE;
     
     recarregaInicioBuffer();
}

// Devolve o caractere lido
void devolveCaractere() {
    if (buffer.indice == (BSIZE + 1)) buffer.indice--;
    else if (buffer.indice == 0) buffer.indice = BTOTAL;

    buffer.indice--;
    lexema.indice--;
}

// Retorna o proximo caractere lido para o analisador lexico
char proxCaractere() {
    buffer.indice++;

    if (buffer.caracteres[buffer.indice] == EOS) {
       if (buffer.indice == BSIZE) {                         // Se o indice estiver no final da primeira metade
          recarregaFinalBuffer();                           
          buffer.indice = BSIZE + 1;                         // Aloca para o inicio da segunda metade do buffer
       } else if (buffer.indice == BTOTAL) {                 // Se o indice estiver no final da segunda metade
          recarregaInicioBuffer();
          buffer.indice = 0;                                 // Aloca para o inicio da primeira metade do buffer
       }
    }
    
    return buffer.caracteres[buffer.indice];                 // Retorna o caractere lido
}

// Concatena o caractere no buffer intermediário
void concatenaLexema(char caractere) {
    lexema.indice++;
    if (lexema.indice >= lexema.tamanho) {
        lexema.tamanho += LINCREASE;
        lexema.buffer = (char *) realloc(lexema.buffer, sizeof(char) * (lexema.tamanho));
        if (lexema.buffer == NULL) system("PAUSE");
    }
    lexema.buffer[lexema.indice] = caractere;
}

// Ignora o lexema armazenado
void limpaLexema() {
    lexema.indice = -1;
}

// Retorna o lexema
char *retornaLexema() {
    concatenaLexema(EOS);
    return lexema.buffer;
}

// Finaliza o buffer de entrada
void finalizaBuffer() {
    free(lexema.buffer);
    fclose(fonte);
}
