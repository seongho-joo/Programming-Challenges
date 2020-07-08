//
//  stack'emUp.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/27.
//  Copyright © 2020 주성호. All rights reserved.
//
// Assignment 19 - p10205 (Stack Them Up)

#include <fstream>
#include <vector>
#include <string>
using namespace std;

ifstream inp("stackThemUp.inp");
ofstream out("stackThemUp.out");

string num[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
string suit[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
vector<int> card(53);
int shuff[101][53];
int N, I, J;

void change(int n) {
    vector<int> temp(53);
    for(int i = 1; i < 53; i++) temp[i] = card[shuff[n][i]];
    card = temp;
}

int main() {
    int T;
    inp >> T;
    bool start = false;
    while(T--) {
        if(start) out << "\n";
        inp >> N;
        for(int i = 1; i <= N; i++)
            for(int j = 1; j < 53; j++) inp >> shuff[i][j];
        
        for(int i = 1; i < 53; i++) card[i] = i;
        string line;
        getline(inp, line);
        while(getline(inp, line), line != "\0") {
            int s = 0;
            for(int i = 0; i < line.size(); i++) {
                s += line[i] - '0';
                s *= 10;
            }
            s /= 10;
            change(s);
        }
        // 공백일 경우 셔플한 카드 출력
        for(int i = 1; i < 53; i++) out << num[card[i] % 13] << " of " << suit[(card[i] - 1) / 13] << "\n";
        // 테스트케이스 구분
        start = true;
    }
    
    return 0;
}
