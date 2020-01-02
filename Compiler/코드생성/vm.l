%{
    #include "vm.tab.h"
%}
number  [0-9]*
word    [a-zA-Z][a-zA-Z0-9]*
%%
program     return(TPROGRAM);
main        return(TMAIN);
proc        return(TPROC);
func        return(TFUNC);
returns     return(TRETURNS);
var         return(TVAR);
int         return(TINT);
long        return(TLONG);
if          return(TIF);
then        return(TTHEN);
else        return(TELSE);
while       return(TWHILE);
for         return(TFOR);
to          return(TTO);
call        return(TCALL);
return      return(TRETURN);
begin       return(TBEGIN);
end         return(TEND);
"="         return(TASS);
"&"         return(TAND);
"|"         return(TOR);
"!"         return(TNOT);
"<"         return(TLT);
"<="        return(TLE);
">"         return(TGT);
">="        return(TGE);
"!="        return(TNE);
"+"         return(TPLUS);
"-"         return(TMINUS);
"*"         return(TMUL);
"/"         return(TDIV);
"("         return('(');
")"         return(')');
";"         return(';');
":"         return(':');
","         return(',');
"."         return('.');
{number}    {yylval.dval = atof(yytext); return(TNUMBER);}
{word}      {yylval.sval = strdup(yytext); return(TNAME);}
\\n         ;
\\t         ;
%%

