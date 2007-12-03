#ifndef _codigo_Intermediario_h
#define _codigo_Intermediario_h

#include "ClassesArvoreIntermediaria.h"
#include "ArvoreIntermediaria.h"
#include "VisitorArvoreIntermediaria.h"
#include "tokens.h"

class Fragmento{
	public:
		virtual	void accept(VisitorArvoreIntermediaria *v) = 0;
};

class ListaDeFragmentos{
	public:
		Fragmento * atual;
		ListaDeFragmentos * prox;
	public:
		ListaDeFragmentos(Fragmento * atual, ListaDeFragmentos * prox);
		void accept(VisitorArvoreIntermediaria *v);		
		~ListaDeFragmentos();
};


class Procedimento: public Fragmento{
	public:
		Frame *frame;
		StmList *corpo;
	public:
		Procedimento(Frame *frame, StmList *corpo);
		void accept(VisitorArvoreIntermediaria *v);		
		~Procedimento();
};


class constanteLiteral: public Fragmento{
	public:
		int indice; //indice no array de lexemas	
	public:
		constanteLiteral(int i);
		void accept(VisitorArvoreIntermediaria *v);		
		~constanteLiteral();
};


class nomeReal: public Fragmento{
	public:
		Label *l;
		float r;
	public:		
		nomeReal(Label *l, float r);
		void accept(VisitorArvoreIntermediaria *v);		
		~nomeReal();
};


class nomeInteiro: public Fragmento{
	public:
		Label *l;
		int i;
	public:		
		nomeInteiro(Label *l, int i);
		void accept(VisitorArvoreIntermediaria *v);		
		~nomeInteiro();
};


class Temp {
	public:
		char * s;
	public:
		Temp(char * s);
		Temp();
		void accept(VisitorArvoreIntermediaria *v);
		~Temp();
};
	
class TempList {
	public:
		Temp *t;
		TempList *tl;
	
	public:
		TempList(Temp *t, TempList *tl);
		void accept(VisitorArvoreIntermediaria *v);		
		~TempList();
};
	
class Label {
	public:
		char * s;
	public:
		Label(char * s);
		Label();
		void accept(VisitorArvoreIntermediaria *v);		
		~Label();
};

class LabelList {
	public:
		Label *l;
		LabelList *ll;
	
	public:
		LabelList(Label *l, LabelList *tl);
		void accept(VisitorArvoreIntermediaria *v);		
		~LabelList();
};


class ListaAcesso{
	public:
		inFrame *l;
		ListaAcesso *prox;
	public:
		ListaAcesso(inFrame *l, ListaAcesso *prox);
		void accept(VisitorArvoreIntermediaria *v);		
		~ListaAcesso();
};




class acessoLocal{
	public:
    	virtual void accept(VisitorArvoreIntermediaria *v) = 0;
};

class inFrame: public acessoLocal{
	public:
		int offset;
	public:
		inFrame(int offset);
		Stm *codigoAcesso(Temp *FP);
		void accept(VisitorArvoreIntermediaria *v);		
		~inFrame();
};		



class inReg: public acessoLocal{
	public:
		Temp temp;
	public:
		inReg(Temp temp);
		Stm *codigoAcesso(Temp *FP);
		void accept(VisitorArvoreIntermediaria *v);		
		~inReg();
};		


class Frame{ 
	public:
		virtual void adicionaParam(int escapa, int tambytes) = 0;
		virtual void adicionaLocal(int escapa, int tambytes) = 0;		
		virtual	void accept(VisitorArvoreIntermediaria *v) = 0;
};

class FrameMips: public Frame{
	public:
		Label *rotulo;
		ListaAcesso *dadosLocais;
	public:
        FrameMips(Label *rotulo, ListaAcesso *dadosLocais);
		void adicionaParam(int escapa, int tambytes);
		void adicionaLocal(int escapa, int tambytes);	
		void accept(VisitorArvoreIntermediaria *v);		
		~FrameMips();	
};		



#endif
