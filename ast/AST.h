
/*
 * (c) 2011 Endika Gutierrez Salas (endSly@gmail.com)
 */

#ifndef AST_AST_h
#define AST_AST_h

#include <vector>
#include <map>
#include <string>
#include "execengine/KernelObjects.h"
    
namespace ast {
    
    using namespace std;
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
        
        vector<string>* variablesList() { return m_varsList; }
        vector<MethodDeclaration*>* methodsList() { return m_methodsList; }
    
        string name() { return m_name; }
    private:
        string m_name;
        string m_superName;
        vector<MethodDeclaration*>* m_methodsList;
        vector<string>* m_varsList;
    };
    
    class MethodDeclaration {
    public:
        MethodDeclaration(string, string, vector<Expression*>&, CodeBlock*);
     
        string name() { return m_name; }
        string subject() { return m_subject; }
        vector<string>* parametersList() { return &m_paramsList; } 
        CodeBlock* methodCode() { return m_methodCode; }
        
    private:
        string m_name;
        string m_subject;
        vector<string> m_paramsList; 
        CodeBlock*  m_methodCode;  
    };
    
    struct MessagePredicate {
    public:
        MessagePredicate(const string& signature) : methodSignature(signature) { }
        
        string methodSignature;
        vector<Expression*> methodVars;
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
        Object* evaluate(Object*);
        
        Object* run(Object*, const vector<Object*>&);
        
        
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
        Object* evaluate(Object*);

    private:
        string m_methodName;
        vector<Expression*> m_methodParams;
        Expression* m_subject;
    };
    
    
    enum ValueType { TypeInteger, TypeDecimal, TypeString, TypeCharacter };
    
    class Value : public Expression {
    public:
        Value(string val, ValueType type) : m_value(val), m_type(type) { }
        
        string toString() { return string("Value[") + m_value + "]"; }
        string value() { return m_value; }
        
        Object* evaluate(Object*);
        
    private:
        ValueType m_type;
        string m_value;
    };
    
    
    class Variable : public Expression {
    public:
        Variable(string name) : m_varName(name) { }
        
        string toString() { return m_varName; }
        string name() { return m_varName; }
        
        Object* evaluate(Object*);
        
    private:
        string m_varName;
    };

} // namespace ast

#endif // AST_AST_h


