/**
*
*           MARVEL COMPILER
*/
#include <stdio.h>
#include <iostream>
#include "DeclaracaoClassesArvore.h"

using namespace std;

void inicializaAnalisadorLexico(char *);
void imprimirASAbstrata(ProgramNode* prgmNode);
ProgramNode* analiseSintatica();
void imprimeTabSimbolos();
void finalizaAnalisadorLexico();

int main(int argc, char *argv[])
{
   printf("\t\t     --- MARVEL COMPILER ---\n\n");
   printf("\n");
   printf("\n");
   printf("\n");
   printf("                                   ~\n");
   printf("                  ת         תת        \n");
   printf("                          תת        \n");
   printf("    ת          תת        תתת   \n");
   printf("    תת              תת    ת     תתת   \n");
   printf("    תת              תת    ת    תתת   \n");
   printf("     ת             תת         תתת       \n");
   printf("     תתת                         תת        \n");
   printf("                          תת          תת        \n");
   printf("        תת        תת            תת    תת        \n");
   printf("                  תתת     ת תתת   \n");
   printf("                       ת   ת תתת   \n");
   printf("                ת   תתתת     תתת   \n");
   printf("                ת   ת        תתת       ßÞ\n");
   printf("                      ת   תת           ת\n");
   printf("                      תתת           תתתש\n");
   printf("\n");
   printf("\n");
   printf("\n");
   printf("\n\n\t\t     -----------------------\n\n");

   inicializaAnalisadorLexico(argv[1]);

   imprimirASAbstrata(analiseSintatica());

   imprimeTabSimbolos();
 
   finalizaAnalisadorLexico();

   system("PAUSE");
   
   return 0;
}
