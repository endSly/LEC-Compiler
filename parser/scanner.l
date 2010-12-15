%{
    (/*
#include <string>
#include "node.h"
#include "parser.hpp"

#define TOKEN(t) (yylval.token = t)
#define SAVE_TOKEN { \
    yylval.string = new std::string(yytext, yyleng) \
}

extern "C" {
    int yywrap() { }
}

%}

identifier              [a-zA-Z_][a-zA-Z0-9_]*
integer                 [0-9]+
decimal                 [0-9]*\.[0-9]+


%%

[ \t\n]                 { ; /* Skip */ }
identifier 	            { SAVE_TOKEN; return TOKEN_IDENTIFIER; }
integer                 { SAVE_TOKEN; return TOKEN_INTEGER; }
decimal                 { SAVE_TOKEN; return TOKEN_DECIMAL; }


.						{ printf("Sintax error at line:%i!\n", yylineno); yyterminate(); exit(1); }

%%

