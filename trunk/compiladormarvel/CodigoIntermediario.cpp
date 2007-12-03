#include <stdlib.h>
#include <stdio.h>
#include "CodigoIntermediario.h"

//Lista de Fragmentos
ListaDeFragmentos::ListaDeFragmentos(Fragmento * atual, ListaDeFragmentos * prox){
	this->atual = atual;
	this->prox = prox;
};
void ListaDeFragmentos::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ListaDeFragmentos::~ListaDeFragmentos(){
	delete this->atual;
	if ( this->prox != NULL ){
		delete this->prox;
	}
};

//Procedimentos
Procedimento::Procedimento(Frame *frame, StmList *corpo){
	this->frame = frame;
	this->corpo = corpo;
};
void Procedimento::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
Procedimento::~Procedimento(){
	delete this->frame;
	delete this->corpo;
};


//Constante Literal
constanteLiteral::constanteLiteral(int i){
	this->indice = i;
};
void constanteLiteral::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
constanteLiteral::~constanteLiteral(){
};


//Nome Real
nomeReal::nomeReal(Label *l,float r){
	this->l = l;
	this->r = r;
};
void nomeReal::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
nomeReal::~nomeReal(){
	delete this->l;
}

//Nome Inteiro
nomeInteiro::nomeInteiro(Label *l,int i){
	this->l = l;
	this->i = i;
};
void nomeInteiro::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
nomeInteiro::~nomeInteiro(){
	delete this->l;
};

//Temp
Temp::Temp(char * s){
	this->s = s;
};
Temp::Temp(){
	this->s = NULL;
}
void Temp::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};	
Temp::~Temp(){};

//Temp List
TempList::TempList(Temp *t, TempList *tl){
	this->t = t;
	this->tl = tl;
};
void TempList::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
TempList::~TempList(){};


//Label
Label::Label(char * s){
	this->s = s;
};
Label::Label(){
	this->s = NULL;
};
void Label::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
Label::~Label(){};

//Label List
LabelList::LabelList(Label *l, LabelList *ll){
	this->l = l;
	this->ll = ll;
};
void LabelList::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
LabelList::~LabelList(){};

//Lista Acesso
ListaAcesso::ListaAcesso(inFrame *l, ListaAcesso *prox){
	this->l = l;
	this->prox = prox;
};
void ListaAcesso::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ListaAcesso::~ListaAcesso(){
	delete this->l;
	if (this->prox != NULL){
		delete this->prox;
	}
};



//In Frame
inFrame::inFrame(int offset){
	this->offset = offset;
};
Stm * inFrame::codigoAcesso(Temp *FP){
	return new EXP(new MEM(new BINOP(PLUS,new TEMP(FP),new CONST(this->offset))));
};
void inFrame::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
inFrame::~inFrame(){};


//In Reg
inReg::inReg(Temp temp){
	this->temp = temp;
};
Stm * inReg::codigoAcesso(Temp *FP){
	return new EXP(new TEMP(FP));
};
void inReg::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
inReg::~inReg(){};


//Frame MIPS
FrameMips::FrameMips(Label *rotulo, ListaAcesso *dadosLocais){
	this->rotulo = rotulo;
	this->dadosLocais = dadosLocais;
};
void FrameMips::adicionaParam(int escapa, int tambytes){};
void FrameMips::adicionaLocal(int escapa, int tambytes){};		
void FrameMips::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
FrameMips::~FrameMips(){
	delete this->rotulo;
	delete this->dadosLocais;
};		






