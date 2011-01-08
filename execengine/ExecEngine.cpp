
#include <iostream>
#include "ast/AST.h"
#include "ExecEngine.h"

namespace execengine {

ExecEngine::ExecEngine(ast::AST* tree)
    : m_globalVars(new VariablesMap())
{
    map<string, ClassDeclaration*>* classesDeclaration = tree->classesMap();
    
    for (map<string, ClassDeclaration*>::iterator it = classesDeclaration->begin()
         ; it != classesDeclaration->end()
         ; it++) {
        string className = (*it).first;
        ClassDeclaration* classDecl = (*it).second;
        
        Class* newClass = new Class(className, NULL, NULL, NULL);
        string classVar = "@" + className;
        
        (*m_globalVars)[classVar] = newClass;
    }
}
        
ExecEngine::~ExecEngine()
{
    delete m_globalVars;
}
        
void ExecEngine::initializeEngine()
{
    
}
        
int ExecEngine::execute(const std::string& className, const std::string& method)
{
    Object* receiverClass = (*m_globalVars)["@" + className];
    if (receiverClass) {
        Object* result = receiverClass->processMessage(method, vector<Object*>());
        return (result == Nil::nil());
    } else {
        std::cout << "Class:" << className << " not found\n";
        return 1;
    }
    
    
    
}

} // namespace execengine

