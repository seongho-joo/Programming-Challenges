/**
 * assignDoc12 : 바둑 집 계산
 */
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("go.inp");
ofstream out("go.out");

struct Coor {
    int y, x;
};

vector<vector<char> > board;
vector<vector<bool> > v;
vector<Coor> coor;  // 아무 돌도 없는곳의 좌표
int dy[4] = {1, -1, 0, 0};
int dx[4] = {0, 0, 1, -1};
int k, black, white, cnt = 0;
bool B, W;

void Init() {
    Coor c;
    coor.clear();
    v.clear();
    v.resize(k, vector<bool>(k, false));
    board.clear();
    board.resize(k, vector<char>(k));

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            inp >> board[i][j];
            c.y = i;
            c.x = j;
            if (board[i][j] == '.') coor.push_back(c);
        }
}
// .주변에 흰 돌과 흑 돌이 있는지 체크
void checkAround(int y, int x) {
    bool flag = false;
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny > -1 && ny < k && nx > -1 && nx < k) {
            if (board[ny][nx] == '.') flag = true;
            if (board[ny][nx] == 'B')
                B = true;
            else if (board[ny][nx] == 'W')
                W = true;
        }
    }
    // 빈 곳이 하나 일 경우
    if (!flag) cnt = 1;
}

void DFS(int y, int x) {
    checkAround(y, x);
    for (int i = 0; i < 4; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny > -1 && ny < k && nx > -1 && nx < k) {
            if (board[ny][nx] == '.') {
                if (!v[ny][nx]) {
                    cnt++;
                    v[ny][nx] = true;
                    DFS(ny, nx);
                }
            }
        }
    }
}

void solve() {
    for (int i = 0; i < coor.size(); i++) {
        int y = coor[i].y, x = coor[i].x;
        if (!v[y][x]) {
            DFS(coor[i].y, coor[i].x);
            if (B && !W) black += cnt;
            if (W && !B) white += cnt;
            B = false;
            W = false;
            cnt = 0;
        }
    }
}

int main() {
    inp >> k;

    Init();
    solve();
    out << black << ' ' << white;
    inp.close();
    out.close();
    return 0;
}