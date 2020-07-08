//
//  rectangles.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/04/21.
//  Copyright © 2020 주성호. All rights reserved.
//

/**
 * Assignment 13 - 직사각형 합의 면적
 */
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("rectangles.inp");
ofstream out("rectangles.out");
const int MAX = 20001;

struct Rec {
    int x, y, dy, div;
    Rec() : x(0), y(0), dy(0), div(0) {}
    Rec(int x, int y, int dy, int div) : x(x), y(y), dy(dy), div(div) {}
};

vector<Rec> rec;
int cnt[MAX * 4], tree[MAX * 4];
bool comp(Rec& a, Rec& b) { return a.x < b.x; }

void update(int idx, int left, int right, int start, int end, int value) {
    if (left > end || right < start) return;
    if (left <= start && end <= right)
        cnt[idx] += value;
    else {
        int mid = (start + end) / 2;
        update(idx * 2, left, right, start, mid, value);
        update(idx * 2 + 1, left, right, mid + 1, end, value);
    }
    if (!cnt[idx]) {
        if (start != end)
            tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
        else
            tree[idx] = 0;
    } else
        tree[idx] = end - start + 1;
}

int main() {
    int n;
    inp >> n;

    rec.resize(2 * n);
    for (int i = 0; i < n; i++) {
        int x, y, x1, y1;
        inp >> x >> y >> x1 >> y1;
        rec[i] = Rec(x, y + 10001, y1 + 10000, 1);        // 왼쪽 선분
        rec[i + n] = Rec(x1, y + 10001, y1 + 10000, -1);  // 오른쪽 선분
    }
    sort(rec.begin(), rec.end(), comp);

    int ret = 0;
    // plane sweeping
    for (int i = 0; i < 2 * n; i++) {
        if (i > 0) ret += (rec[i].x - rec[i - 1].x) * tree[1];
        update(1, rec[i].y, rec[i].dy, 0, MAX - 1, rec[i].div);
    }
    out << ret;
    inp.close(), out.close();
    return 0;
}
