#include "VerificadorEscopo.h"

/* ----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/

// Nivel de escopo atual
int nivelEscopo = 0;
 
// Implementa o construtor da classe de Verificação de Escopo
VerificadorEscopo::VerificadorEscopo(){}
/*---------------------------------------------------------------------------*/


// Implementa os métodos visitantes, que devem verificar os escopos
/*---------------------------------------------------------------------------*/

void VerificadorEscopo::visit(AddOpNode* additionalOpNode){
  
}

void VerificadorEscopo::visit(ArrayNode* arrayNode){

}

void VerificadorEscopo::visit(AssignNode* assignNode){

}

void VerificadorEscopo::visit(BitwiseOpNode* bitwiseOpNode){

}

void VerificadorEscopo::visit(BoolOpNode* boolOpNode){

}

void VerificadorEscopo::visit(CallNode* callNode){

}

void VerificadorEscopo::visit(ComparationOpNode* comparationNode){

}

void VerificadorEscopo::visit(ExpressionListNode* expressionListNode){

}

void VerificadorEscopo::visit(FragCallNode* fragCallNode){

}

void VerificadorEscopo::visit(FragmentNode* fragmentNode){

}

void VerificadorEscopo::visit(IdListNode* idListNode){

}

void VerificadorEscopo::visit(IdNode* idNode){

}

void VerificadorEscopo::visit(IfNode* ifNode){

}

void VerificadorEscopo::visit(LiteralNode* literalNode){

}

void VerificadorEscopo::visit(ModifierListNode* modifierListNode){
 
}

void VerificadorEscopo::visit(ModifierNode* modifierNode){

}   

void VerificadorEscopo::visit(MultOpNode* multOpNode){

}

void VerificadorEscopo::visit(NameDeclNode* nameDeclNode){

}

void VerificadorEscopo::visit(NegativeNode* negativeNode){

}

void VerificadorEscopo::visit(NotNode* notNode){

}

void VerificadorEscopo::visit(NumberNode* numberNode){

}

void VerificadorEscopo::visit(ProgramNode* programNode){

}

void VerificadorEscopo::visit(ReadNode* readNode){

}

void VerificadorEscopo::visit(RelOpNode* relOpNode){

}

void VerificadorEscopo::visit(StatementListNode* stmtListNode){

}

void VerificadorEscopo::visit(WhileNode* whileNode){

}

void VerificadorEscopo::visit(WriteNode* writeNode){

}


void VerificadorEscopo::iniciaEscopo(){
     nivelEscopo++;
}

void VerificadorEscopo::terminaEscopo(){
     nivelEscopo--;
     //Varre a tabela de simbolos e coloca o escopo inativo
}

void VerificadorEscopo::insereEscopo(){
     //busca na tabela de simbolos se já existe escopo senão insere
}

void VerificadorEscopo::retornaEscopo(){
     //busca na tabela de simbolos se já existe escopo
}



