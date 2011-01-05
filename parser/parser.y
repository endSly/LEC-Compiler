%{
    
/*
 * (c) 2011 Endika Gutierrez Salas (endSly@gmail.com)
 */
    
    #include <vector>
    #include <string>
    #include "ast/AST.h"

    extern int yylex();
    extern int yylineno;
    extern char* yyget_text();
	void yyerror(const char *s) { printf("Parser error (line %i): %s  Near: %s\n", yylineno, s, yyget_text()); exit(1); }
	
	extern ast::AST* syntaxTree;
	
	#define DEBUG(msg) printf("DEBUG: %s  yytext:%s yylineno:%i\n",msg,yyget_text(),yylineno)
%}

%union {
	ast::AST*                  ast;
	ast::ClassDeclaration*     classDeclaration;
	ast::MethodDeclaration*    methodDeclaration;
	ast::Expression*           expression;
	ast::MessageSend*          messegeSend;
	ast::MessagePredicate*     messagePredicate;
	std::string*               string;
	std::vector<std::string*>* stringList;
	std::vector<ast::MethodDeclaration*>*      methodsList;
}


/*
 *  Tokens
 */
/* Literal Identifiers */
%token <string> T_VARIDENTIFIER T_IDENTIFIER
%token <string> T_STRING
%token <string> T_CHARACTER
%token <string> T_INTEGER
%token <string> T_DECIMAL

/* Reserved Words */
%token T_CLASS
%token T_IMPORT
%token T_RET

%token T_SEMICOLON T_COLON T_PIPE

%token T_OP_BRACE T_CL_BRACE
%token T_OP_PARENT T_CL_PARENT

/*
 *  Types
 */
%type <ast>                 ast             classDeclList
%type <classDeclaration>    classDeclaration
%type <stringList>          classVarsDecl 
%type <methodsList>         classMethsDecl
%type <methodDeclaration>   methodDecl
%type <expression>          messageSend
%type <messagePredicate>    argMethodDecl   argMessPred         messagePred
%type <expression>          codeBlock       expressionList      expression

%start ast

%%

ast                 : classDeclList                     { $$ = $1; syntaxTree = $$; }
                    ;

classDeclList       : classDeclaration                  { $$ = new ast::AST(); $$->addClass($1); }
                    | classDeclList classDeclaration    { $$ = $1; $$->addClass($2); }
                    ;


classDeclaration    : T_CLASS T_IDENTIFIER 
                        T_PIPE classVarsDecl T_PIPE 
                        T_OP_BRACE classMethsDecl T_CL_BRACE
                    { $$ = new ast::ClassDeclaration($2, NULL, $4, $7); }
                    
                    | T_CLASS T_IDENTIFIER T_COLON T_IDENTIFIER 
                        T_PIPE classVarsDecl T_PIPE 
                        T_OP_BRACE classMethsDecl T_CL_BRACE
                    { $$ = new ast::ClassDeclaration($2, $4, $6, $9); }
                    ;

  classVarsDecl     :                               { $$ = new std::vector<std::string*>(); }
                    | T_VARIDENTIFIER               { $$ = new std::vector<std::string*>(); $$->push_back($1); }
                    | classVarsDecl T_VARIDENTIFIER  { $$ = $1; $$->push_back($2); }
                    ;
  
  classMethsDecl    : /* Nothing */                 { $$ = new std::vector<ast::MethodDeclaration*>(); }
                    | methodDecl classMethsDecl     { $$ = $2; $$->push_back($1); }
                    ;
                    
    methodDecl      : T_VARIDENTIFIER argMethodDecl codeBlock { $$ = new ast::MethodDeclaration($1, $2->methodSignature, $2->methodVars, (ast::CodeBlock*)$3); }
                    ;
                    
      argMethodDecl : T_IDENTIFIER                 { $$ = new ast::MessagePredicate($1); }
                    | T_IDENTIFIER T_VARIDENTIFIER { $$ = new ast::MessagePredicate($1); $$->methodVars->push_back(new ast::Object()/*$2*/); }
                    | T_IDENTIFIER T_VARIDENTIFIER argMethodDecl { $$ = $3; *($$->methodSignature) = (*$1 + ";" + *($$->methodSignature)); $$->methodVars->push_back(new ast::Object() /*$2*/); }
                    ;
                    

messageSend         : expression messagePred    { $$ = new ast::MessageSend($1, $2); }
                    ;
                
  messagePred       : T_IDENTIFIER      { $$ = new ast::MessagePredicate($1); }
                    | argMessPred       { $$ = $1; }
                    ;
                    
    argMessPred     : T_IDENTIFIER expression               { $$ = new ast::MessagePredicate($1); $$->methodVars->push_back($2); }
                    | argMessPred T_IDENTIFIER expression   { $$ = $1; $$->methodSignature->append(";" + *$2); $$->methodVars->push_back($3); }
                    ; 

codeBlock           : T_OP_BRACE expressionList T_CL_BRACE { $$ = $2; }
                    ;

expressionList      :                                           { $$ = new ast::CodeBlock(); }
                    | expression T_SEMICOLON                    { $$ = new ast::CodeBlock(); ((ast::CodeBlock*)$$)->addExpression($1); }
                    | expressionList expression T_SEMICOLON     { $$ = $1; ((ast::CodeBlock*)$$)->addExpression($2); }
                    ;

expression          : messageSend
                    | T_INTEGER     { $$ = new ast::Expression(); }
                    | T_DECIMAL     { $$ = new ast::Expression(); }
                    | T_CHARACTER   { $$ = new ast::Expression(); }
                    | T_STRING      { $$ = new ast::Expression(); }
                    | T_VARIDENTIFIER { $$ = new ast::Expression(); }
                    | codeBlock
                    | T_OP_PARENT expression T_CL_PARENT { $$ = $2; }
                    | T_RET expression { $$ = new ast::Expression(); }
                    ;

%%
