/**
 * Assignment 01 - Bowling 점수 계산하기
 */
#include <fstream>
#include <vector>
using namespace std;

struct Frame {
    int first, second, third;
};

vector<Frame> frame(10);

int solve() {
    int score = 0;
    for (int i = 0; i < 9; i++) {
        // strike
        if (frame[i].first == 10) {
            // dobule
            if (frame[i + 1].first == 10) {
                // turkey
                if (frame[i + 2].first == 10)
                    score += 30;
                else {
                    if (i == 8)
                        score += 20 + frame[i + 1].second;
                    else
                        score += 20 + frame[i + 2].first;
                }
            } else
                score += 10 + frame[i + 1].first + frame[i + 1].second;
        }
        // spair
        else if (frame[i].first + frame[i].second == 10)
            score += 10 + frame[i + 1].first;
        else
            score += frame[i].first + frame[i].second;
    }
    score += (frame[9].first + frame[9].second + frame[9].third);
    return score;
}

int main() {
    ifstream inp("bowling.inp");
    ofstream out("bowling.out");

    int T, data;
    inp >> T;

    Frame fr;

    while (T--) {
        frame.resize(10);
        for (int i = 0; i < 10; i++) {
            if (i == 9) {
                inp >> frame[i].first >> frame[i].second;
                if (frame[i].first + frame[i].second >= 10)
                    inp >> frame[i].third;
                continue;
            }
            inp >> frame[i].first;
            if (frame[i].first == 10) {
                frame[i].second = 0;
                frame[i].third = 0;
            } else {
                inp >> frame[i].second;
            }
        }
        out << solve() << '\n';
        frame.clear();
    }
    return 0;
}