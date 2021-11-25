%{
    /*  
        * Projeto de Compiladores 2021/2022
        * Meta 2
        * 2019218953 João Miguel Ferreira Castelo Branco Catré
        * 2019227240 Sofia Botelho Vieira Alves
    */  
    #include "structures.h"
    #include "y.tab.h"
    
    int yylex_destroy(void);
    void pos(int length, int opt);

    int semicolon_flag = 0; //flag used to check if it is necessary to add a semicolon at the end
    int line_num = 1;
    int column_num = 1;
    int last_col_pos = 1;
    int last_line_pos = 1;
    int flag_lex = 0; //flag used to make lexical analysis if -l is used
    int flag_return = 0; //flag used to build tree
    int flag_sem = 0;

    extern int flag_syntax_error; //flag used to check if there are any syntax errors in order to build (or not) the tree

    extern node* program_root;  
%}
/* Define states for line comments and general comments */
%X LINE_COM GENERAL_COM STRING_COND


num                     [0-9]
octal_digit             [0-7]
octal_lit               0{octal_digit}*
invalid_octal_lit       0{num}*
decimal_lit             [1-9]{num}*
hex_digit               {num}|[A-F]|[a-f]
hex_lit                 0(x|X){hex_digit}+

letter_m                [a-z]
letter_M                [A-Z]

sig                     [+-]?
exp                     [eE]{sig}{num}+

escape                  (\\n|\\f|\\r|\\t|\t|\\\\|\\\")  
raw_strlit              "'"{.}"'"
inter_strlit            '"'{.}'"'
new_line                \r\n|\n|\r
line_comments           "//"
general_start	        "/*"
general_end             "*/"
space                   " "

COMMA       ","
SEMICOLON   ";"
ASSIGN      "="
STAR        "*"
DIV         "/"
MINUS       "-"
PLUS        "+"
EQ          "=="  
GE          ">="
GT          ">"
LBRACE      "{"
LE          "<="
LPAR        "("
LSQ         "["
LT          "<"
MOD         "%"
NE          "!="
NOT         "!"
AND         "&&"
OR          "||"
RBRACE      "}"
RPAR        ")"
RSQ         "]"
PACKAGE     "package"
RETURN      "return"
ELSE        "else"
FOR         "for"
IF          "if"
VAR         "var"
INT         "int"
FLOAT32     "float32"
BOOL        "bool"
STRING      "string"
PRINT       "fmt.Println"
PARSEINT    "strconv.Atoi"
FUNC        "func"
CMDARGS     "os.Args"

STRLIT      \"([^\n\r\\\"]|{escape})*\"  
INTLIT      {decimal_lit}|{octal_lit}|{hex_lit}
REALLIT     ({num}+"."({num}+)?{exp}?)|{num}+{exp}|"."{num}+{exp}?
RESERVED    "break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"else"|"fallthrough"|"func"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"|"++"|"--"
BLANKID     _
ID          ({letter_m}|{letter_M}|"_")+(({letter_m}|{letter_M}|"_"|{num})*)


%%
{STRLIT}                            {semicolon_flag = 1; if(flag_lex == 1) printf("STRLIT(%s)\n",yytext); pos(yyleng, 0);yylval.value = (char*) strdup(yytext); if(flag_return) return STRLIT;}
\"                                  {BEGIN STRING_COND; last_line_pos = line_num; last_col_pos = column_num; column_num+=yyleng; semicolon_flag = 0;}
<STRING_COND>\"                     {semicolon_flag = 1; if(flag_lex == 1) printf("STRLIT(%s)\n",yytext); yylval.value = (char*) strdup(yytext); column_num+=yyleng; BEGIN 0;}
<STRING_COND>{new_line}             {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", last_line_pos, last_col_pos); column_num = 1; line_num++;}
<STRING_COND>{escape}|[^\\\r\n\"]   {column_num+=yyleng;} 
<STRING_COND>\\[^\n\r\"]|\\|\f|\t   {printf("Line %d, column %d: invalid escape sequence (%s)\n", last_line_pos, column_num, yytext); column_num+=yyleng; semicolon_flag = 0;}
<STRING_COND><<EOF>>                {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", last_line_pos, last_col_pos);} 

{line_comments}                 {BEGIN LINE_COM; column_num+=yyleng;}
<LINE_COM>{new_line}            {column_num = 1; BEGIN 0; line_num++;}
<LINE_COM>.                     {column_num+=yyleng;}

{general_start}                 {last_line_pos = line_num; last_col_pos = column_num; BEGIN GENERAL_COM; column_num+=yyleng;}
<GENERAL_COM>{new_line}         {column_num = 1; line_num++;}
<GENERAL_COM><<EOF>>            {printf("Line %d, column %d: unterminated comment\n", last_line_pos, last_col_pos); yyterminate();}
<GENERAL_COM>.                  {column_num+=yyleng;}
<GENERAL_COM>{general_end}      {BEGIN 0; column_num+=yyleng;}

{INTLIT}                        {if(flag_lex == 1) printf("INTLIT(%s)\n", yytext); pos(yyleng, 0); semicolon_flag = 1; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return INTLIT;}
{invalid_octal_lit}             {printf("Line %d, column %d: invalid octal constant (%s)\n", line_num, column_num, yytext); semicolon_flag = 0; column_num+=yyleng;}

{REALLIT}                       {if(flag_lex == 1) printf("REALLIT(%s)\n", yytext); pos(yyleng, 0); semicolon_flag = 1; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return REALLIT;} 
{SEMICOLON}                     {if(flag_lex == 1) printf("SEMICOLON\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return SEMICOLON;}
{COMMA}                         {if(flag_lex == 1) printf("COMMA\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return COMMA;}
{ASSIGN}                        {if(flag_lex == 1) printf("ASSIGN\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return ASSIGN;}
{STAR}                          {if(flag_lex == 1) printf("STAR\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return STAR;}
{DIV}                           {if(flag_lex == 1) printf("DIV\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return DIV;}
{MINUS}                         {if(flag_lex == 1) printf("MINUS\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return MINUS;}
{PLUS}                          {if(flag_lex == 1) printf("PLUS\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return PLUS;}
{EQ}                            {if(flag_lex == 1) printf("EQ\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return EQ;} 
{GE}                            {if(flag_lex == 1) printf("GE\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return GE;}
{GT}                            {if(flag_lex == 1) printf("GT\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return GT;}
{LBRACE}                        {if(flag_lex == 1) printf("LBRACE\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return LBRACE;}
{LE}                            {if(flag_lex == 1) printf("LE\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return LE;}
{LPAR}                          {if(flag_lex == 1) printf("LPAR\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return LPAR;}
{LSQ}                           {if(flag_lex == 1) printf("LSQ\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return LSQ;}
{LT}                            {if(flag_lex == 1) printf("LT\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return LT;}
{MOD}                           {if(flag_lex == 1) printf("MOD\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return MOD;}
{NE}                            {if(flag_lex == 1) printf("NE\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return NE;}
{NOT}                           {if(flag_lex == 1) printf("NOT\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return NOT;}
{AND}                           {if(flag_lex == 1) printf("AND\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return AND;}

"||"                            {if(flag_lex == 1) printf("OR\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return OR;}
{RBRACE}                        {if(flag_lex == 1) printf("RBRACE\n"); pos(yyleng, 0); semicolon_flag = 1; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return RBRACE;}
{RPAR}                          {if(flag_lex == 1) printf("RPAR\n"); pos(yyleng, 0); semicolon_flag = 1; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return RPAR;}
{RSQ}                           {if(flag_lex == 1) printf("RSQ\n"); pos(yyleng, 0); semicolon_flag = 1; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return RSQ;}
{PACKAGE}                       {if(flag_lex == 1) printf("PACKAGE\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return PACKAGE;}
{RETURN}                        {if(flag_lex == 1) printf("RETURN\n"); pos(yyleng, 0); semicolon_flag = 1; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return RETURN;}
{ELSE}                          {if(flag_lex == 1) printf("ELSE\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return ELSE;}
{FOR}                           {if(flag_lex == 1) printf("FOR\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return FOR;}
{IF}                            {if(flag_lex == 1) printf("IF\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return IF;}
{VAR}                           {if(flag_lex == 1) printf("VAR\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return VAR;}
{INT}                           {if(flag_lex == 1) printf("INT\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return INT;}
{FLOAT32}                       {if(flag_lex == 1) printf("FLOAT32\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return FLOAT32;}
{BOOL}                          {if(flag_lex == 1) printf("BOOL\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return BOOL;}
{STRING}                        {if(flag_lex == 1) printf("STRING\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return STRING;}
{PRINT}                         {if(flag_lex == 1) printf("PRINT\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return PRINT;}
{PARSEINT}                      {if(flag_lex == 1) printf("PARSEINT\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return PARSEINT;}
{FUNC}                          {if(flag_lex == 1) printf("FUNC\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return FUNC;}
{CMDARGS}                       {if(flag_lex == 1) printf("CMDARGS\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return CMDARGS;}
{RESERVED}                      {if(flag_lex == 1) printf("RESERVED(%s)\n", yytext); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return RESERVED;}
{BLANKID}                       {if(flag_lex == 1) printf("BLANKID\n"); pos(yyleng, 0); semicolon_flag = 0; yylval.value = (char*) strdup(yytext); if(flag_return == 1)  return BLANKID;}
{ID}                            {if(flag_lex == 1) printf("ID(%s)\n", yytext); pos(yyleng, 0); semicolon_flag = 1; yylval.value = (char*) strdup(yytext); if(flag_return == 1) return ID;}

{space}                         {column_num+=yyleng;}   
\t                              {column_num+=yyleng;}

{new_line}                      {pos(yyleng, 1);
                                if(semicolon_flag == 1){
                                    semicolon_flag = 0;
                                    if(flag_lex == 1){
                                        printf("SEMICOLON\n");                                      
                                    }
                                    yylval.value = (char*) strdup(yytext);
                                    if(flag_return == 1){
                                        semicolon_flag = 0;                                
                                        return SEMICOLON;
                                        }
                                    }
                                }

<<EOF>>                         {pos(yyleng, 0); 
                                if(semicolon_flag == 1){
                                    semicolon_flag = 0;
                                    if(flag_lex == 1){
                                        printf("SEMICOLON\n");                                       
                                        }
                                   
                                    if(flag_return == 1){
                                        semicolon_flag = 0;
                                        return SEMICOLON;
                                        }
                                    }
                                    yylval.value = (char*) strdup(yytext);
                                    yyterminate(); return EOF;
                                }
.                               {printf("Line %d, column %d: illegal character (%s)\n", line_num, column_num, yytext); pos(yyleng, 0); }

%%

void pos(int length, int opt) {  
    last_line_pos = line_num;
    last_col_pos = column_num;
    
    if (opt == 0) column_num += length;
    else if (opt == 1) {
        line_num++; 
        column_num = 1;
    }
}

void yyerror (char *str) {
    flag_syntax_error=1;
    printf ("Line %d, column %d: %s: %s\n", last_line_pos, last_col_pos, str, yytext);
}

int main(int argc, char* argv[])
{   
    if (argc > 1 && strcmp(argv[1], "-l") == 0){
        flag_lex = 1;
        yylex();
    }
    if (argc > 1 && strcmp(argv[1], "-t") == 0){
        flag_return = 1;
        yyparse();
        if(flag_syntax_error == 0){
            print_ast(program_root, 0);
        }
    }
    if (argc > 1 && strcmp(argv[1], "-s") == 0){
        flag_sem = 1;
        yylex();
    }

    else if(argc == 1){
        flag_return = 1;
        yyparse();
    }
return 0;
}

int yywrap() {
return 1;
}
