

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
    std::cout << "[ExecEngine Error] " << msg << "\n";
    exit(1);
}

ExecEngine* ExecEngine::execEngine()
{
    static ExecEngine s_ee;
    return &s_ee;
}
        
void ExecEngine::initializeEngine(ast::AST* tree)
{
    // Insert all static Variables
    (*m_globalVars)[string("@nil")] = Nil::nil();
    
    (*m_globalVars)[string("@Object")] = Object::ObjectClass();
    (*m_globalVars)[string("@String")] = String::ObjectClass();
    (*m_globalVars)[string("@Character")] = Character::ObjectClass();
    (*m_globalVars)[string("@Boolean")] = Boolean::ObjectClass();
    (*m_globalVars)[string("@Integer")] = Object::ObjectClass();
    (*m_globalVars)[string("@Decimal")] = Object::ObjectClass();
        
        
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
         
        vector<string>* classVariables = classDecl->variablesList();
        
        Class* newClass = new Class(className, Object::ObjectClass(), objectMethods, classMethods, classVariables);
        
        // Store class as global var
        (*m_globalVars)[classVar] = newClass;
    }
}
        
int ExecEngine::execute(const std::string& className, const std::string& method)
{
    Object* receiverClass = (*m_globalVars)["@" + className];
    if (receiverClass) {
        Object* result = receiverClass->processMessage(method, vector<Object*>(0));
        cout << "--- Execution finished ---\n";
        return 0;
    } else {
        execengineError("Class:" + className + " not found\n");
    }
    
    
    
}

} // namespace execengine

