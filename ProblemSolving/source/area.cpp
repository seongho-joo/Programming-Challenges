//
//  area.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/05/14.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment 26 삼각형 면적
#include <fstream>
#include <cmath>
using namespace std;

ifstream inp("area.inp");
ofstream out("area.out");

struct Point{
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
};

struct Circle {
    Point p;
    double r;
    Circle() : p(Point()), r(0) {}
    Circle(double x, double y, double r) : p(Point(x, y)), r(r) {}
};

bool isIntersection(Point p, Circle a) {
    Point diff;
    diff.x = p.x - a.p.x;
    diff.y = p.y - a.p.y;
    double l = sqrt((diff.x * diff.x) + (diff.y * diff.y));
    if(l > a.r) return false;
    return true;
}

Point intersection(Circle a, Circle b, Circle c) {
    Point p, q; // 두 원의 교점
    Point diff;

    double l, k;
    diff.x = b.p.x - a.p.x;
    diff.y = b.p.y - a.p.y;

    l = sqrt((diff.x * diff.x) + (diff.y * diff.y)); // 두 중점 사이의 거리
    k = ((l * l) + (a.r * a.r) - (b.r * b.r)) / (2 * l);
    
    p.x = a.p.x + (diff.x * k / l) + (diff.y / l) * sqrt((a.r * a.r) - k * k);
    p.y = a.p.y + (diff.y * k / l) - (diff.x / l) * sqrt((a.r * a.r) - k * k);
    q.x = a.p.x + (diff.x * k / l) - (diff.y / l) * sqrt((a.r * a.r) - k * k);
    q.y = a.p.y + (diff.y * k / l) + (diff.x / l) * sqrt((a.r * a.r) - k * k);
    
    if(isIntersection(p, c)) return p; // p가 세 원의 공통현의 포함되어있음
    if(isIntersection(q, c)) return q; // q가 세 원의 공통현의 포함되어있음
    return {-10000.0, -10000.0};
}

double getArea(Point a, Point b, Point c) {
    return abs((a.x * b.y) + (b.x * c.y) + (c.x * a.y) - (a.x * c.y) - (c.x * b.y) - (b.x * a.y));
}

int main() {
    int T;
    inp >> T;
    out << fixed;
    out.precision(2);
    while(T--) {
        Circle c[3];
        for(int i = 0; i < 3; i++) {
            int x, y, r;
            inp >> x >> y >> r;
            c[i] = Circle(x, y, r);
        }
        Point p1, p2, p3;
        p1 = intersection(c[0], c[1], c[2]);
        p2 = intersection(c[0], c[2], c[1]);
        p3 = intersection(c[1], c[2], c[0]);
        out << getArea(p1, p2, p3) * 0.5 << "\n";
    }
    inp.close(); out.close();
    return 0;
}
