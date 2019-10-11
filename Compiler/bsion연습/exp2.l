%{
#include <stdlib.h>
#include "exp2.tab.h"
extern double vbltables[26];
%}
%%
([0-9]+|[0-9]*\.[0-9]+) {yylval.dval = atof(yytext); return(NUMBER);}
[ \t]       ;
[a-z]       {yylval.vblno = yytext[0]-'a'; return NAME;}
"$"         {return 0;}
\n          |
.           {return(yytext[0]);}
