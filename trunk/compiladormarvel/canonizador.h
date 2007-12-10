//#include "ArvoreIntermediaria.h"
//
//#ifndef _canonizador_h
//#define _canonizador_h
//
//class BasicBlocks {
//    public:
//        StmListList *blocos;
//        Label       *rotulo;
//        StmList     *stmList;
//    public:
//        BasicBlocks(StmList *sl);
//        void addStm(Stm *s);
//        void doStms(StmList *sl);
//        void makeBlocks(StmList *sl);
//};
//
//class StmListList{
//    public:
//        StmList        *atual;
//        StmListList    *prox;
//    public:
//        StmListList(StmList *a, StmListList *p);
//};
//
//class StmExpList {
//	public:	
//	    Stm        *stm;
//	    ExpList    *expList;
//    public:
//  	    StmExpList(Stm *s, ExpList *e); 
//  	    ~StmExpList();
//};
//
//class ExpCall:public Stm {
//    public:
//	    CALL *call;
//    public:
//        ExpCall(CALL *c);
//	    ExpList *kids(); 
//	    Stm *build(ExpList *kids);
//	    void accept(VisitorArvoreIntermediaria *v);
//	    ~ExpCall(); 
//};
//
//bool comute(Stm *s, Exp *e);
//bool isNop(Stm *s);
//
//#endif
