//
//  transform.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/28.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment31 이진트리

#include <fstream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

ifstream inp("transform.inp");
ofstream out("transform.out");

vector<int> tree;
string braket;
int root = 1;

void getBracket(int l, int r) {
    if(l == r) return;
    int size = 0;
    for(int i = l; i < r; i++) {
        if(tree[i] == root) {
            size = i;
            root += 1;
            break;
        }
    }
    out << "(";
    getBracket(l, size);
    out << ")";
    getBracket(size + 1, r);
}

void getInorder() {
    stack<int> S;
    int num = 1;
    for(int i = 0; i < braket.size(); i++) {
        if(braket[i] == '(') {
            S.push(num++);
        } else {
            out << S.top() << " ";
            S.pop();
        }
    }
}

int main() {
    int T;
    inp >> T;
    while(T--) {
        tree.clear();
        root = 1;
        int n, k;
        inp >> n >> k;
        out << n << " ";
        tree.resize(n);
        if(k == 0) {
            for(int i = 0; i < n; i++) inp >> tree[i];
            getBracket(0, n);
        }
        else {
            inp >> braket;
            getInorder();
        }
        out << "\n";
    }
    inp.close(); out.close();
    return 0;
}
