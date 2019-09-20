/**
 * Assignment 09 : 사다리
 */
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("ladder.inp");
ofstream out("ladder.out");

struct Lad {
    int x, y;
};
vector<vector<Lad> > lad;
vector<int> MAX;  // 사다리 최대높이 저장
Lad l;
// 사다리 타는 함수
void Climbing(int x, int y) {
    int dx, dy;
    while (true) {
        if (MAX[x] < y) break;  // 사다리 최대높이보다 높으면 종료
        if (lad[x][y].y != 0) {
            dx = lad[x][y].x;
            dy = lad[x][y].y;
            x = dx;
            y = dy;
        }
        y++;
    }
    out << x << ' ';
}

void solution(int n) {
    int dy = 0;
    for (int i = 0; i < n; i++) {
        while (true) {
            if (lad[i][dy].y != 0) {
                Climbing(lad[i][dy].x, lad[i][dy].y + 1);
                dy = 0;
                break;
            }
            dy++;
        }
    }
    out << '\n';
}

int main() {
    int n;
    inp >> n;
    lad.resize(n, vector<Lad>(10001));
    MAX.resize(n);

    while (true) {
        int x, y;
        inp >> x >> y >> l.x >> l.y;
        MAX[x] = max(y, MAX[x]);
        MAX[l.x] = max(l.y, MAX[l.x]);
        if (x == 0 && y == 0 && l.y == 0 && l.y == 0) break;
        lad[x][y] = l;
        lad[l.x][l.y].x = x;
        lad[l.x][l.y].y = y;
    }

    solution(n);

    inp.close();
    out.close();
    return 0;
}