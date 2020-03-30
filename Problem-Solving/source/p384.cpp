/**
 * Assignment 07 - Slurpys
 */
#include <fstream>
#include <string>
using namespace std;

ifstream inp("p384.inp");
ofstream out("p384.out");

int T;
string word;

bool isSlumps(string sub) {
    int len = sub.length();
    /** Slump가 만족하려면 최소한 3자 이상이여야함 */
    if (len < 3 || (sub[0] != 'D' && sub[0] != 'E') || sub[1] != 'F')
        return false;
    int index = 2;
    while (sub[index] == 'F') index += 1;
    /** G는 항상 마지막에 존재 */
    if (index == len - 1 && sub[index] == 'G')
        return true;
    else  // E나 D가 다시 나온 경우
        return isSlumps(sub.substr(index, len - index));
}

bool isSlimps(string sub) {
    int len = sub.length();
    /** Slimp는 항상 A로 시작함 */
    if (sub[0] != 'A') return false;
    if (len == 2 && sub[1] == 'H')
        return true;  // AH로 끝나는 경우 Slimps는 끝남
    if (sub[len - 1] != 'C')
        return false;  // AH로 시작하는 경우가 아닌경우는 C가 반드시 있어야함
    if (sub[1] == 'B')
        return isSlimps(sub.substr(2, len - 3));
    else
        return isSlumps(sub.substr(1, len - 2));  // A (Slumps) C인 경우
}
int main() {
    inp >> T;

    out << "SLURPYS OUTPUT\n";
    while (T--) {
        inp >> word;
        bool ans = false;
        for (int i = word.size() - 1; i >= 0; i--) {
            if (word[i] == 'C' || word[i] == 'H') {
                ans = isSlimps(word.substr(0, i + 1)) &&
                      isSlumps(word.substr(i + 1, word.size() - i - 1));
                break;
            }
        }
        out << (ans ? "YES" : "NO") << '\n';
    }
    out << "END OF OUTPUT";
    inp.close(), out.close();
    return 0;
}