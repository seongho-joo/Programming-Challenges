/**
 * Assignment 05 : Cube Painting
 */
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string cube, cube1, cube2;
ifstream inp("cube.inp");
ofstream out("cube.out");
// cube1과 cube2의 rgb개수가 같은지 확인
bool chkRGBNum() {
    int g = 0, r = 0, b = 0;
    int cp1, cp2, cp3;
    for (int i = 0; i < cube.length(); i++) {
        if (i == 6) {
            cp1 = g;
            cp2 = r;
            cp3 = b;
            g = 0;
            r = 0;
            b = 0;
        }
        if (cube[i] == 'g') g += 1;
        if (cube[i] == 'r') r += 1;
        if (cube[i] == 'b') b += 1;
    }
    if (cp1 == g && cp2 == r && cp3 == b)
        return true;
    else
        return false;
}
// 주사위 오른쪽으로 회전
string rotateRight(string sp) {
    string temp = sp;
    temp[1] = sp[2];
    temp[2] = sp[4];
    temp[3] = sp[1];
    temp[4] = sp[3];
    return temp;
}
// 주사위 왼쪽으로 회전
string rotateLeft(string sp) {
    string temp = sp;
    temp[1] = sp[3];
    temp[2] = sp[1];
    temp[3] = sp[4];
    temp[4] = sp[2];
    return temp;
}
// 주사위 위로 회전
string rotateUp(string sp) {
    string temp = sp;
    temp[0] = sp[1];
    temp[1] = sp[5];
    temp[4] = sp[0];
    temp[5] = sp[4];
    return temp;
}
// 주사위 아래로 회전
string rotateDown(string sp) {
    string temp = sp;
    temp[0] = sp[4];
    temp[1] = sp[0];
    temp[4] = sp[5];
    temp[5] = sp[1];
    return temp;
}
// 시계방향 회전
string clockwiseDiretion(string sp) {
    string temp = sp;
    temp[0] = sp[2];
    temp[2] = sp[5];
    temp[3] = sp[0];
    temp[5] = sp[3];
    return temp;
}
// 반시계방향 회전
string counterclockwise(string sp) {
    string temp = sp;
    temp[0] = sp[3];
    temp[2] = sp[0];
    temp[3] = sp[5];
    temp[5] = sp[2];
    return temp;
}

bool Rotate(string temp) {
    bool flag = false;
    // 1번면과 6번면이 같을경우 오른쪽으로 회전
    if ((temp[0] == cube2[0]) && (temp[5] == cube2[5])) {
        while (true) {
            temp = rotateRight(temp);
            if (cube2 == temp) return true;
            if (temp == cube1) break;
        }
        if (flag)
            return false;
        else
            return true;
    }
    // 3번면과 4번면이 같을경우 왼쪽으로 회전
    if ((temp[2] == cube2[2]) && (temp[3] == cube2[3])) {
        while (true) {
            temp = rotateUp(temp);
            if (cube2 == temp) return true;
            if (temp == cube1) break;
        }
    }
    // 2번면과 5번
    if ((temp[1] == cube2[1]) && (temp[4] == cube2[4])) {
        while (true) {
            temp = clockwiseDiretion(temp);
            if (cube2 == temp) return true;
            if (temp == cube1) break;
        }
    }
    return false;
}

bool solve() {
    if (cube1 == cube2) return true;
    string tmp = cube1;
    if (Rotate(cube1))
        return true;
    else {
        /**
         * 같은 방향으로만 회전한게 아닐경우
         * cube2의 1번면과 i번면 6번면과 i와 마주보는면을 찾은다음
         * 회전을 시키고 cube1을 회전시킨것과 같은지 비교하고
         * for문을 빠져나간다면 cube1과 cube2는 같은 방법으로
         * 색칠한것이 아님
         */
        for (int i = 1; i < 6; i++) {
            if (cube1[i] == cube2[0]) {
                switch (i) {
                    case 1:
                        if (cube2[5] == cube1[4]) {
                            cube1 = rotateUp(cube1);
                            if (Rotate(cube1)) return true;
                            cube1 = tmp;
                        }

                        break;
                    case 2:
                        if (cube2[5] == cube1[3]) {
                            cube1 = clockwiseDiretion(cube1);
                            if (Rotate(cube1)) return true;
                            cube1 = tmp;
                        }
                        break;
                    case 3:
                        if (cube2[5] == cube1[2]) {
                            cube1 = counterclockwise(cube1);
                            if (Rotate(cube1)) return true;
                            cube1 = tmp;
                        }
                        break;
                    case 4:
                        if (cube2[5] == cube1[1]) {
                            cube1 = rotateDown(cube1);
                            if (Rotate(cube1)) return true;
                            cube1 = tmp;
                        }
                        break;
                    case 5:
                        if (cube2[5] == cube1[0]) {
                            for (int i = 0; i < 2; i++)
                                cube1 = rotateDown(cube1);
                            if (Rotate(cube1)) return true;
                        }
                        break;
                }
            }
        }
    }
    return false;
}

int main() {
    while (!inp.eof()) {
        inp >> cube;
        if (cube == "") break;
        cube1 = cube.substr(0, 6);
        cube2 = cube.substr(6, 12);
        if (!chkRGBNum()) {
            out << "FALSE\n";
            continue;
        }
        if (solve())
            out << "TRUE\n";
        else
            out << "FALSE\n";
        cube = "";
    }

    inp.close();
    out.close();
    return 0;
}