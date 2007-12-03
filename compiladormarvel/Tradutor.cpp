#include "ClassesArvoreAbstrata.h"
#include "Tokens.h"
#include <stdio.h>
#include "Tradutor.h"


Tradutor::Tradutor(){
		this->listaFragmentos = NULL;
		this->dados = NULL;
		this->corpo = NULL;
		this->expTemp = NULL;
		this->stmTemp = NULL;
		this->tamanhoPalavra = 4;
		//inicializacao da pilha de fragmentos
		this->topoFrag = &this->pilhaFrag; 
		this->topoFrag->proximo = NULL;
		this->adicionaStm = 1;
		this->adicionaBloco = 1;
		this->numBloco = 1;
};

ListaDeFragmentos * Tradutor::getListaFragmentos(){
	return this->listaFragmentos;
};

void Tradutor::empilhaFrag(StmList *corpo, ListaAcesso *dados){
	TPilhaFragmentos *novo;
	novo = (TPilhaFragmentos *) malloc(sizeof(TPilhaFragmentos));
	novo->corpo = corpo;
	novo->dados = dados;
	novo->proximo = topoFrag->proximo;
	topoFrag->proximo = novo;	
};

void Tradutor::desempilhaFrag(){
	TPilhaFragmentos *elemento;
	elemento = topoFrag->proximo;
	topoFrag->proximo = elemento->proximo;
	free(elemento);
};

TPilhaFragmentos * Tradutor::getTopoFrag(){
	TPilhaFragmentos *elemento;
	elemento = topoFrag->proximo;
	return elemento;	
};

void Tradutor::adicionaFragmento(Fragmento* frag){
	if (this->listaFragmentos == NULL){
		this->listaFragmentos = new ListaDeFragmentos(frag,NULL);
	}else{
		ListaDeFragmentos *atual = this->listaFragmentos;
		while (atual->prox != NULL){
			atual = atual->prox;	
		}
		ListaDeFragmentos * fl = new ListaDeFragmentos(frag,NULL);
		atual->prox = fl;	
	}    	
}

void Tradutor::adicionaSentenca(Stm * sentenca){
	if (this->corpo == NULL){
		this->corpo = new StmList(sentenca,NULL);
	}else{
		StmList *atual = this->corpo;
		while (atual->prox != NULL){
			atual = atual->prox;	
		}
		StmList * sl = new StmList(sentenca,NULL);
		atual->prox = sl;	
	}		
}

void Tradutor::salvaFrag(){
	/**
	esse metodo salva as informacoes necessarias para a construcao do fragmento
	no caso, o corpo e os dados, os valores atuais sao empilhados e em seguida liberados para 
	o novo fragmento. É usado quando o visitor chega em um no de novo fragmento (funcao,proc)
	**/
	this->empilhaFrag(this->corpo,this->dados);
	this->corpo = NULL;
	this->dados = NULL;
}

void Tradutor::restauraFrag(){
	/**
	esse metodo restaura as informacoes do fragmento anterior, incluindo o fragmento principal
	É usado quando o visitor sai de um no fragmento (funcao,proc)
	**/
	TPilhaFragmentos * topo = this->getTopoFrag();
	this->corpo = topo->corpo;
	this->dados = topo->dados;
	this->desempilhaFrag();	
}

Stm * Tradutor::seqBloco(FragmentNode *o){
	/**
	esse metodo cria a sequencia de comandos do bloco
	**/
	if (o->s1 != NULL){
		o->sl->s->accept(this);
		Stm * stm = this->stmTemp;
		o->sl = o->sl->sl;
		return new SEQ(stm,this->seqBloco(o));
	}else{
		return new LABEL(new Label("FIM$BLOCO"));
	}
}

Stm * Tradutor::seqMoves(WriteNode *o){
	/**
	esse metodo cria uma sequencia de de moves para stdout ... usado no write
	**/
	if (o->el != NULL){
		o->el->e->accept(this);
		Exp * exp = this->expTemp;
		Stm * stm = new MOVE(new TEMP(new Temp("stdout")),exp);
		o->el = o->el->el; //adiantar ponteiro
		return new SEQ(stm,this->seqMoves(o));
	}else{
		return NULL;
	}
}

Stm * Tradutor::seqMoves(ReadNode *o){
	/**
	esse metodo cria uma sequencia de de moves para stdout ... usado no read
	**/
	if (o->el != NULL){
		o->el->e->accept(this);
		Exp * exp = this->expTemp;
		Stm * stm = new MOVE(exp,new TEMP(new Temp("stdin")));
		o->el = o->el->el; //adiantar ponteiro
		return new SEQ(stm,this->seqMoves(o));
	}else{
		return NULL;
	}
}

Exp * Tradutor::acessoNaoLocal(int n){
	if ( n != 0 ){
		return new MEM(new BINOP(MAIS,new CONST(0),this->acessoNaoLocal(n-1)));
	}else{
		return new TEMP(FP);
	}
}

Exp * Tradutor::seqMem(int n){
	if (n != 0){
		return new MEM(this->seqMem(n-1));
	}else{
		return new TEMP(FP);
	}
}

void Tradutor::visit(Stmt *o){
};

void Tradutor::visit(ModifierNode *o){
};

void Tradutor::visit(ProgramNode* o){
	if ( o->sl != NULL ){
		o->sl->accept(this);
	}
	//criando o frame do procedimento Principal
	FrameMips * frame = new FrameMips(new Label("principal"),this->dados);
	
	Procedimento * proc = new Procedimento(frame,this->corpo);
	
	this->adicionaFragmento(proc);	
};

void Tradutor::visit(StatementListNode *o){
	if (o->s != NULL){
        o->s->accept(this);
	}
	if ( o->sl != NULL ){
		o->sl->accept(this);
	}
};

void Tradutor::visit(Exp *o){
	//o->visit(this);
};

void Tradutor::visit(ExpressionListNode *o){
	o->e->accept(this);
	if ( o->el != NULL ){
		o->el->accept(this);
	}
};
	
void Tradutor::visit(ModifierListNode *o){
	o->m->accept(this);
	if ( o->ml != NULL ){
		o->ml->accept(this);
	}
};

void Tradutor::visit(IdListNode *o){
	o->i->accept(this);
	if ( o->il != NULL ){
		o->il->accept(this);
	}
};

void Tradutor::visit(IfNode *o){
    o->e->accept(this); //expressao
    Exp * exp = this->expTemp;
    this->adicionaStm = 0;
    this->adicionaBloco = 0;
    o->s1->accept(this); //statement1
    Stm * stmTrue = this->stmTemp;
    Stm * stmCondicao;
	if ( o->s2 != NULL ){ //s2 é o statement do else , diferente de NULO
		o->s2->accept(this);
	    Stm * stmFalse = this->stmTemp;		
		stmCondicao = new SEQ(
								new CJUMP(DIFERENTE,exp,new CONST(0),new Label("ENTAO"),new Label("SENAO")),
								new SEQ(
									new LABEL(new Label("ENTAO")),
									new SEQ(
										new SEQ(
											stmTrue,
											new JUMP(new NAME(new Label("FIMSE")))
										),
										new SEQ(
											new LABEL(new Label("SENAO")),
											new SEQ(
												stmFalse,
												new LABEL(new Label("FIMSE"))
											)
										)
									)
								)
							);
	    
	}else{
		stmCondicao = new SEQ(new CJUMP(DIFERENTE,exp,new CONST(0),new Label("ENTAO"),new Label("FIM")),new SEQ(new LABEL(new Label("ENTAO")),new SEQ(stmTrue,new LABEL(new Label("FIM")))));
	}
	this->adicionaSentenca(stmCondicao);
	this->adicionaStm = 1;
    this->adicionaBloco = 1;	

};

void Tradutor::visit(WhileNode *o){
	o->e->accept(this); //expressao
	Exp * exp = this->expTemp;
	
    this->adicionaStm = 0;
    this->adicionaBloco = 0;

   	o->s->accept(this); //statement    
    Stm * stm = this->stmTemp;	

    Stm * stmWhile = new SEQ(
    					new LABEL(new Label("TESTE")),
    					new SEQ(
    						new CJUMP(DIFERENTE,exp,new CONST(0),new Label("INICIO"),new Label("FIM")),
    						new SEQ(
    							new LABEL(new Label("INICIO")),
    							new SEQ(
    								stm,
    								new SEQ(
    									new JUMP(new NAME(new Label("TESTE"))),
    									new LABEL(new Label("FIM"))
    								)
    							)
    						)
    					)
    				);
	this->adicionaSentenca(stmWhile);

    this->adicionaStm = 1;
    this->adicionaBloco = 1;
	
   
};

void Tradutor::visit(WriteNode *o){
	this->stmTemp = this->seqMoves(o);
	if (this->adicionaStm){
		this->adicionaSentenca(this->stmTemp);
	}
};

void Tradutor::visit(IdNode *o){
	if (( o->p != NULL ) && (o->p->vector == 0)){
		if (o->p->tipoId == VARIAVEL){
			if (o->dadoLocal){
				this->expTemp = new MEM(new BINOP(MAIS,new TEMP(FP),new CONST(o->p->offset)));				
			}else{
				int diff = (o->nivelChamada - o->p->escopo);
				this->expTemp = new MEM(new BINOP(MAIS,new CONST(o->p->offset),this->acessoNaoLocal(diff)));				
			}	
		}
	}
};

void Tradutor::visit(NumberNode *o){
	if (o->isFloat){
		this->expTemp = new CONSTF(atof(getSymbol(o->num)));
	}else{
		this->expTemp = new CONST(atoi(getSymbol(o->num)));
	}
};

void Tradutor::visit(LiteralNode *o){
	this->expTemp = new NAME(new Label(getSymbol(o->lit)));
};

void Tradutor::visit(NameDeclNode *o){
	//o->id é um idlist
	Id * id = o->id->i;

	//cria o acesso local
	inFrame * inf = new inFrame(id->p->offset);
	
	//colocar na lista de acesso;
	if (this->dados == NULL){
		this->dados = new ListaAcesso(inf,NULL);
	}else{
		ListaAcesso *atual = this->dados;
		while (atual->prox != NULL){
			atual = atual->prox;
		}
		ListaAcesso * la = new ListaAcesso(inf,NULL);
		atual->prox = la;
	}
	
	//percorrendo idlist
	Idlist * il = o->id->il;
	while (il != NULL){
		Id * id = il->i;	
		inFrame * inf = new inFrame(id->p->offset);
		
		ListaAcesso *atual = this->dados;
		while (atual->prox != NULL){
			atual = atual->prox;
		}
		ListaAcesso * la = new ListaAcesso(inf,NULL);
		atual->prox = la;
				
		il = il->il;
	}
	o->mod->accept(this);
	o->id->accept(this);
};

void Tradutor::visit(FragmentNode *o){
	int isConstante = 0;
	int isConstanteLiteral = 0;
	int isConstanteNumerica	= 0;
	int isBloco = 0;
    if (o->mod != NULL) {
			o->mod->accept(this);
			o->id->accept(this);
			if (o->num != NULL){ //CONSTANTE NUMERICA
				isConstante = 1;
				isConstanteNumerica = 1;
				o->num->accept(this);
			}else{
				this->salvaFrag();
				o->sl->accept(this); //FUNCAO
			}
	}else{
	    if (o->id != NULL) { 
			o->id->accept(this);
			if ( o->lit != NULL ){ 
				isConstante = 1;				
				isConstanteLiteral = 1;				
				o->lit->accept(this); //CONSTANTE LITERAL
			}else{
				this->salvaFrag();				
				o->sl->accept(this); //PROCEDIMENTO
			}
		}else{
			if (o->sl != NULL) { 
				isBloco = 1;	//BLOCO
				this->adicionaStm = 0;
				this->stmTemp = new SEQ(new LABEL(new Label("INICIO$BLOCO")),this->seqBloco(o));
				if (this->adicionaBloco){
					this->adicionaSentenca(this->stmTemp);						
				}
				this->adicionaStm = 1;				
			}
		}		
	}
	if (!isBloco){
		if ( isConstante ){
			if (isConstanteLiteral){
				constanteLiteral * ci = new constanteLiteral(o->lit->lit);
				this->adicionaFragmento(ci);
			}else{
				if (isConstanteNumerica){
					if (o->num->isFloat){
						nomeReal * nr = new nomeReal(new Label(getSymbol(o->id->id)),atof(getSymbol(o->num->num)));
						this->adicionaFragmento(nr);					
					}else{
						nomeInteiro * ni = new nomeInteiro(new Label(getSymbol(o->id->id)),atoi(getSymbol(o->num->num)));
						this->adicionaFragmento(ni);											
					}
				}
			}
		}else{		
			//final do fragment, caso funcao e procedimentos criar o frame
			//this->corpo e this->dados nesse ponto sao do fragment
			FrameMips * frame = new FrameMips(new Label(getSymbol(o->id->id)),this->dados);
			Procedimento * proc = new Procedimento(frame,this->corpo);
			this->adicionaFragmento(proc);
	
			this->restauraFrag();
		}
	}

};

void Tradutor::visit(CallNode *o){
	int diff;
	if (o->id->nivelChamada != 0){
		diff = (o->id->nivelChamada - o->id->p->escopo);
	}
	else{
		diff = 0;
	}
		
	ExpList * expList = new ExpList(new TEMP(SL),NULL);
	while(o->e != NULL){ //o->e é a ExpList
		if ( o->e->e != NULL){
			o->e->e->accept(this); //o->e->e e a expressao
			Exp * exp = this->expTemp;	
		
			//adiciona os parametros a lista de expressao
			ExpList *atual = expList;
			while (atual->prox != NULL){
				atual = atual->prox;	
			}
			ExpList * el = new ExpList(exp,NULL);
			atual->prox = el;	
			o->e = o->e->el;
		}
	}    	
		
	this->expTemp = new ESEQ(
						new MOVE(
							new TEMP(SL),
							seqMem(diff)),
						new CALL(
							new NAME(new Label(getSymbol(o->id->id))),
							expList
						)
					);
};

void Tradutor::visit(ArrayNode *o){
    o->e->accept(this);
	Exp * indice = this->expTemp;
	this->expTemp = new MEM(
							new BINOP(
								MAIS,
								new MEM(
									new BINOP(
										MAIS,
										new TEMP(FP),
										new CONST(o->id->p->offset)
									)
								),
								new BINOP(
									MULTIPLICACAO,
									new CONST(this->tamanhoPalavra),
									indice
								)
							)
						);
};

void Tradutor::visit(AssignNode *o){
	if (o->idNode != NULL){
		o->idNode->accept(this);
        Exp * esquerda = expTemp;
		
        o->expressionNode1->accept(this);
		Exp * direita = expTemp;
		
        Stm * stmAssign = new MOVE(esquerda,direita);
		stmTemp = stmAssign;

		if (adicionaStm){
			adicionaSentenca(stmAssign);
		}
		
	}else{
		o->ArrayNode->accept(this);
        Exp * esquerda =expTemp;
		
        o->ExpressionNode->accept(this);
		Exp * direita = expTemp;
		
        Stm * stmAssign = new MOVE(esquerda,direita);
		stmTemp = stmAssign;
		
		if (adicionaStm){
			adicionaSentenca(stmAssign);
		}

	}
};

void Tradutor::visit(ReadNode *o){
	this->stmTemp = this->seqMoves(o);
	if (this->adicionaStm){
		this->adicionaSentenca(this->stmTemp);
	}
};

void Tradutor::visit(FragCallNode *o){
	int diff;
	if (o->id->nivelChamada != 0){
		diff = (o->id->nivelChamada - o->id->p->escopo);
	}
	else{
		diff = 0;
	}
	
	ExpList * expList = new ExpList(new TEMP(SL),NULL);
	while(o->e != NULL){ //o->e é a ExpList
		if ( o->e->e != NULL){
			o->e->e->accept(this); //o->e->e e a expressao
			Exp * exp = this->expTemp;	
		
			//adiciona os parametros a lista de expressao
			ExpList *atual = expList;
			while (atual->prox != NULL){
				atual = atual->prox;	
			}
			ExpList * el = new ExpList(exp,NULL);
			atual->prox = el;	
			o->e = o->e->el;
		}
	}    	
		
	this->stmTemp = new EXP(
						new ESEQ(
								new MOVE(
									new TEMP(SL),
									seqMem(diff)),
								new CALL(
									new NAME(new Label(getSymbol(o->id->id))),
									expList
									)
								)
							);
	if (this->adicionaStm){
		this->adicionaSentenca(this->stmTemp);
	}									
										
};

void Tradutor::visit(RelOpNode *o){
    o->e1->accept(this);
    Exp * esquerda = this->expTemp;
	o->e2->accept(this);
	Exp * direita = this->expTemp;

	TEMP  *R = new TEMP(new Temp("R"));
   	Label *T = new Label("T");
   	Label *F = new Label("F");

   	this->expTemp = new ESEQ(
   						new SEQ(
   							new MOVE(R,new CONST(1)),
   							new SEQ(
   								new CJUMP(o->op,esquerda,direita,T,F),
   								new SEQ(
   									new LABEL(F),
   									new SEQ(
   										new MOVE(R,new CONST(0)),
   										new LABEL(T)
   									)
   								)
   							)
   						)
   						,R
   					);	  	  	
};

void Tradutor::visit(AddOpNode *o){
   o->e1->accept(this);
   Exp * esquerda = this->expTemp;
   o->e2->accept(this);
   Exp * direita = this->expTemp;
   this->expTemp = new BINOP(o->op, esquerda, direita);
};

void Tradutor::visit(MultOpNode *o){
   o->e1->accept(this);
   Exp * esquerda = this->expTemp;
   o->e2->accept(this);
   Exp * direita = this->expTemp;
   this->expTemp = new BINOP(o->op, esquerda, direita);
};

void Tradutor::visit(BoolOpNode *o){
   o->e1->accept(this);
   Exp * esquerda = this->expTemp;
   o->e2->accept(this);
   Exp * direita = this->expTemp;
   
   TEMP  *R = new TEMP(new Temp("R"));
   Label *L1 = new Label("L1");
   Label *L2 = new Label("L2");   
   Label *L3 = new Label("L3");

   if (o->op == AND){
	   this->expTemp = new ESEQ(
	   							new SEQ(
	   								new MOVE(
	   									 R,
	   									 new CONST(0)
											)
	   								,new SEQ(
	   									new CJUMP(DIFERENTE,esquerda,new CONST(0),L1,L2),
	   									new SEQ(
	   										new LABEL(L1),
	   										new SEQ(
	   											new CJUMP(DIFERENTE,direita,new CONST(0),L3,L2),
	   											new SEQ(
	   											    new LABEL(L3),
	   											    new SEQ(
	   											        new MOVE(R,new CONST(1)),
	   											        new LABEL(L2)
											        )
												)
											)
										)
									)
								)
								,R
						);
	}else{
		if (o->op == OR){
		this->expTemp = new ESEQ(
						new SEQ(
							new MOVE(R,esquerda),
							new SEQ(
								new CJUMP(DIFERENTE,direita,new CONST(0),L1,L2),
								new SEQ(
									new LABEL(L1),
									new SEQ(
										new MOVE(R,new CONST(1)),
										new LABEL(L2)
									)
								)
							)
						)
						,R
					);
		}
	}
};

void Tradutor::visit(BitwiseOpNode *o){
    o->e1->accept(this);
    o->e2->accept(this);
};

void Tradutor::visit(NotNode *o){
    o->e->accept(this);
    Exp * e = this->expTemp;
    this->expTemp = new BINOP(AND, new CONST(-1), e);
};

void Tradutor::visit(NegativeNode *o){
    o->e->accept(this);
    Exp * e = this->expTemp;
    this->expTemp = new BINOP(MULTIPLICACAO, new CONST(-1), e);
};

