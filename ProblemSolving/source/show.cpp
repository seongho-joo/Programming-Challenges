//
//  show.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/12.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment 25 TV Show

#include <fstream>
#include <stack>
#include <vector>
using namespace std;

ifstream inp("show.inp");
ofstream out("show.out");

const int MAX = 10001;
vector<vector<int> > adj;
bool finished[MAX];
int dfsn[MAX], sn[MAX];
int bulb[3];
stack<int> S;
int cnt, scc, k;

int oppo(int n) { return n > k ? n - k : n + k; }

void makeAdj() {
    for(int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;
        adj[oppo(bulb[i])].push_back(bulb[j]); // not A -> B
        adj[oppo(bulb[j])].push_back(bulb[i]); // not B -> A
    }
}

void input() {
    for(int i = 0; i < 3; i++) {
        int num; char color;
        inp >> num >> color;
        // Blue는 true, Red는 false로 취급
        if(color == 'B') bulb[i] = num;
        else bulb[i] = num + k;
    }
    makeAdj();
}

int dfs(int cur) {
    dfsn[cur] = ++cnt;
    S.push(cur);
    
    int res = dfsn[cur];
    for(int i = 0; i < adj[cur].size(); i++) {
        int next = adj[cur][i];
        if(dfsn[next] == 0) res = min(res, dfs(next));
        else if(!finished[next]) res = min(res, dfsn[next]);
    }
    
    if(res == dfsn[cur]) {
        while(true) {
            int t = S.top(); S.pop();
            finished[t] = true;
            sn[t] = scc;
            if(t == cur) break;
        }
        scc += 1;
    }
    return res;
}

int main() {
    int T;
    inp >> T;
    
    while(T--) {
        scc = 0; cnt = 0;
        adj.clear();
        fill(finished, finished + MAX, false);
        fill(dfsn, dfsn + MAX, 0);
        fill(sn, sn + MAX, 0);
        int n;
        inp >> k >> n;
        adj.resize(k * 2 + 1);
        while(n--) input();
        
        for(int i = 1; i <= k * 2; i++)
            if(dfsn[i] == 0) dfs(i);
        bool flag = false;
        for(int i = 1; i <= k; i++) {
            if(sn[i] == sn[i + k]) {
                flag = true;
                break;
            }
        }
        out << (flag ? -1 : 1) << '\n';
    }
    
    inp.close(); out.close();
    return 0;
}
