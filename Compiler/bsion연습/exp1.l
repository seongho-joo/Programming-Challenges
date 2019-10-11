%{
#include <stdlib.h>
#include "exp1.tab.h"
extern int yylval;
%}
%%
[0-9]+      {yylval = atoi(yytext); return(NUMBER);}
[ \t]       ;
"$"         {return 0;}
\n          |
.           {return(yytext[0]);}
