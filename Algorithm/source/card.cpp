/**
 * Assignment 14 : Card Game
 */
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("card.inp");
ofstream out("card.out");

vector<vector<int> > first, second;

void Init(int n) {
    first.resize(n, vector<int>(n, 0));
    second.resize(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) inp >> first[i][i];
}

void solve(int n) {
    for (int x = 1; x < n; x++) {
        for (int y = 0; x + y < n; y++) {
            second[y][x + y] = min(first[y][x + y - 1], first[y + 1][x + y]);
            first[y][x + y] = (first[y][x + y - 1] + second[y][x + y - 1] +
                               first[x + y][x + y]) -
                              second[y][x + y];
        }
    }
    out << first[0][n - 1] << '\n';
    first.clear();
    second.clear();
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