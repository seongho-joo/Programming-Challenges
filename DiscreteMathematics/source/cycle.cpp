#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

vector< vector<int> > tree;
vector<int> visited;

int oddCheck() { // BFS �˰���
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
			else if (visited[next] == visited[cur]) { // Ȧ�� ����Ŭ�� ���� �� ��
				return 1;
			}
		}
	}
	return 0; // Ȧ�� ����Ŭ�� �������� ����
}

int main() {
	//FILE *inp = fopen("cycle.inp", "rt");
	ifstream inp("cycle.inp");
	ofstream out("cycle.out");

	int T; // ����� ��
	inp >> T;
	int n, m; // ������ ��, ������ ��
	while (T--) {
		inp >> n >> m;
		tree.resize(m + 1); // ������ ���� ũ�� �ʱ�ȭ
		visited.resize(n + 1, -1);
		while (m--) {
			int v, u; // ���� -> ����
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