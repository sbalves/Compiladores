%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "structures_p.h"

    int yylex(void);
    void yyerror (const char *s);
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
%token <token>  INT FLOAT32 BOOL STRING
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



//Sofia - Program; Declarations; VarDeclaration; VarSpec; Type; FuncDeclaration; Parameters; FuncBody; VarsAndStatements
//João - Statement; Expr; ParseArgs; FuncInvocation

%%

Program: PACKAGE ID SEMICOLON Declarations 

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
    | STRING
    ;

FuncDeclaration: FUNC ID LPAR ParametersOrNull RPAR TypeOrNull FuncBody

TypeOrNull: Type
          | /* EPSILON */ {$$ = NULL;}
          ;

Parameters: ID Type ParametersList

ParametersList: ParametersList COMMA ID Type
              | /* EPSILON */ {$$ = NULL;}
              ;

ParametersOrNull: Parameters
                | /* EPSILON */ {$$ = NULL;}
                ;

FuncBody:   LBRACE VarsAndStatements RBRACE

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

FuncInvocation: ID LPAR FuncInvocationList RPAR

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

NotMinusPlus: NOT | MINUS | PLUS;

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

int main() {
    if (yyparse()){
        printf("INCORRETO\n");
    }
    else{
        printf("CORRETO\n");
    }
    return 0;
}
