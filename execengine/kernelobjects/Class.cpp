
#include "ExecEngine.h"
#include "kernelobjects/Class.h"

namespace execengine {

Class::Class(string className, Class* superClass, MethodsMap* objectMethods, MethodsMap* classMethods, vector<string>* vars) 
    : m_className(className)
    , m_superClass(superClass)
    , m_classMethods(classMethods)
    , m_objectMethods(objectMethods)
    , m_classVariables(vars)
{ }

Class::~Class() {
    delete m_classMethods;
    delete m_objectMethods;
    delete m_classVariables;
}

Class* Class::ObjectClass()
{
    static Class* s_objectClass = NULL;
    
    if (!s_objectClass) {
        MethodsMap* methodsMap = new MethodsMap();
        (*methodsMap)[string("className")] = new KernelMethod(string("className"), Class::kernel_Class_className);
        
        MethodsMap* classMethodsMap = new MethodsMap();
        
        s_objectClass = new Class(string("Class"), Object::ObjectClass(), methodsMap, classMethodsMap);
    }
    
    return s_objectClass;
}

Object* Class::processObjectMessage(Object* self, const string& method, const vector<Object*>& params)
{
#ifdef VERBOSE_DEBUG
	if(self && self->objectClass()) {
		Class * cl = self->objectClass();
		std::string str = cl->className();
		printf("[Calling method %s in an object of type %s]\n", method.c_str(), str.c_str());
	} else {
		printf("[Failed to call method]\n");
	}
#endif

    MethodsMap::iterator it = m_objectMethods->find(method);
    if (it != m_objectMethods->end()) {
        Method* method = it->second;
        return method->run(self, params);
    } 
    
    if (m_superClass)
        return m_superClass->processObjectMessage(self, method, params);
    

    ExecEngine::execengineWarning(string("Trying to access to undefined method. @nil returned. ") 
        + self->objectClass()->m_className + " " +  method);
    return Nil::nil();
}

Object* Class::processMessage(const string& method, const vector<Object*>& params)
{
    MethodsMap::iterator it = m_classMethods->find(method);
    if (it != m_classMethods->end()) {
        Method* method = it->second;
        return method->run(this, params);
    } 
    
    return this->objectClass()->processObjectMessage(this, method, params); 
    
    /*
    if (m_superClass)
        return m_superClass->processMessage(method, params);
    
    execengineWarning(string("Trying to access to undefined class method. @nil returned. ") + this->className() + " " +  method);
    return Nil::nil();
    */
    
}

Object* Class::kernel_Class_new(Object* self, const vector<Object*>& params)
{
    if (checkMethodParams(&params, NULL))
        return new DynamicObject((Class*) self);
    
    ExecEngine::execengineError(string("Incorrect Parameters!"));
}

Object* Class::kernel_Class_className(Object* self, const vector<Object*>& params)
{
    Class* cl = dynamic_cast<Class*>(self);
    
    if (cl)
        return new String(cl->m_className);
        
    ExecEngine::execengineError(string("Kernel class panic! ") + self->objectClass()->className());
}

} // namespace execengine
