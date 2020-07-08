//
//  waldorf.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/21.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment4 - Where's Waldorf?

#include <fstream>
#include <string>
#include <vector>
using namespace std;

ifstream inp("p10010.inp");
ofstream out("p10010.out");

vector<vector<char> > board;
string word;
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int T, n, m, k;

bool check(int y, int x, int I, int l) {
    bool flag = false;

    for (int i = 1; i < word.size(); i++) {
        flag = false;
        if (y < 0 || x < 0 || y >= n || x >= m) continue;
        int ch = word[l];
        if ((ch - 32) == board[y][x] || (ch + 32) == board[y][x] ||
            ch == board[y][x]) {
            flag = true;
            l++;
        } else
            return false;
        y += dy[I];
        x += dx[I];
    }
    return flag;
}

void solve() {
    int y, x, v;
    bool flag = false;
    for (int i = 0; i < n; i++) {
        flag = false;
        for (int j = 0; j < m; j++) {
            flag = false;
            char ch = word.at(0);
            /** 대소문자 구분x */
            if ((ch - 32) == board[i][j] || (ch + 32) == board[i][j] ||
                ch == board[i][j]) {
                y = i + 1, x = j + 1;
                for (int l = 0; l < 8; l++) {
                    int ny = i + dy[l];
                    int nx = j + dx[l];
                    if (ny < 0 || n < 0 || ny >= n || nx >= m) continue;
                    flag = check(ny, nx, l, 1);
                    if (flag) {
                        v = l;
                        break;
                    }
                }
            }
            if (flag) break;
        }
        if (flag) break;
    }
    if (flag)
        out << y << ' ' << x << '\n';
    else
        out << -1 << '\n';
}

void input() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) inp >> board[i][j];
    inp >> k;
    while (k--) {
        inp >> word;
        solve();
    }
}

int main() {
    inp >> T;
    for (int i = 0; i < T; i++) {
        inp >> n >> m;
        board.resize(n, vector<char>(m));
        input();
        board.clear();
        out << '\n';
    }

    inp.close();
    out.close();
    return 0;
}
