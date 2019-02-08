#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <map>
#define INF 987654321
#define MAX 10000
using namespace std;

ifstream inp;
ofstream out;
class Vertex {
public:
	int child, weight; // 정점, 가중치
	int eCnt; // 입력파일에 들어온 간선의 순서
};
class Info {
public:
	int dist; // 최단 거리 저장
	int chk; // 지나간 경로를 저장
	int eCnt; // 간선의 입력 순서를 저장
	bool visited;
};
vector< vector<Vertex> > tree;
vector<Info> gpData;
Info info;
class Graph {
public:
	vector<int> path; // 최단경로 저장
	void Init() { // 초기값 초기화
		info.dist = INF;
		info.visited = false;
		info.chk = -1;
		info.eCnt = -1;
	}
	void dijkstra() {
		Init(); // 초기값 초기화

		gpData.resize(tree.size(), info);
		gpData[0].dist = 0;
		queue<int> q;
		q.push(0);

		while (!q.empty()) {
			int cur = q.front();
			gpData[cur].visited = true;
			for (int i = 0; i < tree[cur].size(); i++) {
				Vertex near = tree[cur][i];
				int via = gpData[cur].dist + near.weight;

				if (gpData[near.child].dist > via) {
					gpData[near.child].dist = via;
					gpData[near.child].chk = cur;
					gpData[near.child].eCnt = near.eCnt;
					q.push(near.child);
				}
				else if (gpData[near.child].dist == via) {
					if (gpData[near.child].eCnt < near.eCnt) {
						gpData[near.child].chk = cur;
						gpData[near.child].eCnt = near.eCnt;
					}
				}
			}
			q.pop();
		}
	}

	void ShortedPath(int destination) {
		vector<int> path;
		path.reserve(MAX);
		path.push_back(destination);
		
		int cur = gpData[destination].chk;

		while (cur != -1) {
			path.push_back(cur);
			cur = gpData[cur].chk;
		}
		this->path = path;
	}

	void PrintPath() {
		for (int i = 1; i < gpData.size(); i++) {
			if (gpData[i].visited) {
				this->path.reserve(MAX);
				ShortedPath(i);
				for (int i = this->path.size() - 1; i >= 0; i--)
					out << "V" << this->path[i] << " ";
				out << "(" << gpData[i].dist << ")" << endl;
			}
			else
				out << "V0 V" << i << " (-1)" << endl;
		}
	}
};
int n, m; // 정점의 수, 간선의 수
int main() {
	inp.open("dijkstra.inp");
	out.open("dijkstra.out");
	Vertex vertex;
	Graph gp;

	inp >> n >> m;

	tree.resize(n);
	int u;
	int v, e, w;
	for (int i = 0; i < m; i++) {
		inp >> u >> vertex.child >> vertex.weight;
		vertex.eCnt = i;
		tree[u].push_back(vertex);
	}

	gp.dijkstra();
	gp.PrintPath();

	inp.close();
	out.close();
	return 0;
}