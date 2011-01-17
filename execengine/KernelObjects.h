
#ifndef execengine_KernelObjects_h
#define execengine_KernelObjects_h

#include <vector>
#include <map>
#include <string>

#include "kernelobjects/Object.h"
#include "kernelobjects/Class.h"
#include "kernelobjects/DynamicObject.h"
#include "kernelobjects/String.h"
#include "kernelobjects/Character.h"
#include "kernelobjects/Integer.h"
#include "kernelobjects/Decimal.h"
#include "kernelobjects/Boolean.h"
#include "kernelobjects/Routine.h"


namespace execengine {
    
    using namespace std;
    

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
    bool checkMethodParams(const vector<Object*> * const, ...);
    
        
}


#endif // execengine_KernelObjects_h
