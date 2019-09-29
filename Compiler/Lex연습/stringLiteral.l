string \"[^"]*\"
%%
{string}    printf("%s\n", yytext);
\n          ;
.           ;
%%
int main() {
    yylex();
}
