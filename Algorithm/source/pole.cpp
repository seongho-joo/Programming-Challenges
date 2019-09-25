/**
 * Assignment 11 : Pole Arrangement
 */
#include <fstream>
using namespace std;

ifstream inp("pole.inp");
ofstream out("pole.out");

int n, l, r;  // 폴의 개수, 왼쪽에서 보이는 폴 수, 오른쪽에서 보이는 폴 수

unsigned long long solve() {
    if (n == 1) {
        if (r == 1 && l == 1)
            return 0;
        else
            return 1;
    } else {
        // 크기가 같은 막대는 없기때문에 불가능
        if (r == 1 && l == 1) return 0;
        // 폴 수로 나올 수 없는 경우
        if (r + l > n + 2) return 0;

        unsigned long long pole[21][21][21];
        // 막대기 수 와 왼쪽이나 오른쪽에서 보이는 막대기 수 가 같으면 경우의 수
        // 는 하나임
        for (int i = 1; i <= n; i++) {
            pole[i][i][1] = 1;
            pole[i][1][i] = 1;
        }
        if (pole[n][r][l] == 1) return 1;
        for (int i = 2; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    pole[i][j][k] = pole[i - 1][j][k] * (i - 2) +
                                    pole[i - 1][j - 1][k] +
                                    pole[i - 1][j][k - 1];
        return pole[n][l][r];
    }
}

int main() {
    int T;
    inp >> T;

    while (T--) {
        inp >> n >> l >> r;
        out << solve() << '\n';
    }

    inp.close();
    out.close();
    return 0;
}