
#include <iostream>
#include <string>
#include "ast/AST.h"
#include "execengine/ExecEngine.h"
#include "parser/parser.hpp"

extern int yyparse();
extern FILE* yyin;

extern ast::AST* syntaxTree;

void showHelp(const char* name) 
{
    std::cout << "Usage: " << name << " filename.lec \"StartupClass\" \"startupMessage\"\n";
    exit(1);
}

int main(int argc, char** args) 
{
    if (argc < 4)
        showHelp(args[0]);
    
    /* Parse */
    if (yyin = fopen(args[1], "r")) {
        yyparse();
        
        fclose(yyin);
    } else {
        showHelp(args[0]);
    }
    
    /* Execute the AST */
    execengine::ExecEngine* ee = new execengine::ExecEngine(syntaxTree);
    
    ee->initializeEngine();
    
    int retVal = ee->execute(std::string(args[2]), std::string(args[3]));
    
    delete ee;
    
    return retVal;
}

