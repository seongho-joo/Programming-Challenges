//
//  The_Cat_in_the_Hat.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/28.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment32 p00107(The Cat in the Hat)

#include <fstream>
#include <cmath>
using namespace std;

typedef long double ld;
ifstream inp("The_Cat_in_the_Hat.inp");
ofstream out("The_Cat_in_the_Hat.out");

int powerOf2(double h) {
    int p = 0;
    while(true) {
        int res = (1 << p);
        if( res > h) return p - 1;
        p += 1;
    }
}

int main() {
    ld h, x;
    while(inp >> h >> x) {
        if(h == 0 && x == 0) break;
        
        if(h == 1) {
            out << "0 1\n";
            continue;
        }
        if(x == 1) {
            int t = powerOf2(h);
            int k = 0;
            while(h >= 1) {
                k += h;
                h /= 2;
            }
            out << t << " " << k << "\n";
            continue;
        }
        double n = 2.0;
        ld rightSide = log(h) / log(x);
        while(fabs(log(n + 1) / log(n) - rightSide) > 1e-12) n += 1;
        
        int g = 0;
        int d = (int)x;
        while(d % (int)n != 1) {
            d /= (int)n;
            g += 1;
        }
        int noWorking = 0;
        g -= 1;
        while(g > -1) {
            noWorking += (int)ceil(pow(n, g));
            g -= 1;
        }
        double total = 0;
        int p = 0;
        double height = h;
        while(pow(n, p) <= x) {
            total += (height * pow(n, p));
            height /= (n + 1);
            p += 1;
        }
        out << noWorking << " " << (long long)total << "\n";
    }
    inp.close(); out.close();
    return 0;
}
