
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
    class Object;
    class Nil;
    
    typedef map<string, Method*> MethodsMap;
    typedef map<string, Object*> VariablesMap;
    
    bool checkMethodParams(const vector<Object*>&, ...);

    class Object {
    public:
        Object() { }
        virtual Object* processMessage(const string&, const vector<Object*>&);
        virtual Class* objectClass()  { return Object::objectClass(); }
        virtual ~Object() { }
        virtual Object* getVariable(const string& varName) { return this; }
        
        bool isInstanceOf(Class*);
        
        static Class* ObjectClass();
        
        static Object* kernel_Object_class(Object*, const vector<Object*>&);
    };
    
    class Class : public Object {
    public:
        Class(string, Class*, MethodsMap*, MethodsMap*, vector<string>* = NULL);
        ~Class();
        
        inline string className() { return m_className; }
        inline Class* superClass() { return m_superClass; }
        inline vector<string>* classVariables() { return m_classVariables; }
        
        Class* objectClass() { return Class::ObjectClass(); }

        static Class* ObjectClass();
        Object* processObjectMessage(Object*, const string&, const vector<Object*>&);
        Object* processMessage(const string&, const vector<Object*>&);
        
        static Object* kernel_Class_new(Object*, const vector<Object*>&);
        static Object* kernel_Class_className(Object*, const vector<Object*>&);
        
    private:
        string m_className;
        Class* m_superClass;
        MethodsMap* m_classMethods;
        MethodsMap* m_objectMethods;
        vector<string>* m_classVariables;
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
        
        static Class* ObjectClass();
        Class* objectClass() { return String::ObjectClass(); }
        
        static Object* kernel_String_concat(Object*, const vector<Object*>&);
        static Object* kernel_String_println(Object*, const vector<Object*>&);
        static Object* kernel_String_length(Object*, const vector<Object*>&);
        
    private:
        std::string m_string; 
    };
    
    class Character : public Object {
    public:
        Character(unsigned int character) : m_character(character) { }
        
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
        
        static Object* kernel_Integer_toString(Object*, const vector<Object*>&);
        
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
