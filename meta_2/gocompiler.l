%{
/*
    * Projeto de Compiladores 2021/2022
    * 2019218953 João Miguel Ferreira Castelo Branco Catré
    * 2019227240 Sofia Botelho Vieira Alves
*/  
    //C
    #include <stdio.h>
    #include <string.h>

    //YACC+
    #include "structures_p.h"
    #include "y.tab.h"
    

    int semi_flag = 0;
    int line_num = 1;
    int column_num = 1;
    int col_com = 1;
    int ln_com = 1;
    int octal_error = 0;
    int illegal_line = 1;
    int illegal_col = 1;
    int invalid_escape = 0;
    int flag_lex = 0;
    int flag_ret = 0;
%}

/* Define states for line comments and general comments */
%X LINE_COM GENERAL_COM STRING_COND INV_ESCAPE


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

escape                  f|n|r|t|\\|\"  
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

STRLIT      (\\{escape}|[^\"\\\r\\\n\\\\])*      
INTLIT      {decimal_lit}|{octal_lit}|{hex_lit}
REALLIT     ({num}+"."({num}+)?{exp}?)|{num}+{exp}|"."{num}+{exp}?
RESERVED    "break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"else"|"fallthrough"|"func"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"|"++"|"--"
BLANKID     _
ID          ({letter_m}|{letter_M}|"_")+(({letter_m}|{letter_M}|"_"|{num})*)


%%
\"\"                            {printf("STRLIT(\"\")\n"); semi_flag = 1; column_num+=yyleng; if(flag_ret == 1) return STRLIT;}
\"                              {ln_com = line_num; col_com = column_num; BEGIN STRING_COND; semi_flag = 0; column_num+=yyleng;}
<STRING_COND>{STRLIT}\"         {printf("STRLIT(\"%s)\n", yytext); 
                                semi_flag = 1; 
                                column_num+=yyleng;
                                if(flag_ret == 1) return STRLIT;
                                BEGIN 0;
                                }
<STRING_COND>\\                 {printf("Line %d, column %d: invalid escape sequence (\\)\n", line_num, column_num);
                                printf("Line %d, column %d: unterminated string literal", ln_com, col_com);
                                column_num += yyleng;
                                }
<STRING_COND>{STRLIT}           {column_num+=yyleng;}
<STRING_COND>\\{new_line}       {printf("Line %d, column %d: invalid escape sequence (\\)\n", line_num, column_num);
                                semi_flag = 0;
                                column_num = 1; 
                                line_num++;
                                BEGIN 0;
                                } 
<STRING_COND>{STRLIT}{new_line} {printf("Line %d, column %d: unterminated string literal\n", ln_com, col_com);
                                semi_flag = 0;
                                column_num = 1; 
                                line_num++;
                                BEGIN 0;
                                }

<STRING_COND>\\[^fnrt\\\"]      {BEGIN INV_ESCAPE;
                                printf("Line %d, column %d: invalid escape sequence (%s)\n", line_num, column_num, yytext);
                                column_num += yyleng;
                                }           
<INV_ESCAPE>\"                  {column_num+=yyleng; BEGIN 0;}
<INV_ESCAPE>\\                  {printf("Line %d, column %d: invalid escape sequence (\\)\n", line_num, column_num);
                                printf("Line %d, column %d: unterminated string literal", ln_com, col_com);
                                column_num += yyleng;
                                }                      
<INV_ESCAPE>{STRLIT}            {column_num+=yyleng;} 
<INV_ESCAPE>\\[^fnrt\\\"]       {printf("Line %d, column %d: invalid escape sequence (%s)\n", line_num, column_num, yytext);
                                column_num += yyleng;
                                }
<INV_ESCAPE>{new_line}          {printf("Line %d, column %d: unterminated string literal\n", ln_com, col_com);
                                semi_flag = 0;
                                column_num = 1; 
                                line_num++;
                                BEGIN 0;
                                }
<INV_ESCAPE>\\{new_line}        {printf("Line %d, column %d: invalid escape sequence (\\)\n", line_num, column_num);
                                printf("Line %d, column %d: unterminated string literal\n", ln_com, col_com);
                                semi_flag = 0;
                                column_num = 1; 
                                line_num++;
                                BEGIN 0;
                                }

{line_comments}                 {BEGIN LINE_COM; column_num+=yyleng;}
<LINE_COM>{new_line}            {column_num = 1; BEGIN 0; line_num++;}
<LINE_COM>.                     {column_num+=yyleng;}

{general_start}                 {ln_com = line_num; col_com = column_num; BEGIN GENERAL_COM; column_num+=yyleng;}
<GENERAL_COM>{new_line}         {column_num = 1; line_num++;}
<GENERAL_COM><<EOF>>            {printf("Line %d, column %d: unterminated comment\n", ln_com, col_com); yyterminate();}
<GENERAL_COM>.                  {column_num+=yyleng;}
<GENERAL_COM>{general_end}      {BEGIN 0; column_num+=yyleng;}

{INTLIT}                        {if(flag_lex == 1) printf("INTLIT(%s)\n", yytext); semi_flag = 1; column_num+=yyleng; if(flag_ret == 1) return INTLIT;}
{invalid_octal_lit}             {printf("Line %d, column %d: invalid octal constant (%s)\n", line_num, column_num, yytext); semi_flag = 1; column_num+=yyleng;}

{REALLIT}                       {if(flag_lex == 1) printf("REALLIT(%s)\n", yytext); semi_flag = 1; column_num+=yyleng; if(flag_ret == 1) return REALLIT;} 
{SEMICOLON}                     {if(flag_lex == 1) printf("SEMICOLON\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return SEMICOLON;}
{COMMA}                         {if(flag_lex == 1) printf("COMMA\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return COMMA;}
{ASSIGN}                        {if(flag_lex == 1) printf("ASSIGN\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return ASSIGN;}
{STAR}                          {if(flag_lex == 1) printf("STAR\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return STAR;}
{DIV}                           {if(flag_lex == 1) printf("DIV\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return DIV;}
{MINUS}                         {if(flag_lex == 1) printf("MINUS\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return MINUS;}
{PLUS}                          {if(flag_lex == 1) printf("PLUS\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return PLUS;}
{EQ}                            {if(flag_lex == 1) printf("EQ\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return EQ;} 
{GE}                            {if(flag_lex == 1) printf("GE\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return GE;}
{GT}                            {if(flag_lex == 1) printf("GT\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return GT;}
{LBRACE}                        {if(flag_lex == 1) printf("LBRACE\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return LBRACE;}
{LE}                            {if(flag_lex == 1) printf("LE\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return LE;}
{LPAR}                          {if(flag_lex == 1) printf("LPAR\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return LPAR;}
{LSQ}                           {if(flag_lex == 1) printf("LSQ\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return LSQ;}
{LT}                            {if(flag_lex == 1) printf("LT\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return LT;}
{MOD}                           {if(flag_lex == 1) printf("MOD\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return MOD;}
{NE}                            {if(flag_lex == 1) printf("NE\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return NE;}
{NOT}                           {if(flag_lex == 1) printf("NOT\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return NOT;}
{AND}                           {if(flag_lex == 1) printf("AND\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return AND;}
{OR}                            {if(flag_lex == 1) printf("OR\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return OR;}
{RBRACE}                        {if(flag_lex == 1) printf("RBRACE\n"); semi_flag = 1; column_num+=yyleng; if(flag_ret == 1) return RBRACE;}
{RPAR}                          {if(flag_lex == 1) printf("RPAR\n"); semi_flag = 1; column_num+=yyleng; if(flag_ret == 1) return RPAR;}
{RSQ}                           {if(flag_lex == 1) printf("RSQ\n"); semi_flag = 1; column_num+=yyleng; if(flag_ret == 1) return RSQ;}
{PACKAGE}                       {if(flag_lex == 1) printf("PACKAGE\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return PACKAGE;}
{RETURN}                        {if(flag_lex == 1) printf("RETURN\n"); semi_flag = 1; column_num+=yyleng; if(flag_ret == 1) return RETURN;}
{ELSE}                          {if(flag_lex == 1) printf("ELSE\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return ELSE;}
{FOR}                           {if(flag_lex == 1) printf("FOR\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return FOR;}
{IF}                            {if(flag_lex == 1) printf("IF\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return IF;}
{VAR}                           {if(flag_lex == 1) printf("VAR\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return VAR;}
{INT}                           {if(flag_lex == 1) printf("INT\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return INT;}
{FLOAT32}                       {if(flag_lex == 1) printf("FLOAT32\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return FLOAT32;}
{BOOL}                          {if(flag_lex == 1) printf("BOOL\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return BOOL;}
{STRING}                        {if(flag_lex == 1) printf("STRING\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return STRING_L;}
{PRINT}                         {if(flag_lex == 1) printf("PRINT\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return PRINT;}
{PARSEINT}                      {if(flag_lex == 1) printf("PARSEINT\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return PARSEINT;}
{FUNC}                          {if(flag_lex == 1) printf("FUNC\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return FUNC;}
{CMDARGS}                       {if(flag_lex == 1) printf("CMDARGS\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return CMDARGS;}
{RESERVED}                      {if(flag_lex == 1) printf("RESERVED(%s)\n", yytext); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return RESERVED;}
{BLANKID}                       {if(flag_lex == 1) printf("BLANKID\n"); semi_flag = 0; column_num+=yyleng; if(flag_ret == 1) return BLANKID;}
{ID}                            {if(flag_lex == 1) printf("ID(%s)\n", yytext); semi_flag = 1; column_num+=yyleng; if(flag_ret == 1) return ID;}

{space}                         {column_num+=yyleng;}   
\t                              {column_num+=yyleng;}
{new_line}                      {if(flag_lex == 1){ if(semi_flag == 1) printf("SEMICOLON\n");} semi_flag = 0; line_num++; column_num = 1;}
.                               {printf("Line %d, column %d: illegal character (%s)\n", line_num, column_num, yytext); column_num+=yyleng;}
<<EOF>>                         {if(flag_lex == 1){ if(semi_flag == 1) printf("SEMICOLON\n");} yyterminate();}

%%

void yyerror (char *s) {
    printf ("Line %d, column %d: %s: %s\n", line_num, column_num, s, yytext);
}

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "-l") == 0){
        flag_lex = 1;
        yylex();
        }

    else if(argc == 1){
        flag_ret = 1;
        yyparse();
    }
return 0;
}

int yywrap() {
return 1;
}