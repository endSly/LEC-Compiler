
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
     
} // namespace execengine
