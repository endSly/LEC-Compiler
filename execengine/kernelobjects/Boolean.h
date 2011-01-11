#ifndef execengine_kernelobjects_Boolean_h
#define execengine_kernelobjects_Boolean_h

#include "kernelobjects/Object.h"

namespace execengine {
    
    class Boolean : public Object {
    public:
        static Boolean* True();
        static Boolean* False();
    
        static Class* ObjectClass();
        Class* objectClass() { return Boolean::ObjectClass(); }

        static Object* kernel_Boolean_true(Object*, const vector<Object*>&);
        static Object* kernel_Boolean_false(Object*, const vector<Object*>&);
        
        static Object* kernel_Boolean_ifTrue(Object*, const vector<Object*>&);
        static Object* kernel_Boolean_ifFalse(Object*, const vector<Object*>&);
        
        static Object* kernel_Boolean_not(Object*, const vector<Object*>&);
        static Object* kernel_Boolean_and(Object*, const vector<Object*>&);
        static Object* kernel_Boolean_or(Object*, const vector<Object*>&);
        static Object* kernel_Boolean_nand(Object*, const vector<Object*>&);
        static Object* kernel_Boolean_nor(Object*, const vector<Object*>&);
        static Object* kernel_Boolean_xor(Object*, const vector<Object*>&);
        
    private:
        Boolean(bool value) : m_value(value) { }
        bool m_value;
    };
    
} // namespace execengine

#endif // execengine_kernelobjects_Boolean_h
