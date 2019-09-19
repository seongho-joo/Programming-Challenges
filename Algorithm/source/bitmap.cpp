/**
 * Assignment 08 : BitMap
 */
#include <fstream>
#include <vector>
using namespace std;

ifstream inp("bitmap.inp");
ofstream out("bitmap.out");
vector<vector<char> > map;
int y = 0, x = 0, cnt = 0;

bool isSame(int y, int x, int n, int m) {
    for (int i = y; i < n; i++)
        for (int j = x; j < m; j++)
            if (map[i][j] != map[y][x]) return false;
    return true;
}

int div(int x) {
    if (x % 2 == 0) return x / 2;
    return (x / 2) + 1;
}
// B -> D
void Compression(int y, int x, int n, int m) {
    if (isSame(y, x, n, m)) {
        out << map[y][x];
        cnt += 1;
        if (cnt % 50 == 0) out << '\n';
    } else {  // 원소가 같지않으면 분할
        out << 'D';
        cnt += 1;
        if (cnt % 50 == 0) out << '\n';
        // 행이 하나일 경우
        if (n - y == 1) {
            Compression(y, x, div(n + y), div(m + x));  // 좌측
            Compression(y, div(m + x), n, m);           // 우측
        }  // 열이 하나일 경우
        else if (m - x == 1) {
            Compression(y, x, div(n + y), m);  // 상단
            Compression(div(n + y), x, n, m);  // 하단
        } else {
            Compression(y, x, div(n + y), div(m + x));  // 좌측상단
            Compression(y, div(m + x), div(n + y), m);  // 우측상단
            Compression(div(n + y), x, n, div(m + x));  // 좌측하단
            Compression(div(n + y), div(m + x), n, m);  // 우측하단
        }
    }
}
// D -> B
void Decompression(int y, int x, int n, int m) {
    char data;
    inp >> data;
    if (data == '\n') inp >> data;
    if (data != 'D') {
        for (int i = y; i < n; i++)
            for (int j = x; j < m; j++) map[i][j] = data;
    } else {
        if (n - y == 1) {
            Decompression(y, x, div(n + y), div(m + x));  // 좌측
            Decompression(y, div(m + x), n, m);           // 우측
        } else if (m - x == 1) {
            Decompression(y, x, div(n + y), m);  // 상단
            Decompression(div(n + y), x, n, m);  // 하단
        } else {
            Decompression(y, x, div(n + y), div(m + x));  // 좌측상단
            Decompression(y, div(m + x), div(n + y), m);  // 우측상단
            Decompression(div(n + y), x, n, div(m + x));  // 좌측하단}
            Decompression(div(n + y), div(m + x), n, m);  // 우측하단
        }
    }
}

int main() {
    while (true) {
        char type, data;
        inp >> type >> y >> x;
        if (type == '#') break;
        map.resize(y, vector<char>(x));
        if (type == 'B') {
            out << "D  " << y << "  " << x << '\n';
            for (int i = 0; i < y; i++) {
                for (int j = 0; j < x; j++) {
                    inp >> data;
                    if (data == '\n') {
                        j--;
                        continue;
                    }
                    map[i][j] = data;
                }
            }
            Compression(0, 0, y, x);
            out << '\n';
        } else {
            out << "B  " << y << "  " << x << '\n';
            Decompression(0, 0, y, x);
            for (int i = 0; i < y; i++)
                for (int j = 0; j < x; j++) {
                    out << map[i][j];
                    cnt++;
                    if (cnt % 50 == 0) out << '\n';
                }
            if (cnt % 50 != 0) out << '\n';
        }
        cnt = 0;
        map.clear();
    }

    inp.close();
    out.close();
    return 0;
}