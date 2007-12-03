#include "VerificadorEscopo.h"
#include "Tokens.h"

/* ----------------------------------------------------------------------------

-----------------------------------------------------------------------------*/

// Nivel de escopo atual
int nivelEscopo;

//Sinalizadores
int estaDeclarando;
int temParametro;

//Offset
int offset = 4;

//Define o "pai" do escopo Atual
IdNode *paiAtual;
 
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
     IdNode *resultado = NULL;
     for (int nivel = nivelEscopo; nivel >=0; nivel--){
             resultado = buscaNoEscopo(nivel,idNode);
          if( resultado != NULL){
             *idNode = *resultado;
             // chave->escopo = resultado->escopo;
             //idNode->paiEscopo = resultado->paiEscopo;
//             idNode->escopo = resultado->escopo;
//             idNode->tipo = resultado->tipo;
             return;
          }
     }
          
     //EMITE ERRO!!!
     emiteErroSemantico(ERRO_VARIAVEL_NAO_DECLARADA,
                        retornaCharToken(idNode->registro->indiceLexema),
                        idNode->linha);
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
        // Recupera o tipo do ID
        tipo = nameDeclNode->modifierListNode->modifierNode->modifier;                           
     }
     
     
     //Verifica se é a declaração de um Fragmento
     if (estaDeclarando){ 
             nameDeclNode->idListNode->idNode->tipo = FRAGMENT; 
             insereEscopo(nameDeclNode->idListNode->idNode, tipo);
             nameDeclNode->idListNode->idNode->offset = offset;
             offset = 0;
             paiAtual = nameDeclNode->idListNode->idNode;
             estaDeclarando = 0;
             temParametro = 1;     
             iniciaEscopo();
     //Verifica se a é declaração do parametro de um fragmento
     }else if ((temParametro) && (tipo == PARAM)){
             tipo = nameDeclNode->modifierListNode->modifierListNode->modifierNode->modifier;
             nameDeclNode->idListNode->idNode->tipo = tipo;                     
             nameDeclNode->idListNode->idNode->paiEscopo = paiAtual;
             insereEscopo(nameDeclNode->idListNode->idNode, tipo);
     //Escopo interno                  
     }else{
           temParametro = 0;
           if ((nameDeclNode->idListNode) != NULL){
                 nameDeclNode->idListNode->idNode->tipo = tipo;  
                 nameDeclNode->idListNode->idNode->offset = offset;
                 offset += 4;
                 nameDeclNode->idListNode->idNode->paiEscopo = paiAtual;
                 insereEscopo(nameDeclNode->idListNode->idNode, tipo);
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
    multimap<int, IdNode*>::iterator itr = niveis.find(nivelEscopo);
    pair<int, IdNode*> p;
    int final =  niveis.count(nivelEscopo);
    for (int i = 0; i < final; i++){
        p = *itr;
        p.second->ativo = 0;
       itr++;
    } 
     nivelEscopo--;
     //Varre a tabela de simbolos e coloca o escopo inativo
}

IdNode *VerificadorEscopo::buscaNoEscopo(int nivel, IdNode *valor){
    pair< multimap<int, IdNode*>::iterator, multimap<int, IdNode*>::iterator> range = niveis.equal_range(nivel); 
    multimap<int, IdNode*>::iterator itr;
    
    for (itr = range.first; itr != range.second; itr++)          
     if (( itr->second->registro->indiceLexema == valor->registro->indiceLexema) && (itr->second->ativo == 1)) return itr->second;
    
    return NULL;
}

void VerificadorEscopo::insereEscopo(IdNode *idNode, int tipo){     
     if (buscaNoEscopo(nivelEscopo,idNode)==NULL){
            idNode->escopo = nivelEscopo;
            idNode->tipo   = tipo;
            niveis.insert(pair<const int, IdNode*>(nivelEscopo,idNode));
     }else{
           //EMITE ERRO!!!!
           emiteErroSemantico(ERRO_VARIAVEL_JA_DECLARADA, 
                              retornaCharToken(idNode->registro->indiceLexema),
                              idNode->linha);
     }
     //busca na tabela de simbolos se já existe escopo senão insere
}
