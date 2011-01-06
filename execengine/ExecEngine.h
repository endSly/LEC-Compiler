#ifndef execengine_ExecEngine_h
#define execengine_ExecEngine_h

#include <string>
#include "ast/AST.h"

namespace execengine {
    
    class ExecEngine {
    public:
        ExecEngine(ast::AST*);
        
        ~ExecEngine();
        
        void initializeEngine();
        
        int execute(const std::string&, const std::string&);
        
    private:
        
    };
    
} // namespace execengine

#endif // execengine_ExecEngine_h
