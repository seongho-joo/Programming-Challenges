/**
 * Assignment 19 - MST
 */
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
#define INF 987654321
using namespace std;

struct Vertex {
    int u, v, w, index;
};
struct Edge {
    int v, w, index;
};

ifstream inp("mst.inp");
ofstream out("mst.out");
vector<Vertex> graph;
vector<vector<Edge> > near;
int n, m;

bool compare(Vertex& x, Vertex& y) {
    if (x.w == y.w) return x.index < y.index;
    return x.w < y.w;
}
struct cmp {
    bool operator()(Edge& x, Edge& y) {
        if (x.w == y.w) return x.index > y.index;
        return x.w > y.w;
    }
};

void Init();
void Kruskal();
void Prim(int s);

int main() {
    inp >> n >> m;
    graph.reserve(m);
    near.resize(n);

    Init();
    Kruskal();
    Prim(0);
    Prim(n / 2);
    Prim(n - 1);

    inp.close();
    out.close();
    return 0;
}

void Init() {
    Vertex v;
    Edge e;
    for (int i = 0; i < m; i++) {
        inp >> v.u >> v.v >> v.w;
        v.index = i;
        graph.push_back(v);
        e.v = v.v;
        e.index = i;
        e.w = v.w;
        near[v.u].push_back(e);
        e.v = v.u;
        near[v.v].push_back(e);
    }
    sort(graph.begin(), graph.end(), compare);
}

int find(vector<int>& root, int i) {
    if (root[i] == i)
        return i;
    else
        return find(root, root[i]);
}

void Union(vector<int>& root, int i, int j) {
    int parent = find(root, i), child = find(root, j);
    root[child] = parent;
}

bool checkCycle(vector<int>& root, int x, int y) {
    x = find(root, x);
    y = find(root, y);

    if (x == y)
        return true;
    else
        return false;
}

void Kruskal() {
    vector<int> cycle, seq;
    int edge = 0;
    cycle.resize(n + 1);
    seq.reserve(n);
    for (int i = 1; i < n + 1; i++) cycle[i] = i;

    for (int i = 0; i < m; i++) {
        if (!checkCycle(cycle, graph[i].u, graph[i].v)) {
            edge += graph[i].w;
            seq.push_back(graph[i].index);
            Union(cycle, graph[i].u, graph[i].v);
        }
    }
    out << "Tree edges by Kruskal algorithm: " << edge << '\n';
    for (int i = 0; i < seq.size(); i++) out << seq[i] << '\n';
}

void Prim(int s) {
    int edge = 0;
    Edge e;
    vector<bool> visited;
    priority_queue<Edge, vector<Edge>, cmp> dist;
    vector<int> seq;
    visited.resize(n, false);
    seq.reserve(n);

    visited[s] = true;

    for (int i = 0; i < near[s].size(); i++) {
        e.v = near[s][i].v;
        e.w = near[s][i].w;
        e.index = near[s][i].index;
        dist.push(e);
    }

    while (!dist.empty()) {
        int cur = dist.top().v;
        int curW = dist.top().w;
        int curIndex = dist.top().index;
        dist.pop();

        if (visited[cur]) continue;

        visited[cur] = true;
        edge += curW;
        seq.push_back(curIndex);

        for (int i = 0; i < near[cur].size(); i++) {
            e.v = near[cur][i].v;
            e.w = near[cur][i].w;
            e.index = near[cur][i].index;
            dist.push(e);
        }
    }

    out << "Tree edges by Prim algorithm with starting vertex " << s << ": "
        << edge << "\n";
    for (int i = 0; i < seq.size(); i++) out << seq[i] << '\n';
}