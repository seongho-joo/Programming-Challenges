/**
 * Assignment 16 : 정육면체 자르기
 */
#include <algorithm>
#include <fstream>
using namespace std;
#define MAX 201
#define INF 987654321
ifstream inp("cube.inp");
ofstream out("cube.out");
int D[201][201][201];
int w, l, h;  // 가로 세로 높이

void Swap(int& i, int& j) {
    int temp = j;
    i = j;
    j = temp;
}

void Init() {
    for (int i = 1; i < MAX; i++)
        for (int j = 1; j < MAX; j++)
            for (int k = 1; k < MAX; k++) {
                if (i == j && j == k)
                    D[i][j][k] = 1;
                else
                    D[i][j][k] = INF;
            }
    for (int i = 1; i < MAX; i++) {
        for (int j = i; j < MAX; j++) {
            for (int k = j; k < MAX; k++) {
                int& ret = D[i][j][k];
                if (ret == INF) {
                    for (int l = i - 1; l >= i / 2; l--)
                        ret = min(ret, D[l][j][k] + D[i - l][j][k]);
                    for (int l = j - 1; l >= j / 2; l--)
                        ret = min(ret, D[i][l][k] + D[i][j - l][k]);
                    for (int l = k - 1; l >= k / 2; l--)
                        ret = min(ret, D[i][j][l] + D[i][j][k - l]);
                    D[i][k][j] = D[j][i][k] = D[j][k][i] = D[k][i][j] =
                        D[k][j][i] = D[i][j][k];
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
        inp >> w >> l >> h;
        out << D[w][l][h] << '\n';
    }

    return 0;
}