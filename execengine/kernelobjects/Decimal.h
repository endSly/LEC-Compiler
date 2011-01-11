#ifndef execengine_kernelobjects_Decimal_h
#define execengine_kernelobjects_Decimal_h

#include "kernelobjects/Object.h"

namespace execengine {
    
    class Decimal : public Object {
    public:
        Decimal(double value) : m_value(value) { }
        ~Decimal() { }
        
        static Class* ObjectClass();
        Class* objectClass() { return Decimal::ObjectClass(); }
        
    private:
        double m_value;
    };
        
} // namespace execengine

#endif // execengine_kernelobjects_Boolean_h
