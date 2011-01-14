#ifndef execengine_kernelobjects_Integer_h
#define execengine_kernelobjects_Integer_h

#include "kernelobjects/Object.h"

namespace execengine {
    
    class Integer : public Object {
    public:
        Integer(long long value) : m_value(value) { }
        ~Integer() { }
        
        static Class* ObjectClass();
        Class* objectClass() { return Integer::ObjectClass(); }
        
        static Object* kernel_Integer_toString(Object*, const vector<Object*>&);
        
    private:
        long long m_value;
    };
    
        
} // namespace execengine

#endif // execengine_kernelobjects_Integer_h
