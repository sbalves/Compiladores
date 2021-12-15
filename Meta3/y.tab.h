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
     SEMICOLON = 258,
     COMMA = 259,
     BLANKID = 260,
     ASSIGN = 261,
     STAR = 262,
     DIV = 263,
     MINUS = 264,
     PLUS = 265,
     EQ = 266,
     GE = 267,
     GT = 268,
     LE = 269,
     LT = 270,
     MOD = 271,
     NE = 272,
     NOT = 273,
     AND = 274,
     OR = 275,
     LBRACE = 276,
     RBRACE = 277,
     LPAR = 278,
     RPAR = 279,
     LSQ = 280,
     RSQ = 281,
     PACKAGE = 282,
     RETURN = 283,
     PRINT = 284,
     PARSEINT = 285,
     FUNC = 286,
     CMDARGS = 287,
     VAR = 288,
     IF = 289,
     ELSE = 290,
     FOR = 291,
     INT = 292,
     FLOAT32 = 293,
     BOOL = 294,
     STRING = 295,
     UNARY = 296,
     ID = 297,
     STRLIT = 298,
     INTLIT = 299,
     REALLIT = 300,
     RESERVED = 301
   };
#endif
/* Tokens.  */
#define SEMICOLON 258
#define COMMA 259
#define BLANKID 260
#define ASSIGN 261
#define STAR 262
#define DIV 263
#define MINUS 264
#define PLUS 265
#define EQ 266
#define GE 267
#define GT 268
#define LE 269
#define LT 270
#define MOD 271
#define NE 272
#define NOT 273
#define AND 274
#define OR 275
#define LBRACE 276
#define RBRACE 277
#define LPAR 278
#define RPAR 279
#define LSQ 280
#define RSQ 281
#define PACKAGE 282
#define RETURN 283
#define PRINT 284
#define PARSEINT 285
#define FUNC 286
#define CMDARGS 287
#define VAR 288
#define IF 289
#define ELSE 290
#define FOR 291
#define INT 292
#define FLOAT32 293
#define BOOL 294
#define STRING 295
#define UNARY 296
#define ID 297
#define STRLIT 298
#define INTLIT 299
#define REALLIT 300
#define RESERVED 301




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 31 "gocompiler.y"
{
        char* value;
        ast_node* node;   
}
/* Line 1529 of yacc.c.  */
#line 146 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

