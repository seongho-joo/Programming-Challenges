#include <iostream>
#include <fstream>
using namespace std;

int Type3(int N, int M, int s, int k) {
	int res = 0;
	int vector = 1, row, col; // vector�� ������ ���ϴ� ����, row col�� �࿭�� �����ϴ� ����
	switch (s) {
	case 1: {
		row = M; col = N - 1; // �������̳� �������� �� ���� N-1
		while (1) {
			if (vector % 4 == 1) { //  �� -> ��
				if (k - row <= 0) { //k�� M���� ���� ��
					res += k;
					break;
				}
				else { // k�� M���� Ŭ ��
					res += row; // �Ʒ��� ���ϱ� �ʱⰪ�� row�� ����
					k -= row; // k�� row��ŭ ������ row�� ����
					row--; // �� �������� ���� �Ÿ�? �� �۾ƴϱ� row�� ����
					vector++;
				}
			}
			else if (vector % 4 == 2) { // �� -> ��
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
			else if (vector % 4 == 3) { // �� - > ��
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
			else { // �� -> ��
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
			if (vector % 4 == 0) { //  �� -> ��
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
			else if (vector % 4 == 1) { // �� -> ��
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
			else if (vector % 4 == 2) { // �� - > ��
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
			else { // �� -> ��
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
			if (vector % 4 == 3) { //  �� -> ��
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
			else if (vector % 4 == 0) { // �� -> ��
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
			else if (vector % 4 == 1) { // �� - > ��
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
			else { // �� -> ��
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
			if (vector % 4 == 2) { //  �� -> ��
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
			else if (vector % 4 == 3) { // �� -> ��
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
			else if (vector % 4 == 0) { // �� - > ��
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
			else { // �� -> ��
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
				if (k - col <= 0) { // �� -> ��
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
			else if (vector % 4 == 2) { // �� -> ��
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
			else if (vector % 4 == 3) { // �� - > ��
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
			else { // �� -> ��
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
				if (k - col <= 0) { // �� -> ��
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
			else if (vector % 4 == 3) { // �� -> ��
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
			else if (vector % 4 == 0) { // �� - > ��
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
			else { // �� -> ��
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
				if (k - col <= 0) { // �� -> ��
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
			else if (vector % 4 == 0) { // �� -> ��
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
			else if (vector % 4 == 1) { // �� - > ��
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
			else { // �� -> ��
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
				if (k - col <= 0) { // �� -> ��
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
			else if (vector % 4 == 1) { // �� -> ��
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
			else if (vector % 4 == 2) { // �� - > ��
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
			else { // �� -> ��
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