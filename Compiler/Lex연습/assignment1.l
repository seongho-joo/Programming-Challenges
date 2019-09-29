%{
    int count = 0;
%}
%s CMT
%%
"(" BEGIN CMT;
<CMT>")" BEGIN 0;
<CMT>a  count += 1;
<CMT>\n ;
.       ;
%%
int main() {
    yylex();
    printf("# of a : %d\n", count);
}
