/**
 * Assignment 02 : 팰린드롬(Palindrome)
 */
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

ifstream inp("palindrome.inp");
ofstream out("palindrome.out");
string str;

int solve() {
    int len = str.size(), MAX, lcs_len = 0;
    vector<vector<int> > table;
    string reverseStr = str;
    reverse(reverseStr.begin(), reverseStr.end());

    table.resize(len + 1, vector<int>(len + 1, 0));
    // LCS
    for (int i = 1; i < len + 1; i++) {
        MAX = 0;
        table[i][0] = 0;
        for (int j = 1; j < len + 1; j++) {
            if (str[i - 1] == reverseStr[j - 1]) {
                MAX = table[i - 1][j - 1] + 1;
                table[i][j] = MAX;
            } else {
                if (table[i][j - 1] > table[i - 1][j])
                    table[i][j] = table[i][j - 1];
                else
                    table[i][j] = table[i - 1][j];
            }
        }
        lcs_len = lcs_len > MAX ? lcs_len : MAX;
    }
    return len - lcs_len;
}

int main() {
    int T;
    inp >> T;

    while (T--) {
        inp >> str;
        int res = solve();
        if (res < 3)
            out << res << '\n';
        else
            out << -1 << '\n';
    }

    inp.close();
    out.close();
    return 0;
}