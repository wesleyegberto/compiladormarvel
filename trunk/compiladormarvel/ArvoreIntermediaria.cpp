#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include "ArvoreIntermediaria.h"


//ExpList
ExpList::ExpList(Exp *prim, ExpList *prox){
	this->prim = prim;
	this->prox = prox;
};
void ExpList::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList::~ExpList(){};


//StmList
StmList::StmList(Stm *prim, StmList *prox){
	this->prim = prim;
	this->prox = prox;
};
void StmList::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
StmList::~StmList(){};

// CONST
CONST::CONST(int value){
	this->value = value;
};
void CONST::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList * CONST::kids(){
     return NULL;        
};

Exp * CONST::build(ExpList * kids){
     return new CONST(this->value);
};
CONST::~CONST(){};

//CONSTF
CONSTF::CONSTF(float value){
	this->value = value;
};
void CONSTF::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList * CONSTF::kids(){
        return NULL;        
};

Exp * CONSTF::build(ExpList * kids){
        return new CONSTF(this->value); 
};
CONSTF::~CONSTF(){};

//NAME
NAME::NAME(Label *l){
	this->l = l;
};
void NAME::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList * NAME::kids(){
        return NULL;
};

Exp * NAME::build(ExpList * kids){
       return new NAME(this->l);
};
NAME::~NAME(){};
//TEMP
TEMP::TEMP(Temp *t){
	this->t = t;
};
void TEMP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList * TEMP::kids(){
        return NULL;
};

Exp * TEMP::build(ExpList * kids){
        return new TEMP(this->t);     
};
TEMP::~TEMP(){};

//BINOP
BINOP::BINOP(int binOP, Exp *left, Exp *right){
	this->binOP = binOP;
	this->left = left;
	this->right = right;
};
void BINOP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList * BINOP::kids(){
    return new ExpList(this->left, new ExpList(this->right,NULL));
};

Exp * BINOP::build(ExpList * kids){
    return new BINOP(this->binOP, kids->prim, kids->prox->prim); 
};
BINOP::~BINOP() {};

//MEM
MEM::MEM(Exp *e){
	this->e = e;
}
void MEM::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList * MEM::kids(){
     return new ExpList(this->e, NULL);        
};

Exp * MEM::build(ExpList * kids){
     return new MEM(kids->prim);
};
MEM::~MEM(){};


//CALL
CALL::CALL(Exp *func, ExpList *args){
	this->func = func;
	this->args = args;
};
void CALL::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList * CALL::kids(){
        return new ExpList(this->func, this->args);        
};

Exp * CALL::build(ExpList * kids){
     return new CALL(kids->prim, kids->prox);    
};
CALL::~CALL(){};


//ESEQ
ESEQ::ESEQ(Stm *s, Exp *e){
	this->s = s;
	this->e = e;
};
void ESEQ::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList * ESEQ::kids(){
        return NULL;
}
Exp * ESEQ::build(ExpList * kids){   
        return NULL;
};
ESEQ::~ESEQ(){};

//MOVE
MOVE::MOVE(Exp *dst, Exp *src){
	this->dst = dst;
	this->src = src;
};
void MOVE::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList *MOVE::kids() {
    if (typeid(* this->dst).name() == typeid(MEM).name())
	    return new ExpList(this->dst, new ExpList(this->src, NULL));
    else
        return new ExpList(this->src, NULL);        
}
Stm *MOVE::build(ExpList *kids){
    if (typeid(* this->dst).name() == typeid(MEM).name())
             return new MOVE(new MEM(kids->prim), kids->prox->prim);
         else
             return new MOVE(this->dst , kids->prim);    
};
MOVE::~MOVE(){};



//EXP
EXP::EXP(Exp *e){
	this->e = e;
};
void EXP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList *EXP::kids() {
    return new ExpList(this->e , NULL);       
}
Stm *EXP::build(ExpList *kids){
    return new EXP(kids->prim);
};
EXP::~EXP(){};

//JUMP
JUMP::JUMP(Exp *e){
	this->e = e;
	this->targets = NULL;
};
JUMP::JUMP(Exp *e, LabelList *targets){
	this->e = e;
	this->targets = targets;
};
void JUMP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList *JUMP::kids() {
    return new ExpList(this->e, NULL);     
}
Stm *JUMP::build(ExpList *kids){
    return new JUMP(kids->prim, this->targets);
};
JUMP::~JUMP(){};


//CJUMP
CJUMP::CJUMP(int relOp, Exp *left, Exp *right, Label *ifTrue, Label *ifFalse){
	this->relOp = relOp;
	this->left = left;
	this->right = right;
	this->ifTrue = ifTrue;
	this->ifFalse = ifFalse;
};
void CJUMP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList * CJUMP::kids(){
    return new ExpList(this->left , new ExpList(this->right,NULL));
};

Stm * CJUMP::build(ExpList *kids){
    return new CJUMP(this->relOp , kids->prim, kids->prox->prim, this->ifTrue, this->ifFalse);
};
CJUMP::~CJUMP(){};


//SEQ
SEQ::SEQ(Stm *left, Stm *right){
	this->left = left;
	this->right = right;
};
void SEQ::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList *SEQ::kids(){
        return NULL;        
};

Stm * SEQ::build(ExpList *kids){
        return NULL;        
};
SEQ::~SEQ(){};

//LABEL
LABEL::LABEL(Label *l){
	this->l = l;
};
void LABEL::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
ExpList *LABEL::kids(){
      return NULL;        
};
Stm *LABEL::build(ExpList *kids){
      return new LABEL(this->l);    
};
LABEL::~LABEL(){};
