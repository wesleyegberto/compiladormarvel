#include "ClassesArvoreAbstrata.h"
#include "Tokens.h"
#include <stdio.h>
#include <iostream>
#include "Tradutor.h"
#define WORD 4

using namespace std;

Tradutor::Tradutor(){
		Fragmentos = NULL;
		dados = NULL;
		corpo = NULL;
		expressao = NULL;
		sentenca = NULL;
        numero_temporario          = 0;
        numero_rotulo              = 0;
        numero_literal             = 0;

};
        Temp *FP = new Temp("FP");
        Temp *SL = new Temp("SL");

//ProgramNode
void Tradutor::visit(ProgramNode* programNode){
	
    if ( programNode->stmtListNode != NULL ) programNode->stmtListNode->accept(this);
    
	//Frame Principal
	FrameMips * frame = new FrameMips(new Label("PROCEDIMENTO$PRINCIPAL"),dados);
	Procedimento * procedimento = new Procedimento(frame,corpo);
	
	adicionaFragmento(procedimento);
    
     //Inicia a Impressão da Arvore de Codigo Intermediario
      VisitorArvoreIntermediaria* visitorAI = new VisitorArvoreIntermediaria();
      Fragmentos->accept(visitorAI);
	
};



//IdNode
void Tradutor::visit(IdNode *idNode){
     int offset, nivel;
     offset = idNode->offset;
     nivel  = idNode->escopo;
     
     //Programa Principal
	 if (nivel == 0){
		expressao = new MEM(new BINOP(PLUS,new TEMP(FP),new CONST(offset)));				
	}else{
		expressao = new MEM(new BINOP(PLUS,new MEM(new TEMP(FP)),new CONST(offset)));				
	}	


};

//NumberNode
void Tradutor::visit(NumberNode* numberNode){
	 if (numberNode->tipo == INTEGER){
		expressao = new CONST(atoi(retornaCharToken(numberNode->number)));
	//FLOAT
    }else{
		expressao = new CONSTF(atof(retornaCharToken(numberNode->number)));
	}
};

//LiteralNode
void Tradutor::visit(LiteralNode* literalNode){
	 char *rotulo = retornaCharToken(literalNode->literal);
//     rotulo = strcat("CONSTANTE_LITERAL$%d",++numero_literal);

     Label* rotuloLiteral = new Label(rotulo);
     Fragmento* consLiteral = new constanteLiteral(retornaCharToken(literalNode->literal));

     expressao = new NAME(rotuloLiteral);
      
     adicionaSentenca(new EXP(expressao));    
     adicionaFragmento(consLiteral);
};

//IfNode
void Tradutor::visit(IfNode* ifNode){
    (ifNode->expressionNode)->accept(this);
    Exp * condicional = expressao;
    (ifNode->statementNode1)->accept(this);
    Stm * entao = sentenca;
    
    Stm *tempStm;
	if (ifNode->statementNode2!= NULL){
        (ifNode->statementNode2)->accept(this);
	    Stm* senao  = sentenca;	
        char *rotulo;
//        rotulo = strcat("LABEL$ENTAO",++numero_rotulo);
        rotulo = "LABEL$ENTAO";
        Label* rotuloEntao = new Label(rotulo);
//        rotulo = strcat("LABEL%d$SENAO",numero_rotulo);
        rotulo = "LABEL$SENAO";
        Label* rotuloSenao = new Label(rotulo);
//        rotulo = strcat("LABEL%d$FIM",numero_rotulo);
        rotulo = "LABEL$FIM";
        Label* rotuloFim   = new Label(rotulo);
        
        tempStm = new SEQ(
                       new CJUMP(NE, condicional, new CONST(0), rotuloEntao, rotuloSenao),
                       new SEQ(new LABEL(rotuloEntao),
                           new SEQ(entao,
                               new SEQ(new JUMP(new NAME(rotuloFim)),
                                   new SEQ(new LABEL(rotuloSenao),
                                       new SEQ(senao,
                                          new LABEL(rotuloFim)))))));       
	    
	}else{
	    char *rotulo;
//             rotulo = strcat("LABEL%d$ENTAO",++numero_rotulo);
                   rotulo = "LABEL$SENAO";
             Label* rotuloEntao = new Label(rotulo);
//             rotulo = strcat("LABEL%d$FIM",numero_rotulo);
                    rotulo = "LABEL$FIM";
             Label* rotuloFim   = new Label(rotulo);
     
          tempStm = new SEQ(new CJUMP(NE, condicional, new CONST(0), rotuloEntao, rotuloFim),
                         new SEQ(new LABEL(rotuloEntao),
                             new SEQ(entao,
                                 new LABEL(rotuloFim))));

	}
	adicionaSentenca(tempStm);
	

};


//WhileNode
void Tradutor::visit(WhileNode* whileNode){
     
	(whileNode->expressionNode)->accept(this);
	Exp* expressaoCondicional = expressao;
   	(whileNode->statementNode)->accept(this);  
    Stm* sentencaEnquanto = sentenca;
    
    char *rotulo;
//     rotulo = strcat("LABEL%d$TESTE",++numero_rotulo);
             rotulo = "LABEL$TESTE";
     Label* rotuloTeste  = new Label(rotulo);
//     rotulo = strcat("LABEL%d$INICIO",numero_rotulo);
             rotulo = "LABEL$INICIO";
     Label* rotuloInicio = new Label(rotulo);
//     rotulo = strcat("LABEL%d$FIM",numero_rotulo);
                  rotulo = "LABEL$FIM";
     Label* rotuloFim    = new Label(rotulo);
     
    Stm* tempWhile = new SEQ(new LABEL(rotuloTeste),
                        new SEQ(new CJUMP(NE, expressaoCondicional, new CONST(0), rotuloInicio, rotuloFim),
                            new SEQ(new LABEL(rotuloInicio),
                                new SEQ( sentencaEnquanto,
                                    new SEQ( new JUMP(new NAME(rotuloTeste)),
                                        new LABEL(rotuloFim))))));

	adicionaSentenca(tempWhile);
};

//NameDecl
void Tradutor::visit(NameDeclNode* nameDeclNode){

    IdListNode* idList = nameDeclNode->idListNode;
    inFrame * iFrame = new inFrame(idList->idNode->offset);
	
	if (dados == NULL){
		dados = new ListaAcesso(iFrame,NULL);
	}else{
		ListaAcesso *nova = dados;
		while (nova->prox != NULL){
			nova = nova->prox;
		}
		nova->prox = new ListaAcesso(iFrame,NULL);
	}
	
    idList = idList->idListNode;
	while (idList != NULL){
       	IdNode* id = idList->idNode;	
		inFrame * iFrame =new inFrame(id->offset);
		
		ListaAcesso *temp = dados;
		while (temp->prox != NULL){
			temp = temp->prox;
		}
		ListaAcesso * temp2 = new ListaAcesso(iFrame,NULL);
		temp->prox = temp2;
				
		idList = idList->idListNode;
	}
 
    if ((nameDeclNode->modifierListNode) != NULL) (nameDeclNode->modifierListNode)->accept(this);
    if ((nameDeclNode->idListNode) != NULL) (nameDeclNode->idListNode)->accept(this);
};


void Tradutor::visit(FragmentNode* fragmentNode){
    
    StatementNode *primeiro = (fragmentNode->statementListNode)->statementNode;
    //Verifica se o fragmento é nomeado (Função ou Procedimento)
    if ( typeid(* primeiro).name() == typeid(NameDeclNode).name() ){
       //Pega a lista de parametros
       NameDeclNode *nome = dynamic_cast<NameDeclNode *>(primeiro);
       IdListNode *parametros = nome->idListNode->idNode->parametros;
        //Tem retorno é Função
        if (nome->modifierListNode != NULL) {
    			nome->modifierListNode->accept(this);
    			nome->idListNode->accept(this);
			
            	ListaAcesso *tempDados = dados;
                dados = NULL;
                StmList *tempCorpo = corpo;
                corpo = NULL;

				(fragmentNode->statementListNode->statementListNode)->accept(this); 
				char *rotulo = retornaCharToken(nome->idListNode->idNode->id);

            	FrameMips * frame = new FrameMips(new Label(rotulo),dados);
				Procedimento * procedimentoTemp = new Procedimento(frame,corpo);
				adicionaFragmento(procedimentoTemp);
			
            	dados = tempDados;
                tempDados = NULL;
                corpo = tempCorpo;
                tempCorpo = NULL;
    	//Não tem retorno é Procedimento
        }else{
    		    nome->idListNode->accept(this); 
	            
                ListaAcesso *tempDados = dados;
                dados = NULL;
                StmList *tempCorpo = corpo;
                corpo = NULL;
				
                (fragmentNode->statementListNode->statementListNode)->accept(this); 
                 char *rotulo = retornaCharToken(nome->idListNode->idNode->id);
//                 rotulo = strcat("PROCEDIMENTO$%s",retornaCharToken(nome->idListNode->idNode->id)); 
				FrameMips * frame = new FrameMips(new Label(rotulo),dados);
				Procedimento * procedimentoTemp = new Procedimento(frame,corpo);
				adicionaFragmento(procedimentoTemp);

            	dados = tempDados;
                tempDados = NULL;
                corpo = tempCorpo;
                tempCorpo = NULL;
    	
    	}
    //Não tem nome é bloco	
    }else{
        	 char *rotulo;
//             rotulo = strcat("LABEL%d$INICIO",++numero_rotulo);
             rotulo = "LABEL$INICIO";
             Label* rotuloInicio = new Label(rotulo);
//             rotulo = strcat("LABEL%d$FIM",numero_rotulo);
                          rotulo = "LABEL$FIM";
             Label* rotuloFim    = new Label(rotulo);

             //Verifica se o bloco não é vazio
             if (fragmentNode->statementListNode != NULL) { 
				
                Stm* StmTemporario = new LABEL(rotuloInicio);
                while(fragmentNode->statementListNode != NULL){
                      fragmentNode->statementListNode->statementNode->accept(this);
    		          StmTemporario = new SEQ(StmTemporario,sentenca);
    		          fragmentNode->statementListNode =fragmentNode->statementListNode->statementListNode;
                }
    
               sentenca = new SEQ(StmTemporario, new LABEL(rotuloFim));
              
             //Blobo Vazio  
	         }else{
                      sentenca = new SEQ(
                                         new LABEL(rotuloInicio),
                                         new LABEL(rotuloFim));
            }
			adicionaSentenca(sentenca);
   }
};

//Call Node
void Tradutor::visit(CallNode* callNode){ 
		
	ExpList * expList = new ExpList(new TEMP(SL),NULL);
	while(callNode->expressionListNode != NULL){ 
		if (callNode->expressionListNode->expressionNode != NULL){
		    callNode->expressionListNode->expressionNode->accept(this); 
			Exp * exp = expressao;	
			ExpList *nova = expList;
			
			//Adiciona ao final da Lista de Expressoes
			while (nova->prox != NULL){
				nova = nova->prox;	
			}
			ExpList * nova2 = new ExpList(exp,NULL);
			nova->prox = nova2;	
			//Pega a Próxima
            callNode->expressionListNode = callNode->expressionListNode->expressionListNode;
		}
	}    	
	
	Exp* acesso;
	 //Procedimento Principal
     if (callNode->idNode->escopo !=0){
        acesso = new MEM(new TEMP(FP));
     }
     else{
        acesso = new TEMP(FP);  
     }	
	expressao = new ESEQ(
						new MOVE(
							new TEMP(SL),
							acesso),
						new CALL(
							new NAME(new Label(retornaCharToken(callNode->idNode->id))),
							expList
						)
					);
};

//Constant
void Tradutor::visit(ConstantNode* constantNode){ 
     (constantNode->nameNode)->accept(this);
     (constantNode->value)->accept(this);
};

//ArrayNode
void Tradutor::visit(ArrayNode* arrayNode){
    if (arrayNode->idNode) (arrayNode->idNode)->accept(this); 
    Exp * expressaoEsquerda  =  expressao;
    if (arrayNode->expressionNode) (arrayNode->expressionNode)->accept(this);
    Exp * expressaoDireita = expressao;
    
	expressao = new MEM(
                     new BINOP(PLUS,expressaoEsquerda,
                         new BINOP(MULT,new CONST(WORD), 
                             new BINOP(MINUS,expressaoDireita, 
                                new CONST(arrayNode->idNode->offset)))));
};

void Tradutor::visit(AssignNode *o){
	if (o->idNode){
		o->idNode->accept(this);
		Exp * esquerda = expressao;
		o->expressionNode1->accept(this);
		Exp * direita =  expressao;
		Stm * stmAssign = new MOVE(new MEM(esquerda),direita);
		sentenca = stmAssign;		
	}else{
		o->arrayNode->accept(this);
		Exp * esquerda = expressao;
		o->expressionNode1->accept(this);
		Exp * direita = expressao;
		sentenca  = new MOVE(new MEM(esquerda),direita);
	}
	
    adicionaSentenca(sentenca);
};

//ReadNode
void Tradutor::visit(ReadNode* readNode){
	 if (readNode->idNode) (readNode->idNode)->accept(this);
     if (readNode->arrayNode) (readNode->arrayNode)->accept(this);
  	 Label* rotuloProcedimento = new Label("PROCEDIMENTO$READ");
    
    Stm * StmTemporario = new SEQ(new LABEL(rotuloProcedimento),
                                  new MOVE(expressao,new TEMP(new Temp("stdin"))));
    
    if (readNode->expressionListNode != NULL){
        //Varre a Lista de Expressoes do ReadNode
        while(readNode->expressionListNode != NULL){
             readNode->expressionListNode->expressionNode->accept(this);
		      StmTemporario = new SEQ(new MOVE(expressao,new TEMP(new Temp("stdin"))),sentenca);
	           readNode->expressionListNode = readNode->expressionListNode->expressionListNode;
        }
    
    Label* rotuloFIM = new Label("FIM$READ");
    sentenca = new SEQ(StmTemporario,new LABEL(rotuloFIM));
	
   }  
		adicionaSentenca(sentenca);
};

//FragCall
void Tradutor::visit(FragCallNode* fragCallNode){
	ExpList * expList = new ExpList(new TEMP(SL),NULL);
	while(fragCallNode->expressionList != NULL){
		if (fragCallNode->expressionList->expressionNode != NULL){
			fragCallNode->expressionList->expressionNode->accept(this);
			Exp * expTemp = expressao;
	    	ExpList *listaAtual = expList;  
	    
            //Ultimo	
            while (listaAtual->prox != NULL) listaAtual = listaAtual->prox;	
		
			ExpList * expTemp2 = new ExpList(expTemp,NULL);
			listaAtual->prox = expTemp2;	
			fragCallNode->expressionList = fragCallNode->expressionList->expressionListNode;
		}
	}    	
	
    Exp* acesso;
	if (fragCallNode->idNode->escopo != 0){acesso = new MEM(new TEMP(FP));
       }else{ acesso = new TEMP(FP);}

	sentenca = new EXP(new ESEQ( new MOVE( new TEMP(SL),acesso),
								new CALL(new NAME(new Label(retornaCharToken(fragCallNode->idNode->id))),
									expList)));

    adicionaSentenca(sentenca);									
};


//WriteNode
void Tradutor::visit(WriteNode* writeNode){
  
     ExpList* listaParametros    = NULL;
     ExpList* ordListaParametros = NULL;
     
     if (writeNode->expressionListNode){
        ExpressionListNode *listaExpressao = writeNode->expressionListNode;
        //Pega a lista de par$ametros do WriteNode
        while (listaExpressao != NULL){
              (listaExpressao->expressionNode)->accept(this);
              listaParametros = new ExpList(expressao,listaParametros);
              listaExpressao  = listaExpressao->expressionListNode;
        }
       
       //Ordena a lista de parametros
        while (listaParametros != NULL){
              ordListaParametros = new ExpList(listaParametros->prim, ordListaParametros);
              listaParametros          = listaParametros->prox;
        }
     }
     listaParametros = NULL;
     
     //Chamada da funcao
     Label* rotuloProcedimento = new Label("PROCEDIMENTO$WRITE");
     sentenca = new EXP(
                    new ESEQ(
                        new MOVE(new TEMP(SL),new TEMP(FP)),
                        new CALL(
                            new NAME(rotuloProcedimento),
                            new ExpList(new TEMP(SL), ordListaParametros))));
     adicionaSentenca(sentenca);
};

//RelOp
void Tradutor::visit(RelOpNode* relOpNode){
     (relOpNode->expressionNode1)->accept(this);
     Exp* esquerda = expressao;
     (relOpNode->expressionNode2)->accept(this);
     Exp* direita = expressao;
     
     char *rotulo;
     //rotulo = strcat("TEMP$%d",++numero_temporario);
     rotulo = "TEMP$";
     Temp* temporario           = new Temp(rotulo); 
     //rotulo = strcat("LABEL%d$VERDADEIRO",++numero_rotulo);
          rotulo = "LABEL$VERDADEIRO";
     Label*     rotuloVerdadeiro = new Label(rotulo);
//     rotulo = strcat("LABEL%d$FALSO",numero_rotulo);
     rotulo = "LABEL$FALSO";
     Label*     rotuloFalso      = new Label(rotulo);
     
     expressao = new ESEQ(
                     new SEQ( new MOVE( new TEMP(temporario),new CONST(1)), 
                         new SEQ( new CJUMP(relOpNode->op, esquerda, direita, rotuloVerdadeiro, rotuloFalso),
                             new SEQ( new LABEL(rotuloFalso),
                                 new SEQ( new MOVE( new TEMP(temporario), new CONST(0)),
                                     new LABEL(rotuloVerdadeiro))))), 
                                       new TEMP(temporario));	  
};

//Add Op
void Tradutor::visit(AddOpNode* additionalOpNode){
      (additionalOpNode->expressionNode1)->accept(this);
       Exp *expressaoEsquerda = expressao;
     
      (additionalOpNode->expressionNode2)->accept(this);
       Exp *expressaoDireita = expressao; 
     
      expressao = new BINOP(additionalOpNode->op, expressaoEsquerda, expressaoDireita);
};


//Mult Op
void Tradutor::visit(MultOpNode* multOpNode){

    (multOpNode->expressionNode1)->accept(this);
     Exp* expressaoEsquerda = expressao;
    (multOpNode->expressionNode2)->accept(this);
     Exp* expressaoDireita = expressao;
     
     expressao = new BINOP(multOpNode->op, expressaoEsquerda, expressaoDireita);
};




//Bool Op
void Tradutor::visit(BoolOpNode* boolOpNode){
 
     (boolOpNode->expressionNode1)->accept(this);
     Exp* esquerda = expressao;
     (boolOpNode->expressionNode2)->accept(this);
     Exp* direita = expressao;
     
     char *rotulo;
//     rotulo = strcat("TEMP$%d",++numero_temporario);
     rotulo = "TEMP$";
     Temp* temporario           = new Temp(rotulo); 
//     rotulo = strcat("LABEL%d$VERDADEIRO",++numero_rotulo);
     rotulo = "LABEL$VERDADEIRO";
     Label*     rotuloVerdadeiro = new Label(rotulo);
//     rotulo = strcat("LABEL%d$FALSO",numero_rotulo);
     rotulo = "LABEL$FALSO";
     Label*     rotuloFalso      = new Label(rotulo);
 
     expressao = new ESEQ(
                     new SEQ( new MOVE(new TEMP(temporario), esquerda),
                         new SEQ( new CJUMP(boolOpNode->op, direita, new CONST(0), rotuloVerdadeiro, rotuloFalso),
                             new SEQ( new LABEL(rotuloVerdadeiro),
                                 new SEQ( new MOVE( new TEMP(temporario), new CONST(1)), new LABEL(rotuloFalso))))),
                                     new TEMP(temporario));

}

//BitwiseOpNode
void Tradutor::visit(BitwiseOpNode* bitwiseOpNode){
     (bitwiseOpNode->expressionNode1)->accept(this);
      Exp* esquerda = expressao;
     (bitwiseOpNode->expressionNode2)->accept(this);
     Exp* direita = expressao;
    expressao = new BINOP(bitwiseOpNode->op,esquerda,direita);
};

//NotNode
void Tradutor::visit(NotNode* notNode){
     (notNode->expressionNode)->accept(this);
     Exp* esquerda = expressao;

     expressao = new BINOP(AND, new CONST(-1), esquerda);
};

//NegativeNode
void Tradutor::visit(NegativeNode* negativeNode){
    (negativeNode->expressionNode)->accept(this);
    expressao = new BINOP(MULT, new CONST(-1), expressao);
};


//Modifier Node
void Tradutor::visit(ModifierNode* modifierNode){};


//StatementListNode
void Tradutor::visit(StatementListNode* stmtListNode){
 if ((stmtListNode->statementNode) != NULL) (stmtListNode->statementNode)->accept(this);
 if ((stmtListNode->statementListNode) != NULL) (stmtListNode->statementListNode)->accept(this);
};


//ExpressionListNode
void Tradutor::visit(ExpressionListNode* expressionListNode){
     if ((expressionListNode->expressionNode) != NULL )(expressionListNode->expressionNode)->accept(this);
     if ((expressionListNode->expressionListNode) != NULL )(expressionListNode->expressionListNode)->accept(this);
};

	
//ModifierListNode
void Tradutor::visit(ModifierListNode* modifierListNode){
     if (modifierListNode->modifierNode)(modifierListNode->modifierNode)->accept(this);        
     if (modifierListNode->modifierListNode)(modifierListNode->modifierListNode)->accept(this);    
};


//IdListNode
void Tradutor::visit(IdListNode* idListNode){
     if ((idListNode->idListNode) == NULL){
         (idListNode->idNode)->accept(this);
     }else{
         (idListNode->idNode)->accept(this);
         (idListNode->idListNode)->accept(this);
     }
};


ListaDeFragmentos * Tradutor::getFragmentos(){
	return Fragmentos;
};


void Tradutor::adicionaFragmento(Fragmento * frag){
	if (Fragmentos == NULL){
		Fragmentos = new ListaDeFragmentos(frag,NULL);
	}else{
		ListaDeFragmentos *atual = Fragmentos;
		while (atual->prox != NULL){
			atual = atual->prox;	
		}
		ListaDeFragmentos * fl = new ListaDeFragmentos(frag,NULL);
		atual->prox = fl;	
	}    	
};


void Tradutor::adicionaSentenca(Stm * sentenca){
	if (corpo == NULL){
		corpo = new StmList(sentenca,NULL);
	}else{
		StmList *atual = corpo;
		while (atual->prox != NULL){
			atual = atual->prox;	
		}
		StmList * sl = new StmList(sentenca,NULL);
		atual->prox = sl;	
	}		
};


