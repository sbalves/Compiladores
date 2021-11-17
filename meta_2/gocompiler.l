%{
/*  
    * Projeto de Compiladores 2021/2022
    * 2019218953 João Miguel Ferreira Castelo Branco Catré
    * 2019227240 Sofia Botelho Vieira Alves
*/  

    //C
    #include <stdio.h>

    //YACC+
    #include "structures.h"
    #include "y.tab.h"
    
    int yylex_destroy(void);

    int semicolon_flag = 0;
    int line_num = 1;
    int column_num = 1;
    int col_com = 1;
    int ln_com = 1;
    int flag_lex = 0;
    int flag_return = 0;

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

sig                     [+|-]?
exp                     [e|E]{sig}{num}+

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
{STRLIT}                            {semicolon_flag = 1; if(flag_lex == 1) printf("STRLIT(%s)\n",yytext); column_num+= yyleng; if(flag_return) return STRLIT;}
\"                                  {BEGIN STRING_COND; ln_com = line_num; col_com = column_num; column_num+=yyleng; semicolon_flag = 0;}
<STRING_COND>\"                     {semicolon_flag = 1; if(flag_lex == 1) printf("STRLIT(%s)\n",yytext); column_num+=yyleng; BEGIN 0;}
<STRING_COND>{new_line}             {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", ln_com, column_num); column_num = 1; line_num++;}
<STRING_COND>{escape}|[^\\\r\n\"]   {column_num+=yyleng;} 
<STRING_COND>\\[^\n\r\"]|\\|\f|\t   {printf("Line %d, column %d: invalid escape sequence (%s)\n", ln_com, column_num, yytext); column_num+=yyleng; semicolon_flag = 0;}
<STRING_COND><<EOF>>                {BEGIN 0; printf("Line %d, column %d: unterminated string literal\n", ln_com, col_com);} 

{line_comments}                 {BEGIN LINE_COM; column_num+=yyleng;}
<LINE_COM>{new_line}            {column_num = 1; BEGIN 0; line_num++;}
<LINE_COM>.                     {column_num+=yyleng;}

{general_start}                 {ln_com = line_num; col_com = column_num; BEGIN GENERAL_COM; column_num+=yyleng;}
<GENERAL_COM>{new_line}         {column_num = 1; line_num++;}
<GENERAL_COM><<EOF>>            {printf("Line %d, column %d: unterminated comment\n", ln_com, col_com); yyterminate();}
<GENERAL_COM>.                  {column_num+=yyleng;}
<GENERAL_COM>{general_end}      {BEGIN 0; column_num+=yyleng;}

{INTLIT}                        {if(flag_lex == 1) printf("INTLIT(%s)\n", yytext); semicolon_flag = 1; column_num+=yyleng; if(flag_return == 1) return INTLIT;}
{invalid_octal_lit}             {printf("Line %d, column %d: invalid octal constant (%s)\n", line_num, column_num, yytext); semicolon_flag = 1; column_num+=yyleng;}

{REALLIT}                       {if(flag_lex == 1) printf("REALLIT(%s)\n", yytext); semicolon_flag = 1; column_num+=yyleng; if(flag_return == 1) return REALLIT;} 
{SEMICOLON}                     {if(flag_lex == 1) printf("SEMICOLON\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return SEMICOLON;}
{COMMA}                         {if(flag_lex == 1) printf("COMMA\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return COMMA;}
{ASSIGN}                        {if(flag_lex == 1) printf("ASSIGN\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return ASSIGN;}
{STAR}                          {if(flag_lex == 1) printf("STAR\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return STAR;}
{DIV}                           {if(flag_lex == 1) printf("DIV\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return DIV;}
{MINUS}                         {if(flag_lex == 1) printf("MINUS\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return MINUS;}
{PLUS}                          {if(flag_lex == 1) printf("PLUS\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return PLUS;}
{EQ}                            {if(flag_lex == 1) printf("EQ\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return EQ;} 
{GE}                            {if(flag_lex == 1) printf("GE\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return GE;}
{GT}                            {if(flag_lex == 1) printf("GT\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return GT;}
{LBRACE}                        {if(flag_lex == 1) printf("LBRACE\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return LBRACE;}
{LE}                            {if(flag_lex == 1) printf("LE\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return LE;}
{LPAR}                          {if(flag_lex == 1) printf("LPAR\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return LPAR;}
{LSQ}                           {if(flag_lex == 1) printf("LSQ\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return LSQ;}
{LT}                            {if(flag_lex == 1) printf("LT\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return LT;}
{MOD}                           {if(flag_lex == 1) printf("MOD\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return MOD;}
{NE}                            {if(flag_lex == 1) printf("NE\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return NE;}
{NOT}                           {if(flag_lex == 1) printf("NOT\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return NOT;}
{AND}                           {if(flag_lex == 1) printf("AND\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return AND;}
{OR}                            {if(flag_lex == 1) printf("OR\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return OR;}
{RBRACE}                        {if(flag_lex == 1) printf("RBRACE\n"); semicolon_flag = 1; column_num+=yyleng; if(flag_return == 1) return RBRACE;}
{RPAR}                          {if(flag_lex == 1) printf("RPAR\n"); semicolon_flag = 1; column_num+=yyleng; if(flag_return == 1) return RPAR;}
{RSQ}                           {if(flag_lex == 1) printf("RSQ\n"); semicolon_flag = 1; column_num+=yyleng; if(flag_return == 1) return RSQ;}
{PACKAGE}                       {if(flag_lex == 1) printf("PACKAGE\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return PACKAGE;}
{RETURN}                        {if(flag_lex == 1) printf("RETURN\n"); semicolon_flag = 1; column_num+=yyleng; if(flag_return == 1) return RETURN;}
{ELSE}                          {if(flag_lex == 1) printf("ELSE\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return ELSE;}
{FOR}                           {if(flag_lex == 1) printf("FOR\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return FOR;}
{IF}                            {if(flag_lex == 1) printf("IF\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return IF;}
{VAR}                           {if(flag_lex == 1) printf("VAR\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return VAR;}
{INT}                           {if(flag_lex == 1) printf("INT\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return INT;}
{FLOAT32}                       {if(flag_lex == 1) printf("FLOAT32\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return FLOAT32;}
{BOOL}                          {if(flag_lex == 1) printf("BOOL\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return BOOL;}
{STRING}                        {if(flag_lex == 1) printf("STRING\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return STRING;}
{PRINT}                         {if(flag_lex == 1) printf("PRINT\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return PRINT;}
{PARSEINT}                      {if(flag_lex == 1) printf("PARSEINT\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return PARSEINT;}
{FUNC}                          {if(flag_lex == 1) printf("FUNC\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return FUNC;}
{CMDARGS}                       {if(flag_lex == 1) printf("CMDARGS\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return CMDARGS;}
{RESERVED}                      {if(flag_lex == 1) printf("RESERVED(%s)\n", yytext); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return RESERVED;}
{BLANKID}                       {if(flag_lex == 1) printf("BLANKID\n"); semicolon_flag = 0; column_num+=yyleng; if(flag_return == 1) return BLANKID;}
{ID}                            {if(flag_lex == 1) printf("ID(%s)\n", yytext); semicolon_flag = 1; column_num+=yyleng; if(flag_return == 1) return ID;}

{space}                         {column_num+=yyleng;}   
\t                              {column_num+=yyleng;}

{new_line}                      {line_num++; column_num = 1;
                                if(semicolon_flag == 1){
                                    if(flag_lex == 1){
                                        printf("SEMICOLON\n");
                                    }
                                    else if(flag_return == 1){
                                        semicolon_flag = 0;
                                        return SEMICOLON;
                                    }
                                }
                                semicolon_flag = 0;
                                }

<<EOF>>                         {if(semicolon_flag == 1){
                                    semicolon_flag = 0;
                                    if(flag_lex == 1)
                                        printf("SEMICOLON\n");
                                    if(flag_return == 1){
                                        yyterminate();
                                        return SEMICOLON;
                                        }
                                    }
                                    yyterminate(); return EOF;
                                }
.                               {printf("Line %d, column %d: illegal character (%s)\n", line_num, column_num, yytext); column_num+=yyleng;}

%%

void yyerror (char *s) {
    int i = 0;
    while(yytext[i] != 0){
        i++;
    }
    printf ("Line %d, column %d: %s: %s\n", line_num, column_num - i, s, yytext);
}

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "-l") == 0){
        flag_lex = 1;
        yylex();
        yylex_destroy();
    }

    else if(argc == 1){
        flag_return = 1;
        yyparse();
        yylex_destroy();
    }
return 0;
}

int yywrap() {
return 1;
}
