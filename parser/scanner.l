%{

#ifndef HAVE_UNISTD_H
#define YY_NO_UNISTD_H
#endif

#include <string>
#include "ast/AST.h"

#ifdef _WIN32
 #include "win_parser.hpp"
#else
 #include "parser.hpp"
#endif 

#define TOKEN(t) (yylval.token = t)
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)


#ifdef _WIN32
extern "C"
{
    extern int yylex();
    
    /*
	This function is called whenever the lexer reaches EOF. Return 1 to indicate that
	we have not reset "yyin" to point to a new file.
	*/
    int yywrap()  { return 1; }

	char* yyget_text() { return yytext; }

	int yytest() { return 0; }
}

#else

extern "C"
{
    int yywrap() { return 1; }
}

#endif // _WIN32

using namespace ast;

%}

%option yylineno
%option never-interactive

identifierLimit     [^ \t\n\{\}\(\)\;\@\"\'0-9]
identifier          {identifierLimit}([^ \t\n\{\}\(\)\;\@]*{identifierLimit})?
binaryOpAdd         [\+\-]|"+="|"-=" 
binaryOpMul         [\*\/\%]|"//"|"*="|"/="
binaryOpLog         [\,\<\>]|and|or|nand|nor|xor|"=="|"!="|"<="|">="
varidentifier       \@[a-zA-Z0-9_]+
integer             ([\-\+])?[0-9]+
decimal             ([\-\+])?[0-9]*"."[0-9]+("e"{integer})?
string              \"[^\"]*\"
character           \'.\'
commentIdent        \"\"
comment             {commentIdent}.*{commentIdent}

%%

[ \t\n]             { }
{comment}           { }

Return				{ return T_RETURN; }
Import              { return T_IMPORT; }
Class               { return T_CLASS; }

\^                  { return T_INTERCALATE; }
\;                  { return T_SEMICOLON; }

\{                  { return T_OP_BRACE; }
\}                  { return T_CL_BRACE; }
\(                  { return T_OP_PARENT; }
\)                  { return T_CL_PARENT; }

{binaryOpAdd}       { SAVE_TOKEN; return T_BINARY_OP_ADD; }
{binaryOpMul}       { SAVE_TOKEN; return T_BINARY_OP_MUL; }
{binaryOpLog}       { SAVE_TOKEN; return T_BINARY_OP_LOG; }

{integer}           { SAVE_TOKEN; return T_INTEGER; }
{decimal}           { SAVE_TOKEN; return T_DECIMAL; }
{string}            { SAVE_TOKEN; return T_STRING; }
{character}         { SAVE_TOKEN; return T_CHARACTER; }

{varidentifier}     { SAVE_TOKEN; return T_VARIDENTIFIER; }
{identifier}        { SAVE_TOKEN; return T_IDENTIFIER; }

.                   printf("Syntax error at line:%i!\n", yylineno); yyterminate(); exit(1);

%%
