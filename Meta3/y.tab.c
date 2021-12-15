/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "gocompiler.y"

      /*  
        * Projeto de Compiladores 2021/2022
        * Meta 3
        * 2019218953 João Miguel Ferreira Castelo Branco Catré
        * 2019227240 Sofia Botelho Vieira Alves
      */ 
        #include "ast.h"
        #include "structures.h"
        #include "semantic_analysis.h"


        int yylex();
        int yyparse();
        void yyerror (const char *str);
        
        int flag_syntax_error=0;

        ast_node* varspec_aux = NULL;
        ast_node* varspec_aux_1 = NULL;
        ast_node* aux = NULL; 
        ast_node* aux2 = NULL;
        ast_node* program_root=NULL; //root node of astree

        // Nós superfluos -> while a correr os nos irmaos, tem que ter no minimo 2 nos irmaos. caso contrário, não printa
        table_t *tables_root = NULL;




/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 31 "gocompiler.y"
{
        char* value;
        ast_node* node;   
}
/* Line 193 of yacc.c.  */
#line 223 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 236 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   476

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  84
/* YYNRULES -- Number of states.  */
#define YYNSTATES  174

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    10,    11,    15,    18,    22,    25,
      28,    34,    37,    41,    45,    48,    50,    52,    54,    56,
      64,    71,    78,    84,    88,    91,    96,   100,   104,   108,
     112,   115,   116,   120,   123,   127,   132,   138,   146,   155,
     164,   174,   178,   183,   188,   194,   196,   199,   201,   203,
     208,   213,   215,   219,   222,   234,   243,   245,   249,   254,
     260,   265,   269,   272,   276,   280,   284,   288,   292,   296,
     300,   304,   308,   312,   316,   320,   324,   327,   330,   333,
     335,   337,   339,   341,   345
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    27,    42,     3,    49,    -1,    50,    -1,
      -1,    50,    51,     3,    -1,    51,     3,    -1,    50,    55,
       3,    -1,    55,     3,    -1,    33,    52,    -1,    33,    23,
      52,     3,    24,    -1,    42,    54,    -1,    42,    53,    54,
      -1,     4,    42,    53,    -1,     4,    42,    -1,    37,    -1,
      38,    -1,    39,    -1,    40,    -1,    31,    42,    23,    56,
      24,    54,    58,    -1,    31,    42,    23,    56,    24,    58,
      -1,    31,    42,    23,    24,    54,    58,    -1,    31,    42,
      23,    24,    58,    -1,    42,    54,    57,    -1,    42,    54,
      -1,     4,    42,    54,    57,    -1,     4,    42,    54,    -1,
      21,    59,    22,    -1,    59,    51,     3,    -1,    59,    60,
       3,    -1,    59,     3,    -1,    -1,    42,     6,    66,    -1,
      21,    22,    -1,    21,    61,    22,    -1,    34,    66,    21,
      22,    -1,    34,    66,    21,    61,    22,    -1,    34,    66,
      21,    22,    35,    21,    22,    -1,    34,    66,    21,    61,
      22,    35,    21,    22,    -1,    34,    66,    21,    22,    35,
      21,    61,    22,    -1,    34,    66,    21,    61,    22,    35,
      21,    61,    22,    -1,    36,    21,    22,    -1,    36,    21,
      61,    22,    -1,    36,    66,    21,    22,    -1,    36,    66,
      21,    61,    22,    -1,    28,    -1,    28,    66,    -1,    64,
      -1,    62,    -1,    29,    23,    66,    24,    -1,    29,    23,
      43,    24,    -1,     1,    -1,    61,    60,     3,    -1,    60,
       3,    -1,    42,     4,     5,     6,    30,    23,    32,    25,
      66,    26,    24,    -1,    42,     4,     5,     6,    30,    23,
       1,    24,    -1,    42,    -1,    63,    23,    24,    -1,    63,
      23,    66,    24,    -1,    63,    23,    66,    65,    24,    -1,
      63,    23,     1,    24,    -1,    65,     4,    66,    -1,     4,
      66,    -1,    66,    20,    66,    -1,    66,    19,    66,    -1,
      66,    15,    66,    -1,    66,    13,    66,    -1,    66,    11,
      66,    -1,    66,    17,    66,    -1,    66,    14,    66,    -1,
      66,    12,    66,    -1,    66,    10,    66,    -1,    66,     9,
      66,    -1,    66,     7,    66,    -1,    66,     8,    66,    -1,
      66,    16,    66,    -1,    18,    66,    -1,     9,    66,    -1,
      10,    66,    -1,    44,    -1,    45,    -1,    42,    -1,    64,
      -1,    23,    66,    24,    -1,    23,     1,    24,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    83,    83,    87,    88,    91,    92,    93,    94,    97,
      98,   101,   105,   115,   119,   126,   127,   128,   129,   132,
     141,   149,   158,   168,   175,   183,   188,   194,   197,   198,
     199,   200,   203,   208,   209,   221,   227,   234,   240,   247,
     255,   264,   267,   272,   276,   282,   283,   285,   287,   288,
     290,   293,   296,   297,   300,   305,   313,   316,   317,   318,
     319,   322,   323,   327,   328,   329,   330,   331,   332,   333,
     334,   335,   336,   337,   338,   339,   340,   341,   342,   343,
     344,   345,   346,   347,   348
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "COMMA", "BLANKID",
  "ASSIGN", "STAR", "DIV", "MINUS", "PLUS", "EQ", "GE", "GT", "LE", "LT",
  "MOD", "NE", "NOT", "AND", "OR", "LBRACE", "RBRACE", "LPAR", "RPAR",
  "LSQ", "RSQ", "PACKAGE", "RETURN", "PRINT", "PARSEINT", "FUNC",
  "CMDARGS", "VAR", "IF", "ELSE", "FOR", "INT", "FLOAT32", "BOOL",
  "STRING", "UNARY", "ID", "STRLIT", "INTLIT", "REALLIT", "RESERVED",
  "$accept", "Program", "Declarations", "Declarations2", "VarDeclaration",
  "VarSpec", "VarSpecList", "Type", "FuncDeclaration", "Parameters",
  "ParametersList", "FuncBody", "VarsAndStatements", "Statement",
  "StatementList", "ParseArgs", "FuncID", "FuncInvocation",
  "CommaExpressionList", "Expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    50,    51,
      51,    52,    52,    53,    53,    54,    54,    54,    54,    55,
      55,    55,    55,    56,    56,    57,    57,    58,    59,    59,
      59,    59,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    61,    61,    62,    62,    63,    64,    64,    64,
      64,    65,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     1,     0,     3,     2,     3,     2,     2,
       5,     2,     3,     3,     2,     1,     1,     1,     1,     7,
       6,     6,     5,     3,     2,     4,     3,     3,     3,     3,
       2,     0,     3,     2,     3,     4,     5,     7,     8,     8,
       9,     3,     4,     4,     5,     1,     2,     1,     1,     4,
       4,     1,     3,     2,    11,     8,     1,     3,     4,     5,
       4,     3,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     1,
       1,     1,     1,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,     0,     2,     3,
       0,     0,     0,     0,     0,     9,     0,     0,     6,     8,
       0,     0,     0,    15,    16,    17,    18,     0,    11,     5,
       7,     0,     0,     0,     0,    14,    12,    31,     0,    22,
      24,     0,    10,    13,     0,    21,     0,    23,     0,    20,
      51,    30,     0,    27,    45,     0,     0,     0,    56,     0,
       0,    48,     0,    47,     0,    19,    33,     0,     0,     0,
       0,     0,     0,    81,    79,    80,    82,    46,     0,     0,
       0,     0,     0,     0,    28,    29,     0,    26,    53,    34,
       0,    77,    78,    76,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    41,     0,     0,     0,    32,     0,    57,     0,
      25,    52,    84,    83,    73,    74,    72,    71,    67,    70,
      66,    69,    65,    75,    68,    64,    63,    50,    49,    35,
       0,    42,    43,     0,     0,    60,     0,    58,     0,     0,
      36,    44,     0,    62,     0,    59,     0,     0,     0,    61,
      37,     0,     0,     0,     0,    39,    38,     0,    55,     0,
      40,     0,     0,    54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,     9,    10,    15,    27,    28,    11,    33,
      47,    39,    44,    67,    68,    61,    62,    76,   148,    77
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int16 yypact[] =
{
     -23,   -28,    25,    24,   -72,   -20,   -14,    -5,   -72,   -20,
      54,    57,    35,    19,    12,   -72,    61,    87,   -72,   -72,
      44,   104,    67,   -72,   -72,   -72,   -72,    55,   -72,   -72,
     -72,    66,    55,    84,    86,   107,   -72,   -72,    92,   -72,
     110,    66,   -72,   -72,    99,   -72,    73,   -72,    92,   -72,
     -72,   -72,   115,   -72,   279,   101,   279,   269,    13,   126,
     128,   -72,   111,   -72,    55,   -72,   -72,   135,   125,   279,
     279,   279,    21,   116,   -72,   -72,   -72,   422,   262,   392,
     141,   407,   143,   279,   -72,   -72,    11,   110,   -72,   -72,
     137,   -72,   -72,   -72,   132,   356,   279,   279,   279,   279,
     279,   279,   279,   279,   279,   279,   279,   279,   279,   136,
     374,   151,   -72,   167,   170,   144,   422,   140,   -72,   318,
     -72,   -72,   -72,   -72,   -72,   -72,    81,    81,   460,   460,
     460,   460,   460,   -72,   460,   449,   436,   -72,   -72,   131,
     189,   -72,   -72,   193,   146,   -72,   279,   -72,    -1,   153,
     147,   -72,   155,   422,   279,   -72,   212,   160,     9,   422,
     -72,   215,   231,   162,   159,   -72,   -72,   241,   -72,   279,
     -72,   336,   173,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   -72,    -2,   187,   172,   -26,   196,   -72,
     121,   117,   -72,   -42,   -71,   -72,   -72,   -44,   -72,   -24
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -57
static const yytype_int16 yytable[] =
{
      63,    36,    60,   154,     1,    38,    40,    16,    63,   113,
     163,     6,   117,     7,     3,    48,    22,    82,    13,    83,
      69,    70,    94,   155,    63,     4,    90,     5,    12,    71,
      69,    70,    79,    81,    72,   118,    63,    14,    87,    71,
     140,   164,    59,   143,    72,    91,    92,    93,    95,    23,
      24,    25,    26,    73,   110,    74,    75,    18,    20,   116,
      19,    14,   119,    73,    29,    74,    75,    63,    31,    63,
      63,    90,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   161,    32,    37,    96,    97,
      30,   167,    23,    24,    25,    26,    63,   105,    90,    63,
      50,    90,    51,    23,    24,    25,    26,    34,    41,    35,
      42,    22,    63,    37,    46,    64,    50,    63,    63,    90,
      52,    53,   153,    63,    78,    90,    50,    54,    55,    84,
     159,    85,     7,    56,    86,    57,    52,    66,    88,   -56,
     121,    58,    50,    54,    55,   171,    52,    89,   115,    56,
     144,    57,    50,    54,    55,    45,   122,    58,    49,    56,
     137,    57,    52,   112,   145,    65,   149,    58,    50,    54,
      55,    50,    52,   139,   156,    56,   152,    57,   158,    54,
      55,   162,   157,    58,   169,    56,   168,    57,    52,   141,
      50,    52,   142,    58,    50,    54,    55,   173,    54,    55,
      21,    56,     0,    57,    56,    17,    57,    43,   120,    58,
      52,   150,    58,    50,    52,   151,    50,    54,    55,     0,
       0,    54,    55,    56,     0,    57,     0,    56,     0,    57,
       0,    58,    50,    52,   160,    58,    52,   165,     0,     0,
      54,    55,    50,    54,    55,     0,    56,     0,    57,    56,
       0,    57,    52,   166,    58,     0,     0,    58,     0,    54,
      55,     0,    52,   170,     0,    56,     0,    57,     0,    54,
      55,    69,    70,    58,     0,    56,     0,    57,    69,    70,
      71,     0,     0,    58,     0,    72,     0,    71,    69,    70,
      80,     0,    72,     0,     0,     0,     0,    71,     0,     0,
       0,     0,    72,     0,    73,   109,    74,    75,     0,     0,
       0,    73,     0,    74,    75,     0,     0,     0,     0,     0,
       0,    73,   146,    74,    75,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,     0,   107,   108,     0,
       0,     0,   147,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,   107,   108,     0,     0,     0,
       0,     0,   172,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,   107,   108,     0,     0,     0,
     123,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,     0,   107,   108,     0,     0,     0,   138,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
       0,   107,   108,   111,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,     0,   107,   108,   114,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
       0,   107,   108,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,     0,   107,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    96,    97,    98,
      99,     0,     0,     0,     0,     0,   105
};

static const yytype_int16 yycheck[] =
{
      44,    27,    44,     4,    27,    31,    32,     9,    52,    80,
       1,    31,     1,    33,    42,    41,     4,     4,    23,     6,
       9,    10,     1,    24,    68,     0,    68,     3,    42,    18,
       9,    10,    56,    57,    23,    24,    80,    42,    64,    18,
     111,    32,    44,   114,    23,    69,    70,    71,    72,    37,
      38,    39,    40,    42,    78,    44,    45,     3,    23,    83,
       3,    42,    86,    42,     3,    44,    45,   111,    24,   113,
     114,   113,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   156,    42,    21,     7,     8,
       3,   162,    37,    38,    39,    40,   140,    16,   140,   143,
       1,   143,     3,    37,    38,    39,    40,     3,    24,    42,
      24,     4,   156,    21,     4,    42,     1,   161,   162,   161,
      21,    22,   146,   167,    23,   167,     1,    28,    29,     3,
     154,     3,    33,    34,    23,    36,    21,    22,     3,    23,
       3,    42,     1,    28,    29,   169,    21,    22,     5,    34,
       6,    36,     1,    28,    29,    38,    24,    42,    41,    34,
      24,    36,    21,    22,    24,    48,    35,    42,     1,    28,
      29,     1,    21,    22,    21,    34,    30,    36,    23,    28,
      29,    21,    35,    42,    25,    34,    24,    36,    21,    22,
       1,    21,    22,    42,     1,    28,    29,    24,    28,    29,
      13,    34,    -1,    36,    34,     9,    36,    35,    87,    42,
      21,    22,    42,     1,    21,    22,     1,    28,    29,    -1,
      -1,    28,    29,    34,    -1,    36,    -1,    34,    -1,    36,
      -1,    42,     1,    21,    22,    42,    21,    22,    -1,    -1,
      28,    29,     1,    28,    29,    -1,    34,    -1,    36,    34,
      -1,    36,    21,    22,    42,    -1,    -1,    42,    -1,    28,
      29,    -1,    21,    22,    -1,    34,    -1,    36,    -1,    28,
      29,     9,    10,    42,    -1,    34,    -1,    36,     9,    10,
      18,    -1,    -1,    42,    -1,    23,    -1,    18,     9,    10,
      21,    -1,    23,    -1,    -1,    -1,    -1,    18,    -1,    -1,
      -1,    -1,    23,    -1,    42,    43,    44,    45,    -1,    -1,
      -1,    42,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    42,     4,    44,    45,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    19,    20,    -1,
      -1,    -1,    24,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      -1,    -1,    26,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    19,    20,    -1,    -1,    -1,
      24,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    19,    20,    -1,    -1,    -1,    24,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    19,    20,    21,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    19,    20,    21,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    19,    20,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    19,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    27,    48,    42,     0,     3,    31,    33,    49,    50,
      51,    55,    42,    23,    42,    52,    51,    55,     3,     3,
      23,    52,     4,    37,    38,    39,    40,    53,    54,     3,
       3,    24,    42,    56,     3,    42,    54,    21,    54,    58,
      54,    24,    24,    53,    59,    58,     4,    57,    54,    58,
       1,     3,    21,    22,    28,    29,    34,    36,    42,    51,
      60,    62,    63,    64,    42,    58,    22,    60,    61,     9,
      10,    18,    23,    42,    44,    45,    64,    66,    23,    66,
      21,    66,     4,     6,     3,     3,    23,    54,     3,    22,
      60,    66,    66,    66,     1,    66,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    19,    20,    43,
      66,    21,    22,    61,    21,     5,    66,     1,    24,    66,
      57,     3,    24,    24,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    24,    24,    22,
      61,    22,    22,    61,     6,    24,     4,    24,    65,    35,
      22,    22,    30,    66,     4,    24,    21,    35,    23,    66,
      22,    61,    21,     1,    32,    22,    22,    61,    24,    25,
      22,    66,    26,    24
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 83 "gocompiler.y"
    {program_root = newNode("Program", NULL);
                                                add_child(program_root, (yyvsp[(4) - (4)].node));}
    break;

  case 3:
#line 87 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 4:
#line 88 "gocompiler.y"
    {(yyval.node) = NULL;}
    break;

  case 5:
#line 91 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (3)].node); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));}
    break;

  case 6:
#line 92 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (2)].node);}
    break;

  case 7:
#line 93 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (3)].node); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));}
    break;

  case 8:
#line 94 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (2)].node);}
    break;

  case 9:
#line 97 "gocompiler.y"
    {(yyval.node) = (yyvsp[(2) - (2)].node);}
    break;

  case 10:
#line 98 "gocompiler.y"
    {(yyval.node) = (yyvsp[(3) - (5)].node);}
    break;

  case 11:
#line 101 "gocompiler.y"
    {(yyval.node) = newNode("VarDecl", NULL); add_child((yyval.node), (yyvsp[(2) - (2)].node));
                                add_sibling((yyvsp[(2) - (2)].node), newNode("Id", (yyvsp[(1) - (2)].value)));
                                }
    break;

  case 12:
#line 105 "gocompiler.y"
    {(yyval.node) = newNode("VarDecl", NULL); aux = newNode("Id", (yyvsp[(1) - (3)].value)); 
                                add_child((yyval.node), (yyvsp[(3) - (3)].node)); add_sibling((yyvsp[(3) - (3)].node), aux); add_sibling((yyval.node), (yyvsp[(2) - (3)].node));
                                varspec_aux = (yyval.node)->sibling;
                                while(varspec_aux != NULL && strcmp(varspec_aux->first_child->id, "notype") == 0){
                                        strcpy(varspec_aux->first_child->id, (yyvsp[(3) - (3)].node)->id);
                                        varspec_aux = varspec_aux->sibling;
                                }
                                }
    break;

  case 13:
#line 115 "gocompiler.y"
    {(yyval.node) = newNode("VarDecl", NULL); varspec_aux_1 = newNode("notype", NULL);
                                        add_sibling((yyval.node), (yyvsp[(3) - (3)].node)); add_child((yyval.node), varspec_aux_1); 
                                        add_sibling(varspec_aux_1, newNode("Id", (yyvsp[(2) - (3)].value)));
                                        }
    break;

  case 14:
#line 119 "gocompiler.y"
    {(yyval.node) = newNode("VarDecl", NULL);
                                        aux = newNode("notype", NULL);
                                        add_child((yyval.node), aux);
                                        add_sibling(aux, newNode("Id", (yyvsp[(2) - (2)].value))); 
                                        }
    break;

  case 15:
#line 126 "gocompiler.y"
    {(yyval.node) = newNode("Int", NULL);}
    break;

  case 16:
#line 127 "gocompiler.y"
    {(yyval.node) = newNode("Float32", NULL);}
    break;

  case 17:
#line 128 "gocompiler.y"
    {(yyval.node) = newNode("Bool", NULL);}
    break;

  case 18:
#line 129 "gocompiler.y"
    {(yyval.node) = newNode("String", NULL);}
    break;

  case 19:
#line 132 "gocompiler.y"
    {(yyval.node) = newNode("FuncDecl", NULL); 
                                                                aux = newNode("FuncHeader", NULL);
                                                                aux2 = newNode("Id", (yyvsp[(2) - (7)].value));
                                                                add_child((yyval.node), aux);                                                                                
                                                                add_sibling(aux, (yyvsp[(7) - (7)].node));
                                                                add_child(aux, aux2);
                                                                add_sibling((yyvsp[(6) - (7)].node), (yyvsp[(4) - (7)].node));
                                                                add_sibling(aux2, (yyvsp[(6) - (7)].node));
                                                                }
    break;

  case 20:
#line 141 "gocompiler.y"
    {(yyval.node) = newNode("FuncDecl", NULL);
                                                                aux = newNode("FuncHeader", NULL);
                                                                aux2 = newNode("Id", (yyvsp[(2) - (6)].value));
                                                                add_child((yyval.node), aux);
                                                                add_sibling(aux, (yyvsp[(6) - (6)].node));
                                                                add_child(aux, aux2);
                                                                add_sibling(aux2, (yyvsp[(4) - (6)].node));
                                                                }
    break;

  case 21:
#line 149 "gocompiler.y"
    {(yyval.node) = newNode("FuncDecl", NULL);
                                                                aux = newNode("FuncHeader", NULL);
                                                                add_child((yyval.node), aux);
                                                                aux2 = newNode("Id", (yyvsp[(2) - (6)].value));
                                                                add_sibling(aux, (yyvsp[(6) - (6)].node));
                                                                add_child(aux, aux2);
                                                                add_sibling(aux2, (yyvsp[(5) - (6)].node));
                                                                add_sibling((yyvsp[(5) - (6)].node), newNode("FuncParams", NULL));
                                                                }
    break;

  case 22:
#line 158 "gocompiler.y"
    {(yyval.node) = newNode("FuncDecl", NULL);
                                                                aux = newNode("FuncHeader", NULL);
                                                                aux2 = newNode("Id", (yyvsp[(2) - (5)].value));
                                                                add_child((yyval.node), aux);
                                                                add_child(aux, aux2);
                                                                add_sibling(aux2, newNode("FuncParams", NULL));
                                                                add_sibling(aux, (yyvsp[(5) - (5)].node));
                                                                }
    break;

  case 23:
#line 168 "gocompiler.y"
    {(yyval.node) = newNode("FuncParams", NULL);
                                                aux = newNode("ParamDecl", NULL);
                                                add_child((yyval.node), aux);        
                                                add_sibling(aux, (yyvsp[(3) - (3)].node));
                                                add_child(aux, (yyvsp[(2) - (3)].node));
                                                add_sibling((yyvsp[(2) - (3)].node), newNode("Id", (yyvsp[(1) - (3)].value)));
                                                }
    break;

  case 24:
#line 175 "gocompiler.y"
    {(yyval.node) = newNode("FuncParams", NULL);
                                                aux = newNode("ParamDecl", NULL);
                                                add_child((yyval.node), aux);        
                                                add_child(aux, (yyvsp[(2) - (2)].node));
                                                add_sibling((yyvsp[(2) - (2)].node), newNode("Id", (yyvsp[(1) - (2)].value)));
                                                }
    break;

  case 25:
#line 183 "gocompiler.y"
    {(yyval.node) = newNode("ParamDecl", NULL);
                                                        add_child((yyval.node), (yyvsp[(3) - (4)].node));
                                                        add_sibling((yyvsp[(3) - (4)].node), newNode("Id", (yyvsp[(2) - (4)].value)));
                                                        add_sibling((yyval.node), (yyvsp[(4) - (4)].node));
                                                        }
    break;

  case 26:
#line 188 "gocompiler.y"
    {(yyval.node) = newNode("ParamDecl", NULL);
                                                        add_child((yyval.node), (yyvsp[(3) - (3)].node));
                                                        add_sibling((yyvsp[(3) - (3)].node), newNode("Id", (yyvsp[(2) - (3)].value)));
                                                        }
    break;

  case 27:
#line 194 "gocompiler.y"
    {(yyval.node) = newNode("FuncBody", NULL); add_child((yyval.node), (yyvsp[(2) - (3)].node));}
    break;

  case 28:
#line 197 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (3)].node); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));}
    break;

  case 29:
#line 198 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (3)].node); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));}
    break;

  case 30:
#line 199 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (2)].node);}
    break;

  case 31:
#line 200 "gocompiler.y"
    {(yyval.node) = newNode("NULL", NULL);}
    break;

  case 32:
#line 203 "gocompiler.y"
    {(yyval.node) = newNode("Assign", NULL);
                                                                        aux = newNode("Id", (yyvsp[(1) - (3)].value));
                                                                        add_child((yyval.node), aux);
                                                                        add_sibling(aux, (yyvsp[(3) - (3)].node));
                                                                        }
    break;

  case 33:
#line 208 "gocompiler.y"
    {(yyval.node) = newNode("NULL", NULL);}
    break;

  case 34:
#line 209 "gocompiler.y"
    {aux = (yyvsp[(2) - (3)].node);
                                                                        int n = 0;
                                                                        while(aux != NULL){
                                                                                if(strcmp(aux->id, "NULL") != 0) n++;
                                                                                aux = aux->sibling;
                                                                        }
                                                                        if(n>=2){
                                                                                (yyval.node) = newNode("Block", NULL);
                                                                                add_child((yyval.node), (yyvsp[(2) - (3)].node));
                                                                        }
                                                                        else (yyval.node) = (yyvsp[(2) - (3)].node);
                                                                        }
    break;

  case 35:
#line 221 "gocompiler.y"
    {(yyval.node) = newNode("If", NULL );
                                                                        add_child((yyval.node), (yyvsp[(2) - (4)].node));
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling((yyvsp[(2) - (4)].node), aux);
                                                                        add_sibling(aux, newNode("Block", NULL));
                                                                        }
    break;

  case 36:
#line 227 "gocompiler.y"
    {(yyval.node) = newNode("If", NULL);
                                                                        add_child((yyval.node), (yyvsp[(2) - (5)].node));
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling((yyvsp[(2) - (5)].node), aux);
                                                                        add_child(aux, (yyvsp[(4) - (5)].node));
                                                                        add_sibling(aux, newNode("Block", NULL));
                                                                        }
    break;

  case 37:
#line 234 "gocompiler.y"
    {(yyval.node) = newNode("If", NULL);
                                                                        add_child((yyval.node), (yyvsp[(2) - (7)].node));
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling((yyvsp[(2) - (7)].node), aux);
                                                                        add_sibling(aux, newNode("Block", NULL));
                                                                        }
    break;

  case 38:
#line 240 "gocompiler.y"
    {(yyval.node) = newNode("If", NULL);
                                                                        add_child((yyval.node), (yyvsp[(2) - (8)].node));
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling((yyvsp[(2) - (8)].node), aux);
                                                                        add_child(aux, (yyvsp[(4) - (8)].node));
                                                                        add_sibling(aux, newNode("Block", NULL));
                                                                        }
    break;

  case 39:
#line 247 "gocompiler.y"
    {(yyval.node) = newNode("If", NULL);
                                                                        add_child((yyval.node), (yyvsp[(2) - (8)].node));
                                                                        aux=newNode("Block", NULL);
                                                                        aux2=newNode("Block", NULL);
                                                                        add_sibling((yyvsp[(2) - (8)].node), aux);
                                                                        add_sibling(aux, aux2);
                                                                        add_child(aux2, (yyvsp[(7) - (8)].node));
                                                                        }
    break;

  case 40:
#line 255 "gocompiler.y"
    {(yyval.node) = newNode("If", NULL);
                                                                                add_child((yyval.node), (yyvsp[(2) - (9)].node));
                                                                                aux=newNode("Block", NULL);
                                                                                aux2=newNode("Block", NULL);
                                                                                add_sibling((yyvsp[(2) - (9)].node), aux);
                                                                                add_child(aux, (yyvsp[(4) - (9)].node));
                                                                                add_sibling(aux, aux2);
                                                                                add_child(aux2, (yyvsp[(8) - (9)].node));
                                                                                }
    break;

  case 41:
#line 264 "gocompiler.y"
    {(yyval.node) = newNode("For", NULL);
                                                                        add_child((yyval.node), newNode("Block", NULL));
                                                                        }
    break;

  case 42:
#line 267 "gocompiler.y"
    {(yyval.node) = newNode("For", NULL);
                                                                        aux=newNode("Block", NULL);
                                                                        add_child((yyval.node), aux);
                                                                        add_child(aux, (yyvsp[(3) - (4)].node));
                                                                        }
    break;

  case 43:
#line 272 "gocompiler.y"
    {(yyval.node) = newNode("For", NULL);
                                                                        add_child((yyval.node), (yyvsp[(2) - (4)].node));
                                                                        add_sibling((yyvsp[(2) - (4)].node), newNode("Block", NULL));
                                                                        }
    break;

  case 44:
#line 276 "gocompiler.y"
    {(yyval.node) = newNode("For", NULL);
                                                                        add_child((yyval.node), (yyvsp[(2) - (5)].node));
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling((yyvsp[(2) - (5)].node), aux);
                                                                        add_child(aux, (yyvsp[(4) - (5)].node));
                                                                        }
    break;

  case 45:
#line 282 "gocompiler.y"
    {(yyval.node) = newNode("Return", NULL);}
    break;

  case 46:
#line 283 "gocompiler.y"
    {(yyval.node) = newNode("Return", NULL);
                                                                        add_child((yyval.node), (yyvsp[(2) - (2)].node));}
    break;

  case 47:
#line 285 "gocompiler.y"
    {(yyval.node) = newNode("Call", NULL);
                                                                        add_child((yyval.node), (yyvsp[(1) - (1)].node));}
    break;

  case 48:
#line 287 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 49:
#line 288 "gocompiler.y"
    {(yyval.node) = newNode("Print", NULL);
                                                                        add_child((yyval.node), (yyvsp[(3) - (4)].node));}
    break;

  case 50:
#line 290 "gocompiler.y"
    {(yyval.node) = newNode("Print", NULL);
                                                                        aux = newNode("StrLit", (yyvsp[(3) - (4)].value));
                                                                        add_child((yyval.node), aux);}
    break;

  case 51:
#line 293 "gocompiler.y"
    {(yyval.node) = newNode("Error", NULL); free_ast(program_root);}
    break;

  case 52:
#line 296 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (3)].node); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node));}
    break;

  case 53:
#line 297 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (2)].node);}
    break;

  case 54:
#line 300 "gocompiler.y"
    {(yyval.node) = newNode("ParseArgs", NULL);
                                                                                aux = newNode("Id", (yyvsp[(1) - (11)].value));
                                                                                add_child((yyval.node), aux);
                                                                                add_sibling(aux, (yyvsp[(9) - (11)].node));
                                                                                }
    break;

  case 55:
#line 305 "gocompiler.y"
    {(yyval.node) = newNode("ParseArgs", NULL);
                                                                                aux = newNode("Id", (yyvsp[(1) - (8)].value));
                                                                                add_child((yyval.node), aux);
                                                                                add_sibling(aux, newNode("Error", NULL));
                                                                                free_ast(program_root);
                                                                                }
    break;

  case 56:
#line 313 "gocompiler.y"
    {(yyval.node) = newNode("Id", (yyvsp[(1) - (1)].value));}
    break;

  case 57:
#line 316 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (3)].node);}
    break;

  case 58:
#line 317 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (4)].node); add_sibling((yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));}
    break;

  case 59:
#line 318 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (5)].node); add_sibling((yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node)); add_sibling((yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));}
    break;

  case 60:
#line 319 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (4)].node); add_sibling((yyvsp[(1) - (4)].node), newNode("Error", NULL)); free_ast(program_root);}
    break;

  case 61:
#line 322 "gocompiler.y"
    {(yyval.node) = (yyvsp[(1) - (3)].node); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 62:
#line 323 "gocompiler.y"
    {(yyval.node) = (yyvsp[(2) - (2)].node);}
    break;

  case 63:
#line 327 "gocompiler.y"
    {(yyval.node) = newNode("Or", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 64:
#line 328 "gocompiler.y"
    {(yyval.node) = newNode("And", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 65:
#line 329 "gocompiler.y"
    {(yyval.node) = newNode("Lt",NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 66:
#line 330 "gocompiler.y"
    {(yyval.node) = newNode("Gt",NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 67:
#line 331 "gocompiler.y"
    {(yyval.node) = newNode("Eq", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 68:
#line 332 "gocompiler.y"
    {(yyval.node) = newNode("Ne", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 69:
#line 333 "gocompiler.y"
    {(yyval.node) = newNode("Le", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 70:
#line 334 "gocompiler.y"
    {(yyval.node) = newNode("Ge", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 71:
#line 335 "gocompiler.y"
    {(yyval.node) = newNode("Add", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 72:
#line 336 "gocompiler.y"
    {(yyval.node) = newNode("Sub", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 73:
#line 337 "gocompiler.y"
    {(yyval.node) = newNode("Mul", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 74:
#line 338 "gocompiler.y"
    {(yyval.node) = newNode("Div", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 75:
#line 339 "gocompiler.y"
    {(yyval.node) = newNode("Mod", NULL); add_child((yyval.node), (yyvsp[(1) - (3)].node)); add_sibling((yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));}
    break;

  case 76:
#line 340 "gocompiler.y"
    {(yyval.node) = newNode("Not", NULL); add_child((yyval.node), (yyvsp[(2) - (2)].node));}
    break;

  case 77:
#line 341 "gocompiler.y"
    {(yyval.node) = newNode("Minus", NULL); add_child((yyval.node), (yyvsp[(2) - (2)].node));}
    break;

  case 78:
#line 342 "gocompiler.y"
    {(yyval.node) = newNode("Plus", NULL); add_child((yyval.node), (yyvsp[(2) - (2)].node));}
    break;

  case 79:
#line 343 "gocompiler.y"
    {(yyval.node) = newNode("IntLit", (yyvsp[(1) - (1)].value));}
    break;

  case 80:
#line 344 "gocompiler.y"
    {(yyval.node) = newNode("RealLit", (yyvsp[(1) - (1)].value));}
    break;

  case 81:
#line 345 "gocompiler.y"
    {(yyval.node) = newNode("Id", (yyvsp[(1) - (1)].value));}
    break;

  case 82:
#line 346 "gocompiler.y"
    {(yyval.node) = newNode("Call", NULL); add_child((yyval.node), (yyvsp[(1) - (1)].node));}
    break;

  case 83:
#line 347 "gocompiler.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);}
    break;

  case 84:
#line 348 "gocompiler.y"
    {(yyval.node) = newNode("Error", NULL); free_ast(program_root);}
    break;


/* Line 1267 of yacc.c.  */
#line 2206 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 350 "gocompiler.y"

