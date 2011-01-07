
#include "KernelObjects.h"

namespace execengine {

Object::Object(Class* objClass)
    : m_class(objClass)
{

}

Object* Object::processMessage(const string& method, const vector<Object*>& params)
{
    return Object::nil();
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
