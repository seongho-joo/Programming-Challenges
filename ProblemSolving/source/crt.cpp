//
//  crt.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/19.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment28 CRT

#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long lint;

ifstream inp("crt.inp");
ofstream out("crt.out");

struct Crt {
    lint rem, num;
};

lint gcd(lint a, lint b) {
    if(a < b) swap(a, b);
    return (a % b != 0 ? gcd(b, a % b) : b);
}

lint xGCD(lint a, lint b) {
    bool flag = false;
    if(a < b) {
        flag = true;
        swap(a, b);
    }
    lint q, r, t, s;
    lint r1 = a, r2 = b;
    lint s1 = 1, s2 = 0;
    lint t1 = 0, t2 = 1;
    
    while(r2 > 0) {
        q = r1 / r2;
        r = r1 % r2;
        
        r1 = r2; r2 = r;
        
        s = s1 - q * s2;
        s1 = s2; s2 = s;
        
        t = t1 - q * t2;
        t1 = t2; t2 = t;
        q = 0; r = 0;
    }
    
    if(flag) return t1;
    return s1;
}

int main() {
    int T, n;
    inp >> T;
    while(T--) {
        inp >> n;
        Crt c1, c2;
        inp >> c1.rem >> c1.num;
        for(int i = 0; i < n - 1; i++) {
            inp >> c2.rem >> c2.num;
            if(c1.rem == -1) continue;
            c2.rem -= c1.rem;
            
            if(c2.rem < 0) {
                lint tmp = c2.rem * -1;
                if(tmp % c2.num == 0) tmp /= c2.num;
                tmp = (tmp / c2.num) + 1;
                c2.rem += (c2.num * tmp);
            }
            
            lint t = gcd(c1.num, c2.num);
            c2.num /= t;
            if(c2.rem % t != 0) {
                c1.rem = -1;
                continue;
            }
            
            c2.rem /= t;
            
            lint inverse = xGCD(c1.num / t, c2.num);
            c2.rem *= inverse;
            if(c2.rem < 0) {
                lint tmp = c2.rem * -1;
                if(tmp % c2.num == 0) tmp /= c2.num;
                tmp = (tmp / c2.num) + 1;
                c2.rem += (c2.num * tmp);
            }
            c2.rem %= c2.num;
            
            c1.rem += (c1.num * c2.rem);
            c1.num *= c2.num;
        }
        out << c1.rem << "\n";
    }
    inp.close(); out.close();
    return 0;
}
