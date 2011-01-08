
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
    class KernelClass;
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
    
    /**
     *  Class is used to store dynamic class methods
     */
    class Class : public Object {
    public:
        Class(string, Class*, MethodsMap*, vector<string>*);
    
        Object* processMessage(const string&, const vector<Object*>&);
        string className() { return m_className; }
        vector<string>* classVariables() { return m_classVars; }
        MethodsMap* classMethods() { return m_classMethods; }
        
        ~Class() { }
    private:
        Class() { }
        Class(const Class&) { }
        
        static KernelClass* m_classKernelMethods;
        
        MethodsMap* m_classMethods;
        vector<string>* m_classVars;
        
        string m_className;
        Class* m_superClass;
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
    
    
    /**
     *  KernelClass stores KernelObjects methods
     */
    class KernelClass : public Object {
    public:
        KernelClass();
        
        Object* processMessage(const string&, const vector<Object*>&);
        Object* getVariable(const string&);
        
        KernelMethodsMap* classMethods() { return m_kernelMethods; }
        
        ~KernelClass() { }

    private:
        KernelMethodsMap* m_kernelMethods;
    };
    
    class Nil : public Object {    
    public:
        static Object* nil() { static Nil s_nil; return &s_nil; }
        
        Object* processMessage(const string&, const vector<Object*>&) { return this; }
        Object* getVariable(const string& varName) { return this; }
        
    private:
        Nil() { }
        Nil(const Nil&) { }
    };
    
    

    class Routine : public Object {
    public:
        Routine(CodeBlock* code, Object* obj) : m_routineCode(code), m_runningObject(obj) { }
        Object* processMessage(const string&, const vector<Object*>&);
        ~Routine() { }
        
    private:
        static KernelClass* m_class;

        CodeBlock* m_routineCode;
        Object* m_runningObject;
    };
    
    class String : public Object {
    public:
        String(const std::string& str) : m_string(str) { }
        Object* processMessage(const string&, const vector<Object*>&);
        ~String() { }
        
    private:
        static KernelClass* m_class;

        std::string m_string; 
    };
    
    class Character : public Object {
    public:
        Character(unsigned int character) : m_character(character) { }
        Object* processMessage(const string&, const vector<Object*>&);
        ~Character() { }
        
    private:
        static KernelClass* m_class;

        unsigned int m_character; 
    };
    
    class Boolean : public Object {
    public:
        static Boolean* True();
        static Boolean* False();
    
        Object* processMessage(const string&, const vector<Object*>&);

    private:
        Boolean() { }
        Boolean(const Boolean&) { }
        ~Boolean() { }
    
        static KernelClass* m_class;
        
        bool m_value;
        
        static Boolean* m_false;
        static Boolean* m_true;
    };
    
    class Integer : public Object {
    public:
        Integer(long long value) : m_value(value) { }
        Object* processMessage(const string&, const vector<Object*>&);
        ~Integer() { }
        
    private:
        static KernelClass* m_class;

        long long m_value;
    };
    
    class Decimal : public Object {
    public:
        Decimal(double value) : m_value(value) { }
        Object* processMessage(const string&, const vector<Object*>&);

        ~Decimal() { }
        
    private:
        static KernelClass* m_class;
        
        double m_value;
    };
    
}


#endif // execengine_KernelObjects_h
