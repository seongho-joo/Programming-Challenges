/**
 * Assignment 24 - Zigsaw Sudoku
 */

#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

ifstream inp("sudoku.inp");
ofstream out("sudoku.out");
int T;
pair<int, char> map[9][9];
bool p[9][10];

void input() {
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) inp >> map[i][j].first;
    /** 구간 입력 */
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) inp >> map[i][j].second;

    /** 구간들의 숫자의 중복 판단 */
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            if (map[i][j].first) {
                p[map[i][j].second - 'a'][map[i][j].first] = true;
            }
        }
}

bool check(int y, int x, int k) {
    for (int i = 0; i < 9; i++) {
        /** 행 탐색 */
        if (map[i][x].first == k) return false;
        /** 열 탐색 */
        if (map[y][i].first == k) return false;
    }
    return true;
}

void print(int n) {
    out << "Test Case No: " << n + 1 << '\n';
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) out << map[i][j].first << ' ';
        out << '\n';
    }
    out << '\n';
}
/** 완전탐색으로 백트래킹 */
int sudoku(int cnt, int n) {
    if (cnt == 81) {
        print(n);
        return 1;
    }
    int y = cnt / 9, x = cnt % 9;
    int v = map[y][x].second - 'a';
    /** 스도쿠에 채워졌을 경우 카운트 증가 */
    if (map[y][x].first) {
        if (sudoku(cnt + 1, n))
            return 1;
        else
            return 0;
    } else {
        for (int k = 1; k < 10; k++) {
            /** 행, 열, 구간에 같은 수 가 있는지 확인 */
            if (check(y, x, k) && !p[v][k]) {
                map[y][x].first = k;
                p[v][k] = true;
                if (sudoku(cnt + 1, n)) return 1;
                /** 백트래킹 */
                map[y][x].first = 0;
                p[v][k] = false;
            }
        }
    }
    return 0;
}

int main() {
    inp >> T;
    clock_t s, e;
    s = clock();
    for (int i = 0; i < T; i++) {
        input();
        sudoku(0, i);
        for (int j = 0; j < 9; j++)
            for (int k = 0; k < 10; k++) p[j][k] = false;
    }
    e = clock();
    cout << (double)(e - s) << '\n';
    inp.close();
    out.close();
    return 0;
}