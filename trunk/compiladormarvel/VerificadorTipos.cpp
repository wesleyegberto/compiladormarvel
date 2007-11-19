#include "VerificadorTipos.h"
#include "ClassesArvoreAbstrata.h"
#include "Erro.h"
#include "Tokens.h"
#include "TabSimbolos.h"

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
     linha = 0;
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
        emiteErroSemantico(ERRO_INCOMPATIBILIDADE_TIPO, "ADICAO", linha);
     }
     
     // Verifica se os tipos sao iguais a tipos nao compativeis com a operacao
     if ((tipoExpressionNode1 != INTEGER) || (tipoExpressionNode1 != FLOAT) ||
         (tipoExpressionNode2 != INTEGER) || (tipoExpressionNode2 != FLOAT)) {
        // Lança ERRO de tipo incompativel com a operacao de adicao
         emiteErroSemantico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "ADICAO", linha);                          
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
        emiteErroSemantico(ERRO_TIPO_INCOMPATIVEL_INDICE_ARRAY, NULL, linha);
     }
     
     // Estabelecer uma forma de verificar se o valor passado pertence ao inter-
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
        emiteErroSemantico(ERRO_TIPO_INCOMPATIVEL_ATRIBUICAO, NULL, linha);
     }
     
     if (tipoExpressionNode1 != tipoExpressionNode2){
        // Lança erro de tipos incompatíveis 
        emiteErroSemantico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, NULL, linha);
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
        emiteErroSemantico(ERRO_INCOMPATIBILIDADE_TIPO, "BITWISEOPNODE", linha);
     }
     
     // Verifica se os tipos sao compativeis para essa operacao
     if (tipoExpressionNode1 != BOOLEAN || tipoExpressionNode2 != BOOLEAN) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao booleana
        emiteErroSemantico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "BITWISE", linha);
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
        emiteErroSemantico(ERRO_INCOMPATIBILIDADE_TIPO, "BOOLEANA", linha);
     }
     
     // Verifica se os tipos sao compativeis para essa operacao
     if (tipoExpressionNode1 != BOOLEAN || tipoExpressionNode2 != BOOLEAN) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao booleana
        emiteErroSemantico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "BOOLEANA", linha);
     }
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(CallNode* callNode){
}

void VerificadorTipos::visit(ConstantNode* constantNode){
     (constantNode->accept(this));
     int tipoConstantNode = tipo;
     
     if (tipoConstantNode == NUM) {
        // O nó é do tipo NUM
        tipo = INTEGER;
     } else {
        // Senão o nó é do tipo LITERAL, que no caso é interpretado como CHAR.
        tipo = CHAR;
     }
}

void VerificadorTipos::visit(ExpressionListNode* expressionListNode){
     (expressionListNode->expressionNode->accept(this));
     if (expressionListNode->expressionListNode)
        (expressionListNode->expressionListNode->accept(this));
}

void VerificadorTipos::visit(FragCallNode* fragCallNode){
     // Chama o visitante do FragCallNode para recuperar o tipo do id
     (fragCallNode->idNode->accept(this));
     int tipoId = tipo;
     
     // Chama o visitante do FragCallNode para recuperar o tipo da expressão
     (fragCallNode->expressionList->accept(this));
     int tipoExpressionNode = tipo;
     
     // Verifica a compatibilidade de tipos entre os integrantes do nó FragCall
     if (tipoExpressionNode != tipoId){
        // Lança erro de incompatilidade de tipo na chamada do fragmento
        emiteErroSemantico(ERRO_TIPO_INCOMPATIVEL_CHAMADA_FRAG, NULL, linha);  
     }
     
     // O nó deve retornar o tipo do ID
     tipo = tipoId;
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
//     fprintf(stdout, "---------------------------------------------------\n");
//     fprintf(stdout, "variavel: %s\n", retornaCharToken(idNode->registro->indiceLexema));     
//     fprintf(stdout, "tipo do no: %d\n", idNode->registro->tipo);
//     fprintf(stdout, "numero da linha: %d\n", idNode->registro->linha);     
     tipo = idNode->registro->tipo;
     linha = idNode->registro->linha;
}

void VerificadorTipos::visit(IfNode* ifNode){
     // Chama o visitante para recuperar o tipo da expressão
     (ifNode->expressionNode->accept(this));
     int tipoExpressionNode = tipo;
     
     if (tipoExpressionNode != BOOLEAN) {
        // Lança erro de expressao não booleana numa clausula if
        emiteErroSemantico(ERRO_EXPRESSAO_NAO_BOOLEANA, NULL, linha);
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
     //linha = literalNode->registro->linha;
}

void VerificadorTipos::visit(ModifierListNode* modifierListNode){
     
     // Verifica se o modifierList desse nó está vazio e chama seu visitante
     if (modifierListNode->modifierListNode) (modifierListNode->modifierListNode->accept(this));
     
     // Chama o visitante do modifier desse nó
     (modifierListNode->modifierNode->accept(this));
     
     // Invocando o accept do modifierNode, a variável tipo fica setada para esse nó.
}

void VerificadorTipos::visit(ModifierNode* modifierNode){
     // Atribui ao tipo, o definido no nó modifier pelo atributo int modifier
     tipo = modifierNode->modifier;
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
        emiteErroSemantico(ERRO_INCOMPATIBILIDADE_TIPO, "MULTIPLICACAO", linha);
     }
     
     // Verifica se os tipos sao compativeis para essa operacao
     if ((tipoExpressionNode1 != INTEGER) || 
         (tipoExpressionNode1 != FLOAT) ||
         (tipoExpressionNode2 != INTEGER) ||
         (tipoExpressionNode2 != FLOAT)) {
        // Lanca erro semantico de incompatibilidade de tipos na operacao multiplicacao
        emiteErroSemantico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "MULTIPLICACAO", linha);
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
         emiteErroSemantico(ERRO_INCOMPATIBILIDADE_TIPO, "NEGACAO", linha);
     }
     
     // Seta o tipo para o no atual
     tipo = tipoExpressionNode;
}

void VerificadorTipos::visit(NotNode* notNode){
     (notNode->expressionNode->accept(this));
     int tipoNotNode = tipo;
     if (tipoNotNode != BOOLEAN) {
        // Lanca erro de tipo incompativel na comparacao not equal
        emiteErroSemantico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "NEGACAO", linha);
     }
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(NumberNode* numberNode){
     tipo = numberNode->registro->tipo;
     linha = numberNode->registro->linha;
}

void VerificadorTipos::visit(ProgramNode* programNode){
     // Chama o visitante para seu StatementList
     (programNode->stmtListNode->accept(this));
     
     // Esse nó não retorna tipo
     tipo = EMPTY;
}

void VerificadorTipos::visit(ReadNode* readNode){
     // Variáveis auxiliares do métodos
     int tipoExpressao;

     if (readNode->expressionListNode){
          ExpressionListNode *expressionListNode = readNode->expressionListNode;
          if (expressionListNode == NULL){
             // Lançar erro semântico com ReadNode sem expressão definida
          } else {
                 while (expressionListNode != NULL){
                       // Chama o visitante para recuperar o tipo da expressão desse nó-filho
                       (expressionListNode->expressionNode->accept(this));
                       tipoExpressao = tipo;
                       
                       if ((tipoExpressao != INTEGER) || (tipoExpressao != FLOAT)){
                          // Lançar erro semantico de tipo incompativel com a operacao
                          emiteErroSemantico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "LEITURA", linha);
                       }
                       
                       // Recupera a lista filha de expressões
                       expressionListNode = expressionListNode->expressionListNode;
                       
                 }// end while
          } // end if 
     } // end if 

     // Chama o visitante para o array filho e faz sua verificação
     if (readNode->arrayNode) (readNode->arrayNode->accept(this));
     
     // Não chama o visitante para o id filho, pois isso seria necessário no 
     // caso de verificar o seu tipo, sendo que o visitante do id filho 
     // só recupera o seu tipo.

     // O nó atual não retorna tipo 
     tipo = EMPTY;
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
        emiteErroSemantico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "RELACIONAL", linha);
        
     } // Verifica com o else else {
          // tipo = BOOLEAN;
          //}
     
     // Atribui o tipo do lado esquerdo ao tipo global para continuar o Semantico
     tipo = BOOLEAN;
}

void VerificadorTipos::visit(StatementListNode* stmtListNode){
     (stmtListNode->statementNode->accept(this));
     if (stmtListNode->statementListNode)
        (stmtListNode->statementListNode->accept(this));
}

void VerificadorTipos::visit(WhileNode* whileNode){
     // Chama o visitante para recuperar o tipo da expressão
     (whileNode->expressionNode->accept(this));
     int tipoExpressionNode = tipo;
     
     if (tipoExpressionNode != BOOLEAN) {
        // Lança erro de expressão não booleana em condicional while
        emiteErroSemantico(ERRO_EXPRESSAO_NAO_BOOLEANA, NULL, linha);
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
         emiteErroSemantico(ERRO_COMANDO_SEM_EXPRESSAO, "WRITE", linha);
         
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
                      emiteErroSemantico(ERRO_TIPO_NAO_ESPERADO_OPERACAO, "WRITE", linha);
                  }
                  // Recupera a próxima lista
                  expressionList = expressionList->expressionListNode;
            }
     }
     // O nó Write não precisa enviar tipo a nível superior.
     tipo = EMPTY;
}

