#include "ImpressaoArvoreAbstrata.h"

/* ----------------------------------------------------------------------------
  Implementação do construtor e dos métodos visitantes da
  classe responsável por imprimir a ArvoreAbstrata.
  
  Nos casos em que o objeto Node passado para o método visitante tem
  mais de um construtor, os atributos devem ser testados antes do método
  accept(visitor) ser chamado.
  
-----------------------------------------------------------------------------*/

// Declaração da variável da classe
int nivel = 0;
 
// Implementa o construtor da classe de Impressao
ImpressaoArvoreAbstrata::ImpressaoArvoreAbstrata(int nvl) : nivel(nvl) {}
/*---------------------------------------------------------------------------*/


// Implementa os métodos visitantes, que devem imprimir o próprio nó e chamar
// os métodos de seus filhos.
/*---------------------------------------------------------------------------*/

void ImpressaoArvoreAbstrata::visit(AddOpNode* additionalOpNode){
      nivel++;
      imprimeNivel();
      fprintf(stdout, "AddOpNode\n");
      nivel++;
      imprimeNivel();
      if (additionalOpNode->op == PLUS) fprintf(stdout, "ADD_OP\n");
      if (additionalOpNode->op == MINUS) fprintf(stdout, "MINUS_OP\n");
      (additionalOpNode->expressionNode1)->accept(this);
      (additionalOpNode->expressionNode2)->accept(this);
      nivel--;
      nivel--;
}

void ImpressaoArvoreAbstrata::visit(ArrayNode* arrayNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "ArrayNode\n");
     if (arrayNode->idNode) (arrayNode->idNode)->accept(this);
     if (arrayNode->expressionNode) (arrayNode->expressionNode)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(AssignNode* assignNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "AssignNode\n");
     if (assignNode->idNode) (assignNode->idNode)->accept(this);
     if (assignNode->arrayNode) (assignNode->arrayNode)->accept(this);
     if (assignNode->expressionNode1) (assignNode->expressionNode1)->accept(this);
     if (assignNode->expressionNode2) (assignNode->expressionNode2)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(BitwiseOpNode* bitwiseOpNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "BitwiseOpNode\n");
     nivel++;
     imprimeNivel();
     if (bitwiseOpNode->op == BITAND) fprintf(stdout, "BITAND_OP\n");
     if (bitwiseOpNode->op == BITOR) fprintf(stdout, "BITOR_OP\n");
     (bitwiseOpNode->expressionNode1)->accept(this);
     (bitwiseOpNode->expressionNode2)->accept(this);
     nivel--;
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(BoolOpNode* boolOpNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "BoolOpNode\n");
     nivel++;
     imprimeNivel();
     if (boolOpNode->op == AND) fprintf(stdout, "AND_OP\n");
     if (boolOpNode->op == OR) fprintf(stdout, "OR_OP\n");
     (boolOpNode->expressionNode1)->accept(this);
     (boolOpNode->expressionNode2)->accept(this);
     nivel--;
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(CallNode* callNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "CallNode\n");
     (callNode->idNode)->accept(this);
     (callNode->expressionListNode)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(ConstantNode* constantNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "ConstantNode\n");
     (constantNode->nameNode)->accept(this);
     (constantNode->value)->accept(this);
     nivel--;
}


void ImpressaoArvoreAbstrata::visit(ExpressionListNode* expressionListNode){
     if ((expressionListNode->expressionNode) != NULL )(expressionListNode->expressionNode)->accept(this);
     if ((expressionListNode->expressionListNode) != NULL )(expressionListNode->expressionListNode)->accept(this);
}

void ImpressaoArvoreAbstrata::visit(FragCallNode* fragCallNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "FragCallNode\n");
     (fragCallNode->idNode)->accept(this);
     (fragCallNode->expressionList)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(FragmentNode* fragmentNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "FragmentNode\n");
     (fragmentNode->statementListNode)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(IdListNode* idListNode){
     if ((idListNode->idListNode) == NULL){ 
         (idListNode->idNode)->accept(this);
     }else{
         (idListNode->idNode)->accept(this);
         (idListNode->idListNode)->accept(this);
     }
}

void ImpressaoArvoreAbstrata::visit(IdNode* idNode){
     nivel++;
     imprimeNivel();
      fprintf(stdout, "ID.%s\n",retornaCharToken(idNode->id));
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(IfNode* ifNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "IfNode\n");
     (ifNode->expressionNode)->accept(this);
     (ifNode->statementNode1)->accept(this);
     (ifNode->statementNode2)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(LiteralNode* literalNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "LITERAL.%s\n",retornaCharToken( literalNode->literal));
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(ModifierListNode* modifierListNode){
     if (modifierListNode->modifierNode)(modifierListNode->modifierNode)->accept(this);        
     if (modifierListNode->modifierListNode)(modifierListNode->modifierListNode)->accept(this);    
}

void ImpressaoArvoreAbstrata::visit(ModifierNode* modifierNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "ModifierNode."); 
     if (modifierNode->modifier == FLOAT) fprintf(stdout, "FLOAT\n");
     if (modifierNode->modifier == INTEGER) fprintf(stdout, "INTEGER\n");
     if (modifierNode->modifier == PARAM) fprintf(stdout, "PARAM\n");
     if (modifierNode->modifier == VECTOR) {
             fprintf(stdout, "VECTOR.%s\n",retornaCharToken((modifierNode)->num));
             }           
     nivel--;
}   

void ImpressaoArvoreAbstrata::visit(MultOpNode* multOpNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "MultOpNode\n");
     nivel++;
     imprimeNivel();
     if (multOpNode->op == MULT) fprintf(stdout, "MULT_OP\n");
     if (multOpNode->op == DIV) fprintf(stdout, "DIV_OP\n");
     if (multOpNode->op == MOD) fprintf(stdout, "MOD_OP\n");
     (multOpNode->expressionNode1)->accept(this);
     (multOpNode->expressionNode2)->accept(this);
     nivel--;
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(NameDeclNode* nameDeclNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "NameDeclNode\n");
    if ((nameDeclNode->modifierListNode) != NULL) (nameDeclNode->modifierListNode)->accept(this);
      (nameDeclNode->idListNode)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(NegativeNode* negativeNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "NegativeNode\n");
     (negativeNode->expressionNode)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(NotNode* notNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "NotNode\n");
     (notNode->expressionNode)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(NumberNode* numberNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "NUM.%s \n",retornaCharToken(numberNode->number));
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(ProgramNode* programNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "ProgramNode\n");
     (programNode->stmtListNode)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(ReadNode* readNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "ReadNode\n");
     // ReadNode tem dois construtores, cada um com um parâmetro diferente
     if (readNode->idNode) (readNode->idNode)->accept(this);
     if (readNode->arrayNode) (readNode->arrayNode)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(RelOpNode* relOpNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "RelationalOpNode\n");
     nivel++;
     imprimeNivel();
     if (relOpNode->op == EQUALS) fprintf(stdout, "EQ_OP\n");
     if (relOpNode->op == NE) fprintf(stdout, "NE_OP\n");
     if (relOpNode->op == GE) fprintf(stdout, "GE_OP\n");
     if (relOpNode->op == LE) fprintf(stdout, "LE_OP\n");
     if (relOpNode->op == LT) fprintf(stdout, "LT_OP\n");
     if (relOpNode->op == GT) fprintf(stdout, "GT_OP\n");
     (relOpNode->expressionNode1)->accept(this);
     (relOpNode->expressionNode2)->accept(this);
     nivel--;
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(StatementListNode* stmtListNode){
     if ((stmtListNode->statementNode) != NULL) (stmtListNode->statementNode)->accept(this);
     if ((stmtListNode->statementListNode) != NULL) (stmtListNode->statementListNode)->accept(this);
}

void ImpressaoArvoreAbstrata::visit(WhileNode* whileNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "WhileNode\n");
     (whileNode->expressionNode)->accept(this);
     (whileNode->statementNode)->accept(this);
     nivel--;
}

void ImpressaoArvoreAbstrata::visit(WriteNode* writeNode){
     nivel++;
     imprimeNivel();
     fprintf(stdout, "WriteNode\n");
     (writeNode->expressionListNode)->accept(this);
     nivel--;
}



// Imprime os espaços relativos ao nó da árvore
void ImpressaoArvoreAbstrata::imprimeNivel(){
     int n;
     // Imprime espaço tantas vezes quanto for nível do node
     for (n=0; n < nivel; n++){
         fprintf(stdout,"  ");
     }
     // Imprime o sinal do nível "-", conforme especificação
     fprintf(stdout, "-");
}

