#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

vector< vector<int> > tree;
vector<int> visited;

int oddCheck() { // BFS 알고리즘
	queue<int> q;
	visited[0] = 1;
	q.push(0);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < tree[cur].size(); i++) {
			int next = tree[cur][i];
			if (visited[next] == -1) {
				visited[next] = 1 - visited[cur];
				q.push(next);
			}
			else if (visited[next] == visited[cur]) { // 홀수 싸이클이 존재 할 때
				return 1;
			}
		}
	}
	return 0; // 홀수 싸이클이 존재하지 않음
}

int main() {
	//FILE *inp = fopen("cycle.inp", "rt");
	ifstream inp("cycle.inp");
	ofstream out("cycle.out");

	int T; // 경우의 수
	inp >> T;
	int n, m; // 정점의 수, 간선의 수
	while (T--) {
		inp >> n >> m;
		tree.resize(m + 1); // 간선의 수로 크기 초기화
		visited.resize(n + 1, -1);
		while (m--) {
			int v, u; // 정점 -> 정점
			inp >> v >> u;
			tree[u].push_back(v);
			tree[v].push_back(u);
		}
		if (oddCheck())
			out << "O" << endl;
		else
			out << "X" << endl;
		tree.clear();
		visited.clear();
	}
	inp.close();
	out.close();
	return 0;
}