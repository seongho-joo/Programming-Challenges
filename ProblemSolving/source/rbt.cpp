//
//  rbt.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/04.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignement23 RBT 구현 - 중간고사 대체 과제

#include <fstream>
#include <string>
using namespace std;

ifstream inp("rbt.inp");
ofstream out("rbt.out");

struct Node {
    int key;
    string color;
    Node *left, *right, *parent;
    Node() : key(-1), color("BLACK"), left(NULL), right(NULL), parent(NULL) {}
    Node(int key) : key(key), color("RED"), left(NULL), right(NULL), parent(NULL) {}
};

class RBT {
    Node *root;
public:
    RBT() { root = NULL; }
    
    void insert(int);
    void insert_fixup(Node*);
    void rotateRight(Node*);
    void rotateLeft(Node*);
    void remove(int);
    void removeNode(Node*, Node*, int);
    void remove_fixup(Node *);
    void print(int);
};

int main() {
    RBT tree;
    while(true) {
        char query;
        int key;
        inp >> query >> key;
        if (key == -1) break;
        if (query == 'i') tree.insert(key);
        else if (query == 'd') tree.remove(key);
        else tree.print(key);
    }
    
    inp.close(); out.close();
    return 0;
}

void RBT::insert(int key) {
    if(root == NULL) {
        root = new Node(key);
        root->color = "BLACK";
    }
    else {
        Node* temp = root;
        Node* nw = new Node(key);
        
        while(true) {
            if(temp->key > key) {
                if(temp->left == NULL) {
                    temp->left = nw;
                    nw->parent = temp;
                    break;
                } else temp = temp->left;
            } else {
                if(temp->right == NULL) {
                    temp->right = nw;
                    nw->parent = temp;
                    break;
                } else temp = temp->right;
            }
        }
        insert_fixup(nw);
    }
}

void RBT::insert_fixup(Node *z) {
    while(z != root && z->parent->color == "RED") {
        Node *g = z->parent->parent;
        Node *u = root;
        // z의 부모가 왼쪽자식일 때
        if(z->parent == g->left) {
            if(g->right != NULL) u = g->right;
            // case 1 : uncle의 색이 RED인 경우
            if(u->color == "RED") {
                z->parent->color = "BLACK";
                u->color = "BLACK";
                g->color = "RED";
                z = z->parent->parent;
            }
            // case 2 : uncle의 색이 BLACK인 경우
            else if(u->color == "BLACK")  {
                // z가 오른쪽 자식일 때 z의 부모에 대하여 leftRotate
                if(z == z->parent->right)
                    rotateLeft(z->parent);
                z->parent->color = "BLACK";
                g->color = "RED";
                rotateRight(g);
            }
        }
        // z의 부모가 오른쪽 자식일 때
        else {
            if(g->left != NULL) u = g->left;
            // case 1 : uncle의 색이 RED인 경우
            if(u->color == "RED") {
                z->parent->color = "BLACK";
                u->color = "BLACK";
                g->color = "RED";
                z = z->parent->parent;
            }
            // case 2 : uncle의 색이 BLACK인 경우
            else if(u->color == "BLACK")  {
                // z가 오른쪽 자식일 때 z의 부모에 대하여 leftRotate
                if(z == z->parent->left)
                    rotateRight(z->parent);
                z->parent->color = "BLACK";
                g->color = "RED";
                rotateLeft(g);
            }
        }
    }
    root->color = "BLACK";
}

void RBT::remove(int key) {
    Node *temp = root;
    Node *parent = temp;
    
    while(temp != NULL) {
        if(temp->key == key) {
            removeNode(parent, temp, key);
            break;
        }
        
        if(temp->key > key) {
            parent = temp;
            temp = temp->left;
        }
        else {
            parent = temp;
            temp = temp->right;
        }
    }
}

void RBT::removeNode(Node *parent, Node *cur, int key) {
    if(cur == NULL) return;
    
    if(cur->key == key) {
        // 단말노드
        if(cur->left == NULL && cur->right == NULL) {
            if(parent->key == cur->key) cur = NULL;
            else if(parent->right == cur) {
                remove_fixup(cur);
                cur->parent->right = NULL;
            }
            else {
                remove_fixup(cur);
                cur->parent->left = NULL;
            }
        }
        // 차수가 1인 노드
        else if(cur->left != NULL && cur->right == NULL) {
            int sw = cur->key;
            cur->key = cur->left->key;
            cur->left->key = sw;
            removeNode(cur, cur->left, key);
        }
        else if(cur->left == NULL && cur->right != NULL) {
            int sw = cur->key;
            cur->key = cur->right->key;
            cur->right->key = sw;
            removeNode(cur, cur->right, key);
        }
        // 차수가 2인 노드
        else {
            bool flag = false;
            Node *temp = cur->right;
            while(temp->left != NULL) {
                flag = true;
                parent = temp;
                temp = temp->left;
            }
            if(!flag) parent = cur;
            int sw = cur->key;
            cur->key = temp->key;
            temp->key = sw;
            removeNode(parent,temp, sw);
        }
    }
}

void RBT::remove_fixup(Node *z) {
    while(z->color == "BLACK" && z != root) {
        Node *w;
        /** z가 왼쪽 자식일 때*/
        if(z == z->parent->left) {
            if(z->parent->right != NULL) {
                w = z->parent->right;
                // case 1 : 형제노드가 RED일 때
                if (w->color == "RED") {
                    w->color = "BLACK";
                    z->parent->color = "RED";
                    rotateLeft(z->parent);
                    // 재정비
                    w = z->parent->right;
                }
                // case 2: w의 자식 모두 블랙일 경우
                if(w->left != NULL && w->right != NULL && w->left->color == "BLACK" && w->right->color == "BLACK") {
                    w->color = "RED";
                    z = z->parent;
                } else if (w->left == NULL && w->right == NULL) {
                    w->color = "RED";
                    z = z->parent;
                }
                // case 3: w의 오른쪽 자식이 블랙일 경우
                else if(w->right == NULL || w->right->color == "BLACK") {
                    w->color = "RED";
                    w->left->color = "BLACK";
                    rotateRight(w);
                    w = z->parent->right;
                }
                // case 4: w의 오른쪽 자식이 레드일 경우
                else if(w->right->color == "RED") {
                    w->color = z->parent->color;
                    z->parent->color = "BLACK";
                    w->right->color = "BLACK";
                    rotateLeft(z->parent);
                    z = root;
                }
            }
        }
        // 오른쪽 자식일 때
        else {
            if(z->parent->left != NULL) {
                w = z->parent->left;
                // case 1 : 형제노드가 RED일 때
                if (w->color == "RED") {
                    w->color = "BLACK";
                    z->parent->color = "RED";
                    rotateRight(z->parent);
                    // 재정비
                    w = z->parent->left;
                }
                // case 2: w의 자식 모두 블랙일 경우
                if(w->left != NULL && w->right != NULL && w->left->color == "BLACK" && w->right->color == "BLACK") {
                        w->color = "RED";
                        z = z->parent;
                }
                else if(w->left == NULL && w->right == NULL) {
                    w->color = "RED";
                    z = z->parent;
                }
                // case 3: w의 왼쪽 자식이 블랙일 경우
                else if(w->left == NULL ||w->left->color == "BLACK") {
                    w->color = "RED";
                    w->right->color = "BLACK";
                    rotateLeft(w);
                    w = z->parent->left;
                }
                // case 4: w의 왼쪽 자식이 레드일 경우
                else if(w->left->color == "RED") {
                    w->color = z->parent->color;
                    z->parent->color = "BLACK";
                    w->left->color = "BLACK";
                    rotateRight(z->parent);
                    z = root;
                }
            }
        }
    }
    z->color = "BLACK";
}

void RBT::rotateRight(Node *x) {
    Node *temp = new Node();
    if(x->left->right != NULL) temp->left = x->left->right;
    temp->right = x->right;
    temp->key = x->key;
    temp->color = x->color;
    x->key = x->left->key;
    x->color = x->left->color;
    x->right = temp;
    
    if(temp->left != NULL) temp->left->parent = temp;
    if(temp->right != NULL) temp->right->parent = temp;
    temp->parent = x;
       
    if(x->left->left != NULL) x->left = x->left->left;
    else x->left = NULL;
       
    if(x->left != NULL) x->left->parent = x;
}

void RBT::rotateLeft(Node *x) {
    Node* temp = new Node();
    if(x->right->left != NULL) temp->right = x->right->left;
    temp->left = x->left;
    temp->key = x->key;
    temp->color = x->color;
    x->key = x->right->key;
    x->color = x->right->color;
    x->left = temp;
    
    if(temp->left != NULL) temp->left->parent = temp;
    if(temp->right != NULL) temp->right->parent = temp;
    temp->parent = x;
    
    if(x->right->right != NULL) x->right = x->right->right;
    else x->right = NULL;
    
    if(x->right != NULL) x->right->parent = x;
}

void RBT::print(int key) {
    Node *temp = root;
    while(temp->key != key) {
        if(temp->key > key) temp = temp->left;
        else temp = temp->right;
    }
    out << "color(" << key << "): " << temp->color << "\n";
}
