/**
 * Assignment 14 - 다각형 접선 2
 */
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef long long lint;
ifstream inp("tangent2.inp");
ofstream out("tangent2.out");

int T;
struct Point {
    int idx;
    lint x, y, p, q;
    char part;
    Point() : idx(0), x(0), y(0), p(0), q(0), part('1') {}
    Point(int idx, int x, int y, char part)
        : idx(idx), x(x), y(y), p(1), q(0), part(part) {}

    bool operator<(const Point& a) const {
        if (q * a.p != p * a.q) return q * a.p < p * a.q;
        if (y != a.y) return y < a.y;
        return x < a.x;
    }
    bool operator==(const Point& a) const { return x == a.x && y == a.y; }
};

vector<Point> P, Q, convex, inside;
vector<Point> convexP, convexQ, temp;
Point tangentP[2], tangentQ[2], p[2], q[2];
int p_len, q_len;

void init(vector<Point>&, char);
void convexHull(int, vector<Point>, vector<Point>&);
void setIndex();
void getTangent();
void getInsidePoint();
lint getArea();

int main() {
    inp >> T;

    while (T--) {
        P.clear(), Q.clear(), convex.clear();
        convexP.clear(), convexQ.clear();
        temp.clear(), inside.clear();
        init(P, 'p'), init(Q, 'q');
        // 컨벡스 헐을 구함
        convexHull(P.size() + Q.size(), temp, convex);
        convexHull(P.size(), P, convexP);
        convexHull(Q.size(), Q, convexQ);
        p_len = convexP.size(), q_len = convexQ.size();
        // 전체 컨벡스 헐의 인덱스 다시 설정
        setIndex();
        // 내부 접선을 구함
        getTangent();
        getInsidePoint();
        lint ans = getArea();
        if ((ans % 2 == 0))
            out << ans / 2 << ".0\n";
        else
            out << ans / 2 << ".5\n";
    }

    inp.close(), out.close();
    return 0;
}

lint getArea() {
    lint ret = 0;
    for (int i = 0; i < inside.size(); i++) {
        int j = (i + 1) % inside.size();
        ret += (inside[i].x * inside[j].y - inside[i].y * inside[j].x);
    }
    return abs(ret);
}

void getInsidePoint() {
    for (int i = tangentP[0].idx; i != tangentP[1].idx; i = (i + 1) % P.size())
        inside.push_back(P[i]);
    inside.push_back(tangentP[1]);
    for (int i = tangentQ[0].idx; i != tangentQ[1].idx; i = (i + 1) % Q.size())
        inside.push_back(Q[i]);
    inside.push_back(tangentQ[1]);
}

void init(vector<Point>& v, char part) {
    int n, x, y;
    inp >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        inp >> x >> y;
        v[i] = Point(i, x, y, part);
    }
    // p, q의 모든좌표를 넣음
    for (int i = 0; i < n; i++) temp.push_back(v[i]);
}

lint ccw(Point& a, Point& b, Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
// 도형의 하단부터 시작해서 내부 접선을 구함
void insideTangent(Point startQ, Point endP, Point endQ, Point startP) {
    int cnt = 0;
    // q_bottom -> p_bottom
    for (int i = startQ.idx;; i--) {
        if (i < 0) i = q_len - 1;
        cnt = 0;
        bool flag = false;
        for (int j = endP.idx;; j = (j + 1) % p_len) {
            cnt = 0;
            for (int k = (j + 1) % p_len; k != j; k = (k + 1) % p_len)
                if (ccw(convexQ[i], convexP[j], convexP[k]) >= 0) cnt += 1;
            if (cnt == p_len - 1) {
                cnt = 0;
                for (int k = i - 1;; k--) {
                    if (k < 0) k = q_len - 1;
                    if (k == i) break;
                    if (ccw(convexP[j], convexQ[i], convexQ[k]) >= 0) cnt += 1;
                }
                if (cnt == q_len - 1) {
                    tangentP[1] = convexP[j];
                    flag = true;
                    break;
                }
                break;
            }
        }
        if (flag) break;
    }
    // p_bottom -> q_bottom
    for (int i = endP.idx;; i = (i + 1) % p_len) {
        cnt = 0;
        bool flag = false;
        for (int j = startQ.idx;; j--) {
            if (j < 0) j = q_len - 1;
            cnt = 0;
            for (int k = (j + 1) % q_len; k != j; k = (k + 1) % q_len)
                if (ccw(convexP[i], convexQ[j], convexQ[k]) <= 0) cnt += 1;
            if (cnt == q_len - 1) {
                cnt = 0;
                for (int k = (i + 1) % p_len; k != i; k = (k + 1) % p_len) {
                    if (ccw(convexQ[j], convexP[i], convexP[k]) <= 0) cnt += 1;
                }
                if (cnt == p_len - 1) {
                    tangentQ[0] = convexQ[j];
                    flag = true;
                    break;
                }
                break;
            }
        }
        if (flag) break;
    }
    // q_top -> p_top
    for (int i = endQ.idx;; i = (i + 1) % q_len) {
        cnt = 0;
        bool flag = false;
        for (int j = startP.idx;; j--) {
            cnt = 0;
            if (j < 0) j = p_len - 1;
            for (int k = (j + 1) % p_len; k != j; k = (k + 1) % p_len)
                if (ccw(convexQ[i], convexP[j], convexP[k]) <= 0) cnt += 1;
            if (cnt == p_len - 1) {
                cnt = 0;
                for (int k = (i + 1) % q_len; k != i; k = (k + 1) % q_len)
                    if (ccw(convexP[j], convexQ[i], convexQ[k]) <= 0) cnt += 1;
                if (cnt == q_len - 1) {
                    tangentP[0] = convexP[j];
                    flag = true;
                    break;
                }
                break;
            }
        }
        if (flag) break;
    }
    // p_top -> q_top
    for (int i = startP.idx;; i--) {
        cnt = 0;
        if (i < 0) i = p_len - 1;
        bool flag = false;
        for (int j = endQ.idx;; j = (j + 1) % q_len) {
            cnt = 0;
            for (int k = (j + 1) % q_len; k != j; k = (k + 1) % q_len)
                if (ccw(convexP[i], convexQ[j], convexQ[k]) >= 0) cnt += 1;
            if (cnt == q_len - 1) {
                cnt = 0;
                for (int k = i - 1;; k--) {
                    if (k < 0) k = p_len - 1;
                    if (k == i) break;
                    if (ccw(convexQ[j], convexP[i], convexP[k]) >= 0) cnt += 1;
                }
                if (cnt == p_len - 1) {
                    tangentQ[1] = convexQ[j];
                    flag = true;
                    break;
                }
                break;
            }
        }
        if (flag) break;
    }
}
void getTangent() {
    for (int i = 0; i < convex.size(); i++) {
        int j = (i + 1) % convex.size();
        if (convex[i].part != convex[j].part) {
            if (convex[i].part == 'q')
                q[0] = convex[i], p[0] = convex[j];
            else
                p[1] = convex[i], q[1] = convex[j];
        }
    }
    insideTangent(q[1], p[1], q[0], p[0]);
}

void convexHull(int len, vector<Point> v, vector<Point>& c) {
    sort(v.begin(), v.end());
    for (int i = 0; i < len; i++) {
        v[i].p = v[i].x - v[0].x;
        v[i].q = v[i].y - v[0].y;
    }
    sort(v.begin() + 1, v.end());

    c.push_back(v[0]);
    c.push_back(v[1]);
    int next = 2;

    while (next < len) {
        while (c.size() >= 2) {
            Point first = c.back();
            c.pop_back();
            Point second = c.back();
            if (ccw(second, first, v[next]) > 0) {
                c.push_back(first);
                break;
            }
        }
        c.push_back(v[next++]);
    }
}
// 전체 볼록껍질의 인덱스 설정
void setIndex() {
    for (int i = 0; i < convex.size(); i++) {
        for (int j = 0; j < convexP.size(); j++)
            if (convex[i] == convexP[j]) convex[i].idx = j;
        for (int j = 0; j < convexQ.size(); j++)
            if (convex[i] == convexQ[j]) convex[i].idx = j;
    }
}