//
//  scud.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/06/08.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment36 Scud

#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

typedef long long lint;
ifstream inp("scud.inp");
ofstream out("scud.out");

struct Point {
    int x, y, p, q;
    Point() : x(0), y(0), p(1), q(0) {}
    Point(int x, int y) : x(x), y(y), p(1), q(0) {}
    bool operator < (const Point A) const {
        if (1LL * q * A.p != 1LL * p * A.q) return 1LL * q * A.p < 1LL * p * A.q;
        if(y != A.y) return y < A.y;
        return x < A.x;
    }
};

struct Kingdom {
    vector<Point> hull;
    double area;
    bool disappear;
    Kingdom() : area(0), disappear(false) {}
    Kingdom(vector<Point>& p, double area) : hull(p), area(area), disappear(false) {}
};

vector<Kingdom> kingdom;
vector<Point> P;
vector<bool> duplicate;

lint ccw(Point& A, Point& B, Point& C) {
    lint ret = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    if (ret > 0) return 1;
    else if (ret == 0) return 0;
    else return -1;
}

double getArea(lint n, vector<Point> k) {
    double area = 0.0;
    for(int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (k[i].x * k[j].y - k[i].y * k[j].x);
    }
    return area / 2;
}

void convexhull(int n) {
    vector<Point> hull;
    sort(P.begin(), P.end());
    for(int i = 0; i < n; i++) {
        P[i].p = P[i].x - P[0].x;
        P[i].q = P[i].y - P[0].y;
    }
    sort(P.begin(), P.end());
    
    hull.push_back(P[0]);
    hull.push_back(P[1]);
    int next = 2;
    
    while(next < n) {
        while(hull.size() >= 2) {
            Point first = hull.back(); hull.pop_back();
            Point second = hull.back();
            if(ccw(second, first, P[next]) > 0) {
                hull.push_back(first);
                break;
            }
        }
        hull.push_back(P[next++]);
    }
    double area = getArea(hull.size(), hull);
    kingdom.push_back(Kingdom(hull, area));
}

bool isInside(vector<Point> k, Point p) {
    lint len = k.size();
    for(int i = 0; i < len; i++) {
        int j = (i + 1) % len;
        // 반시계가 아니면 점이 포함되지 않음
        if (ccw(k[i], k[j], p) < 0) return false;
        else if(ccw(k[i], k[j], p) == 0) {
            if((max(k[i].x, k[j].x) < p.x) || (min(k[i].x, k[j].x) > p.x)) return false;
            if((max(k[i].y, k[j].y) < p.y) || (min(k[i].y, k[j].y) > p.y)) return false;
        }
    }
    return true;
}

int main() {
    int n;
    while(true) {
        inp >> n;
        if(n == -1) break;
        P.resize(n);
        for(int i = 0; i < n; i++) {
            int x, y;
            inp >> x >> y;
            P[i] = Point(x, y);
        }
        convexhull(n);
        P.clear();
    }
    Point p;
    lint len = kingdom.size();
    duplicate.resize(len, false);
    double ans = 0.0;
    while(inp >> p.x >> p.y) {
        for(int i = 0; i < len; i++) {
            if(!duplicate[i]) {
                kingdom[i].disappear = isInside(kingdom[i].hull, p);
                if(kingdom[i].disappear) {
                    ans += kingdom[i].area;
                    duplicate[i] = true;
                }
            }
        }
    }
    out << fixed;
    out.precision(2);
    out << ans << "\n";
    inp.close(); out.close();
    return 0;
}
