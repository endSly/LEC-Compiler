
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
        
        string classVar = "@" + className;
        
        
    }
}
        
ExecEngine::~ExecEngine()
{
    
}
        
void ExecEngine::initializeEngine()
{
    
}
        
int ExecEngine::execute(const std::string& className, const std::string& method)
{
    
    
    return 0;
}

} // namespace execengine

