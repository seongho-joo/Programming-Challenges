//
//  ones.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/19.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment29 p10127(Ones)

#include <fstream>
using namespace std;

ifstream inp("ones.inp");
ofstream out("ones.out");

int main() {
    int n;
    while((inp >> n)) {
        int cnt = 0, temp = 1;
        while(true) {
            cnt += 1;
            if(temp % n == 0) break;
            temp = temp * 10 + 1;
            temp %= n;
        }
        out << cnt << "\n";
    }
    inp.close(); out.close();
    return 0;
}
