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
        
        static Object* kernel_Integer_add(Object*, const vector<Object*>&);
        static Object* kernel_Integer_sub(Object*, const vector<Object*>&);
        static Object* kernel_Integer_mul(Object*, const vector<Object*>&);
        static Object* kernel_Integer_fdiv(Object*, const vector<Object*>&);
        static Object* kernel_Integer_idiv(Object*, const vector<Object*>&);
        static Object* kernel_Integer_mod(Object*, const vector<Object*>&);
        
        static Object* kernel_Integer_equal(Object*, const vector<Object*>&);
        static Object* kernel_Integer_notEqual(Object*, const vector<Object*>&);
        static Object* kernel_Integer_greater(Object*, const vector<Object*>&);
        static Object* kernel_Integer_lower(Object*, const vector<Object*>&);
        static Object* kernel_Integer_greaterEq(Object*, const vector<Object*>&);
        static Object* kernel_Integer_lowerEq(Object*, const vector<Object*>&);
        
    private:
        long long m_value;
    };
    
        
} // namespace execengine

#endif // execengine_kernelobjects_Integer_h
