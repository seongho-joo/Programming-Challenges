#include <iostream>
#include <fstream>
using namespace std;


int Width(int N, int M, int width[50][50], int column[50][50]) {
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (i == N - 1) break;
		for (int j = 0; j < M - 1; j++) {
			if (width[i][j] == width[i + 1][j]) { // 볼록한 곳이 같을 때
				if (column[i][j] != column[i][j + 1]) cnt = 1;
				else {
					cnt = 0;
					break; 
				}
			}
			else { // 볼록한 곳이 다를 때
				if (column[i][j] == column[i][j + 1]) cnt = 1;
				else {
					cnt = 0;
					break;
				}
			}
		}
		if (cnt == 0) break;
	}
	return cnt;
} 
int Column(int N, int M, int column[50][50], int width[50][50]) {
	int cnt = 0;
	for (int i = 0; i < N - 1; i++) {
		for (int j = 0; j < M; j++) {
			if (j == M - 1) break;
			if (column[i][j] == column[i][j + 1]) {
				if (width[i][j] != width[i + 1][j]) cnt = 1;
				else {
					cnt = 0;
					break;
				}
			}
			else {
				if (width[i][j] == width[i + 1][j]) cnt = 1;
				else {
					cnt = 0;
					break;
				}
			}
		}
		if (cnt == 0) break;
	}
	return cnt;
}

int main() {
	ifstream inp("paper.inp");
	ofstream out("paper.out");
	int T; // 경우의 수
	inp >> T;
	int N, M; // 가로 세로
	int convex; // 위로 볼록 1 아래로 볼록 0
	int width[50][50]; // 가로로 접힌 배열
	int column[50][50]; // 세로로 접힌 배열
	int result = 0;
	while (T--) {
		inp >> N >> M;
		int col, row;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M - 1; j++) {
				inp >> convex;
				width[i][j] = convex;
			}
		}
		for (int i = 0; i < N - 1; i++) {
			for (int j = 0; j < M; j++) {
				inp >> convex;
				column[i][j] = convex;
			}
		}
		row = Width(N, M, width, column);
		col = Column(N, M, column, width);
		if (row == 1 && col == 1) out << 1 << " ";
		else out << 0 << " ";
	}

	inp.close();
	out.close();
	return 0;
}