#ifndef AST_NodeFunctionDeclaration_h
#define AST_NodeFunctionDeclaration_h

#include <string>
#include <vector>
#include "ASTNode.h"
#include "NodeBlock.h"
#include "NodeVariableDeclaration.h"

namespace ast {
    
    using namespace std;
    
    class NodeFunctionDeclaration : public ASTNode {
        
    public:
        NodeFunctionDeclaration(string* functionName, 
                                vector<NodeVariableDeclaration*>* inputParams,
                                vector<NodeVariableDeclaration*>* outputParams,
                                NodeBlock* functionBlock) 
                                : m_functionName(functionName)
                                , m_inputParameters(inputParams)
                                , m_outputParameters(outputParams)
                                , m_functionBlock(functionBlock) { }
                                
        inline ~NodeFunctionDeclaration() { 
            delete m_functionName; 
            delete m_inputParameters;
            delete m_outputParameters;
            delete m_functionBlock;
        }
        
        inline string* functionName() { return m_functionName; }
        inline vector<NodeVariableDeclaration*>* inputParameters() { return m_inputParameters; }
        inline vector<NodeVariableDeclaration*>* outputParameters() { return m_outputParameters; }
        inline NodeBlock* functionBlock() { return m_functionBlock; }
        
    private:
        string* m_functionName;
        vector<NodeVariableDeclaration*>* m_inputParameters;
        vector<NodeVariableDeclaration*>* m_outputParameters;
        NodeBlock* m_functionBlock;
        
        
    };
    
} // namespace ast

#endif // AST_NodeFunctionDeclaration_h