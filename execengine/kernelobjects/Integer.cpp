
#include <cstdio>
#include "kernelobjects/Integer.h"
#include "kernelobjects/Decimal.h"
#include "kernelobjects/Boolean.h"
#include "kernelobjects/Class.h"
#include "ExecEngine.h"

namespace execengine {

Class* Integer::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
    if (!s_objectClass) { /* We are going to make Class */
        MethodsMap* methodsMap = new MethodsMap();
        (*methodsMap)[string("toString")] = new KernelMethod(string("toString"), Integer::kernel_Integer_toString);
        (*methodsMap)[string("+@")] = new KernelMethod(string("+@"), Integer::kernel_Integer_add);
        (*methodsMap)[string("-@")] = new KernelMethod(string("-@"), Integer::kernel_Integer_sub);
        (*methodsMap)[string("*@")] = new KernelMethod(string("*@"), Integer::kernel_Integer_mul);
        (*methodsMap)[string("/@")] = new KernelMethod(string("/@"), Integer::kernel_Integer_fdiv);
        (*methodsMap)[string("//@")] = new KernelMethod(string("//@"), Integer::kernel_Integer_idiv);
        (*methodsMap)[string("%@")] = new KernelMethod(string("%@"), Integer::kernel_Integer_mod);
        (*methodsMap)[string("==@")] = new KernelMethod(string("==@"), Integer::kernel_Integer_equal);
        (*methodsMap)[string("!=@")] = new KernelMethod(string("!=@"), Integer::kernel_Integer_notEqual);
        (*methodsMap)[string(">@")] = new KernelMethod(string(">@"), Integer::kernel_Integer_greater);
        (*methodsMap)[string("<@")] = new KernelMethod(string("<@"), Integer::kernel_Integer_lower);
        (*methodsMap)[string(">=@")] = new KernelMethod(string(">=@"), Integer::kernel_Integer_greaterEq);
        (*methodsMap)[string("<=@")] = new KernelMethod(string("<=@"), Integer::kernel_Integer_lowerEq);
        
        MethodsMap* classMethodsMap = new MethodsMap();
        
        s_objectClass = new Class(string("Integer"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

Object* Integer::kernel_Integer_toString(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, NULL)) {
        char str[24];
        sprintf(str, "%lld", ((Integer*) self)->m_value);
        return new String(string(str));
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Integer::kernel_Integer_add(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        return new Integer(((Integer*) self)->m_value + ((Integer*) params[0])->m_value);
        
    } else if (checkMethodParams(&params, Decimal::ObjectClass(), NULL)) {
        return new Decimal(((Integer*) self)->m_value + ((Decimal*) params[0])->value());
        
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Integer::kernel_Integer_sub(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        return new Integer(((Integer*) self)->m_value - ((Integer*) params[0])->m_value);
        
    } else if (checkMethodParams(&params, Decimal::ObjectClass(), NULL)) {
        return new Decimal(((Integer*) self)->m_value - ((Decimal*) params[0])->value());
        
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Integer::kernel_Integer_mul(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        return new Integer(((Integer*) self)->m_value * ((Integer*) params[0])->m_value);
        
    } else if (checkMethodParams(&params, Decimal::ObjectClass(), NULL)) {
        return new Decimal(((Integer*) self)->m_value * ((Decimal*) params[0])->value());
        
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Integer::kernel_Integer_fdiv(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        if ((((Integer*) self)->m_value % ((Integer*) params[0])->m_value) == 0)
            return new Integer(((Integer*) self)->m_value / ((Integer*) params[0])->m_value);
        else
            return new Decimal((double)(((Integer*) self)->m_value) / ((Integer*) params[0])->m_value);
            
    } else if (checkMethodParams(&params, Decimal::ObjectClass(), NULL)) {
        return new Decimal((double)(((Integer*) self)->m_value) / ((Decimal*) params[0])->value());
        
    }else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Integer::kernel_Integer_idiv(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        return new Integer(((Integer*) self)->m_value / ((Integer*) params[0])->m_value);
        
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Integer::kernel_Integer_mod(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        return new Integer(((Integer*) self)->m_value % ((Integer*) params[0])->m_value);
        
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}
        
Object* Integer::kernel_Integer_equal(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) 
        return Boolean::boolean(((Integer*) self)->m_value == ((Integer*) params[0])->m_value);
        
    return Boolean::False();
}

Object* Integer::kernel_Integer_notEqual(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) 
        return Boolean::boolean(((Integer*) self)->m_value != ((Integer*) params[0])->m_value);
        
    return Boolean::True();
}

Object* Integer::kernel_Integer_greater(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        return Boolean::boolean(((Integer*) self)->m_value > ((Integer*) params[0])->m_value);
        
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Integer::kernel_Integer_lower(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        return Boolean::boolean(((Integer*) self)->m_value < ((Integer*) params[0])->m_value);
        
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Integer::kernel_Integer_greaterEq(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        return Boolean::boolean(((Integer*) self)->m_value >= ((Integer*) params[0])->m_value);
        
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}

Object* Integer::kernel_Integer_lowerEq(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, Integer::ObjectClass(), NULL)) {
        return Boolean::boolean(((Integer*) self)->m_value <= ((Integer*) params[0])->m_value);
        
    } else
        ExecEngine::execengineError(string("Incorrect parameter"));
}


}
