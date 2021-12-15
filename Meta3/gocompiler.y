%{
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


%} 

%union{
        char* value;
        ast_node* node;   
};

// Yacc tokens 
%token SEMICOLON COMMA 
%token BLANKID
%token ASSIGN STAR DIV MINUS PLUS 
%token EQ GE GT LE LT MOD NE
%token NOT AND OR
%token LBRACE RBRACE LPAR RPAR LSQ RSQ 
%token PACKAGE
%token RETURN PRINT PARSEINT FUNC CMDARGS VAR
%token IF ELSE FOR
%token INT FLOAT32 BOOL STRING UNARY

%token <value> ID
%token <value> STRLIT INTLIT REALLIT
%token <value> RESERVED

// Yacc nonterminal types - *alterar consoante a árvore*
%type <node> Program
%type <node> Declarations Declarations2
%type <node> VarDeclaration
%type <node> VarSpec VarSpecList
%type <node> Type
%type <node> FuncDeclaration 
%type <node> Parameters ParametersList
%type <node> FuncBody
%type <node> VarsAndStatements
%type <node> Statement StatementList
%type <node> ParseArgs
%type <node> FuncInvocation FuncID
%type <node> CommaExpressionList Expr

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

%nonassoc ELSE IF UNARY


%%

Program: PACKAGE ID SEMICOLON Declarations      {program_root = newNode("Program", NULL);
                                                add_child(program_root, $4);}
        ;

Declarations: Declarations2             {$$ = $1;}
            | /* EPSILON */             {$$ = NULL;}
            ;

Declarations2:  Declarations2 VarDeclaration SEMICOLON          {$$ = $1; add_sibling($1, $2);}
        |       VarDeclaration SEMICOLON                        {$$ = $1;}
        |       Declarations2 FuncDeclaration SEMICOLON         {$$ = $1; add_sibling($1, $2);}
        |       FuncDeclaration SEMICOLON                       {$$ = $1;}
        ;

VarDeclaration: VAR VarSpec                           {$$ = $2;}
              | VAR LPAR VarSpec SEMICOLON RPAR       {$$ = $3;}
              ;

VarSpec: ID Type                {$$ = newNode("VarDecl", NULL); add_child($$, $2);
                                add_sibling($2, newNode("Id", $1));
                                } 

        | ID VarSpecList Type   {$$ = newNode("VarDecl", NULL); aux = newNode("Id", $1); 
                                add_child($$, $3); add_sibling($3, aux); add_sibling($$, $2);
                                varspec_aux = $$->sibling;
                                while(varspec_aux != NULL && strcmp(varspec_aux->first_child->id, "notype") == 0){
                                        strcpy(varspec_aux->first_child->id, $3->id);
                                        varspec_aux = varspec_aux->sibling;
                                }
                                }
        ;

VarSpecList:    COMMA ID VarSpecList    {$$ = newNode("VarDecl", NULL); varspec_aux_1 = newNode("notype", NULL);
                                        add_sibling($$, $3); add_child($$, varspec_aux_1); 
                                        add_sibling(varspec_aux_1, newNode("Id", $2));
                                        }
                | COMMA ID              {$$ = newNode("VarDecl", NULL);
                                        aux = newNode("notype", NULL);
                                        add_child($$, aux);
                                        add_sibling(aux, newNode("Id", $2)); 
                                        }
        ;

Type: INT      {$$ = newNode("Int", NULL);} 
    | FLOAT32  {$$ = newNode("Float32", NULL);}    
    | BOOL     {$$ = newNode("Bool", NULL);}
    | STRING   {$$ = newNode("String", NULL);}      
    ;

FuncDeclaration: FUNC ID LPAR Parameters RPAR Type FuncBody     {$$ = newNode("FuncDecl", NULL); 
                                                                aux = newNode("FuncHeader", NULL);
                                                                aux2 = newNode("Id", $2);
                                                                add_child($$, aux);                                                                                
                                                                add_sibling(aux, $7);
                                                                add_child(aux, aux2);
                                                                add_sibling($6, $4);
                                                                add_sibling(aux2, $6);
                                                                }
                | FUNC ID LPAR Parameters RPAR FuncBody         {$$ = newNode("FuncDecl", NULL);
                                                                aux = newNode("FuncHeader", NULL);
                                                                aux2 = newNode("Id", $2);
                                                                add_child($$, aux);
                                                                add_sibling(aux, $6);
                                                                add_child(aux, aux2);
                                                                add_sibling(aux2, $4);
                                                                }
                | FUNC ID LPAR RPAR Type FuncBody               {$$ = newNode("FuncDecl", NULL);
                                                                aux = newNode("FuncHeader", NULL);
                                                                add_child($$, aux);
                                                                aux2 = newNode("Id", $2);
                                                                add_sibling(aux, $6);
                                                                add_child(aux, aux2);
                                                                add_sibling(aux2, $5);
                                                                add_sibling($5, newNode("FuncParams", NULL));
                                                                }
                | FUNC ID LPAR RPAR FuncBody                    {$$ = newNode("FuncDecl", NULL);
                                                                aux = newNode("FuncHeader", NULL);
                                                                aux2 = newNode("Id", $2);
                                                                add_child($$, aux);
                                                                add_child(aux, aux2);
                                                                add_sibling(aux2, newNode("FuncParams", NULL));
                                                                add_sibling(aux, $5);
                                                                }
                ;

Parameters: ID Type ParametersList              {$$ = newNode("FuncParams", NULL);
                                                aux = newNode("ParamDecl", NULL);
                                                add_child($$, aux);        
                                                add_sibling(aux, $3);
                                                add_child(aux, $2);
                                                add_sibling($2, newNode("Id", $1));
                                                }
        | ID Type                               {$$ = newNode("FuncParams", NULL);
                                                aux = newNode("ParamDecl", NULL);
                                                add_child($$, aux);        
                                                add_child(aux, $2);
                                                add_sibling($2, newNode("Id", $1));
                                                }
        ;

ParametersList: COMMA ID Type ParametersList            {$$ = newNode("ParamDecl", NULL);
                                                        add_child($$, $3);
                                                        add_sibling($3, newNode("Id", $2));
                                                        add_sibling($$, $4);
                                                        }
        | COMMA ID Type                                 {$$ = newNode("ParamDecl", NULL);
                                                        add_child($$, $3);
                                                        add_sibling($3, newNode("Id", $2));
                                                        }
              ;

FuncBody:   LBRACE VarsAndStatements RBRACE       {$$ = newNode("FuncBody", NULL); add_child($$, $2);}
        ;

VarsAndStatements:  VarsAndStatements VarDeclaration SEMICOLON  {$$ = $1; add_sibling($1, $2);}
                 |  VarsAndStatements Statement SEMICOLON       {$$ = $1; add_sibling($1, $2);}
                 |  VarsAndStatements SEMICOLON                 {$$ = $1;}
                 |  /*Epsilon = NULL*/                          {$$ = newNode("NULL", NULL);}
                 ;

Statement:  ID ASSIGN Expr                                              {$$ = newNode("Assign", NULL);
                                                                        aux = newNode("Id", $1);
                                                                        add_child($$, aux);
                                                                        add_sibling(aux, $3);
                                                                        }
        |   LBRACE RBRACE                                               {$$ = newNode("NULL", NULL);}
        |   LBRACE StatementList RBRACE                                 {aux = $2;
                                                                        int n = 0;
                                                                        while(aux != NULL){
                                                                                if(strcmp(aux->id, "NULL") != 0) n++;
                                                                                aux = aux->sibling;
                                                                        }
                                                                        if(n>=2){
                                                                                $$ = newNode("Block", NULL);
                                                                                add_child($$, $2);
                                                                        }
                                                                        else $$ = $2;
                                                                        }
        | IF Expr LBRACE RBRACE                                         {$$ = newNode("If", NULL );
                                                                        add_child($$, $2);
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling($2, aux);
                                                                        add_sibling(aux, newNode("Block", NULL));
                                                                        }
        | IF Expr LBRACE StatementList RBRACE                           {$$ = newNode("If", NULL);
                                                                        add_child($$, $2);
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling($2, aux);
                                                                        add_child(aux, $4);
                                                                        add_sibling(aux, newNode("Block", NULL));
                                                                        }
        | IF Expr LBRACE RBRACE ELSE LBRACE RBRACE                      {$$ = newNode("If", NULL);
                                                                        add_child($$, $2);
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling($2, aux);
                                                                        add_sibling(aux, newNode("Block", NULL));
                                                                        }
        | IF Expr LBRACE StatementList RBRACE ELSE LBRACE RBRACE        {$$ = newNode("If", NULL);
                                                                        add_child($$, $2);
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling($2, aux);
                                                                        add_child(aux, $4);
                                                                        add_sibling(aux, newNode("Block", NULL));
                                                                        }
        | IF Expr LBRACE RBRACE ELSE LBRACE StatementList RBRACE        {$$ = newNode("If", NULL);
                                                                        add_child($$, $2);
                                                                        aux=newNode("Block", NULL);
                                                                        aux2=newNode("Block", NULL);
                                                                        add_sibling($2, aux);
                                                                        add_sibling(aux, aux2);
                                                                        add_child(aux2, $7);
                                                                        }
        | IF Expr LBRACE StatementList RBRACE ELSE LBRACE StatementList RBRACE {$$ = newNode("If", NULL);
                                                                                add_child($$, $2);
                                                                                aux=newNode("Block", NULL);
                                                                                aux2=newNode("Block", NULL);
                                                                                add_sibling($2, aux);
                                                                                add_child(aux, $4);
                                                                                add_sibling(aux, aux2);
                                                                                add_child(aux2, $8);
                                                                                }
        | FOR LBRACE RBRACE                                             {$$ = newNode("For", NULL);
                                                                        add_child($$, newNode("Block", NULL));
                                                                        }
        | FOR LBRACE StatementList RBRACE                               {$$ = newNode("For", NULL);
                                                                        aux=newNode("Block", NULL);
                                                                        add_child($$, aux);
                                                                        add_child(aux, $3);
                                                                        }
        | FOR Expr LBRACE RBRACE                                        {$$ = newNode("For", NULL);
                                                                        add_child($$, $2);
                                                                        add_sibling($2, newNode("Block", NULL));
                                                                        }
        | FOR Expr LBRACE StatementList RBRACE                          {$$ = newNode("For", NULL);
                                                                        add_child($$, $2);
                                                                        aux=newNode("Block", NULL);
                                                                        add_sibling($2, aux);
                                                                        add_child(aux, $4);
                                                                        }
        |   RETURN                                                      {$$ = newNode("Return", NULL);} 
        |   RETURN Expr                                                 {$$ = newNode("Return", NULL);
                                                                        add_child($$, $2);}
        |   FuncInvocation                                              {$$ = newNode("Call", NULL);
                                                                        add_child($$, $1);}
        |   ParseArgs                                                   {$$ = $1;}
        |   PRINT LPAR Expr RPAR                                        {$$ = newNode("Print", NULL);
                                                                        add_child($$, $3);}
        |   PRINT LPAR STRLIT RPAR                                      {$$ = newNode("Print", NULL);
                                                                        aux = newNode("StrLit", $3);
                                                                        add_child($$, aux);}
        |   error                                                       {$$ = newNode("Error", NULL); free_ast(program_root);}
        ;

StatementList: StatementList Statement SEMICOLON        {$$ = $1; add_sibling($1, $2);}
              | Statement SEMICOLON                     {$$ = $1;}
              ;

ParseArgs:  ID COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR     {$$ = newNode("ParseArgs", NULL);
                                                                                aux = newNode("Id", $1);
                                                                                add_child($$, aux);
                                                                                add_sibling(aux, $9);
                                                                                }
        |   ID COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                    {$$ = newNode("ParseArgs", NULL);
                                                                                aux = newNode("Id", $1);
                                                                                add_child($$, aux);
                                                                                add_sibling(aux, newNode("Error", NULL));
                                                                                free_ast(program_root);
                                                                                }
        ;

FuncID: ID                                                   {$$ = newNode("Id", $1);}
        ;

FuncInvocation: FuncID LPAR RPAR                                {$$ = $1;}
              | FuncID LPAR Expr RPAR                           {$$ = $1; add_sibling($1, $3);}
              | FuncID LPAR Expr CommaExpressionList RPAR       {$$ = $1; add_sibling($1, $3); add_sibling($3, $4);}
              | FuncID LPAR error RPAR                          {$$ = $1; add_sibling($1, newNode("Error", NULL)); free_ast(program_root);}
              ;

CommaExpressionList: CommaExpressionList COMMA Expr          {$$ = $1; add_sibling($1, $3);}
        | COMMA Expr                                         {$$ = $2;}
        ;


Expr:   Expr OR Expr            {$$ = newNode("Or", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr AND Expr           {$$ = newNode("And", NULL); add_child($$, $1); add_sibling($1, $3);} 
    |   Expr LT Expr            {$$ = newNode("Lt",NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr GT Expr            {$$ = newNode("Gt",NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr EQ Expr            {$$ = newNode("Eq", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr NE Expr            {$$ = newNode("Ne", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr LE Expr            {$$ = newNode("Le", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr GE Expr            {$$ = newNode("Ge", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr PLUS Expr          {$$ = newNode("Add", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr MINUS Expr         {$$ = newNode("Sub", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr STAR Expr          {$$ = newNode("Mul", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr DIV Expr           {$$ = newNode("Div", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   Expr MOD Expr           {$$ = newNode("Mod", NULL); add_child($$, $1); add_sibling($1, $3);}
    |   NOT Expr                {$$ = newNode("Not", NULL); add_child($$, $2);}
    |   MINUS Expr  %prec DIV   {$$ = newNode("Minus", NULL); add_child($$, $2);}
    |   PLUS Expr   %prec DIV   {$$ = newNode("Plus", NULL); add_child($$, $2);}
    |   INTLIT                  {$$ = newNode("IntLit", $1);}
    |   REALLIT                 {$$ = newNode("RealLit", $1);}
    |   ID                      {$$ = newNode("Id", $1);}
    |   FuncInvocation          {$$ = newNode("Call", NULL); add_child($$, $1);}
    |   LPAR Expr RPAR          {$$ = $2;}
    |   LPAR error RPAR         {$$ = newNode("Error", NULL); free_ast(program_root);}
    ;
%%