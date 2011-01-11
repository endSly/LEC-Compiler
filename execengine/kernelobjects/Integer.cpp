
#include "kernelobjects/Integer.h"
#include "kernelobjects/Class.h"
#include "ExecEngine.h"

namespace execengine {

Class* Integer::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
    if (!s_objectClass) { /* We are going to make Class */
        MethodsMap* methodsMap = new MethodsMap();
        (*methodsMap)[string("toString")] = new KernelMethod(string("toString"), Integer::kernel_Integer_toString);
        
        MethodsMap* classMethodsMap = new MethodsMap();
        
        s_objectClass = new Class(string("Integer"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

Object* Integer::kernel_Integer_toString(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, NULL)) {
        char str[24];
        sprintf(str, "%lld", ((Integer*) self)->m_value);
        return new String(string(str));
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
    
    return self;
}

}
