
#ifndef AST_AST_h
#define AST_AST_h

#include <vector>

#include "ASTNode.h"
#include "NodeAssignament.h"
#include "NodeBlock.h"
#include "NodeBinaryOperator.h"
#include "NodeConditional.h"
#include "NodeFunctionCall.h"
#include "NodeFunctionDeclaration.h"
#include "NodeLiteral.h"


namespace ast {
    
    class AST {
        
    public:
        AST(ASTNode* node) : m_rootNode(node) { }
        inline ASTNode* rootNode() { return m_rootNode; }
        
    private:

        ASTNode* m_rootNode;
    };
    
} // namespace ast

#endif // AST_AST_h


