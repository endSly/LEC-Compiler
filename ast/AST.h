
#include <vector>
#include "ASTNode.h"

namespace ast {
    
    typedef std::vector<NodeVariableDeclaration*> ParametersList;
    
    class AST {
        
    public:
        AST(ASTNode* node) : m_rootNode(node) { }
        inline ASTNode* rootNode() { return m_rootNode; }
        
        
    private:
        
        
        ASTNode* m_rootNode;
        
        
    }
    
}


