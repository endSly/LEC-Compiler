#ifndef execengine_ExecEngine_h
#define execengine_ExecEngine_h

#include <string>
#include <vector>
#include <map>

#include "ast/AST.h"

namespace execengine {
    
    using namespace std;
    using namespace ast;
    
    static void execengineWarning(const string& msg);
    static void execengineError(const string& msg);
    
    class Method {
    public:
        virtual Object* run(Object* self, const vector<Object*>& param) { return 0; }
    
    protected:
        Method(const string& name, vector<string>* params = NULL)  : m_name(name), m_parameters(params) { }
        
        string m_name;
        vector<string>* m_parameters;
    };
    
    class DynamicMethod : public Method {
    public:
        DynamicMethod(ast::MethodDeclaration* decl) : Method(decl->name(), decl->parametersList()), m_code(decl->methodCode()) { }
        
        Object* run(Object* self, const vector<Object*>& params) { return m_code->run(self, params); }
    
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
        

		//! Prints a warning to console and continues
		//! execution.
		//!
		//! @param msg Warning message
		static void execengineWarning(const string& msg);
        
		//! Prints an error to the error stream and aborts the program.
		//! 
		//! @param msg Error message
		//! @return Never returns
		static void execengineError(const string& msg);
    
        static ExecEngine* execEngine();
        
        void initializeEngine(ast::AST*);

		//! Runs the specified method. (The method takes no arguments).
		//!
		//! @param className Name of the class the method belongs to.
		//! @param method Name of the method to run.
        int execute(const std::string& className, const std::string& method);
        

		//! Returns the map of global variables.
		//! 
        VariablesMap* globalVariables() { return m_globalVars; }
        
        
    private:

        ExecEngine() : m_globalVars(new VariablesMap()) { }
        
		~ExecEngine() { delete m_globalVars; }
    
        VariablesMap* m_globalVars;
    };
    
} // namespace execengine

#endif // execengine_ExecEngine_h
