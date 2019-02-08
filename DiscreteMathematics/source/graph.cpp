#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

int DFS_sum, BFS_sum;
int n, m; // 정점의 개수, 엣지의 개수
int v, u, w; // 정점, 엣지, 가중치
vector< vector<int> > weight; // 가중치 설정
vector< vector<int> > tree; // 그래프 정점 연결
vector<bool> visited;
void sortGraph() { // 그래프 정렬 함수
	for (int i = 0; i < n; i++)
		sort(tree[i].begin(), tree[i].end());
}

void DFS(int s) { // DFS 알고리즘
	visited[s] = true;
	for (int i = 0; i < tree[s].size(); i++) {
		int next = tree[s][i];
		if (visited[next] == false && weight[s][next] !=0) {
			DFS_sum += weight[s][next];
			DFS(next);
		}
	}
}
void BFS(int s) { // BFS 알고리즘
	queue<int> q;
	visited[s] = true;
	q.push(s);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < tree[cur].size(); i++) {
			int next = tree[cur][i];
			if (!visited[next]) {
				visited[next] = true;
				q.push(next);
				BFS_sum += weight[next][cur];
			}
		}
	}
}

int main() {
	ifstream inp("graph.inp");
	ofstream out("graph.out");
	int T;
	int num, s; // 시작점 개수
	inp >> T;
	while (T--) {
		inp >> n >> m;
		tree.resize(n);
		weight.assign(n, vector<int>(n, 0));
		for (int i = 0; i < m; i++) {
			inp >> v >> u >> w;
			weight[v][u] = w;
			weight[u][v] = w;
			tree[v].push_back(u);
			tree[u].push_back(v);
		}
		sortGraph(); // 순차적으로 접근하기 위해 정렬
		inp >> num;
		for (int i = 0; i < num; i++) {
			inp >> s;
			visited = vector<bool>(n, false);
			DFS(s);
			visited = vector<bool>(n, false);
			BFS(s);
			out << "n=" << n << " m=" << m << " start=" << s << " DFS:" << DFS_sum << " BFS:" << BFS_sum << endl;
			DFS_sum = 0; BFS_sum = 0;
		}
		tree.clear();
		weight.clear();
	}
	inp.close();
	out.close();
	return 0;
}
