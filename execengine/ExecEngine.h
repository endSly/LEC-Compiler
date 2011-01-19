#ifndef execengine_ExecEngine_h
#define execengine_ExecEngine_h

#include <string>
#include <vector>
#include <map>

namespace ast {
    class AST;
    class MethodDeclaration;
    class CodeBlock;
}

namespace execengine {
    
    using namespace std;
    using namespace ast;
    
    class Object;
    
    class Method {
    public:
        virtual Object* run(Object* self, const vector<Object*>& param) { return 0; }
    
    protected:
        Method(const string& name, vector<string>* params = NULL)  : m_name(name), m_parametersName(params) { }
        
        string m_name;
        vector<string>* m_parametersName;
    };
    
    class DynamicMethod : public Method {
    public:
        DynamicMethod(ast::MethodDeclaration* decl);
        
        Object* run(Object* self, const vector<Object*>& params);
    
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
    
    typedef map<string, Method*> MethodsMap;
    typedef map<string, Object*> VariablesMap;
    
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
        
    private:
        ExecEngine() { }
    };
    
    class ExecContext {
        friend class ExecEngine;
    public:
        ExecContext(Object* self) : m_self(self) { }
        
        inline Object* self() { return m_self; }
        static inline VariablesMap* globalVariables() { static VariablesMap* s_gv = new VariablesMap(); return s_gv; }
        inline VariablesMap* contextVariables() { return &m_contextVariables; }
        
        Object* getVariable(const string&);
        Object* setVariable(const string&, Object*);
    
    private:
        Object* m_self;
        VariablesMap m_contextVariables;
    };
    
} // namespace execengine

#endif // execengine_ExecEngine_h
