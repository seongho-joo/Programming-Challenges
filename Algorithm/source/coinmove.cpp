/**
 * Assignment 17 : Coin Move Game
 */
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

vector<vector<int> > coin;
int k, p, s;
// current - k 중 0이 나오면 이기고 1이 하나라도 나오면 못이김
bool preCheck(int pre, int l) {
    for (int i = 1; i < k + 1; i++) {
        if (l == i) continue;
        if (coin[i][pre] == 1) return false;
    }
    return true;
}

void solution(ofstream& out) {
    for (int i = 1; i < s + 1; i++) {
        // 출발지는 p의 배수와 관계없음
        if (i % p == 0 && i != s) continue;
        for (int j = 1; j < k + 1; j++) {
            int pre = i - j, &ret = coin[j][i];
            if ((pre % p == 0 && pre != 0) || pre < 0)
                ret = 0;
            else {
                if (preCheck(pre, j))
                    ret = 1;
                else
                    ret = 0;
            }
        }
    }

    int res = 0;
    for (int i = 0; i < k + 1; i++)
        if (coin[i][s] == 1) res = max(res, s - i);
    if (res == 0)
        out << -1 << '\n';
    else
        out << res << '\n';
}

int main() {
    ifstream inp("coinmove.inp");
    ofstream out("coinmove.out");

    int T;
    inp >> T;

    while (T--) {
        inp >> p >> k >> s;
        coin.resize(k + 1, vector<int>(s + 1));
        solution(out);
        coin.clear();
    }

    inp.close();
    out.close();
    return 0;
}