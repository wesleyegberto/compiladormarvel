#include "canonizador.h"

// MoveCall
MoveCall::MoveCall(TEMP *o, CALL *d){
	origem  = o;
	destino = d;
};

ExpList *MoveCall::kids(){
	return origem->kids();
};

Stm *MoveCall::build(ExpList *kids){
	return new MOVE(destino, origem->build(kids));
};

void MoveCall::accept(VisitorArvoreIntermediaria *v){
    v->visit(this);
};

MoveCall::~MoveCall(){};


// StmExpList
StmExpList::StmExpList(Stm *s, ExpList *e) {
	this->stm = s;
	this->expList = e;
};
StmExpList::~StmExpList(){};



// ExpCall
ExpCall::ExpCall(CALL *c){
	this->call = c;
};

ExpList *ExpCall::kids(){
	return call->kids();
};

Stm *ExpCall::build(ExpList *kids){
	return new EXP(call->build(kids));
};

void ExpCall::accept(VisitorArvoreIntermediaria *v){
    v->visit(this);
};

ExpCall::~ExpCall(){};



// ListaStmList
ListaStmList::ListaStmList(StmList *a, ListaStmList *p){
    this->atual = a;
    this->prox = p;
}
