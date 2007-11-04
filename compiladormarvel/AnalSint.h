
/**
 * 
 *          Analisador Sintático
 * 
 */
#include "ClassesArvoreAbstrata.h"

// Função que casa o token lido com o esperado
void match(int token, int follow[], int* iLexema);

// Retorna se o lookahead pertence ao follow
int lookaheadPertenceFollow(int follow[]);

//Imprime a Arvore de Sintaxe Abstrata
void imprimirASAbstrata(ProgramNode* prgmNode);

/*Inicia a analise sintatica*/
ProgramNode* analiseSintatica();


//Produção Program
ProgramNode* program();

//Produção StatementList
StatementListNode* statementList();

//Produção StatementList'
StatementListNode* statementListLinha(StatementNode* stmLinha);

//Produção Statement
StatementNode* statement();

//Produção Statement'
StatementNode* statementLinha();

// Produção StatementDuasLinhas
StatementNode* statementDuasLinhas(IdNode *idDuasLinhas);

//Produção NameDecl
NameDeclNode* namedecl();

//Produção Fragment
StatementNode* fragment();

//Produção Expression
ExpressionNode* expression();

//Produção Expression'
ExpressionNode* expressionLinha(ExpressionNode* sexprE);

//Produção Expression''
ExpressionNode* expressionDuasLinhas(ExpressionNode* cmpExprE);

//Produção BoolExp
ExpressionNode* boolExp(ExpressionNode* boolExprE);

//Produção Bool_Or
ExpressionNode* boolOr(ExpressionNode* orExprE);

//Produção Bool_and
ExpressionNode* boolAnd(ExpressionNode* andExprE);

//Produção Expr_List
ExpressionListNode* expressionList();


//Produção Expr_List'
ExpressionListNode* expressionListLinha();

//Produção ModifierList
ModifierListNode* modifierList();

//Produção ModifierList'
ModifierListNode* modifierListLinha(ModifierNode* modV);

//Produção Id_List
IdListNode* idList();

//Produção Id_List'
IdListNode* idListLinha();

//Produção Simple_Exp
ExpressionNode* simpleExpression();

//Produção Simple_Exp'
ExpressionNode* simpleExpressionLinha(ExpressionNode* addExpE);

//Produção Comp_Op
int compOp();

//Produção Comp_Op
int relOp();

//Produção Modifier
ModifierNode* modifier();

//Produção Term
ExpressionNode* term();

//Produção Term'
ExpressionNode* termLinha(ExpressionNode* multExpE);

//Produção Sign
int signOp();

//Produção Add_Op
int addOp();

//Produção Mult_Op
int multOp();

//Produção Factor
ExpressionNode* factor();

//Produção Factor'
ExpressionNode* factorLinha(IdNode* idN);

// Retorna se o lookahead pertence ao first do não terminal
int lookaheadPertenceFirst(int naoTerminal);
