#ifndef execengine_kernelobjects_Object_h
#define execengine_kernelobjects_Object_h

#include <vector>
#include <string>

namespace execengine {
    
    using namespace std;
    
    class Class;
    
    class Object {
    public:
        Object() { }
        virtual Object* processMessage(const string&, const vector<Object*>&);
        virtual Class* objectClass()  { return Object::objectClass(); }
        virtual ~Object() { }
        virtual Object* getVariable(const string& varName) { return this; }
        
        bool isInstanceOf(Class*);
        
        static Class* ObjectClass();
        
        static Object* kernel_Object_class(Object*, const vector<Object*>&);
    };
    
} // namespace execengine

#endif // execengine_kernelobjects_Object_h
