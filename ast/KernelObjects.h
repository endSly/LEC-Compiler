

#ifndef AST_KernelObjects_h
#define AST_KernelObjects_h

#include <vector>
#include <map>
#include <string>

namespace ast {
    
    using namespace std;
    
    class Class;
    class CodeBlock;
    class Object;
    
    class Expression;

    typedef map<string, CodeBlock*> MethodsMap;
    typedef map<string, Object*> VariablesMap;
    
    class Object {
    public:
        Object(Class*);
        
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
        static Object* nilObject();
        
        virtual ~Object();
        
        
    private:
        Object();
        
        Class* m_class;
        unsigned int m_referencesCount;
        
        static VariablesMap* m_globalVariables;
        VariablesMap* m_localVariables;
        MethodsMap* m_localMethods;
    };
    
    class Class : public Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        Class* m_superClass;
        MethodsMap m_classMethods;
        
    };
    
    class CodeBlock : public Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&);
    };
    
    class String : public Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        std::string m_string; 
    };
    
    class Boolean : public Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        bool m_value;
    };
    
    class Integer : public Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        long long m_value;
    };
    
    class Decimal : public Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        double m_value;
    };
    
}


#endif // AST_KernelObjects_h