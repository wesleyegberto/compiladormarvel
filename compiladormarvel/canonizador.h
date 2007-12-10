#include "ArvoreIntermediaria.h"

#ifndef _canonizador_h
#define _canonizador_h

class MoveCall: public Stm{
    public:
		TEMP *origem;
  		CALL *destino;
	public:
		MoveCall(TEMP *o, CALL *d);
  		ExpList *kids();
  		Stm *build(ExpList *kids);
		void accept(VisitorArvoreIntermediaria *v);
		~MoveCall();
};

class StmExpList {
	public:	
	  Stm        *stm;
	  ExpList    *expList;
    public:
  	  StmExpList(Stm *s, ExpList *e); 
  	  ~StmExpList();
};

class ExpCall:public Stm {
   public:
	CALL *call;
   public:
	ExpCall(CALL *c);
	ExpList *kids(); 
	Stm *build(ExpList *kids);
	void accept(VisitorArvoreIntermediaria *v);
	~ExpCall(); 
};

class ListaStmList{
   public:
    StmList        *atual;
    ListaStmList   *prox;
   public:
    ListaStmList(StmList *a, ListaStmList *p);
};


#endif
