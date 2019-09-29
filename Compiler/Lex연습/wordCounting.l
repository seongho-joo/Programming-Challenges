%{
    int wordCount = 0;
%}
word    [^ \t\n]+
eol     \n
%%
{word}  {wordCount++; printf("%s ", yytext);}
{eol}   printf("\n");
.       ;
%%
int main() {
    yylex();
    printf("# of words: %d\n", wordCount);
}
