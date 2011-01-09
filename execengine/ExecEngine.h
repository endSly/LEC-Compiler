#ifndef execengine_ExecEngine_h
#define execengine_ExecEngine_h

#include <string>
#include <vector>
#include <map>

#include "ast/AST.h"

namespace execengine {
    
    using namespace std;
    
    void execengineWarning(const string& msg);
    void execengineError(const string& msg);
    
    class Method {
    public:
        Method(ast::MethodDeclaration* decl) : methodName(decl->name()), code(decl->methodCode()), parameters(decl->parametersList()) { }
        Method(string name, CodeBlock* cb, vector<string>* params) : methodName(name), code(cb), parameters(params) { }
        string methodName;
        CodeBlock* code;
        vector<string>* parameters;
    };
    
    class ExecEngine {
    public:
        ExecEngine();
        
        ~ExecEngine();
        
        void initializeEngine(ast::AST*);
        
        int execute(const std::string&, const std::string&);
        
    private:
        VariablesMap* m_globalVars;
    };
    
} // namespace execengine

#endif // execengine_ExecEngine_h
