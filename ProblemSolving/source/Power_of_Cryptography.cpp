//
//  Power_of_Cryptography.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/28.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment31 p00113(Power of Cryptography)

#include <fstream>
#include <cmath>
using namespace std;

ifstream inp("Power_of_Cryptography.inp");
ofstream out("Power_of_Cryptography.out");

int main() {
    double n = 0, p = 0, k;
    while((inp >> n)) {
        inp >> p;
        k = pow(p, (1 / n));
        out << k << "\n";
    }
    
    inp.close(); out.close();
    return 0;
}
