%{
    int ifCount = 0;
%}
word    [a-zA-Z]+
%%
if      ifCount += 1;
{word}  ;
.       ;
%%
int main() {
    yylex();
    printf("# of if statements : %d\n", ifCount);
}
