/**
 * Assignment 15 : Coin Game
 */
#include <fstream>
using namespace std;
#define MAX 104

ifstream inp("coin.inp");
ofstream out("coin.out");
int cache[MAX][MAX][MAX];

void Init() {
    for (int i = 3; i < MAX; i++) {
        for (int j = 3; j < MAX; j++) {
            for (int k = 3; k < MAX; k++) {
                if (i == 3 && j == 3 && k == 3)
                    cache[i][j][k] = 0;
                else {
                    // alice가 지는 상황이 있으면 그 수 만큼
                    // 동전을 빼서 선을 컴퓨터에게 주면 alice가 이기게 됨
                    if (cache[i - 1][j][k] == -1 || cache[i][j - 1][k] == -1 ||
                        cache[i][j][k - 1] == -1)
                        cache[i][j][k] = 1;
                    else if (cache[i - 2][j][k] == -1 ||
                             cache[i][j - 2][k] == -1 ||
                             cache[i][j][k - 2] == -1)
                        cache[i][j][k] = 1;
                    else if (cache[i - 3][j][k] == -1 ||
                             cache[i][j - 3][k] == -1 ||
                             cache[i][j][k - 3] == -1)
                        cache[i][j][k] = 1;
                    else
                        cache[i][j][k] = -1;
                }
            }
        }
    }
}

int main() {
    int T;
    inp >> T;

    Init();

    while (T--) {
        int a, b, c;
        inp >> a >> b >> c;
        out << '(' << a << ' ' << b << ' ' << c
            << ") : " << cache[a + 3][b + 3][c + 3] << '\n';
    }

    inp.close();
    out.close();
    return 0;
}