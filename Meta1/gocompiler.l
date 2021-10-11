/*  
    João Miguel Ferreira Castelo Branco Catré - 2019218953
    Sofia Botelho Vieira Alves - 2019227240
*/

/* ./gocompiler -l < factorial.dgo */

/* Comments */
num                     [0-9]
letter_m                  [a-z]
letter_M                  [A-Z]
sig                     [+|-]?
exp                     [e|E]{sig}{num}*
base                    [0b|0B|0|0o|0O|0x|0X] /*O undescore é para validar?*/
raw_strlit              "'"{.}"'"
inter_strlit            '"'{.}'"'
new_line                \r\n|\n|\r
Line_comments           ("//"."\n")
General_comments        ("/*".("\n"*)"*/")


/* Tokens */
ID          ({letter_m}|{letter_M}|"_")+(({letter_m}|{letter_M}|"_"|{num})*)  
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
RESERVED    "break"|"case"|"chan"|"const"|"continue"|"for"|"import"|"interface"|"map"|"package"|"range"|"return"|"select"|"struct"|"switch"|"type"|"var"|"++"|"--"


%%

/* Tokens */
{ID}        {printf(" ID(yytext) ");}
{STRLIT}    {printf(" STRLIT ");}
{INTLIT}    {printf(" INTLIT(yytext) ");}
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
{REALLIT}   {printf(" REALLIT ");}
{SEMICOLON} {printf(" SEMICOLON ");}
{COMMA}     {printf(" COMMA ");}
{ASSIGN}    {printf(" ASSIGN ");}
{STAR}      {printf(" STAR ");}
{DIV}       {printf(" DIV ");}
{MINUS}     {printf(" MINUS ");}
{PLUS}      {printf(" PLUS ");}
{EQ}        {printf(" EQ ");} 
{GE}        {printf(" GE ");}
{GT}        {printf(" GT ");}
{LBRACE}    {printf(" LBRACE ");}
{LE}        {printf(" LE ");}
{LPAR}      {printf(" LPAR ");}
{LSQ}       {printf(" LSQ ");}
{LT}        {printf(" LT ");}
{MOD}       {printf(" MOD ");}
{NE}        {printf(" NE ");}
{NOT}       {printf(" NOT ");}
{AND}       {printf(" AND ");}
{OR}        {printf(" OR ");}
{RBRACE}    {printf(" RBRACE ");}
{RPAR}      {printf(" RPAR ");}
{RSQ}       {printf(" RSQ ");}
{PACKAGE}   {printf(" PACKAGE ");}
{RETURN}    {printf(" RETURN ");}
{ELSE}      {printf(" ELSE ");}
{FOR}       {printf(" FOR ");}
{IF}        {printf(" IF ");}
{VAR}       {printf(" VAR ");}
{INT}       {printf(" INT ");}
{FLOAT32}   {printf(" FLOAT32 ");}
{BOOL}      {printf(" BOOL ");}
{STRING}    {printf(" STRING ");}
{PRINT}     {printf(" PRINT ");}
{PARSEINT}  {printf(" PARSEINT ");}
{FUNC}      {printf(" FUNC ");}
{CMDARGS}   {printf(" CMDARGS ");}
{RESERVED}  {printf(" RESERVED(yytext) ");}


/* Aceitar (e ignorar) os separadores de tokens */
.                   {;} 
new_line                  {;}
" "                 {;}   
\t                  {;}
/* Comments */
{Line_comments}         {;}
{General_comments}      {;}

%%
int main()
{
yylex(); return 0;
}
int yywrap() {
return 1;
}