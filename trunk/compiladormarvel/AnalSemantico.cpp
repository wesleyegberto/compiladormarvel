#include "AnalSemantico.h"
#include <stdio.h>
#include "VerificadorEscopo.h"
#include "ClassesArvoreAbstrata.h"
#include "VerificadorTipos.h"
#include "VerificadorVariaveis.h"

/*

  Arquivo de implementação do header AnalSemantico, responsável 
  por iniciar e finalizar a análise semântica, tendo suporte do
  padrão Visitor para cada um dos módulos verificadores de regras
  semânticas.

*/

void iniciarAnaliseSemantica(ProgramNode* programNode){
     
     // Verifica se o parâmetro passado não é nulo
     if (programNode != NULL) {
        // Inicia a análise semântica chamando cada uma das classes que implementam regras semânticas
        
        // Verificação de escopo
        VerificadorEscopo* verificadorEscopo = new VerificadorEscopo();
        (programNode->accept(verificadorEscopo));
        
        // Verificação de tipos
        VerificadorTipos* verificadorTipos = new VerificadorTipos();
        (programNode->accept(verificadorTipos));
        
        // Verificação de variáveis
        VerificadorVariaveis* verificadorVariaveis = new VerificadorVariaveis();
        (programNode->accept(verificadorVariaveis));
     }
                          
}

void finalizarAnaliseSemantica(){
     
}
