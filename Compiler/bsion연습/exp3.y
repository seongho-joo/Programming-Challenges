%{
#include "symbol.h"
#include <stdio.h>
#include <string.h>
int yylex();
%}
%union {
    double dval;
    struct symtab *symp;
}
%token <symp> NAME;
%token <dval> NUMBER;
%type <dval> Fact Term Exp
%%
StmtList: StmtList Stmt'\n'
| Stmt'\n'
;

Stmt: NAME '=' Exp      {$1->value = $3;}
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
| NAME                  {$$ = $1->value;}
| '('Exp')'             {$$=$2;}
;
%%
struct symtab *symlook(char *s) {
    struct symtab *sp;
    for(sp = symtab; sp < &symtab[NSYMS]; sp++) {
        if(sp->name && !strcmp(sp->name, s)) return sp;
        if(!sp->name) {
            sp->name = strdup(s);
            return sp;
        }
    }
    yyerror("Too many symbols");
    exit(1);
}
