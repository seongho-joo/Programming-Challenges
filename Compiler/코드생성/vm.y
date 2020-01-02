%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #define MAXLEN 15
    
    union Value {
        int num;
        char *var;
    };
    typedef struct Addr {
        char name[MAXLEN];
        int addr;
    }Addr;
    typedef struct Node {
        char kind[MAXLEN];
        union Value value;
        struct Node* bro;
        struct Node* child;
    }Node;
    void preOrder(Node*);
    Node* createNode(char* kind);
    Node *root;
    
    /** 코드생성부분 */
    int countVar(Node* root);
    void codeR(Node* root);
    void codeL(Node* root);
    void code(Node* root);
    void codeGen(Node* root);
    int p = 0, v = 0, l = 0;
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
    $$->bro = $4; // SUBPGM
    $$->child = $6; // VARDECL
    $6->bro = $7; // COMP
    
    // preOrder($$);
    codeGen($$);
    // code($$);
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
    $$->child = $2; // NAME
    $2->bro = $4; // VARDECL
    $4->bro = $6; // VARDECL
    $6->bro = $7; // COMP
};
FuncDecl: TFUNC Name '(' FormParam ')' TRETURNS '(' Type ')' VarDecl CompStmt{
    $$ = createNode("FUNC") ;
    $$->child = $2; // NAME
    $2->bro = $8; // TYPE
    $8->bro = $4; // VARDECL
    $4->bro = $10; // VARDECL
    $10->bro = $11; // COMP
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
    $$ = createNode("RETURN");
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
int countVar(Node* root){
    int cnt = 0;
    Node *t_node1, *t_node2;
    
    if(root->child != NULL) {
        t_node1 = root->child;
        while(t_node1 != NULL) {
            t_node2 = t_node1->child;
            while(t_node2->bro != NULL) {
                t_node2 = t_node2->bro;
                cnt++;
            }
            t_node1 = t_node1->bro;
        }
    }
    return cnt;
}

void codeL(Node* root) {
    printf("lda p(%s); ", root->value.var);
}
void codeR(Node* root) {
    if(strcmp(root->kind, "NUMBER") == 0) {
        printf("ldc %d; ", root->value.num);
    } else if(strcmp(root->kind, "NAME") == 0) {
        codeL(root);
        printf("ind; ");
    } else if(strcmp(root->kind, "PLUS") == 0 ||
    strcmp(root->kind, "MINUS") == 0 ||
    strcmp(root->kind, "TIMES") == 0 ||
    strcmp(root->kind, "DVIDE") == 0) {
        codeR(root->child);
        codeR(root->child->bro);
        if(strcmp(root->kind, "PLUS") == 0) printf("add; ");
        else if(strcmp(root->kind, "MINUS") == 0) printf("sub; ");
        else if(strcmp(root->kind, "TIMES") == 0) printf("mul; ");
        else if(strcmp(root->kind, "DVIDE") == 0) printf("div; ");
    } else if(strcmp(root->kind, "NEG") == 0) {
        codeR(root->child);
        printf("neg; ");
    } else if(strcmp(root->kind, "EQ") == 0 ||
    strcmp(root->kind, "NE") == 0 ||
    strcmp(root->kind, "GT") == 0 ||
    strcmp(root->kind, "GE") == 0 ||
    strcmp(root->kind, "LT") == 0 ||
    strcmp(root->kind, "LE") == 0 ) {
        codeR(root->child);
        codeR(root->child->bro);
        if(strcmp(root->kind, "EQ") == 0) printf("equ; ");
        else if(strcmp(root->kind, "NE") == 0) printf("neq; ");
        else if(strcmp(root->kind, "GT") == 0) printf("grt; ");
        else if(strcmp(root->kind, "GE") == 0) printf("geq; ");
        else if(strcmp(root->kind, "LT") == 0) printf("les; ");
        else if(strcmp(root->kind, "LE") == 0) printf("leq; ");
    } else if(strcmp(root->kind, "FCALL") == 0) {
        printf("mst; ");
        Node* t_node = root->child->bro;
        p = 0;
        while(t_node != NULL) {
            codeR(t_node);
            p++;
            t_node = t_node->bro;
        }
        printf("cup %d l%s ",p, root->child->value.var);
    }
}
void code(Node* root) {
    Node* tmp;
    int temp;
    if(strcmp(root->kind, "MAIN") == 0) {
        v = 0;
        v = countVar(root->child);
        printf("ssp %d; ", v + 2);
        code(root->child->bro);
        printf("stp ");
    } else if(strcmp(root->kind, "ASSIGN") == 0) {
        codeL(root->child);
        codeR(root->child->bro);
        printf("sto; ");
    } else if(strcmp(root->kind, "IF") == 0) {
        codeR(root->child);
        printf("fjp l%d", l);
        code(root->child->bro);
        temp = l;
        /** if then else 문 */
        if(root->child->bro->bro != NULL) {
            temp++;
            printf("ujp l%d; l%d: ", l + 1, l);
            l += 2;
            code(root->child->bro->bro);
        } else {
            l++;
            printf("l%d;", temp);
        }
    } else if(strcmp(root->kind, "WHILE") == 0) {
        printf("l%d: ", l);
        codeR(root->child);
        temp = l++;
        printf("fjp l%d; ", l);
        code(root->child->bro);
        printf("ujp l%d; l%d:", temp, l);
        l++;
    } else if(strcmp(root->kind, "FOR") == 0) {
        codeL(root->child);
        codeR(root->child->bro);
        printf("sto; l%d: ", l);
        temp = l++;
        codeR(root->child);
        codeR(root->child->bro->bro);
        printf("leq; fjp l%d; ", l);
        
        code(root->child->bro->bro->bro);
        codeL(root->child);
        codeR(root->child->bro);
        printf("ldc 1; add; sto; ujp l%d; l%d: ", temp, l);
        l++;
    } else if(strcmp(root->kind, "PCALL") == 0) {
        printf("mst; ");
        tmp = root->child->bro;
        p = 0;
        while(tmp != NULL) {
            codeR(tmp);
            p++;
            tmp = tmp->bro;
        }
        printf("cup %d l%s ", p, root->child->value.var);
    } else if(strcmp(root->kind, "PROC") == 0) {
        v = p = 0;
        p = countVar(root->child->bro);
        v = countVar(root->child->bro->bro);
        printf("l%s: ssp %d; ", root->child->value.var, p + v + 2);
        code(root->child->bro->bro->bro);
        printf("retp; ");
    } else if(strcmp(root->kind, "FUNC") == 0) {
        v = p = 0;
        v = countVar(root->child->bro->bro->bro);
        p = countVar(root->child->bro->bro);
        printf("l%s: ssp %d; ", root->child->value.var, p + v + 2);
        code(root->child->bro->bro->bro->bro);
        printf("reft; ");
    } else if(strcmp(root->kind, "RETURN") == 0) {
        codeR(root->child);
        printf("str 0; reft ");
    } else if(strcmp(root->kind, "COMP") == 0) {
        tmp = root->child;
        while(tmp != NULL) {
            code(tmp);
            tmp = tmp->bro;
        }
    }
}
void codeGen(Node* root) {
    Node* tmp = root->bro;
    while(tmp != NULL) {
        code(tmp);
        tmp = tmp->bro;
        if(tmp == NULL) break;
    }
    code(root);
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
