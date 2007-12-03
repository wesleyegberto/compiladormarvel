// Inclue apenas as declarações das classes utilizadas.
// As classes em si não são necessárias para calcular o tamanho do visitor
// pois seus métodos recebem apenas ponteiros como parâmetro.
// Forward declaration
#ifndef _Visitor_h_included_
#define _Visitor_h_included_

#include "DeclaracaoClassesArvore.h"

class Visitor{
      public:
             virtual void visit(ProgramNode* programNode) = 0;
             virtual void visit(StatementListNode* stmtNode) = 0;
             virtual void visit(NameDeclNode* nameDeclNode) = 0;
             virtual void visit(FragmentNode* fragmentNode) = 0;
             virtual void visit(IfNode* ifNode) = 0;
             virtual void visit(WhileNode* whileNode) = 0;
             virtual void visit(AssignNode* assignNode) = 0;
             virtual void visit(FragCallNode* fragCallNode) = 0;
             virtual void visit(ReadNode* readNode) = 0;
             virtual void visit(WriteNode* writeNode) = 0;
             virtual void visit(ConstantNode* constantNode) = 0;
             virtual void visit(ExpressionListNode* expressionListNode) = 0;
             virtual void visit(CallNode* callNode) = 0;
             virtual void visit(ArrayNode* arrayNode) = 0;
             virtual void visit(RelOpNode* relationalOpNode) = 0;
             virtual void visit(AddOpNode* additionalOpNode) = 0;
             virtual void visit(MultOpNode* multOpNode) = 0;
             virtual void visit(BoolOpNode* boolOpNode) = 0;
             virtual void visit(BitwiseOpNode* bitwiseOpNode) = 0;
             virtual void visit(NotNode* notNode) = 0;
             virtual void visit(NegativeNode* negativeNode) = 0;
             virtual void visit(ModifierListNode* modifierListNode) = 0;
             virtual void visit(ModifierNode* modifierNode) = 0;
             virtual void visit(IdNode* idNode) = 0;
             virtual void visit(IdListNode* idListNode) = 0;
             virtual void visit(NumberNode* numberNode) = 0;
             virtual void visit(LiteralNode* literalNode)= 0;
             
};

#endif
