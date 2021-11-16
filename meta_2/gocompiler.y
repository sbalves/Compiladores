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
    token_t* token;
    ast_node_t* node;
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
//%left COMMA
%right ASSIGN
%left OR 
%left AND
%left LT LE GT GE EQ NE
%left PLUS MINUS
%left STAR DIV MOD
%right NOT
//%left LPAR RPAR LSQ RSQ

%nonassoc ELSE IF


//Sofia - Program; Declarations; VarDeclaration; VarSpec; Type; FuncDeclaration; Parameters; FuncBody; VarsAndStatements
//João - Statement; Expr; ParseArgs; FuncInvocation

%%

Program: PACKAGE ID SEMICOLON Declarations                    {$$ = NULL;}
        ;

Declarations: Declarations VarDeclaration SEMICOLON       {$$ = NULL;}
            | Declarations FuncDeclaration SEMICOLON       {$$ = NULL;}
            | /* EPSILON */ {$$ = NULL;}
            ;

VarDeclaration: VAR VarSpec       {$$ = NULL;}
              | VAR LPAR VarSpec SEMICOLON RPAR       {$$ = NULL;}
              ;

VarSpec: ID VarSpecList Type       {$$ = NULL;}
        ;

VarSpecList: VarSpecList COMMA ID        {$$ = NULL;}
           | /* EPSILON */ {$$ = NULL;}
           ;

Type: INT      {$$ = NULL;}
    | FLOAT32  {$$ = NULL;}    
    | BOOL     {$$ = NULL;}   
    | STRING_L {$$ = NULL;}      
    ;

FuncDeclaration: FUNC ID LPAR ParametersOrNull RPAR TypeOrNull FuncBody       {$$ = NULL;}
            ;

TypeOrNull: Type       {$$ = NULL;}
          | /* EPSILON */ {$$ = NULL;}
          ;

Parameters: ID Type ParametersList       {$$ = NULL;}
        ;

ParametersList: ParametersList COMMA ID Type       {$$ = NULL;}
              | /* EPSILON */ {$$ = NULL;}
              ;

ParametersOrNull: Parameters       {$$ = NULL;}
                | /* EPSILON */ {$$ = NULL;}
                ;

FuncBody:   LBRACE VarsAndStatements RBRACE       {$$ = NULL;}
        ;

VarsAndStatements:  VarsAndStatements VarsAndStatementsList SEMICOLON        {$$ = NULL;}
                |   /* EPSILON */     {$$ = NULL;}
                ; 

VarsAndStatementsList:  VarDeclaration | Statement       {$$ = NULL;}
                    |   /* EPSILON */ {$$ = NULL;}
                    ;

Statement:  ID ASSIGN Expr       {$$ = NULL;}
        |   LBRACE StatementList1 RBRACE       {$$ = NULL;}
        |   IF Expr LBRACE StatementList1 RBRACE StatementList        {$$ = NULL;}
        |   FOR ExprOrNull LBRACE StatementList1 RBRACE        {$$ = NULL;}
        |   RETURN ExprOrNull        {$$ = NULL;}
        |   FuncInvocation {$$ = NULL;}
        |   ParseArgs        {$$ = NULL;}
        |   PRINT LPAR Expr RPAR       {$$ = NULL;}
        |   PRINT LPAR STRLIT RPAR       {$$ = NULL;}
        |   error SEMICOLON              {$$ = NULL;}
        ;


StatementList:  ELSE LBRACE StatementList1 RBRACE       {$$ = NULL;}
            |   /* EPSILON */ {$$ = NULL;}
            ;


StatementList1: StatementList1 Statement SEMICOLON       {$$ = NULL;}
              | /* EPSILON */   {$$ = NULL;}
              ;

ParseArgs:  ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR       {$$ = NULL;}
        |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR  {$$ = NULL;}
        ;

FuncInvocation: ID LPAR FuncInvocationList RPAR       {$$ = NULL;}
              | ID LPAR error RPAR {$$ = NULL;}
            ;

FuncInvocationList: Expr CommaExpressionList       {$$ = NULL;}
                |   /* EPSILON */ {$$ = NULL;}
                ;

CommaExpressionList: CommaExpressionList COMMA Expr       {$$ = NULL;}
                |    /* EPSILON */         {$$ = NULL;}
                ;

Expr:   Expr MOD Expr        {$$ = NULL;}
    |   Expr LT Expr        {$$ = NULL;}
    |   Expr GT Expr        {$$ = NULL;}
    |   Expr EQ Expr        {$$ = NULL;}
    |   Expr NE Expr        {$$ = NULL;}
    |   Expr LE Expr        {$$ = NULL;}
    |   Expr GE Expr        {$$ = NULL;}
    |   Expr OR Expr        {$$ = NULL;}
    |   Expr AND Expr        {$$ = NULL;}
    |   Expr PLUS Expr        {$$ = NULL;}
    |   Expr MINUS Expr        {$$ = NULL;}
    |   Expr STAR Expr        {$$ = NULL;}
    |   Expr DIV Expr        {$$ = NULL;}
    |   NOT Expr       {$$ = NULL;}
    |   MINUS Expr       {$$ = NULL;}
    |   PLUS Expr       {$$ = NULL;}
    |   INTLIT {$$ = NULL;}
    |   REALLIT {$$ = NULL;}
    |   ID {$$ = NULL;}
    |   FuncInvocation {$$ = NULL;}
    |   LPAR Expr RPAR       {$$ = NULL;}
    |   LPAR error RPAR      {$$ = NULL;}
    ;

ExprOrNull: Expr       {$$ = NULL;}
            | /* EPSILON */         {$$ = NULL;}
            ;

%%

/* FLAG WARNING - Criar flags!!!*/


