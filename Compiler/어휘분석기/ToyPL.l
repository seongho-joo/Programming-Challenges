%s          CMT
num         [0-9]*
word        [a-zA-Z][a-zA-Z0-9]*
%%
"/*"        BEGIN CMT;
<CMT>{word} ;
<CMT>{num}  ;
<CMT>.      ;
<CMT>\n     ;
<CMT>"*/"   BEGIN 0;
program     printf("TPROGRAM");
main        printf("TMAIN");
proc        printf("TPROC");
func        printf("TFUNC");
returns     printf("TRETURNS");
var         printf("TVAR");
int         printf("TINT");
long        printf("TLONG");
if          printf("TIF");
then        printf("TTHEN");
else        printf("TELSE");
while       printf("TWHILE");
for         printf("TFOR");
to          printf("TTO");
call        printf("TCALL");
return      printf("TRETURN");
begin       printf("TBEGIN");
end         printf("TEND");

"<="        printf("TLE");
">="        printf("TGE");
"!="        printf("TNE");
"="         printf("TASS");
"&"         printf("TAND");
"|"         printf("TOR");
"!"         printf("TNOT");
"<"         printf("TLT");
">"         printf("TGT");
"+"         printf("TPLUS");
"-"         printf("TMINUS");
"*"         printf("TMUL");
"/"         printf("TDIV");

" "         ECHO;
"("         ECHO;
")"         ECHO;
":"         ECHO;
";"         ECHO;
"."         ECHO;
","         ECHO;

{word}      printf("TWORD");
{num}       printf("TNUMBER");
.           ;
%%
int main(){
    yylex();
}
