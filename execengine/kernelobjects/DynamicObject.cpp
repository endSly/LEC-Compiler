
#include "DynamicObject.h"

namespace execengine {
    
DynamicObject::DynamicObject(Class* objClass)
    : m_class(objClass)
    , m_localVariables(new VariablesMap())
{
    vector<string>* vars = objClass->classVariables();
    for (vector<string>::iterator var = vars->begin(); var != vars->end(); var++) {
        (*m_localVariables)[*var] = Nil::nil();
    }
    
}

Object* DynamicObject::getObjectVariable(const string& varName)
{
    VariablesMap::iterator it = m_localVariables->find(varName);
    if (it != m_localVariables->end()) 
        return it->second;

    return NULL;
}

bool DynamicObject::setObjectVariable(const string& varName, Object* value)
{
    VariablesMap::iterator it = m_localVariables->find(varName);
    if (it != m_localVariables->end()) {
        it->second->releaseObject();
        it->second = value->retainObject();
        return true;
    }

    return false;
}
    
} // namespace execengine
