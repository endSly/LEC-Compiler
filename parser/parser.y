%{
	#include "ast/AST.h"
	
	extern int yylex();
	void yyerror(const char *s) { printf("Parser error: %s\n", s); exit(1); }
	
	using namespace ast;
	
	AST* syntaxTree;
%}

%union {
	ASTNode*               node;
	std::vector<ASTNode*>* nodeList;
	std::string*           string;
	int                    tokenId;
}


/*
 *  Tokens
 */
/* Literal Identifiers */
%token <string> TOKEN_IDENTIFIER
%token <string> TOKEN_INTEGER
%token <string> TOKEN_DECIMAL

/* Operators */
%token <tokenId> TOKEN_OP_UN_MATH_NEGATIVE
%token <tokenId> TOKEN_OP_UN_LOGICAL_NOT
%token <tokenId> TOKEN_OP_UN_BIT_NOT

%token <tokenId> TOKEN_OP_BI_MATH_ADD                   // +
%token <tokenId> TOKEN_OP_BI_MATH_SUB                   // -
%token <tokenId> TOKEN_OP_BI_MATH_MUL                   // *
%token <tokenId> TOKEN_OP_BI_MATH_DIV                   // /
%token <tokenId> TOKEN_OP_BI_MATH_MOD                   // mod
%token <tokenId> TOKEN_OP_BI_MATH_INTDIV                // div
%token <tokenId> TOKEN_OP_BI_LOGICAL_GREATER            // >
%token <tokenId> TOKEN_OP_BI_LOGICAL_GREATER_EQ         // >=
%token <tokenId> TOKEN_OP_BI_LOGICAL_LOWER              // <
%token <tokenId> TOKEN_OP_BI_LOGICAL_LOWER_EQ           // <=
%token <tokenId> TOKEN_OP_BI_LOGICAL_EQUAL              // ==
%token <tokenId> TOKEN_OP_BI_LOGICAL_NOT_EQUAL          // !=
%token <tokenId> TOKEN_OP_BI_LOGICAL_AND                // and
%token <tokenId> TOKEN_OP_BI_LOGICAL_OR                 // or
%token <tokenId> TOKEN_OP_BI_LOGICAL_XOR                // xor
%token <tokenId> TOKEN_OP_BI_BIT_AND                    // &
%token <tokenId> TOKEN_OP_BI_BIT_OR                     // |
%token <tokenId> TOKEN_OP_BI_BIT_XOR                    // ^
%token <tokenId> TOKEN_OP_BI_BIT_NAND                   // !&
%token <tokenId> TOKEN_OP_BI_BIT_NOR                    // !|
%token <tokenId> TOKEN_OP_BI_BIT_NXOR                   // !^

%token <tokenId> TOKEN_OP_TERNARY_CONDITIONAL

/* Reserved Words */
%token TOKEN_FUNC
%token TOKEN_IF
%token TOKEN_FOR
%token TOKEN_NULL

/* Types */
%token <tokenId> TOKEN_INT;
%token <tokenId> TOKEN_FLOAT;

/* Punctiation symbols */
%token TOKEN_ASSIGNAMENT        // =
%token TOKEN_DECLARATE_INIT     // :=
%token TOKEN_OP_PARENT
%token TOKEN_CL_PARENT
%token TOKEN_OP_BRACKET
%token TOKEN_CL_BRACKET
%token TOKEN_OP_BRACE
%token TOKEN_CL_BRACE

%token TOKEN_DOT
%token TOKEN_COMMA
%token TOKEN_DOT_COMMA
%token TOKEN_COLON

%token TOKEN_CR
%token TOKEN_TAB


/* 
 *  Precedence 
 */
%left TOKEN_OP_BI_MATH_MUL 
%left TOKEN_OP_BI_MATH_DIV
%left TOKEN_OP_BI_MATH_ADD

/*
 *  Types
 */
%type <node> module
%type <nodeList> stamentsList
%type <node> stament
%type <node> expresion
%type <node> functionDeclaration

%type <nodeList> parameters
%type <string> name

%type <tokenId> binaryOperator

%start module

%%


module : stamentsList { syntaxTree = new AST($1); }

stamentsList : stament { }
             | stamentsList stament { }

stament : expresion TOKEN_CR
        | expresion TOKEN_DOT_COMMA
        | functionDeclaration
        
expresion : assignation
          | functionCall
        
        
        
functionDeclaration : TOKEN_FUNC identifier functionParams { }
                    | TOKEN_FUNC identifier functionParams TOKEN_COLON functionParams { }

    functionParams : { $$ = NULL; }
                   | TOKEN_OP_PARENT TOKEN_CL_PARENT  { $$ = NULL; }
                   | TOKEN_OP_PARENT parameters TOKEN_CL_PARENT { $$ = $2}

        parameters : variableDeclaration { $$ = new std::vector<ASTNode*>(); $$->push_back($1); }
                   | parameters TOKEN_COMMA variableDeclaration { $1->push_back($3); }
        
		
variableDeclaration : type identifier { }
                    | type identifier TOKEN_ASSIGNAMENT expresion { }
                    | identifier TOKEN_DECLARATE_INIT expresion { }

		
type : TOKEN_INT | TOKEN_FLOAT

identifier : TOKEN_IDENTIFIER { $$ = new std::string($1); }
		
binaryMathOperator : TOKEN_OP_BI_MATH_ADD 
                   | TOKEN_OP_BI_MATH_SUB 
                   | TOKEN_OP_BI_MATH_MUL 
                   | TOKEN_OP_BI_MATH_DIV
                   | TOKEN_OP_BI_MATH_MOD
                   | TOKEN_OP_BI_MATH_INTDIV

%%
