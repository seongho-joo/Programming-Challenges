#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Timeline {
public:
	int point; // 시작 점, 끝 점
	int year;
	int month;
	int day;
	int total; // 정렬을 시키는 기준
};
vector<Timeline> timeline;
bool compare(const Timeline& x, const Timeline& y) {
	if (x.total == y.total) return x.point > y.point;
	return x.total < y.total;
}

int Solution(int N) {
	int Max = -1, row = 0;
	for (int i = 0; i < N * 2; i++) {
		if (!timeline[i].point) {
			row++;
			Max = max(row, Max); // row 갱신 
		}
		else if (timeline[i].point) 
			row--;
	}
	return Max;
}

int main() {
	ifstream inp("timeline.inp");
	ofstream out("timeline.out");
	Timeline tl;
	int T;
	inp >> T;
	while (T--) {
		int N;
		char dot;
		inp >> N;
		timeline.reserve(N);
		for (int i = 0; i < N * 2;i++) {
			inp >> tl.year >> dot >> tl.month >> dot >> tl.day;
			if (i % 2 == 0) tl.point = 0; // 시작
			else tl.point = 1; // 끝
			tl.total = (tl.year * 10000) + (tl.month * 100) + tl.day;
			timeline.push_back(tl);
		}
		sort(timeline.begin(), timeline.end(), compare);
		out << Solution(N) << endl;
		timeline.clear();
	}
	inp.close();
	out.close();
	return 0;
}