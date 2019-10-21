%{
#include "pp.tab.h"
%}
%%
if      {return(TIF);}
then    {return(TTHEN);}
while   {return(TWHILE);}
do      {return(TDO);}
end     {return(TEND);}
c0      {return(TC0);}
stmt    {return(TSTMT);}
.       ;
\n      {return 0;}
