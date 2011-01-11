
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include "KernelObjects.h"
#include "ExecEngine.h"

#include "ast/AST.h"

namespace execengine {

bool checkMethodParams(const vector<Object*>& params, ...)
{
    va_list args;
    va_start(args, params);
    
    int i = 0;
    const int lastParam = params.size();

    for (Class* type; (type = (Class*)va_arg(args, void*)); i++) {
        if ((i > lastParam) // Not enought params
            || (type != params[i]->objectClass())) { // Just pointer comparison
            return false; 
        }
    }

    if (i != lastParam)
        return false;
    
    return true;
}

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
    static Class* s_objectClass = NULL;
    
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
    if (checkMethodParams(params, String::ObjectClass(), NULL))
        ((String*) self)->m_string.append(((String*) params[0])->m_string);
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
    
    return self;
}

Object* String::kernel_String_println(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, NULL))
        cout << ((String*) self)->m_string << "\n";
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
        
    return self;
}

Object* String::kernel_String_length(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(params, NULL))
        return new Integer(((String*) self)->m_string.length());
    else
        ExecEngine::execengineError(string("Incorrect parameter"));
        
    return self;
}
    
/*
 *  Character
 */ 
Class* Character::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
    if (!s_objectClass) { /* We are going to make Class */
        MethodsMap* methodsMap = new MethodsMap();
        MethodsMap* classMethodsMap = new MethodsMap();
        
        s_objectClass = new Class(string("Character"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

/*
 *  Boolean
 */ 
Class* Boolean::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
    if (!s_objectClass) { /* We are going to make Class */
        MethodsMap* methodsMap = new MethodsMap();
        MethodsMap* classMethodsMap = new MethodsMap();
        
        s_objectClass = new Class(string("Boolean"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

/*
 *  Integer
 */ 
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

/*
 *  Decimal
 */
Class* Decimal::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
    if (!s_objectClass) { /* We are going to make Class */
        MethodsMap* methodsMap = new MethodsMap();
        MethodsMap* classMethodsMap = new MethodsMap();
        
        s_objectClass = new Class(string("Decimal"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}
     
} // namespace execengine
