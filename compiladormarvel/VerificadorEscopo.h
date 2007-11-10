/*
*/
#include "Visitor.h"
#include "ClassesArvoreAbstrata.h"
#include "TabSimbolos.h"
#include <stdio.h>


#ifndef VERIFICADORESCOPO_H
#define VERIFICADORESCOPO_H


// Define os atributos e métodos visitantes.
class VerificadorEscopo : public Visitor {
          public:
             // Declaração do construtor
             VerificadorEscopo();
             
             // Métodos visitantes
              void visit(ProgramNode* programNode);
              void visit(StatementListNode* stmtNode);
              void visit(NameDeclNode* nameDeclNode);
              void visit(FragmentNode* fragmentNode);
              void visit(IfNode* ifNode);
              void visit(WhileNode* whileNode);
              void visit(AssignNode* assignNode);
              void visit(FragCallNode* fragCallNode);
              void visit(ReadNode* readNode);
              void visit(WriteNode* writeNode);
              void visit(ExpressionListNode* expressionListNode);
              void visit(CallNode* callNode);
              void visit(ArrayNode* arrayNode);
              void visit(RelOpNode* relationalOpNode);
              void visit(AddOpNode* additionalOpNode);
              void visit(MultOpNode* multOpNode);
              void visit(BoolOpNode* boolOpNode);
              void visit(BitwiseOpNode* bitwiseOpNode);
              void visit(NotNode* notNode);
              void visit(NegativeNode* negativeNode);
              void visit(ModifierListNode* modifierListNode);
              void visit(ModifierNode* modifierNode);
              void visit(IdNode* idNode);
              void visit(IdListNode* idListNode);
              void visit(NumberNode* numberNode);
              void visit(LiteralNode* literalNode);
              

              void iniciaEscopo();
              void terminaEscopo();
              void insereEscopo();
              void retornaEscopo();
                                       
};
#endif
