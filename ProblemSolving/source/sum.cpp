//
//  sum.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/06/22.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment38 수열의 합(기말고사 1)

#include <fstream>
#include <vector>
using namespace std;

ifstream inp("sum.inp");
ofstream out("sum.out");

vector<int> dp;

int getSeq(int n) {
    dp[0] = 1;
    dp[1] = 2;
    for(int i = 2; i < n + 1; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + 2;
        if(dp[i] >= n) return dp[i - 1];
    }
    return 0;
}

int main() {
    int T;
    inp >> T;
    
    while(T--) {
        int n;
        inp >> n;
        dp.resize(n + 1);
        out << getSeq(n) << "\n";
        dp.clear();
    }
    return 0;
}
