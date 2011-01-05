
/*
 * (c) 2011 Endika Gutierrez Salas (endSly@gmail.com)
 */

#include "AST.h"

#include <iostream>

//extern int yyline;

ast::AST* syntaxTree;

#define DEBUG

void parserError(const char* msg) {
    std::cerr << "Error (Line:" /*<< yyline*/ << "); " << msg << '\n';
    exit(1);
}

namespace ast {

void AST::addClass(ClassDeclaration* classDecl) 
{
    m_classesMap->insert(std::pair<string, ClassDeclaration*>(classDecl->name(), classDecl));
}

ClassDeclaration* AST::findClass(string* className)
{
    map<string, ClassDeclaration*>::iterator it = m_classesMap->find(*className);
    
    return (it != m_classesMap->end()) 
            ? it->second 
            : NULL;
}

ClassDeclaration::ClassDeclaration(string* className, string* superName, vector<string*>* vars, vector<MethodDeclaration*>* methods)
    : m_name(*className)
    , m_varsList(vars)
{
#ifdef DEBUG
    std::cout << "ClassDefinition: " << className << " : " << superName;
#endif
    if (superName && !(m_superClass = syntaxTree->findClass(superName)))
        parserError("Undefined super class.");
    
    m_methodsMap = new map<string, MethodDeclaration*>();
    for (vector<MethodDeclaration*>::iterator it = methods->begin()
         ; it != methods->end()
         ; it++) {
        MethodDeclaration* methodDec = *it;
        m_methodsMap->insert(std::pair<string, MethodDeclaration*>(methodDec->signature(), methodDec));      
     }
     
#ifdef DEBUG
    std::cout << " Ok!\n";
#endif

}


MethodDeclaration::MethodDeclaration(string* subjectObj, string* methodSignature, vector<Expression*>* paramsVars, CodeBlock* code)
    : m_methodCode(code)
{
    
}

MessageSend::MessageSend(Expression* subject, MessagePredicate* predicate)
{
    
}



} // namespace ast 