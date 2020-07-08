//
//  path.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/20.
//  Copyright © 2020 주성호. All rights reserved.
//
// Assignment 17 최대 합 경로 찾기

#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

ifstream inp("path.inp");
ofstream out("path.out");

struct Tree {
    int key, parent, left, right;
    Tree(): parent(-1), left(-1), right(-1), key(-1) {}
};

const int INF = -1987654321;
int T, N, MAX = INF;
vector<int> inorder, preorder;
vector<Tree> tree;
//  preorder로 주어진 인덱스번호로 트리 세팅
void setTree(int idx, int root) {
    if (tree[root].key == -1) {
        tree[root].key = idx;
        return;
    }
    if (tree[root].key > idx) {
        if (tree[root].left == -1) {
            tree[root].left = idx;
            tree[idx].parent = root;
        }
        setTree(idx, tree[root].left);
    } else {
        if (tree[root].right == -1) {
            tree[root].right = idx;
            tree[idx].parent = root;
        }
        setTree(idx, tree[root].right);
    }
}
// 트리 경로 중 최대 값을 구함
int maxSum(Tree t) {
    if(t.left == -1 && t.right == -1) {
        MAX = max(MAX, inorder[t.key]);
        return inorder[t.key];
    }
    int left = INF, right = INF;
    
    if (t.left != -1) left = maxSum(tree[t.left]);
    if (t.right != -1) right = maxSum(tree[t.right]);
    int tmp = left + right + inorder[t.key];
    // 단말 노드에서 단말 노드의 경로를 구하기 때문에 차수가 2가아니면 비교 안함
    if(t.left != -1 && t.right != -1)
        MAX = max(tmp, MAX);
    
    return max(left, right) + inorder[t.key];
}

int main() {
    inp >> T;
    while(T--) {
        MAX = INF;
        inorder.clear(); preorder.clear(); tree.clear();
        inp >> N;
        inorder.resize(N); tree.resize(N); preorder.resize(N);
        
        for(int i = 0; i < N; i++) inp >> inorder[i];
        for(int i = 0; i < N; i++) inp >> preorder[i];
        
        for(int i = 0; i < N; i++) setTree(preorder[i], preorder[0]);
        
        maxSum(tree[preorder[0]]);
        
        out << MAX << '\n';
    }
    
    inp.close(); out.close();
    return 0;
}
