//
//  scc.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/04.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment22 SCC 찾기 - 중간고사 대체 과제

#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

ifstream inp("scc.inp");
ofstream out("scc.out");

vector<vector<int> > adj;
vector<int> dfsn;
vector<bool> finished;
stack<int> S;
int n, m; // 정점 갯수, 간선 갯수
int cnt, ans;

int dfs(int cur) {
    dfsn[cur] = ++cnt;
    S.push(cur);
    
    int res = dfsn[cur];
    for(int i = 0; i < adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (dfsn[next] == 0) res = min(res,dfs(next));
        else if (!finished[next]) res = min(res, dfsn[next]);
    }

    if (res == dfsn[cur]) {
        while(true) {
            int t = S.top(); S.pop();
            finished[t] = true;
            if(t == cur) break;
        }
        ans += 1;
    }
    return res;
}

int main() {
    inp >> n >> m;
    adj.resize(n); dfsn.resize(n, 0);
    finished.resize(n, false);
    
    for(int i = 0; i < m; i++) {
        int x, y;
        inp >> x >> y;
        adj[x].push_back(y);
    }
    
    for(int i = 0; i < n; i++)
        if(dfsn[i] == 0) dfs(i);
    
    out << ans << "\n";
    
    inp.close(); out.close();
    return 0;
}
