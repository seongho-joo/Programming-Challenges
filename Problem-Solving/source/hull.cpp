/**
 * Assignment 10 - Convex Hull
 */
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;
const int MAX = 20000;

ifstream inp("hull.inp");
ofstream out("hull.out");

struct Point {
    int x, y;
    int p, q;
    Point() : x(0), y(0), p(1), q(0) {}
    Point(int x1, int y1) : x(x1), y(y1), p(1), q(0) {}
};

bool comp(const Point& A, const Point& B) {
    if (1LL * A.q * B.p != 1LL * A.p * B.q)
        return 1LL * A.q * B.p < 1LL * A.p * B.q;
    if (A.x != B.x) return A.x < B.x;
    return A.y < B.y;
}

vector<Point> p, ans;
int N, x, y;
// 벡터AB와 벡터AC의 CCW
long long CCW(const Point& A, const Point& B, const Point& C) {
    return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (B.y - A.y) * (C.x - A.x);
}

void solve() {
    // 점들을 x좌표 -> y좌표 순으로 정렬 : 0번 점이 제일 아래 제일 왼쪽
    sort(p.begin(), p.end(), comp);
    for (int i = 1; i < N; i++) {
        p[i].p = p[i].x - p[0].x;
        p[i].q = p[i].y - p[0].y;
    }
    sort(p.begin() + 1, p.end(), comp);

    vector<int> s;
    // 우선 처음 점 2개를 스택에 넣음
    s.push_back(0);
    s.push_back(1);
    int next = 2;

    while (next < N) {
        while (s.size() >= 2) {
            int first, second;
            first = s.back(), s.pop_back();
            second = s.back();
            // 외적이 0보다 크면 ccw, 0이면 같은 선상, 0보다 작으면 cw
            if (CCW(p[second], p[first], p[next]) > 0) {
                s.push_back(first);
                break;
            }
        }
        s.push_back(next++);
    }
    int len = s.size();
    ans.resize(len);

    out << len << '\n';
    for (int i = 0; i < len; i++) out << p[s[i]].x << ' ' << p[s[i]].y << '\n';
}

int main() {
    inp >> N;
    p.resize(N);

    for (int i = 0; i < N; i++) {
        inp >> x >> y;
        p[i] = Point(x, y);
    }

    solve();

    inp.close(), out.close();
    return 0;
}