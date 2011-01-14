#ifndef execengine_kernelobjects_Class_h
#define execengine_kernelobjects_Class_h

#include <string>
#include <map>
#include "kernelobjects/Object.h"

namespace execengine {
    
    class Method;
    
    typedef map<string, Method*> MethodsMap;
    typedef map<string, Object*> VariablesMap;
    
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
    
} // namespace execengine


#endif // execengine_kernelobjects_Class_h
