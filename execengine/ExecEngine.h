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
        virtual Object* run(Object* self, const vector<Object*>& param) { }
    
    protected:
        Method(const string& name, vector<string>* params = NULL)  : m_name(name), m_parameters(params) { }
        
        string m_name;
        vector<string>* m_parameters;
    };
    
    class DynamicMethod : public Method {
    public:
        DynamicMethod(ast::MethodDeclaration* decl) : Method(decl->name(), decl->parametersList()), m_code(decl->methodCode()) { }
        
        Object* run(Object* self, const vector<Object*>&) { return m_code->evaluate(self); }
    
    private:
        CodeBlock* m_code;
    };
    
    typedef Object* (*KernelFunction)(Object*, const vector<Object*>&);
    
    class KernelMethod : public Method {
    public:
        KernelMethod(const string& name, KernelFunction function) : Method(name), m_function(function) { }
    
        Object* run(Object* self, const vector<Object*>& params) { return m_function(self, params); }
        
    private:
        KernelFunction m_function;
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
