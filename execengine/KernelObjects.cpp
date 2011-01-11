
#include <iostream>
#include <cstdlib>
#include "KernelObjects.h"
#include "ExecEngine.h"

#include "ast/AST.h"

namespace execengine {

/** Object */
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
        
        MethodsMap* classMethodsMap = new MethodsMap();
        
        s_objectClass = new Class(string("Object"), NULL, methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

Object* Object::kernel_Object_class(Object* self, const vector<Object*>& parms)
{
    return self->objectClass();
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

/** Class */
Class::Class(string className, Class* superClass, MethodsMap* objectMethods, MethodsMap* classMethods, vector<string>* vars) 
    : m_className(className)
    , m_superClass(superClass)
    , m_classMethods(classMethods)
    , m_objectMethods(objectMethods)
    , m_classVariables(vars)
{ }

Class::~Class() {
    delete m_classMethods;
    delete m_objectMethods;
    delete m_classVariables;
}

Class* Class::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
    if (!s_objectClass) {
        MethodsMap* methodsMap = new MethodsMap();
        (*methodsMap)[string("className")] = new KernelMethod(string("className"), Class::kernel_Class_className);
        
        MethodsMap* classMethodsMap = new MethodsMap();
        (*classMethodsMap)[string("className")] = new KernelMethod(string("className"), Class::kernel_Class_className);
        
        s_objectClass = new Class(string("Class"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

Object* Class::processObjectMessage(Object* self, const string& method, const vector<Object*>& params)
{
    MethodsMap::iterator it = m_objectMethods->find(method);
    if (it != m_objectMethods->end()) {
        Method* method = it->second;
        return method->run(self, params);
    } 
    
    if (m_superClass)
        return m_superClass->processObjectMessage(self, method, params);
    

    ExecEngine::execengineWarning(string("Trying to access to undefined method. @nil returned. ") + this->className() + " " +  method);
    return Nil::nil();
}

Object* Class::processMessage(const string& method, const vector<Object*>& params)
{
    MethodsMap::iterator it = m_classMethods->find(method);
    if (it != m_classMethods->end()) {
        Method* method = it->second;
        return method->run(this, params);
    } 
    
    return this->objectClass()->processObjectMessage(this, method, params); 
    
    /*
    if (m_superClass)
        return m_superClass->processMessage(method, params);
    
    execengineWarning(string("Trying to access to undefined class method. @nil returned. ") + this->className() + " " +  method);
    return Nil::nil();
    */
    
}

Object* kernel_Class_new(Object* self, const vector<Object*>& params)
{
    /*
    
    TODO!!!!
    
    */
}

Object* Class::kernel_Class_className(Object* self, const vector<Object*>& params)
{
    Class* cl = dynamic_cast<Class*>(self);
    
    if (cl)
        return new String(cl->m_className);
        
    ExecEngine::execengineError(string("Kernel class panic! ") + self->objectClass()->className());
    return Nil::nil();
}

/** DynamicObject */
DynamicObject::DynamicObject(Class* objClass)
    : m_class(objClass)
    , m_localVariables(new VariablesMap())
{
    vector<string>* vars = objClass->classVariables();
    for (vector<string>::iterator var = vars->begin(); var != vars->end(); var++) {
        (*m_localVariables)[*var] = Nil::nil();
    }
    
}

Object* DynamicObject::getVariable(const string& varName)
{
    Object* result;
    VariablesMap::iterator it = m_localVariables->find(varName);
    if (it != m_localVariables->end()) {
        result = it->second;
    } else {
        ExecEngine::execengineWarning(string("Trying to access to undefined variable. @nil returned. ") + this->m_class->className() + " " +  varName);
        result = Nil::nil();
    }
    return result;
}


/*
 *  String
 */
Class* String::ObjectClass()
{
    static Class* s_stringClass = NULL;
    
    if (!s_stringClass) { /* We are going to make Class */
        MethodsMap* methodsMap = new MethodsMap();
        (*methodsMap)[string("+@")] = new KernelMethod(string("+@"), String::kernel_String_concat);
        (*methodsMap)[string("append:@")] = new KernelMethod(string("append:@"), String::kernel_String_concat);
        (*methodsMap)[string("println")] = new KernelMethod(string("println"), String::kernel_String_println);
        (*methodsMap)[string("length")] = new KernelMethod(string("length"), String::kernel_String_length);
        
        MethodsMap* classMethodsMap = new MethodsMap();
        (*methodsMap)[string("println")] = new KernelMethod(string("println"), String::kernel_String_println);
        
        s_stringClass = new Class(string("String"), Object::ObjectClass(), methodsMap, classMethodsMap);
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
        ExecEngine::execengineError(string("Incorrect parameter"));
    
    return self;
}

Object* String::kernel_String_println(Object* self, const vector<Object*>&)
{
    String* str = dynamic_cast<String*>(self);
    
    if (str) 
        cout << str->m_string << "\n";
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
        
    return self;
}

Object* String::kernel_String_length(Object* self, const vector<Object*>&)
{
    String* str = dynamic_cast<String*>(self);
    
    if (str) 
        return new Integer(str->m_string.length());
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
        
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
