%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex(void);
    void yyerror (const char *s);
%} 


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
%type <node> VarSpec
%type <node> Type
%type <node> FuncDeclaration
%type <node> Parameters
%type <node> FuncBody
%type <node> VarsAndStatements
%type <node> Statement
%type <node> ParseArgs
%type <node> FuncInvocation
%type <node> Expr



//Sofia - Program; Declarations; VarDeclaration; VarSpec; Type; FuncDeclaration; Parameters; FuncBody; VarsAndStatements
//João - Statement; Expr; ParseArgs; FuncInvocation

%%

Program: PACKAGE ID SEMICOLON Declarations {}

Declarations: Declarations VarDeclaration SEMICOLON
            | Declarations FuncDeclaration SEMICOLON
            ;

VarDeclaration: VAR VarSpec
              | VAR LPAR VarSpec SEMICOLON RPAR
              ;

VarSpec: ID VarSpecList Type

VarSpecList: VarSpecList COMMA ID 
           | /* epsilon */
           ;

Type: INT
    | FLOAT32
    | BOOL
    | STRING
    ;

TypeOrNull: Type
          | /* epsilon */
          ;

FuncDeclaration: FUNC ID LPAR ParametersList RPAR TypeOrNull FuncBody

Parameters: ID Type ParametersList

ParametersList: ParametersList COMMA ID Type
              | /* epsilon */
              ;

FuncBody:   LBRACE VarsAndStatements RBRACE

VarsAndStatements:  VarsAndStatements VarsAndStatementsList SEMICOLON 
                |   /* epsilon */     {$$ = NULL;}
                ; 

VarsAndStatementsList:  VarDeclaration | Statement
                    |   /* EPSILON */ {$$ = NULL;}
                    ;

Statement:  ID ASSIGN Expr
        |   LBRACE StatementList1 RBRACE                                                   {$$ = statement($2);}
        |   IF Expr LBRACE Statement SEMICOLON RBRACE StatementList
        |   FOR ExpressionList LBRACE StatementList1 RBRACE
        |   RETURN ExpressionList
        |   FuncInvocation | ParseArgs                                                          {$$ = FuncInvocation($1) || ParseArgs();}    
        |   PRINT LPAR (Expr | STRLIT) RPAR
        ;

StatementList1: StatementList1 Statement SEMICOLON
              | /* epsilon */   {$$ = NULL;}
              ;

StatementList:  ELSE LBRACE Statement SEMICOLON RBRACE
            |   /* EPSILON */ {$$ = NULL;}
            ;


ParseArgs:  ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR

FuncInvocation: ID LPAR FuncInvocationList RPAR

FuncInvocationList: Expr CommaExpressionList
                |   /* EPSILON */ {$$ = NULL;}
                ;

CommaExpressionList: CommaExpressionList COMMA Expr
                |    /* EPSILON */         {$$ = NULL;}
                ;

Expr:   Expr (OR | AND) Expr
    |   Expr (LT | GT | EQ | NE | LE | GE) Expr 
    |   Expr (PLUS | MINUS | STAR | DIV | MOD) Expr   
    |   (NOT | MINUS | PLUS) Expr
    |   INTLIT | REALLIT | ID | FuncInvocation | LPAR Expr RPAR
    ;

ExpressionList: Expr
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

