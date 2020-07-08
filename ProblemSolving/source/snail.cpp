//
//  snail.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/21.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment 08 - Snail

#include <cmath>
#include <fstream>
using namespace std;

ifstream inp("p573.inp");
ofstream out("p573.out");
int h, u, d, f;
int day = 1;

bool solve() {
    int cur_h = 0;
    day = 1;
    f = u * 0.01 * f;
    while (true) {
        if (u > 0) cur_h += u;
        if (cur_h > h) return true;
        cur_h -= d;
        u -= f;
        if (cur_h <= 0) return false;
        day += 1;
    }
}

int main() {
    while (inp >> h >> u >> d >> f) {
        if (h == 0) break;
        h *= 100, u *= 100, d *= 100;
        bool ans = solve();
        out << (ans ? "success " : "failure ") << "on day " << day << '\n';
    }

    inp.close(), out.close();
    return 0;
}

