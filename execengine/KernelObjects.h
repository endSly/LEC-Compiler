
#ifndef execengine_KernelObjects_h
#define execengine_KernelObjects_h

#include <vector>
#include <map>
#include <string>

#include "kernelobjects/Object.h"
#include "kernelobjects/Class.h"
#include "kernelobjects/String.h"
#include "kernelobjects/Character.h"
#include "kernelobjects/Integer.h"
#include "kernelobjects/Decimal.h"
#include "kernelobjects/Boolean.h"
#include "kernelobjects/Routine.h"


namespace execengine {
    
    using namespace std;
    
    bool checkMethodParams(const vector<Object*> * const, ...);
    
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
    
        
}


#endif // execengine_KernelObjects_h
