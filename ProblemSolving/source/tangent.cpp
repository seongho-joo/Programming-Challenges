//
//  tangent.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/21.
//  Copyright © 2020 주성호. All rights reserved.
//

/**
 * Assignment 12 - 다각형 접선 1
 */
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;

struct Point {
    long long x, y, p, q;
    int part, idx;
    Point() : x(0), y(0), p(0), q(0), part(0), idx(0) {}
    Point(long long x, long long y, int part, int idx)
        : x(x), y(y), p(1), q(0), part(part), idx(idx) {}
};

bool comp(const Point& a, const Point& b) {
    if (1LL * a.q * b.p != 1LL * a.p * b.q)
        return 1LL * a.q * b.p < 1LL * a.p * b.q;
    // 수직 상태일때 q값을 큰 순으로 정렬
    if (a.p == 0 && b.p == 0) return a.q > b.q;
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

long long ccw(Point& a, Point& b, Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

ifstream inp("tangent.inp");
ofstream out("tangent.out");
vector<Point> P, Q, polygon;
Point tangentP[2], tangentQ[2];
int T, n;
long long x, y;

void convexHull(int p, int q);
long long getOutside();
long long getArea(vector<Point>& a);

int main() {
    inp >> T;
    while (T--) {
        P.clear(), Q.clear(), polygon.clear();
        inp >> n;
        P.resize(n);
        for (int i = 0; i < n; i++) {
            inp >> x >> y;
            P[i] = Point(x, y, 1, i);
        }
        inp >> n;
        Q.resize(n);
        for (int i = 0; i < n; i++) {
            inp >> x >> y;
            Q[i] = Point(x, y, 2, i);
        }
        convexHull(P.size(), Q.size());
        long long pArea, qArea, total, outside, ret;
        outside = getOutside();    // convex hull의 바깥 부분 면적
        pArea = getArea(P);        // P의 면적
        qArea = getArea(Q);        // Q의 면적
        total = getArea(polygon);  // P, Q의 convexHull 면적
        ret = total - (pArea + qArea) - outside;
        if ((ret % 2) == 0)
            out << ret / 2 << ".0\n";
        else
            out << ret / 2 << ".5\n";
    }
}
// 도형의 넓이
long long getArea(vector<Point>& a) {
    long long ret = 0;
    for (int i = 0; i < a.size(); i++) {
        int j = (i + 1) % a.size();
        ret += (a[i].x * a[j].y - a[i].y * a[j].x);
    }
    return abs(ret);
}
// convex hull의 바깥 부분 면적을 구함
long long getOutside() {
    long long area = 0;
    for (int i = 0; i < polygon.size(); i++) {
        vector<Point> v;
        int j = (i + 1) % polygon.size();
        int start = polygon[i].idx;
        int end = polygon[j].idx;
        // convex hull을 순회할 때 같은 도형이면서
        // 인덱스가 연속적이지 않으면 바깥부분의 해당
        if (polygon[i].part == polygon[j].part) {
            // P도형의 바깥부분 면적
            if (polygon[i].part == 1 && (start + 1) % P.size() != end) {
                for (int i = start;; i = (i + 1) % P.size()) {
                    v.push_back(P[i]);
                    if (i == end) break;
                }
                area += getArea(v);
            }
            // Q도형의 바깥부분 면적
            if (polygon[i].part == 2 && (start + 1) % Q.size() != end) {
                for (int i = start;; i = (i + 1) % Q.size()) {
                    v.push_back(Q[i]);
                    if (i == end) break;
                }
                area += getArea(v);
            }
        }
    }
    return area;
}
// 두 다각형의 컨벡스헐을 구함
void convexHull(int pLen, int qLen) {
    vector<Point> temp;
    temp.reserve(pLen + qLen);

    for (int i = 0; i < pLen; i++) temp.push_back(P[i]);
    for (int i = 0; i < qLen; i++) temp.push_back(Q[i]);

    sort(temp.begin(), temp.end(), comp);
    for (int i = 1; i < temp.size(); i++) {
        temp[i].p = temp[i].x - temp[0].x;
        temp[i].q = temp[i].y - temp[0].y;
    }
    sort(temp.begin() + 1, temp.end(), comp);

    vector<int> st;
    st.push_back(0);
    st.push_back(1);
    int next = 2;

    while (next < temp.size()) {
        while (st.size() >= 2) {
            int first = st.back();
            st.pop_back();
            int second = st.back();
            if (ccw(temp[second], temp[first], temp[next]) >= 0) {
                st.push_back(first);
                break;
            }
        }
        st.push_back(next++);
    }
    polygon.resize(st.size());
    for (int i = 0; i < st.size(); i++) {
        Point p = temp[st[i]];
        polygon[i] = p;
    }
}

