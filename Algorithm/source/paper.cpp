/**
 * Assignment 04 : Color Paper
 */
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("paper.inp");
ofstream out("paper.out");

struct Paper {
    int x, y, w, h;
};

int board[10000][10000];
vector<Paper> paper;
vector<int> idx;
// 완전히 가려진 종이, 부분적으로 가려진 종이, 완전히 보이는 종이
int cover, section, all;

void Insert(Paper p) {
    idx.push_back(p.x);
    idx.push_back(p.y);
    idx.push_back(p.w);
    idx.push_back(p.h);
}
// 좌표압축
void Compression(int len) {
    sort(idx.begin(), idx.end());
    idx.erase(unique(idx.begin(), idx.end()), idx.end());  // 중복 제거

    for (int i = 0; i < len; i++) {
        paper[i].x =
            lower_bound(idx.begin(), idx.end(), paper[i].x) - idx.begin();
        paper[i].y =
            lower_bound(idx.begin(), idx.end(), paper[i].y) - idx.begin();
        paper[i].w =
            lower_bound(idx.begin(), idx.end(), paper[i].w) - idx.begin();
        paper[i].h =
            lower_bound(idx.begin(), idx.end(), paper[i].h) - idx.begin();
    }
}
// 2차원배열에 종이세팅
void paperCover(int len) {
    for (int i = 0; i < len; i++)
        for (int j = paper[i].y; j < paper[i].h; j++)
            for (int k = paper[i].x; k < paper[i].w; k++) board[j][k] = i;
}

void solution() {
    int n = paper.size();
    Compression(n);
    paperCover(n);

    bool visible = false, unvisible = false;

    for (int i = 0; i < n; i++) {
        visible = false, unvisible = false;
        for (int j = paper[i].y; j < paper[i].h; j++) {
            for (int k = paper[i].x; k < paper[i].w; k++) {
                if (board[j][k] == i)
                    visible = true;
                else
                    unvisible = true;
            }
        }
        if (visible && unvisible) // 부분적으로 가려진 종이
            section += 1;
        else if (visible) // 완전히 보이는 종이
            all += 1;
        else // 완전히 가려진 종이
            cover += 1;
    }
}

int main() {
    Paper p;

    int n;  // 색종이의 수
    inp >> n;
    paper.reserve(n);

    while (n--) {
        inp >> p.x >> p.y >> p.w >> p.h;
        p.w += p.x;
        p.h += p.y;
        paper.push_back(p);
        Insert(p);
    }

    solution();

    out << cover << ' ' << section << ' ' << all;

    inp.close();
    out.close();
    return 0;
}