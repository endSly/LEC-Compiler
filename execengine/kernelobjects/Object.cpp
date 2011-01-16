
#include <iostream>
#include "kernelobjects/Object.h"
#include "kernelobjects/Class.h"
#include "ExecEngine.h"

namespace execengine {

Object* Object::processMessage(const string& method, const vector<Object*>& params) 
{ 
    return this->objectClass()->processObjectMessage(this, method, params); 
}

Class* Object::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
    if (!s_objectClass) {
        MethodsMap* methodsMap = new MethodsMap();
        (*methodsMap)[string("class")] = new KernelMethod(string("class"), Class::kernel_Object_class);
        (*methodsMap)[string("evaluate")] = new KernelMethod(string("evaluate"), Class::kernel_Object_evaluate);
        
        MethodsMap* classMethodsMap = new MethodsMap();
        
        s_objectClass = new Class(string("Object"), NULL, methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

bool Object::isInstanceOf(Class* otherClass)
{
    Class* selfClass = this->objectClass();
    
    // Check if is same class
    if (selfClass == otherClass)
        return true;
        
    // Check if is subclass
    while ((selfClass = selfClass->superClass())) {
        if (selfClass == otherClass)
            return true;
    }
    return false;
}

Object* Object::kernel_Object_class(Object* self, const vector<Object*>& params)
{
    return self->objectClass();
}

Object* Object::kernel_Object_superClass(Object* self, const vector<Object*>& params)
{
    /*
     * TODO!!!
     */
	return 0;
}

Object* Object::kernel_Object_evaluate(Object* self, const vector<Object*>& params)
{
    return self;
}

} // namespace execengine

