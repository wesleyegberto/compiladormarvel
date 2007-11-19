/**
*
*           MARVEL COMPILER
*/

#include <cstdlib>
#include <iostream>
#include "Buffer.h"
#include "TabSimbolos.h"
#include "AnalLex.h"
#include "AnalSint.h"
#include "VerificadorEscopo.h"
#include "VerificadorTipos.h"

using namespace std;

int main(int argc, char *argv[])
{
   printf("\t\t     --- MARVEL COMPILER ---\n\n");
   printf("\n");
   printf("\n");
   printf("\n");
   printf("                                   ~\n");
   printf("                  ú         úú        \n");
   printf("                          úú        \n");
   printf("    ú          úú        úúú   \n");
   printf("    úú              úú    ú     úúú   \n");
   printf("    úú              úú    ú    úúú   \n");
   printf("     ú             úú         úúú       \n");
   printf("     úúú                         úú        \n");
   printf("                          úú          úú        \n");
   printf("        úú        úú            úú    úú        \n");
   printf("                  úúú     ú úúú   \n");
   printf("                       ú   ú úúú   \n");
   printf("                ú   úúúú     úúú   \n");
   printf("                ú   ú        úúú       ßÞ\n");
   printf("                      ú   úú           ú\n");
   printf("                      úúú           úúúù\n");
   printf("\n");
   printf("\n");
   printf("\n");
   printf("\n\n\t\t     -----------------------\n\n");

   inicializaAnalisadorLexico(argv[1]);
   
   ProgramNode *ASA = analiseSintatica();

   imprimirASAbstrata(ASA);
       
       // Inicia a verificação de escopo e declaração de variáveis
       VerificadorEscopo* verifEscopo = new VerificadorEscopo();
       ASA->accept(verifEscopo);
       
       // Inicia a verificação de tipos
       VerificadorTipos* verifTipos = new VerificadorTipos();
       ASA->accept(verifTipos);
       
       

   imprimeTabSimbolos();
 
   finalizaAnalisadorLexico();

     system("PAUSE");
   
   return 0;
}
