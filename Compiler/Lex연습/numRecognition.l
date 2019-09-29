%%
[0-9]*  printf("number => %s (%d) \n", yytext, yyleng);
.	;
%%
int main() {
    yylex();
    printf("end\n");
}

