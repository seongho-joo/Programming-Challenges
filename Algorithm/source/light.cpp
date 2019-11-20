/**
 * Assignment 23 : 가로등
 */
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;
typedef pair<int, int> pii;

ifstream inp("light.inp");
ofstream out("light.out");
vector<pii> lamp, section;
int n, k;

bool compare(const pii &a, const pii &b) { return a.first < b.first; }

void Input() {
    inp >> n;
    /** 가로등 밝기 입력 */
    lamp.resize(n);
    for (int i = 0; i < n; i++) inp >> lamp[i].first >> lamp[i].second;

    inp >> k;
    section.resize(k);
    /** 밝히고자하는 구간 입력 */
    for (int i = 0; i < n; i++) inp >> section[i].first >> section[i].second;
    sort(lamp.begin(), lamp.end(), compare);
}

void solution() {
    int left, cnt, idx;
    for (int i = 0; i < k; i++) {
        cnt = 0, left = section[i].first, idx = -1;
        bool flag = false, check = false;
        while (true) {
            int MAX = -1;
            check = false;
            int temp = idx;
            idx = upper_bound(lamp.begin(), lamp.end(), pii(left, 0), compare) -
                  lamp.begin();
            /** 밝히려는 구간을 다 밝히지 못함 */
            if (idx == temp) {
                check = true;
                break;
            }
            for (int j = idx - 1; j >= 0; j--) {
                if (lamp[j].second > section[i].first) {
                    if (lamp[j].second >= section[i].second) {
                        flag = true;
                        break;
                    }
                    if (MAX < lamp[j].second) {
                        MAX = lamp[j].second;
                        left = MAX;
                    }
                }
            }
            cnt += 1;
            if (flag || check) break;
        }
        if (check)
            out << -1 << '\n';
        else
            out << cnt << '\n';
    }
}

int main() {
    Input();
    solution();

    inp.close();
    out.close();
    return 0;
}
