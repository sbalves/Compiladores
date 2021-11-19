/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    STRLIT = 259,
    INTLIT = 260,
    REALLIT = 261,
    SEMICOLON = 262,
    COMMA = 263,
    BLANKID = 264,
    ASSIGN = 265,
    STAR = 266,
    DIV = 267,
    MINUS = 268,
    PLUS = 269,
    MOD = 270,
    EQ = 271,
    GE = 272,
    GT = 273,
    LE = 274,
    LT = 275,
    NE = 276,
    LBRACE = 277,
    RBRACE = 278,
    LPAR = 279,
    RPAR = 280,
    LSQ = 281,
    RSQ = 282,
    NOT = 283,
    AND = 284,
    OR = 285,
    PACKAGE = 286,
    RETURN = 287,
    PRINT = 288,
    PARSEINT = 289,
    FUNC = 290,
    CMDARGS = 291,
    VAR = 292,
    IF = 293,
    ELSE = 294,
    FOR = 295,
    INT = 296,
    FLOAT32 = 297,
    BOOL = 298,
    STRING = 299,
    RESERVED = 300
  };
#endif
/* Tokens.  */
#define ID 258
#define STRLIT 259
#define INTLIT 260
#define REALLIT 261
#define SEMICOLON 262
#define COMMA 263
#define BLANKID 264
#define ASSIGN 265
#define STAR 266
#define DIV 267
#define MINUS 268
#define PLUS 269
#define MOD 270
#define EQ 271
#define GE 272
#define GT 273
#define LE 274
#define LT 275
#define NE 276
#define LBRACE 277
#define RBRACE 278
#define LPAR 279
#define RPAR 280
#define LSQ 281
#define RSQ 282
#define NOT 283
#define AND 284
#define OR 285
#define PACKAGE 286
#define RETURN 287
#define PRINT 288
#define PARSEINT 289
#define FUNC 290
#define CMDARGS 291
#define VAR 292
#define IF 293
#define ELSE 294
#define FOR 295
#define INT 296
#define FLOAT32 297
#define BOOL 298
#define STRING 299
#define RESERVED 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 10 "gocompiler.y"

    token_t* token;
    ast_node_t* node;

#line 152 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
