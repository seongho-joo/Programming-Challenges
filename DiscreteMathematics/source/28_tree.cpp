#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

class Vertex {
public:
	int vertex; // ����
	int weight; // ����ġ
};
vector< vector<Vertex> > tree;
vector<int> weight; // ��Ʈ�κ��� �ڽ��� �Ÿ�
int len_MAX, result; // �����κ��� ���������� �ִ�Ÿ�, ������ ����ġ���� ��

int find_MaxLength(int v, int len) { // BFS�� �̿��� Ʈ���� ������� �ִ� �Ÿ� ã��
	vector<bool> visit(tree.size(), false);
	queue<int> q;
	q.push(v);
	visit[v] = true;
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (int i = 0; i < tree[here].size(); i++) {
			int there = tree[here][i].vertex; // �ڽĳ�� 
			if (!visit[there]) { /* �湮���� �ʾ��� �� */
				visit[there] = true;
				q.push(there);
				if (weight[here] != 0) { /*�θ��带 �湮 ������*/
					weight[there] = weight[here] + tree[here][i].weight;
				}
				else
					weight[there] = tree[here][i].weight;
			}
		}
	}
	int w_MAX = 0;
	for (int i = 0; i < weight.size(); i++) /*���������� �ִ�Ÿ�*/
		w_MAX = max(weight[i], w_MAX);
	return w_MAX;
}

int find_length(int s, int w) { // DFS�˰����� �̿��Ͽ� ��������� �Ÿ��� ����
	if (tree[s].size() != 0) { // �ڽ��� ������ ��
		int W, W_MAX = 0; // �ڽ��� ����ġ, ����ġ ��
		for (int i = 0; i < tree[s].size(); i++) {
			W = find_length(tree[s][i].vertex, w + tree[s][i].weight); // DFS ��� ��ȸ
			W_MAX = max(W, W_MAX);
		}
		return W_MAX; // ������尡 �ƴ� �� ��ȯ ��
	}
	return w; // �ڽ��� ���� �� ��ȯ ��
}

void update_Weight(int s, int w) { // find_length�� ���� DFS�� ��ȸ�� �̿��Ͽ� ����ġ ������Ʈ
	if (tree[s].size() != 0) {
		int child_W; // �ڽĳ���� �Ÿ�
		for (int i = 0; i < tree[s].size(); i++) {
			child_W = find_length(tree[s][i].vertex, w + tree[s][i].weight); // DFS�˰����� �̿��Ͽ� �ڽ��� ��������� �ִ�Ÿ��� ����
			int interval = len_MAX - child_W; // ���� ������ �ִ� �Ÿ��� Ʈ���� �ִ�Ÿ��� �� ��
			tree[s][i].weight += interval; // ���� ������ �ִ� �Ÿ��� Ʈ���� �ִ�Ÿ��� ������ ���� ������
			result += interval; // ���������� ��
			update_Weight(tree[s][i].vertex, w + tree[s][i].weight); // DFS ��� ��ȸ
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
			tree[v.vertex].push_back({ i, v.weight }); // �θ�, �ڽ�, ����ġ
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