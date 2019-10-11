%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}
%token NUMBER
%%
Exp :   Exp '+' Term        {printf("rule 1\n");}
    |   Term                {printf("rule 2\n");}
    ;
Term    :   Term '*' Num    {printf("rule 3\n");}
        |   Num             {printf("rule 4\n");}
        ;
Num     :   NUMBER          {printf("rule 5\n");}
        ;
