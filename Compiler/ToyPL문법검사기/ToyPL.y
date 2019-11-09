%{
    #include <stdio.h>
%}
%token  TPROGRAM TMAIN TPROC TFUNC TRETURNS TVAR TINT TLONG TIF TTHEN TELSE TWHILE TFOR TTO TCALL TRETURN TBEGIN TEND TASS TAND TOR TNOT TLT TLE TGT TGE TNE TPLUS TMINUS TMUL TDIV TNUMBER TWORD
%%
Program     : TPROGRAM TWORD ';' SubPgmList TMAIN VarDecl CompStmt '.'
;
VarDecl     : TVAR DclList ';'
|
;
DclList     : DclList ';' Decl
            | Decl
;
Decl        : VarList ':' Type
;
VarList     : VarList ',' Var
            | Var
;
Type        : TINT | TLONG;
Var         : TWORD;
SubPgmList  : SubPgmList SubPgm | ;
SubPgm      : ProcDecl | FuncDecl ;
ProcDecl    : TPROC TWORD '(' FormParam ')' VarDecl CompStmt;
FuncDecl    : TFUNC TWORD '(' FormParam ')' TRETURNS '(' Type ')'                    VarDecl CompStmt;
FormParam   : DclList | ;

Stmt        : AsgnStmt
            | IfStmt
            | WhileStmt
            | ForStmt
            | CallStmt
            | RtrnStmt
            | CompStmt
;
AsgnStmt    : Var TASS Expr
;
IfStmt      : TIF '(' Cond ')' TTHEN Stmt
            | TIF '(' Cond ')' TTHEN Stmt TELSE Stmt
;
WhileStmt   : TWHILE '(' Cond ')' Stmt
;
ForStmt     : TFOR '(' Var '=' Expr TTO Expr ')' Stmt
;
CallStmt    : TCALL TWORD '(' ParamList ')'
;
RtrnStmt    : TRETURN '(' Expr ')'
;
CompStmt    : TBEGIN StmtList TEND
;
StmtList    : StmtList ';' Stmt
            | Stmt;
Cond        : Cond TAND Rel | Cond TOR Rel
            | TNOT Rel | Rel
;
Rel         : Expr TLT Expr | Expr TLE Expr
            | Expr TGT Expr | Expr TGE Expr
            | Expr TASS Expr | Expr TNE Expr
;
Expr        : Expr TPLUS Term | Expr TMINUS Term
            | Term
;
Term        : Term TMUL Fact | Term TDIV Fact
            | Fact
;
Fact        : Var | TNUMBER | FuncCall
            | TMINUS Fact | '(' Expr ')'
;
FuncCall    : TWORD '(' ParamList ')';
ParamList   : ExprList | ;
ExprList    : ExprList ',' Expr | Expr
;
%%
int main() {
    yyparse();
    return(0);
}
