
#include <iostream>
#include "ExecEngine.h"
#include "String.h"

namespace execengine {
    
Class* String::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
	// Load the string class on-demand.
    if (!s_objectClass) { /* We are going to make Class */
        MethodsMap* methodsMap = new MethodsMap();
        (*methodsMap)[string("+@")] = new KernelMethod(string("+@"), String::kernel_String_concat);
        (*methodsMap)[string("append:@")] = new KernelMethod(string("append:@"), String::kernel_String_concat);
        (*methodsMap)[string("println")] = new KernelMethod(string("println"), String::kernel_String_println);
        (*methodsMap)[string("length")] = new KernelMethod(string("length"), String::kernel_String_length);
        
        MethodsMap* classMethodsMap = new MethodsMap();
        (*methodsMap)[string("println")] = new KernelMethod(string("println"), String::kernel_String_println);
        
        s_objectClass = new Class(string("String"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

Object* String::kernel_String_concat(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, String::ObjectClass(), NULL))
        ((String*) self)->m_string.append(((String*) params[0])->m_string);
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
    
    return self;
}

Object* String::kernel_String_println(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, NULL))
        cout << ((String*) self)->m_string << "\n";
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
        
    return self;
}

Object* String::kernel_String_length(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, NULL))
        return new Integer(((String*) self)->m_string.length());
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
        
    return self;
}
    
} // namespace execengine
