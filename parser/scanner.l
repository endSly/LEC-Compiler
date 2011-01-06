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

%option yylineno

identifier          [^ \t\n\{\}\(\)\;\@]+
varidentifier       \@[a-zA-Z0-9_]+
integer             ([\-\+])?[0-9]+
decimal             ([\-\+])?[0-9]*"."[0-9]+("e"([\-\+])?{integer}+)?
string              \"[^\"]*\"
character           \'.\'
commentIdent        \"\"\"
comment             {commentIdent}.*{commentIdent}

%%

[ \t\n]             { }
{comment}           { }

Import              { return T_IMPORT; }
Class               { return T_CLASS; }

\^                  { return T_INTERCALATE; }
\;                  { return T_SEMICOLON; }

\{                  { return T_OP_BRACE; }
\}                  { return T_CL_BRACE; }
\(                  { return T_OP_PARENT; }
\)                  { return T_CL_PARENT; }


{integer}           { SAVE_TOKEN; return T_INTEGER; }
{decimal}           { SAVE_TOKEN; return T_DECIMAL; }
{string}            { SAVE_TOKEN; return T_STRING; }
{character}         { SAVE_TOKEN; return T_CHARACTER; }

{varidentifier}     { SAVE_TOKEN; return T_VARIDENTIFIER; }
{identifier}        { SAVE_TOKEN; return T_IDENTIFIER; }

.                   printf("Sintax error at line:%i!\n", yylineno); yyterminate(); exit(1);

%%
