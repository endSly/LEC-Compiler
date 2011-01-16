
/*
 * (c) 2011 Endika Gutierrez Salas (endSly@gmail.com)
 */

#include "AST.h"
#include "execengine/KernelObjects.h"
#include "execengine/ExecEngine.h"

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

const char* ROOT_CLASS_NAME = "Object";

using namespace execengine;

void AST::addClass(ClassDeclaration* classDecl) 
{
    m_classesMap->insert(std::pair<string, ClassDeclaration*>(classDecl->name(), classDecl));
}

ClassDeclaration* AST::findClass(const string& className)
{
    map<string, ClassDeclaration*>::iterator it = m_classesMap->find(className);
    return (it != m_classesMap->end()) 
            ? it->second 
            : NULL;
}

ClassDeclaration::ClassDeclaration(string className, string superName, vector<string>* vars, vector<MethodDeclaration*>* methods)
    : m_name(className)
    , m_superName(superName)
    , m_varsList(vars)
    , m_methodsList(methods)
{ }


MethodDeclaration::MethodDeclaration(string subjectObj, string methodSignature, vector<Expression*>& paramsVars, CodeBlock* code)
    : m_name(methodSignature)
    , m_subject(subjectObj)
    , m_methodCode(code)
{
    for (vector<Expression*>::iterator it = paramsVars.begin()
         ; it != paramsVars.end()
         ; it++) {
        
        Variable* paramVar = dynamic_cast<Variable*>(*it);
        m_paramsList.push_back(paramVar->name());
     }
}

/*
 *  Code Expressions
 */

Object* Value::evaluate(ExecContext* context) 
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

Object* Variable::evaluate(ExecContext* context) 
{
    return context->getVariable(m_varName);
}

Object* ReturnStatement::evaluate(ExecContext* context)
{
	//printf("%s\n", "[On ReturnStatement::evaluate]");
	return Nil::nil();
}
Object* CodeBlock::evaluate(ExecContext* context){
    return new Routine(this, context);
}

Object* CodeBlock::run(ExecContext* context)
{
    Object* result = Nil::nil();
    for (vector<Expression*>::iterator it = m_expressionList->begin()
         ; it != m_expressionList->end()
         ; it++) {
        
        Expression* expr = *it;
        result = expr->evaluate(context);

		if(expr->isReturningExpression())
			return result;
    }
    
    return result;
}

MessageSend::MessageSend(Expression* subject, MessagePredicate* predicate)
    : m_subject(subject)
    , m_methodParams(predicate->methodVars)
    , m_methodName(predicate->methodSignature)
{ }

Object* MessageSend::evaluate(ExecContext* context) 
{
    Object* subject = m_subject->evaluate(context);
    vector<Object*> params;

    for (vector<Expression*>::iterator param = m_methodParams.begin()
         ; param != m_methodParams.end()
         ; param++) {
        params.push_back((*param)->evaluate(context));
    }
         
    return subject->processMessage(m_methodName, params);
}

} // namespace ast 
