%{
        #include "structures.h"
        int yylex();
        int yyparse();
        void yyerror (const char *s);
        node* varspec_aux = NULL;
        node* varspec_aux_1 = NULL;
        node* aux = NULL;
        node* program_root=NULL; //root node of astree
        int flag_syntax_error=0;
%} 

%union{
        char* value ;
        struct node* node;   
};

// Yacc tokens 
%token SEMICOLON COMMA 
%token BLANKID
%token ASSIGN STAR DIV MINUS PLUS MOD
%token EQ GE GT LE LT NE
%token LBRACE RBRACE LPAR RPAR LSQ RSQ 
%token NOT AND OR
%token PACKAGE
%token RETURN PRINT PARSEINT FUNC CMDARGS VAR
%token IF ELSE FOR
%token INT FLOAT32 BOOL STRING

%token <value> ID
%token <value> STRLIT INTLIT REALLIT
%token <value> RESERVED

// Yacc nonterminal types - *alterar consoante a árvore*
%type <node> Program
%type <node> Declarations
%type <node> VarDeclaration
%type <node> VarSpec VarSpecList
%type <node> Type TypeOrNull
%type <node> FuncDeclaration CommaExpressionList
%type <node> Parameters ParametersList ParametersOrNull
%type <node> FuncBody
%type <node> VarsAndStatements
%type <node> Statement StatementList StatementList1
%type <node> ParseArgs
%type <node> FuncInvocation
%type <node> Expr

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

Program: PACKAGE ID SEMICOLON Declarations      {program_root = newNode("Program", NULL); add_child(program_root, $4);}
        ;

Declarations: Declarations VarDeclaration SEMICOLON       {$$ = $1; add_sibling($1, $2);}
            | Declarations FuncDeclaration SEMICOLON      {$$ = $1; add_sibling($1, $2);}
            | /* EPSILON */ {$$ = NULL;}
            ;

VarDeclaration: VAR VarSpec                           {$$ = $2;}
              | VAR LPAR VarSpec SEMICOLON RPAR       {$$ = $3;}
              ;
VarSpec: ID VarSpecList Type    {$$ = newNode("VarDecl", NULL); aux = newNode("Id", $1) ;add_child($$, aux); add_sibling(aux, $3); add_sibling($$, $2);
                                        varspec_aux = $$->sibling;
                                        while(varspec_aux != NULL && strcmp(varspec_aux->first_child->type, "notype") == 0){
                                                strcpy(varspec_aux->first_child->type, $3->type);
                                                varspec_aux = varspec_aux->sibling;
                                        }
                                }
        ;

VarSpecList: COMMA ID VarSpecList       {$$ = newNode("VarDecl", NULL); varspec_aux_1 = newNode("notype", NULL);add_sibling($$, $3); 
                                        add_child($$, varspec_aux_1); add_sibling(varspec_aux_1, newNode("Id", $2));
                                        }
           | /* EPSILON */ {$$ = NULL;}
           ;

Type: INT      {$$ = newNode("Int", NULL);} 
    | FLOAT32  {$$ = newNode("Float32", NULL);}    
    | BOOL     {$$ = newNode("Bool", NULL);}
    | STRING   {$$ = newNode("String", NULL);}      
    ;



FuncDeclaration: FUNC ID LPAR ParametersOrNull RPAR TypeOrNull FuncBody       {$$ = newNode("FuncDecl", NULL); aux = newNode("FuncHeader", NULL);
                                                                                add_child($$, aux);                                                                                
                                                                                add_sibling(aux, $7);
                                                                                add_child(aux, newNode("Id", $2));
                                                                                add_sibling($6, $4);
                                                                                add_sibling(newNode("Id", $2), $6);
                                                                                } 
            ;

TypeOrNull: Type                                {$$ = newNode("FuncParams", NULL);}
          | /* EPSILON */                       {$$ = NULL;}
          ;

ParametersOrNull: Parameters                    {$$ = newNode("FuncParams", NULL);}
                | /* EPSILON */                 {$$ = NULL;}
                ;



Parameters: ID Type ParametersList      {$$ = newNode("FuncParams", NULL);
                                                aux = newNode("ParamDecl", NULL);
                                                add_child($$, aux);        
                                                add_sibling(aux, $3);
                                                add_child(aux, $2);
                                                add_sibling($2, newNode("Id", $1));
                                        }
        ;

ParametersList: COMMA ID Type ParametersList            {$$ = newNode("ParamDecl", NULL);
                                                                add_child($$, $3);
                                                                add_sibling($3, newNode("Id", $2));
                                                                add_sibling($$, $4);
                                                        }
                | /* EPSILON */                         {$$ = NULL;}
              ;

FuncBody:   LBRACE VarsAndStatements RBRACE       {;}
        ;

VarsAndStatements:  VarsAndStatements VarDeclaration SEMICOLON  {$$=$1; add_sibling($1, $2);}
                 |  VarsAndStatements Statement SEMICOLON       {$$=$1; add_sibling($1, $2);}
                 |  VarsAndStatements SEMICOLON                 {$1=$1;}
                 |  /*Epsilon = NULL*/                          {$$=newNode("NULL", NULL);}
                 ;

Statement:  ID ASSIGN Expr                                              {$$ = newNode("Assign",NULL); 
                                                                        aux = newNode("Id", $1); 
                                                                        add_child($$, aux); 
                                                                        add_sibling(aux,$3);}

        |   LBRACE StatementList1 RBRACE                                {$$ = $2;}

        |   IF Expr LBRACE StatementList1 RBRACE StatementList          {$$ = newNode("If",NULL); 
                                                                        add_child($$, $2);
                                                                        aux = newNode("Block", NULL);
                                                                        add_sibling($2,aux);
                                                                        add_child(aux,$6);}

        |   FOR Expr LBRACE StatementList1 RBRACE                       {$$ = newNode("For",NULL); 
                                                                        add_child($$, $2);
                                                                        aux = newNode("Block", NULL);
                                                                        add_sibling($2,aux);
                                                                        add_child(aux,$4);}

        |   FOR LBRACE StatementList1 RBRACE                            {$$ = newNode("For",NULL); 
                                                                        aux = newNode("Block", NULL); 
                                                                        add_child($$, aux);
                                                                        add_child(aux,$3);}

        |   RETURN                                                      {$$ = newNode("Return", NULL);}
        |   RETURN Expr                                                 {$$ = newNode("Return", NULL); 
                                                                        add_child($$,$2);}

        |   FuncInvocation                                              {$$ = $1;}
        |   ParseArgs                                                   {$$ = newNode("ParseArgs", NULL);}
        |   PRINT LPAR Expr RPAR                                        {$$ = newNode("Print", NULL); 
                                                                        add_child($$, $3);}
                                                                                
        |   PRINT LPAR STRLIT RPAR                                      {$$ = newNode("Print", NULL); 
                                                                        aux = newNode("StrLit", $3); 
                                                                        add_child($$,aux);}
                                                                        
        |   error                                                       {$$ = NULL;}
        ;

StatementList:  ELSE LBRACE StatementList1 RBRACE       {$$ = $3}
            |   /* EPSILON */                           {$$ = NULL;}
            ;


StatementList1: StatementList1 Statement SEMICOLON       {$$ = $1; add_sibling($$, $2);}
              | /* EPSILON */   {$$ = NULL;}
              ;

ParseArgs:  ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR     {$$ = newNode("ParseArgs", NULL);
                                                                                aux = newNode("Id", $1);
                                                                                add_child($$, aux);
                                                                                add_sibling(aux, $9);
                                                                                }
        |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR    {$$ = newNode("ParseArgs", NULL);
                                                                aux = newNode("Id", $1);
                                                                add_child($$, aux);
                                                                add_sibling(aux, newNode("Error", NULL));
                                                                }
        ;

FuncInvocation: ID LPAR RPAR                                 {$$=newNode("Id", $1);}
              | ID LPAR Expr RPAR                            {$$=newNode("Id", $1); add_sibling($$, $3);}
              | ID LPAR Expr CommaExpressionList RPAR        {$$=newNode("Id", $1); add_sibling($$, $3); add_sibling($3, $4);}
              | ID LPAR error RPAR                           {$$=newNode("Id", $1); add_sibling($$, newNode("Error", NULL));}
              ;

CommaExpressionList: CommaExpressionList COMMA Expr          {$$=$1; add_sibling($1, $3);}
        | COMMA Expr                                         {$$=$2;}
        ;


Expr:   Expr MOD Expr           {$$ = newNode("Mod", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr LT Expr            {$$ = newNode("Lt",NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr GT Expr            {$$ = newNode("Gt",NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr EQ Expr            {$$ = newNode("Eq", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr NE Expr            {$$ = newNode("Ne", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr LE Expr            {$$ = newNode("Le", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr GE Expr            {$$ = newNode("Ge", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr OR Expr            {$$ = newNode("Or", NULL); add_child($$, $1); add_sibling($1, $3);} 
    |   Expr AND Expr           {$$ = newNode("And", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr PLUS Expr          {$$ = newNode("Add", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr MINUS Expr         {$$ = newNode("Sub", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr STAR Expr          {$$ = newNode("Star", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr DIV Expr           {$$ = newNode("Div", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   NOT Expr                {$$ = newNode("Not", NULL); add_child($$, $2);}
    |   MINUS Expr  %prec DIV   {$$ = newNode("Minus", NULL); add_child($$, $2);}
    |   PLUS Expr   %prec DIV   {$$ = newNode("Plus", NULL); add_child($$, $2);}
    |   INTLIT                  {$$ = newNode("IntLit", $1);}
    |   REALLIT                 {$$ = newNode("RealLit", $1);}
    |   ID                      {$$ = newNode("Id", $1);}
    |   FuncInvocation          {$$ = newNode("Call", NULL); add_child($$, $1);}
    |   LPAR Expr RPAR          {$$ = $2;}
    |   LPAR error RPAR         {$$ = newNode("Error", NULL);}
    ;
%%