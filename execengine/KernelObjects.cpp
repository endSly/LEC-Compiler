
#include "KernelObjects.h"

namespace execengine {

Object::Object(Class* objClass)
    : m_class(objClass)
{

}

Object* Object::processMessage(const string& method, const vector<Object*>& params)
{
    
}
        
Object::~Object()
{
    
}
     
} // namespace execengine
