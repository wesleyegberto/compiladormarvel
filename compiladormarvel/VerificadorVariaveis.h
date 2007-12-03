/*
  Arquivo header que define a classe VerificacaoVariaveis, que herda de
  Visitor (é a implementação de Visitor para o caso em que a declaração
  das variáveis é verificada).
*/
#ifndef VERIFICADORVARIAVEIS_H
#define VERIFICADORVARIAVEIS_H

#include "Visitor.h"

// Define os atributos e os métodos visitantes
class VerificadorVariaveis : public Visitor {

      public:
             int    parametros;             // define a quantidade de parametros
             int    offset;                 // offset
//             void*  ponteiro_estrutura_tipo;

      public:
             // Declaração do construtor
             VerificadorVariaveis();
             
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


