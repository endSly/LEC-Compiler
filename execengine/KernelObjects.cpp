
#include <iostream>
#include "KernelObjects.h"

#include "ast/AST.h"

namespace execengine {

void execengineWarning(const string& msg) 
{
    std::cout << "[ExecEngine Warning] " << msg << "\n";
}

/*
 * DynamicObject
 */
DynamicObject::DynamicObject(Class* objClass)
    : m_class(objClass)
{
    m_localVariables = new VariablesMap();
    
    vector<string>* vars = objClass->classVariables();
    for (vector<string>::iterator var = vars->begin(); var != vars->end(); var++) {
    }
    
}

Object* DynamicObject::processMessage(const string& method, const vector<Object*>& params)
{
    Object* result;
    MethodsMap* methodsMap = m_class->classMethods();
    MethodsMap::iterator it = methodsMap->find(method);
    if (it != methodsMap->end()) {
        /* We found the method */
        CodeBlock* method = it->second;
        result = method->evaluate(this);
    } else {
        execengineWarning(string("Trying to call to undefined method. @nil returned. ") + this->m_class->className() + " " +  method);
        result = Nil::nil();
    }
    
    return result;
}

Object* DynamicObject::getVariable(const string& varName)
{
    Object* result;
    VariablesMap::iterator it = m_localVariables->find(varName);
    if (it != m_localVariables->end()) {
        /* We found the var */
        result = it->second;
    } else {
        execengineWarning(string("Trying to access to undefined variable. @nil returned. ") + this->m_class->className() + " " +  varName);
        result = Nil::nil();
    }
    return result;
}

Object* KernelObject::getVariable(const string&) { return Nil::nil(); }

Object* KernelObject::processMessage(const string&, const vector<Object*>&) { return Nil::nil(); }

Object* String::processMessage(const string& method, const vector<Object*>& params)
{
    return Nil::nil();
}
     
Object* Character::processMessage(const string& method, const vector<Object*>& params)
{
    return Nil::nil();
}
     
Object* Integer::processMessage(const string& method, const vector<Object*>& params)
{
    return Nil::nil();
}
     
Object* Decimal::processMessage(const string& method, const vector<Object*>& params)
{
    return Nil::nil();
}
     
} // namespace execengine
