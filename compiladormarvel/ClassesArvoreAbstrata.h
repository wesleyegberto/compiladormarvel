/*  
    Header que especifica os nós em forma de classe para a Árvore de 
    Sintaxe Abstrata.
    Cada um dos nós possui elementos especificados para sua construção,
    seus construtores e a definição do método accept, que será invocado
    utilizando o padrão visitor.
*/
#include "Visitor.h"

using namespace std;

#ifndef StatementNode_header
#define StatementNode_header

class StatementNode {
     public:
         virtual void accept(Visitor* visit) = 0;      
};
#endif



#ifndef ExpressionNode_header
#define ExpressionNode_header

class ExpressionNode {
     public:
         virtual void accept(Visitor* visit) = 0;      
};
#endif



#ifndef StatementListNode_header
#define StatementListNode_header

class StatementListNode{
    public:
        StatementNode*     statementNode;
        StatementListNode* statementListNode;
    public:
        StatementListNode(StatementNode* sn);
        StatementListNode(StatementNode* sn, StatementListNode* sln);
        void accept(Visitor* visitor); 
        ~StatementListNode();
};

#endif

#ifndef ProgramNode_header
#define ProgramNode_header

class ProgramNode{
    public:
        StatementListNode* stmtListNode;
    public:
        ProgramNode(StatementListNode* sln);
        void accept(Visitor* visitor) ;
        ~ProgramNode();
};

#endif

#ifndef ModifierNode_header
#define ModifierNode_header

class ModifierNode{
    public:
        int  modifier;
        int  num;
    public:
        ModifierNode(int m, int n);
        ModifierNode(int m);
        void accept(Visitor* visitor) ;
};
#endif

#ifndef ModifierListNode_header
#define ModifierListNode_header

class ModifierListNode{
    public:
        ModifierNode*     modifierNode;
        ModifierListNode* modifierListNode;
    public:
        ModifierListNode(ModifierNode* mn);
        ModifierListNode(ModifierNode* mn, ModifierListNode* mln);
        void accept(Visitor* visitor) ;
        ~ModifierListNode();
};
#endif

#ifndef IdNode_header
#define IdNode_header

class IdNode : public ExpressionNode {
    public:
        int     id;
        struct Registro  *registro;
    public:
        IdNode(int i, struct Registro  *reg);
        void accept(Visitor* visitor) ;
};
#endif

#ifndef LiteralNode_header
#define LiteralNode_header

class LiteralNode : public ExpressionNode {
    public:
        int     literal;
    public:
        LiteralNode(int l);
        void accept(Visitor* visitor) ;
};
#endif

#ifndef NumberNodeNode_header
#define NumberNodeNode_header

class NumberNode : public ExpressionNode {
    public:
        int               number;
        struct Registro  *registro;
    public:
        NumberNode(int n, struct Registro *reg);
        void accept(Visitor* visitor) ;
};
#endif

#ifndef IdListNode_header
#define IdListNode_header

class IdListNode{
    public:
        IdNode*     idNode;
        IdListNode* idListNode;
    public:
        IdListNode(IdNode* in);
        IdListNode(IdNode* in, IdListNode* iln);
        void accept(Visitor* visitor);
        ~IdListNode();
};
#endif

#ifndef ExpressionListNode_header
#define ExpressionListNode_header 

class ExpressionListNode{
    public:
        ExpressionNode*       expressionNode;
        ExpressionListNode*   expressionListNode;
        int                   tipoExpressionListNode;
    public:
        ExpressionListNode(ExpressionNode* en, ExpressionListNode* eln);
        ExpressionListNode(ExpressionNode* en);
        void accept(Visitor* visitor) ;
        ~ExpressionListNode();
};
#endif

#ifndef NameDeclNode_header
#define NameDeclNode_header

class NameDeclNode : public StatementNode {
    public:
        ModifierListNode* modifierListNode;
        IdListNode*       idListNode;
    public:
        NameDeclNode(ModifierListNode* mln, IdListNode* iln);
        void accept(Visitor* visitor) ;
        ~NameDeclNode();
};
#endif

#ifndef FragmentNode_header
#define FragmentNode_header

class FragmentNode : public StatementNode {
    public:
        StatementListNode*  statementListNode;
    public:
        FragmentNode(StatementListNode* sln);
        void accept(Visitor* visitor) ;
        ~FragmentNode();
};
#endif

#ifndef IfNode_header
#define IfNode_header

class IfNode : public StatementNode {
    public:
        ExpressionNode*   expressionNode;
        StatementNode*    statementNode1;
        StatementNode*    statementNode2;
    public:
        IfNode(ExpressionNode* en, StatementNode* sn1, StatementNode* sn2);
        void accept(Visitor* visitor) ;
        ~IfNode();
};
#endif

#ifndef WhileNode_header
#define WhileNode_header

class WhileNode : public StatementNode {
    public:
        ExpressionNode*  expressionNode;
        StatementNode*   statementNode;
    public:
        WhileNode(ExpressionNode* en, StatementNode* sn);
        void accept(Visitor* visitor) ;
        ~WhileNode();
};
#endif

#ifndef ArrayNode_header
#define ArrayNode_header

class ArrayNode : public ExpressionNode {
    public:
        IdNode*          idNode;
        ExpressionNode*  expressionNode;
    public:
        ArrayNode(IdNode* in, ExpressionNode* en);
        void accept(Visitor* visitor) ;
        ~ArrayNode();
};

#endif

#ifndef AssignNode_header
#define AssignNode_header

class AssignNode : public StatementNode {
    public:
        IdNode*           idNode;
        ArrayNode*        arrayNode;
        ExpressionNode*   expressionNode1;
        ExpressionNode*   expressionNode2;
    public:
        AssignNode(IdNode* in, ExpressionNode* en);
        AssignNode(IdNode* in, ExpressionNode* en1, ExpressionNode* en2);
        AssignNode(ArrayNode* an, ExpressionNode* en);
        void accept(Visitor* visitor) ;
        ~AssignNode();
};

#endif

#ifndef FragCallNode_header
#define FragCallNode_header

class FragCallNode : public StatementNode {
    public:
        IdNode*                idNode;
        ExpressionListNode*    expressionList;
    public:
        FragCallNode(IdNode* in, ExpressionListNode* eln);
        void accept(Visitor* visitor) ;
        ~FragCallNode();
};

#endif

#ifndef ReadNode_header
#define ReadNode_header

class ReadNode : public StatementNode {
    public:
        IdNode*                idNode;
        ArrayNode*             arrayNode;
        ExpressionListNode*    expressionListNode;
    public:
        ReadNode(IdNode* in);
        ReadNode(ArrayNode* an);
        ReadNode(ExpressionListNode* eln);
        void accept(Visitor* visitor) ;
        ~ReadNode();
};

#endif

#ifndef WriteNode_header
#define WriteNode_header

class WriteNode : public StatementNode {
    public:
        ExpressionListNode*  expressionListNode;
    public:
        WriteNode(ExpressionListNode* eln);
        void accept(Visitor* visitor);
        ~WriteNode();
};

#endif


#ifndef ConstantNode_header
#define ConstantNode_header

class ConstantNode : public StatementNode {
     public:
        NameDeclNode*  nameNode;
        ExpressionNode* value;
    public:
        ConstantNode(NameDeclNode* ndn, ExpressionNode* en);
        void accept(Visitor* visitor);
        ~ConstantNode();
};
#endif

#ifndef CallNode_header
#define CallNode_header

class CallNode : public ExpressionNode {
    public:
        IdNode*              idNode;
        ExpressionListNode*  expressionListNode;
    public:
        CallNode(IdNode* in, ExpressionListNode* eln);
        void accept(Visitor* visitor) ;
        ~CallNode();
};

#endif

#ifndef RelOpNode_header
#define RelOpNode_header

class RelOpNode : public ExpressionNode {
      public:
        int              op;
        ExpressionNode*  expressionNode1;
        ExpressionNode*  expressionNode2;                
      public:
        RelOpNode(int o, ExpressionNode* en1, ExpressionNode* en2);
        void accept(Visitor* visitor) ;
        ~RelOpNode();
};

#endif

#ifndef AppOpNode_header
#define AppOpNode_header

class AddOpNode : public ExpressionNode {
      public:
        int              op;
        ExpressionNode*  expressionNode1;
        ExpressionNode*  expressionNode2;                
      public:
        AddOpNode(int o, ExpressionNode* en1, ExpressionNode* en2);
        void accept(Visitor* visitor) ;
        ~AddOpNode();
};
#endif

#ifndef MultOpNode_header
#define MultOpNode_header

class MultOpNode : public ExpressionNode {
      public:
        int              op;
        ExpressionNode*  expressionNode1;
        ExpressionNode*  expressionNode2;                
      public:
        MultOpNode(int o, ExpressionNode* en1, ExpressionNode* en2);
        void accept(Visitor* visitor) ;
        ~MultOpNode();
};

#endif

#ifndef BoolOpNode_header
#define BoolOpNode_header

class BoolOpNode : public ExpressionNode {
      public:
        int              op;
        ExpressionNode*  expressionNode1;
        ExpressionNode*  expressionNode2;                
      public:
        BoolOpNode(int o, ExpressionNode* en1, ExpressionNode* en2);
        void accept(Visitor* visitor) ;
        ~BoolOpNode();
};

#endif

#ifndef BitwiseOpNode_header
#define BitwiseOpNode_header

class BitwiseOpNode : public ExpressionNode {
      public:
        int              op;
        ExpressionNode*  expressionNode1;
        ExpressionNode*  expressionNode2;                
      public:
        BitwiseOpNode(int o, ExpressionNode* en1, ExpressionNode* en2);
        void accept(Visitor* visitor) ;
        ~BitwiseOpNode();
};

#endif


#ifndef NotNode_header
#define NotNode_header

class NotNode : public ExpressionNode {
    public:
        ExpressionNode*  expressionNode;
    public:
        NotNode(ExpressionNode* en);
        void accept(Visitor* visitor) ;
        ~NotNode();
};

#endif

#ifndef NegativeNode_header
#define NegativeNode_header

class NegativeNode: public ExpressionNode {
    public:
        ExpressionNode*  expressionNode;
    public:
        NegativeNode(ExpressionNode* en);
        void accept(Visitor* visitor) ;
        ~NegativeNode();
};
#endif
