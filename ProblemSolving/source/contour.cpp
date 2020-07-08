//
//  contour.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/06/08.
//  Copyright © 2020 주성호. All rights reserved.
//
//  Assignment35 Sky Line

#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

typedef long long lint;
const int MAX = 4000004;
ifstream inp("contour.inp");
ofstream out("contour.out");

struct Building {
    lint x, y, height, div;
    Building() : x(0), y(0), height(0), div(0) {}
    Building(lint x, lint h, lint div) : x(x), y(0), height(h), div(div) {}
    bool operator < (const Building& a) const {
        if(x == a.x) return y > a.y;
        return x < a.x;
    }
};
vector<Building> coor;
lint cnt[MAX], tree[MAX];

void update(lint idx, lint left, lint right, lint start, lint end, lint val) {
    if(left > end || right < start) return;
    if(left <= start && end <= right) cnt[idx] += val;
    else {
        lint mid = (start + end) / 2;
        update(idx * 2, left, right, start, mid, val);
        update(idx * 2 + 1, left, right, mid + 1, end, val);
    }
    
    if(!cnt[idx]) {
        if(start != end) tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
        else tree[idx] = 0;
    }
    else tree[idx] = end - start + 1;
}

void solve() {
    lint ret = 0;
    for(int i = 0; i < coor.size(); i++) {
        if (i > 0) ret += (coor[i].x - coor[i - 1].x) * tree[1];
        update(1, 0, coor[i].height, 0, (MAX / 4) - 1, coor[i].div);
        if(i != 0 && tree[1] == 0) {
            out << ret << " ";
            ret = 0;
        }

    }
    out << "\n";
}

int main() {
    lint x, dx, h;
    int i = 1;
    while(inp >> x >> h >> dx) {
        if(x == 0 && dx == 0 && h == 0) {
            out << "Test Case #" << i++ << " : ";
            sort(coor.begin(), coor.end());
            solve();
            coor.clear();
            continue;
        }
        coor.push_back(Building(x, h - 1, 1));
        coor.push_back(Building(dx, h - 1, -1));
    }
    
    inp.close(); out.close();
    return 0;
}

