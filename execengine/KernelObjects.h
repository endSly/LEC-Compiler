
#ifndef execengine_KernelObjects_h
#define execengine_KernelObjects_h

#include <vector>
#include <map>
#include <string>

namespace ast {
    class CodeBlock;
    class Expression;
}

namespace execengine {
    
    using namespace std;
    using namespace ast;
    
    class Class;
    class Routine;
    class Object;
    class Nil;
    
    typedef Object* (*NativeMethod)(const Object*, const vector<Object*>);
    typedef map<string, NativeMethod*> KernelMethodsMap;
    typedef map<string, CodeBlock*> MethodsMap;
    typedef map<string, Object*> VariablesMap;

    static VariablesMap* m_globalVariables;
    
    class Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&) { }
        virtual Object* getVariable(const string& varName) { }

        virtual ~Object() { }
 
    protected:
        Object() { }
        VariablesMap* globalVariables() { return m_globalVariables; }
        
    private:
        unsigned int m_referencesCount;
        
        static VariablesMap* m_globalVariables;
    };
    
    class DynamicObject : public Object {
    public:
        DynamicObject(Class*);
    
        Object* processMessage(const string&, const vector<Object*>&);
        Object* getVariable(const string& varName);

        ~DynamicObject() { delete m_localVariables; }
        
    private:
        Class* m_class;
        
        
        VariablesMap* m_localVariables;
    };
    
    class KernelObject : public Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&);
        Object* getVariable(const string&);
        
        ~KernelObject() { }
        
    protected:
        KernelObject() { }
    };
    
    class Nil : public KernelObject {
    private:
        Nil() { }
        Nil(const Nil&) { }
        
    public:
        static Object* nil() { static Nil s_nil; return &s_nil; }
        
        Object* processMessage(const string&, const vector<Object*>&) { return this; }
        Object* getVariable(const string& varName) { return this; }
    };
    
    
    class Class : public KernelObject {
    public:
        Class(string);
    
        Object* processMessage(const string&, const vector<Object*>&);
        string className() { return m_className; }
        vector<string>* classVariables() { return m_classVars; }
        MethodsMap* classMethods() { return m_classMethods; }
        
        ~Class() { }
    private:
        static Class* m_class;
        static KernelMethodsMap* m_classKernelMethods;
        
        MethodsMap* m_classMethods;
        vector<string>* m_classVars;
        
        string m_className;
        Class* m_superClass;
    };
    
    class Routine : public KernelObject {
    public:
        Routine(CodeBlock* code, Object* obj) : m_routineCode(code), m_runningObject(obj) { }
        Object* processMessage(const string&, const vector<Object*>&);
        ~Routine() { }
        
    private:
        static Class* m_class;
        static KernelMethodsMap* m_classMethods;
        
        CodeBlock* m_routineCode;
        Object* m_runningObject;
    };
    
    class String : public KernelObject {
    public:
        String(const std::string& str) : m_string(str) { }
        Object* processMessage(const string&, const vector<Object*>&);
        ~String() { }
        
    private:
        static Class* m_class;
        static KernelMethodsMap* m_classMethods;
        
        std::string m_string; 
    };
    
    class Character : public KernelObject {
    public:
        Character(unsigned int character) : m_character(character) { }
        Object* processMessage(const string&, const vector<Object*>&);
        ~Character() { }
        
    private:
        static Class* m_class;
        static KernelMethodsMap* m_classMethods;
        
        unsigned int m_character; 
    };
    
    class Boolean : public KernelObject {
    public:
        static Boolean* True();
        static Boolean* False();
    
        Object* processMessage(const string&, const vector<Object*>&);

    private:
        Boolean() { }
        Boolean(const Boolean&) { }
        ~Boolean() { }
    
        static Class* m_class;
        static KernelMethodsMap* m_classMethods;
    
        bool m_value;
        
        static Boolean* m_false;
        static Boolean* m_true;
    };
    
    class Integer : public KernelObject {
    public:
        Integer(long long value) : m_value(value) { }
        Object* processMessage(const string&, const vector<Object*>&);
        ~Integer() { }
        
    private:
        static Class* m_class;
        static KernelMethodsMap* m_classMethods;
        
        long long m_value;
    };
    
    class Decimal : public KernelObject {
    public:
        Decimal(double value) : m_value(value) { }
        Object* processMessage(const string&, const vector<Object*>&);

        ~Decimal() { }
        
    private:
        static Class* m_class;
        static KernelMethodsMap* m_classMethods;
        
        double m_value;
    };
    
}


#endif // execengine_KernelObjects_h
