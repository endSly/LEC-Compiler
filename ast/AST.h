
/*
 * (c) 2011 Endika Gutierrez Salas (endSly@gmail.com)
 */

#ifndef AST_AST_h
#define AST_AST_h

#include <vector>
#include <map>
#include <string>
#include "execengine/KernelObjects.h"

using namespace std;
    
namespace ast {
    
    using namespace execengine;
    
    class ClassDeclaration;
    class MethodDeclaration;
    class CodeBlock;
    class MessageSend;
    class Expression;
    
    extern const char* ROOT_CLASS_NAME;
    
    class AST {
    public:
        AST() : m_classesMap(new map<string, ClassDeclaration*>) { }
        
        void addClass(ClassDeclaration*);
        ClassDeclaration* findClass(const string&);
        map<string, ClassDeclaration*>* classesMap() { return m_classesMap; }
        
    private:
        map<string, ClassDeclaration*>* m_classesMap;
    };
    
    class ClassDeclaration {
    public:
        ClassDeclaration(string, string, vector<string>*, vector<MethodDeclaration*>*);
    
        string name() { return m_name; }
    private:
        string m_name;
        string m_superName;
        map<string, MethodDeclaration*>* m_methodsMap;
        vector<string>* m_varsList;
    };
    
    class MethodDeclaration {
    public:
        MethodDeclaration(string, string, vector<Expression*>*, CodeBlock*);
     
        string signature() { return m_name; }
    private:
        string m_name;
        vector<string>* m_paramsList; 
        CodeBlock*  m_methodCode;  
    };
    
    struct MessagePredicate {
    public:
        MessagePredicate(const string& signature) : methodSignature(signature), methodVars(new vector<Expression*>()) { }
        
        string methodSignature;
        vector<Expression*>* methodVars;
    };
    
    /*
     *  Code Expressions
     */
    
    class Expression {
    public:
        void setReturningExpression(bool ret) { m_returningExpression = ret; }
        bool isReturningExpression() { return m_returningExpression; }
        virtual string toString() { return string("Abstract Expression"); }
        virtual ~Expression() { }
        
        virtual Object* evaluate(Object*) { return execengine::Nil::nil(); }
        
    protected:
        Expression() : m_returningExpression(false) { }
        bool m_returningExpression;
    };
    
    class CodeBlock : public Expression {
    public:
        CodeBlock() : m_expressionList(new vector<Expression*>()), m_blockVars(new vector<string>()) { }

        void addExpression(Expression* expression) { m_expressionList->push_back(expression); }
        string toString() { return string("CodeBlock"); }
        execengine::Object* evaluate(execengine::Object*);
        
        ~CodeBlock() { delete m_expressionList; }
        
    private:
        vector<Expression*>* m_expressionList;
        vector<string>* m_blockVars;
    };
    

    
    class MessageSend : public Expression {
    public:
        MessageSend(Expression*, MessagePredicate*);
        ~MessageSend() { }
        
        string toString() { return string("MsgSend"); }
        execengine::Object* evaluate(execengine::Object*);

    private:
        string m_methodName;
        vector<Expression*>* m_methodParams;
        Expression* m_subject;
    };
    
    
    enum ValueType { TypeInteger, TypeDecimal, TypeString, TypeCharacter };
    
    class Value : public Expression {
    public:
        Value(string val, ValueType type) : m_value(val), m_type(type) { }
        
        string toString() { return string("Value[") + m_value + "]"; }
        string value() { return m_value; }
        
        execengine::Object* evaluate(execengine::Object*);
        
    private:
        ValueType m_type;
        string m_value;
    };
    
    
    class Variable : public Expression {
    public:
        Variable(string name) : m_varName(name) { }
        
        string toString() { return m_varName; }
        string name() { return m_varName; }
        
        execengine::Object* evaluate(execengine::Object*);
        
    private:
        string m_varName;
    };

} // namespace ast

#endif // AST_AST_h


