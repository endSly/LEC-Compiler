

#include "ast/AST.h"
#include "parser/parser.hpp"

extern int yyparse();

int main(int argc, char** args) 
{
    yyparse();
    
    return 0;
}

