#include "VerificadorTipos.h"

/* Definições para o Verificador de Tipos */
#define BOOLEAN 0
#define CHAR    1
#define NUMBER  2
#define EMPTY   0
#define FALSE   0
#define TRUE    1

/* ----------------------------------------------------------------------------
  Implementação do construtor e dos métodos visitantes da
  classe responsável por verificar o tipo da variável.
  
  Nos casos em que o objeto Node passado para o método visitante tem
  mais de um construtor, os atributos devem ser testados antes do método
  accept(visitor) ser chamado.
-----------------------------------------------------------------------------*/

 
// Implementa o construtor da classe de verificacao
VerificadorTipos::VerificadorTipos() {
     tipo = EMPTY;
}
/*---------------------------------------------------------------------------*/
// Implementa os métodos visitantes
/*---------------------------------------------------------------------------*/

void VerificadorTipos::visit(AddOpNode* additionalOpNode){
     // Chama o visitante para recuperar o tipo do lado direito
     (additionalOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (additionalOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de diferenca de tipos na operacao adicao
        //emiteErroSematico(ERRO_INCOMPATIBILIDADE_TIPO, "ADICAO", 0);
     }
     
     // Verifica se os tipos sao iguais a tipos nao compativeis com a operacao
     if ((tipoExpressionNode1 != INTEGER) || (tipoExpressionNode1 != FLOAT) ||
         (tipoExpressionNode2 != INTEGER) || (tipoExpressionNode2 != FLOAT)) {
        // Lança ERRO de tipo incompativel com a operacao de adicao
         //emiteErroSematico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "ADICAO", 0);                          
     }
          
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = tipoExpressionNode2;
}

void VerificadorTipos::visit(ArrayNode* arrayNode){
     // Chama o visitante para recuperar o tipo do vetor
     (arrayNode->idNode->accept(this));
     int tipoArray = tipo;
     
     // Chama o visitante para recuperar o tipo da expressao
     (arrayNode->expressionNode->accept(this));
     int tipoExpressionNode = tipo;
     
     if (tipoExpressionNode != INTEGER) {
        // Lança erro de tipo incompatível para referencia de indíce do vetor                       
        // emiteErroSematico(ERRO_TIPO_INCOMPATIVEL_INDICE_ARRAY, NULL, 0);
     }
     
     // Estabelecer uma forma de verificar se o valor passado pertence ao inter
     // valo que define os elementos do array.
     
     tipo = tipoArray;    
     
}

void VerificadorTipos::visit(AssignNode* assignNode){
     // Chama o visitante para recuperar o tipo do id que recebera a atribuição
     (assignNode->idNode)->accept(this);
     int tipoId = tipo;
     
     // Chama o visitante para recuperar o tipo da primeira expressão
     (assignNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo da segunda expressão
     (assignNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     if ((tipoExpressionNode1 != tipoId) || (tipoExpressionNode2 != tipoId)){
        // Lança erro de tipos incompatíveis durante uma atribuição
        //emiteErroSematico(ERRO_TIPO_INCOMPATIVEL_ATRIBUICAO, NULL, 0);
     }
     
     if (tipoExpressionNode1 != tipoExpressionNode2){
        // Lança erro de tipos incompatíveis 
        //emiteErroSematico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, NULL, 0);
     }
     
     // O nó tem que retornar o tipo do ID para nível superior na árvore.
     tipo = tipoId;
}

void VerificadorTipos::visit(BitwiseOpNode* bitwiseOpNode){
     // Chamao visitante para recuperar o tipo do lado direito
     (bitwiseOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (bitwiseOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de diferenca de tipos entre os operandos
        //emiteErroSematico(ERRO_INCOMPATIBILIDADE_TIPO, "BITWISEOPNODE", 0);
     }
     
     // Verifica se os tipos sao compativeis para essa operacao
     if (tipoExpressionNode1 != BOOLEAN || tipoExpressionNode2 != BOOLEAN) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao booleana
        //emiteErroSematico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "BITWISE", 0);
     }
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(BoolOpNode* boolOpNode){
     // Chama o visitante para recuperar o tipo do lado direito
     (boolOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (boolOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de diferenca de tipos na operacao booleana
        //emiteErroSematico(ERRO_INCOMPATIBILIDADE_TIPO, "BOOLEANA", 0);
     }
     
     // Verifica se os tipos sao compativeis para essa operacao
     if (tipoExpressionNode1 != BOOLEAN || tipoExpressionNode2 != BOOLEAN) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao booleana
        //emiteErroSematico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "BOOLEANA", 0);
     }
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(CallNode* callNode){
}

void VerificadorTipos::visit(ConstantNode* constantNode){
}

void VerificadorTipos::visit(ExpressionListNode* expressionListNode){
}

void VerificadorTipos::visit(FragCallNode* fragCallNode){
}

void VerificadorTipos::visit(FragmentNode* fragmentNode){
     (fragmentNode->statementListNode->accept(this));

     // Esse nó não retorna tipo
     tipo = EMPTY;
}

void VerificadorTipos::visit(IdListNode* idListNode){
     // Chama o visitante para a lista de nós
     if (idListNode->idListNode) (idListNode->idListNode->accept(this));
     
     // Chama o visitante para o idNode filho
     (idListNode->idNode->accept(this));
     
     // O nó idNode filho recupera o tipo atual
}

void VerificadorTipos::visit(IdNode* idNode){
     tipo = idNode->registro->tipo;
}

void VerificadorTipos::visit(IfNode* ifNode){
     // Chama o visitante para recuperar o tipo da expressão
     (ifNode->expressionNode->accept(this));
     int tipoExpressionNode = tipo;
     
     if (tipoExpressionNode != BOOLEAN) {
        // Lança erro de expressao não booleana numa clausula if
        //emiteErroSematico(ERRO_EXPRESSAO_NAO_BOOLEANA, NULL, 0);
     }
     
     // Visita a cláusula ENTAO
     (ifNode->statementNode1->accept(this));
     
     // Verifica se a cláusula SENAO está vazia e chama seu visitante
     if (ifNode->statementNode2) (ifNode->statementNode2->accept(this));
     
     // O tipo desse nó é vazio pois não retorna ao nível superior
     tipo = EMPTY;                          
}

void VerificadorTipos::visit(LiteralNode* literalNode){
     tipo = CHAR;
}

void VerificadorTipos::visit(ModifierListNode* modifierListNode){
}

void VerificadorTipos::visit(ModifierNode* modifierNode){
}   

void VerificadorTipos::visit(MultOpNode* multOpNode){
     // Chama o visitante para recuperar o tipo do lado direito
     (multOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (multOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de diferenca de tipos na operacao multiplicacao
        //emiteErroSematico(ERRO_INCOMPATIBILIDADE_TIPO, "MULTIPLICACAO", 0);
     }
     
     // Verifica se os tipos sao compativeis para essa operacao
     if ((tipoExpressionNode1 != INTEGER) || 
         (tipoExpressionNode1 != FLOAT) ||
         (tipoExpressionNode2 != INTEGER) ||
         (tipoExpressionNode2 != FLOAT)) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao multiplicacao
        //emiteErroSematico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "MULTIPLICACAO", 0);
     }
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = tipoExpressionNode2;
}

void VerificadorTipos::visit(NameDeclNode* nameDeclNode){
     // Chama o visitante para a lista de Modifiers
     (nameDeclNode->modifierListNode->accept(this));
     
     // Chama o visitante para a lista de ids
     (nameDeclNode->idListNode->accept(this));
     
     // Esse nó não retorna tipo para o nível acima na ASA
     tipo = EMPTY;
}

void VerificadorTipos::visit(NegativeNode* negativeNode){
     // Chama o visitante para recuperar o tipo da expressao
     (negativeNode->expressionNode->accept(this));
     
     // Recupera o tipo da expressao
     int tipoExpressionNode = tipo;
     
     // Verifica se a expressao retorna um tipo valido para negacao
     if ((tipoExpressionNode != INTEGER) || 
         (tipoExpressionNode != FLOAT) ||
         (tipoExpressionNode != NUM)){
         // Lanca erro de tipo incompativel com operador negativo
         
     }
     
     // Seta o tipo para o no atual
     tipo = tipoExpressionNode;
}

void VerificadorTipos::visit(NotNode* notNode){
     (notNode->expressionNode->accept(this));
     int tipoNotNode = tipo;
     if (tipoNotNode != BOOLEAN) {
        // Lanca erro de tipo incompativel na comparacao not equal
     }
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(NumberNode* numberNode){
     tipo = numberNode->registro->tipo;
}

void VerificadorTipos::visit(ProgramNode* programNode){
}

void VerificadorTipos::visit(ReadNode* readNode){
}

void VerificadorTipos::visit(RelOpNode* relOpNode){
     // Chama o visitante para recuperar o tipo do lado direito
     (relOpNode->expressionNode1->accept(this));
     int tipoExpressionNode1 = tipo;
     
     // Chama o visitante para recuperar o tipo do lado esquerdo
     (relOpNode->expressionNode2->accept(this));
     int tipoExpressionNode2 = tipo;
     
     // Verifica se os tipos sao iguais
     if (tipoExpressionNode1 != tipoExpressionNode2) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao relacional
        
     } // Verifica com o else else {
          // tipo = BOOLEAN;
          //}
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(StatementListNode* stmtListNode){
}

void VerificadorTipos::visit(WhileNode* whileNode){
     // Chama o visitante para recuperar o tipo da expressão
     (whileNode->expressionNode->accept(this));
     int tipoExpressionNode = tipo;
     
     if (tipoExpressionNode != BOOLEAN) {
        // Lança erro de expressão não booleana em condicional while
        // emiteErroSematico(ERRO_EXPRESSAO_NAO_BOOLEANA, NULL, 0);
     }
     
     // Chama o vistante para o conteúdo do while.
     (whileNode->statementNode->accept(this));
     
     // O tipo desse nó é vazio pois não retorna ao nível superior     
     tipo = EMPTY;
}

void VerificadorTipos::visit(WriteNode* writeNode){
     // Variáveis locais auxiliares
     //----------------------------------------------------------------
     
     // Recupera a lista de expressao do nó Write
     ExpressionListNode* expressionList = writeNode->expressionListNode;
     // Declara um inteiro que deve conter o tipo de cada expressão
     int tipoExpression;

     // Verifica se a lista de expressões do nó Write está vazia.
     if (expressionList == NULL){
         // Lança erro de comando write sem expressão
         //emiteErroSematico(ERRO_COMANDO_SEM_EXPRESSAO, "WRITE", 0);
         
     } else {
            // Efetua uma iteração entre os elementos expressions da lista
            while (expressionList != NULL){
                  // Chama o visitante para recuperar o tipo da expressão
                  (expressionList->expressionNode->accept(this));
                  tipoExpression = tipo;
                  // Verifica se o tipo da expressão atual é compatível 
                  if ((tipoExpression != INTEGER) &&
                      (tipoExpression != FLOAT)   &&
                      (tipoExpression != CHAR)){
                      // Lança erro de tipo incompatível com o comando 
                      // emiteErroSematico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "WRITE", 0);
                  }
                  // Recupera a próxima lista
                  // expressionList = expressionList->expressionListNode;
            }
     }
     // O nó Write não precisa enviar tipo a nível superior.
     tipo = EMPTY;
}

