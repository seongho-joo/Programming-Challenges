//
//  spiral.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/06/22.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment42 와선(기말고사 5)

#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream inp("spiral.inp");
ofstream out("spiral.out");

typedef long long lint;
struct Point{
    int x, y, p, q;
    Point() : x(0), y(0), p(1), q(0) {}
    Point(int x, int y) : x(x), y(y), p(1), q(0) {}
    bool operator < (const Point& a) const {
        if(1LL * q * a.p != 1LL * p * a.q) return 1LL * q * a.p < 1LL * p * a.q;
        if(p == 0 && a.p == 0) return q > a.q;
        if(x != a.x) return x < a.x;
        return y < a.y;
    }
};

vector<Point> p;

lint ccw(const Point& a, const Point& b, const Point& c) {
    lint ret = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if(ret < 0) return -1;
    else if(ret == 0) return 0;
    else return 1;
}

void convexHull(int n) {
    sort(p.begin(), p.end());
    for(int i = 1; i < n; i++) {
        p[i].p = p[i].x - p[0].x;
        p[i].q = p[i].y - p[0].y;
    }
    sort(p.begin() + 1, p.end());
    
    vector<Point> ans;
    ans.push_back(p[0]);
    ans.push_back(p[1]);
    int next = 2;
    
    while(next < n) {
        while(ans.size() >= 2) {
            Point f = ans.back(); ans.pop_back();
            Point s = ans.back();
            if(ccw(s, f, p[next]) >= 0) {
                ans.push_back(f);
                break;
            }
        }
        ans.push_back(p[next++]);
    }
}

int main() {
    int T;
    inp >> T;
    
    while(T--) {
        int n;
        inp >> n;
        p.resize(n);
        for(int i = 0; i < n; i++) {
            int x, y;
            inp >> x >> y;
            p[i] = Point(x, y);
        }
        convexHull(n);
    }
    
    inp.close(); out.close();
    return 0;
}
