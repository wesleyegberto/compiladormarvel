#include "ClassesArvoreAbstrata.h"
#include <stdio.h>

ProgramNode::ProgramNode(StatementListNode* sln) : stmtListNode(sln) {}
void ProgramNode::accept(Visitor* v) {v->visit(this);}
ProgramNode::~ProgramNode() {delete stmtListNode;}

StatementListNode::StatementListNode(StatementNode* sn) : statementNode(sn), statementListNode(NULL) {}
StatementListNode::StatementListNode(StatementNode* sn, StatementListNode* sln) : statementListNode(sln), statementNode(sn) {}
void StatementListNode::accept(Visitor* v) {v->visit(this);}
StatementListNode::~StatementListNode() {
    delete statementListNode;
    delete statementNode;
}

NameDeclNode::NameDeclNode(ModifierListNode* mln, IdListNode* iln) : modifierListNode(mln), idListNode(iln) {}
void NameDeclNode::accept(Visitor* v) {v->visit(this);}
NameDeclNode::~NameDeclNode() {
    delete modifierListNode;
    delete idListNode;
}

ModifierListNode::ModifierListNode(ModifierNode* mn, ModifierListNode* mln) : modifierNode(mn), modifierListNode(mln) {}
ModifierListNode::ModifierListNode(ModifierNode* mn) : modifierNode(mn), modifierListNode(NULL) {}
void ModifierListNode::accept(Visitor* v) {v->visit(this);}
ModifierListNode::~ModifierListNode() {
    delete modifierNode;
    delete modifierListNode;
}

ModifierNode::ModifierNode(int m) : modifier(m) {}
ModifierNode::ModifierNode(int m, int n) : modifier(m), num(n) {}
void ModifierNode::accept(Visitor* v) {v->visit(this);}


IdListNode::IdListNode(IdNode* in, IdListNode* iln) : idNode(in), idListNode(iln) {}
IdListNode::IdListNode(IdNode* in) : idNode(in), idListNode(NULL) {}
void IdListNode::accept(Visitor* v) {v->visit(this);}
IdListNode::~IdListNode() {
    delete idNode;
    delete idListNode;
}

FragmentNode::FragmentNode(StatementListNode* sln) : statementListNode(sln) {}
void FragmentNode::accept(Visitor* v) {v->visit(this);}
FragmentNode::~FragmentNode() {delete statementListNode;}

IfNode::IfNode(ExpressionNode* en, StatementNode* sn1, StatementNode* sn2) : expressionNode(en), statementNode1(sn1), statementNode2(sn2) {}
void IfNode::accept(Visitor* v) {v->visit(this);}
IfNode::~IfNode() {
    delete expressionNode;
    delete statementNode1;
    delete statementNode2;
}

WhileNode::WhileNode(ExpressionNode* en, StatementNode* sn) : expressionNode(en), statementNode(sn) {}
void WhileNode::accept(Visitor* v) {v->visit(this);}
WhileNode::~WhileNode() {
    delete expressionNode;
    delete statementNode;
}

AssignNode::AssignNode(IdNode* in, ExpressionNode* en1, ExpressionNode* en2) : idNode(in), expressionNode1(en1), expressionNode2(en2) {}
AssignNode::AssignNode(IdNode* in, ExpressionNode* en) : idNode(in), expressionNode1(en), expressionNode2(NULL), arrayNode(NULL) {}
AssignNode::AssignNode(ArrayNode* an, ExpressionNode* en) : arrayNode(an), expressionNode1(en), idNode(NULL), expressionNode2(NULL) {}
void AssignNode::accept(Visitor* v) {v->visit(this);}
AssignNode::~AssignNode() {
    delete arrayNode;
    delete idNode;
    delete expressionNode1;
    delete expressionNode2;
}

FragCallNode::FragCallNode(IdNode* in, ExpressionListNode* eln) : idNode(in), expressionList(eln) {}
void FragCallNode::accept(Visitor* v) {v->visit(this);}
FragCallNode::~FragCallNode() {
    delete idNode;
    delete expressionList;
}

ReadNode::ReadNode(ArrayNode* an) : arrayNode(an) {}
ReadNode::ReadNode(IdNode* in) : idNode(in) {}
ReadNode::ReadNode(ExpressionListNode* eln) : expressionListNode(eln) {}
void ReadNode::accept(Visitor* v) {v->visit(this);}
ReadNode::~ReadNode() {
    delete arrayNode;
    delete idNode;
    delete expressionListNode;
}

WriteNode::WriteNode(ExpressionListNode* eln) : expressionListNode(eln) {}
void WriteNode::accept(Visitor* v) {v->visit(this);}
WriteNode::~WriteNode() {delete expressionListNode;}

ConstantNode::ConstantNode(NameDeclNode* ndn, ExpressionNode* en) : nameNode(ndn), value(en) {}
void ConstantNode::accept(Visitor* v) {v->visit(this);}
ConstantNode::~ConstantNode() {
     delete nameNode; 
     delete value;
}

ExpressionListNode::ExpressionListNode(ExpressionNode* en) : expressionNode(en), expressionListNode(NULL) {}
ExpressionListNode::ExpressionListNode(ExpressionNode* en, ExpressionListNode* eln) : expressionNode(en), expressionListNode(eln) {}
void ExpressionListNode::accept(Visitor* v) {v->visit(this);}
ExpressionListNode::~ExpressionListNode() {
    delete expressionNode;
    delete expressionListNode;
}

CallNode::CallNode(IdNode* in, ExpressionListNode* eln) : idNode(in), expressionListNode(eln) {}
void CallNode::accept(Visitor* v) {v->visit(this);}
CallNode::~CallNode() {
    delete idNode;
    delete expressionListNode;
}

ArrayNode::ArrayNode(IdNode* in, ExpressionNode* en) : idNode(in), expressionNode(en) {}
void ArrayNode::accept(Visitor* v) {v->visit(this);}
ArrayNode::~ArrayNode() {
    delete idNode;
    delete expressionNode;
}


IdNode::IdNode(int i, struct Registro  *reg) : id(i), registro(reg) {}
void IdNode::accept(Visitor* v) {v->visit(this);}

LiteralNode::LiteralNode(int l) : literal(l) {}
void LiteralNode::accept(Visitor* v) {v->visit(this);}

NumberNode::NumberNode(int n, struct Registro *reg) : number(n), registro(reg) {}
void NumberNode::accept(Visitor* v) {v->visit(this);}

RelOpNode::RelOpNode(int o, ExpressionNode* en1, ExpressionNode* en2) : op(o), expressionNode1(en1), expressionNode2(en2) {}
void RelOpNode::accept(Visitor* v) {v->visit(this);}
RelOpNode::~RelOpNode(){
    delete expressionNode1;
    delete expressionNode2;
}


BoolOpNode::BoolOpNode(int o, ExpressionNode* en1, ExpressionNode* en2) : op(o), expressionNode1(en1), expressionNode2(en2) {}
void BoolOpNode::accept(Visitor* v) {v->visit(this);}
BoolOpNode::~BoolOpNode() {
    delete expressionNode1;
    delete expressionNode2;
}

NegativeNode::NegativeNode(ExpressionNode* en) : expressionNode(en) {}
void NegativeNode::accept(Visitor* v) {v->visit(this);}
NegativeNode::~NegativeNode() { delete expressionNode; }

AddOpNode::AddOpNode(int o, ExpressionNode* en1, ExpressionNode* en2) : op(o), expressionNode1(en1), expressionNode2(en2) {}
void AddOpNode::accept(Visitor* v) {v->visit(this);}
AddOpNode::~AddOpNode() {
    delete expressionNode1;
    delete expressionNode2;
}

MultOpNode::MultOpNode(int o, ExpressionNode* en1, ExpressionNode* en2) : op(o), expressionNode1(en1), expressionNode2(en2) {}
void MultOpNode::accept(Visitor* v) {v->visit(this);}
MultOpNode::~MultOpNode() {
    delete expressionNode1;
    delete expressionNode2;
}

NotNode::NotNode(ExpressionNode* en) : expressionNode(en) {}
void NotNode::accept(Visitor* v) {v->visit(this);}
NotNode::~NotNode() { delete expressionNode; }
