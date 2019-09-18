/**
 * Assignment 07 : 도치 수 (Inversion Number)
 */
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("inv.inp");
ofstream out("inv.out");
vector<int> seq, m;
long long ans = 0;

void Init(int n) {
    ans = 0;
    seq.clear();
    seq.reserve(n);
    m.resize(n);
    int num;
    while (n--) {
        inp >> num;
        seq.push_back(num);
    }
}

void merge(int left, int right) {
    int mid = (left + right) / 2;
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (seq[i] <= seq[j])
            m[k] = seq[i++];
        else {
            m[k] = seq[j++];
            ans += (mid - i + 1);
        }
        k++;
    }
    if (i > mid)
        for (int x = j; x <= right; x++) m[k++] = seq[x];
    else
        for (int x = i; x <= mid; x++) m[k++] = seq[x];

    for (int i = left; i <= right; i++) seq[i] = m[i];
}

void Divide(int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        Divide(left, mid);
        Divide(mid + 1, right);
        merge(left, right);
    }
}

int main() {
    int T;
    inp >> T;

    while (T--) {
        int n;  // 수열의 개수
        inp >> n;
        Init(n);
        Divide(0, n - 1);
        out << ans << '\n';
    }

    inp.close();
    out.close();
    return 0;
}