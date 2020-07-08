//
//  2ndjj.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/06/22.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment39 Second Level Jolly Jumpers(기말고사 2)

#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

ifstream inp("2ndjj.inp");
ofstream out("2ndjj.out");

vector<int> arr, first, second;

void getJolly(int n, vector<int> v, vector<int>& ret) {
    for(int i = 0; i < n - 1; i++) ret[i] = abs(v[i] - v[i + 1]);
}

bool checkArray(vector<int> v) {
    sort(v.begin(), v.end());
    for(int i = 0; i < v.size() - 1; i++)
        if(v[i] + 1 != v[i + 1]) return false;
    return true;
}

void solve(int n) {
    getJolly(n, arr, first);
    getJolly(n - 1, first, second);
    
    if(checkArray(second)) out << "Yes";
    else out << "No";
    
    out << "\n";
    arr.clear(); first.clear(); second.clear();
}

int main() {
    int T;
    inp >> T;
    
    while (T--) {
        int n;
        inp >> n;
        arr.resize(n); first.resize(n - 1); second.resize(n - 2);
        for(int i = 0; i < n; i++) inp >> arr[i];
        solve(n);
    }
    
    inp.close(); out.close();
    return 0;
}
