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

identifier           [a-zA-Z_][a-zA-Z0-9_]*
integer              [0-9]+
decimal              [0-9]*\.[0-9]+

%%

[ \t\n]              ;
{identifier}         SAVE_TOKEN; return TOKEN_IDENTIFIER;
{integer}            SAVE_TOKEN; return TOKEN_INTEGER;
{decimal}            SAVE_TOKEN; return TOKEN_DECIMAL;
\".*\"               SAVE_TOKEN; return TOKEN_LITERAL_STRING;
\"\"[.\n]*\"\"       SAVE_TOKEN; return TOKEN_LITERAL_STRING;

func                 return TOKEN_FUNC;
if                   return TOKEN_IF;
for                  return TOKEN_FOR;
null                 return TOKEN_NULL;

int                  return TOKEN_INT;
float                return TOKEN_FLOAT;

"-"                  return TOKEN_OP_UN_MATH_NEGATIVE;
not                  return TOKEN_OP_UN_LOGICAL_NOT;
"~"                  return TOKEN_OP_UN_BIT_NOT;

"+"                  return TOKEN_OP_BI_MATH_ADD;
"-"                  return TOKEN_OP_BI_MATH_SUB;
"*"                  return TOKEN_OP_BI_MATH_MUL;
"/"                  return TOKEN_OP_BI_MATH_DIV;
mod                  return TOKEN_OP_BI_MATH_MOD;
div                  return TOKEN_OP_BI_MATH_INTDIV;

">"                  return TOKEN_OP_BI_LOGICAL_GREATER;
">="                 return TOKEN_OP_BI_LOGICAL_GREATER_EQ;
"<"                  return TOKEN_OP_BI_LOGICAL_LOWER;
"<="                 return TOKEN_OP_BI_LOGICAL_LOWER_EQ;
"=="                 return TOKEN_OP_BI_LOGICAL_EQUAL;
"!="                 return TOKEN_OP_BI_LOGICAL_NOT_EQUAL;

and                  return TOKEN_OP_BI_LOGICAL_AND;
or                   return TOKEN_OP_BI_LOGICAL_OR;
xor                  return TOKEN_OP_BI_LOGICAL_XOR;

"&"                  return TOKEN_OP_BI_BIT_AND;
"|"                  return TOKEN_OP_BI_BIT_OR;
"^"                  return TOKEN_OP_BI_BIT_XOR;
"!&"                 return TOKEN_OP_BI_BIT_NAND;
"!|"                 return TOKEN_OP_BI_BIT_NOR;
"!^"                 return TOKEN_OP_BI_BIT_NXOR;

"="                  return TOKEN_ASSIGNAMENT;
":="                 return TOKEN_DECLARATE_INIT;
"("                  return TOKEN_OP_PARENT;
")"                  return TOKEN_CL_PARENT;
"["                  return TOKEN_OP_BRACKET;
"]"                  return TOKEN_CL_BRACKET;
"{"                  return TOKEN_OP_BRACE;
"}"                  return TOKEN_CL_BRACE;

"."                  return TOKEN_DOT;
","                  return TOKEN_COMMA;
";"                  return TOKEN_SEMICOLON;
":"                  return TOKEN_COLON;

"\n"                 return TOKEN_CR;
"\t"                 return TOKEN_TAB;

.                    printf("Sintax error at line:%i!\n", yylineno); yyterminate(); exit(1);

%%

