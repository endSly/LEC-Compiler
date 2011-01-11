
#include "kernelobjects/Decimal.h"
#include "kernelobjects/Class.h"

namespace execengine {

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

}
