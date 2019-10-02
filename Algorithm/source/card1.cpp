/**
 * Assignment 13 : Card Selection
 */
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

#define INF -987654321

ifstream inp("card.inp");
ofstream out("card.out");
vector<int> card;
vector<vector<int> > cache;
int last, sum;

void Init(int n) {
    card.clear();
    card.reserve(n);
    cache.resize(n, vector<int>(3, 0));

    int data;
    while (n--) {
        inp >> data;
        card.push_back(data);
    }

    last = card.back();

    card.pop_back();
    card.pop_back();
}

void solve(int n) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) cache[i][j] = card[i];
    // 마지막 카드 직전카드는 선택하지 못함
    for (int i = 0; i < 3; i++) cache[n - 2][i] = INF;

    cache[3][0] = max(cache[1][1], cache[1][2]) + card[3];
    cache[3][1] = max(cache[0][0], max(cache[0][1], cache[0][1])) + card[3];
    cache[3][2] = INF;  // i - 4를 선택할 수 없는경우

    for (int i = 4; i < n; i++) {
        cache[i][0] = max(cache[i - 2][1], cache[i - 2][2]) + card[i];
        cache[i][1] =
            max(cache[i - 3][0], max(cache[i - 3][1], cache[i - 3][2])) +
            card[i];
        cache[i][2] =
            max(cache[i - 4][0], max(cache[i - 4][1], cache[i - 4][2])) +
            card[i];
    }

    out << max(cache[n - 1][0], max(cache[n - 1][1], cache[n - 1][2])) << '\n';
}

int main() {
    int T;
    inp >> T;

    while (T--) {
        int n;
        inp >> n;
        Init(n);
        solve(n);
    }

    inp.close();
    out.close();
    return 0;
}