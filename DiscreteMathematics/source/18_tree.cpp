#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;
#define MAX 1000000

vector<int> indegree;
vector<int> outdegree;

int TreeCheck() {
	int root = -1;
	for (int i = 0; i < outdegree.size() - 1; i++)
		if (outdegree[i] == outdegree[i + 1]) return -1;

	for (int i = 0, j = 0; i < indegree.size();) {
		while (i < indegree.size() - 1 && indegree[i] == indegree[i + 1]) i++;
		if (i < indegree.size()) {
			int p = indegree[i++];
			while (j < outdegree.size() - 1 && p > outdegree[j]) j++;
			if (p != outdegree[j]) {
				if (root != -1) return -1;
				root = p;
			}
		}
		else j++;
	}

	return root;
}

int main() {
	FILE *inp = fopen("tree.inp", "rt");
	FILE *out = fopen("tree.out", "wt");
	clock_t s, e;
	s = clock();
	int p, c;
	bool check = false;
	int tree_ch = 0;
	for (int i = 1;; i++) {
		indegree.reserve(MAX);
		outdegree.reserve(MAX);
		while (true) {
			fscanf(inp, "%d %d", &p, &c);
			if (p == -1) {
				e = clock();
				cout << ((e - s) / CLOCKS_PER_SEC) << endl;
				return 0;
			}
			else if (p == 0 && c == 0) break;
			indegree.push_back(p); outdegree.push_back(c);
		}
		sort(indegree.begin(), indegree.end()); // 부모 노드 정렬
		sort(outdegree.begin(), outdegree.end()); // 자식 노드 정렬
		fprintf(out, "Test Case %d: %d\n", i, TreeCheck());
		indegree.clear();
		outdegree.clear();
	}
	
	
	fclose(inp);
	fclose(out);
	return 0;
}