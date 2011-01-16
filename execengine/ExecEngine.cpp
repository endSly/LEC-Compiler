

#include <iostream>
#include <cstdlib>
#include "ast/AST.h"

#include "ExecEngine.h"
#include "KernelObjects.h"

namespace execengine {

void ExecEngine::execengineWarning(const string& msg) 
{
    std::cout << "[ExecEngine Warning] " << msg << "\n";
}

void ExecEngine::execengineError(const string& msg) 
{
    std::cerr << "[ExecEngine Error] " << msg << "\n";
    exit(1);
}

DynamicMethod::DynamicMethod(ast::MethodDeclaration* decl) 
    : Method(decl->name(), decl->parametersList())
    , m_code(decl->methodCode()) 
{ }

Object* DynamicMethod::run(Object* self, const vector<Object*>& params) 
{ 
    ExecContext context(self);
    
    // Store all variables into the context
    vector<string>::iterator nameIt = m_parametersName->begin();
    vector<Object*>::const_iterator varIt = params.begin();
    for (; nameIt != m_parametersName->end() && varIt != params.end()
         ; ++nameIt, ++varIt) {
         
        (*(context.contextVariables()))[*nameIt] = *varIt;
    }
    
    return m_code->run(&context); 
}

ExecEngine* ExecEngine::execEngine()
{
    static ExecEngine s_ee;
    return &s_ee;
}
        
void ExecEngine::initializeEngine(ast::AST* tree)
{
    // Insert all static Variables
    VariablesMap* globalVars = ExecContext::globalVariables();
    
    (*globalVars)[string("@nil")] = Nil::nil();
    
    (*globalVars)[string("@Object")] = Object::ObjectClass();
    (*globalVars)[string("@String")] = String::ObjectClass();
    (*globalVars)[string("@Character")] = Character::ObjectClass();
    (*globalVars)[string("@Boolean")] = Boolean::ObjectClass();
    (*globalVars)[string("@Integer")] = Integer::ObjectClass();
    (*globalVars)[string("@Decimal")] = Decimal::ObjectClass();
    (*globalVars)[string("@Routine")] = Routine::ObjectClass();
        
    // Insert Classe from AST
    map<string, ClassDeclaration*>* classesDeclaration = tree->classesMap();
    
    for (map<string, ClassDeclaration*>::iterator it = classesDeclaration->begin()
         ; it != classesDeclaration->end()
         ; it++) {
        string className = (*it).first;
        ClassDeclaration* classDecl = (*it).second;
        
        string classVar = "@" + className;
        
        MethodsMap* classMethods = new MethodsMap();
        MethodsMap* objectMethods = new MethodsMap();
        
        // Add all methods
        vector<MethodDeclaration*>* methodsDeclaration = classDecl->methodsList();
        for (vector<MethodDeclaration*>::iterator methodIt = methodsDeclaration->begin()
             ; methodIt != methodsDeclaration->end()
             ; methodIt++) {
            MethodDeclaration* methodDecl = *methodIt;
            
            if (methodDecl->subject() == classVar) { // We have class method
                classMethods->insert(pair<string, Method*>(methodDecl->name(), new DynamicMethod(methodDecl)));
                
            } else if (methodDecl->subject() == string("@self")) { // We have an object method
                objectMethods->insert(pair<string, Method*>(methodDecl->name(), new DynamicMethod(methodDecl)));
                
            } else {
                execengineError("Unknown subject " + methodDecl->subject());
            }
         }
        
        Class* newClass = new Class(className, Object::ObjectClass(), 
            objectMethods, classMethods, classDecl->variablesList());
        
        // Store class as global var
        (*globalVars)[classVar] = newClass;
    }
}
        
int ExecEngine::execute(const std::string& className, const std::string& method)
{
    Object* receiverClass = (*ExecContext::globalVariables())["@" + className];
    if (receiverClass) {
        Object* result = receiverClass->processMessage(method, vector<Object*>(0));
        return 0;
    } else {
        execengineError("Class:" + className + " not found\n");
    }
}

Object* ExecContext::getVariable(const string& varName) 
{
    // Find in context variable
    VariablesMap::iterator it = m_contextVariables.find(varName);
    if (it != m_contextVariables.end())
        return it->second;
    
    // Find in Object
    Object* variable = m_self->getObjectVariable(varName);
    if (variable)
        return variable;
    
    // Find in global variables
    it = globalVariables()->find(varName);
    if (it != globalVariables()->end())
        return it->second;
    
    // Undefined variable
    ExecEngine::execengineError("Trying to access to undefined variable: " + varName);
}

void ExecContext::setVariable(const string& varName, Object* value)
{
    // Find in context variable
    VariablesMap::iterator it = m_contextVariables.find(varName);
    if (it != m_contextVariables.end()) {
        it->second->releaseObject();
        it->second = value->retainObject();
        return;
    }
    
    // Find in Object
    if (m_self->setObjectVariable(varName, value)) {
        return;
    }
    
    // Find in global variables
    it = globalVariables()->find(varName);
    if (it != globalVariables()->end()) {
        it->second->releaseObject();
        it->second = value->retainObject();
        return;
    }
    
    // Undefined variable
    ExecEngine::execengineError("Trying to access to undefined variable: " + varName);
}

} // namespace execengine

