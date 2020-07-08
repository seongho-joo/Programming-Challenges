//
//  service.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/27.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment21 - 의료봉사

#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 7602;
const int INF = 987654321;
ifstream inp("service.inp");
ofstream out("service.out");

vector<vector<int> > adj;
vector<int> c[MAX], f[MAX];
vector<int> location, level(MAX), work(MAX);
int N, P, M;
int source = 0, sink;

bool setLevel() {
    fill(level.begin(), level.end(), -1);
    queue<int> Q;
    Q.push(source);
    level[source] = 0;
    while(!Q.empty()) {
        int cur = Q.front(); Q.pop();
        for(int i = 0; i < adj[cur].size(); i++) {
            int there = adj[cur][i];
            if(level[there] == -1 && c[cur][there] - f[cur][there] > 0) {
                level[there] = level[cur] + 1;
                Q.push(there);
            }
        }
    }
    return level[sink] != -1;
}

int dinic(int cur, int e, int flow) {
    if(cur == e) return flow;
    for(int &i = work[cur]; i < adj[cur].size(); i++) {
        int next = adj[cur][i];
        if(level[next] == level[cur] + 1 && c[cur][next] - f[cur][next] > 0) {
            int ret = dinic(next, e, min(c[cur][next] - f[cur][next], flow));
            if(ret > 0) {
                f[cur][next] += ret;
                f[next][cur] -= ret;
                return ret;
            }
        }
    }
    return 0;
}

void init() {
    adj.clear();
    inp >> N >> P >> M;
    sink = N * P + N;
    location.resize(P + 1);
    for(int i = 1; i <= P; i++) {
        inp >> location[i]; // 해당 기간의 지역 개수
        sink += location[i];
    }
    sink = sink + 1;
    
    adj.resize(MAX);
    fill(c, c + MAX, vector<int>(MAX, 0));
    fill(f, f + MAX, vector<int>(MAX, 0));
    // source 연결
    for(int i = 1; i <= N; i++) {
        adj[0].push_back(i);
        adj[i].push_back(0);
        c[0][i] = M;
    }
    int j = N + 1;
    // A 와 P 연결
    for(int i = 1; i <= N; i++) {
        for(int k = 0; k < P; k++) {
            adj[i].push_back(j);
            adj[j].push_back(i);
            c[i][j] = 1;
            j += 1;
        }
    }
    // P 와 B 연결
    for(int i = 1; i <= N; i++) {
        int team_size;
        inp >> team_size;
        for(int j = 0; j < team_size; j++) {
            int x, y;
            inp >> x >> y;
            int u = N + (i - 1) * P + x;
            int v = N + N * P;
            for(int k = 1; k <= x - 1; k++) v += location[k];
            v += y;
//            adj[i].push_back(u); // A -> P 연결
            adj[u].push_back(v); // P -> B 연결
            adj[v].push_back(u);
            c[u][v] = 1;
        }
    }
    // sink 연결
    for(int i = N * P + N + 1; i < sink; i++) {
        adj[i].push_back(sink);
        adj[sink].push_back(i);
        c[i][sink] = 1;
    }

}

int main(){
    int T;
    inp >> T;
    
    while(T--) {
        init();
        while(setLevel()) {
            fill(work.begin(), work.end(), 0);
            while(true) {
                if(dinic(0, sink, INF) == 0) {
                    break;
                }
            }
        }
        bool flag = false;
        for(int i = N * P + N + 1; i < sink; i++) {
            if(f[sink][i] == 0) {
                flag = true;
                break;
            }
        }
        out << (flag ? "0" : "1") << "\n";
    }
    inp.close(); out.close();
    return 0;
}
