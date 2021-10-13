/*  
    João Miguel Ferreira Castelo Branco Catré - 2019218953
    Sofia Botelho Vieira Alves - 2019227240
*/

/* INTLIT hexadecimal to decimal code from A (10) to F (15)
    {INTLIT}    {for(int i=0; i<yyleng; i++){
                if(yytext[i] == A||a){
                    yytext[i] = 10;
                }
                else if(yytext[i] == B||b){
                    yytext[i] == 11;
                }
                else if(yytext[i] == C||c){
                    yytext[i] == 12;
                }
                else if(yytext[i] == D||d){
                    yytext[i] == 13;
                }
                else if(yytext[i] == E||e){
                    yytext[i] == 14;
                }
                else if(yytext[i] == F||f){
                    yytext[i] == 15;
                }
            }
            printf(" intlit ");}
*/

/*  ./gocompiler -l < factorial.dgo */
/*  ./gocompiler -l < factorial.dgo | diff factorial.out - */

/* Define states for line comments and general comments */
%X LINE_COM GENERAL_COM STRING

num                     [0-9]
hex_digit               {num}|[A-F]|[a-f]
octal_digit             [0-7]
octal_lit               0{octal_digit}+
decimal_lit             [1-9]{num}+
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
general_start	             "/*"
general_end                   "*/"



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
\"                           {BEGIN STRING;printf("STRLIT(\"");}
<STRING>{STRLIT}             {printf("%s", yytext);}
<STRING>\"                   {printf("\")\n");BEGIN 0;}
{line_comments}              {BEGIN LINE_COM;}
<LINE_COM>{new_line}         {BEGIN 0;}
<LINE_COM>.                  {;}
{general_start}              {BEGIN GENERAL_COM;}
<GENERAL_COM>{new_line}      {;}
<GENERAL_COM>.               {;}
<GENERAL_COM>{general_end}   {BEGIN 0;}
{INTLIT}                     {printf("INTLIT(%s)\n", yytext);}
{REALLIT}                    {printf("REALLIT(%s)\n", yytext);}
{SEMICOLON}                  {printf("SEMICOLON\n");}
{COMMA}                      {printf("COMMA\n");}
{ASSIGN}                     {printf("ASSIGN\n");}
{STAR}                       {printf("STAR\n");}
{DIV}                        {printf("DIV\n");}
{MINUS}                      {printf("MINUS\n");}
{PLUS}                       {printf("PLUS\n");}
{EQ}                         {printf("EQ\n");} 
{GE}                         {printf("GE\n");}
{GT}                         {printf("GT\n");}
{LBRACE}                     {printf("LBRACE\n");}
{LE}                         {printf("LE\n");}
{LPAR}                       {printf("LPAR\n");}
{LSQ}                        {printf("LSQ\n");}
{LT}                         {printf("LT\n");}
{MOD}                        {printf("MOD\n");}
{NE}                         {printf("NE\n");}
{NOT}                        {printf("NOT\n");}
{AND}                        {printf("AND\n");}
{OR}                         {printf("OR\n");}
{RBRACE}                     {printf("RBRACE\n");}
{RPAR}                       {printf("RPAR\n");}
{RSQ}                        {printf("RSQ\n");}
{PACKAGE}                    {printf("PACKAGE\n");}
{RETURN}                     {printf("RETURN\n");}
{ELSE}                       {printf("ELSE\n");}
{FOR}                        {printf("FOR\n");}
{IF}                         {printf("IF\n");}
{VAR}                        {printf("VAR\n");}
{INT}                        {printf("INT\n");}
{FLOAT32}                    {printf("FLOAT32\n");}
{BOOL}                       {printf("BOOL\n");}
{STRING}                     {printf("STRING\n");}
{PRINT}                      {printf("PRINT\n");}
{PARSEINT}                   {printf("PARSEINT\n");}
{FUNC}                       {printf("FUNC\n");}
{CMDARGS}                    {printf("CMDARGS\n");}
{RESERVED}                   {printf("RESERVED(%s)\n", yytext);}
{BLANKID}                    {printf("BLANKID\n");}
{ID}                         {printf("ID(%s)\n", yytext);}
" "                          {;}   
\t                           {;}
{new_line}                   {;}
.                            {;}


%%
int main()
{
yylex(); return 0;
}

int yywrap() {
return 1;
}