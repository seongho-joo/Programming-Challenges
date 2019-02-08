#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int Max = 99999, Min = 0; // K의 범위 값


int sequence(int A, int n) {
/*
	1 ~ k
	k+1 ~ 2k+1
	2k+2 ~ 3k+3
	이런 식으로 계차수열이 나타 나는데 k + x를 구하는 함수
*/
	if (A == 2)
		return 1;
	else
		return n + sequence(A - 1, n + 1);
}

int first(int A) {
	if (A == 1)
		return 0;
	else
		return sequence(A, 1);
}

int solution(int Q, int A) {
	int MAX = 0, MIN = 0; // line의 계차수열
	MIN = first(A); // 계차수열의 min 값
	MAX = first(A + 1) - 1; // 계차수열의 max 값
	double min_num, max_num; // k의 범위 값

	min_num = (double) (Q - MAX) / A; // (A-1) * k + MIN <= Q <= A * k + MAX
	max_num = (double) (Q - MIN) / (A - 1);
	min_num = ceil(min_num); max_num = floor(max_num); // min은 올림, max는 내림

	if (Max > max_num) Max = max_num;
	if (Min < min_num) Min = min_num;
	if (Max == Min) return Max;
	else return -1;
}

int main() {
	ifstream inp("line.inp");
	ofstream out("line.out");

	int T;
	inp >> T;
	int Q, A, res = 0, count = 1;
	int line;
	while (T--) {
		inp >> line; // 라인 수
		for (int i = 0; i < line; i++) {
			inp >> Q >> A;
			res = solution(Q, A);
			if (res == -1) count++;
		}
		if (res == -1) out << -1 << endl;
		else out << count << " " << res << endl;
		res = 0;
		count = 1;
		Max = 99999;
		Min = 0;
	}

	inp.close();
	out.close();
	return 0;
}