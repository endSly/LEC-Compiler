#ifndef execengine_kernelobjects_DynamicObject_h
#define execengine_kernelobjects_DynamicObject_h

#include "Object.h"
#include "Class.h"

namespace execengine {

    class Class;
    
    class DynamicObject : public Object {
    public:
        Class* objectClass() { return m_class; }
        ~DynamicObject() { delete m_localVariables; }
    
        DynamicObject(Class*);
        Object* getObjectVariable(const string&);
        bool setObjectVariable(const string&, Object*);

        static Object* kernel_DynamicClass_new(Object*, const vector<Object*>&);

    private:
        VariablesMap* m_localVariables;
        
        Class* m_class;
    };
    
} // namespace execengine

#endif // execengine_kernelobjects_DynamicObject_h
