
#include "ExecEngine.h"
#include "KernelObjects.h"
#include "kernelobjects/Boolean.h"

namespace execengine {

Class* Boolean::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
    if (!s_objectClass) { /* We are going to make Class */
        MethodsMap* methodsMap = new MethodsMap();
        (*methodsMap)[string("ifTrue:@")] = new KernelMethod(string("ifTrue:@"), Boolean::kernel_Boolean_ifTrue);
        (*methodsMap)[string("ifFalse:@")] = new KernelMethod(string("ifFalse:@"), Boolean::kernel_Boolean_ifFalse);
        (*methodsMap)[string("not")] = new KernelMethod(string("not"), Boolean::kernel_Boolean_not);
        (*methodsMap)[string("and@")] = new KernelMethod(string("and@"), Boolean::kernel_Boolean_and);
        (*methodsMap)[string("or@")] = new KernelMethod(string("or@"), Boolean::kernel_Boolean_or);
        (*methodsMap)[string("nand@")] = new KernelMethod(string("nand@"), Boolean::kernel_Boolean_nand);
        (*methodsMap)[string("nor@")] = new KernelMethod(string("nor@"), Boolean::kernel_Boolean_nor);
        (*methodsMap)[string("xor@")] = new KernelMethod(string("xor@"), Boolean::kernel_Boolean_xor);
        
        MethodsMap* classMethodsMap = new MethodsMap();
        (*classMethodsMap)[string("true")] = new KernelMethod(string("true"), Boolean::kernel_Boolean_true);
        (*classMethodsMap)[string("false")] = new KernelMethod(string("false"), Boolean::kernel_Boolean_false);
        
        s_objectClass = new Class(string("Boolean"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

/* Kernel Methods */
Object* Boolean::kernel_Boolean_true(Object*, const vector<Object*>& params)
{
    if (checkMethodParams(params, NULL))
        return Boolean::True();
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Boolean::kernel_Boolean_false(Object*, const vector<Object*>& params)
{
    if (checkMethodParams(params, NULL))
        return Boolean::False();
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
}
        
Object* Boolean::kernel_Boolean_ifTrue(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, Object::ObjectClass(), NULL)) {
        if (((Boolean*) self)->m_value) 
            return params[0]->processMessage(string("evaluate"), params);
            
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Boolean::kernel_Boolean_ifFalse(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, Object::ObjectClass(), NULL)) {
        if (!((Boolean*) self)->m_value) 
            return params[0]->processMessage(string("evaluate"), params);
    }
}
        
Object* Boolean::kernel_Boolean_not(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, NULL))
        return self == Boolean::True() ? Boolean::False() : Boolean::True();
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Boolean::kernel_Boolean_and(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, Boolean::ObjectClass(), NULL))
        return Boolean::boolean(((Boolean*) self)->m_value && ((Boolean*) params[0])->m_value);
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Boolean::kernel_Boolean_or(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, Boolean::ObjectClass(), NULL))
        return Boolean::boolean(((Boolean*) self)->m_value || ((Boolean*) params[0])->m_value);
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Boolean::kernel_Boolean_nand(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, Boolean::ObjectClass(), NULL))
        return Boolean::boolean(!(((Boolean*) self)->m_value || ((Boolean*) params[0])->m_value));
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Boolean::kernel_Boolean_nor(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, Boolean::ObjectClass(), NULL))
        return Boolean::boolean(!(((Boolean*) self)->m_value || ((Boolean*) params[0])->m_value));
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Boolean::kernel_Boolean_xor(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, Boolean::ObjectClass(), NULL))
        return Boolean::boolean(((Boolean*) self)->m_value ^ ((Boolean*) params[0])->m_value);
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

} // namespace execengine
