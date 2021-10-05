/*  
    João Miguel Ferreira Castelo Branco Catré - 2019218953
    Sofia Botelho Vieira Alves - 2019227240
*/

/* ./gocompiler -l < factorial.dgo */

/* Comments */
pos                     [0-9]
alfa_m                  [a-z]
alfa_M                  [A-Z]
sig                     [+|-]?
exp                     [e|E]{sig}{num}*
base                    [0b|0B|0|0o|0O|0x|0X] /*O undescore é para validar?*/
Line_comments           ("//"."\n")
General_comments        ("/*".("\n"*)"*/")


/* Tokens */
ID          ((alfa_m*)|(alfa_M*)|("_")*|({num}*))+ 
STRLIT      [^"\r""\n"\"]+         /*Especificar erro lexical caso encontre seq escape diferentes das referidas*/ 
INTLIT      (base*({num}*|[A-F]*|[a-f]*))+
REALLIT     ({sig}({num}+)"."({num}*)(exp))|{sig}("."([0.9]+)exp)|({sig}{num}+exp)
SEMICOLON   ";"
COMMA       ","
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
RESERVED    "" /*???*/


%%
/* Comments */
{Line_comments}         {printf("Line comments");}
{General_comments}      {printf("General comments");}

/* Tokens */
{ID}        {printf(" ID ");}
{STRLIT}    {printf(" STRLIT ");}
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
{REALLIT}   {printf(" reallit ");}
{SEMICOLON} {printf(" semicolon ");}
{COMMA}     {printf(" comma ");}
{ASSIGN}    {printf(" assign ");}
{STAR}      {printf(" star ");}
{DIV}       {printf(" div ");}
{MINUS}     {printf(" minus ");}
{PLUS}      {printf(" plus ");}
{EQ}        {printf(" eq ");} 
{GE}        {printf(" ge ");}
{GT}        {printf(" gt ");}
{LBRACE}    {printf(" lbrace ");}
{LE}        {printf(" le ");}
{LPAR}      {printf(" lpar ");}
{LSQ}       {printf(" lsq ");}
{LT}        {printf(" lt ");}
{MOD}       {printf(" MOD ");}
{NE}        {printf(" ne ");}
{NOT}       {printf(" not ");}
{AND}       {printf(" and ");}
{OR}        {printf(" or ");}
{RBRACE}    {printf(" rbrace ");}
{RPAR}      {printf(" rpar ");}
{RSQ}       {printf(" rsq ");}
{PACKAGE}   {printf(" package ");}
{RETURN}    {printf(" return ");}
{ELSE}      {printf(" else ");}
{FOR}       {printf(" for ");}
{IF}        {printf(" if ");}
{VAR}       {printf(" var ");}
{INT}       {printf(" int ");}
{FLOAT32}   {printf(" float32 ");}
{BOOL}      {printf(" bool ");}
{STRING}    {printf(" string ");}
{PRINT}     {printf(" print ");}
{PARSEINT}  {printf(" parseint ");}
{FUNC}      {printf(" func ");}
{CMDARGS}   {printf(" cmdargs ");}
{RESERVED}  {printf(" reserved ");}


/* Aceitar (e ignorar) os separadores de tokens */
.                   {;} 
\n                  {;}
" "                 {;}   
\t                  {;}

%%
int main()
{
yylex(); return 0;
}
int yywrap() {
return 1;
}