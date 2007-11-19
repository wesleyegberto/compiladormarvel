#include "VerificadorVariaveis.h"
#include "ClassesArvoreAbstrata.h"
#include "VerificadorEscopo.h"
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
}
/*---------------------------------------------------------------------------*/


// Implementa os métodos visitantes
/*---------------------------------------------------------------------------*/

void VerificadorVariaveis::visit(AddOpNode* additionalOpNode){}

void VerificadorVariaveis::visit(ArrayNode* arrayNode){}

void VerificadorVariaveis::visit(AssignNode* assignNode){}

void VerificadorVariaveis::visit(BitwiseOpNode* bitwiseOpNode){}

void VerificadorVariaveis::visit(BoolOpNode* boolOpNode){}

void VerificadorVariaveis::visit(CallNode* callNode){
     // Conteudo do metodo
}

void VerificadorVariaveis::visit(ConstantNode* constantNode){}

void VerificadorVariaveis::visit(ExpressionListNode* expressionListNode){}

void VerificadorVariaveis::visit(FragCallNode* fragCallNode){
     // Conteudo do método
}

void VerificadorVariaveis::visit(FragmentNode* fragmentNode){
     // Conteudo do metodo
}

void VerificadorVariaveis::visit(IdListNode* idListNode){
     (idListNode->idNode->accept(this));
     if (idListNode->idListNode) (idListNode->idListNode->accept(this));
}

void VerificadorVariaveis::visit(IdNode* idNode){
     // Conteudo do metodo
}

void VerificadorVariaveis::visit(IfNode* ifNode){}

void VerificadorVariaveis::visit(LiteralNode* literalNode){}

void VerificadorVariaveis::visit(ModifierListNode* modifierListNode){
     (modifierListNode->modifierNode->accept(this));
     if (modifierListNode->modifierListNode) 
        (modifierListNode->modifierListNode->accept(this));
}

void VerificadorVariaveis::visit(ModifierNode* modifierNode){
     // Conteudo do metodo
}   

void VerificadorVariaveis::visit(MultOpNode* multOpNode){}

void VerificadorVariaveis::visit(NameDeclNode* nameDeclNode){
     (nameDeclNode->modifierListNode->accept(this));
     (nameDeclNode->idListNode->accept(this));
}

void VerificadorVariaveis::visit(NegativeNode* negativeNode){}

void VerificadorVariaveis::visit(NotNode* notNode){}

void VerificadorVariaveis::visit(NumberNode* numberNode){
     // Conteúdo do método
}

void VerificadorVariaveis::visit(ProgramNode* programNode){
     // Inicia a criação do escopo
         // Como chamar início de escopo, já que é classe? 
         // iniciaEscopo();
     // Inicia os procedimentos visitantes
     (programNode->stmtListNode->accept(this));
         // Idem chamada de início de escopo Finaliza o escopo
         // finalizaEscopo();
}

void VerificadorVariaveis::visit(ReadNode* readNode){}

void VerificadorVariaveis::visit(RelOpNode* relOpNode){}

void VerificadorVariaveis::visit(StatementListNode* stmtListNode){
     // Conteúdo do método
}

void VerificadorVariaveis::visit(WhileNode* whileNode){}

void VerificadorVariaveis::visit(WriteNode* writeNode){}

