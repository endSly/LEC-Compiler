
#include "Routine.h"
#include "Class.h"
#include "ast/AST.h"
#include "ExecEngine.h"

namespace execengine {

Class* Routine::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
	// Load the Routine class on-demand
    if (!s_objectClass) { /* We are going to make Class */
        MethodsMap* methodsMap = new MethodsMap();
        (*methodsMap)[string("evaluate")] = new KernelMethod(string("evaluate"), Routine::kernel_Routine_evaluate);
        
        MethodsMap* classMethodsMap = new MethodsMap();
        
        s_objectClass = new Class(string("Routine"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

Object* Routine::kernel_Routine_evaluate(Object* self, const vector<Object*>& params)
{
    ((Routine*) self)->m_routineCode->run(((Routine*) self)->m_runningObject, params);
	return self;
}

} // namespace execengine

