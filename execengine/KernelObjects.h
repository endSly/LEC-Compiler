
#ifndef execengine_KernelObjects_h
#define execengine_KernelObjects_h

#include <vector>
#include <map>
#include <string>

namespace execengine {
    
    using namespace std;
    
    class Class;
    class CodeBlock;
    class Object;
    
    class Expression;
    
    typedef map<string, CodeBlock*> MethodsMap;
    typedef map<string, Object*> VariablesMap;
    
    
    
    class Object {
    public:
        Object(Class*);
        static Object* nil() { return NULL; }
        
        virtual Object* processMessage(const string&, const vector<Object*>&);

        virtual ~Object();
 
    protected:
        Object() { }
        
    private:
        Class* m_class;
        unsigned int m_referencesCount;
        
        static VariablesMap* m_globalVariables;
        VariablesMap* m_localVariables;
        MethodsMap* m_localMethods;
    };
    
    class Class : public Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        Class* m_superClass;
        MethodsMap m_classMethods;
        
    };
    
    class Routine : public Object {
    public:
        virtual Object* processMessage(const string&, const vector<Object*>&);
    };
    
    class String : public Object {
    public:
        String(const std::string& str) : m_string(str) { }
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        std::string m_string; 
    };
    
    class Character : public Object {
    public:
        Character(unsigned int character) : m_character(character) { }
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        unsigned int m_character; 
    };
    
    class Boolean : public Object {
    public:
        static Boolean* True();
        static Boolean* False();
    
        virtual Object* processMessage(const string&, const vector<Object*>&);

    private:
        Boolean() { }
        Boolean(const Boolean&) { }
    
        bool m_value;
        
        static Boolean* m_false;
        static Boolean* m_true;
    };
    
    class Integer : public Object {
    public:
        Integer(long long value) : m_value(value) { }
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        long long m_value;
    };
    
    class Decimal : public Object {
    public:
        Decimal(double value) : m_value(value) { }
        virtual Object* processMessage(const string&, const vector<Object*>&);
        
    private:
        double m_value;
    };
    
}


#endif // execengine_KernelObjects_h
