//
//  factory.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/16.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment 27 무인공장

#include <algorithm>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

const int MAX = 40004;
ifstream inp("factory.inp");
ofstream out("factory.out");

struct Period {
    int start, end;
    Period() : start(0), end(0) {}
    Period(int s, int d) : start(s), end(s + d) {}
};

int N, d; // 기계 수, 검사 기간
vector<vector<int> > adj;
vector<Period> machine;
int dfsn[MAX], sn[MAX], cnt, scc;
bool finished[MAX];
stack<int> S;

int oppo(int num) { return num < N ? num + N : num - N; }

void makeGraph() {
    for(int i = 1; i <= N * 2; i++) {
        for(int j = 1; j <= N * 2; j++) {
            if(i != j) {
                if((machine[i].start <= machine[j].start && machine[i].end > machine[j].start)) {
                    adj[oppo(i)].push_back(j);  // not A -> B
                    adj[oppo(j)].push_back(i);  // not B -> A
                }
            }
        }
    }
}

int dfs(int cur) {
    dfsn[cur] = ++cnt;
    S.push(cur);
    
    int ret = dfsn[cur];
    for(int i = 0 ; i < adj[cur].size(); i++) {
        int next = adj[cur][i];
        if(dfsn[next] == 0) ret = min(ret, dfs(next));
        else if(!finished[next]) ret = min(ret, dfsn[next]);
    }
    
    if(ret == dfsn[cur]) {
        while(true) {
            int t = S.top(); S.pop();
            finished[t] = true;
            sn[t] = scc;
            if(t == cur) break;
        }
        scc += 1;
    }
    return ret;
}

void init() {
    adj.clear();
    machine.clear();
    scc = 0; cnt = 0;
    fill(dfsn, dfsn + MAX, 0);
    fill(sn, sn + MAX, 0);
    fill(finished, finished + MAX, false);
}

int main() {
    int T;
    inp >> T;
    for(int i = 1; i <= T; i++) {
        init();
        inp >> N >> d;
        
        adj.resize(N * 2 + 1);
        machine.resize(N * 2 + 1);
        
        for(int i = 1; i <= N; i++) {
            int s, f;
            inp >> s >> f;
            machine[i] = Period(s, d);
            machine[i + N] = Period(f, d);
        }
        
        makeGraph();
        
        for(int i = 1; i <= N * 2; i++) if(dfsn[i] == 0) dfs(i);

        bool flag = false;
        
        for (int i = 1; i < N; i++) {
            if (sn[i] == sn[i + N]) {
                flag = true;
                break;
            }
        }
        
        out << "Test Case #" << i << ": " << (flag ? "Impossible" : "Possible") << "\n";
    }
    
    inp.close(); out.close();
    return 0;
}
