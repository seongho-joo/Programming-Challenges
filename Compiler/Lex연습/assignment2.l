%s CMT
%s comment
%%
"{" {ECHO; BEGIN CMT;}
<CMT>"/*"[a-zA-Z0-9]+"*/" ;
<CMT>"}" {ECHO; BEGIN 0;}
<CMT>.  ECHO;
.       ECHO;
%%
int main() {
    yylex();
}
