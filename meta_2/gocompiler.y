%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <assert.h>

    #include "structures.h"

    int yylex(void);
    void yyerror (const char *s);
    int yyparse();

    ast_node_t *Program; //root node of astree
%} 

%union{
    token_t* token;
    ast_node_t* node;
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


%%

Program: PACKAGE ID SEMICOLON Declarations                    {;}
        ;

Declarations: Declarations VarDeclaration SEMICOLON       {$$ = $1;}
            | Declarations FuncDeclaration SEMICOLON       {$$ = $1;}
            | /* EPSILON */ {$$ = NULL;}
            ;

VarDeclaration: VAR VarSpec       {;}
              | VAR LPAR VarSpec SEMICOLON RPAR       {;}
              ;

VarSpec: ID VarSpecList Type       {;}
        ;

VarSpecList: VarSpecList COMMA ID        {$$ = $1;}
           | /* EPSILON */ {$$ = NULL;}
           ;

Type: INT      {;}
    | FLOAT32  {;}    
    | BOOL     {;}   
    | STRING_L {;}      
    ;

FuncDeclaration: FUNC ID LPAR ParametersOrNull RPAR TypeOrNull FuncBody       {;}
            ;

TypeOrNull: Type       {;}
          | /* EPSILON */ {$$ = NULL;}
          ;

Parameters: ID Type ParametersList       {;}
        ;

ParametersList: ParametersList COMMA ID Type       {$$ = $1;}
              | /* EPSILON */ {$$ = NULL;}
              ;

ParametersOrNull: Parameters       {;}
                | /* EPSILON */ {$$ = NULL;}
                ;

FuncBody:   LBRACE VarsAndStatements RBRACE       {;}
        ;

VarsAndStatements:  VarsAndStatements VarsAndStatementsList SEMICOLON        {$$ = $1;}
                |   /* EPSILON */     {$$ = NULL;}
                ; 

VarsAndStatementsList:  VarDeclaration  {;}
                |       Statement       {;}
                |       /* EPSILON */   {$$ = NULL;}
                ;

Statement:  ID ASSIGN Expr                                              {;}
        |   LBRACE StatementList1 RBRACE                                {;}
        |   IF Expr LBRACE StatementList1 RBRACE StatementList          {;}
        |   FOR ExprOrNull LBRACE StatementList1 RBRACE                 {;}
        |   RETURN ExprOrNull                                           {;}
        |   FuncInvocation                                              {;}
        |   ParseArgs                                                   {;}
        |   PRINT LPAR Expr RPAR                                        {;}
        |   PRINT LPAR STRLIT RPAR                                      {;}
        |   error                                                       {;}
        ;


StatementList:  ELSE LBRACE StatementList1 RBRACE       {;}
            |   /* EPSILON */                           {$$ = NULL;}
            ;


StatementList1: StatementList1 Statement SEMICOLON       {$$ = $1;}
              | /* EPSILON */   {$$ = NULL;}
              ;

ParseArgs:  ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR       {;}
        |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR  {;}
        ;

FuncInvocation: ID LPAR FuncInvocationList RPAR       {;}
              | ID LPAR error RPAR {;}
            ;

FuncInvocationList: Expr CommaExpressionList       {;}
                |   /* EPSILON */ {$$ = NULL;}
                ;

CommaExpressionList: CommaExpressionList COMMA Expr       {$$ = $1;}
                |    /* EPSILON */         {$$ = NULL;}
                ;

Expr:   Expr MOD Expr           {$$ = $1;}
    |   Expr LT Expr            {$$ = $1;}
    |   Expr GT Expr            {$$ = $1;}
    |   Expr EQ Expr            {$$ = $1;}
    |   Expr NE Expr            {$$ = $1;}
    |   Expr LE Expr            {$$ = $1;}
    |   Expr GE Expr            {$$ = $1;}
    |   Expr OR Expr            {$$ = $1;}
    |   Expr AND Expr           {$$ = $1;}
    |   Expr PLUS Expr          {$$ = $1;}
    |   Expr MINUS Expr         {$$ = $1;}
    |   Expr STAR Expr          {$$ = $1;}
    |   Expr DIV Expr           {$$ = $1;}
    |   NOT Expr                {;}
    |   MINUS Expr              {;}
    |   PLUS Expr               {;}
    |   INTLIT                  {;}
    |   REALLIT                 {;}
    |   ID                      {;}
    |   FuncInvocation          {;}
    |   LPAR Expr RPAR          {;}
    |   LPAR error RPAR         {;}
    ;

ExprOrNull: Expr                {;}
        | /* EPSILON */         {;}
            ;

%%