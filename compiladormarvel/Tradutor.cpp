#include "ClassesArvoreAbstrata.h"
#include "Tokens.h"
#include <stdio.h>
#include "Tradutor.h"



Tradutor::Tradutor(){
     expressao                         = NULL;
     stmTemp                           = NULL;
     bytes_para_passagem_de_parametros = 0;
     programaPrincipal                 = 0;
     numero_temporario                 = 0;
     numero_rotulo                     = 0;
     numero_literal                    = 0;
     lista_sentenca                    = new StmList(NULL,NULL);  
     listaAcesso                       = NULL; 
     listaFragmentos                   = NULL;

};



//IdNode
void Tradutor::visit(IdNode *idNode){
	
	 Temp *regFP = new Temp("FP");
	 int offset, nivel;
     offset = idNode->offset;
     nivel  = idNode->escopo;
     
     if (nivel == 0){
        expressao = new MEM(new TEMP(regFP));
     }
     else{
        expressao = new TEMP(regFP);  
     }

     expressao = new MEM(
                     new BINOP(PLUS,expressao,new CONST(offset)));
    
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

//Write
void Tradutor::visit(WriteNode* writeNode){
  
     ExpList*listaParametros          = NULL;
     ExpList*ordListaParametros = NULL;
     
     if (writeNode->expressionListNode){
        ExpressionListNode *listaExpressao = writeNode->expressionListNode;
        while (listaExpressao != NULL){
              (listaExpressao->expressionNode)->accept(this);
              listaParametros = new ExpList(expressao,listaParametros);
              listaExpressao  = listaExpressao->expressionListNode;
        }
       
        while (listaParametros != NULL){
              ordListaParametros = new ExpList(listaParametros->prim, ordListaParametros);
              listaParametros          = listaParametros->prox;
        }
     }
     listaParametros = NULL;
     
     //Chamada da funcao
     Temp* SL  = new Temp("SL");
     Temp* FP  = new Temp("FP");
     Label* rotuloProcedimento = new Label("PROCEDIMENTO$WRITE");
     
     if (!programaPrincipal){
        expressao = new MEM(new TEMP(FP));
     }
     else{
        expressao = new TEMP(FP);  
     }
     
     stmTemp = new EXP(
                    new ESEQ(
                        new MOVE(new TEMP(SL),expressao),
                        new CALL(
                            new NAME(rotuloProcedimento),
                            new ExpList(new TEMP(SL), ordListaParametros))));
     addStm(stmTemp);

};

//Array
void Tradutor::visit(ArrayNode* arrayNode){
    
    
     if (arrayNode->idNode) (arrayNode->idNode)->accept(this);
     Exp * expressaoEsquerda;
     expressaoEsquerda =  expressao;
     if (arrayNode->expressionNode) (arrayNode->expressionNode)->accept(this);
     Exp * expressaoDireita;
     expressaoDireita =  expressao;
    

     expressao = new MEM(
                     new BINOP(PLUS,expressaoEsquerda,
                         new BINOP(MULT,new CONST(4), 
                             new BINOP(MINUS,expressaoDireita, 
                                 new CONST(arrayNode->idNode->offset)))));


};

//Assign
void Tradutor::visit(AssignNode *o){
	if (o->idNode){
		o->idNode->accept(this);
        Exp * esquerda = expressao;
		
        o->expressionNode1->accept(this);
		Exp * direita = expressao;
		
        Stm * stmAssign = new MOVE(new MEM(esquerda),direita);
		 
	}else{
		o->arrayNode->accept(this);
        Exp * esquerda = expressao;
		
        o->expressionNode1->accept(this);
		Exp * direita = expressao;
		
        stmTemp = new MOVE(new MEM(esquerda),direita);
		
	}
 
 addStm(stmTemp);
};

//While
void Tradutor::visit(WhileNode* whileNode){
     (whileNode->expressionNode)->accept(this);
     Exp* expressaoCondicional = expressao;
     (whileNode->statementNode)->accept(this);
     Stm* sentencaEnquanto = stmTemp;
     
     char rotulo[64];
     printf(rotulo,"LABEL%d$TESTE",++numero_rotulo);
     Label* rotuloTeste  = new Label(rotulo);
     printf(rotulo,"LABEL%d$INICIO",numero_rotulo);
     Label* rotuloInicio = new Label(rotulo);
     printf(rotulo,"LABEL%d$FIM",numero_rotulo);
     Label* rotuloFim    = new Label(rotulo);
     
     stmTemp = new SEQ(
                    new LABEL(rotuloTeste),
                    new SEQ(new CJUMP(NE, expressaoCondicional, new CONST(0), rotuloInicio, rotuloFim),
                        new SEQ(new LABEL(rotuloInicio),
                            new SEQ( sentencaEnquanto,
                                new SEQ( 	new JUMP(new NAME(rotuloTeste)),
                                    new LABEL(rotuloFim))))));
                                    

     addStm(stmTemp);
}

//Rel Op
void Tradutor::visit(RelOpNode* relOpNode){
 
     (relOpNode->expressionNode1)->accept(this);
     Exp* esquerda = expressao;
     (relOpNode->expressionNode2)->accept(this);
     Exp* direita = expressao;
     
     char rotulo[64];
     printf(rotulo,"TEMP$%d",++numero_temporario);
     Temp* temporario           = new Temp(rotulo); 
     printf(rotulo,"LABEL%d$VERDADEIRO",++numero_rotulo);
     Label*     rotuloVerdadeiro = new Label(rotulo);
     printf(rotulo,"LABEL%d$FALSO",numero_rotulo);
     Label*     rotuloFalso      = new Label(rotulo);
     
     expressao = new ESEQ(
                     new SEQ( new MOVE( new TEMP(temporario),new CONST(1)), 
                         new SEQ( new CJUMP(relOpNode->op, esquerda, direita, rotuloVerdadeiro, rotuloFalso),
                             new SEQ( new LABEL(rotuloFalso),
                                 new SEQ( new MOVE( new TEMP(temporario), new CONST(0)),
                                     new LABEL(rotuloVerdadeiro))))), 
                                       new TEMP(temporario));
   
}

//Bool Op
void Tradutor::visit(BoolOpNode* boolOpNode){
 
     (boolOpNode->expressionNode1)->accept(this);
     Exp* esquerda = expressao;
     (boolOpNode->expressionNode2)->accept(this);
     Exp* direita = expressao;
     
     char rotulo[64];
     printf(rotulo,"TEMP$%d",++numero_temporario);
     Temp* temporario           = new Temp(rotulo); 
     printf(rotulo,"LABEL%d$VERDADEIRO",++numero_rotulo);
     Label*     rotuloVerdadeiro = new Label(rotulo);
     printf(rotulo,"LABEL%d$FALSO",numero_rotulo);
     Label*     rotuloFalso      = new Label(rotulo);
 
     expressao = new ESEQ(
                     new SEQ( new MOVE(new TEMP(temporario), esquerda),
                         new SEQ( new CJUMP(boolOpNode->op, direita, new CONST(0), rotuloVerdadeiro, rotuloFalso),
                             new SEQ( new LABEL(rotuloVerdadeiro),
                                 new SEQ( new MOVE( new TEMP(temporario), new CONST(1)), new LABEL(rotuloFalso))))),
                                     new TEMP(temporario));

}

//Read
void Tradutor::visit(ReadNode* readNode){
    if (readNode->idNode) (readNode->idNode)->accept(this);
     if (readNode->arrayNode) (readNode->arrayNode)->accept(this);

     ExpList* listaParametros    = NULL;
     ExpList* ordListaParametros = NULL;
     
     if (readNode->expressionListNode != NULL){
        ExpressionListNode* listaExpressao = readNode->expressionListNode;
        while (listaExpressao != NULL){
              (listaExpressao->expressionNode)-> accept(this);
              listaParametros = new ExpList(expressao,listaParametros);
              listaExpressao  = listaExpressao->expressionListNode;
        }

        while (listaParametros != NULL){
              ordListaParametros = new ExpList(listaParametros->prim, ordListaParametros);
              listaParametros          = listaParametros->prox;
        }
     }
     listaParametros = NULL;
     
     //Chamada da funcao
     Temp* SL  = new Temp("SL");
     Temp* FP  = new Temp("FP");
     Label* rotuloProcedimento = new Label("PROCEDIMENTO$READ");
     
     if (!programaPrincipal){
        expressao = new MEM(new TEMP(FP));
     }
     else{
        expressao = new TEMP(FP);  
     }
     
     stmTemp = new EXP(
                    new ESEQ(new MOVE( new TEMP(SL),expressao),
                        new CALL( new NAME(rotuloProcedimento),
                            new ExpList(new TEMP(SL), ordListaParametros))));
     
     addStm(stmTemp);
};

//Stm List
void Tradutor::visit(StatementListNode* stmtListNode){
     if ((stmtListNode->statementNode) != NULL) (stmtListNode->statementNode)->accept(this);
     if ((stmtListNode->statementListNode) != NULL) (stmtListNode->statementListNode)->accept(this);
};

//Literal
void Tradutor::visit(LiteralNode* literalNode){
  
     char rotulo[64];
     printf(rotulo,"CONSTANTE_LITERAL$%d",++numero_literal);
     Label* rotuloLiteral = new Label(rotulo);
     Fragmento* consLiteral = new constanteLiteral(literalNode->literal);
     
     addFragmento(consLiteral);
     
     expressao = new NAME(rotuloLiteral);
};

//Number
void Tradutor::visit(NumberNode* numberNode){
     
     if (numberNode->tipo == INTEGER){
        expressao = new CONST(numberNode->number);
     }
     else{
        expressao = new CONSTF(numberNode->number);  
     }
};

//Not
void Tradutor::visit(NotNode* notNode){
  
     (notNode->expressionNode)->accept(this);
     Exp* esquerda = expressao;

     expressao = new BINOP(MINUS, new CONST(0), esquerda);
};

//If
void Tradutor::visit(IfNode* ifNode){
    
     (ifNode->expressionNode)->accept(this);
     Exp* condicional = expressao;
     (ifNode->statementNode1)->accept(this);
     Stm* entao = stmTemp;
     
     if (ifNode->statementNode2!= NULL){
        (ifNode->statementNode2)->accept(this);
        Stm* senao = stmTemp;

        char rotulo[64];
        sprintf(rotulo,"LABEL%d$ENTAO",++numero_rotulo);
        Label* rotuloEntao = new Label(rotulo);
        sprintf(rotulo,"LABEL%d$SENAO",numero_rotulo);
        Label* rotuloSenao = new Label(rotulo);
        sprintf(rotulo,"LABEL%d$FIM",numero_rotulo);
        Label* rotuloFim   = new Label(rotulo);
     
        stmTemp = new SEQ(
                       new CJUMP(NE, condicional, new CONST(0), rotuloEntao, rotuloSenao),
                       new SEQ(new LABEL(rotuloEntao),
                           new SEQ(entao,
                               new SEQ(new JUMP(new NAME(rotuloFim)),
                                   new SEQ(new LABEL(rotuloSenao),
                                       new SEQ(senao,
                                           new LABEL(rotuloFim)))))));
     }
     else{
          
             char rotulo[64];
             sprintf(rotulo,"LABEL%d$ENTAO",++numero_rotulo);
             Label* rotuloEntao = new Label(rotulo);
             sprintf(rotulo,"LABEL%d$FIM",numero_rotulo);
             Label* rotuloFim   = new Label(rotulo);
     
          stmTemp = new SEQ(new CJUMP(NE, condicional, new CONST(0), rotuloEntao, rotuloFim),
                         new SEQ(new LABEL(rotuloEntao),
                             new SEQ(entao,
                                 new LABEL(rotuloFim))));
     }
     
     addStm(stmTemp);
};

//Fragment
void Tradutor::visit(FragmentNode* fragmentNode){
      
     programaPrincipal = 0;    
     int bytes = 0;
     StatementNode *primeiro = (fragmentNode->statementListNode)->statementNode;
    
    //Verifica se o Fragmento é nomeado
    if ( typeid(* primeiro).name() == typeid(NameDeclNode).name() ){
             NameDeclNode *parametros = dynamic_cast<NameDeclNode *>(primeiro);
             
             IdListNode *listaId = parametros->idListNode->idNode->parametros;
             
             while (listaId != NULL){
                   bytes += listaId->idNode->tamanho;
                    listaId = listaId->idListNode;
             }
             
             if (bytes>bytes_para_passagem_de_parametros){
                bytes_para_passagem_de_parametros = bytes;
             }
             
             //Parametros
             ExpList* listaParametros          = NULL;
             ExpList* ordListaParametros       = NULL;
             
             if (fragmentNode->statementListNode != NULL){
                StatementListNode* listaExpressao = fragmentNode->statementListNode;
                while (listaExpressao != NULL){
                      (listaExpressao->statementNode)-> accept(this);
                      listaParametros = new ExpList(expressao,listaParametros);
                      listaExpressao  = listaExpressao->statementListNode;
                }
                
                while (listaParametros != NULL){
                      ordListaParametros = new ExpList(listaParametros->prim, ordListaParametros);
                      listaParametros          = listaParametros->prox;
                }
             }
             listaParametros = NULL;
             
             //Chamada da funcao
             char rotulo[64];
             printf(rotulo,"PROCEDIMENTO$%s",retornaCharToken(parametros->idListNode->idNode->id));
             
             Temp* SL  = new Temp("SL");
             Temp* FP  = new Temp("FP");
             Label* rotuloProcedimento = new Label(rotulo);
             
             if (!programaPrincipal){
                expressao = new MEM(new TEMP(FP));
             }
             else{
                expressao = new TEMP(FP);  
             }
             
             expressao = new ESEQ(
                             new MOVE(
                                 new TEMP(SL),expressao),
                             new CALL(
                                 new NAME(rotuloProcedimento),
                                 new ExpList(new TEMP(SL), ordListaParametros)));
  }else{
     char rotulo[64];
     printf(rotulo,"LABEL%d$INICIO",++numero_rotulo);
     Label* rotuloInicio = new Label(rotulo);
     printf(rotulo,"LABEL%d$FIM",numero_rotulo);
     Label* rotuloFim    = new Label(rotulo);
     
     if (fragmentNode->statementListNode != NULL){
     
        StatementListNode*    listaSentenca;
        StmList* listaSentencaRI           = NULL;
        StmList* ordlistaSentencaRI       = NULL;
        
        listaSentenca = fragmentNode->statementListNode;
        
        while (listaSentenca != NULL){ 
              (listaSentenca->statementNode)-> accept(this);
              listaSentencaRI = new StmList(stmTemp,listaSentencaRI);
              listaSentenca = listaSentenca->statementListNode;
        }
        
        /*Ordenando a lista de sentencas.*/
        while (listaSentencaRI != NULL){
              ordlistaSentencaRI = new StmList(listaSentencaRI->prim, ordlistaSentencaRI);
              listaSentencaRI          = listaSentencaRI->prox;
        }
        listaSentencaRI = NULL;
        lista_sentenca             = ordlistaSentencaRI;
        stmTemp = new SEQ(new LABEL(rotuloInicio),
                       new SEQ(stmTemp, 
                           new LABEL(rotuloFim)));
     }
     else{
        stmTemp = new SEQ(
                       new LABEL(rotuloInicio),
                       new LABEL(rotuloFim));
     }
  }
      addStm(stmTemp); 
      programaPrincipal = 1;
};

//NameDecl
void Tradutor::visit(NameDeclNode* nameDeclNode){
   	
	IdListNode* idList = nameDeclNode->idListNode;
	inFrame * iFrame = new inFrame(idList->idNode->offset);
	
	
	if (listaAcesso == NULL){
		listaAcesso = new ListaAcesso(iFrame,NULL);
	}else{
		ListaAcesso *nova = listaAcesso;
        while (nova->prox != NULL){
			nova = nova->prox;
		}
		nova->prox = new ListaAcesso(iFrame,NULL);
	}
	
  
	while (idList != NULL){
		IdNode* id = idList->idNode;	
		inFrame * iFrame =new inFrame(id->offset);
		
		ListaAcesso *atual = listaAcesso;
		while (atual->prox != NULL){
			atual = atual->prox;
		}
		ListaAcesso * listaAcesso2 = new ListaAcesso(iFrame,NULL);
		atual->prox = listaAcesso2;
				
		idList = idList->idListNode;
	}
	
   
    if ((nameDeclNode->modifierListNode) != NULL) (nameDeclNode->modifierListNode)->accept(this);
      (nameDeclNode->idListNode)->accept(this);
   
};


//Program
void Tradutor::visit(ProgramNode* programNode){

     programaPrincipal = 1;
     lista_sentenca = NULL;
     
     if (programNode->stmtListNode != NULL){
         (programNode->stmtListNode)->accept(this);
     }


     
     FrameMips * frame = new FrameMips(new Label("PROCEDIMENTO$PRINCIPAL"),listaAcesso);
     
     Fragmento* procedimento = new Procedimento(frame,lista_sentenca);
     
     addFragmento(procedimento);
    
      VisitorArvoreIntermediaria* visitorAI = new VisitorArvoreIntermediaria();
      listaFragmentos->accept(visitorAI);
};



void Tradutor::visit(FragCallNode* fragCallNode){
   
     (fragCallNode->idNode)->accept(this);
     (fragCallNode->expressionList)->accept(this);

	Temp* SL  = new Temp("SL");
	Temp* FP  = new Temp("FP");
	ExpList * expList = new ExpList(new TEMP(SL),NULL);
	while(fragCallNode->expressionList != NULL){
		if (fragCallNode->expressionList->expressionNode != NULL){
	    	fragCallNode->expressionList->expressionNode->accept(this);
			Exp * expT = expressao;	
			ExpList *lAtual = expList;
			
            while (lAtual->prox != NULL){
				lAtual = lAtual->prox;	
			}
			ExpList * expT2 = new ExpList(expT,NULL);
			lAtual->prox = expT2;	
			fragCallNode->expressionList = fragCallNode->expressionList->expressionListNode;
		}
	}    	
		
	if (!programaPrincipal){
                expressao = new MEM(new TEMP(FP));
                }
             else{
                expressao = new TEMP(FP);  
             }
             	
	stmTemp = new EXP(new ESEQ( new MOVE( new TEMP(SL),expressao),
								new CALL(
									new NAME(new Label(retornaCharToken(fragCallNode->idNode->id))),
									expList)
								)
							);
	
    

      addStm(stmTemp);										
	
};

void Tradutor::visit(ConstantNode* constantNode){ 
     (constantNode->nameNode)->accept(this);
     (constantNode->value)->accept(this);
};

void Tradutor::visit(BitwiseOpNode* bitwiseOpNode){
     (bitwiseOpNode->expressionNode1)->accept(this);
     (bitwiseOpNode->expressionNode2)->accept(this);
};

void Tradutor::visit(ExpressionListNode* expressionListNode){
     if ((expressionListNode->expressionNode) != NULL )(expressionListNode->expressionNode)->accept(this);
     if ((expressionListNode->expressionListNode) != NULL )(expressionListNode->expressionListNode)->accept(this);
};
void Tradutor::visit(CallNode* callNode){    
     (callNode->idNode)->accept(this);
     (callNode->expressionListNode)->accept(this);
};

void Tradutor::visit(IdListNode* idListNode){
     if ((idListNode->idListNode) == NULL){ 
         (idListNode->idNode)->accept(this);
     }else{
         (idListNode->idNode)->accept(this);
         (idListNode->idListNode)->accept(this);
     }
};

void Tradutor::visit(ModifierListNode* modifierListNode){
     if (modifierListNode->modifierNode)(modifierListNode->modifierNode)->accept(this);        
     if (modifierListNode->modifierListNode)(modifierListNode->modifierListNode)->accept(this);    
};

void Tradutor::visit(ModifierNode* modifierNode){
  
}; 

void Tradutor::visit(NegativeNode* negativeNode){
     (negativeNode->expressionNode)->accept(this);
};

ListaDeFragmentos* Tradutor::getListaFragmentos(){

};

void Tradutor::addFragmento(Fragmento * frag){
	if (listaFragmentos == NULL){
		listaFragmentos = new ListaDeFragmentos(frag,NULL);
	}else{
		ListaDeFragmentos *temp = listaFragmentos;
		while (temp->prox != NULL){
			temp = temp->prox;	
		}
		ListaDeFragmentos * temp2 = new ListaDeFragmentos(frag,NULL);
		temp->prox = temp2;	
		listaFragmentos = temp;
	}    	
};

void Tradutor::addStm(Stm * stm){
	if (lista_sentenca == NULL){
		lista_sentenca = new StmList(stm,NULL);
	}else{
		StmList *temp = lista_sentenca;
		while (temp->prox != NULL){
			temp = temp->prox;	
		}
		StmList * temp2 = new StmList(stm,NULL);
		temp->prox = temp2;	
		lista_sentenca = temp;
	}		
}




