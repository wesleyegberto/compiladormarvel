#include "VerificadorEscopo.h"

/* ----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/

// Nivel de escopo atual
int nivelEscopo;

//Sinalizadores
int estaDeclarando;
int eParametro;
 
// Implementa o construtor da classe de Verificação de Escopo
VerificadorEscopo::VerificadorEscopo(){
    nivelEscopo = -1;
    estaDeclarando = 0;
    eParametro = 0;                                   
}
/*---------------------------------------------------------------------------*/


// Implementa os métodos visitantes, que devem verificar os escopos
/*---------------------------------------------------------------------------*/

void VerificadorEscopo::visit(AddOpNode* additionalOpNode){
     (additionalOpNode->expressionNode1)->accept(this);
     (additionalOpNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(ArrayNode* arrayNode){
     if (arrayNode->idNode) (arrayNode->idNode)->accept(this);
     if (arrayNode->expressionNode) (arrayNode->expressionNode)->accept(this);
}

void VerificadorEscopo::visit(AssignNode* assignNode){
     if (assignNode->idNode) (assignNode->idNode)->accept(this);
     if (assignNode->arrayNode) (assignNode->arrayNode)->accept(this);
     if (assignNode->expressionNode1) (assignNode->expressionNode1)->accept(this);
     if (assignNode->expressionNode2) (assignNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(BitwiseOpNode* bitwiseOpNode){
    (bitwiseOpNode->expressionNode1)->accept(this);
    (bitwiseOpNode->expressionNode2)->accept(this);
    
}

void VerificadorEscopo::visit(BoolOpNode* boolOpNode){
    (boolOpNode->expressionNode1)->accept(this);
    (boolOpNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(CallNode* callNode){
    (callNode->idNode)->accept(this);
    (callNode->expressionListNode)->accept(this);
}


void VerificadorEscopo::visit(ConstantNode* constantNode){
    (constantNode->nameNode)->accept(this);
    (constantNode->value)->accept(this);
}

void VerificadorEscopo::visit(ExpressionListNode* expressionListNode){
    if ((expressionListNode->expressionNode) != NULL )(expressionListNode->expressionNode)->accept(this);
    if ((expressionListNode->expressionListNode) != NULL )(expressionListNode->expressionListNode)->accept(this);  
}

void VerificadorEscopo::visit(FragCallNode* fragCallNode){
    (fragCallNode->idNode)->accept(this);
    (fragCallNode->expressionList)->accept(this);

}

void VerificadorEscopo::visit(FragmentNode* fragmentNode){
    (fragmentNode->statementListNode)->accept(this);
}

void VerificadorEscopo::visit(IdListNode* idListNode){
     if ((idListNode->idListNode) == NULL){ 
         (idListNode->idNode)->accept(this);
     }else{
         (idListNode->idNode)->accept(this);
         (idListNode->idListNode)->accept(this);
     }
}

void VerificadorEscopo::visit(IdNode* idNode){
     
}

void VerificadorEscopo::visit(IfNode* ifNode){
    (ifNode->expressionNode)->accept(this);
    (ifNode->statementNode1)->accept(this);
    (ifNode->statementNode2)->accept(this);
}

void VerificadorEscopo::visit(LiteralNode* literalNode){

}

void VerificadorEscopo::visit(ModifierListNode* modifierListNode){
    if (modifierListNode->modifierNode)(modifierListNode->modifierNode)->accept(this);        
    if (modifierListNode->modifierListNode)(modifierListNode->modifierListNode)->accept(this);    
}

void VerificadorEscopo::visit(ModifierNode* modifierNode){

}   

void VerificadorEscopo::visit(MultOpNode* multOpNode){
    (multOpNode->expressionNode1)->accept(this);
    (multOpNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(NameDeclNode* nameDeclNode){
    if ((nameDeclNode->modifierListNode) != NULL) (nameDeclNode->modifierListNode)->accept(this);
    (nameDeclNode->idListNode)->accept(this);
}

void VerificadorEscopo::visit(NegativeNode* negativeNode){
    (negativeNode->expressionNode)->accept(this);
}

void VerificadorEscopo::visit(NotNode* notNode){
    (notNode->expressionNode)->accept(this);
}

void VerificadorEscopo::visit(NumberNode* numberNode){

}

void VerificadorEscopo::visit(ProgramNode* programNode){
    (programNode->stmtListNode)->accept(this);
}

void VerificadorEscopo::visit(ReadNode* readNode){
     if (readNode->idNode) (readNode->idNode)->accept(this);
     if (readNode->arrayNode) (readNode->arrayNode)->accept(this);
}

void VerificadorEscopo::visit(RelOpNode* relOpNode){
     (relOpNode->expressionNode1)->accept(this);
     (relOpNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(StatementListNode* stmtListNode){
     if ((stmtListNode->statementNode) != NULL) (stmtListNode->statementNode)->accept(this);
     if ((stmtListNode->statementListNode) != NULL) (stmtListNode->statementListNode)->accept(this);

}

void VerificadorEscopo::visit(WhileNode* whileNode){
    (whileNode->expressionNode)->accept(this);
    (whileNode->statementNode)->accept(this);
}

void VerificadorEscopo::visit(WriteNode* writeNode){
    (writeNode->expressionListNode)->accept(this);
}


void VerificadorEscopo::iniciaEscopo(){
     nivelEscopo++;
}

void VerificadorEscopo::terminaEscopo(){
     nivelEscopo--;
     //Varre a tabela de simbolos e coloca o escopo inativo
}

void VerificadorEscopo::insereEscopo(REGISTRO *entrada){
     entrada->escopo = nivelEscopo;
     //busca na tabela de simbolos se já existe escopo senão insere
}

int VerificadorEscopo::retornaEscopo(int nivel){
     
     //busca na tabela de simbolos se já existe escopo
}



