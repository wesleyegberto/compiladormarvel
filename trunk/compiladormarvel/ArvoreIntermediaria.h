#ifndef _arvore_Intermediaria_h
#define _arvore_Intermediaria_h

#include "ClassesArvoreIntermediaria.h"
#include "CodigoIntermediario.h"
#include "VisitorArvoreIntermediaria.h"

//Expressoes
class Exp{
	public:
		virtual void accept(VisitorArvoreIntermediaria *v) = 0;
		virtual ExpList *kids() = 0;
        virtual Exp *build(ExpList *kids) = 0;
};

class ExpList {
	public:
		Exp *prim;
		ExpList *prox;
	public:
		ExpList(Exp *prim, ExpList *prox);
		void accept(VisitorArvoreIntermediaria *v);		
		~ExpList();
};

//Sentencas
class Stm{
	public:
        virtual void accept(VisitorArvoreIntermediaria *v) = 0;			
        virtual ExpList *kids() = 0;
        virtual Stm *build(ExpList kids) = 0;
};

class StmList {
	public:
		Stm *prim;
		StmList *prox;
	public:
		StmList(Stm *prim, StmList *prox);
		void accept(VisitorArvoreIntermediaria *v);
		~StmList();
};



//Extends Exp
class CONST: public Exp{
	public:
		int value;
	public:
		CONST(int value);
		void accept(VisitorArvoreIntermediaria *v);
		~CONST();
};
	
class CONSTF: public Exp{
	public:
		float value;
	public:
		CONSTF(float value);
		void accept(VisitorArvoreIntermediaria *v);
		~CONSTF();
};

class NAME: public Exp{
	public:
		Label *l;
	public:
		NAME(Label *l);
		void accept(VisitorArvoreIntermediaria *v);
		~NAME();
};

class TEMP: public Exp{
	public:
		Temp *t;
	public:
		TEMP(Temp *t);
		void accept(VisitorArvoreIntermediaria *v);
		~TEMP();
};

class BINOP: public Exp{
	public:
		int binOP;
		Exp *left;
		Exp *right;
	public:
		BINOP(int binOP, Exp *left, Exp *right);
		void accept(VisitorArvoreIntermediaria *v);
		~BINOP();
};

class MEM: public Exp{
	public:
		Exp *e;
	public:
		MEM(Exp *e);
		void accept(VisitorArvoreIntermediaria *v);
		~MEM();
};

class CALL: public Exp{
	public:
		Exp *func;
		ExpList *args;
	public:
		CALL(Exp *func, ExpList *args);
		void accept(VisitorArvoreIntermediaria *v);
		~CALL();
};

class ESEQ: public Exp{
	public:
		Stm *s;
		Exp *e;
	public:
		ESEQ(Stm *s, Exp *e);
		void accept(VisitorArvoreIntermediaria *v);
		~ESEQ();
};	


//extends Stm	

class MOVE: public Stm{
	public:
		Exp *dst;
		Exp *src;
	public:
		MOVE(Exp *dst, Exp *src);
		void accept(VisitorArvoreIntermediaria *v);
		~MOVE();
};

class EXP: public Stm{
	public:
		Exp *e;
	public:
		EXP(Exp *e);
		void accept(VisitorArvoreIntermediaria *v);
		~EXP();
};

class JUMP: public Stm{
	public:
		Exp *e;
		LabelList *targets;
	public:
		JUMP(Exp *e);
		JUMP(Exp *e, LabelList *targets);
		void accept(VisitorArvoreIntermediaria *v);
		~JUMP();
};

class CJUMP: public Stm{
	public:
		int relOp;
		Exp *left;
		Exp *right;
		Label *ifTrue;
		Label *ifFalse;
		
	public:
		CJUMP(int relOp, Exp *left, Exp *right, Label *ifTrue, Label *ifFalse);
		void accept(VisitorArvoreIntermediaria *v);
		~CJUMP();
};

class SEQ: public Stm{
	public:
		Stm *left;
		Stm *right;
	public:
		SEQ(Stm *left, Stm *right);
		void accept(VisitorArvoreIntermediaria *v);
		~SEQ();
};

class LABEL: public Stm{
	public:
		Label *l;
	public:
		LABEL(Label *l);
		void accept(VisitorArvoreIntermediaria *v);
		~LABEL();
};			
#endif
