//
//  mice.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/30.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment20 - Jerry & Tom

#include <fstream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long lint;
struct Point{
    lint x, y;
    Point(): x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

const int holeMax = 51, miceMax = holeMax * 5 + 1;
const int MAX = holeMax + miceMax;
const int nMax = 1001;
const int INF = 987654321;

ifstream inp("mice.inp");
ofstream out("mice.out");
vector<vector<int> > adj;
int c[MAX][MAX], f[MAX][MAX];
int level[MAX], work[MAX];
Point house[nMax], hole[holeMax + 1], mice[miceMax];
int n, k, h, m, adj_size;

int ccw(Point& a, Point& b, Point& c) {
    lint ret = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if(ret > 0) return 1;
    else if(ret == 0) return 0;
    else return -1;
}

bool intersect(Point a, Point b, Point c, Point d) {
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);
    // 일직선 일 경우
    if(ab == 0 && cd == 0) {
        if(max(a.x, b.x) < min(c.x, d.x)) return false;
        if(min(a.x, b.x) > max(c.x, d.x)) return false;
        if(max(a.y, b.y) < min(c.y, d.y)) return false;
        if(min(a.y, b.y) > max(c.y, d.y)) return false;
        return true;
    }
    return ab <= 0 && cd <= 0;
}
// 쥐의 가시거리를 이용해 이분그래프를 만듦
void makeDipartiteGraph() {
    // 쥐
    for(int i = 0; i < m; i++) {
        // 쥐 구멍
        for(int j = 0; j < h; j++) {
            int cnt = 0;
            // 모서리
            for(int k = 0; k < n; k++) {
                int l = (k + 1) % n;
                 bool cross = intersect(mice[i], hole[j], house[k], house[l]);
                if(cross) cnt += 1;
            }
            if(cnt == 1) {
                int v = m + j + 1;
                adj[i + 1].push_back(v);
                adj[v].push_back(i + 1);
                c[i + 1][v] = 1;
            }
        }
    }
    // start, 쥐 간선연결
    for(int i = 1; i <= m; i++) {
        adj[0].push_back(i);
        adj[i].push_back(0);
        c[0][i] = 1;
    }
    // 구멍, sink 간선연결
    for(int i = m + 1; i <= m + h; i++) {
        adj[i].push_back(adj_size);
        adj[adj_size].push_back(i);
        c[i][adj_size] = k;
    }
}

void input() {
    adj.clear();
    memset(house, 0, sizeof(house));
    memset(hole, 0, sizeof(hole));
    memset(mice, 0, sizeof(mice));
    memset(c, 0, sizeof(c));
    memset(f, 0, sizeof(f));
    int x, y;
    
    inp >> n >> k >> h >> m;
    for(int i = 0; i < n; i++) {
       inp >> x >> y;
       house[i] = Point(x, y);
    }
    for(int i = 0; i < h; i++) {
       inp >> x >> y;
       hole[i] = Point(x, y);
    }
    for(int i = 0; i < m; i++) {
       inp >> x >> y;
       mice[i] = Point(x, y);
    }
    adj_size = m + h + 1;
    adj.resize(adj_size + 1);
}

bool setLevel() {
    fill(level, level + MAX, -1);
    queue<int> Q;
    Q.push(0);
    level[0] = 0;
    while(!Q.empty()) {
        int here = Q.front(); Q.pop();
        for(int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i];
            if(level[there] == -1 && c[here][there] - f[here][there] > 0) {
                level[there] = level[here] + 1;
                Q.push(there);
            }
        }
    }
    return level[adj_size] != -1;
}

int dinic(int here, int flow) {
    if(here == adj_size) return flow;
    for(int &i = work[here]; i < adj[here].size(); i++) {
        int next = adj[here][i];
        if(level[next] == level[here] + 1 && c[here][next] - f[here][next] > 0) {
            int ret = dinic(next, min(c[here][next] - f[here][next], flow));
            if(ret > 0) {
                f[here][next] += ret;
                f[next][here] -= ret;
                return ret;
            }
        }
    }
    return 0;
}


int main() {
    int T;
    inp >> T;
    while(T--) {
        input();
        makeDipartiteGraph();
        int total = 0;
        while(setLevel()) {
            fill(work, work + MAX, 0);
            while(true) {
                int ret = dinic(0, INF);
                if(ret == 0) break;
                total += ret;
            }
        }
        out << (total == m ? "Possible" : "Impossible") << "\n";
    }
    inp.close(); out.close();
    return 0;
}
