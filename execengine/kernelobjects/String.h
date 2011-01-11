#ifndef execengine_kernelobjects_String_h
#define execengine_kernelobjects_String_h

#include <string>
#include "Object.h"

namespace execengine {
    
    class String : public Object {
    public:
        String(const std::string& str) : m_string(str) { }
        
        static Class* ObjectClass();
        Class* objectClass() { return String::ObjectClass(); }
        
        static Object* kernel_String_concat(Object*, const vector<Object*>&);
        static Object* kernel_String_println(Object*, const vector<Object*>&);
        static Object* kernel_String_length(Object*, const vector<Object*>&);
        
    private:
        std::string m_string; 
    };
    
} // namespace execengine

#endif // execengine_kernelobjects_String_h
