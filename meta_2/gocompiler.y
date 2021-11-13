%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <assert.h>

    #include "structures_p.h"

    extern int yylex(void);
    extern void yyerror (const char *s);
    int yylex_destroy(void);              // free memory allocated by lex internal scanner

    ast_node_t *Program; //root node of astree
%} 

%union{
    token_t token;
    ast_node_t node;
    char* id;
    char string[10];
};

// Yacc tokens 
%token <token>  ID
%token <token>  STRLIT INTLIT REALLIT
%token <token>  SEMICOLON COMMA 
%token <token>  BLANKID
%token <token>  ASSIGN STAR DIV MINUS PLUS MOD
%token <token>  EQ GE GT LE LT NE
%token <token>  LBRACE RBRACE LPAR RPAR LSQ RSQ 
%token <token>  NOT AND OR
%token <token>  PACKAGE
%token <token>  RETURN PRINT PARSEINT FUNC CMDARGS VAR
%token <token>  IF ELSE FOR
%token <token>  INT FLOAT32 BOOL STRING_L
%token <token>  RESERVED

// Yacc nonterminal types - *alterar consoante a árvore*
%type <node> Program
%type <node> Declarations
%type <node> VarDeclaration
%type <node> VarSpec VarSpecList
%type <node> Type TypeOrNull
%type <node> FuncDeclaration CommaExpressionList
%type <node> Parameters ParametersList ParametersOrNull
%type <node> FuncBody
%type <node> VarsAndStatements VarsAndStatementsList
%type <node> Statement StatementList StatementList1
%type <node> ParseArgs
%type <node> FuncInvocation FuncInvocationList
%type <node> Expr ExprOrNull

//Precedências

%left COMMA
%right ASSIGN
%left OR 
%left AND
%left LT LE GT GE EQ NE
%left PLUS MINUS
%left STAR DIV MOD
%right NOT
%left LPAR RPAR LSQ RSQ

%nonassoc ELSE IF


//Sofia - Program; Declarations; VarDeclaration; VarSpec; Type; FuncDeclaration; Parameters; FuncBody; VarsAndStatements
//João - Statement; Expr; ParseArgs; FuncInvocation

%%

Program: PACKAGE ID SEMICOLON Declarations 
        ;

Declarations: Declarations VarDeclaration SEMICOLON
            | Declarations FuncDeclaration SEMICOLON
            | /* EPSILON */ {$$ = NULL;}
            ;

VarDeclaration: VAR VarSpec
              | VAR LPAR VarSpec SEMICOLON RPAR
              ;

VarSpec: ID VarSpecList Type

VarSpecList: VarSpecList COMMA ID 
           | /* EPSILON */ {$$ = NULL;}
           ;

Type: INT
    | FLOAT32
    | BOOL
    | STRING_L
    ;

FuncDeclaration: FUNC ID LPAR ParametersOrNull RPAR TypeOrNull FuncBody
            ;

TypeOrNull: Type
          | /* EPSILON */ {$$ = NULL;}
          ;

Parameters: ID Type ParametersList
        ;

ParametersList: ParametersList COMMA ID Type
              | /* EPSILON */ {$$ = NULL;}
              ;

ParametersOrNull: Parameters
                | /* EPSILON */ {$$ = NULL;}
                ;

FuncBody:   LBRACE VarsAndStatements RBRACE
        ;

VarsAndStatements:  VarsAndStatements VarsAndStatementsList SEMICOLON 
                |   /* EPSILON */     {$$ = NULL;}
                ; 

VarsAndStatementsList:  VarDeclaration | Statement
                    |   /* EPSILON */ {$$ = NULL;}
                    ;

Statement:  ID ASSIGN Expr
        |   LBRACE StatementList1 RBRACE
        |   IF Expr LBRACE StatementList1 RBRACE StatementList 
        |   FOR ExprOrNull LBRACE StatementList1 RBRACE 
        |   RETURN ExprOrNull 
        |   FuncInvocation | ParseArgs 
        |   PRINT LPAR ExprOrStril RPAR
        ;

ExprOrStril: Expr 
           | STRLIT
           ;


StatementList:  ELSE LBRACE StatementList1 RBRACE
            |   /* EPSILON */ {$$ = NULL;}
            ;


StatementList1: StatementList1 Statement SEMICOLON
              | /* EPSILON */   {$$ = NULL;}
              ;

ParseArgs:  ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR
        ;

FuncInvocation: ID LPAR FuncInvocationList RPAR
            ;

FuncInvocationList: Expr CommaExpressionList
                |   /* EPSILON */ {$$ = NULL;}
                ;

CommaExpressionList: CommaExpressionList COMMA Expr
                |    /* EPSILON */         {$$ = NULL;}
                ;

Expr:   Expr Operators Expr 
    |   NotMinusPlus Expr
    |   INTLIT | REALLIT | ID | FuncInvocation | LPAR Expr RPAR
    ;

NotMinusPlus: NOT | MINUS | PLUS
            ;

Operators: LT 
         | GT 
         | EQ 
         | NE 
         | LE 
         | GE
         | OR
         | AND
         | PLUS
         | MINUS
         | STAR 
         | DIV 
         | MOD
         ;

ExprOrNull: Expr
            | /* EPSILON */         {$$ = NULL;}
            ;

%%

/* FLAG WARNING */
/* yacc -Wcounterexamples mycalc_2.y */

void argparse(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-l")) {
             e1_flag = t_flag = e2_flag = false;
             l_flag = true;  
        } else if (!strcmp(argv[i], "-e1")){
            t_flag = l_flag = e2_flag = false;
            e1_flag = true;
        } else if (!strcmp(argv[i], "-e2")) {
            e1_flag = t_flag = l_flag = false;
            e2_flag = true;
        } else if (!strcmp(argv[i], "-t")) {
            l_flag = e2_flag = e1_flag = false;
            t_flag = true; 
        }
    }
}

int main(int argc, char *argv[]) {
    argparse(argc, argv);
    
    if (l_flag || e1_flag) {
        return yylex();
    } 
    
    if (e2_flag) {
        yyparse(); 
    } else if (t_flag) {
        yyparse();
        print_ast(program);  
    }

    free_ast(program);
    yylex_destroy();
    return 0;
} 
