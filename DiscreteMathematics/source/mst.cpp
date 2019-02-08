#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#define MAX 20001
using namespace std;

typedef struct Result {
	int nodeCount, total_cost;
}Result;

vector<pair<int, int> > graph[MAX];
vector<int> visited(MAX, 0);
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > tail;
vector<Result> result;
Result res;

int nodeCount;
bool compare(const Result& x, const Result& y) {
	if (x.nodeCount == y.nodeCount) return x.total_cost < y.total_cost;
	else return x.nodeCount < y.nodeCount;
}
void PrimAlgorithm(int s, int n) {
	nodeCount = 0;
	if (visited[s]) return;

	visited[s] = 1;

	for (int i = 0; i < graph[s].size(); i++) {
		int next = graph[s][i].first;
		int nextCost = graph[s][i].second;
		tail.push(make_pair(nextCost, next));
	}

	int sum = 0;

	while (!tail.empty()) {
		int here = tail.top().second;
		int hereCost = tail.top().first;
		tail.pop();
		/* 이미 방문한 정점은 무시 */
		if (visited[here]) continue;
		
		visited[here] = 1;
		sum += hereCost;
		for (int i = 0; i < graph[here].size(); i++) {
			int there = graph[here][i].first;
			int thereCost = graph[here][i].second;
			tail.push(make_pair(thereCost, there));
		}
	}

	for (int i = 0; i < n; i++) {
		if (visited[i] == 1) {
			nodeCount++; // 노드개수 카운트
			visited[i] = -1;
		}
	}
	if (nodeCount == 0) nodeCount++; // 정점에 연결된 간선이 없을시 +1
	res.nodeCount = nodeCount;
	res.total_cost = sum;
	result.push_back(res);
}

int main() {
	ifstream inp("mst.inp");
	ofstream out("mst.out");

	int n = 0, m = 0; // 정점의 수, 간선의 수
	inp >> n >> m;
	int u = 0 , v = 0, w = 0;
	result.reserve(n);
	while (m--) {
		inp >> u >> v >> w;
		graph[u].push_back(make_pair(v, w));
		graph[v].push_back(make_pair(u, w));
	}
	for (int i = 0; i < n; i++) {
		PrimAlgorithm(i, n);
	}
	sort(result.begin(), result.end(), compare);
	for (int i = 0, n = result.size(); i < n; i++)
		out << result[i].nodeCount << " " << result[i].total_cost << endl;

	inp.close();
	out.close();
	return 0;
}
