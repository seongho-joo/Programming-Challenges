//
//  mult.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/04.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment24 곱의방법수 - 중간고사 대체 과제

#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

ifstream inp("mult.inp");
ofstream out("mult.out");

int cnt;

void solve(int n, int p) {
    vector<int> divisor, div;
    for(int i = 2; i <= sqrt(n); i++) {
        if(n % i == 0) {
            divisor.push_back(i);
            div.push_back(n / i);
        }
    }
    
    for(int i = 0; i < divisor.size(); i++) {
        if(divisor[i] >= p) {
            cnt += 1;
            solve(div[i], divisor[i]);
        }
    }
}


int main() {
    int T, n;
    inp >> T;
    
    while(T--) {
        inp >> n;
        cnt = 0;
        solve(n, 0);
        out << n << " " << cnt << "\n";
    }
    
    inp.close(); out.close();
    return 0;
}
