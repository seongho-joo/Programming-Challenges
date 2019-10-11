%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
double vbltables[26];
%}
%union {
    double dval;
    int vblno;
}
%token <vblno> NAME;
%token <dval> NUMBER;
%type <dval> Fact Term Exp
%%
StmtList: StmtList Stmt'\n'
| Stmt'\n'
;

Stmt: NAME '=' Exp      {vbltables[$1] = $3;}
| Exp                   {printf("=%f\n", $1);}
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
| NAME                  {$$ = vbltables[$1];}
| '('Exp')'             {$$=$2;}
;
