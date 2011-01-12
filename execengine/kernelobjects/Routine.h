#ifndef execengine_kernelobjects_Routine_h
#define execengine_kernelobjects_Routine_h

#include "Object.h"

namespace ast {
    class CodeBlock;
}

namespace execengine {
    
    class Class;
    
    class Routine : public Object {
    public:
        Routine(ast::CodeBlock* code, Object* obj) : m_routineCode(code), m_runningObject(obj) { }
        ~Routine() { }
        
        static Class* ObjectClass();
        Class* objectClass() { return Routine::ObjectClass(); }
        
        static Object* kernel_Routine_evaluate(Object*, const vector<Object*>&);
        
    private:
        ast::CodeBlock* m_routineCode;
        Object* m_runningObject;
    };
    
} // namespace execengine

#endif // execengine_kernelobjects_Routine_h
