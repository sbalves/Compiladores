/*  
    João Miguel Ferreira Castelo Branco Catré - 2019218953
    Sofia Botelho Vieira Alves - 2019227240
*/

/*  ./gocompiler -l < factorial.dgo */
/*  ./gocompiler -l < factorial.dgo | diff factorial.out - */

/* <STRING><<EOF>>              {printf("Line %d, column %d: unterminated string literal\n", ln_com, col_com); yyterminate();} */

%{
    #include <stdio.h>
    #include <string.h>

    int semi_flag = 0;
    int line_num = 1;
    int column_num = 1;
    int col_com = 1;
    int ln_com = 1;
    int octal_error = 0;
    int illegal_line = 1;
    int illegal_col = 1;
    int invalid_escape = 0;
%}

/* Define states for line comments and general comments */
%X LINE_COM GENERAL_COM STRING INV_ESCAPE PARAGRAFO


num                     [0-9]
hex_digit               {num}|[A-F]|[a-f]
octal_digit             [0-7]
octal_lit               0{octal_digit}*
invalid_octal_lit       0{num}*
decimal_lit             [1-9]{num}*
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

STRLIT      (\\{escape}|[^"\r\n\\])*      
INTLIT      {decimal_lit}|{octal_lit}|{hex_lit}
REALLIT     ({num}+"."({num}+)?{exp}?)|{num}+{exp}|"."{num}+{exp}?
RESERVED    "break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"else"|"fallthrough"|"func"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"|"++"|"--"
BLANKID     _
ID          ({letter_m}|{letter_M}|"_")+(({letter_m}|{letter_M}|"_"|{num})*)


%%
\"\"                            {printf("STRLIT(\"\")\n"); semi_flag = 1; column_num+=yyleng;}
\"                              {ln_com = line_num; col_com = column_num; BEGIN STRING; semi_flag = 0; column_num+=yyleng;}

<STRING>{STRLIT}                {column_num+=yyleng;}

<STRING>{STRLIT}\"              {
                                printf("STRLIT(\"%s)\n", yytext); 
                                semi_flag = 1; 
                                column_num+=yyleng;
                                BEGIN 0;
                                }

<STRING>{STRLIT}{new_line}      {
                                printf("Line %d, column %d: unterminated string literal\n", ln_com, col_com);
                                semi_flag = 0;
                                column_num = 1; 
                                line_num++;
                                BEGIN 0;
                                } 

<STRING>\\{new_line}            {
                                printf("Line %d, column %d: invalid escape sequence (\\)\n", line_num, column_num);
                                semi_flag = 0;
                                column_num = 1; 
                                line_num++;
                                BEGIN 0;
                                }

<STRING>\\[^fnrt\\\"]           {BEGIN INV_ESCAPE;
                                printf("Line %d, column %d: invalid escape sequence (%s)\n", line_num, column_num, yytext);
                                column_num += yyleng;
                                }                                

<INV_ESCAPE>{STRLIT}            {column_num+=yyleng;} 

<INV_ESCAPE>\\[^fnrt\\\"]       {printf("Line %d, column %d: invalid escape sequence (%s)\n", line_num, column_num, yytext);
                                column_num += yyleng;
                                }

<INV_ESCAPE>\"                  {column_num+=yyleng; BEGIN 0;}

<INV_ESCAPE>{new_line}          {
                                printf("Line %d, column %d: unterminated string literal\n", ln_com, col_com);
                                semi_flag = 0;
                                column_num = 1; 
                                line_num++;
                                BEGIN 0;
                                }

<INV_ESCAPE>\\{new_line}        {
                                printf("Line %d, column %d: invalid escape sequence (\\)\n", line_num, column_num);
                                printf("Line %d, column %d: unterminated string literal\n", ln_com, col_com);
                                semi_flag = 0;
                                column_num = 1; 
                                line_num++;
                                BEGIN 0;
                                }

<INV_ESCAPE>\\                  {printf("Line %d, column %d: invalid escape sequence (\\)\n", line_num, column_num);
                                printf("Line %d, column %d: unterminated string literal", ln_com, col_com);
                                column_num += yyleng;
                                }   


<STRING>\\                      {printf("Line %d, column %d: invalid escape sequence (\\)\n", line_num, column_num);
                                printf("Line %d, column %d: unterminated string literal", ln_com, col_com);
                                column_num += yyleng;
                                }
                                
{line_comments}                 {BEGIN LINE_COM; column_num+=yyleng;}
<LINE_COM>{new_line}            {column_num = 1; BEGIN 0; line_num++;}
<LINE_COM>.                     {column_num+=yyleng;}

{general_start}                 {ln_com = line_num; col_com = column_num; BEGIN GENERAL_COM; column_num+=yyleng;}
<GENERAL_COM>{new_line}         {column_num = 1; line_num++;} /* ver erro */
<GENERAL_COM><<EOF>>            {printf("Line %d, column %d: unterminated comment\n", ln_com, col_com); yyterminate();}
<GENERAL_COM>.                  {column_num+=yyleng;}
<GENERAL_COM>{general_end}      {BEGIN 0; column_num+=yyleng;}

{INTLIT}                        {printf("INTLIT(%s)\n", yytext); semi_flag = 1; column_num+=yyleng;}
{invalid_octal_lit}             {printf("Line %d, column %d: invalid octal constant (%s)\n", line_num, column_num, yytext); semi_flag = 1; column_num+=yyleng;}

{REALLIT}                       {printf("REALLIT(%s)\n", yytext); semi_flag = 1; column_num+=yyleng;} 
{SEMICOLON}                     {printf("SEMICOLON\n"); semi_flag = 0; column_num+=yyleng;}
{COMMA}                         {printf("COMMA\n"); semi_flag = 0; column_num+=yyleng;}
{ASSIGN}                        {printf("ASSIGN\n"); semi_flag = 0; column_num+=yyleng;}
{STAR}                          {printf("STAR\n"); semi_flag = 0; column_num+=yyleng;}
{DIV}                           {printf("DIV\n"); semi_flag = 0; column_num+=yyleng;}
{MINUS}                         {printf("MINUS\n"); semi_flag = 0; column_num+=yyleng;}
{PLUS}                          {printf("PLUS\n"); semi_flag = 0; column_num+=yyleng;}
{EQ}                            {printf("EQ\n"); semi_flag = 0; column_num+=yyleng;} 
{GE}                            {printf("GE\n"); semi_flag = 0; column_num+=yyleng;}
{GT}                            {printf("GT\n"); semi_flag = 0; column_num+=yyleng;}
{LBRACE}                        {printf("LBRACE\n"); semi_flag = 0; column_num+=yyleng;}
{LE}                            {printf("LE\n"); semi_flag = 0; column_num+=yyleng;}
{LPAR}                          {printf("LPAR\n"); semi_flag = 0; column_num+=yyleng;}
{LSQ}                           {printf("LSQ\n"); semi_flag = 0; column_num+=yyleng;}
{LT}                            {printf("LT\n"); semi_flag = 0; column_num+=yyleng;}
{MOD}                           {printf("MOD\n"); semi_flag = 0; column_num+=yyleng;}
{NE}                            {printf("NE\n"); semi_flag = 0; column_num+=yyleng;}
{NOT}                           {printf("NOT\n"); semi_flag = 0; column_num+=yyleng;}
{AND}                           {printf("AND\n"); semi_flag = 0; column_num+=yyleng;}
{OR}                            {printf("OR\n"); semi_flag = 0; column_num+=yyleng;}
{RBRACE}                        {printf("RBRACE\n"); semi_flag = 1; column_num+=yyleng;}
{RPAR}                          {printf("RPAR\n"); semi_flag = 1; column_num+=yyleng;}
{RSQ}                           {printf("RSQ\n"); semi_flag = 1; column_num+=yyleng;}
{PACKAGE}                       {printf("PACKAGE\n"); semi_flag = 0; column_num+=yyleng;}
{RETURN}                        {printf("RETURN\n"); semi_flag = 1; column_num+=yyleng;}
{ELSE}                          {printf("ELSE\n"); semi_flag = 0; column_num+=yyleng;}
{FOR}                           {printf("FOR\n"); semi_flag = 0; column_num+=yyleng;}
{IF}                            {printf("IF\n"); semi_flag = 0; column_num+=yyleng;}
{VAR}                           {printf("VAR\n"); semi_flag = 0; column_num+=yyleng;}
{INT}                           {printf("INT\n"); semi_flag = 0; column_num+=yyleng;}
{FLOAT32}                       {printf("FLOAT32\n"); semi_flag = 0; column_num+=yyleng;}
{BOOL}                          {printf("BOOL\n"); semi_flag = 0; column_num+=yyleng;}
{STRING}                        {printf("STRING\n"); semi_flag = 0; column_num+=yyleng;}
{PRINT}                         {printf("PRINT\n"); semi_flag = 0; column_num+=yyleng;}
{PARSEINT}                      {printf("PARSEINT\n"); semi_flag = 0; column_num+=yyleng;}
{FUNC}                          {printf("FUNC\n"); semi_flag = 0; column_num+=yyleng;}
{CMDARGS}                       {printf("CMDARGS\n"); semi_flag = 0; column_num+=yyleng;}
{RESERVED}                      {printf("RESERVED(%s)\n", yytext); semi_flag = 0; column_num+=yyleng;}
{BLANKID}                       {printf("BLANKID\n"); semi_flag = 0; column_num+=yyleng;}
{ID}                            {printf("ID(%s)\n", yytext); semi_flag = 1; column_num+=yyleng;}

{space}                         {column_num+=yyleng;}   
\t                              {column_num+=yyleng;}
{new_line}                      {if(semi_flag == 1) printf("SEMICOLON\n"); semi_flag = 0; line_num++; column_num = 1;}
.                               {printf("Line %d, column %d: illegal character (%s)\n", line_num, column_num, yytext); column_num+=yyleng;}
<<EOF>>                         {if(semi_flag == 1) printf("SEMICOLON\n"); yyterminate();}

%%

int main()
{
yylex();
return 0;
}

int yywrap() {
return 1;
}