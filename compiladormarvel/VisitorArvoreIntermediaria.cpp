

#include <stdio.h>
#include "VisitorArvoreIntermediaria.h"
#include "ArvoreIntermediaria.h"
#include "Tokens.h"


VisitorArvoreIntermediaria::VisitorArvoreIntermediaria(){
	nivel = 0;
	cont = 0;
    printf("\n         ษอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป\n");
    printf("         บ                  ARVORE DE CODIGO INTEMEDIARIO                บ\n");
    printf("         ศอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ\n");
     
};

int eLABEL = 0;
void VisitorArvoreIntermediaria::visit(ExpList *o){
	o->prim->accept(this);
	if ( o->prox != NULL){
		o->prox->accept(this);
	}
};
void VisitorArvoreIntermediaria::visit(StmList *o){
	o->prim->accept(this);
	if ( o->prox != NULL){
		o->prox->accept(this);
	}
};
void VisitorArvoreIntermediaria::visit(CONST *o){
	nivel++;
	ImprimeEspacos();	
	printf("CONST.%i\n",o->value);
	nivel--;
};
void VisitorArvoreIntermediaria::visit(CONSTF *o){
	nivel++;
	ImprimeEspacos();	
	printf("CONSTF.%f\n",o->value);
	nivel--;
};
void VisitorArvoreIntermediaria::visit(NAME *o){
	nivel++;
	ImprimeEspacos();	
	printf("NAME.");	
    o->l->accept(this);
	nivel--;
};
void VisitorArvoreIntermediaria::visit(TEMP *o){
	nivel++;
	ImprimeEspacos();	
    printf("TEMP.");
	o->t->accept(this);	    	
	nivel--;
};
void VisitorArvoreIntermediaria::visit(BINOP *o){
	nivel++;
	ImprimeEspacos();
     switch(o->binOP){
        case MULT:printf("BINOP.MULT\n");
              break;              
        case DIV:printf("BINOP.DIV\n");
          break;              
        case MOD:printf("BINOP.MOD\n");
          break;              
        case PLUS:printf("BINOP.PLUS\n");
          break;              
        case MINUS:printf("BINOP.MINUS\n");
          break;              
        default: printf("BINOP\n");        
     }


	o->left->accept(this);
	o->right->accept(this);
	nivel--;
};
void VisitorArvoreIntermediaria::visit(MEM *o){
	nivel++;
	ImprimeEspacos();	
	printf("MEM.\n");
	if(o->e !=NULL) o->e->accept(this);	
	nivel--;
};
void VisitorArvoreIntermediaria::visit(CALL *o){
	nivel++;
	ImprimeEspacos();	
	printf("CALL \n");
	o->func->accept(this);
	if ( o->args != NULL ){
		o->args->accept(this);
	}
	nivel--;
};
void VisitorArvoreIntermediaria::visit(ESEQ *o){
	nivel++;
	ImprimeEspacos();	
	printf("ESEQ \n");
	o->s->accept(this);
	o->e->accept(this);	
	nivel--;
};
void VisitorArvoreIntermediaria::visit(MOVE *o){
	nivel++;
	ImprimeEspacos();	
	printf("MOVE \n");
	o->dst->accept(this);
	o->src->accept(this);	
	nivel--;	
};
void VisitorArvoreIntermediaria::visit(EXP *o){
	nivel++;
	ImprimeEspacos();	
	printf("EXP \n");
	o->e->accept(this);	
	nivel--;
};
void VisitorArvoreIntermediaria::visit(JUMP *o){
	nivel++;
	ImprimeEspacos();	
	printf("JUMP \n");
	o->e->accept(this);
	if (o->targets != NULL){
		o->targets->accept(this);
	}
	nivel--;
};
void VisitorArvoreIntermediaria::visit(CJUMP *o){
	nivel++;
	ImprimeEspacos();	
	     switch(o->relOp){
        case EQUALS:printf("CJUMP.EQUALS\n");
              break;              
        case LT:printf("CJUMP.LT\n");
          break;              
        case LE:printf("CJUMP.LE\n");
          break;              
        case GE:printf("CJUMP.GE\n");
          break;              
        case GT:printf("CJUMP.GT\n");
          break;   
        case NE:printf("CJUMP.NE\n");
          break;            
        default: printf("CJUMP\n");        
     }

	o->left->accept(this);
	o->right->accept(this);
//	o->ifTrue->accept(this);
//	o->ifFalse->accept(this);		
	nivel--;
};
void VisitorArvoreIntermediaria::visit(SEQ *o){
	nivel++;
	ImprimeEspacos();	
	printf("SEQ.\n");
	if (o->left == NULL){
		printf("Left.NULL\n");
	}
	o->left->accept(this);
	if (o->right != NULL){
		o->right->accept(this);			
	}	
	nivel--;
};
void VisitorArvoreIntermediaria::visit(LABEL *o){
	nivel++;
	ImprimeEspacos();
	printf("LABEL.");
	eLABEL = 1;
	o->l->accept(this);	
	eLABEL = 0;
	nivel--;
};




void VisitorArvoreIntermediaria::visit(Temp *o){
	printf("%s\n",o->s);
};
void VisitorArvoreIntermediaria::visit(TempList *o){
	o->t->accept(this);
	if (o->tl != NULL){
		o->tl->accept(this);
	}	
};
void VisitorArvoreIntermediaria::visit(Label *o){		
//    ImprimeEspacos();
    printf("%s\n",o->s);
};
void VisitorArvoreIntermediaria::visit(LabelList *o){
	o->l->accept(this);
	if (o->ll != NULL){
		o->ll->accept(this);
	}
};
void VisitorArvoreIntermediaria::visit(inFrame *o){
	nivel++;
	ImprimeEspacos();		
	printf("InFrame offset: %i\n",o->offset);
	nivel--;
};
void VisitorArvoreIntermediaria::visit(inReg *o){
};
void VisitorArvoreIntermediaria::visit(ListaAcesso *o){
	o->l->accept(this);
	if (o->prox != NULL){
		o->prox->accept(this);
	}	
};
void VisitorArvoreIntermediaria::visit(FrameMips *o){
	printf("\n   ออออออออออออออออออออออออออออออออออ FRAME ออออออออออออออออออออออออออออออออออ\n ");
	nivel++;
	ImprimeEspacos();	
	if ( o->rotulo != NULL ){
		printf("Rotulo: ");		
		o->rotulo->accept(this);
		printf("\n");		
	}
	if ( o->dadosLocais != NULL ){
		o->dadosLocais->accept(this);
	}
	nivel--;
};		

void VisitorArvoreIntermediaria::visit(ListaDeFragmentos *o){
	o->atual->accept(this);
	if ( o->prox != NULL ){
		o->prox->accept(this);
	}
};
void VisitorArvoreIntermediaria::visit(Procedimento *o){
	if ( o->frame != NULL){
		o->frame->accept(this);
	}
	if (o->corpo != NULL){
		printf("\n   ออออออออออออออออออออออออออออออออออ CORPO ออออออออออออออออออออออออออออออออออ\n ");		
		o->corpo->accept(this);
	}
};
void VisitorArvoreIntermediaria::visit(constanteLiteral *o){
	nivel++;
	ImprimeEspacos();
	printf("\n   ออออออออออออออออออออออออออออ CONSTANTE LITERAL ออออออออออออออออออออออออออออ\n ");			
	ImprimeEspacos();
    printf("%s\n",o->literal);
	nivel--;	
};
void VisitorArvoreIntermediaria::visit(nomeReal *o){
	nivel++;
	ImprimeEspacos();
	printf("\n   ออออออออออออออออออออออออออออออออออ NOME REAL ออออออออออออออออออออออออออออออออออ\n ");			
	printf("Rotulo: ");	
	o->l->accept(this);		
	printf("\n Valor.%f",o->r);
	nivel--;		
};
void VisitorArvoreIntermediaria::visit(nomeInteiro *o){
	nivel++;
	ImprimeEspacos();
	printf("\n   ออออออออออออออออออออออออออออออออออ NOME INTEIRO ออออออออออออออออออออออออออออออออออ\n ");				
	printf("Rotulo: ");
	o->l->accept(this);	
	printf("\n Valor: %i",o->i);
	nivel--;		
};
void VisitorArvoreIntermediaria::ImprimeEspacos(){
	cont = 0;
	while(cont <= nivel){
        printf("  ");
        cont++;
	}
};
