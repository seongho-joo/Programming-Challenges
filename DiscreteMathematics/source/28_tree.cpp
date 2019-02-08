#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class Vertex {
public:
	int vertex; // 정점
	int weight; // 가중치
};
vector< vector<Vertex> > tree;
vector<int> weight; // 루트로부터 자식의 거리
int len_MAX, result; // 루투로부터 리프노드까지 최대거리, 수정한 가중치들의 합

int find_MaxLength(int v, int len) { // BFS를 이용한 트리의 리프노드 최대 거리 찾기
	vector<bool> visit(tree.size(), false);
	queue<int> q;
	q.push(v);
	visit[v] = true;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (int i = 0; i < tree[here].size(); i++) {
			int there = tree[here][i].vertex; // 자식노드 
			if (!visit[there]) { /* 방문하지 않았을 때 */
				visit[there] = true;
				q.push(there);
				if (weight[here] != 0) { /*부모노드를 방문 했을때*/
					weight[there] = weight[here] + tree[here][i].weight;
				}
				else
					weight[there] = tree[here][i].weight;
			}
		}
	}
	int w_MAX = 0;
	for (int i = 0; i < weight.size(); i++) /*리프노드들의 최대거리*/
		w_MAX = max(weight[i], w_MAX);
	return w_MAX;
}

int find_length(int s, int w) { // DFS알고리즘을 이용하여 리프노드의 거리를 구함
	if (tree[s].size() != 0) { // 자식이 존재할 때
		int W, W_MAX = 0; // 자식의 가중치, 가중치 합
		for (int i = 0; i < tree[s].size(); i++) {
			W = find_length(tree[s][i].vertex, w + tree[s][i].weight); // DFS 재귀 순회
			W_MAX = max(W, W_MAX);
		}
		return W_MAX; // 리프노드가 아닐 때 반환 값
	}
	return w; // 자식이 없을 때 반환 값
}

void update_Weight(int s, int w) { // find_length와 같이 DFS를 순회를 이용하여 가중치 업데이트
	if (tree[s].size() != 0) {
		int child_W; // 자식노드의 거리
		for (int i = 0; i < tree[s].size(); i++) {
			child_W = find_length(tree[s][i].vertex, w + tree[s][i].weight); // DFS알고리즘을 이용하여 자식의 리프노드의 최대거리를 구함
			int interval = len_MAX - child_W; // 현재 정점의 최대 거리와 트리의 최대거리를 빼 줌
			tree[s][i].weight += interval; // 현재 정점의 최대 거리를 트리의 최대거리로 갱신을 위해 더해줌
			result += interval; // 에지길이의 합
			update_Weight(tree[s][i].vertex, w + tree[s][i].weight); // DFS 재귀 순회
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
			tree[v.vertex].push_back({ i, v.weight }); // 부모, 자식, 가중치
		}
		len_MAX = find_MaxLength(0, 0);
		update_Weight(0, 0);
		out << result << endl;
		tree.clear();
		weight.clear();
		len_MAX = 0;
		result = 0;
	}
	inp.close(); out.close();
	return 0;
}