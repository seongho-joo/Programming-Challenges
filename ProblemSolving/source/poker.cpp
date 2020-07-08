//
//  poker.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/21.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment 18 - Poker

#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

typedef pair<string, int> psi;
struct Poker {
    char p;
    int n;
    Poker(): p(' '), n(0) {}
    Poker(char p, int n): p(p), n(n) {}
    bool operator < (const Poker a) const {
        if(p != a.p) return p < a.p;
        return n < a.n;
    }
};
ifstream inp("poker.inp");
ofstream out("poker.out");
string gen[9] = {"Top", "One Pair", "Two Pair", "Triple", "Straight", "Flush", "Full House", "Four Card", "Straight Flush"};
bool genealogy[9];
//  a, 2, 3, 4, 5, 6, 7, 8, 9, 10, j, q, k
int number[14];
vector<int> num;
vector<Poker> poker;

void solve() {
    int sCount = 0,dCount = 0, hCount = 0, cCount = 0;
    for(int i = 0; i < poker.size(); i++) {
        if(poker[i].p == 'S') sCount += 1;
        else if(poker[i].p == 'D') dCount += 1;
        else if(poker[i].p == 'H') hCount += 1;
        else cCount += 1;
    }
    // Flush가 존재하면 같은문양의 수가 5개
    if(sCount >= 5 || dCount >= 5 || hCount >= 5 || cCount >= 5) genealogy[5] = true;
    int cnt = 0, triple = 0;
    // one pair, two pair, triple이 존재하는지 알아봄
    for(int i = 1; i < 14; i++) {
        // Four Card
        if(number[i] >= 4) genealogy[7] = true;
        // Triple
        else if(number[i] >= 3) triple += 1;
        else if(number[i] >= 2) cnt += 1;
    }
    // one pair
    if(cnt == 1) genealogy[1] = true;
    // two pair
    if(cnt >= 2 || triple >= 2) genealogy[2] = true;
    // Triple
    if(triple >= 1) genealogy[3] = true;
    // full house
    if((genealogy[2] && genealogy[3]) || (genealogy[1] && genealogy[3])) genealogy[6] = true;
    // Straight가 존재하는지 알아봄
    for(int i = 1; i < 11; i++) {
        if(i == 10) {
            if(number[i] > 0 && number[i + 1] > 0 && number[i + 2] > 0 && number[i + 3] > 0 && number[1] > 0)
                genealogy[4] = true;
            continue;
        }
        if(number[i] > 0 && number[i + 1] > 0 && number[i + 2] > 0 && number[i + 3] > 0 && number[i + 4] > 0)
            genealogy[4] = true;
    }
    
    if(genealogy[5]) {
        int count = 0;
        for(int i = 0 ; i < poker.size(); i++) {
            int j = (i + 1) % poker.size();
            if(poker[i].p == poker[j].p) {
                if(poker[i].n == 1 && poker[j].n == 10) count += 1;
                else if(poker[i].n == 13 && poker[j].n == 1) count += 1;
                else if(poker[i].n + 1 ==  poker[j].n) count += 1;
                else count = 0;
            }
            else {
                if(poker[i].n == 13) {
                    for(int k = 0; k < poker.size(); k++)
                        if(poker[k].p == poker[i].p && poker[k].n == 1) {
                            count += 1;
                            break;
                        }
                }
                else count = 0;
            }
            if(count >= 4) {
                genealogy[8] = true;
                break;
            }
        }
        if(count >= 4) genealogy[8] = true;
    }
}

int main() {
    int T;
    inp >> T;
    while(T--) {
        fill(genealogy, genealogy + 9, false);
        genealogy[0] = true;
        fill(number, number + 14, 0);
        poker.resize(7);
        
        for(int i = 0; i < 7; i++) {
            string input;
            int num;
            inp >> input;
            if (input[1] == 'A') num = 1;
            else if (input[1] == 'T') num = 10;
            else if (input[1] == 'J') num = 11;
            else if (input[1] == 'Q') num = 12;
            else if (input[1] == 'K') num = 13;
            else num = input[1] - '0';
            number[num] += 1;
            poker[i] = Poker(input[0], num);
            
        }
        sort(poker.begin(), poker.end());
        solve();
        
        for(int i = 8; i >= 0; i--) {
            if(genealogy[i]) {
                out << gen[i] << '\n';
                break;
            }
        }
    }
    
    inp.close(); out.close();
    return 0;
}
