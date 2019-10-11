%{
#include "calc.tab.h"
%}
%%
[0-9]+  return(NUMBER);
[ \t]   ;
\n      return(0);
\+      return('+');
\*      return('*');
.       { printf("'%c' : illegal character\n", yytext[0]); exit(-1); }
