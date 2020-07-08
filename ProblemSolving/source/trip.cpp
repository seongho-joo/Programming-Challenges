//
//  trip.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/21.
//  Copyright © 2020 주성호. All rights reserved.
//

/**
 * Assignment 2 : The Trip
 */
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

ifstream inp("p10137.inp");
ofstream out("p10137.out");

int n, dollar, cent, sum, lowerAvg, highAvg;
int adove, below, ans;
char temp;
vector<double> cost;

void solve() {
    lowerAvg = sum / n;
    /** 나누어 떨어지지 않으면 1센트를 더냄 */
    highAvg = lowerAvg + ((sum % n) ? 1 : 0);

    adove = 0, below = 0;
    for (int i = 0; i < n; i++) {
        if (highAvg < cost[i]) adove += cost[i] - highAvg;
        if (lowerAvg > cost[i]) below += lowerAvg - cost[i];
    }
    ans = max(adove, below);

    /**
     * setw(2) 2칸 확보
     * setfill('0') setw()에서 확보한 공간을 '0' 으로 채움
     * */
    out << '$' << (ans / 100) << '.' << setw(2) << setfill('0') << (ans % 100)
        << '\n';
}

int main() {
    while (inp >> n, n) {
        sum = 0;
        cost.resize(n);
        for (int i = 0; i < n; i++) {
            inp >> dollar >> temp >> cent;
            cost[i] = dollar * 100 + cent;
            sum += cost[i];
        }
        solve();
    }

    inp.close();
    out.close();
    return 0;
}
