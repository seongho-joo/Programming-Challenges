%{
    #include <stdio.h>
    #include <string.h>
    
    union Value {
        double num;
        char *var;
    };
    
    typedef struct Node {
        char kind[10];
        union Value value;
        struct Node* bro;
        struct Node* child;
    }Node;
    
    void preOrder(Node*);
    Node* createNode(char* kind);
    Node *root;
%}
%union {
    double dval;
    char *sval;
    struct Node *nval;
}
%token  TPROGRAM TMAIN TPROC TFUNC TRETURNS TVAR TINT TLONG TIF TTHEN TELSE TWHILE TFOR TTO TCALL TRETURN TBEGIN TEND TASS TAND TOR TNOT TLT TLE TGT TGE TNE TPLUS TMINUS TMUL TDIV

%token <dval> TNUMBER
%token <sval> TNAME
%type <nval> Program VarDecl DclList Decl VarList Type Var SubPgmList SubPgm ProcDecl FuncDecl FormParam Stmt AsgnStmt IfStmt ForStmt WhileStmt CallStmt RtrnStmt CompStmt Cond Rel Expr Fact FuncCall ParamList ExprList Term Name Number StmtList
%%
Program: TPROGRAM TNAME ';' SubPgmList TMAIN VarDecl CompStmt '.' {
            $$ = createNode("MAIN");
            $$->bro = $4;
            $$->child = $6;
            $6->bro = $7;
            preOrder($$);
        };
VarDecl: TVAR DclList ';' {
    $$ = createNode("VARDECL");
    $$->child = $2;
}
| { $$ = createNode("VARDECL"); }
;
DclList: DclList ';' Decl {
    root = $1;
    while(root->bro != NULL) root = root->bro;
    root->bro = $3;
    $$ = $1;
}
| Decl { $$ = $1; }
;
Decl: VarList ':' Type {
    $$ = createNode("DECL");
    $$->child = $1;
    root = $1;
    while(root->bro != NULL) root = root->bro;
    root->bro = $3;
}
;
VarList: VarList ',' Var {
    root = $1;
    while(root->bro != NULL) root = root->bro;
    root->bro = $3;
    $$ = $1;
}
| Var { $$ = $1; }
;
Type:   TINT { $$ = createNode("INT"); }
    |   TLONG { $$ = createNode("LONG"); }
;
Var: Name { $$ = $1; };

SubPgmList: SubPgmList SubPgm {
        root = $1;
        while(root->bro != NULL) root = root->bro;
        root->bro = $2;
        $$ = $1;
    }
| SubPgm { $$ = $1; }
| {$$ = NULL; }
;
SubPgm: ProcDecl { $$ = $1; }
| FuncDecl { $$ = $1; }
;
ProcDecl: TPROC Name '(' FormParam ')' VarDecl CompStmt {
    $$ = createNode("PROC");
    $$->child = $2;
    $2->bro = $4;
    $4->bro = $7;
};
FuncDecl: TFUNC Name '(' FormParam ')' TRETURNS '(' Type ')' VarDecl CompStmt{
    $$ = createNode("FUNC");
    $$->child = $2;
    $2->bro = $8;
    $8->bro = $4;
    $4->bro = $10;
    $10->bro = $11;
};
FormParam:  DclList{
    $$ = createNode("VARDECL");
    $$->child = $1;
}
| {$$ = createNode("VARDECL");}
;
Stmt: AsgnStmt { $$ = $1; }
| IfStmt { $$ = $1; }
| WhileStmt { $$ = $1; }
| ForStmt { $$ = $1; }
| CallStmt { $$ = $1; }
| RtrnStmt { $$ = $1; }
| CompStmt { $$ = $1; }
;
AsgnStmt: Var TASS Expr {
    $$ = createNode("ASSIGN");
    $$->child = $1;
    $1->bro = $3;
}
;
IfStmt: TIF '(' Cond ')' TTHEN Stmt {
    $$ = createNode("IF");
    $$->child = $3;
    $3->bro = $6;
}
| TIF '(' Cond ')' TTHEN Stmt TELSE Stmt {
    $$ = createNode("IF");
    $$->child = $3;
    $3->bro = $6;
    $6->bro = $8;
}
;
WhileStmt: TWHILE '(' Cond ')' Stmt {
    $$ = createNode("WHILE");
    $$->child = $3;
    $3->bro = $5;
}
;
ForStmt: TFOR '(' Var '=' Expr TTO Expr ')' Stmt {
    $$ = createNode("FOR");
    $$->child = $3;
    $3->bro = $5;
    $5->bro = $7;
    $7->bro = $9;
}
;
CallStmt: TCALL Name '(' ParamList ')' {
    $$ = createNode("PCALL");
    $$->child = $2;
    $2->bro = $4;
}
;
RtrnStmt: TRETURN '(' Expr ')' {
    $$ = createNode("RETRUN");
    $$->child = $3;
}
;
CompStmt: TBEGIN StmtList TEND {
    $$ = createNode("COMP");
    $$->child = $2;
}
;
StmtList: StmtList ';' Stmt {
    root = $1;
    while(root->bro != NULL) root = root->bro;
    root->bro = $3;
    $$ = $1;
}
| Stmt{ $$ = $1; };
Cond: Cond TAND Rel {
    $$ = createNode("AND");
    $$->child = $1;
    root = $1;
    while(root->bro != NULL) root = root->bro;
    root->bro = $3;
}
| Cond TOR Rel {
    $$ = createNode("OR");
    $$->child = $1;
    root = $1;
    while(root->bro != NULL) root = root->bro;
    root->bro = $3;
}
| TNOT Rel{
    $$ = createNode("NOT");
    $$->child = $2;
}
| Rel { $$ = $1; }
;
Rel : Expr TLT Expr {
    $$ = createNode("LT");
    $$->child = $1;
    $1->bro = $3;
}
| Expr TLE Expr {
    $$ = createNode("LE");
    $$->child = $1;
    $1->bro = $3;
}
| Expr TGT Expr{
    $$ = createNode("GT");
    $$->child = $1;
    $1->bro = $3;
}
| Expr TGE Expr {
    $$ = createNode("GE");
    $$->child = $1;
    $1->bro = $3;
}
| Expr TASS Expr {
    $$ = createNode("EQ");
    $$->child = $1;
    $1->bro = $3;
}
| Expr TNE Expr {
    $$ = createNode("LE");
    $$->child = $1;
    $1->bro = $3;
}
;
Expr: Expr TPLUS Term {
    $$ = createNode("PLUS");
    $$->child = $1;
    $1->bro = $3;
}
| Expr TMINUS Term {
    $$ = createNode("MINUS");
    $$->child = $1;
    $1->bro = $3;
}
| Term { $$ = $1; }
;
Term: Term TMUL Fact {
    $$ = createNode("TIMES");
    $$->child = $1;
    $1->bro = $3;
}
| Term TDIV Fact {
    $$ = createNode("DIVIDE");
    $$->child = $1;
    $1->bro = $3;
}
| Fact { $$ = $1; }
;
Fact: Var { $$ = $1; }
| Number { $$ = $1; }
| FuncCall { $$ = $1; }
| TMINUS Fact {
    $$ = createNode("NEG");
    $$->child = $2;
}
| '(' Expr ')' { $$ = $2; }
;
FuncCall: Name '(' ParamList ')'{
    $$ = createNode("FCALL");
    $$->child = $1;
    $1->bro = $3;
};
ParamList: ExprList { $$ = $1; }
| { $$ = NULL; };
ExprList: ExprList ',' Expr {
    root = $1;
    while(root->bro != NULL) root = root->bro;
    root->bro = $3;
    $$ = $1;
}
| Expr { $$ = $1; }
;
Name : TNAME {
    $$ = createNode("NAME");
    $$->value.var = yylval.sval;
}
Number : TNUMBER {
    $$ = createNode("NUMBER");
    $$->value.num = yylval.dval;
}
%%

Node* createNode(char* kind) {
    Node* new = (Node*)malloc(sizeof(Node));
    strcpy(new->kind, kind);
    new->bro = NULL;
    new->child = NULL;
    return new;
}
void preOrder(Node *root) {
    printf("%s ", root->kind);
    if(root->child != NULL) preOrder(root->child);
    if(root->bro != NULL) preOrder(root->bro);
}
int main() {
    yyparse();
    return(0);
}
