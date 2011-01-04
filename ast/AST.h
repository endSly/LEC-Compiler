
/*
 * (c) 2011 Endika Gutierrez Salas (endSly@gmail.com)
 */

#ifndef AST_AST_h
#define AST_AST_h

#include <vector>
#include <map>
#include <string>


namespace ast {
    
    using namespace std;
    
    class ClassDeclaration;
    class MethodDeclaration;
    class CodeBlock;
    class MessageSend;
    
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
        ClassDeclaration(string*, string*, vector<string*>*, vector<MethodDeclaration*>*);
    
        string name() { return m_name; }
    private:
        string m_name;
        ClassDeclaration* m_superClass;
        map<string, MethodDeclaration*>* m_methodsMap;
        vector<string*>* m_varsList;
    };
    
    class MethodDeclaration {
    public:
        MethodDeclaration(MessageSend*, CodeBlock*);
     
        string signature() { return m_name; }
    private:
        string m_name;
        vector<string*>* m_paramsList; 
        CodeBlock*  m_methodCode;  
    };
    
    class Expression {
    public:
        virtual ~Expression() { }
    };
    
    class CodeBlock : public Expression {
    public:
        CodeBlock() : m_expressionList(new vector<Expression*>()) { }
        
        ~CodeBlock() { delete m_expressionList; }
        
        void addExpression(Expression* expression) { m_expressionList->push_back(expression); }
        
    private:
        vector<Expression*>* m_expressionList;
    };
    
    struct MessagePredicate {
    public:
        MessagePredicate(string* signature) : methodSignature(new string(*signature)), methodVars(new vector<Expression*>()) { }
        
        string* methodSignature;
        vector<Expression*>* methodVars;
    };
    
    class MessageSend : public Expression {
    public:
        MessageSend(Expression*, MessagePredicate*);
        
        ~MessageSend() { }
    };
    
    class Object : public Expression {
        
    };
    
} // namespace ast

#endif // AST_AST_h


