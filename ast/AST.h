
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
    
    class AST {
    public:
        AST() : m_classesMap(new map<string, ClassDeclaration*>) { }
        
        void addClass(ClassDeclaration*);
        ClassDeclaration* findClass(string*);
        
    private:
        map<string, ClassDeclaration*>* m_classesMap;
    };
    
    class ClassDeclaration {
    public:
        ClassDeclaration(string*, string*, vector<string>*, vector<MethodDeclaration*>*);
    
        string name() { return m_name; }
    private:
        string m_name;
        ClassDeclaration* m_superClass;
        map<string, MethodDeclaration*>* m_methodsMap;
        vector<string>* m_varsList;
    };
    
    class MethodDeclaration {
    public:
        MethodDeclaration(string*, string*, vector<Expression*>*, CodeBlock*);
     
        string signature() { return m_name; }
    private:
        string m_name;
        vector<string*>* m_paramsList; 
        CodeBlock*  m_methodCode;  
    };
    
    struct MessagePredicate {
    public:
        MessagePredicate(string* signature) : methodSignature(new string(*signature)), methodVars(new vector<Expression*>()) { }
        
        string* methodSignature;
        vector<Expression*>* methodVars;
    };
    
    /*
     *  Code Expressions
     */
    
    class Expression {
    public:
        virtual string toString() { return string("Abstract Expression"); }
        virtual ~Expression() { }
        
        virtual Object* evaluate(Object*) { return execengine::Object::nil(); }
    };
    
    class CodeBlock : public Expression {
    public:
        CodeBlock() : m_expressionList(new vector<Expression*>()) { }
        ~CodeBlock() { delete m_expressionList; }
        
        void addExpression(Expression* expression) { m_expressionList->push_back(expression); }
        string toString() { return string("CodeBlock"); }
        virtual execengine::Object* evaluate(execengine::Object*);
        
    private:
        vector<Expression*>* m_expressionList;
    };
    

    
    class MessageSend : public Expression {
    public:
        MessageSend(Expression*, MessagePredicate*);
        ~MessageSend() { }
        
        string toString() { return string("MsgSend"); }
        virtual execengine::Object* evaluate(execengine::Object*);
    };
    
    
    enum ValueType { Integer, Decimal, String, Character };
    
    class Value : public Expression {
    public:
        Value(string val, ValueType type) : m_value(val), m_type(type) { }
        
        string toString() { return string("Value[") + m_value + "]"; }
        string value() { return m_value; }
        
        virtual execengine::Object* evaluate(execengine::Object*);
        
    private:
        ValueType m_type;
        string m_value;
    };
    
    
    class Variable : public Expression {
    public:
        Variable(string name) : m_varName(name) { }
        
        string toString() { return m_varName; }
        string name() { return m_varName; }
        
        virtual execengine::Object* evaluate(execengine::Object*);
        
    private:
        string m_varName;
    };
} // namespace ast

#endif // AST_AST_h


