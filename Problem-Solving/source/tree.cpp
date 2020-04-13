/**
 * Assignment 15 -  트리 조정
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Vertex {
   public:
    int vertex;  // 정점
    int weight;  // 가중치
};
vector<vector<Vertex> > tree;
vector<int> weight;   // 루트로부터 자식의 거리
int len_MAX, result;  // 루투로부터 리프노드까지 최대거리, 수정한 가중치들의 합
// BFS를 이용한 트리의 리프노드 최대 거리 찾기
int find_MaxLength(int v, int len) {
    vector<bool> visit(tree.size(), false);
    queue<int> q;
    q.push(v);
    visit[v] = true;
    while (!q.empty()) {
        int here = q.front();
        q.pop();
        for (int i = 0; i < tree[here].size(); i++) {
            // 자식노드
            int there = tree[here][i].vertex;
            /* 방문하지 않았을 때 */
            if (!visit[there]) {
                visit[there] = true;
                q.push(there);
                /*부모노드를 방문 했을때*/
                if (weight[here] != 0) {
                    weight[there] = weight[here] + tree[here][i].weight;
                } else
                    weight[there] = tree[here][i].weight;
            }
        }
    }
    int w_MAX = 0;
    /*리프노드들의 최대거리*/
    for (int i = 0; i < weight.size(); i++) w_MAX = max(weight[i], w_MAX);
    return w_MAX;
}
// DFS알고리즘을 이용하여 리프노드의 거리를 구함
int find_length(int s, int w) {
    if (tree[s].size() != 0) {  // 자식이 존재할 때
        int W, W_MAX = 0;       // 자식의 가중치, 가중치 합
        for (int i = 0; i < tree[s].size(); i++) {
            // DFS 재귀 순회
            W = find_length(tree[s][i].vertex, w + tree[s][i].weight);
            W_MAX = max(W, W_MAX);
        }
        return W_MAX;  // 리프노드가 아닐 때 반환 값
    }
    return w;  // 자식이 없을 때 반환 값
}
// find_length와 같이 DFS를 순회를 이용하여 가중치 업데이트
void update_Weight(int s, int w) {
    if (tree[s].size() != 0) {
        int child_W;  // 자식노드의 거리
        for (int i = 0; i < tree[s].size(); i++) {
            // DFS알고리즘을 이용하여 자식의 리프노드의 최대거리를 구함
            child_W = find_length(tree[s][i].vertex, w + tree[s][i].weight);
            // 현재 정점의 최대 거리와 트리의 최대거리를 빼 줌
            int interval = len_MAX - child_W;
            // 현재 정점의 최대 거리를 트리의 최대거리로 갱신을 위해 더해줌
            tree[s][i].weight += interval;
            result += interval;  // 에지길이의 합
            update_Weight(tree[s][i].vertex,
                          w + tree[s][i].weight);  // DFS 재귀 순회
        }
    }
}
int main() {
    ifstream inp("tree.inp");
    ofstream out("tree.out");
    Vertex v;
    int T;
    inp >> T;
    while (T--) {
        int n;
        inp >> n;
        tree.resize(n);
        weight.resize(n);
        for (int i = 1; i < n; i++) {
            inp >> v.vertex >> v.weight;
            Vertex ver;
            ver.vertex = i, ver.weight = v.weight;
            tree[v.vertex].push_back(ver);  // 부모, 자식, 가중치
        }
        len_MAX = find_MaxLength(0, 0);
        update_Weight(0, 0);
        out << result << endl;
        tree.clear();
        weight.clear();
        len_MAX = 0;
        result = 0;
    }
    inp.close(), out.close();
    return 0;
}