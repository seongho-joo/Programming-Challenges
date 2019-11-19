/**
 * Assignment 21 : Block Compaction
 */
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#define M 10001
using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
FILE *inp = fopen("block.inp", "rt");
FILE *out = fopen("block.out", "wt");

int n, T, it;
struct Vertex {
    int x, y, p, q;
    bool operator<(const Vertex &r) const { return x < r.x; }
};
Vertex rect[M];
int dx[M];             /** p가 이동해야할 x값 저장 */
int arr[M], arrnum[M]; /** dx배열을 이분탐색하기위한 배열, index */

void Input() {
    fscanf(inp, "%d", &n);
    for (int i = 0; i < n; i++)
        fscanf(inp, "%d %d %d %d", &rect[i].x, &rect[i].y, &rect[i].p,
               &rect[i].q);
}

bool blockMovement() {
    /** x축을 기준으로 정렬 */
    sort(rect, rect + n);
    it = 0;
    for (int i = 0; i < n; i++) {
        dx[i] = 0;
        /** 이분탐색을하면서 현재 x 값에서 가장가까운 p값의 인덱스 - 1 반환*/
        it = upper_bound(arr, arr + i, rect[i].x) - arr;
        /**  */
        for (int j = it - 1; j >= 0; j--) {
            /** 현재 블록의 왼쪽에 블럭이있으면 dx를 해당하는 블럭의 p값으로
             * 저장 */
            if (MAX(rect[i].y, rect[arrnum[j]].y) <
                MIN(rect[i].q, rect[arrnum[j]].q)) {
                dx[i] = arr[j];
                break;
            }
        }
        dx[i] += rect[i].p - rect[i].x;
        arr[i] = dx[i];
        arrnum[i] = i;
        /** 이분탐색을 하기위한 정렬 */
        for (int j = i; j - 1 >= 0; j--) {
            if (arr[j] < arr[j - 1]) {
                arr[j] = arr[j - 1];
                arrnum[j] = arrnum[j - 1];
                arr[j - 1] = dx[i];
                arrnum[j - 1] = i;
            } else
                break;
        }
    }
    /** 블럭이 움직이면 true 움직이지 않으면 false */
    bool ret = false;
    /** 블럭의 이동 */
    for (int i = 0; i < n; i++) {
        int value = rect[i].p - dx[i];
        rect[i].x -= value;
        rect[i].p -= value;
        if (value > 0) ret = true;
    }
    return ret;
}

void solve() {
    bool flag;
    while (true) {
        // downward
        for (int i = 0; i < n; i++) {
            swap(rect[i].x, rect[i].y);
            swap(rect[i].p, rect[i].q);
        }
        flag = blockMovement();
        // leftward
        for (int i = 0; i < n; i++) {
            swap(rect[i].x, rect[i].y);
            swap(rect[i].p, rect[i].q);
        }
        flag |= blockMovement();
        if (!flag) break;
    }
    int maxX = 0, maxY = 0;
    for (int i = 0; i < n; i++)
        maxX = MAX(rect[i].p, maxX), maxY = MAX(maxY, rect[i].q);
    fprintf(out, "%d %d\n", maxX, maxY);
}

int main() {
    fscanf(inp, "%d", &T);
    while (T--) {
        Input();
        solve();
    }
    return 0;
}