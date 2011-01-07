
/*
 * (c) 2011 Endika Gutierrez Salas (endSly@gmail.com)
 */

#include "AST.h"
#include "execengine/KernelObjects.h"

#include <iostream>
#include <cstdlib>

ast::AST* syntaxTree;

extern int yylineno;

#define DEBUG

void parserError(const char* msg) {
    std::cerr << "Error (Line:" << yylineno << "); " << msg << '\n';
    exit(1);
}

namespace ast {

using namespace execengine;

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

ClassDeclaration::ClassDeclaration(string* className, string* superName, vector<string>* vars, vector<MethodDeclaration*>* methods)
    : m_name(*className)
    , m_varsList(vars)
{
#ifdef DEBUG
    std::cout << "ClassDef: " << *className << " : " << (superName ? *superName : "Object") << "\n";
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

}


MethodDeclaration::MethodDeclaration(string subjectObj, string methodSignature, vector<Expression*>* paramsVars, CodeBlock* code)
    : m_methodCode(code)
{
#ifdef DEBUG
    std::cout << "  MethodDef: " << subjectObj << " " << methodSignature << "\n";
#endif
}

MessageSend::MessageSend(Expression* subject, MessagePredicate* predicate)
{
#ifdef DEBUG
    std::cout << "    MsgSend:" << subject->toString() << " " << predicate->methodSignature;
    if (predicate->methodVars->size()) {
        std::cout << "\tParams: ";
        for (int i = 0; i < predicate->methodVars->size(); i++)
            std::cout << predicate->methodVars->at(i)->toString() << ", ";
    }
    std::cout << "\n";
#endif
}

/*
 *  Code Expressions
 */

Object* Value::evaluate(Object* self) 
{
    switch (m_type) {
    case TypeInteger:
        return new Integer((long long)atol(m_value.c_str()));
    case TypeDecimal:
        return new Decimal((double)atof(m_value.c_str()));
    case TypeString:
        return new String((std::string)m_value.substr(1, m_value.length() - 2));
    case TypeCharacter:
        return new Character((char)(m_value.c_str()[1]));
    }
}

Object* Variable::evaluate(Object* self) 
{
    return self->getVariable(m_varName);
}

Object* CodeBlock::evaluate(Object* self) 
{
    return Object::nil();
}

Object* MessageSend::evaluate(Object* self) 
{
    //return self->processMessage;
    return Object::nil();
}

} // namespace ast 
