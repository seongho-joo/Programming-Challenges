//
//  rectangles.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/06/03.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment34 set of rectangles

#include <algorithm>
#include <vector>
#include <fstream>
#include <set>
#include <cmath>
using namespace std;

ifstream inp("rectangles.inp");
ofstream out("rectangles.out");
int a, b, L;

set<pair<int, int> > pitagoras;
vector<int> sum;

int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

void pitagorasTriple() {
    for(int x = 1; x < 1001; x++) {
        for(int y = 1; y < x; y++) {
            if((x + y) % 2 != 0 && x > y) {
                a = 2 * x * y;
                b = pow(x, 2) - pow(y, 2);
                if(a < b) swap(a, b);
                if(gcd(a, b) == 1) {
                    pitagoras.insert(make_pair(a, b));
                    sum.push_back(2 * (a + b));
                }
            }
        }
    }
    
    for(int i = 3;; i += 2) {
        a = (pow(i, 2) - 1) / 2;
        b = i;
        if(a < b) swap(a, b);
        if(pitagoras.count(make_pair(a, b)) == 0) {
            if(2 * (a + b) > 1000000) break;
            sum.push_back(2 * (a + b));
        }
    }
    
    sort(sum.begin(), sum.end());
    for(int i = 1; i < sum.size(); i++) sum[i] += sum[i - 1];
}

int main() {
    int T;
    inp >> T;
    
    pitagorasTriple();
    
    while(T--) {
        inp >> L;
        for(int i = 0; i < sum.size(); i++)
            if(sum[i] > L) {
                out << i << "\n";
                break;
            }
    }
    inp.close(); out.close();
    return 0;
}
