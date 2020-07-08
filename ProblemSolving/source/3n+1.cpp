//
//  3n+1.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/21.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment 1 : The 3n + 1 problem

#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("3n+1.inp");
ofstream out("3n+1.out");

int i, j;
int Max, Min;

int Solve() {
    int maxCount = 0;
    for (int i = Min; i <= Max; i++) {
        int n = i, cnt = 1;
        while (n != 1) {
            if (n % 2 == 1)
                n = 3 * n + 1;
            else
                n /= 2;
            cnt += 1;
        }
        maxCount = cnt < maxCount ? maxCount : cnt;
    }
    return maxCount;
}

int main() {
    while (!inp.eof()) {
        inp >> i >> j;

        if (i == -1) break;

        if (i == j)
            Max = i, Min = i;
        else if (i < j)
            Max = j, Min = i;
        else
            Max = i, Min = j;

        out << i << ' ' << j << ' ' << Solve() << '\n';

        i = -1;
        j = -1;
    }

    inp.close();
    out.close();
    return 0;
}
