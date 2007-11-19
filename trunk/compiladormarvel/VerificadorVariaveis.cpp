#include "VerificadorVariaveis.h"

/* ----------------------------------------------------------------------------
  Implementação do construtor e dos métodos visitantes da
  classe responsável por verificar a declaracao de variáveis.
  
  Nos casos em que o objeto Node passado para o método visitante tem
  mais de um construtor, os atributos devem ser testados antes do método
  accept(visitor) ser chamado.
  
-----------------------------------------------------------------------------*/

 
// Implementa o construtor da classe de verificacao
VerificadorVariaveis::VerificadorVariaveis() {
   tipoVariavel = 0;
   tamanho = 0;
   offset = 4;
   parametros = 0;
//   in
}
/*---------------------------------------------------------------------------*/


// Implementa os métodos visitantes
/*---------------------------------------------------------------------------*/

void VerificadorVariaveis::visit(AddOpNode* additionalOpNode){
}

void VerificadorVariaveis::visit(ArrayNode* arrayNode){
}

void VerificadorVariaveis::visit(AssignNode* assignNode){
}

void VerificadorVariaveis::visit(BitwiseOpNode* bitwiseOpNode){
}

void VerificadorVariaveis::visit(BoolOpNode* boolOpNode){
}

void VerificadorVariaveis::visit(CallNode* callNode){
}

void VerificadorVariaveis::visit(ConstantNode* constantNode){
}

void VerificadorVariaveis::visit(ExpressionListNode* expressionListNode){
}

void VerificadorVariaveis::visit(FragCallNode* fragCallNode){
}

void VerificadorVariaveis::visit(FragmentNode* fragmentNode){
}

void VerificadorVariaveis::visit(IdListNode* idListNode){
}

void VerificadorVariaveis::visit(IdNode* idNode){
}

void VerificadorVariaveis::visit(IfNode* ifNode){
}

void VerificadorVariaveis::visit(LiteralNode* literalNode){
}

void VerificadorVariaveis::visit(ModifierListNode* modifierListNode){
}

void VerificadorVariaveis::visit(ModifierNode* modifierNode){
}   

void VerificadorVariaveis::visit(MultOpNode* multOpNode){
}

void VerificadorVariaveis::visit(NameDeclNode* nameDeclNode){
}

void VerificadorVariaveis::visit(NegativeNode* negativeNode){
}

void VerificadorVariaveis::visit(NotNode* notNode){
}

void VerificadorVariaveis::visit(NumberNode* numberNode){
}

void VerificadorVariaveis::visit(ProgramNode* programNode){
}

void VerificadorVariaveis::visit(ReadNode* readNode){
}

void VerificadorVariaveis::visit(RelOpNode* relOpNode){
}

void VerificadorVariaveis::visit(StatementListNode* stmtListNode){
}

void VerificadorVariaveis::visit(WhileNode* whileNode){
}

void VerificadorVariaveis::visit(WriteNode* writeNode){
}

