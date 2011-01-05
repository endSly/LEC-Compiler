
#include <iostream>
#include "ast/AST.h"
#include "parser/parser.hpp"

extern int yyparse();
extern FILE* yyin;

void showHelp(const char* name) 
{
    std::cout << "Usage: " << name << " file\n";
    exit(1);
}

int main(int argc, char** args) 
{
    if (argc < 2)
        showHelp(args[0]);

    
    if (yyin = fopen(args[1], "r")) {
        yyparse();
        
        fclose(yyin);
        
    } else {
        showHelp(args[0]);
    }
    
    return 0;
}

