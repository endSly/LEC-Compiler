#ifndef AST_NodeBlock_h
#define AST_NodeBlock_h

#include <vector>
#include "ASTNode.h"

namespace ast {
    
    class NodeBlock : public ASTNode {
        
    public:
        NodeBlock() : m_nodeList(new std::vector<ASTNode*>()) { }
        ~NodeBlock() { delete m_nodeList; }
        
        inline void addNode(ASTNode* node) { m_nodeList->push_back(node); }
        
        
        inline std::vector<ASTNode*>* nodeList() { return m_nodeList; }
        
    private:
        std::vector<ASTNode*>* m_nodeList;
        
    };
    
} // namespace ast

#endif // AST_NodeBlock_h
