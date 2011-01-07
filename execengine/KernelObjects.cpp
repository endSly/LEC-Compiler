
#include <iostream>
#include "KernelObjects.h"

namespace execengine {

void execengineWarning(const string& msg) 
{
    std::cout << "[ExecEngine Warning] " << msg << "\n";
}

Object::Object(Class* objClass)
    : m_class(objClass)
    , m_localVariables(new VariablesMap())
{

}

Object* Object::processMessage(const string& method, const vector<Object*>& params)
{
    return Object::nil();
}

Object* Object::getVariable(const string& varName)
{
    VariablesMap::iterator it = m_localVariables->find(varName);
    if (it != m_localVariables->end()) {
        /* We found the var */
        return it->second;
    } else {
        execengineWarning(string("Trying to access to undefined variable. @nil returned. ") + this->m_class->className() + " " +  varName);
    }
}
        
Object::~Object()
{
    
}

Object* String::processMessage(const string& method, const vector<Object*>& params)
{
    return Object::nil();
}
     
Object* Character::processMessage(const string& method, const vector<Object*>& params)
{
    return Object::nil();
}
     
Object* Integer::processMessage(const string& method, const vector<Object*>& params)
{
    return Object::nil();
}
     
Object* Decimal::processMessage(const string& method, const vector<Object*>& params)
{
    return Object::nil();
}
     
} // namespace execengine
