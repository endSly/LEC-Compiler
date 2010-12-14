
#include "ast/ASTNode.h"

class AST::NodeExpresion;

namespace AST {
    
    class NodeBinaryOperator : ASTNode {
    public:
        
        
    private:
        NodeExpresion* m_leftExpresion;
        NodeExpresion* m_rightExpresion;
        
        int m_operation;
    };
    
}
