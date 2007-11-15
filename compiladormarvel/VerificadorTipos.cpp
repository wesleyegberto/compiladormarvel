#include "VerificadorTipos.h"

#define BOOLEAN 0
#define CHAR    1
#define NUMBER  2

/* ----------------------------------------------------------------------------
  Implementação do construtor e dos métodos visitantes da
  classe responsável por verificar o tipo da variável.
  
  Nos casos em que o objeto Node passado para o método visitante tem
  mais de um construtor, os atributos devem ser testados antes do método
  accept(visitor) ser chamado.
  
-----------------------------------------------------------------------------*/

 
// Implementa o construtor da classe de verificacao
VerificadorTipos::VerificadorTipos() {}
/*---------------------------------------------------------------------------*/


// Implementa os métodos visitantes
/*---------------------------------------------------------------------------*/

void VerificadorTipos::visit(AddOpNode* additionalOpNode){
     // Chama o visitante para recuperar o tipo do lado direito
     (additionalOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (additionalOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de diferenca de tipos na operacao adicao
     }
     
     // Verifica se os tipos sao iguais a tipos nao compativeis com a operacao
     if ((tipoExpressionNode1 != INTEGER) || (tipoExpressionNode1 != FLOAT) ||
         (tipoExpressionNode2 != INTEGER) || (tipoExpressionNode2 != FLOAT)){                            
        // Lança ERRO de tipo incompativel com a operacao de adicao
     }
          
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = tipoExpressionNode2;
}

void VerificadorTipos::visit(ArrayNode* arrayNode){
     tipo = arrayNode->idNode->registro->tipo;
}

void VerificadorTipos::visit(AssignNode* assignNode){
     (assignNode->idNode)->accept(this);
      
}

void VerificadorTipos::visit(BitwiseOpNode* bitwiseOpNode){
     // Chamao visitante para recuperar o tipo do lado direito
     (bitwiseOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (bitwiseOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de diferenca de tipos na operacao booleana
     }
     
     // Verifica se os tipos sao compativeis para essa operacao
     if (tipoExpressionNode1 != BOOLEAN || tipoExpressionNode2 != BOOLEAN) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao booleana
     }
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(BoolOpNode* boolOpNode){
     // Chama o visitante para recuperar o tipo do lado direito
     (boolOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (boolOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de diferenca de tipos na operacao booleana
     }
     
     // Verifica se os tipos sao compativeis para essa operacao
     if (tipoExpressionNode1 != BOOLEAN || tipoExpressionNode2 != BOOLEAN) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao booleana
     }
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(CallNode* callNode){
}

void VerificadorTipos::visit(ConstantNode* constantNode){
}

void VerificadorTipos::visit(ExpressionListNode* expressionListNode){
}

void VerificadorTipos::visit(FragCallNode* fragCallNode){
}

void VerificadorTipos::visit(FragmentNode* fragmentNode){
}

void VerificadorTipos::visit(IdListNode* idListNode){
}

void VerificadorTipos::visit(IdNode* idNode){
     tipo = idNode->registro->tipo;
}

void VerificadorTipos::visit(IfNode* ifNode){
}

void VerificadorTipos::visit(LiteralNode* literalNode){
     tipo = CHAR;
}

void VerificadorTipos::visit(ModifierListNode* modifierListNode){
}

void VerificadorTipos::visit(ModifierNode* modifierNode){
}   

void VerificadorTipos::visit(MultOpNode* multOpNode){
     // Chama o visitante para recuperar o tipo do lado direito
     (multOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (multOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de diferenca de tipos na operacao multiplicacao
     }
     
     // Verifica se os tipos sao compativeis para essa operacao
     if ((tipoExpressionNode1 != INTEGER) || 
         (tipoExpressionNode1 != FLOAT) ||
         (tipoExpressionNode2 != INTEGER) ||
         (tipoExpressionNode2 != FLOAT)) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao multiplicacao
     }
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = tipoExpressionNode2;
}

void VerificadorTipos::visit(NameDeclNode* nameDeclNode){
     
      
//     if (tipo <> PARAM) nameDeclNode.idl
     
     
}

void VerificadorTipos::visit(NegativeNode* negativeNode){
     // Chama o visitante para recuperar o tipo da expressao
     (negativeNode->expressionNode->accept(this));
     
     // Recupera o tipo da expressao
     int tipoExpressionNode = tipo;
     
     // Verifica se a expressao retorna um tipo valido para negacao
     if ((tipoExpressionNode != INTEGER) || 
         (tipoExpressionNode != FLOAT) ||
         (tipoExpressionNode != NUM)){
         // Lanca erro de tipo incompativel com operador negativo
     }
     
     // Seta o tipo para o no atual
     tipo = tipoExpressionNode;
}

void VerificadorTipos::visit(NotNode* notNode){
     (notNode->expressionNode->accept(this));
     int tipoNotNode = tipo;
     if (tipoNotNode != BOOLEAN) {
        // Lanca erro de tipo incompativel na comparacao not equal
     }
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(NumberNode* numberNode){
     tipo = numberNode->registro->tipo;
}

void VerificadorTipos::visit(ProgramNode* programNode){
}

void VerificadorTipos::visit(ReadNode* readNode){
}

void VerificadorTipos::visit(RelOpNode* relOpNode){
     // Chama o visitante para recuperar o tipo do lado direito
     (relOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (relOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao relacional
        
     } // else {
          // tipo = BOOLEAN;
          //}
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(StatementListNode* stmtListNode){
}

void VerificadorTipos::visit(WhileNode* whileNode){
}

void VerificadorTipos::visit(WriteNode* writeNode){
}

