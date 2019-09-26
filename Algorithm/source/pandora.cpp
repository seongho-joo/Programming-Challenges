/**
 * Assignment 12 : Pandora
 */
#include <fstream>
#include <string>
using namespace std;

ifstream inp("pandora.inp");
ofstream out("pandora.out");

string S;

int solve() {
    S.push_back(S[0]);
    S.push_back(S[1]);
    int len = S.length();
    // 현재 방향, 이전 방향, 전전 방향
    // 0-위 1-왼 2-아 3-오
    int cur = 0, pre = 0, ppre = 0;
    bool X = false, Y = false;
    for (int i = 0; i < len; i++) {
        ppre = pre;
        pre = cur;
        if (S[i] == 'L')
            cur = (cur + 1) % 4;
        else
            cur = (cur + 3) % 4;
        // 시계방향으로 오목하면 선을 그었을 때 만나는 부분이 4개가 됨
        if (cur == 3 && pre == 0 && ppre == 1) Y = true;  // 오른쪽으로 오목
        if (cur == 1 && pre == 2 && ppre == 3) Y = true;  // 왼쪽으로 오목
        if (cur == 0 && pre == 1 && ppre == 2) X = true;  // 아래로 오목
        if (cur == 2 && pre == 3 && ppre == 0) X = true;  // 위로 오목
    }
    if (!X && !Y)
        return 2;
    else if (X && Y)
        return 0;
    else
        return 1;
}

int main() {
    int T;
    inp >> T;

    while (T--) {
        inp >> S;
        out << solve() << '\n';
    }

    inp.close();
    out.close();
    return 0;
}