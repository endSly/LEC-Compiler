%{

    
/*
 * (c) 2011 Endika Gutierrez Salas (endSly@gmail.com)
 */
    #include <stdio.h>
    #include <cstdlib>
    #include <vector>
    #include <string>
    #include "ast/AST.h"


#ifdef _WIN32
extern "C"
{
    extern int yylex();
	extern int yyparse();
	int yylineno;
	char* yyget_text();
	void yyerror(const char *s) { printf("Parser error (line %i): %s  Near: %s\n", yylineno, s, yyget_text()); exit(1); }
}
	
#else 
    extern int yylex();
    extern int yyparse();
    extern int yylineno;
    extern char* yyget_text();
	void yyerror(const char *s) { printf("Parser error (line %i): %s  Near: %s\n", yylineno, s, yyget_text()); exit(1); }

#endif // _WIN32

	extern ast::AST* syntaxTree;
	
%}



%union {
	ast::AST*                  ast;
	ast::ClassDeclaration*     classDeclaration;
	ast::MethodDeclaration*    methodDeclaration;
	ast::ReturnStatement*      returnStatement;
	ast::Expression*           expression;
	ast::MessageSend*          messegeSend;
	ast::MessagePredicate*     messagePredicate;
	std::string*               string;
	std::vector<std::string>* stringList;
	std::vector<ast::MethodDeclaration*>*      methodsList;
}


/*
 *  Tokens
 */
/* Literal Identifiers */
%token <string> T_VARIDENTIFIER T_IDENTIFIER
%token <string> T_BINARY_OP_ADD T_BINARY_OP_MUL T_BINARY_OP_LOG
%token <string> T_STRING
%token <string> T_CHARACTER
%token <string> T_INTEGER
%token <string> T_DECIMAL

/* Reserved Words */
%token T_CLASS
%token T_IMPORT
%token T_RETURN
%token T_INTERCALATE
%token T_ASSIGNAMENT

%token T_SEMICOLON

%token T_OP_BRACE T_CL_BRACE
%token T_OP_PARENT T_CL_PARENT

/*
 *  Types
 */
%type <ast>                 ast classDeclList
%type <classDeclaration>    classDeclaration
%type <stringList>          classVarsDecl 
%type <methodsList>         classMethsDecl
%type <methodDeclaration>   methodDecl
%type <expression>          messageSend binaryMsgSend
%type <messagePredicate>    argMethodDecl messagePred
%type <expression>          codeBlock expressionList expression singleExpression assignament



%left T_BINARY_OP_LOG
%left T_BINARY_OP_ADD
%left T_BINARY_OP_MUL


%start ast

%%

ast                 : classDeclList                     { $$ = $1; syntaxTree = $$; }
                    ;

classDeclList       : classDeclaration                  { $$ = new ast::AST(); $$->addClass($1); }
                    | classDeclList classDeclaration    { $$ = $1; $$->addClass($2); }
                    ;


classDeclaration    : T_CLASS T_IDENTIFIER 
                        T_OP_PARENT classVarsDecl T_CL_PARENT 
                        T_OP_BRACE classMethsDecl T_CL_BRACE
                    { $$ = new ast::ClassDeclaration(*$2, std::string(ast::ROOT_CLASS_NAME), $4, $7); }
                    
                    | T_CLASS T_IDENTIFIER T_INTERCALATE T_IDENTIFIER 
                        T_OP_PARENT classVarsDecl T_CL_PARENT 
                        T_OP_BRACE classMethsDecl T_CL_BRACE
                    { $$ = new ast::ClassDeclaration(*$2, *$4, $6, $9); }
                    ;

  classVarsDecl     :                               { $$ = new std::vector<std::string>(); }
                    | T_VARIDENTIFIER classVarsDecl { $$ = $2; $$->push_back(*$1); }
                    ;
  
  classMethsDecl    : /* Nothing */                 { $$ = new std::vector<ast::MethodDeclaration*>(); }
                    | methodDecl classMethsDecl     { $$ = $2; $$->push_back($1); }
                    ;
                    
    methodDecl      : T_VARIDENTIFIER argMethodDecl codeBlock { $$ = new ast::MethodDeclaration(*$1, $2->methodSignature, $2->methodVars, (ast::CodeBlock*)$3); }
                    ;
                    
      argMethodDecl : T_IDENTIFIER                 { $$ = new ast::MessagePredicate(*$1); }
                    | T_IDENTIFIER T_VARIDENTIFIER { $$ = new ast::MessagePredicate(*$1 + "@"); $$->methodVars.insert($$->methodVars.begin(), new ast::Variable(*$2)); }
                    | T_IDENTIFIER T_VARIDENTIFIER argMethodDecl   { $$ = $3; $$->methodSignature.insert(0, *$1 + "@"); $$->methodVars.insert($$->methodVars.begin(), new ast::Variable(*$2)); }
                    
                    ;
                    

messageSend         : singleExpression messagePred    { $$ = new ast::MessageSend($1, $2); }
                    ;
                
  messagePred       : T_IDENTIFIER                                { $$ = new ast::MessagePredicate(*$1); }
                    | T_IDENTIFIER singleExpression               { $$ = new ast::MessagePredicate(*$1 + "@", $2); }
                    | T_IDENTIFIER singleExpression messagePred   { $$ = $3; $$->methodSignature.insert(0, *$1 + "@"); $$->methodVars.insert($$->methodVars.begin(), $2); }
                    ;


binaryMsgSend       : singleExpression T_BINARY_OP_LOG singleExpression  { $$ = new ast::MessageSend($1, new ast::MessagePredicate(*$2 + "@", $3)); }
                    | singleExpression T_BINARY_OP_ADD singleExpression  { $$ = new ast::MessageSend($1, new ast::MessagePredicate(*$2 + "@", $3)); }
                    | singleExpression T_BINARY_OP_MUL singleExpression  { $$ = new ast::MessageSend($1, new ast::MessagePredicate(*$2 + "@", $3)); }
                    ;

assignament         : T_VARIDENTIFIER T_ASSIGNAMENT expression  { $$ = new ast::Assignament(new ast::Variable(*$1), $3); }
                    ;

codeBlock           : T_OP_BRACE expressionList T_CL_BRACE { $$ = $2; }
                    ;

expressionList      :                                           { $$ = new ast::CodeBlock(); }
                    | expression                                { $$ = new ast::CodeBlock(); ((ast::CodeBlock*)$$)->addExpression($1) }
                    | expression T_SEMICOLON expressionList     { $$ = $3; ((ast::CodeBlock*)$$)->addExpression($1); }
                    ;
                    
expression          : messageSend 
                    | singleExpression
                    | assignament
                    | T_RETURN      { $$ = new ast::ReturnStatement(); }
                    ;

singleExpression    : T_INTEGER     { $$ = new ast::Value(*$1, ast::TypeInteger); }
                    | T_DECIMAL     { $$ = new ast::Value(*$1, ast::TypeDecimal); }
                    | T_CHARACTER   { $$ = new ast::Value(*$1, ast::TypeCharacter); }
                    | T_STRING      { $$ = new ast::Value(*$1, ast::TypeString); }
                    | T_VARIDENTIFIER { $$ = new ast::Variable(*$1); }
                    | codeBlock
                    | binaryMsgSend
                    | T_OP_PARENT expression T_CL_PARENT { $$ = $2; }
                    ;

%%
