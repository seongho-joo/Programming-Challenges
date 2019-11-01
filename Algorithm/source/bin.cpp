/**
 * Assignment 18 : Recycling Bins
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#define INF 987654321
using namespace std;

ifstream inp("bin.inp");
ofstream out("bin.out");

vector<int> coor;  // 집들의 x좌표
vector<vector<int> > dist, Distance;
int n, m;  // 집의 수, 재활용 수집통 수

void Init() {
    dist.clear();
    coor.clear();
    Distance.clear();
    inp >> n >> m;
    coor.resize(n + 1);
    dist.resize(n + 1, vector<int>(n + 1, 0));
    Distance.resize(n + 1, vector<int>(m + 1, INF));

    for (int i = 0; i < m + 1; i++) Distance[0][i] = 0;
    for (int i = 1; i < n + 1; i++) inp >> coor[i];
    sort(coor.begin(), coor.end());
    // 수집통이 한 개 일때 최솟값
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int mid = (i + j) / 2;
            for (int k = i; k <= j; k++) dist[i][j] += abs(coor[mid] - coor[k]);
        }
    }
}

void solve() {
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            int cur = INF;
            for (int k = 1; k < i + 1; k++)
                cur = min(cur, Distance[i - k][j - 1] + dist[i - k + 1][i]);
            Distance[i][j] = cur;
        }
    }
}

int main() {
    int T;
    inp >> T;

    while (T--) {
        Init();
        if (n == m)
            out << 0 << '\n';
        else {
            solve();
            out << Distance[n][m] << '\n';
        }
    }

    inp.close();
    out.close();
    return 0;
}