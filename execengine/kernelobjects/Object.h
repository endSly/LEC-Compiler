#ifndef execengine_kernelobjects_Object_h
#define execengine_kernelobjects_Object_h

#include <vector>
#include <string>

namespace execengine {
    
    using namespace std;
    
    class Class;
    
	
	//! Represents an Object in the language. Classes, variables, routines, etc all derive
	//! from this Object class.
	//! Methods might be called on an Object, and they provide some additional
	//! functionalities.
    class Object {
    public:

		//! Constructs an Object.
        Object() { }

		//! Calls a method on the object.
		//!
		//! @param method Method to call on the "this" object.
		//! @param params Parameters to pass to the method.
        virtual Object* processMessage(const string& method, const vector<Object*>& params);

		//! Returns the Class this object belongs to.
		//! A Class is also an object.
        virtual Class* objectClass()  { return Object::ObjectClass(); }

		//! Destroys the object.
		//!
        virtual ~Object() { }
       
		Object* getVariable(const string& varName) { return this; }
        
		//! Checks whether the "this" object is an instance of the
		//! specified Class (or if that Class is among its base classes
		//!
		//! @return True if "this" is of Class type otherClass. 
		//!			False otherwise.
        bool isInstanceOf(Class* otherClass);
        
		//! Creates the Class object of Object, if it hasn't been created already.
		//! If it has been created, it does nothing.
        static Class* ObjectClass();
        
		//! Returns the Class of the "this" object. Available to the language.
		//!
        static Object* kernel_Object_class(Object*, const vector<Object*>&);
		
		//! Returns the parent class of the "this" object. Available to the language.
		//!
        static Object* kernel_Object_superClass(Object*, const vector<Object*>&);

	
        static Object* kernel_Object_evaluate(Object*, const vector<Object*>&);
    };
    
} // namespace execengine

#endif // execengine_kernelobjects_Object_h
