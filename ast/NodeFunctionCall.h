#ifndef AST_NodeFunctionCall_h
#define AST_NodeFunctionCall_h

#include <string>
#include <vector>
#include "ASTNode.h"

namespace ast {
    
    using namespace std;
    
    class NodeFunctionCall : public ASTNode {
        
    public:
        NodeFunctionCall(string* signature, vector<ASTNode*>* inParams, vector<ASTNode*>* outParams)
            : m_functionSignature(signature)
            , m_inputParams(inParams)
            , m_outputParams(outParams) { }
            
        ~NodeFunctionCall() { delete m_functionSignature; delete m_inputParams; delete m_outputParams; }
        
        inline string* functionSignature() { return m_functionSignature; }
        inline vector<ASTNode*>* inputParameters() { return m_inputParams; }
        inline vector<ASTNode*>* outputParameters() { return m_outputParams; }
        
    private:
        string* m_functionSignature;
        vector<ASTNode*>* m_inputParams;
        vector<ASTNode*>* m_outputParams;
        
    };
    
} // namespace ast

#endif // AST_NodeFunctionCall_h


