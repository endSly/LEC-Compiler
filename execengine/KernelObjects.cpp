
#include <iostream>
#include <cstdlib>
#include "KernelObjects.h"
#include "ExecEngine.h"

#include "ast/AST.h"

namespace execengine {

/** Object */
Object* Object::processMessage(const string& method, const vector<Object*>& params) 
{ 
    this->objectClass()->processObjectMessage(this, method, params); 
}

Class* Object::ObjectClass()
{
    static Class s_objectClass(string("Object"), NULL);
    return &s_objectClass;
}

/** Class */
Object* Class::kernel_Class_className(Object* self, const vector<Object*>& params)
{
    Class* cl = dynamic_cast<Class*>(self);
    
    if (cl)
        return new String(cl->className());
        
    execengineError(string("Kernel class panic! ") + self->objectClass()->className());
    return Nil::nil();
    
}

/** DynamicClass */
DynamicClass::DynamicClass(string className, Class* superClass, MethodsMap* objectMethods, MethodsMap* classMethods, vector<string>* vars) 
    : Class(className, superClass)
    , m_classMethods(classMethods)
    , m_objectMethods(objectMethods)
    , m_classVariables(m_classVariables)
{ }

Object* DynamicClass::processObjectMessage(Object* self, const string& method, const vector<Object*>& params)
{
    MethodsMap::iterator it = m_objectMethods->find(method);
    if (it != m_objectMethods->end()) {
        Method* method = it->second;
        return method->code->evaluate(self);
    } 
    
    execengineWarning("Trying to call to undefined object method. @nil returned. " + self->objectClass()->className() + " " +  method);
    return Nil::nil();
}

Object* DynamicClass::processMessage(const string& method, const vector<Object*>& params)
{
    MethodsMap::iterator it = m_classMethods->find(method);
    if (it != m_classMethods->end()) {
        Method* method = it->second;
        return method->code->evaluate(this);
    } 
    
    execengineWarning("Trying to call to undefined class method. @nil returned. " + this->objectClass()->className() + " " +  method);
    return Nil::nil();
}

Object* kernel_DynamicClass_new(Object* self, const vector<Object*>& params)
{
    DynamicClass* constructorClass = dynamic_cast<DynamicClass*>(self);
    
    if (constructorClass)
        return new DynamicObject(constructorClass);
        
    execengineError("Kernel Class Panic! " + (self ? self->objectClass()->className() : string("NULL class")));
    
}

Class* DynamicClass::objectClass()
{
    static KernelClass *s_objectClass = NULL;
    
    if (!s_objectClass) {
        KernelMethodsMap* methodsMap = new KernelMethodsMap();
        (*methodsMap)[string("className")] = Class::kernel_Class_className;
        
        s_objectClass = new KernelClass(string("Class"), Object::ObjectClass(), methodsMap);
    }
    
    return s_objectClass;
}

/** KernelClass */
KernelClass::KernelClass(string className, Class* superClass, KernelMethodsMap* methods) 
    : Class(className, superClass)
    , m_kernelMethods(methods) 
{ }

Object* KernelClass::processObjectMessage(Object* self, const string& method, const vector<Object*>& params)
{
    KernelMethodsMap::iterator it = m_kernelMethods->find(method);
    if (it != m_kernelMethods->end()) {
        KernelMethod method = it->second;
        return (*method)(self, params);
    }
    
    execengineWarning(string("Trying to call to undefined kernel method. @nil returned. "));// + self->objectClass()->className() + " " +  method);

    return Nil::nil();
}

Class* KernelClass::objectClass()
{
    static KernelClass *s_objectClass = NULL;
    
    if (!s_objectClass) {
        KernelMethodsMap* methodsMap = new KernelMethodsMap();
        (*methodsMap)[string("className")] = Class::kernel_Class_className;
        
        s_objectClass = new KernelClass(string("Class"), Object::ObjectClass(), methodsMap);
    }
    
    return s_objectClass;
}


static Object* kernel_KernelClass_new(Object*, const vector<Object*>&)
{
    return Nil::nil();
}

/** DynamicObject */
DynamicObject::DynamicObject(Class* objClass)
    : m_class(objClass)
    , m_localVariables(new VariablesMap())
{
    /*
     * TODO!!!
     *
    vector<string>* vars = objClass->classVariables();
    for (vector<string>::iterator var = vars->begin(); var != vars->end(); var++) {
    }
    */
    
}

Object* DynamicObject::getVariable(const string& varName)
{
    Object* result;
    VariablesMap::iterator it = m_localVariables->find(varName);
    if (it != m_localVariables->end()) {
        result = it->second;
    } else {
        execengineWarning(string("Trying to access to undefined variable. @nil returned. ") + this->m_class->className() + " " +  varName);
        result = Nil::nil();
    }
    return result;
}


/*
 *  String
 */
Class* String::ObjectClass()
{
    static KernelClass* s_stringClass = NULL;
    
    if (!s_stringClass) { /* We are going to make Class */
        KernelMethodsMap* methodsMap = new KernelMethodsMap();
        (*methodsMap)[string("+@")] = &String::kernel_String_concat;
        (*methodsMap)[string("append:@")] = &String::kernel_String_concat;
        (*methodsMap)[string("print")] = &String::kernel_String_print;
        (*methodsMap)[string("length")] = &String::kernel_String_length;
        
        s_stringClass = new KernelClass(string("String"), Object::ObjectClass(), methodsMap);
    }
    
    return s_stringClass;
}

Object* String::kernel_String_concat(Object* self, const vector<Object*>& params)
{
    String* str = dynamic_cast<String*>(self);
    String* param = dynamic_cast<String*>(params[0]);
    
    if (str && param) 
        str->m_string.append(param->m_string);
    else
        execengineError(string("Incorrect parameter"));
    
    return self;
}

Object* String::kernel_String_print(Object* self, const vector<Object*>&)
{
    String* str = dynamic_cast<String*>(self);
    
    if (str) 
        cout << str->m_string;
    else
        execengineError(string("Incorrect parameter"));
        
    return self;
}

Object* String::kernel_String_length(Object* self, const vector<Object*>&)
{
    String* str = dynamic_cast<String*>(self);
    
    if (str) 
        return new Integer(str->m_string.length());
    else
        execengineError(string("Incorrect parameter"));
        
    return self;
}
    
/*
 *  Character
 */ 
Class* Character::ObjectClass()
{
    return NULL;
}

/*
 *  Boolean
 */ 
Class* Boolean::ObjectClass()
{
    return NULL;
}

/*
 *  Integer
 */ 
Class* Integer::ObjectClass()
{
    return NULL;
}

/*
 *  Decimal
 */
Class* Decimal::ObjectClass()
{
    return NULL;
}
     
} // namespace execengine
