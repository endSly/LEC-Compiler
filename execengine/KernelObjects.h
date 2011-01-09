
#ifndef execengine_KernelObjects_h
#define execengine_KernelObjects_h

#include <vector>
#include <map>
#include <string>

namespace ast {
    class CodeBlock;
}

namespace execengine {
    
    using namespace std;
    using namespace ast;
    
    class Method;
    
    class Class;
    class KernelClass;
    class Routine;
    class Object;
    class Nil;

    typedef Object* (*KernelMethod)(Object*, const vector<Object*>&);
    typedef map<string, KernelMethod> KernelMethodsMap;
    typedef map<string, Method*> MethodsMap;
    typedef map<string, Object*> VariablesMap;

    class Object {
    public:
        Object() { }
        virtual Object* processMessage(const string&, const vector<Object*>&);
        virtual Class* objectClass()  { return Object::objectClass(); }
        virtual ~Object() { }
        Object* getVariable(const string& varName) { return this; }
        
        static Class* ObjectClass();
    };
    
    class Class : public Object {
    public:
        Class(string className, Class* superClass) : m_className(className), m_superClass(superClass) { }
        virtual Object* processObjectMessage(Object*, const string&, const vector<Object*>&) { }
        string className() { return m_className; }
        ~Class() { }
        virtual Class* objectClass() { }
        
        static Object* kernel_Class_className(Object*, const vector<Object*>&);
        
    private:
        string m_className;
        Class* m_superClass;
    };
    
    class DynamicClass : public Class {
    public:
        ~DynamicClass() { delete m_objectMethods; delete m_classMethods; delete m_classVariables; }
        
        DynamicClass(string, Class*, MethodsMap*, MethodsMap*, vector<string>*);
        Object* processObjectMessage(Object*, const string&, const vector<Object*>&);
        Object* processMessage(const string&, const vector<Object*>&);
        Class* objectClass();
        
    private:
        MethodsMap* m_classMethods;
        MethodsMap* m_objectMethods;
        vector<string>* m_classVariables;
    };
    
    /**
     *  KernelClass stores KernelObjects methods
     */
    class KernelClass : public Class {
    public:
        ~KernelClass() { delete m_kernelMethods; }
        
        KernelClass(string, Class*, KernelMethodsMap*);
        Object* processObjectMessage(Object*, const string&, const vector<Object*>&);
        Class* objectClass();
        
        static Object* kernel_KernelClass_new(Object*, const vector<Object*>&);
        
    private:
        KernelMethodsMap* m_kernelMethods;
    };
    
    class DynamicObject : public Object {
    public:
        Class* objectClass() { return m_class; }
        ~DynamicObject() { delete m_localVariables; }
    
        DynamicObject(Class*);
        Object* getVariable(const string& varName);

        static Object* kernel_DynamicClass_new(Object*, const vector<Object*>&);

    private:
        VariablesMap* m_localVariables;
        
        Class* m_class;
    };
    
    class Nil : public Object {    
    public:
        static Object* nil() { static Nil s_nil; return &s_nil; }
        Object* processMessage(const string&, const vector<Object*>&) { return this; }
        Object* getVariable(const string& varName) { return this; }
        Class* objectClass() { return Object::ObjectClass(); }
    };

    class String : public Object {
    public:
        String(const std::string& str) : m_string(str) { }
        ~String() { }
        
        static Class* ObjectClass();
        Class* objectClass() { return String::ObjectClass(); }
        
        static Object* kernel_String_concat(Object*, const vector<Object*>&);
        static Object* kernel_String_print(Object*, const vector<Object*>&);
        static Object* kernel_String_length(Object*, const vector<Object*>&);
        
    private:
        std::string m_string; 
    };
    
    class Character : public Object {
    public:
        Character(unsigned int character) : m_character(character) { }
        ~Character() { }
        
        static Class* ObjectClass();
        Class* objectClass() { return Character::ObjectClass(); }
        
    private:
        unsigned int m_character; 
    };
    
    class Boolean : public Object {
    public:
        static Boolean* True();
        static Boolean* False();
    
        static Class* ObjectClass();
        Class* objectClass() { return Boolean::ObjectClass(); }

    private:
        Boolean() { }
        Boolean(const Boolean&) { }
        ~Boolean() { }
        
        bool m_value;
        
        static Boolean* m_false;
        static Boolean* m_true;
    };
    
    class Integer : public Object {
    public:
        Integer(long long value) : m_value(value) { }
        ~Integer() { }
        
        static Class* ObjectClass();
        Class* objectClass() { return Integer::ObjectClass(); }
        
    private:
        long long m_value;
    };
    
    class Decimal : public Object {
    public:
        Decimal(double value) : m_value(value) { }
        ~Decimal() { }
        
        static Class* ObjectClass();
        Class* objectClass() { return Decimal::ObjectClass(); }
        
    private:
        double m_value;
    };


    class Routine : public Object {
    public:
        Routine(CodeBlock* code, Object* obj) : m_routineCode(code), m_runningObject(obj) { }
        ~Routine() { }
        
        static Class* ObjectClass();
        Class* objectClass() { return Routine::ObjectClass(); }
        
    private:
        CodeBlock* m_routineCode;
        Object* m_runningObject;
    };
    
        
}


#endif // execengine_KernelObjects_h
