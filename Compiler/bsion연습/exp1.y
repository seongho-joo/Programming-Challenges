%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}
%token NUMBER
%%
ExpList: ExpList Exp'\n'    {printf("=%d\n", $2);}
| Exp'\n'                   {printf("=%d\n", $1);}
;

Exp : Exp '+' Term      {$$=$1+$3;}
| Exp '-' Term          {$$=$1-$3;}
| Term                  {$$=$1;}
;

Term : Term '*' Fact    {$$=$1*$3;}
| Term '/' Fact         {$$=$1/$3;}
| Fact                  {$$=$1;}
;

Fact : NUMBER           {$$=$1;}
| '('Exp')'             {$$=$2;}
;
