/*
  Arquivo header que define a classe VerificacaoVariaveis, que herda de
  Visitor (é a implementação de Visitor para o caso em que a declaração
  das variáveis é verificada).
*/
#include "Visitor.h"
#include "ClassesArvoreAbstrata.h"
#include "TabSimbolos.h"
#include "Erro.h"
#include <stdio.h>

#ifndef VERIFICADORTIPOS_H
#define VERIFICADORTIPOS_H



// Define os atributos e os métodos visitantes
class VerificadorTipos : public Visitor {
      
      public:
             int tipo;

      public:
             // Declaração do construtor
             VerificadorTipos();
             
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
              void visit(ConstantNode* constantNode);
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


};
#endif
