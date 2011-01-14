#ifndef execengine_kernelobjects_Boolean_h
#define execengine_kernelobjects_Boolean_h

#include "kernelobjects/Object.h"

namespace execengine {
    
    class Boolean : public Object {
    public:
        inline static Boolean* True() { static Boolean s_true(true); return &s_true; }
        inline static Boolean* False() { static Boolean s_false(false); return &s_false; };
        
        inline static Boolean* boolean(bool b) { b ? Boolean::True() : Boolean::False(); }
        
        static Class* ObjectClass();
        Class* objectClass() { return Boolean::ObjectClass(); }

        static Object* kernel_Boolean_true(Object*, const vector<Object*>&);
        static Object* kernel_Boolean_false(Object*, const vector<Object*>&);
        
        static Object* kernel_Boolean_ifTrue(Object*, const vector<Object*>&);
        static Object* kernel_Boolean_ifTrue_else(Object*, const vector<Object*>&);
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
