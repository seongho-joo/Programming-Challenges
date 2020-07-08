//
//  ball.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/21.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment3 Dropping Balls

#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("p679.inp");
ofstream out("p679.out");

const int MAX = 524289;
const int SIZE = 1048575;
int T, depth, I;
vector<bool> tree(SIZE);
long long cache[21][MAX];

int solution(int d, int D, int node) {
    /** 트리의 높이와 현재 탐색하는 높이와 같으면 노드번호 반환 */
    if (d == D) return node;
    /** 노드번호가 false 이면 왼쪽 서브트리 탐색 */
    if (!tree[node]) {
        tree[node] = true;
        return solution(d + 1, D, node * 2 + 1);
    }
    tree[node] = false;
    /** 노드번호가 true일 경우 오른쪽 서브트리 탐색 */
    return solution(d + 1, D, node * 2 + 2);
}

int main() {
    for (int i = 2; i < 21; i++) {
        tree.assign(SIZE, false);
        for (int j = 1; j < MAX; j++) cache[i][j] = solution(1, i, 0) + 1;
    }

    inp >> T;
    while (T--) {
        inp >> depth >> I;
        out << cache[depth][I] << '\n';
    }
    inp.close();
    out.close();
    return 0;
}
