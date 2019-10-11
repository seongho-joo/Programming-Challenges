%{
#include <stdlib.h>
#include "symbol.h"
#include "exp3.tab.h"
%}
%%
([0-9]+|[0-9]*\.[0-9]+) {yylval.dval = atof(yytext); return(NUMBER);}
[ \t]       ;
[A-Za-z][A-Za-z0-9]*    {yylval.symp = symlook(yytext); return NAME;}
"$"         {return 0;}
\n          |
.           {return(yytext[0]);}
