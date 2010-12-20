#ifndef AST_NodeVariableDeclaration_h
#define AST_NodeVariableDeclaration_h

#include <string>
#include "ASTNode.h"

namespace ast {
    
    class NodeVariableDeclaration : public ASTNode {
        
    public:
        NodeVariableDeclaration(std::string* variableName) : m_variableName(variableName) { }
        ~NodeVariableDeclaration() { }
        
    private:
        std::string* m_variableName;
        
    };
    
} // namespace ast

#endif // AST_NodeVariableDeclaration_h
