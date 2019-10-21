%{
    #include <stdio.h>
    #include <string.h>
    int yylex();
    void yyerror(const char *s);
    int i=0;
    int k=0;
%}
%token TIF TTHEN TWHILE TDO TEND TC0 TSTMT
%%
S   : If
| While
| stmt
;
If  :   TIF {printf("\n");for(k=0;k<i;k++)printf(" ");printf("if ");}
        TC0 {printf("c0 ");}
        TTHEN {printf("then ");i+=4;}
        S {i-=4;}
;
While   :   TWHILE {printf("\n");for(k=0;k<i;k++)printf(" ");printf("while ");}
            TC0 {printf("c0 ");}
            TDO {printf("do ");i+=4;}
            S {i-=4;}
            TEND {printf("\n");for(k=0;k<i;k++)printf(" ");printf("end ");}
;
stmt    :   TSTMT {printf("\n");for(k=0;k<i;k++)printf(" ");printf("stmt ");}
;
%%
int main() {
    yyparse();
    printf("\n");
}
