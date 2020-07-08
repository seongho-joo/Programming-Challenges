//
//  shoemaker.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/19.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment30 p10026(Shoemaker)

#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream inp("shoemaker.inp");
ofstream out("shoemaker.out");

struct Job {
    int time, pay, idx;
    Job() : time(0), pay(0), idx(0) {}
    Job(int day, int pay, int i) : time(day), pay(pay), idx(i) {}
};
vector<Job> job;

bool comp(Job a, Job b) {
    if(a.time * b.pay == b.time * a.pay) return a.idx < b.idx;
    return a.time * b.pay < b.time * a.pay;
}

int main() {
    int T, N;
    inp >> T;
    
    for(int i = 0; i < T; i++) {
        if(i != 0) out << "\n";
        job.clear();
        
        inp >> N;
        job.resize(N);
        for(int i = 0; i < N; i++) {
            int t, p;
            inp >> t >> p;
            job[i] = Job(t, p, i + 1);
        }
        sort(job.begin(), job.end(), comp);
        
        for(int i = 0; i < N; i++) out << job[i].idx << " ";
    }
    
    inp.close(); out.close();
    return 0;
}
