#ifndef execengine_kernelobjects_Character_h
#define execengine_kernelobjects_Character_h

#include <string>
#include "Object.h"

namespace execengine {
    
    class Class;
    
    class Character : public Object {
    public:
        Character(unsigned int character) : m_character(character) { }
        
        static Class* ObjectClass();
        Class* objectClass() { return Character::ObjectClass(); }
        
    private:
        unsigned int m_character; 
    };
    
} // namespace execengine

#endif //  execengine_kernelobjects_Character_h
