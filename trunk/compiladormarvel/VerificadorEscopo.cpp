#include "VerificadorEscopo.h"
#include "Tokens.h"

/* ----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/

// Nivel de escopo atual
int nivelEscopo;

//Sinalizadores
int estaDeclarando;
int temParametro;

//Define o "pai" do escopo Atual
REGISTRO *paiAtual;
 
// Retorna a linha atual
int retornaLinha();

// Implementa o construtor da classe de Verificação de Escopo
VerificadorEscopo::VerificadorEscopo(){
    nivelEscopo = -1;
    estaDeclarando = 0;
    temParametro = 0; 
    paiAtual = NULL;
}
/*---------------------------------------------------------------------------*/
// Implementa os métodos visitantes, que devem verificar os escopos
/*---------------------------------------------------------------------------*/

void VerificadorEscopo::visit(AddOpNode* additionalOpNode){
     (additionalOpNode->expressionNode1)->accept(this);
     (additionalOpNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(ArrayNode* arrayNode){
     if (arrayNode->idNode) (arrayNode->idNode)->accept(this);
     if (arrayNode->expressionNode) (arrayNode->expressionNode)->accept(this);
}

void VerificadorEscopo::visit(AssignNode* assignNode){
    
     if (assignNode->idNode) (assignNode->idNode)->accept(this);
     if (assignNode->arrayNode) (assignNode->arrayNode)->accept(this);
     if (assignNode->expressionNode1) (assignNode->expressionNode1)->accept(this);
     if (assignNode->expressionNode2) (assignNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(BitwiseOpNode* bitwiseOpNode){
    (bitwiseOpNode->expressionNode1)->accept(this);
    (bitwiseOpNode->expressionNode2)->accept(this);
    
}

void VerificadorEscopo::visit(BoolOpNode* boolOpNode){
    (boolOpNode->expressionNode1)->accept(this);
    (boolOpNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(CallNode* callNode){
    (callNode->idNode)->accept(this);
    (callNode->expressionListNode)->accept(this);
}


void VerificadorEscopo::visit(ConstantNode* constantNode){
    estaDeclarando = 1;
    (constantNode->nameNode)->accept(this);
    (constantNode->value)->accept(this);
    terminaEscopo();
}

void VerificadorEscopo::visit(ExpressionListNode* expressionListNode){
    if ((expressionListNode->expressionNode) != NULL )(expressionListNode->expressionNode)->accept(this);
    if ((expressionListNode->expressionListNode) != NULL )(expressionListNode->expressionListNode)->accept(this);  
}

void VerificadorEscopo::visit(FragCallNode* fragCallNode){
    (fragCallNode->idNode)->accept(this);
    (fragCallNode->expressionList)->accept(this);

}

void VerificadorEscopo::visit(FragmentNode* fragmentNode){
     
     //Primeiro nó do Fragment
     StatementNode *primeiro = (fragmentNode->statementListNode)->statementNode;
    
    //Verifica se o Fragmento é nomeado
    if ( typeid(* primeiro).name() == typeid(NameDeclNode).name() )
       estaDeclarando = 1;
    //else iniciaEscopo();
       
    
    StatementNode *segundo = fragmentNode->statementListNode->statementListNode->statementNode;
    
    //Verifica se o Fragmento tem parametros,
    if ( typeid(* segundo).name() == typeid(NameDeclNode).name() ){
       NameDeclNode *parametro = dynamic_cast<NameDeclNode *>(segundo);  
       if (parametro->modifierListNode->modifierNode->modifier == PARAM) temParametro = 1;
    }
    
    (fragmentNode->statementListNode)->accept(this);
    
    terminaEscopo();
}

void VerificadorEscopo::visit(IdListNode* idListNode){
     if ((idListNode->idListNode) == NULL){ 
         (idListNode->idNode)->accept(this);
     }else{
         (idListNode->idNode)->accept(this);
         (idListNode->idListNode)->accept(this);
     }
}

void VerificadorEscopo::visit(IdNode* idNode){   
     REGISTRO *chave = idNode->registro;
     REGISTRO *resultado = NULL;
     for (int nivel = nivelEscopo; nivel >=0; nivel--){
             resultado = buscaNoEscopo(nivel,chave);
          if( resultado != NULL){
             // chave->escopo = resultado->escopo;
             chave->param = resultado->param;
             return;
          }
     }
          
     //EMITE ERRO!!!
     emiteErroSemantico(ERRO_VARIAVEL_NAO_DECLARADA,
                        retornaCharToken(idNode->registro->indiceLexema),
                        idNode->registro->linha);
}

void VerificadorEscopo::visit(IfNode* ifNode){
    (ifNode->expressionNode)->accept(this);
    (ifNode->statementNode1)->accept(this);
    (ifNode->statementNode2)->accept(this);
}

void VerificadorEscopo::visit(LiteralNode* literalNode){}

void VerificadorEscopo::visit(ModifierListNode* modifierListNode){
    if (modifierListNode->modifierNode)(modifierListNode->modifierNode)->accept(this);        
    if (modifierListNode->modifierListNode)(modifierListNode->modifierListNode)->accept(this);    
}

void VerificadorEscopo::visit(ModifierNode* modifierNode){}   

void VerificadorEscopo::visit(MultOpNode* multOpNode){
    (multOpNode->expressionNode1)->accept(this);
    (multOpNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(NameDeclNode* nameDeclNode){
     int tipo = 0;
     
     if ((nameDeclNode->modifierListNode) != NULL) {
                  tipo = nameDeclNode->modifierListNode->modifierNode->modifier;                           
     }
     
     
     //Verifica se é a declaração de um Fragmento
     if (estaDeclarando){ 
             nameDeclNode->idListNode->idNode->registro->tipo = FRAGMENT;                     
             insereEscopo(nameDeclNode->idListNode->idNode->registro);
             paiAtual = nameDeclNode->idListNode->idNode->registro;
             estaDeclarando = 0;
             temParametro = 1;     
             iniciaEscopo();
     //Verifica se a é declaração do parametro de um fragmento
     }else if ((temParametro) && (tipo == PARAM)){
             tipo = nameDeclNode->modifierListNode->modifierListNode->modifierNode->modifier;
             nameDeclNode->idListNode->idNode->registro->tipo = tipo;                     
             nameDeclNode->idListNode->idNode->registro->param = paiAtual;
             insereEscopo(nameDeclNode->idListNode->idNode->registro);
     //Escopo interno                  
     }else{
           temParametro = 0;
           if ((nameDeclNode->idListNode) != NULL){
                 nameDeclNode->idListNode->idNode->registro->tipo = tipo;   
                 nameDeclNode->idListNode->idNode->registro->param = paiAtual;
                 insereEscopo(nameDeclNode->idListNode->idNode->registro);
           }
     }    
}

void VerificadorEscopo::visit(NegativeNode* negativeNode){
    (negativeNode->expressionNode)->accept(this);
}

void VerificadorEscopo::visit(NotNode* notNode){
    (notNode->expressionNode)->accept(this);
}

void VerificadorEscopo::visit(NumberNode* numberNode){}

void VerificadorEscopo::visit(ProgramNode* programNode){
    iniciaEscopo();
    (programNode->stmtListNode)->accept(this);
    terminaEscopo();
}

void VerificadorEscopo::visit(ReadNode* readNode){
     if (readNode->idNode) (readNode->idNode)->accept(this);
     if (readNode->arrayNode) (readNode->arrayNode)->accept(this);
}

void VerificadorEscopo::visit(RelOpNode* relOpNode){
     (relOpNode->expressionNode1)->accept(this);
     (relOpNode->expressionNode2)->accept(this);
}

void VerificadorEscopo::visit(StatementListNode* stmtListNode){
     if ((stmtListNode->statementNode) != NULL) (stmtListNode->statementNode)->accept(this);
     if ((stmtListNode->statementListNode) != NULL) (stmtListNode->statementListNode)->accept(this);
}

void VerificadorEscopo::visit(WhileNode* whileNode){
    (whileNode->expressionNode)->accept(this);
    (whileNode->statementNode)->accept(this);
}

void VerificadorEscopo::visit(WriteNode* writeNode){
    (writeNode->expressionListNode)->accept(this);
}


void VerificadorEscopo::iniciaEscopo(){
     nivelEscopo++;
}


void VerificadorEscopo::terminaEscopo(){
    multimap<int, REGISTRO*>::iterator itr = niveis.find(nivelEscopo);
    pair<int, REGISTRO*> p;
    int final =  niveis.count(nivelEscopo);
    for (int i = 0; i < final; i++){
        p = *itr;
        p.second->ativo = 0;
       itr++;
    } 
     nivelEscopo--;
     //Varre a tabela de simbolos e coloca o escopo inativo
}

REGISTRO *VerificadorEscopo::buscaNoEscopo(int nivel, REGISTRO *valor){
    multimap<int, REGISTRO*>::iterator itr = niveis.find(nivel);
    pair<int, REGISTRO*> p;
    int final =  niveis.count(nivel);
    for (int i = 0; i < final; i++){
        p = *itr;
        if ((p.second->indiceLexema == valor->indiceLexema) && (p.second->ativo == 1)) return p.second;
       itr++;
    } 
    return NULL;
}
void VerificadorEscopo::insereEscopo(REGISTRO *entrada){
     if (buscaNoEscopo(nivelEscopo,entrada)==0){
            niveis.insert(pair<const int, REGISTRO*>(nivelEscopo,entrada));
            entrada->escopo = nivelEscopo;
     }else{
           //EMITE ERRO!!!!
           emiteErroSemantico(ERRO_VARIAVEL_JA_DECLARADA, retornaCharToken(entrada->indiceLexema), entrada->linha);
     }
     //busca na tabela de simbolos se já existe escopo senão insere
}
