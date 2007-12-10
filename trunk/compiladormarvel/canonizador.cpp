#include <stdio.h>
#include <typeinfo>
#include "canonizador.h"

// Blocos Basicos
BasicBlocks::BasicBlocks(StmList *sl) {
	this->blocos = NULL;
	this->stmList = NULL;
    rotulo = new Label("FIM");
    makeBlocks(sl);

};
void BasicBlocks::addStm(Stm *s) {
	if (this->stmList == NULL) this->stmList = new StmList(s,NULL);
	else {
		StmList *atual = this->stmList;
		while (atual->prox != NULL) atual = atual->prox;	
		StmList *sl = new StmList(s,NULL);
		atual->prox = sl;	
	}			
};
void BasicBlocks::doStms(StmList *sl){
    if (sl == NULL) doStms(new StmList(new JUMP(new NAME(this->rotulo)), NULL));
    else{
        // TODO esse typeof naum funciona
        if (typeid(sl->prim).name() == typeid(JUMP).name() || typeid(sl->prim).name() == typeid(CJUMP).name()) {
	        addStm(sl->prim);
	        makeBlocks(sl->prox);
        }else{ 
              if (typeid(sl->prim).name() == typeid(LABEL).name()){
                 LABEL *lbl = dynamic_cast<LABEL*>(sl->prim);
				 doStms(new StmList(new JUMP(new NAME(lbl->l)),sl));
              }else{
	             addStm(sl->prim);
	             doStms(sl->prox);
              }
			}
		}
};
void BasicBlocks::makeBlocks(StmList *sl) {
    if (sl != NULL){ 
	    if (typeid(sl->prim).name() == typeid(LABEL).name()) {
		    this->stmList = new StmList(sl->prim,NULL);
		    if (this->blocos == NULL) this->blocos = new StmListList(this->stmList,NULL);  	   				
			else{
				StmListList *atual = this->blocos;
				while (atual->prox != NULL)	atual = atual->prox;	
			 	atual->prox = new StmListList(this->stmList,NULL);
			}
			doStms(sl->prox);
		}else makeBlocks(new StmList(new LABEL(new Label()), sl));
	}
};



// StmListList
StmListList::StmListList(StmList *a, StmListList *p){
    this->atual = a;
    this->prox = p;
}



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

ExpCall::~ExpCall(){};



