//
//  robot.cpp
//  ProblemSolvoing
//
//  Created by 주성호 on 2020/06/22.
//  Copyright © 2020 주성호. All rights reserved.
//

#include <fstream>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
typedef long long lint;
const int mod = 1000000007;
ifstream inp("robot.inp");
ofstream out("robot.out");

vector<vector<int> > dp;

void setBoard(int n, int m) {
    for(int i = 1; i <= n; i++) dp[i][0] = 1;
    for(int i = 1; i <= m; i++) dp[0][i] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            dp[i][j] += ((dp[i - 1][j] + dp[i][j - 1]) % mod);
        }
    }
}

int main() {
    int T;
    inp >> T;
    
    while(T--) {
        int n, m;
        int ans = 0;
        pii a, b;
        inp >> n >> m >> a.first >> a.second >> b.first >> b.second;
        dp.resize(n + 1, vector<int>(m + 1, 0));
        setBoard(n, m);
        int dif = 0;
        int pathA = 0, pathB = 0;
        pathA = (1LL * dp[a.first][a.second] * dp[n - a.first][m - a.second]) % mod;
        pathB = (1LL * dp[b.first][b.second] * dp[n - b.first][m - b.second]) % mod;
        ans = (1LL * (pathA + pathB)) % mod;
        if((a.first <= b.first && a.second <= b.second)) {
            dif = 1LL * (((dp[a.first][a.second] * dp[b.first - a.first][b.second - a.second]) % mod) * dp[n - b.first][m - b.second]) % mod;
            ans -= dif;
        }
        else if((a.first >= b.first && a.second >= b.second)) {
            dif = (((dp[b.first][b.second] * dp[a.first - b.first][a.second - b.second]) % mod) * dp[n - a.first][m - a.second]) % mod;
            ans -= dif;
        }
        out << ans % mod << "\n";
        dp.clear();
    }
    
    inp.clear(); out.close();
    return 0;
}
