#include <iostream>
#include <fstream>
using namespace std;

int Type3(int N, int M, int s, int k) {
	int res = 0;
	int vector = 1, row, col; // vector는 방향을 정하는 변수, row col은 행열을 저장하는 변수
	switch (s) {
	case 1: {
		row = M; col = N - 1; // 오른쪽이나 왼쪽으로 갈 때는 N-1
		while (1) {
			if (vector % 4 == 1) { //  왼 -> 오
				if (k - row <= 0) { //k가 M보다 작을 때
					res += k;
					break;
				}
				else { // k가 M보다 클 때
					res += row; // 아래로 가니깐 초기값을 row로 해줌
					k -= row; // k가 row만큼 갔으니 row를 빼줌
					row--; // 한 바퀴돌면 도는 거리? 가 작아니깐 row를 빼줌
					vector++;
				}
			}
			else if (vector % 4 == 2) { // 위 -> 아
				if (k - col <= 0) {
					res += k * M;
					break;
				}
				else {
					res += M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else if (vector % 4 == 3) { // 오 - > 왼
				if (k - row <= 0) {
					res -= k;
					break;
				}
				else {
					res -= row;
					k -= row;
					row--;
					vector++;
				}
			}
			else { // 아 -> 위
				if (k - col <= 0) {
					res -= M * k;
					break;
				}
				else {
					res -= M * col;
					k -= col;
					col--;
					vector++;
				}
			}
		}
		break;
	}
	case 2: {
		row = M - 1; col = N;
		while (1) {
			if (vector % 4 == 0) { //  왼 -> 오
				if (k - row <= 0) {
					res += k;
					break;
				}
				else {
					res += row;
					k -= row;
					row--;
					vector++;
				}
			}
			else if (vector % 4 == 1) { // 위 -> 아
				if (k - col <= 0) {
					res += k * M;
					break;
				}
				else {
					res += M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else if (vector % 4 == 2) { // 오 - > 왼
				if (k - row <= 0) {
					res -= k;
					break;
				}
				else {
					res -= row;
					k -= row;
					row--;
					vector++;
				}
			}
			else { // 아 -> 위
				if (k - col <= 0) {
					res -= M * k;
					break;
				}
				else {
					res -= M * col;
					k -= col;
					col--;
					vector++;
				}
			}
		}
		break;
	}
	case 3: {
		row = M; col = N - 1;
		res = N * M + 1;
		while (1) {
			if (vector % 4 == 3) { //  왼 -> 오
				if (k - row <= 0) {
					res += k;
					break;
				}
				else {
					res += row;
					k -= row;
					row--;
					vector++;
				}
			}
			else if (vector % 4 == 0) { // 위 -> 아
				if (k - col <= 0) {
					res += k * M;
					break;
				}
				else {
					res += M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else if (vector % 4 == 1) { // 오 - > 왼
				if (k - row <= 0) {
					res -= k;
					break;
				}
				else {
					res -= row;
					k -= row;
					row--;
					vector++;
				}
			}
			else { // 아 -> 위
				if (k - col <= 0) {
					res -= M * k;
					break;
				}
				else {
					res -= M * col;
					k -= col;
					col--;
					vector++;
				}
			}
		}
		break;
	}
	case 4: {
		row = M - 1; col = N;
		res = N * M - row + M;
		while (1) {
			if (vector % 4 == 2) { //  왼 -> 오
				if (k - row <= 0) {
					res += k;
					break;
				}
				else {
					res += row;
					k -= row;
					row--;
					vector++;
				}
			}
			else if (vector % 4 == 3) { // 위 -> 아
				if (k - col <= 0) {
					res += k * M;
					break;
				}
				else {
					res += M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else if (vector % 4 == 0) { // 오 - > 왼
				if (k - row <= 0) {
					res -= k;
					break;
				}
				else {
					res -= row;
					k -= row;
					row--;
					vector++;
				}
			}
			else { // 아 -> 위
				if (k - col <= 0) {
					res -= M * k;
					break;
				}
				else {
					res -= M * col;
					k -= col;
					col--;
					vector++;
				}
			}
		}
		break;
	}
	}
	return res;
}
int Type4(int N, int M, int s, int k) {
	int res = 0;
	int row, col, vector = 1;
	switch (s) {
	case 1: {
		res = -M + 1;
		row = M - 1; col = N;
		while (1) {
			if (vector % 4 == 1) {
				if (k - col <= 0) { // 위 -> 아
					res += k * M;
					break;
				}
				else {
					res += M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else if (vector % 4 == 2) { // 왼 -> 오
				if (k - row <= 0) {
					res += k;
					break;
				}
				else {
					res += row;
					k -= row;
					row--;
					vector++;
				}
			}
			else if (vector % 4 == 3) { // 아 - > 위
				if (k - col <= 0) {
					res -= k * M;
					break;
				}
				else {
					res -= M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else { // 오 -> 왼
				if (k - row <= 0) {
					res -= k;
					break;
				}
				else {
					res -= row;
					k -= row;
					row--;
					vector++;
				}
			}
		}
		break;
	}
	case 2: {
		res = M + 1;
		row = M; col = N - 1;
		while (1) {
			if (vector % 4 == 2) {
				if (k - col <= 0) { // 위 -> 아
					res += k * M;
					break;
				}
				else {
					res += M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else if (vector % 4 == 3) { // 왼 -> 오
				if (k - row <= 0) {
					res += k;
					break;
				}
				else {
					res += row;
					k -= row;
					row--;
					vector++;
				}
			}
			else if (vector % 4 == 0) { // 아 - > 위
				if (k - col <= 0) {
					res -= k * M;
					break;
				}
				else {
					res -= M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else { // 오 -> 왼
				if (k - row <= 0) {
					res -= k;
					break;
				}
				else {
					res -= row;
					k -= row;
					row--;
					vector++;
				}
			}
		}
		break;
	}
	case 3: {
		res = N * M + M;
		row = M - 1; col = N;
		while (1) {
			if (vector % 4 == 3) {
				if (k - col <= 0) { // 위 -> 아
					res += k * M;
					break;
				}
				else {
					res += M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else if (vector % 4 == 0) { // 왼 -> 오
				if (k - row <= 0) {
					res += k;
					break;
				}
				else {
					res += row;
					k -= row;
					row--;
					vector++;
				}
			}
			else if (vector % 4 == 1) { // 아 - > 위
				if (k - col <= 0) {
					res -= k * M;
					break;
				}
				else {
					res -= M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else { // 오 -> 왼
				if (k - row <= 0) {
					res -= k;
					break;
				}
				else {
					res -= row;
					k -= row;
					row--;
					vector++;
				}
			}
		}
		break;
	}
	case 4: {
		row = M; col = N - 1;
		res = N * M - M;
		while (1) {
			if (vector % 4 == 0) {
				if (k - col <= 0) { // 위 -> 아
					res += k * M;
					break;
				}
				else {
					res += M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else if (vector % 4 == 1) { // 왼 -> 오
				if (k - row <= 0) {
					res += k;
					break;
				}
				else {
					res += row;
					k -= row;
					row--;
					vector++;
				}
			}
			else if (vector % 4 == 2) { // 아 - > 위
				if (k - col <= 0) {
					res -= k * M;
					break;
				}
				else {
					res -= M * col;
					k -= col;
					col--;
					vector++;
				}
			}
			else { // 오 -> 왼
				if (k - row <= 0) {
					res -= k;
					break;
				}
				else {
					res -= row;
					k -= row;
					row--;
					vector++;
				}
			}
		}
		break;
	}
	}
	return res;
}
int main() {
	ifstream in("grid2.inp");
	ofstream out("grid2.out");

	int T = 0, N = 0, M = 0, t, s, k;
	int res = 0;
	int index = 1;
	in >> T;
	while (T--) {
		in >> N >> M >> t >> s >> k;
		if (t == 3) {
			res = Type3(N, M, s, k);
			out << res << "\n";
		}
		else {
			res = Type4(N, M, s, k);
			out << res << "\n";
		}
	}
	in.close();
	out.close();
	return 0;
}