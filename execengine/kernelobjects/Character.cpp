
#include "Character.h"
#include "Class.h"

namespace execengine {

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

} // namespace execengine
