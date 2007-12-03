#ifndef _Visitor_arvore_Intermediaria_h
#define _Visitor_arvore_Intermediaria_h
#include "ClassesArvoreIntermediaria.h"


class VisitorArvoreIntermediaria{
    public:
       int nivel, cont;  
	public:
		VisitorArvoreIntermediaria();
        void visit(ExpList *o);
        void visit(StmList *o);
        void visit(CONST *o);
        void visit(CONSTF *o);
        void visit(NAME *o);
        void visit(TEMP *o);
        void visit(BINOP *o);
        void visit(MEM *o);
        void visit(CALL *o);
        void visit(ESEQ *o);
        void visit(MOVE *o);
        void visit(EXP *o);
        void visit(JUMP *o);
        void visit(CJUMP *o);
        void visit(SEQ *o);
        void visit(LABEL *o);
        void visit(Temp *o);
        void visit(TempList *o);
        void visit(Label *o);
        void visit(LabelList *o);
        void visit(inFrame *o);
        void visit(inReg *o);
        void visit(ListaAcesso *o);
        void visit(FrameMips *o);		
        void visit(ListaDeFragmentos *o);
        void visit(Procedimento *o);
        void visit(constanteLiteral *o);
        void visit(nomeReal *o);
        void visit(nomeInteiro *o);      
        void ImprimeEspacos();
};
#endif
