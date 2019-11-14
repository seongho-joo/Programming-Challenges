/**
 * Assignment 22 : 물탱크
 */
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

struct Tank {
    int y, x, h;
};

struct Compare {
    bool operator()(const Tank& x, const Tank& y) { return x.h > y.h; }
};
ifstream inp("watertank.inp");
ofstream out("watertank.out");

int n, m, h;
vector<vector<int> > height;   // 물의 높이를 저장
vector<vector<int> > hole[2];  // [0] : 가로 구멍, [1] : 세로 구멍

void Input() {
    inp >> n >> m >> h;
    height.resize(n, vector<int>(m));
    hole[0].resize(n + 1, vector<int>(m));  // 가로 구멍 크기 지정
    hole[1].resize(n, vector<int>(m + 1));  // 세로 구멍 크기 지정
    // 초기에 물의 높이는 물탱크 높이
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) height[i][j] = h;
    // 가로구멍 입력
    for (int i = 0; i < n + 1; i++)
        for (int j = 0; j < m; j++) inp >> hole[0][i][j];
    // 세로구멍 입력
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m + 1; j++) inp >> hole[1][i][j];
}

Tank Init(int y, int x, int h) {
    Tank t;
    t.y = y;
    t.x = x;
    t.h = h;
    return t;
}
// 바깥과 통하는 벽들의 구멍을 찾고 물 높이 저장
void holeInput(priority_queue<Tank, vector<Tank>, Compare>& pq) {
    Tank t;
    for (int i = 0; i < m; i++) {
        // 첫번째 가로벽
        if (hole[0][0][i] != -1) {
            height[0][i] = hole[0][0][i], height[0][i];
            pq.push(Init(0, i, height[0][i]));
        }
        // n + 1번째 가로벽
        if (hole[0][n][i] != -1) {
            height[n - 1][i] = hole[0][n][i];
            pq.push(Init(n - 1, i, height[n - 1][i]));
        }
    }
    for (int i = 0; i < n; i++) {
        // 첫번째 세로벽
        if (hole[1][i][0] != -1) {
            height[i][0] = min(hole[1][i][0], height[i][0]);
            pq.push(Init(i, 0, height[i][0]));
        }
        // m + 1 세로벽
        if (hole[1][i][m] != -1) {
            height[i][m - 1] = min(hole[1][i][m], height[i][m - 1]);
            pq.push(Init(i, m - 1, height[i][m - 1]));
        }
    }
}
// BFS로 풀이
int solve() {
    Tank t;
    priority_queue<Tank, vector<Tank>, Compare> tank;
    vector<vector<bool> > visited;
    visited.resize(n, vector<bool>(m, false));
    holeInput(tank);

    while (!tank.empty()) {
        int y = tank.top().y, x = tank.top().x;
        tank.pop();
        if (visited[y][x]) continue;
        // 위쪽 가로벽 구멍이 있고 위쪽 물 높이가 더 높을경우
        if (hole[0][y][x] != -1 && y != 0 && height[y][x] < height[y - 1][x]) {
            /**
             * 현재 물 높이보다 크거나 같을경우 위 물 높이는 구멍 높이로 변경
             * 작을 경우 현재 물 높이로 변경
             */
            if (height[y][x] <= hole[0][y][x])
                height[y - 1][x] = min(hole[0][y][x], height[y - 1][x]);
            else
                height[y - 1][x] = height[y][x];
            visited[y][x] = true;
            tank.push(Init(y - 1, x, height[y - 1][x]));
        }
        // 아래쪽 가로벽에 구멍이 있고 아래쪽 물 높이가 더 높을경우
        if (hole[0][y + 1][x] != -1 && y != n - 1 &&
            height[y][x] < height[y + 1][x]) {
            /**
             * 현재 물 높이보다 크거나 같을경우 아래 물 높이는 구멍 높이로
             * 변경 작을 경우 현재 물 높이로 변경
             */
            if (height[y][x] <= hole[0][y + 1][x])
                height[y + 1][x] = min(hole[0][y + 1][x], height[y + 1][x]);
            else
                height[y + 1][x] = height[y][x];
            visited[y][x] = true;
            tank.push(Init(y + 1, x, height[y + 1][x]));
        }
        // 왼쪽 가로벽에 구멍이 있고 왼쪽 물 높이가 더 높을경우
        if (hole[1][y][x] != -1 && x != 0 && height[y][x] < height[y][x - 1]) {
            /**
             * 현재 물 높이보다 크거나 같을경우 왼쪽 물 높이는 구멍 높이로
             * 변경 작을 경우 현재 물 높이로 변경
             */
            if (height[y][x] <= hole[1][y][x])
                height[y][x - 1] = min(height[y][x - 1], hole[1][y][x]);
            else
                height[y][x - 1] = height[y][x];
            visited[y][x] = true;
            tank.push(Init(y, x - 1, height[y][x - 1]));
        }
        // 오른쪽 가로벽에 구멍이 있고 오른쪽 물 높이가 더 높을경우
        if (hole[1][y][x + 1] != -1 && x != m - 1 &&
            height[y][x] < height[y][x + 1]) {
            /**
             * 현재 물 높이보다 크거나 같을경우 오른쪽 물 높이는 구멍
             * 높이로 변경 작을 경우 현재 물 높이로 변경
             */
            if (height[y][x] < hole[1][y][x + 1])
                height[y][x + 1] = min(height[y][x + 1], hole[1][y][x + 1]);
            else
                height[y][x + 1] = height[y][x];
            visited[y][x] = true;
            tank.push(Init(y, x + 1, height[y][x + 1]));
        }
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) sum += height[i][j];
    return sum;
}

int main() {
    int T;
    inp >> T;
    while (T--) {
        height.clear();
        hole[0].clear();
        hole[1].clear();
        Input();
        out << solve() << '\n';
    }
    inp.close();
    out.close();
    return 0;
}