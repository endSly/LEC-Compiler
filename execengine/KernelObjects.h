
#ifndef execengine_KernelObjects_h
#define execengine_KernelObjects_h

#include <vector>
#include <map>
#include <string>

#include "kernelobjects/Object.h"
#include "kernelobjects/Class.h"
#include "kernelobjects/String.h"
#include "kernelobjects/Integer.h"
#include "kernelobjects/Decimal.h"
#include "kernelobjects/Boolean.h"

namespace ast {
    class CodeBlock;
}

namespace execengine {
    
    using namespace std;
    using namespace ast;
    
    bool checkMethodParams(const vector<Object*>&, ...);
    
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
    
    class Character : public Object {
    public:
        Character(unsigned int character) : m_character(character) { }
        
        static Class* ObjectClass();
        Class* objectClass() { return Character::ObjectClass(); }
        
    private:
        unsigned int m_character; 
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
