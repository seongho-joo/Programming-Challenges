//
//  flow.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/20.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment 16 Max Flow

#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 10000;
const int INF = 987654321;
ifstream inp("flow.inp");
ofstream out("flow.out");
int N;
vector<vector<int> > near;  // 인접행렬
int f[MAX][MAX];            // i -> j 최대용량
int c[MAX][MAX];            // i -> j 현재 흐르는 유량

void solve() {
    int total = 0, s = 0, e = N - 1;
    while(true) {
        int prev[MAX]; // 방문배열
        fill(prev, prev+MAX, -1);
        queue<int> Q;
        Q.push(s);
        while(!Q.empty() && prev[e] == -1) {
            int cur = Q.front(); Q.pop();
            for(int i = 0; i < near[cur].size(); i++) {
                int next = near[cur][i];
                if(c[cur][next] - f[cur][next] > 0 && prev[next] == - 1) {
                    Q.push(next);
                    prev[next] = cur; // 경로기억
                    if(next == e) break;
                }
            }
        }
        if(prev[e] == -1) break;
        
        int flow = INF;
        for(int i = e; i != s; i = prev[i])
            flow = min(flow, c[prev[i]][i] - f[prev[i]][i]);
        for(int i = e; i != s; i = prev[i]) {
            f[prev[i]][i] += flow;
            f[i][prev[i]] -= flow;
        }
        total += flow;
    }
    out << total << '\n';
}

int main() {
    int u, v, e;
    inp >> N;
    near.resize(N);
    while(inp >> u >> v >> e, u != -1) {
        c[u][v] = c[v][u] += e;
        near[u].push_back(v);
        near[v].push_back(u);
    }
    
    solve();
    
    inp.close(); out.close();
    return 0;
}
