//
//  conEq.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/06/22.
//  Copyright © 2020 주성호. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

long long int t,a,b,c;
vector<long long int> num;



int main() {

   ifstream inp;
   ofstream out;
   inp.open("conEq.inp");
   out.open("conEq.out");
   inp >> t;
   while (t--) {
      num.clear();
      inp >> a >> b >> c;
      num.push_back(a);
      num.push_back(b);
      num.push_back(c);
      sort(num.begin(), num.end());
      
      if (c == num[0] || c == num[1]) {
         int y[10000], r[10000][2], s = 0, k = 0;
         int a1 = num[2], b1 = num[1];
         while (a1 % b1 != 0) {
            y[s++] = (a1 / b1) * (-1);
            if (a1 % b1 == 0) {
               break;
            }
            long long int temp = a1 % b1;
            a1 = b1;
            b1 = temp;
         }

         if (b1 > num[0]) {
            cout << -1 << endl;
         }

         else {
            s--;
            r[s][0] = 1;
            r[s][1] = y[s];
            s--;
            while (s > -1) {
               r[s][0] = r[s + 1][1];
               r[s][1] = r[s + 1][0] + r[s + 1][1] * y[s];
               s--;
            }
            if (r[0][1] < 0)r[0][1] *= -1;
            if (r[0][0] < 0)r[0][0] *= -1;
            out << (r[0][1] + r[0][0]) * (c/b1) << endl;
         }
      }
      else {
         if (a < b) {
            long long int k = b;
            a = b;
            b = k;
         }
         long long int ret = 987654321;
         long long int as = 0,bs = 0,c1 = c;
         as = c1 / a;
         c1 %= a;
         if (c1 % b != 0) {
            out << -1 << endl;
            break;
         }
         ret = min(ret, as + c1 / b);
         as++;
         c = as * a - c;
         if (c1 % b != 0) {
            out << ret << endl;
            break;
         }
         ret = min(ret, as + c / b);
         out << ret << endl;
      }
   }
}
