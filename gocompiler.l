/*  
    João Miguel Ferreira Castelo Branco Catré - 2019218953
    Sofia Botelho Vieira Alves - 2019227240
*/

/*  ./gocompiler -l < factorial.dgo */
/*  ./gocompiler -l < factorial.dgo | diff factorial.out - */

%{
    #include <stdio.h>
    #include <string.h>

    int semi_flag = 0;
%}

/* Define states for line comments and general comments */
%X LINE_COM GENERAL_COM STRING IDENTIFIERS KEYWORDS token


num                     [0-9]
hex_digit               {num}|[A-F]|[a-f]
octal_digit             [0-7]
octal_lit               0{octal_digit}*
decimal_lit             [1-9]{num}*
hex_lit                 0(x|X){hex_digit}+
letter_m                [a-z]
letter_M                [A-Z]
sig                     [+|-]?
exp                     [e|E]{sig}{num}+
escape                  \f|\n|\r|\t|\\|\"
raw_strlit              "'"{.}"'"
inter_strlit            '"'{.}'"'
new_line                \r\n|\n|\r
line_comments           "//"
general_start	        "/*"
general_end             "*/"


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

STRLIT      (\\{escape}|[^"])*         
INTLIT      {decimal_lit}|{octal_lit}|{hex_lit}
REALLIT     ({num}+"."({num}+)?{exp}?)|{num}+{exp}|"."{num}+{exp}?

RESERVED    "break"|"case"|"chan"|"const"|"continue"|"default"|"defer"|"else"|"fallthrough"|"func"|"go"|"goto"|"import"|"interface"|"map"|"range"|"select"|"struct"|"switch"|"type"|"++"|"--"
BLANKID     _
ID          ({letter_m}|{letter_M}|"_")+(({letter_m}|{letter_M}|"_"|{num})*)


%%
\"\"                         {printf("STRLIT(\"\")\n"); semi_flag = 0;}
\"                           {BEGIN STRING; semi_flag = 0;}
<STRING>{STRLIT}             {printf("STRLIT(\"%s\")\n", yytext); semi_flag = 1;} //
<STRING>\"                   {BEGIN 0; semi_flag = 0;}
{line_comments}              {BEGIN LINE_COM; semi_flag = 0;}
<LINE_COM>{new_line}         {BEGIN 0; semi_flag = 0;}
<LINE_COM>.                  {;}
{general_start}              {BEGIN GENERAL_COM; semi_flag = 0;}
<GENERAL_COM>{new_line}      {;}
<GENERAL_COM>.               {;}
<GENERAL_COM>{general_end}   {BEGIN 0; semi_flag = 0;}
{INTLIT}                     {printf("INTLIT(%s)\n", yytext); semi_flag = 0;
                                if(strcmp(&yytext[strlen(yytext)], "\n")){
                                    printf("SEMICOLON\n");
                                } 
} //
{REALLIT}                    {printf("REALLIT(%s)\n", yytext); semi_flag = 1;} //
{SEMICOLON}                  {printf("SEMICOLON\n"); semi_flag = 0;}
{COMMA}                      {printf("COMMA\n"); semi_flag = 0;}
{ASSIGN}                     {printf("ASSIGN\n"); semi_flag = 0;}
{STAR}                       {printf("STAR\n"); semi_flag = 0;}
{DIV}                        {printf("DIV\n"); semi_flag = 0;}
{MINUS}                      {printf("MINUS\n"); semi_flag = 0;}
{PLUS}                       {printf("PLUS\n"); semi_flag = 0;}
{EQ}                         {printf("EQ\n"); semi_flag = 0;} 
{GE}                         {printf("GE\n"); semi_flag = 0;}
{GT}                         {printf("GT\n"); semi_flag = 0;}
{LBRACE}                     {printf("LBRACE\n"); semi_flag = 0;}
{LE}                         {printf("LE\n"); semi_flag = 0;}
{LPAR}                       {printf("LPAR\n"); semi_flag = 0;}
{LSQ}                        {printf("LSQ\n"); semi_flag = 0;}
{LT}                         {printf("LT\n"); semi_flag = 0;}
{MOD}                        {printf("MOD\n"); semi_flag = 0;}
{NE}                         {printf("NE\n"); semi_flag = 0;}
{NOT}                        {printf("NOT\n"); semi_flag = 0;}
{AND}                        {printf("AND\n"); semi_flag = 0;}
{OR}                         {printf("OR\n"); semi_flag = 0;}
{RBRACE}                     {printf("RBRACE\n"); semi_flag = 1;} //
{RPAR}                       {printf("RPAR\n"); semi_flag = 1;} //
{RSQ}                        {printf("RSQ\n"); semi_flag = 1;} //
{PACKAGE}                    {printf("PACKAGE\n"); semi_flag = 1;}
{RETURN}                     {printf("RETURN\n"); semi_flag = 1;} //
{ELSE}                       {printf("ELSE\n"); semi_flag = 0;}
{FOR}                        {printf("FOR\n"); semi_flag = 0;}
{IF}                         {printf("IF\n"); semi_flag = 0;}
{VAR}                        {printf("VAR\n"); semi_flag = 0;}
{INT}                        {printf("INT\n"); semi_flag = 0;}
{FLOAT32}                    {printf("FLOAT32\n"); semi_flag = 0;}
{BOOL}                       {printf("BOOL\n"); semi_flag = 0;}
{STRING}                     {printf("STRING\n"); semi_flag = 0;}
{PRINT}                      {printf("PRINT\n"); semi_flag = 0;}
{PARSEINT}                   {printf("PARSEINT\n"); semi_flag = 0;}
{FUNC}                       {printf("FUNC\n"); semi_flag = 0;}
{CMDARGS}                    {printf("CMDARGS\n"); semi_flag = 0;}
{RESERVED}                   {printf("RESERVED(%s)\n", yytext); semi_flag = 0;}
{BLANKID}                    {printf("BLANKID\n"); semi_flag = 0;}
{ID}                         {printf("ID(%s)\n", yytext); semi_flag = 1;} //
" "                          {;}   
\t                           {;}
{new_line}                   {;}
.                            {;}


%%

int main()
{
yylex();
return 0;
}

int yywrap() {
return 1;
}