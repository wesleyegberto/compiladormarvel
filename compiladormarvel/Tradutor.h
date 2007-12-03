
#ifndef _Tradutor_h
#define _Tradutor_h

#include "Visitor.h"
#include "ArvoreIntermediaria.h"
#include "CodigoIntermediario.h"

	typedef struct rPilhaFragmentos {
			StmList * corpo; //ponteiro para o parametro
			ListaAcesso * dados;
			struct rPilhaFragmentos *proximo;
		}
		TPilhaFragmentos;
		
// Define os atributos e métodos visitantes.
class Tradutor : public Visitor {
      	public:
		ListaDeFragmentos * listaFragmentos;
		ListaAcesso * dados; //dados do procedimento analisado
		StmList * corpo; //corpo do procedimento analisado 
		Exp * expTemp;
		Stm * stmTemp;
		int tamanhoPalavra;
		
		TPilhaFragmentos pilhaFrag;
		TPilhaFragmentos * topoFrag;
		
		
		/*
		int adicionaAssing: no caso de staments que chamam outros statements ( if ... while) o assign estava 
		sendo adicionado repetidadaemnte ao corpo do fragmento (BENZE). Agora so sera adicionado se o valor
		desse atributo for 1 (VERDADEIRO)
		*/
		int adicionaStm; 
		int adicionaBloco; //similar a adicionaStm
		
		int numBloco;

      public:
             // Declaração do construtor
             Tradutor();
             
             // Métodos visitantes
              void visit(ProgramNode* programNode);
              void visit(StatementListNode* stmtNode);
              void visit(NameDeclNode* nameDeclNode);
              void visit(FragmentNode* fragmentNode);
              void visit(IfNode* ifNode);
              void visit(WhileNode* whileNode);
              void visit(AssignNode* assignNode);
              void visit(FragCallNode* fragCallNode);
              void visit(ReadNode* readNode);
              void visit(WriteNode* writeNode);
              void visit(ConstantNode* constantNode);
              void visit(ExpressionListNode* expressionListNode);
              void visit(CallNode* callNode);
              void visit(ArrayNode* arrayNode);
              void visit(RelOpNode* relationalOpNode);
              void visit(AddOpNode* additionalOpNode);
              void visit(MultOpNode* multOpNode);
              void visit(BoolOpNode* boolOpNode);
              void visit(BitwiseOpNode* bitwiseOpNode);
              void visit(NotNode* notNode);
              void visit(NegativeNode* negativeNode);
              void visit(ModifierListNode* modifierListNode);
              void visit(ModifierNode* modifierNode);
              void visit(IdNode* idNode);
              void visit(IdListNode* idListNode);
              void visit(NumberNode* numberNode);
              void visit(LiteralNode* literalNode);
             
              // Método responsável pela impressão do nível da árvore
    		   ListaDeFragmentos * getListaFragmentos();
	          void empilhaFrag(StmList *corpo, ListaAcesso *dados);
		      void desempilhaFrag();
		      TPilhaFragmentos * getTopoFrag();
		      void adicionaFragmento(Fragmento * frag);
		      void adicionaSentenca(Stm * sentenca);
		      void salvaFrag();
		      void restauraFrag();
		      Stm * seqBloco(FragmentNode *o); 
		      Stm * seqMoves(WriteNode *o); 		
		      Stm * seqMoves(ReadNode *o); 
		      Exp * acessoNaoLocal(int n);	
		      Exp * seqMem(int n);
                                       
};
#endif
