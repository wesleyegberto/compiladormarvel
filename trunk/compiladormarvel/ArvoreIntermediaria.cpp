#include <stdlib.h>
#include <stdio.h>
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


//CONST
CONST::CONST(int value){
	this->value = value;
};
void CONST::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
CONST::~CONST(){};

//CONSTF
CONSTF::CONSTF(float value){
	this->value = value;
};
CONSTF::~CONSTF(){};
void CONSTF::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//NAME
NAME::NAME(Label *l){
	this->l = l;
};
NAME::~NAME(){};
void NAME::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//TEMP
TEMP::TEMP(Temp *t){
	this->t = t;
};
TEMP::~TEMP(){};
void TEMP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//BINOP
BINOP::BINOP(int binOP, Exp *left, Exp *right){
	this->binOP = binOP;
	this->left = left;
	this->right = right;
};
BINOP::~BINOP(){};
void BINOP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//MEM
MEM::MEM(Exp *e){
	this->e = e;
}
MEM::~MEM(){};
void MEM::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//CALL
CALL::CALL(Exp *func, ExpList *args){
	this->func = func;
	this->args = args;
};
CALL::~CALL(){};
void CALL::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//ESEQ
ESEQ::ESEQ(Stm *s, Exp *e){
	this->s = s;
	this->e = e;
};
ESEQ::~ESEQ(){};
void ESEQ::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//MOVE
MOVE::MOVE(Exp *dst, Exp *src){
	this->dst = dst;
	this->src = src;
};
MOVE::~MOVE(){};
void MOVE::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//EXP
EXP::EXP(Exp *e){
	this->e = e;
};
EXP::~EXP(){};
void EXP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//JUMP
JUMP::JUMP(Exp *e){
	this->e = e;
	this->targets = NULL;
};
JUMP::JUMP(Exp *e, LabelList *targets){
	this->e = e;
	this->targets = targets;
};
JUMP::~JUMP(){};
void JUMP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//CJUMP
CJUMP::CJUMP(int relOp, Exp *left, Exp *right, Label *ifTrue, Label *ifFalse){
	this->relOp = relOp;
	this->left = left;
	this->right = right;
	this->ifTrue = ifTrue;
	this->ifFalse = ifFalse;
};
CJUMP::~CJUMP(){};
void CJUMP::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//SEQ
SEQ::SEQ(Stm *left, Stm *right){
	this->left = left;
	this->right = right;
};
SEQ::~SEQ(){};
void SEQ::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};

//LABEL
LABEL::LABEL(Label *l){
	this->l = l;
};
LABEL::~LABEL(){};
void LABEL::accept(VisitorArvoreIntermediaria *v){
	v->visit(this);
};
