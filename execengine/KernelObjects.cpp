
#include <iostream>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include "KernelObjects.h"
#include "ExecEngine.h"

#include "ast/AST.h"

namespace execengine {


//! Verifies that the parameters passed to a given method are of the
//! type that is expected.
//!
//! @param params Pointer to vector containing the parameters to verify.
//! Might not be null. It's only a pointer (instead of a reference)
//! due to vararg function contraints.
//!
//! @param varargs Variadic Arguments. Pointers to the expected types of the
//! previous parameters. The last argument passed must be NULL. The number
//! of arguments must hence be equal to the previous vector's size plus
//! one, for the terminating NULL argument.
//!
//! @return True if every parameter is of the expected type ( either
//! the exact same type or a subclass ).
//!	False otherwise, or if an error occurs.
bool checkMethodParams(const vector<Object*> * const params_ptr, ...)
{
	// If a null pointer to the vector is passed, just return false.
	if(!params_ptr)
		return false;

    va_list args;
    va_start(args, params_ptr);

	// Note: The function now takes a pointer rather than a reference. This is a
	// work-around to some interesting issue with vararg functions. (Which occurs in
	// Visual Studio, and possibly most compilers).
	// 
	// va_start is a macro which initialises va_list through a formula similar to the
	// following: args = &params + sizeof(params).
	// The result of this is theoretically the memory address of the next argument in
	// the stack. However, if params is a reference to a vector ( as it used to be ),
	// &params does not return the address of the pointer that is behind the reference.
	// Instead, it returns the address of the real "params" object.
	// Furthermore, sizeof(param) does not return the size of the pointer behind
	// the reference. Instead, it returns the size of the vector object, hence adding
	// a larger number than it should. The memory that gets read to subsequent calls
	// to va_arg is hence undefined.
	//
	// To avoid this, I have modified the function's signature to take a pointer instead.
	// Though not very pretty, there is no obvious alternative. 
 
	const vector<Object*> & params = *params_ptr;

    const int lastParam = params.size();

	int i = 0;

    // For each argument, until the NULL terminating vararg is reached.
    for ( Class * type = 0 ;  (type = (Class*)va_arg(args, void*)) != 0  ; i++) {

		// We have read more variadic arguments than we expected.
        if (i > lastParam)
            return false; 
        
        bool isInstance = false;
        
        // Check if it is instance or subclass
        for (Class* objectClass = (Class*) params[i]->objectClass()
             ; objectClass != NULL
             ; objectClass = objectClass->superClass()) {
            if (type == objectClass) { // Just pointer comparison 
                isInstance = true;
                break;
            }
        }
        
        if (!isInstance)
            return false;
    }

    if (i != lastParam)
        return false;
    
    return true;
}

/** DynamicObject */
DynamicObject::DynamicObject(Class* objClass)
    : m_class(objClass)
    , m_localVariables(new VariablesMap())
{
    vector<string>* vars = objClass->classVariables();
    for (vector<string>::iterator var = vars->begin(); var != vars->end(); var++) {
        (*m_localVariables)[*var] = Nil::nil();
    }
    
}

Object* DynamicObject::getObjectVariable(const string& varName)
{
    VariablesMap::iterator it = m_localVariables->find(varName);
    if (it != m_localVariables->end()) 
        return it->second;

    return NULL;
}

} // namespace execengine
