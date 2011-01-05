/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_VARIDENTIFIER = 258,
     T_IDENTIFIER = 259,
     T_STRING = 260,
     T_CHARACTER = 261,
     T_INTEGER = 262,
     T_DECIMAL = 263,
     T_CLASS = 264,
     T_IMPORT = 265,
     T_RET = 266,
     T_SEMICOLON = 267,
     T_COLON = 268,
     T_PIPE = 269,
     T_OP_BRACE = 270,
     T_CL_BRACE = 271,
     T_OP_PARENT = 272,
     T_CL_PARENT = 273
   };
#endif
/* Tokens.  */
#define T_VARIDENTIFIER 258
#define T_IDENTIFIER 259
#define T_STRING 260
#define T_CHARACTER 261
#define T_INTEGER 262
#define T_DECIMAL 263
#define T_CLASS 264
#define T_IMPORT 265
#define T_RET 266
#define T_SEMICOLON 267
#define T_COLON 268
#define T_PIPE 269
#define T_OP_BRACE 270
#define T_CL_BRACE 271
#define T_OP_PARENT 272
#define T_CL_PARENT 273




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 21 "parser.y"
{
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
/* Line 1529 of yacc.c.  */
#line 97 "parser.hpp"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

