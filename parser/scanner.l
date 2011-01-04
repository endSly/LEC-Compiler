%{
    
#include <string>
#include "ast/AST.h"

#include "parser.hpp"

#define TOKEN(t) (yylval.token = t)
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)

extern "C" {
    int yywrap() { }
    
}

using namespace ast;

%}

varIdentifier       [a-zA-Z_][a-zA-Z0-9_]*
methodIdentifier    [^ \t\n\{\}\(\)\;]
integer             [0-9]+
decimal             [0-9]*\.[0-9]+(e{integer}+)?
string              \"[^\"]\"
character           \'.\'

%%

{varIdentifier}     { SAVE_TOKEN; return T_VARIDENTIFIER; }
{methodIdentifier}  { SAVE_TOKEN; return T_VARIDENTIFIER; }
{integer}           { SAVE_TOKEN; return T_INTEGER; }
{decimal}           { SAVE_TOKEN; return T_DECIMAL; }
{string}            { SAVE_TOKEN; return T_STRING; }
{character}         { SAVE_TOKEN; return T_CHARACTER; }

import              { return T_IMPORT; }
class               { return T_CLASS; }
return              { return T_RET; }

\:                  { return T_COLON; }
\;                  { return T_SEMICOLON; }

\{                  { return T_OP_BRACE; }
\}                  { return T_CL_BRACE; }
\[                  { return T_OP_BRACKET; }
\]                  { return T_CL_BRACKET; }
\(                  { return T_OP_PARENT; }
\)                  { return T_CL_PARENT; }

\|                  { return T_PIPE; }

[ \t\n]             { }

.                   printf("Sintax error at line:%i!\n", yylineno); yyterminate(); exit(1);

%%
