/**
 * Assignment 11 - Points inside in a polygon P
 */
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

ifstream inp("point.inp");
ofstream out("point.out");
vector<Point> polygon;
int N, P, x, y;

bool isInside(Point p) {
    int cross = 0;
    for (int i = 0; i < N; i++) {
        int j = (i + 1) % N;
        if ((p.x == polygon[i].x && p.y == polygon[i].y) ||
            (p.x == polygon[j].x && p.y == polygon[j].y))
            return true;
        if ((polygon[i].y > p.y) != (polygon[j].y > p.y)) {
            double atX = (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) /
                             (polygon[j].y - polygon[i].y) +
                         polygon[i].x;
            if (p.x < atX) cross += 1;
        }
    }

    return cross % 2 > 0;
}

void solve() {
    inp >> P;
    while (P--) {
        Point k;
        inp >> k.x >> k.y;
        out << (isInside(k) ? 1 : 0) << '\n';
    }
}

int main() {
    inp >> N;
    polygon.resize(N);

    for (int i = 0; i < N; i++) {
        inp >> x >> y;
        polygon[i] = Point(x, y);
    }

    solve();

    inp.close(), out.close();
    return 0;
}