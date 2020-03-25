/**
 * Assignment5 - To Carry or not to Carry
 */
#include <algorithm>
#include <cmath>
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("p10469.inp");
ofstream out("p10469.out");

const int MAX = 32;
long long x, y;
vector<int> binaryX, binaryY, sum;

vector<int> binarization(long long decimal) {
    vector<int> binary;

    while (true) {
        binary.push_back(decimal % 2);
        decimal /= 2;
        if (decimal < 2) {
            binary.push_back(decimal);
            break;
        }
    }

    // reverse(binary.begin(), binary.end());
    return binary;
}

long long solve(int len) {
    sum.resize(len, 0);

    for (int i = 0; i < len; i++) {
        if (binaryX[i] == 1 && binaryY[i] == 1)
            sum[i] = 0;
        else
            sum[i] = binaryX[i] + binaryY[i];
    }
    long long result = 0;

    for (int i = 0; i < len; i++) {
        result += (long long)pow(2, i) * sum[i];
    }

    return result;
}

int main() {
    while (inp >> x >> y, x != -1) {
        binaryX.reserve(32), binaryY.reserve(32);
        binaryX = binarization(x), binaryY = binarization(y);

        while (binaryX.size() < binaryY.size()) binaryX.push_back(0);
        while (binaryY.size() < binaryX.size()) binaryY.push_back(0);

        out << solve(binaryX.size()) << '\n';
        x = -1, y = -1;
    }

    inp.close(), out.close();
    return 0;
}