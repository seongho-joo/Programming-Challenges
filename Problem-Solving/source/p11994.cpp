/**
 * Assignment 09 - Happy Painting!
 */
#include <fstream>
#include <set>
#include <vector>
using namespace std;

ifstream inp("p11994.inp");
ofstream out("p11994.out");

struct Tree {
    int parent, color;
};

int n, m, t, x, y, c;
int cnt, p;
vector<Tree> tree;
vector<bool> v;
set<int> color;

void input() {
    int num;
    inp >> n >> m;
    tree.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        inp >> num;
        if (num == 0)
            tree[i].parent = i;
        else
            tree[i].parent = num;
    }

    for (int i = 1; i <= n; i++) {
        inp >> num;
        if (tree[i].parent != i) tree[i].color = num;
    }
}

void updateColor(int u) {
    if (u == p)
        return;
    else {
        tree[u].color = c;
        updateColor(tree[u].parent);
    }
}

void findX(int u) {
    v[u] = true;
    if (u == tree[u].parent) return;
    return findX(tree[u].parent);
}

void findY(int u) {
    if (v[u]) {
        p = u;
        return;
    }
    if (u == tree[u].parent) return;
    findY(tree[u].parent);
}

bool checkAncestor() {
    if (x == y) return false;
    for (int i = y;; i = tree[i].parent) {
        if (i == x) return false;
        if (i == tree[i].parent) break;
    }
    return true;
}

void solve() {
    while (m--) {
        p = -1;
        inp >> t >> x >> y;
        v.assign(n + 1, false);
        cnt = 0;

        findX(x);
        findY(y);
        switch (t) {
            case 1:
                inp >> c;
                // x와 y가 같거나 x가 y의 조상이면 연산 수행 x
                if (checkAncestor()) {
                    tree[x].parent = y;
                    tree[x].color = c;
                }
                break;
            case 2:
                inp >> c;
                // x와 y의 조상이 다르면 연산수행 x
                if (p != -1) {
                    updateColor(x);
                    updateColor(y);
                }
                break;
            case 3:
                // x와 y의 조상이 다르면 연산수행 x
                if (p == -1)
                    out << "0 0\n";
                else {
                    for (int i = x; i != p; i = tree[i].parent) {
                        color.insert(tree[i].color);
                        cnt += 1;
                    }
                    for (int i = y; i != p; i = tree[i].parent) {
                        color.insert(tree[i].color);
                        cnt += 1;
                    }
                    out << cnt << ' ' << color.size() << '\n';
                    color.clear();
                    cnt = 0;
                }
                break;
        }
    }
}

int main() {
    input();
    solve();
    inp.close(), out.close();
    return 0;
}