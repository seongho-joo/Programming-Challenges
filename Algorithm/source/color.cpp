/**
 * Assignment 20 - Color Length
 */
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>
using namespace std;

ifstream inp("color.inp");
ofstream out("color.out");

string car[2];
vector<vector<int> > cache;
vector<int> total, part; // 주어진 자동차 색의 수, 부분적으로 나눈 자동차 색의 수

void Init() {
    cache.clear();
    total.clear();
    total.resize(26, 0);
    for (int i = 0; i < 2; i++) {
        inp >> car[i];
        for (int j = 0; j < car[i].size(); j++) total[car[i][j] - 'A'] += 1;
    }
    for (int i = 0; i < 2; i++) car[i].insert(car[i].begin(), 'a');
    cache.resize(car[0].size(), vector<int>(car[1].size()));
}
// 주어진 자동차의 색의 수와 부분적 자동차 색의 수를 비교해서 색이다른 자동차 갯수 카운팅
int getCount() {
    int cnt = 0;
    for (int i = 0; i < 26; i++)
        if (part[i] != 0)
            if (part[i] != total[i]) cnt += 1;
    return cnt;
}

void solution() {
    int cnt = 0;
    for (int i = 0; i < car[0].size(); i++) {
        part.clear();
        part.resize(26, 0);
        // car[0][i]까지 자동차 색 카운팅
        for (int k = 0; k <= i; k++) {
            char c0 = car[0][k];
            if (c0 != 'a') part[c0 - 'A'] += 1;
        }
        // car[1][j]까지 알파벳 카운팅
        for (int j = 0; j < car[1].size(); j++) {
            char c1 = car[1][j];
            if (c1 != 'a') part[c1 - 'A'] += 1;
            if (i == j && i == 0)
                cache[i][j] = 0;
            else {
                // 기존의 알파벳 갯수와 다른 알파벳의 개수를 구함
                cnt = getCount();
                if (i == 0)
                    cache[i][j] = cache[i][j - 1] + cnt;
                else if (j == 0)
                    cache[i][j] = cache[i - 1][j] + cnt;
                else
                    cache[i][j] = min(cache[i - 1][j], cache[i][j - 1]) + cnt;
            }
        }
    }
}

int main() {
    int n;
    inp >> n;
    while (n--) {
        Init();
        int i = car[0].size() - 1, j = car[1].size() - 1;
        solution();
        out << cache[i][j] << '\n';
    }
    inp.close();
    out.close();
    return 0;
}