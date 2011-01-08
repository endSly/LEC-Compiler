#ifndef execengine_ExecEngine_h
#define execengine_ExecEngine_h

#include <string>
#include <map>

#include "KernelObjects.h"

namespace ast {
    class AST;
}

namespace execengine {
    
    using namespace std;
    
    class ExecEngine {
    public:
        ExecEngine(ast::AST*);
        
        ~ExecEngine();
        
        void initializeEngine();
        
        int execute(const std::string&, const std::string&);
        
    private:
        VariablesMap* m_globalVars;
    };
    
} // namespace execengine

#endif // execengine_ExecEngine_h
