
/**
 * 
 *          Analisador Sintático
 * 
 */
#include "AnalSint.h"
#include <stdio.h>
#include "ImpressaoArvoreAbstrata.h"
#include "Tokens.h"
#include "TabSimbolos.h"
#include "Erro.h"

int proxToken();
int retornaLinha();
char *retornaLiteralToken(int token);

int lookahead;

//Imprime a Arvore de Sintaxe Abstrata
void imprimirASAbstrata(ProgramNode* prgmNode){
    printf("\nÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n");
    printf("º                  ARVORE DE SINTAXE ABSTRATA                   º\n");
    printf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n");
     
     if (prgmNode != NULL){
       ImpressaoArvoreAbstrata* impressao = new ImpressaoArvoreAbstrata(0);
       prgmNode->accept(impressao);
    }
    printf("ÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ\n");
}

/*Inicia a analise sintatica*/
ProgramNode* analiseSintatica(){
     //Pega o primeiro token esperado    
     lookahead = proxToken();

     //Se final de arquivo a arvore é vazia
     if (lookahead == EOF){
        match(EOF, NULL, NULL);
        return NULL;
     }
     else{
        // Chama a produção inicial
        return program();
     }
}



//Follow de Program
int followProgram[] = {EOF};

//Produção Program
ProgramNode* program(){
       printf("Program\n");
       StatementListNode* stmtListNode = statementList();
       match(EOF,followProgram, NULL);
       return new ProgramNode(stmtListNode);            
}

//Follow de StatementList
int followStatementList[] = {EOF, ENDFRAGMENT};

//Produção StatementList
StatementListNode* statementList(){
        printf("StatementList\n");
        StatementNode* stmt = statement();
        StatementListNode* stmtListLinha = statementListLinha(stmt);
        return stmtListLinha;
}

//Follow de StatementListLinha
int followStatementListLinha[] = {EOF, ENDFRAGMENT};

//Produção StatementList'
StatementListNode* statementListLinha(StatementNode* stmLinha){
     printf("StatementList'\n");
     if (lookahead == SMCLN){   
         match(SMCLN,followStatementListLinha, NULL);
         StatementListNode* stmtListLinha = statementListLinha(statement());
         return new StatementListNode(stmLinha, stmtListLinha);
     } else if (stmLinha == NULL) return NULL;
     else return new StatementListNode(stmLinha);
}


//Follow de Statement
int followStatement[] = {ELSE, SMCLN, EOF, ENDFRAGMENT};

//Follow de Statement''
int followStatementDuasLinhas[] = {ELSE, SMCLN, EOF, ENDFRAGMENT};

//Follow de Destiny
int followDestiny[] = {ELSE, SMCLN, EOF, ENDFRAGMENT};

//Follow de Fragcall
int followFragcall[] = {ELSE, SMCLN, EOF, ENDFRAGMENT};

//Produção Statement
StatementNode* statement(){
printf("Statement\n");
      if (lookahead == ID){
            int lexema = retornaIndiceLexemaAtual();
            REGISTRO *regi = retornaRegistroAtual();
            IdNode* idStm = new IdNode(lexema, regi);
            match(ID, followStatement, &lexema);       
            return statementDuasLinhas(idStm);         
      }else if (lookahead == IF){
            match(IF,followStatement, NULL);
            ExpressionNode* exp = expression();
            StatementNode* stmt = statement();
            StatementNode* stmtLinha = statementLinha();
            return new IfNode(exp, stmt, stmtLinha);
      }else if (lookahead == WHILE){
            match(WHILE,followStatement, NULL);
            ExpressionNode* exp = expression();
            StatementNode* stmt = statement();
            return new WhileNode(exp, stmt);
      }else if (lookahead == WRITE){
            match(WRITE,followStatement, NULL);
            match(OPENPAR,followStatement, NULL);
            ExpressionListNode* expList = expressionList();            
            match(CLOSEPAR,followStatement, NULL);
            return new WriteNode(expList);
      }else if (lookahead == READ){
            match(READ,followStatement, NULL);
            match(OPENPAR,followStatement, NULL);
            ExpressionListNode* expList = expressionList();            
            match(CLOSEPAR,followStatement, NULL);
            return new ReadNode(expList);
      }else if (lookaheadPertenceFirst(NameDecl) == 1){
            return  namedecl();
      }else if (lookaheadPertenceFirst(Fragment) == 1){
            return fragment();
      }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha()); return NULL;}
}

// Produção StatementDuasLinhas
StatementNode* statementDuasLinhas(IdNode *idDuasLinhas){
            //Produção Statement''              
            if ((lookahead == ASSIGN) || (lookahead == OPENBRA)){//Produção Destiny
                  printf("Destiny\n");
                  if (lookahead == ASSIGN){
                      match(ASSIGN,followDestiny, NULL);
                      ExpressionNode* expAssign = expression();
                      return new AssignNode(idDuasLinhas,expAssign);           
                  } else if (lookahead == OPENBRA){
                      match(OPENBRA,followDestiny, NULL);
                      ExpressionNode* expAssign2 = expression();
                      match(CLOSEBRA,followDestiny, NULL);
                      match(ASSIGN,followDestiny, NULL);
                      ExpressionNode* expAssign3 = expression();
                      ArrayNode* arrayNd = new ArrayNode(idDuasLinhas,expAssign2);
                      return new AssignNode(arrayNd,expAssign3);           
                  }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha()); return NULL;}
            }else if (lookahead == OPENPAR){//Produção Fragcall
                   printf("Fragcall\n");
                   match(OPENPAR,followFragcall, NULL);
                   ExpressionListNode* expListFRC  = expressionList();
                   match(CLOSEPAR,followFragcall, NULL);
                   return new FragCallNode(idDuasLinhas,expListFRC); 
            }else return new NameDeclNode(NULL,new IdListNode(idDuasLinhas));
            //Fim Produção statementDuasLinhas
      
}      

//Follow de Statement'
int followStatementLinha[] = {ELSE, SMCLN, EOF, ENDFRAGMENT};

//Produção Statement'
StatementNode* statementLinha(){
      printf("Statement'\n");   
      if (lookahead == ELSE){
            match(ELSE,followStatementLinha, NULL);
            return statement();
      }else return NULL;
}

//Follow de NameDecl
int followNameDecl[] = {ELSE, SMCLN, EOF, ENDFRAGMENT};

//Produção NameDecl
NameDeclNode* namedecl(){
      printf("Statement'\n");  
       ModifierListNode* modifiers = modifierList();
       IdListNode* idlistdl = idList();
       return new NameDeclNode(modifiers,idlistdl);
}

//Follow de Fragment
int followFragment[] = {ELSE, SMCLN, EOF, ENDFRAGMENT};

//Produção Fragment
StatementNode* fragment(){
    printf("Fragment\n");  
    if (lookahead == FRAGMENT ){
       
       match(FRAGMENT,followFragment, NULL);
       StatementListNode* stmtLFrag = NULL;
        
       // Produção MidifierList ID; Statement_List ou produção MidifierList ID; NUM
       if ( lookaheadPertenceFirst(ModifierList) == 1 ){
              NameDeclNode* nmdecl = namedecl();
              match(SMCLN,followFragment, NULL);
              
              if (lookahead == NUM ){
                  int fragNumIndex = retornaIndiceLexemaAtual();
                  match(NUM,followFragment, &fragNumIndex);
                  match(ENDFRAGMENT,followFragment, NULL);
                  return new ConstantNode(nmdecl, new NumberNode(fragNumIndex, retornaRegistroAtual())); 
              }else{
                         StatementListNode* stmtListLinha = statementListLinha(statement());
                         stmtLFrag = new StatementListNode(nmdecl,stmtListLinha);
               }
              
       // Produção ID; Statement_List ou produção ID; LITERAL
       }else if (lookahead == ID ){
               int lexema = retornaIndiceLexemaAtual();
               REGISTRO *regi = retornaRegistroAtual();
               IdNode* idFrgm = new IdNode(lexema,regi);
               match(ID, followFragment, &lexema); 
               if (lookahead == SMCLN)    match(SMCLN,followFragment, NULL);       
            //Não é constante
                  StatementNode* stmFrag = statementDuasLinhas(idFrgm);
    
                  if (lookahead == LITERAL ){ 
                      int ifragLiteral = retornaIndiceLexemaAtual();
                      match(LITERAL,followFragment, &ifragLiteral);
                      match(ENDFRAGMENT,followFragment, NULL);
                      return new ConstantNode(new NameDeclNode(NULL, new IdListNode(idFrgm)),  new LiteralNode(ifragLiteral)); 
                  } else stmtLFrag = statementListLinha(stmFrag);
                    
       //Produção Statemente_List
       } else  stmtLFrag = statementList();

             
       match(ENDFRAGMENT,followFragment, NULL);
       return new FragmentNode(stmtLFrag);
       
    }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha()); return NULL;}
}


//Follow de Expression
int followExpression[] = {FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Expression
ExpressionNode* expression(){
       printf("Expression\n");  
       if (lookahead == LITERAL ){            
              int iLiteral = retornaIndiceLexemaAtual();
              LiteralNode* literal = new LiteralNode(iLiteral);
              match(LITERAL,followExpression, &iLiteral);
              if (lookaheadPertenceFirst(ExpressionDuasLinhas) == 1)
                  return expressionDuasLinhas(literal); 
              else
                  return literal; 
       }else{
              ExpressionNode* simpExp = simpleExpression();
              ExpressionNode* exprelinha = expressionLinha(simpExp);
              ExpressionNode* expreDuasLinhas = expressionDuasLinhas(exprelinha);
              return expreDuasLinhas; 
       }
}

//Follow de Expression'
int followExpressionLinha[] = {OR, AND, EQUALS, NE, FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Expression'
ExpressionNode* expressionLinha(ExpressionNode* sexprE){
       printf("Expression'\n");                 
       if (lookaheadPertenceFirst(Rel_Op) == 1){
             int relOpVar = relOp();
             ExpressionNode* sexprD = simpleExpression();
             if(sexprD == NULL) return NULL; else
             return new RelOpNode(relOpVar,sexprE,sexprD);
       }else return sexprE;
}

//Follow de Expression''
int followExpressionDuasLinhas[] = {FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Expression''
ExpressionNode* expressionDuasLinhas(ExpressionNode* cmpExprE){
       printf("Expression''\n"); 
       if (lookaheadPertenceFirst(Bool_Exp) == 1){                              
             return boolExp(cmpExprE);
       }else if (lookaheadPertenceFirst(Comp_Op) == 1){ //Comp_Op
             int compOpVar = compOp();
             ExpressionNode* compExprD = expression();
             if(compExprD == NULL) return NULL; else
             return new RelOpNode(compOpVar,cmpExprE,compExprD);
       }     
       return cmpExprE;
}

//Follow de BoolExp
int followBoolExp[] = {FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};


//Produção BoolExp
ExpressionNode* boolExp(ExpressionNode* boolExprE){
       printf("BoolExp\n"); 
       ExpressionNode* boolOrVar  = boolOr(boolExprE);
       ExpressionNode* boolAndVar = boolAnd(boolOrVar);       
       return boolAndVar;
}

//Follow de Bool_Or
int followBool_Or[] = {AND,  FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR};

//Produção Bool_Or
ExpressionNode* boolOr(ExpressionNode* orExprE){
       printf("Bool_Or\n");                 
       if (lookahead == OR){
             match(OR,followBool_Or, NULL);
             ExpressionNode* orExprD = expression();
             if(orExprD == NULL) return NULL; else
             return new BoolOpNode(OR, orExprE, orExprD);          
       } else return orExprE;
}

//Follow de Bool_and
int followBool_and[] = {FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Bool_and
ExpressionNode* boolAnd(ExpressionNode* andExprE){
       printf("Bool_and\n");                 
       if (lookahead == AND){
             match(AND,followBool_and, NULL);
             ExpressionNode* andExprD = expression();
             if(andExprD == NULL) return NULL; else
             return new BoolOpNode(AND, andExprE, andExprD);
          
       } else return andExprE;
}

//Follow de Expr_List
int followExpr_List[] = {CLOSEPAR};

//Produção Expr_List
ExpressionListNode* expressionList(){
       printf("Expr_List\n"); 
       ExpressionNode* expreVar = expression();
       ExpressionListNode* expreListLinhaVar = expressionListLinha();
       if (expreListLinhaVar == NULL) return new ExpressionListNode(expreVar);
          else return new ExpressionListNode(expreVar,expreListLinhaVar) ;
}

//Follow de Expr_List'
int followExpr_ListLinha[] = {CLOSEPAR};

//Produção Expr_List'
ExpressionListNode* expressionListLinha(){
       printf("Expr_List'\n"); 
      if (lookahead == COMMA ){
            match(COMMA,followExpr_ListLinha, NULL);
            ExpressionNode* expreLinhaVar = expression();
            ExpressionListNode* expreListLinhaVar = expressionListLinha();
            return new ExpressionListNode(expreLinhaVar,expreListLinhaVar);
      }else return NULL; 
}

//Follow de ModifierList
int followModifierList[] = {ID};

//Produção ModifierList
ModifierListNode* modifierList(){
      printf("ModifierList\n");                   
      ModifierNode* modfierVar = modifier();
      ModifierListNode* modifierListLinhaVar = modifierListLinha(modfierVar);
     return modifierListLinhaVar;
   
}


//Follow de ModifierList'
int followModifierListLinha[] = {ID};

//Produção ModifierList'
ModifierListNode* modifierListLinha(ModifierNode* modV){
     printf("ModifierList'\n");                     
     if (lookaheadPertenceFirst(Modifier) == 1){ 
          ModifierListNode* modifierListLinhaVar = modifierListLinha(modifier());
          return new ModifierListNode(modV,modifierListLinhaVar);
     }else return new ModifierListNode(modV);     
}


//Follow de Id_List
int followId_List[] = {ELSE, SMCLN, EOF, ENDFRAGMENT};

//Produção Id_List
IdListNode* idList(){
       printf("Id_List\n");   
   if (lookahead == ID ){
     int id = retornaIndiceLexemaAtual();  
     REGISTRO *regi= retornaRegistroAtual();
     IdNode* idN = new IdNode(id,regi);
     match(ID,followId_List, &id);
     IdListNode* idListVar = idListLinha();
     if (idListVar == NULL) return new IdListNode(idN,idListVar);
        else return new IdListNode(idN);
   }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha()); return NULL;}
}

//Follow de Id_List'
int followId_ListLinha[] = {ELSE, SMCLN, EOF, ENDFRAGMENT};

//Produção Id_List'
IdListNode* idListLinha(){
     printf("Id_List'\n"); 
     if (lookahead == COMMA ){
          match(COMMA,followId_ListLinha, NULL);
          int id2 = retornaIndiceLexemaAtual();
          REGISTRO *regi2 = retornaRegistroAtual();
          IdNode* idN2 = new IdNode(id2, regi2);
          match(ID,followId_ListLinha, &id2);
          IdListNode* idListLinhaVar2 = idListLinha();           
          return new IdListNode(idN2,idListLinhaVar2);
     }else return NULL;
}

//Follow de Simple_Exp
int followSimple_Exp[] = {LT, LE, GT, GE, OR,  AND, EQUALS, NE, FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Simple_Exp
ExpressionNode* simpleExpression(){
     printf("Simple_Exp\n");
     if (lookaheadPertenceFirst(Sign) == 1){ 
          ExpressionNode* termv;
          if (signOp() == MINUS) termv = new NegativeNode(term());
              else termv = term();
          ExpressionNode* simpleExpLinha = simpleExpressionLinha(termv);
          return simpleExpLinha;
     }else {
          ExpressionNode* termVar = term();   
          ExpressionNode* simpleExpLinhaVar = simpleExpressionLinha(termVar);
          return simpleExpLinhaVar;
     }
}

//Follow de Simple_Exp'
int followSimple_ExpLinha[] = {LT, LE, GT, GE, OR,  AND, EQUALS, NE, FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Simple_Exp'
ExpressionNode* simpleExpressionLinha(ExpressionNode* addExpE){
    printf("Simple_Exp'\n");
     if (lookaheadPertenceFirst(Add_Op) == 1){
          int addOpVar = addOp();
          ExpressionNode* addExpD = simpleExpression();
          if(addExpD == NULL) return NULL; else
          return new AddOpNode(addOpVar,addExpE,addExpD );
     }else return addExpE;

}


//Follow de Comp_Op
int followComp_Op[] = {ID, NOT, NUM, OPENPAR, PLUS, MINUS, LITERAL};

//Produção Comp_Op
int compOp(){
    printf("Comp_Op\n");
     if (lookahead == EQUALS ){
        match(EQUALS,followComp_Op, NULL);
        return EQUALS;
     }else if (lookahead == NE ){
         match(NE,followComp_Op, NULL);
        return NE;
     }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha());}
}

//Follow de Rel_Op
int followRel_Op[] = {ID, NOT, NUM, OPENPAR, PLUS, MINUS};

//Produção Rel_Op
int relOp(){
    printf("Rel_Op\n");
     if (lookahead == LT ){
        match(LT,followRel_Op, NULL);
        return LT;
     }else if (lookahead == LE ){
        match(LE,followRel_Op, NULL);
        return LE;
     }else if (lookahead == GE ){
         match(GE,followRel_Op, NULL);
        return GE;
     }else if (lookahead == GT ){
        match(GT,followRel_Op, NULL);
        return GT;
     }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha());}
}

//Follow de Modifier
int followModifier[] = {FLOAT, INTEGER, PARAM, VECTOR, ID};

//Produção Modifier
ModifierNode* modifier(){
     printf("Modifier\n");
     if (lookahead == FLOAT ){
        match(FLOAT,followModifier, NULL); 
        return new ModifierNode(FLOAT);
     }else if (lookahead == INTEGER ){
        match(INTEGER,followModifier, NULL);
        return new ModifierNode(INTEGER);
     }else if (lookahead == PARAM ){
         match(PARAM,followModifier, NULL);
        return new ModifierNode(PARAM);
     }else if (lookahead == VECTOR ){
        match(VECTOR,followModifier, NULL);
        match(OPENBRA,followModifier, NULL);
        int numValue = retornaIndiceLexemaAtual();
        match(NUM,followModifier, &numValue);
        match(CLOSEBRA,followModifier, NULL);
        return new ModifierNode(VECTOR,numValue);
     }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha());}
}

//Follow de Term
int followTerm[] = {PLUS, MINUS, BITOR, LT, LE, GT, GE, OR, AND, EQUALS, NE, FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Term
ExpressionNode* term(){
    printf("Term\n");
    ExpressionNode* expTerm = factor();
    ExpressionNode* expTermLinha = termLinha(expTerm);
    return expTermLinha;
}


//Follow de Term'
int followTermLinha[] = {PLUS, MINUS, BITOR, LT, LE, GT, GE, OR, AND, EQUALS, NE, FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Term'
ExpressionNode* termLinha(ExpressionNode* multExpE){
    printf("Term'\n");
    if (lookaheadPertenceFirst(Mult_Op)){
         int multOpVar = multOp();
         ExpressionNode* multExpD = term();
         if(multExpD == NULL) return NULL; else
           return new MultOpNode(multOpVar,multExpE,multExpD);
    }else return multExpE;
}

//Follow de Sign
int followSign[] = {ID, NOT, NUM, OPENPAR};

//Produção Sign
int signOp(){
    printf("Sign\n");
    if (lookahead == PLUS ){
        match(PLUS,followSign, NULL);
        return PLUS;
    }else if (lookahead == MINUS ){
        match(MINUS,followSign, NULL);
        return MINUS;
    }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha());}
}

//Follow de Add_Op
int followAdd_Op[] = {ID, NOT, NUM, OPENPAR, PLUS, MINUS};

//Produção Add_Op
int addOp(){
    printf("Add_Op\n");
    if (lookahead == PLUS ){
        match(PLUS,followAdd_Op, NULL);
        return PLUS;
    }else if (lookahead == MINUS ){
        match(MINUS,followAdd_Op, NULL);
        return MINUS;
    }else if (lookahead == BITOR ){
        match(BITOR,followAdd_Op, NULL);
        return BITOR;
    }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha());}
}

//Follow de Mult_Op
int followMult_Op[] = {ID, NOT, NUM, OPENPAR};

//Produção Mult_Op
int multOp(){
    printf("Mult_Op\n");
    if (lookahead == MULT ){
        match(MULT,followMult_Op, NULL);
        return MULT;
    }else if (lookahead == DIV ){
        match(DIV,followMult_Op, NULL);
        return DIV;
    }else if (lookahead == MOD ){
        match(MOD,followMult_Op, NULL);
        return MOD;
    }else if (lookahead == BITAND ){
        match(BITAND,followMult_Op, NULL);
        return BITAND;
    }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha());}
}

//Follow de Factor
int followFactor[] = {MULT, DIV, MOD, BITAND, PLUS, MINUS, BITOR, LT, LE, GT, GE, OR, AND, EQUALS, NE, FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Factor
ExpressionNode* factor(){
    printf("Factor\n");                
       if (lookahead == ID ){
           int fIdIndex = retornaIndiceLexemaAtual();
           REGISTRO *fregi = retornaRegistroAtual();
           IdNode* fId = new IdNode(fIdIndex,fregi);
           match(ID,followFactor, &fIdIndex);
           return factorLinha(fId);
       }else if (lookahead == NOT ){
           match(NOT,followFactor, NULL);
           return new NotNode(factor());
       }else if (lookahead == NUM ){
           int fNumIndex = retornaIndiceLexemaAtual();
           match(NUM,followFactor, &fNumIndex);
           return new NumberNode(fNumIndex, retornaRegistroAtual());
       }else if (lookahead == OPENPAR ){
           match(OPENPAR,followFactor, NULL);
           ExpressionNode* expreP = expression();
           match(CLOSEPAR,followFactor, NULL);
           return expreP;
       }else {emiteErroSintatico(ERRO_TOKEN_INVALIDO,lookahead,retornaLinha()); return NULL;}
}

//Follow de Factor'
int followFactorLinha[] = {MULT, DIV, MOD, BITAND, PLUS, MINUS, BITOR, LT, LE, GT, GE, OR, AND, EQUALS, NE, FLOAT, INTEGER, PARAM, VECTOR, FRAGMENT, ID, IF, WHILE, WRITE, READ, ELSE, SMCLN, EOF, ENDFRAGMENT, CLOSEBRA, COMMA, CLOSEPAR, AND};

//Produção Factor'
ExpressionNode* factorLinha(IdNode* idN){
    printf("Factor'\n");                
       if (lookahead == OPENBRA ){
           match(OPENBRA,followFactorLinha, NULL);
           ExpressionNode* arrayExp = expression();
           match(CLOSEBRA,followFactorLinha, NULL);
           return new ArrayNode(idN,arrayExp);
       }else if (lookahead == OPENPAR ){
           match(OPENPAR,followFactorLinha, NULL);  
           ExpressionListNode* vCallExp = expressionList();
           match(CLOSEPAR,followFactorLinha, NULL);  
           return new CallNode(idN,vCallExp);
       }else return idN;

}

// Função que casa o token lido com o esperado
// ou faz a sincronização caso o token não case
void match(int token, int follow[], int* iLexema){
    // token casou com o esperado
    if(lookahead == token) { 
          if(iLexema) printf("Match: %s.%s\n", retornaLiteralToken(token), retornaCharToken(*iLexema));
          else        printf("Match: %s\n", retornaLiteralToken(token));
          // Pega o proximo token esperado        
          if (token != EOF) lookahead = proxToken();
    }
    //token encontrado não é o esperado
    else{ 
        if (token == EOF) {                                               //igual fim de arquivo
            emiteErroSintatico(ERRO_TOKEN_ESPERADO,token,retornaLinha()); //emite o erro
            return;
        }else if(lookaheadPertenceFollow(follow)){                        //pertence ao follow
            emiteErroSintatico(ERRO_TOKEN_ESPERADO,token,retornaLinha()); //Emite erro
        }else{                                                            //token não pertence ao follow da produção atual e não é fim de arquivo
           lookahead = proxToken();                                       
           while ((lookaheadPertenceFollow(follow)==0)||(lookahead == token)){ //procura o proximo token valido
                 if (lookahead==EOF) break;
                 emiteErroSintatico(ERRO_TOKEN_ESPERADO,token,retornaLinha()); 
           }
        }
        emiteErroSintatico(ERRO_TOKEN_INVALIDO,token,retornaLinha());           //Emite erro
        lookahead = proxToken();                                        //retorna o proximo token
     }
}


// Retorna se o lookahead pertence ao follow
int lookaheadPertenceFollow(int follow[]){
  int i;
  int tamanho = sizeof(follow) / sizeof(follow[0]);
  for(i=0; i < tamanho; i++)
  if(follow[i] == lookahead) return 1;    
  return 0;  
}

// Retorna se o lookahead pertence ao first do não terminal
int lookaheadPertenceFirst(int naoTerminal){
 switch( naoTerminal ){
    case Program: 
         if ((lookahead == FLOAT) || (lookahead == INTEGER) || (lookahead == PARAM) || (lookahead == VECTOR) || (lookahead == FRAGMENT) || (lookahead == ID) || (lookahead == IF) || (lookahead == WHILE) || (lookahead == WRITE) || (lookahead == READ) ) return 1;
         break;
    case Statement_List: 
         if ((lookahead == FLOAT) || (lookahead == INTEGER) || (lookahead == PARAM) || (lookahead == VECTOR) || (lookahead == FRAGMENT) || (lookahead == ID) || (lookahead == IF) || (lookahead == WHILE) || (lookahead == WRITE) || (lookahead == READ) ) return 1;
         break;
    case Statement_ListLinha:  
         if (lookahead == SMCLN) return 1;
         break;
    case Statement:  
         if ((lookahead == FLOAT) || (lookahead == INTEGER) || (lookahead == PARAM) || (lookahead == VECTOR) || (lookahead == FRAGMENT) || (lookahead == ID) || (lookahead == IF) || (lookahead == WHILE) || (lookahead == WRITE) || (lookahead == READ) ) return 1;
         break;
    case StatementLinha:  
         if (lookahead == ELSE) return 1;
         break;
    case StatementDuasLinhas: 
         if ((lookahead == ASSIGN) || (lookahead == OPENPAR) || (lookahead == OPENBRA) ) return 1;
         break;
    case NameDecl: 
         if ((lookahead == FLOAT) || (lookahead == INTEGER) || (lookahead == PARAM) || (lookahead == VECTOR) ) return 1;
         break;
    case Fragment: 
         if (lookahead == FRAGMENT) return 1;
         break;
    case Destiny: 
         if ((lookahead == ASSIGN) || (lookahead == OPENBRA) ) return 1;
         break;
    case Expression: 
         if ((lookahead == ID) || (lookahead == NOT) || (lookahead == NUM) || (lookahead == OPENPAR) || (lookahead == PLUS) || (lookahead == MINUS) || (lookahead == LITERAL) ) return 1;
         break;
    case ExpressionLinha: 
         if ((lookahead == LT) || (lookahead == LE) || (lookahead == GE) || (lookahead == GT) ) return 1;
         break;
    case ExpressionDuasLinhas: 
         if ((lookahead == OR) || (lookahead == AND) || (lookahead == EQUALS) || (lookahead == NE) ) return 1;
         break;
    case FragCall: 
         if (lookahead == OPENPAR) return 1;
         break;
    case Expr_List: 
         if ((lookahead == ID) || (lookahead == NOT) || (lookahead == NUM) || (lookahead == OPENPAR) || (lookahead == PLUS) || (lookahead == MINUS) || (lookahead == LITERAL) ) return 1;
         break;
    case Expr_ListLinha: 
         if (lookahead == COMMA) return 1;
         break;
    case ModifierList: 
         if ((lookahead == FLOAT) || (lookahead == INTEGER) || (lookahead == PARAM) || (lookahead == VECTOR) ) return 1;
         break;
    case ModifierListLinha: 
         if ((lookahead == FLOAT) || (lookahead == INTEGER) || (lookahead == PARAM) || (lookahead == VECTOR) ) return 1;
         break;
    case Id_List: 
         if (lookahead == ID) return 1;
         break;
    case Id_ListLinha: 
         if (lookahead == COMMA) return 1;
         break;
    case Simple_Expr: 
         if ((lookahead == ID) || (lookahead == NUM) || (lookahead == NOT) || (lookahead == OPENPAR ) || (lookahead == PLUS) || (lookahead == MINUS) ) return 1;
         break;
    case Simple_ExprLinha: 
         if ((lookahead == PLUS) || (lookahead == MINUS) || (lookahead == BITOR) ) return 1;
         break;
    case Comp_Op: 
         if ((lookahead == EQUALS) || (lookahead == NE) ) return 1;
         break;
    case Rel_Op: 
         if ((lookahead == LT) || (lookahead == LE) || (lookahead == GE) || (lookahead == GT) ) return 1;
         break;
    case Modifier: 
         if ((lookahead == FLOAT) || (lookahead == INTEGER) || (lookahead == PARAM) || (lookahead == VECTOR) ) return 1;
         break;
    case Term: 
         if ((lookahead == ID) || (lookahead == NUM) || (lookahead == NOT) || (lookahead == OPENPAR ) ) return 1;
         break;
    case TermLinha: 
         if ((lookahead == MULT) || (lookahead == DIV) || (lookahead == MOD) || (lookahead == BITAND) ) return 1;
         break;
    case Sign: 
         if ((lookahead == PLUS) || (lookahead == MINUS)) return 1;
         break;
    case Add_Op: 
         if ((lookahead == PLUS) || (lookahead == MINUS) || (lookahead == BITOR) ) return 1;
         break;
    case Mult_Op: 
         if ((lookahead == MULT) || (lookahead == DIV) || (lookahead == MOD) || (lookahead == BITAND) ) return 1;
         break;
    case Factor: 
         if ((lookahead == ID) || (lookahead == NUM) || (lookahead == NOT) || (lookahead == OPENPAR ) ) return 1;
         break;
    case FactorLinha: 
         if ((lookahead == OPENBRA ) || (lookahead == OPENPAR ) ) return 1;
         break;
    case Bool_Exp: 
         if ((lookahead == AND) || (lookahead == OR) ) return 1;
         break;
    case Bool_Or: 
         if (lookahead == OR) return 1;
         break;
    case Bool_And: 
         if (lookahead == AND ) return 1;
         break;
    default : return 0;
  }     
  return 0;
}
